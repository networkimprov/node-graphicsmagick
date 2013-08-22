#include "node_graphicsmagick.h"

using namespace v8;
using namespace node;

using namespace std;

void init(Handle<Object> exports) {
  initAsync(exports);
  Magick::InitializeMagick(NULL);
  Image::Init(exports);
}

NODE_MODULE(node_graphicsmagick, init);

//fix: make JS accessible createGeometry/Color functions, which create GM objects wrapped in an External
// user calls it and passes result to Image methods
// this is simpler than defining complete JS classes

bool isObjectGeometry(Handle<Value> obj) {
  if (!obj->IsObject() || obj->IsFunction())
   return false;
  Local<Object> aObj = obj->ToObject();
  Local<String> aKey;
  return !((!aObj->Has(aKey = String::New("width")) || !aObj->Get(aKey)->IsUint32()) ||
      (!aObj->Has(aKey = String::New("height")) || !aObj->Get(aKey)->IsUint32()) ||
     (aObj->Has(aKey = String::New("xOff")) && !aObj->Get(aKey)->IsUint32()) ||
     (aObj->Has(aKey = String::New("yOff")) && !aObj->Get(aKey)->IsUint32()) ||
     (aObj->Has(aKey = String::New("xNegative")) && !aObj->Get(aKey)->IsBoolean()) ||
     (aObj->Has(aKey = String::New("yNegative")) && !aObj->Get(aKey)->IsBoolean()) ||
     (aObj->Has(aKey = String::New("percent")) && !aObj->Get(aKey)->IsBoolean()) ||
     (aObj->Has(aKey = String::New("aspect")) && !aObj->Get(aKey)->IsBoolean()) ||
     (aObj->Has(aKey = String::New("greater")) && !aObj->Get(aKey)->IsBoolean()) ||
     (aObj->Has(aKey = String::New("less")) && !aObj->Get(aKey)->IsBoolean()));
}

Magick::Geometry* createObjectGeometry(Handle<Value> obj) {
  Local<Object> aObj = obj->ToObject();
  Local<String> aKey;
  Magick::Geometry* aGeometry = new Magick::Geometry(
    aObj->Get(String::New("width"))->ToUint32()->Value(),
    aObj->Get(String::New("height"))->ToUint32()->Value(),
    aObj->Has(aKey = String::New("xOff")) ? aObj->Get(aKey)->ToUint32()->Value() : 0,
    aObj->Has(aKey = String::New("yOff")) ? aObj->Get(aKey)->ToUint32()->Value() : 0,
    aObj->Has(aKey = String::New("xNegative")) ? aObj->Get(aKey)->ToBoolean()->Value() : false,
    aObj->Has(aKey = String::New("yNegative")) ? aObj->Get(aKey)->ToBoolean()->Value() : false
  );
  if (aObj->Has(aKey = String::New("percent")))
    aGeometry->percent(aObj->Get(aKey)->ToBoolean()->Value());
  if (aObj->Has(aKey = String::New("aspect")))
    aGeometry->aspect(aObj->Get(aKey)->ToBoolean()->Value());
  if (aObj->Has(aKey = String::New("greater")))
    aGeometry->greater(aObj->Get(aKey)->ToBoolean()->Value());
  if (aObj->Has(aKey = String::New("less")))
    aGeometry->less(aObj->Get(aKey)->ToBoolean()->Value());
  return aGeometry;
}

bool isObjectColor(Handle<Value> obj) {
  if (!obj->IsObject() || obj->IsFunction())
    return false;
  Local<Object> aObj = obj->ToObject();
  Local<String> aKey1, aKey2, aKey3, aKey4;
  if (aObj->Has(aKey1 = String::New("red")) && aObj->Has(aKey2 = String::New("green")) && aObj->Has(aKey3 = String::New("blue")))
    return !((!aObj->Get(aKey1)->IsNumber() || !aObj->Get(aKey2)->IsNumber() || !aObj->Get(aKey3)->IsNumber()) || (aObj->Has(aKey4 = String::New("alpha")) && !aObj->Get(aKey4)->IsNumber()));
  if (aObj->Has(aKey1 = String::New("redQuantum")) && aObj->Has(aKey2 = String::New("greenQuantum")) && aObj->Has(aKey3 = String::New("blueQuantum")))
    return !((!aObj->Get(aKey1)->IsUint32() || !aObj->Get(aKey2)->IsUint32() || !aObj->Get(aKey3)->IsUint32()) || (aObj->Has(aKey4 = String::New("alphaQuantum")) && !aObj->Get(aKey4)->IsUint32()));
  if (aObj->Has(aKey1 = String::New("shade")))
    return !((!aObj->Get(aKey1)->IsNumber()) || (aObj->Has(aKey4 = String::New("alpha")) && !aObj->Get(aKey4)->IsNumber()));
  if (aObj->Has(aKey1 = String::New("mono")))
    return !((!aObj->Get(aKey1)->IsBoolean()) || (aObj->Has(aKey4 = String::New("alpha")) && !aObj->Get(aKey4)->IsNumber()));
  if (aObj->Has(aKey1 = String::New("hue")) && aObj->Has(aKey2 = String::New("saturation")) && aObj->Has(aKey3 = String::New("luminosity")))
    return !((!aObj->Get(aKey1)->IsNumber() || !aObj->Get(aKey2)->IsNumber() || !aObj->Get(aKey3)->IsNumber()) || (aObj->Has(aKey4 = String::New("alpha")) && !aObj->Get(aKey4)->IsNumber()));
  if (aObj->Has(aKey1 = String::New("Y")) && aObj->Has(aKey2 = String::New("U")) && aObj->Has(aKey3 = String::New("V")))
    return !(!aObj->Get(aKey1)->IsNumber() || !aObj->Get(aKey2)->IsNumber() || !aObj->Get(aKey3)->IsNumber());
  return false;
}

Magick::Color* createObjectColor(Handle<Value> obj) {
  Local<Object> aObj = obj->ToObject();
  Local<String> aKey1, aKey2, aKey3, aKey4;
  Magick::Color* aColor;
  if (aObj->Has(aKey1 = String::New("red")) && aObj->Has(aKey2 = String::New("green")) && aObj->Has(aKey3 = String::New("blue"))) {
    aColor = new Magick::ColorRGB(aObj->Get(aKey1)->ToNumber()->Value(), aObj->Get(aKey2)->ToNumber()->Value(), aObj->Get(aKey3)->ToNumber()->Value());
    if (aObj->Has(aKey4 = String::New("alpha")))
      aColor->alphaQuantum(aObj->Get(aKey4)->ToNumber()->Value());
  } else if (aObj->Has(aKey1 = String::New("redQuantum")) && aObj->Has(aKey2 = String::New("greenQuantum")) && aObj->Has(aKey3 = String::New("blueQuantum"))) {
    aColor = new Magick::Color(aObj->Get(aKey1)->ToUint32()->Value(), aObj->Get(aKey2)->ToUint32()->Value(), aObj->Get(aKey3)->ToUint32()->Value());
    if (aObj->Has(aKey4 = String::New("alphaQuantum")))
      aColor->alphaQuantum(aObj->Get(aKey4)->ToUint32()->Value());
  } else
    assert(0); //fix: really blow up if color spec incomplete?
  return aColor;
}

bool checkArguments(int signature[], const Arguments& args, int optionals[]) {
  int aArgN = 0, aOptN = 0;

  for (int aSigN=0; signature[aSigN] != eEnd; ++aSigN) {
    int aIsType;
    switch (abs(signature[aSigN])) {
    case eInt32:          aIsType = args[aArgN]->IsInt32();                                  break;
    case eUint32:         aIsType = args[aArgN]->IsUint32();                                 break;
    case eBoolean:        aIsType = args[aArgN]->IsBoolean();                                break;
    case eString:         aIsType = args[aArgN]->IsString();                                 break;
    case eArray:          aIsType = args[aArgN]->IsArray();                                  break;
    case eBuffer:
    case eObjectImage:
    case eObject:         aIsType = args[aArgN]->IsObject() && !args[aArgN]->IsFunction();   break;
    case eObjectColor:    aIsType = isObjectColor(args[aArgN]);                              break; //fix: isExternal
    case eObjectGeometry: aIsType = isObjectGeometry(args[aArgN]);                           break;
    case eNull:           aIsType = args[aArgN]->IsNull();                                   break;
    case eFunction:       aIsType = args[aArgN]->IsFunction();                               break;
    default: {
      std::string aEx("incorrect signature member: ");
      aEx += (char)(signature[aSigN] + '0');
      throw aEx;
      }
    }

    if (signature[aSigN] < 0) {
      optionals[aOptN] = aIsType ? aArgN++ : -1;
      ++aOptN;
    } else {
      if (!aIsType)
        return false;
      ++aArgN;
    }
  }

  return aArgN == args.Length();
}

static std::string generateSignatureString(int signature[]) {
  std::string aStr = "(";
  for (int aSigN=0; signature[aSigN] != eEnd; ++aSigN) {
    if (aSigN) aStr += ", ";
    if (signature[aSigN] < 0) aStr += "[";
    switch (abs(signature[aSigN])) {
    case eInt32:          aStr += "int32";    break;
    case eUint32:         aStr += "uint32";   break;
    case eBoolean:        aStr += "boolean";  break;
    case eString:         aStr += "string";   break;
    case eObject:         aStr += "object";   break;
    case eArray:          aStr += "array";    break;
    case eBuffer:         aStr += "Buffer";   break;
    case eObjectColor:    aStr += "Color";    break;
    case eObjectGeometry: aStr += "Geometry"; break;
    case eObjectImage:    aStr += "Image";    break;
    case eNull:           aStr += "null";     break;
    case eFunction:       aStr += "function"; break;
    default:              throw "incorrect sig member"; 
    }
    if (signature[aSigN] < 0) aStr += "]";
  }
  aStr += ")";
  return aStr;
}

Handle<Value> throwSignatureErr(int signature[]) {
  std::string aStr("arguments are ");
  aStr += generateSignatureString(signature);
  return ThrowException(v8::Exception::TypeError(String::New(aStr.c_str())));
}

Handle<Value> throwSignatureErr(SetType sets[]) {
  std::string aStr("arguments are ");
  int aSigN = 0;
  while (sets[aSigN].signature != NULL) {
    if (aSigN > 0)
      aStr += " or ";
    aStr += generateSignatureString(sets[aSigN].signature);
    aSigN++;
  }
  return ThrowException(v8::Exception::TypeError(String::New(aStr.c_str())));
}
