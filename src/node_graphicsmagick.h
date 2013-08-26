#ifndef _NODE_GRAPHICSMAGICK_H_
#define _NODE_GRAPHICSMAGICK_H_

#include <Magick++.h>

#include "async.h"
#include <string.h>

/*
  TODO: high level description of how the binding is implemented
*/

enum ArgumentType {
  eEnd,
  eInt32, eUint32, eBoolean, eString, eObject, eArray, eFunction, eNull,
  eBuffer,
  eObjectColor, eObjectGeometry, eObjectImage
};

//Used for methods with multiple signatures and actions.
struct SetType {
  int* signature;
  int action;
};

//Checks arguments against signature and returns if they match.
//Also sets optionals - for each optional in the signature sets the index in args, or -1 if it is not present.
bool checkArguments(int signature[], const Arguments& args, int optionals[]);

//Returns a ThrowException for the specified signature.
Handle<Value> throwSignatureErr(int signature[]);

//Returns a ThrowException for a method with multiple signatures.
Handle<Value> throwSignatureErr(SetType sets[]);

//Used to create a class that only has a constructor (Color, Geometry).
//only the constructor_template and New method must still be defined.
#define DECLARE_GENERIC_CLASS(cname)                                                      \
class cname : public node::ObjectWrap {                                                   \
public:                                                                                   \
  static Persistent<FunctionTemplate> constructor_template;                               \
  static void Init(v8::Handle<v8::Object> target) {                                       \
    constructor_template = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New)); \
    constructor_template->InstanceTemplate()->SetInternalFieldCount(1);                   \
    constructor_template->SetClassName(String::NewSymbol(#cname));                        \
    target->Set(String::NewSymbol(#cname), constructor_template->GetFunction());          \
  }                                                                                       \
  Magick::cname& get() { return *mElem; };                                                \
  void set(Magick::cname* pElem) { mElem = pElem; }                                       \
  void Reference() { this->Ref(); }                                                       \
  void Unreference() { this->Unref(); }                                                   \
private:                                                                                  \
  cname() : mElem(NULL) {}                                                                \
  ~cname() { if (mElem) delete mElem; }                                                   \
  Magick::cname* mElem;                                                                   \
  static v8::Handle<v8::Value> New(const v8::Arguments& args);                            \
};

DECLARE_GENERIC_CLASS(Color)
DECLARE_GENERIC_CLASS(Geometry)

//Generic structure used to store signature arguments values, the action and return value.
struct GenericFunctionCall {
  //Generic data store for a single argument.
  struct GenericValue {
    GenericValue() : type(eEnd) {}
    ~GenericValue() {
      switch (type) {
      case eString:         delete string;                        break;
      case eObjectColor:    ((Color*) pointer)->Unreference();    break;
      case eObjectGeometry: ((Geometry*) pointer)->Unreference(); break;
      }
    }
    GenericValue& operator=(const GenericValue&) { assert(0); } //todo: this will blow up on attempt to val[] = defaults[] below? //some items may need deep copy
    union {
      double dbl;
      uint32_t uint32;
      int32_t int32;
      bool boolean;
      std::string* string;
      void* pointer;
    };
    int type;
  };
  
  GenericFunctionCall();
  //Creates the generic function call. Assumes the arguments, optionals and signature match.
  GenericFunctionCall(int act, const Arguments& args, int signature[], int optionals[], GenericValue* defaults = NULL) : action(act) {
    int aLength;
    for (aLength = 0; signature[aLength] != eEnd; ++aLength);
    val = new GenericValue[aLength];
    for (int aOptN = 0, aSigN = 0; signature[aSigN] != eEnd; ++aSigN) {
      int aArgInd = signature[aSigN] < 0 && optionals[aOptN] >= 0 ? optionals[aOptN] : aSigN;
      if (signature[aSigN] < 0) {
        ++aOptN;
        if (optionals[aOptN-1] < 0) {
          if (abs(signature[aSigN]) != eFunction)
            val[aSigN] = defaults[aOptN-1];
          continue;
        }
      }
      switch (abs(signature[aSigN])) {
      case eInt32:          val[aSigN].int32 = args[aArgInd]->Int32Value();                                                                   break;
      case eUint32:         val[aSigN].uint32 = args[aArgInd]->Uint32Value();                                                                 break;
      case eBoolean:        val[aSigN].boolean = args[aArgInd]->BooleanValue();                                                               break;
      case eString:         val[aSigN].string = new std::string(*String::Utf8Value(args[aArgInd]));                                           break;
      case eObjectColor:    val[aSigN].pointer = (void*) GetInstance<Color>(args[aArgInd]); ((Color*) val[aSigN].pointer)->Reference();       break;
      case eObjectGeometry: val[aSigN].pointer = (void*) GetInstance<Geometry>(args[aArgInd]); ((Geometry*) val[aSigN].pointer)->Reference(); break;
      case eFunction:                                                                                                                         break;
      default: assert(0);
      }
      val[aSigN].type = abs(signature[aSigN]);
    }
  }
  ~GenericFunctionCall() { if (val) delete[] val; }
  int action;
  GenericValue* val;
  GenericValue retVal;
};

//Function used to wrap sync/async methods easily.
/*
1. Generates the GenericFunctionCall from the arguments.
2. If the last argument is a function:
  2.1.1 Asynchronously calls Generic_process, which must implement tha data processing.
    Will have access to a GenericFunctionCall object which also contains the action.
    Will have access to the calling object, obtained from unwrapping the arguments.
  2.1.2 When the processing is complete it calls Generic_convert to generate de JS return objects.
    Will have access to a GenericFunctionCall object in which the return data should have been set in Generic_process.
else
  2.2 Synchronously calls Generic_process and Generic_convert.

Assumes the arguments and signature match and that the optionals are set.

Classes must implement:
  void Generic_process(void* pData, void* pThat);
  Handle<Value> Image::Generic_convert(void* pData);

Accepts inherited classes
T is the derived class, for which the Generic_process and Generic_convert will be called
N is the base class. Used for async operations.
*/
//TODO: see if this can be moved to async.h

//fix: possible to use same args across _start functions so they can be merged?

template<class T, class N>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], int* optionals, GenericFunctionCall::GenericValue* defaults = NULL) {
  HandleScope scope;
  int aLength = 0;
  for (int a = 0; signature[a] != eEnd; ++a)
    if (signature[a] < 0)
      aLength++;
  GenericFunctionCall* aData = new GenericFunctionCall(act, args, signature, optionals, defaults); //deleted by Generic_convert on non error
  Handle<Value> aResult = Undefined();
  try {
    aResult = invoke<N>(optionals[aLength-1] >= 0, args, (void*)aData, T::Generic_process, T::Generic_convert);
  } catch (Handle<Value> ex) {
    delete aData;
    return ThrowException(ex);
  }
  return scope.Close(aResult);
}

//Calls generic_start but also checks if the arguments match the signature and generates the optionals.
//TODO: see if this can be moved to async.h
template<class T, class N>
Handle<Value> generic_check_start(int act, const Arguments& args, int signature[], GenericFunctionCall::GenericValue* defaults = NULL) {
  int aLength = 0;
  for (int a = 0; signature[a] != eEnd; ++a)
    if (signature[a] < 0)
      aLength++;
  int* aOptionals;
  assert(aLength > 0);
  aOptionals = new int[aLength];
  if (!checkArguments(signature, args, aOptionals)) {
    delete[] aOptionals;
    return throwSignatureErr(signature);
  }
  Handle<Value> aResult = generic_start<T, N>(act, args, signature, aOptionals, defaults);
  delete[] aOptionals;
  return aResult;
}

//generic_check_start with multiple signatures
//skip allows some signatures to be treated differently
template<class T, class N>
Handle<Value> generic_check_start(const Arguments& args, SetType sets[], GenericFunctionCall::GenericValue* defaults[] = NULL, int skip = 0) {
  Handle<Value> aResult;
  int aSize = 0;
  while (sets[aSize].signature != NULL) aSize++;
  int* aOptionals = new int[aSize], aN;
  for (aN = skip; aN < aSize; aN++)
    if (checkArguments(sets[aN].signature, args, aOptionals)) {
      aResult = generic_start<T, N>(sets[aN].action, args, sets[aN].signature, aOptionals, defaults == NULL? NULL : defaults[aN]);
      break;
    }
  if (aN == aSize)
    aResult = throwSignatureErr(sets);
  delete[] aOptionals;
  return aResult;
}


//generic_start for classes which are not derived
template<class T>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], int* optionals = NULL, GenericFunctionCall::GenericValue* defaults = NULL) {
  return generic_start<T,T>(act, args, signature, optionals, defaults);
}

//generic_check_start for classes which are not derived
template<class T>
Handle<Value> generic_check_start(int act, const Arguments& args, int signature[], GenericFunctionCall::GenericValue* defaults = NULL) {
  return generic_check_start<T, T>(act, args, signature, defaults);
}
template<class T>
Handle<Value> generic_check_start(const Arguments& args, SetType sets[], GenericFunctionCall::GenericValue* defaults[] = NULL, int skip = 0) {
  return generic_check_start<T, T>(args, sets, defaults, skip);
}

//The Image class - /doc/Image.md
class Image : public AsyncWrap<Image> {
public:
  static void Init(Handle<Object> target);

  static Persistent<FunctionTemplate> constructor_template;

  Magick::Image& getImage() { return *mImage; }
  void setImage(Magick::Image* pImg) { mImage = pImg; } //takes ownership of the image object

  static void Generic_process(void* data, void* that);
  static Handle<Value> Generic_convert(void* data);

protected:
  Image() : mImage(NULL) { }
  ~Image() { if (mImage) delete mImage; }

  Magick::Image* mImage;

  static Handle<Value> New(const Arguments& args);
  static Handle<Value> Write(const Arguments& args);
  static Handle<Value> WriteFile(const Arguments& args);

};

#endif
