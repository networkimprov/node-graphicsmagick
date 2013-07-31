#ifndef _NODE_GRAPHICSMAGICK_H_
#define _NODE_GRAPHICSMAGICK_H_

#include <Magick++.h>

#include "async.h"
#include <string.h>

enum ArgumentType {
  eEnd,
  eInt32,
  eUint32,
  eBoolean,
  eString,
  eObject,
  eArray,
  eBuffer,
  eObjectColor,
  eObjectGeometry,
  eObjectImage,
  eNull,
  eFunction
};

bool checkArguments(int signature[], const Arguments& args, int optionals[]);
Handle<Value> throwSignatureErr(int signature[]);
Handle<Value> throwSignatureErr(int *signatures[], int sigN);

Magick::Geometry* createObjectGeometry(Handle<Value> obj);
Magick::Color* createObjectColor(Handle<Value> obj);

struct GenericData {
  struct Item {
    Item() : type(eEnd) {};
    void setString(const std::string &str) { if (type == eString) *string = str; else { string = new std::string(str); type = eString; } };
    ~Item() {
      switch (type) {
      case eString:         delete string;                      break;
      case eObjectColor:    delete (Magick::Color*)    pointer; break;
      case eObjectGeometry: delete (Magick::Geometry*) pointer; break;
      }
    }
    void setObjectType(void* p, int t) {
      type = t;
      pointer = p;
    }
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
  int action;
  Item* val;
  Item retVal;
  GenericData();
  GenericData(int act, const Arguments& args, int signature[], int optionals[], Item* defaults = NULL) : action(act) {
    int aLength;
    for (aLength = 0; signature[aLength] != eEnd; ++aLength);
    val = new Item[aLength];
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
      case eInt32:          val[aSigN].int32 = args[aArgInd]->Int32Value();                                 break;
      case eUint32:         val[aSigN].uint32 = args[aArgInd]->Uint32Value();                               break;
      case eBoolean:        val[aSigN].boolean = args[aArgInd]->BooleanValue();                             break;
      case eString:         val[aSigN].setString(*String::Utf8Value(args[aArgInd]));                        break;
      case eObjectColor:    val[aSigN].setObjectType(createObjectColor(args[aArgInd]), eObjectColor);       break;
      case eObjectGeometry: val[aSigN].setObjectType(createObjectGeometry(args[aArgInd]), eObjectGeometry); break;
      case eFunction: break;
      default: assert(0);
      }
    }
  }
  ~GenericData() { if (val) delete[] val; }
};

//if checkArguments = false, optionals must be supplied
template<class T, class N>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], bool checkArgs = true, int* optionals = NULL, GenericData::Item* defaults = NULL) {
  HandleScope scope;
  int aLength = 0;
  for (int a = 0; signature[a] != eEnd; ++a)
    if (signature[a]<0) aLength++;
  int* aOptionals;
  if (checkArgs) {
    assert(aLength > 0);
    aOptionals = new int[aLength];
    if (!checkArguments(signature, args, aOptionals))
      return throwSignatureErr(signature);
  } else
    aOptionals = optionals;
  GenericData* aData = new GenericData(act, args, signature, aOptionals, defaults); //deleted by Generic_convert on non error
  Handle<Value> aResult = Undefined();
  try {
    aResult = invoke<N>(aOptionals[aLength-1] >= 0, args, (void*)aData, T::Generic_process, T::Generic_convert);
  } catch (Handle<Value> ex) {
    if (checkArgs)
      delete[] aOptionals;
    delete aData;
    return ThrowException(ex);
  }
  if (checkArgs)
    delete[] aOptionals;
  return scope.Close(aResult);
}

template<class T>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], bool checkArgs = true, int* optionals = NULL, GenericData::Item* defaults = NULL) {
  return generic_start<T,T>(act, args, signature, checkArgs, optionals, defaults);
}

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
