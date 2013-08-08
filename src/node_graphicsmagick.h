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
  eInt32, eUint32, eBoolean, eString, eObject, eArray, eFunction, eNull, //fix: moved up function & null
  eBuffer,
  eObjectColor, eObjectGeometry, eObjectImage
};

//Checks arguments against signature and returns if they match.
//Also sets optionals - for each optional in the signature sets the index in args, or -1 if it is not present.
bool checkArguments(int signature[], const Arguments& args, int optionals[]);

//Returns a ThrowException for the specified signature.
Handle<Value> throwSignatureErr(int signature[]);

//Returns a ThrowException for a method with multiple signatures.
Handle<Value> throwSignatureErr(int *signatures[], int sigN);

//Checks if a JS Object is of Geometry type (as on /doc/Geometry.md).
bool isObjectGeometry(Handle<Value> obj);

//Converts a JS Geometry Object to Magick::Geometry. Assumes the JS Geometry Object is valid.
Magick::Geometry* createObjectGeometry(Handle<Value> obj);

//Checks if a JS Object is of Color type (as on /doc/Color.md).
bool isObjectColor(Handle<Value> obj);

//Converts a JS Color  Object to Magick::Color. Assumes the JS Color  Object is valid.
Magick::Color* createObjectColor(Handle<Value> obj);

//Generic structure used to store signature arguments values, the action and return value.
//fix: 'data' isn't descriptive; GenericFunctionCall? GenericLibOp?
struct GenericData {
  //Generic data store for a single argument.
  //fix: 'item' not descriptive; perhaps 'Value'?
  struct Item {
    Item() : type(eEnd) {}
    ~Item() {
      switch (type) {
      case eString:         delete string;                      break;
      case eObjectColor:    delete (Magick::Color*)    pointer; break;
      case eObjectGeometry: delete (Magick::Geometry*) pointer; break;
      }
    }
    Item& operator=(const Item&) { assert(0); } //some items may need deep copy
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
  
  GenericData();
  //Creates the generic data. Assumes the arguments, optionals and signature match.
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
      case eInt32:          val[aSigN].int32 = args[aArgInd]->Int32Value();                         break;
      case eUint32:         val[aSigN].uint32 = args[aArgInd]->Uint32Value();                       break;
      case eBoolean:        val[aSigN].boolean = args[aArgInd]->BooleanValue();                     break;
      case eString:         val[aSigN].string = new std::string(*String::Utf8Value(args[aArgInd])); break;
      case eObjectColor:    val[aSigN].pointer = createObjectColor(args[aArgInd]);                  break;
      case eObjectGeometry: val[aSigN].pointer = createObjectGeometry(args[aArgInd]);               break;
      case eFunction:                                                                               break;
      default: assert(0);
      }
      val[aSigN].type = abs(signature[aSigN]);
    }
  }
  ~GenericData() { if (val) delete[] val; }
  int action;
  Item* val;
  Item retVal;
};

//Function used to wrap sync/async methods easily.
/*
1. Checks if the arguments are in accordance with the signature (if required);
    If checkArguments is false, optionals must be supplied. Used for methods with multiple signatures.
2. Generates the GenericData from the arguments.
3. If the last argument is a function:
  3.1.1 Asynchronously calls Generic_process, which must implement tha data processing.
    Will have access to a GenericData object which also contains the action.
    Will have access to the calling object, obtained from unwrapping the arguments.
  3.1.2 When the processing is complete it calls Generic_convert to generate de JS return objects.
    Will have access to a GenericData object in which the return data should have been set in Generic_process.
else
  3.2 Synchronously calls Generic_process and Generic_convert.

Classes must implement:
  void Generic_process(void* pData, void* pThat); - the
  Handle<Value> Image::Generic_convert(void* pData);

Accepts inherited classes
T is the derived class, for which the Generic_process and Generic_convert will be called
N is the base class. Used for async operations.
*/
//TODO: see if this can be moved to async.h
template<class T, class N>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], bool checkArgs = true, int* optionals = NULL, GenericData::Item* defaults = NULL) {
  HandleScope scope;
  int aLength = 0;
  for (int a = 0; signature[a] != eEnd; ++a)
    if (signature[a] < 0)
      aLength++;
  int* aOptionals;
  if (checkArgs) { //fix: require caller to call checkArguments always, or never by taking list of signatures?
    assert(aLength > 0);
    aOptionals = new int[aLength]; //fix: mem leak if return throwSignatureErr below?
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

//generic_start for classes which are not derived
template<class T>
Handle<Value> generic_start(int act, const Arguments& args, int signature[], bool checkArgs = true, int* optionals = NULL, GenericData::Item* defaults = NULL) {
  return generic_start<T,T>(act, args, signature, checkArgs, optionals, defaults);
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
