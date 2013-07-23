#include "node_graphicsmagick.h"

using namespace v8;
using namespace node;

using namespace std;

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
    case eNull:           aIsType = args[aArgN]->IsNull();                                   break;
    case eFunction:       aIsType = args[aArgN]->IsFunction();                               break;
    default: { std::string aEx("incorrect signature member: "); aEx += (char)(signature[aSigN] + '0'); throw aEx; }
    }

    if (signature[aSigN] < 0) {
      optionals[aOptN] = aIsType ? aArgN++ : -1;
      ++aOptN;
    } else {
      if (!aIsType) return false;
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
    case eObjectImage:    aStr += "Image";    break;
    case eNull:           aStr += "null";     break;
    case eFunction:       aStr += "function"; break;
    default:         throw "incorrect sig member"; 
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

Handle<Value> throwSignatureErr(int *signatures[], int sigN) {
  std::string aStr("arguments are ");
  for (int a = 0; a < sigN; a++) {
    if (a > 0)
      aStr += " or ";
    aStr += generateSignatureString(signatures[a]);
  }
  return ThrowException(v8::Exception::TypeError(String::New(aStr.c_str())));
}

void init(Handle<Object> exports) {
  initAsync(exports);
  Magick::InitializeMagick(NULL);
  Image::Init(exports);
}

NODE_MODULE(node_graphicsmagick, init);
