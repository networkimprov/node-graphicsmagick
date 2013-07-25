#ifndef _ASYNC_H_
#define _ASYNC_H_

#include <v8.h>
#include <node.h>
#include <string>

using namespace v8;
using namespace node;
using std::string;

void initAsync (Handle<Object> target);

void tryCallCatch(Handle<Function> fn, Handle<Object> context, int argc, Handle<Value>* argv);

template <class T>
T* GetInstance(Handle<Value> val) {
  if (val->IsObject() && T::constructor_template->HasInstance(val->ToObject()))
    return ObjectWrap::Unwrap<T>(val->ToObject());
  return NULL;
}

typedef void (*FuncPool) (uv_work_t* req);
typedef void (*FuncDone) (uv_work_t* req, int );

extern Persistent<String> kBusyMsg;

struct AsyncOpBase {
  AsyncOpBase(Handle<Function> cb)
    : watcherHandle(NULL), callback(), error(NULL) {
    callback = Persistent<Function>::New(cb);
  }
  virtual ~AsyncOpBase() {
    if (error) delete error;
    if (watcherHandle != NULL)
      uv_unref((uv_handle_t*) watcherHandle);
    callback.Dispose();
  }
  void RefUv(uv_work_t*& p) {
    uv_ref((uv_handle_t*) &p);
    watcherHandle = p;
  }
  uv_work_t* watcherHandle;
  Persistent<Function> callback;
  string* error;
};

void sendToThreadPool(FuncPool execute, FuncDone done, AsyncOpBase* data);

typedef void (*FuncProcess) (void* data, void* that);
typedef Handle<Value> (*FuncConvert) (void* data);

template <class T>
struct AsyncOp : public AsyncOpBase {
  AsyncOp(Handle<Object> ob, Handle<Function> cb)
    : AsyncOpBase(cb), object(ObjectWrap::Unwrap<T>(ob)) {
    if (object->mBusy)
      throw Exception::Error(kBusyMsg);
    object->mBusy = true;
    object->Ref();
  }
  AsyncOp(T* ob, Handle<Function> cb, void* dt, FuncProcess pr, FuncConvert cv)
    : AsyncOpBase(cb), object(ob), data(dt), process(pr), convert(cv) {
    object->Ref();
  }
  virtual ~AsyncOp() { object->Unref(); }
  void poolDone() { object->mBusy = false; }
  T* object;
  void* data;
  FuncProcess process;
  FuncConvert convert;
};

template<class T>
void async_pool(uv_work_t* req) {
  AsyncOp<T>* aAsOp = (AsyncOp<T>*)req->data;
  try {
    (*aAsOp->process)(aAsOp->data, aAsOp->object);
  } catch (std::exception& err) {
    aAsOp->error = new string(err.what());
  }
  aAsOp->object->mBusy = false;
  return;
}

template<class T>
void async_done(uv_work_t* req, int) {
  HandleScope scope;
  AsyncOp<T>* aAsOp = (AsyncOp<T>*)req->data;
  Handle<Value> aArgv[2];
  if (aAsOp->error) {
    aArgv[0] = Exception::Error(String::New(aAsOp->error->c_str()));
  } else {
    aArgv[0] = Null();
    aArgv[1] = (*aAsOp->convert)(aAsOp->data);
  }
  tryCallCatch(aAsOp->callback, aAsOp->object->handle_, aAsOp->error ? 1 : 2, aArgv);
  delete aAsOp;
  delete req;
  return;
}

template<class T>
Handle<Value> invoke(bool async, const Arguments& args, void* data, FuncProcess process, FuncConvert convert) {
  T* that = ObjectWrap::Unwrap<T>(args.This());
  if (that->mBusy) 
    throw Exception::Error(kBusyMsg);
  if (async) {
    that->mBusy = true;
    AsyncOp<T>* aAsOp = new AsyncOp<T>(that, Local<Function>::Cast(args[args.Length()-1]), data, process, convert);
    sendToThreadPool(async_pool<T>, async_done<T>, aAsOp);
    return Undefined();
  } else {
    try {
      process(data, that);
    } catch (std::exception& err) {
      throw Exception::Error(String::New(err.what()));
    }
    return convert(data);
  }
}

template <class T>
class AsyncWrap : public ObjectWrap {
public:
  void AddReference() { Ref(); }
  void RemoveReference() { Unref(); }
protected:
  AsyncWrap() : ObjectWrap(), mBusy(false) {}
  ~AsyncWrap() {}

  bool mBusy;

  friend struct AsyncOp<T>;
  friend Handle<Value> invoke<T>(bool async, const Arguments& args, void* data, FuncProcess process, FuncConvert convert);
  friend void async_pool<T>(uv_work_t* req);
};

#endif
