#include "node_graphicsmagick.h"
#include <node_buffer.h>

using namespace v8;
using namespace node;

using namespace std;

void init(Handle<Object> exports) {
  initAsync(exports);
  Magick::InitializeMagick(NULL);
  Image::Init(exports);
  Blob::Init(exports);
  Color::Init(exports);
  Geometry::Init(exports);
}

NODE_MODULE(node_graphicsmagick, init);

//todo: add doc for Blob
Persistent<FunctionTemplate> Blob::constructor_template;
Handle<Value> Blob::New(const Arguments& args) {
  HandleScope scope;
  Blob* that = new Blob();
  that->Wrap(args.This());

  if (args.Length() != 0 && !( args.Length() == 1 && args[0]->IsObject() && Buffer::HasInstance(args[0]->ToObject())))
    return ThrowException(v8::Exception::TypeError(String::New("Arguments are () or (Buffer)")));

  if (args.Length() == 1)
    that->set(new Magick::Blob(Buffer::Data(args[0]), Buffer::Length(args[0])));
  else
    that->set(new Magick::Blob());

  return args.This();
}

Persistent<FunctionTemplate> Color::constructor_template;
Handle<Value> Color::New(const Arguments& args) {
  HandleScope scope;
  Color* that = new Color();
  that->Wrap(args.This());
  if (args.Length() != 1 || !args[0]->IsObject() || args[0]->IsFunction())
    return ThrowException(v8::Exception::TypeError(String::New("Invalid ColorObject")));
  Local<Object> aObj = args[0]->ToObject();
  Local<String> aKey1, aKey2, aKey3, aKey4;
  Magick::Color* aColor = NULL;

  if (aObj->Has(aKey1 = String::New("red")) && aObj->Has(aKey2 = String::New("green")) && aObj->Has(aKey3 = String::New("blue"))) {
    if (!aObj->Get(aKey1)->IsNumber() || !aObj->Get(aKey2)->IsNumber() || !aObj->Get(aKey3)->IsNumber())
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject red, green and blue are number")));
    aColor = new Magick::ColorRGB(aObj->Get(aKey1)->ToNumber()->Value(), aObj->Get(aKey2)->ToNumber()->Value(), aObj->Get(aKey3)->ToNumber()->Value());
  } else if (aObj->Has(aKey1 = String::New("redQuantum")) && aObj->Has(aKey2 = String::New("greenQuantum")) && aObj->Has(aKey3 = String::New("blueQuantum"))) {
    if  ((!aObj->Get(aKey1)->IsUint32() || !aObj->Get(aKey2)->IsUint32() || !aObj->Get(aKey3)->IsUint32()) || (aObj->Has(aKey4 = String::New("alphaQuantum")) && !aObj->Get(aKey4)->IsUint32()))
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject redQuantum, greenQuantum, blueQuantum and alphaQuantum are uint32")));
    aColor = new Magick::Color(aObj->Get(aKey1)->ToUint32()->Value(), aObj->Get(aKey2)->ToUint32()->Value(), aObj->Get(aKey3)->ToUint32()->Value());
    if (aObj->Has(aKey4 = String::New("alphaQuantum")))
      aColor->alphaQuantum(aObj->Get(aKey4)->ToUint32()->Value());
  } else if (aObj->Has(aKey1 = String::New("shade"))) {
    if (!aObj->Get(aKey1)->IsNumber())
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject.shade is number")));
    aColor = new Magick::ColorGray(aObj->Get(aKey1)->ToNumber()->Value());
  } else if (aObj->Has(aKey1 = String::New("mono"))) {
    if (!aObj->Get(aKey1)->IsBoolean())
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject.mono is boolean")));
    aColor = new Magick::ColorMono(aObj->Get(aKey1)->ToBoolean()->Value());
  } else if (aObj->Has(aKey1 = String::New("hue")) && aObj->Has(aKey2 = String::New("saturation")) && aObj->Has(aKey3 = String::New("luminosity"))) {
    if (!aObj->Get(aKey1)->IsNumber() || !aObj->Get(aKey2)->IsNumber() || !aObj->Get(aKey3)->IsNumber())
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject hue, saturation and luminosity are number")));
    aColor = new Magick::ColorHSL(aObj->Get(aKey1)->ToNumber()->Value(), aObj->Get(aKey2)->ToNumber()->Value(), aObj->Get(aKey3)->ToNumber()->Value());
  } else if (aObj->Has(aKey1 = String::New("Y")) && aObj->Has(aKey2 = String::New("U")) && aObj->Has(aKey3 = String::New("V"))) {
    if (!aObj->Get(aKey1)->IsNumber() || !aObj->Get(aKey2)->IsNumber() || !aObj->Get(aKey3)->IsNumber())
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject Y, U and V are number")));
    aColor = new Magick::ColorYUV(aObj->Get(aKey1)->ToNumber()->Value(), aObj->Get(aKey2)->ToNumber()->Value(), aObj->Get(aKey3)->ToNumber()->Value());
  }

  if (aObj->Has(aKey1 = String::New("alpha"))) {
    if (!aObj->Get(aKey1)->IsNumber()) {
      delete aColor;
      return ThrowException(v8::Exception::TypeError(String::New("ColorObject.alpha is number")));
    } else
      aColor->alpha(aObj->Get(aKey1)->ToNumber()->Value());
  }

  that->set(aColor);
  return args.This();
}

Persistent<FunctionTemplate> Geometry::constructor_template;
Handle<Value> Geometry::New(const Arguments& args) {
  HandleScope scope;
  Geometry* that = new Geometry();
  that->Wrap(args.This());
  if (args.Length() != 1 || !args[0]->IsObject() || args[0]->IsFunction())
    return ThrowException(v8::Exception::TypeError(String::New("Invalid GeometryObject")));
  Local<Object> aObj = args[0]->ToObject();
  Local<String> aKey;
  if (!aObj->Has(aKey = String::New("width")) || !aObj->Get(aKey)->IsUint32())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.witdh is uint32")));
  if (!aObj->Has(aKey = String::New("height")) || !aObj->Get(aKey)->IsUint32())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.height is uint32")));
  if (aObj->Has(aKey = String::New("xOff")) && !aObj->Get(aKey)->IsUint32())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.xOff is uint32")));
  if (aObj->Has(aKey = String::New("yOff")) && !aObj->Get(aKey)->IsUint32())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.yOff is uint32")));
  if (aObj->Has(aKey = String::New("xNegative")) && !aObj->Get(aKey)->IsBoolean())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.xNegative is boolean")));
  if (aObj->Has(aKey = String::New("yNegative")) && !aObj->Get(aKey)->IsBoolean())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.yNegative is boolean")));
  if (aObj->Has(aKey = String::New("percent")) && !aObj->Get(aKey)->IsBoolean())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.percent is boolean")));
  if (aObj->Has(aKey = String::New("aspect")) && !aObj->Get(aKey)->IsBoolean())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.aspect is boolean")));
  if (aObj->Has(aKey = String::New("greater")) && !aObj->Get(aKey)->IsBoolean())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.greater is boolean")));
  if (aObj->Has(aKey = String::New("less")) && !aObj->Get(aKey)->IsBoolean())
    return ThrowException(v8::Exception::TypeError(String::New("GeometryObject.less is boolean")));

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

  that->set(aGeometry);
  return args.This();
}

bool checkArguments(int signature[], const Arguments& args, int optionals[]) {
  int aArgN = 0, aOptN = 0;

  for (int aSigN=0; signature[aSigN] != eEnd; ++aSigN) {
    int aIsType;
    switch (abs(signature[aSigN])) {
    case eInt32:          aIsType = args[aArgN]->IsInt32();                                                                          break;
    case eUint32:         aIsType = args[aArgN]->IsUint32();                                                                         break;
    case eBoolean:        aIsType = args[aArgN]->IsBoolean();                                                                        break;
    case eString:         aIsType = args[aArgN]->IsString();                                                                         break;
    case eArray:          aIsType = args[aArgN]->IsArray();                                                                          break;
    case eBuffer:
    case eObjectImage:
    case eObject:         aIsType = args[aArgN]->IsObject() && !args[aArgN]->IsFunction();                                           break;
    case eObjectBlob:     aIsType = args[aArgN]->IsObject() && Blob::constructor_template->HasInstance(args[aArgN]->ToObject());     break;
    case eObjectColor:    aIsType = args[aArgN]->IsObject() && Color::constructor_template->HasInstance(args[aArgN]->ToObject());    break;
    case eObjectGeometry: aIsType = args[aArgN]->IsObject() && Geometry::constructor_template->HasInstance(args[aArgN]->ToObject()); break;
    case eNull:           aIsType = args[aArgN]->IsNull();                                                                           break;
    case eFunction:       aIsType = args[aArgN]->IsFunction();                                                                       break;
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
    case eObjectBlob:     aStr += "Blob";     break;
    case eObjectColor:    aStr += "Color";    break;
    case eObjectGeometry: aStr += "Geometry"; break;
    case eObjectImage:    aStr += "Image";    break;
    case eNull:           aStr += "null";     break;
    case eFunction:       aStr += "function"; break;
    default:              assert(0); 
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
