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

struct GenericData {
  struct Item {
    Item() : isStr(false) {};
    Item(const char *a) : isStr(true) { string = new std::string(a); };
    Item(double a) : dbl(a), isStr(false) {};
    Item(uint32_t a) : uint32(a), isStr(false) {};
    Item(int32_t a) : int32(a), isStr(false) {};
    Item(bool a) : boolean(a), isStr(false) {};
    Item(void* a) : isStr(false) {};
    Item& operator=(const Item& p) {
      if (this != &p) {
        unsetString();
        if (p.isStr)
          setString(*p.string);
        else
          memcpy (&dbl, &p.dbl, sizeof(double));
      }
      return *this;    // Return ref for multiple assignment
    }
    void setString(const std::string &str) { if (isStr) *string = str; else { string = new std::string(str); isStr = true; } };
    void unsetString() { if (isStr) { delete string; isStr = false; } };
    ~Item() { if (isStr) delete string; }
    union {
      double dbl;
      uint32_t uint32;
      int32_t int32;
      bool boolean;
      std::string* string;
      void* pointer;
    };
    bool isStr;
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
      case eInt32:    val[aSigN].int32 = args[aArgInd]->Int32Value();          break;
      case eUint32:   val[aSigN].uint32 = args[aArgInd]->Uint32Value();        break;
      case eBoolean:  val[aSigN].boolean = args[aArgInd]->BooleanValue();      break;
      case eString:   val[aSigN].setString(*String::Utf8Value(args[aArgInd])); break;
      case eFunction: break;
      default: assert(0);
      }
    }
  }
  ~GenericData() { if (val) delete[] val; }
};

template<class T, class N>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], GenericData::Item* defaults = NULL) {
  HandleScope scope;
  int aLength = 0;
  for (int a = 0; signature[a] != eEnd; ++a)
    if (signature[a]<0) aLength++;
  assert(aLength > 0);
  int* optionals = new int[aLength];
  if (!checkArguments(signature, args, optionals))
    return throwSignatureErr(signature);
  GenericData* aData = new GenericData(act, args, signature, optionals, defaults); //deleted by Generic_convert on non error
  Handle<Value> aResult = Undefined();
  try {
    aResult = invoke<N>(optionals[aLength-1] >= 0, args, (void*)aData, T::Generic_process, T::Generic_convert);
  } catch (Handle<Value> ex) {
    delete[] optionals;
    delete aData;
    return ThrowException(ex);
  }
  delete[] optionals;
  return scope.Close(aResult);
}

template<class T>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], GenericData::Item* defaults = NULL) {
  return generic_start<T,T>(act, args, signature, defaults);
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

};

#endif
