#include "async.h"

Persistent<String> kBusyMsg;

void tryCallCatch(Handle<Function> fn, Handle<Object> context, int argc, Handle<Value>* argv) {
  TryCatch try_catch;

  fn->Call(context, argc, argv);

  if (try_catch.HasCaught())
    FatalException(try_catch);
}

void sendToThreadPool(FuncPool execute, FuncDone done, AsyncOpBase* data){
  uv_work_t* aReq = new uv_work_t;
  aReq->data = data;

  uv_queue_work(uv_default_loop(), aReq, execute, done);

  data->RefUv(aReq);
}

void initAsync (Handle<Object> target) {
  kBusyMsg = Persistent<String>::New(String::New("object busy with async op"));
}
