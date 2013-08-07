#include "node_graphicsmagick.h"
#include <node_buffer.h>

Persistent<FunctionTemplate> Image::constructor_template;

void Image::Init(Handle<Object> target) {
  constructor_template = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Image"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "write", Write);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "writeFile", WriteFile);
  target->Set(String::NewSymbol("Image"), constructor_template->GetFunction());
}

//fix: comment describing these symbols
enum {
  eNew2, eNew3,//fix: new1 ?
  eWrite1, eWrite2, eWrite3,
  eWriteFile
};


static int kNew1[] = { eEnd };
static int kNew2[] = { eObjectGeometry, eObjectColor, eEnd };
static int kNew3[] = { eString, -eFunction, eEnd };
static int* kNewSet[] = { kNew1, kNew3 }; //fix: not used?; omits new2
Handle<Value> Image::New(const Arguments& args) {
  HandleScope scope;
  int aOpt[1];
  Image* that = new Image();
  that->Wrap(args.This());
  try {
    if (checkArguments(kNew1, args, aOpt)) //fix: see fix comment in generic_start; should write this as a loop
      that->setImage(new Magick::Image());
    else if (checkArguments(kNew2, args, aOpt))
      generic_start<Image>(eNew2, args, kNew2, false, aOpt);
    else if (checkArguments(kNew3, args, aOpt))
      generic_start<Image>(eNew3, args, kNew3, false, aOpt);
    //fix: else what about signature error? default ctor? if so, no need to checkArguments(kNew1...)
  } catch (std::exception& err) { //fix: if only for setImage, try/catch just that
    return ThrowException(Exception::Error(String::New(err.what())));
  }
  return args.This();
}

static int kWriteFile[] = { eString, -eFunction, eEnd };
Handle<Value> Image::WriteFile(const Arguments& args) {
  return generic_start<Image>(eWriteFile, args, kWriteFile);
}

static int kWrite1[] = { eString, -eFunction, eEnd };
static int kWrite2[] = { -eFunction, eEnd };
static int kWrite3[] = { eString, eUint32, -eFunction, eEnd };
static int* kWriteSet[] = { kWrite1, kWrite2, kWrite3 };
Handle<Value> Image::Write(const Arguments& args) {
  HandleScope scope;
  int aOpt[1];
  if (checkArguments(kWrite1, args, aOpt)) //fix: loop?
    return generic_start<Image>(eWrite1, args, kWrite1, false, aOpt);
  else if (checkArguments(kWrite2, args, aOpt))
    return generic_start<Image>(eWrite2, args, kWrite2, false, aOpt);
  else if (checkArguments(kWrite3, args, aOpt))
    return generic_start<Image>(eWrite3, args, kWrite3, false, aOpt);
  else
    return throwSignatureErr(kWriteSet, 3);
}

void Image::Generic_process(void* pData, void* pThat) {
  GenericData* data = (GenericData*) pData;
  Image* that = (Image *) pThat;
  switch (data->action) {
  case eNew2:
    that->setImage(new Magick::Image(*((Magick::Geometry*) data->val[0].pointer), *((Magick::Color*) data->val[1].pointer)));
    data->retVal.pointer = that;
    break;
  case eNew3:
    that->setImage(new Magick::Image(*data->val[0].string));
    data->retVal.pointer = that;
    break;
  case eWriteFile:
    that->getImage().write(*data->val[0].string);
    data->retVal.pointer = that;
    break;
  case eWrite1:
  case eWrite2:
  case eWrite3: {
    Magick::Blob* aBlob = new Magick::Blob();
    switch (data->action) {
    case eWrite1: that->getImage().write(aBlob, *data->val[0].string);                              break;
    case eWrite2: that->getImage().write(aBlob);                                                    break;
    case eWrite3: that->getImage().write(aBlob, *data->val[0].string, data->val[1].uint32);         break;
    }
    //TODO delete aBlob on exception
    data->retVal.pointer = aBlob;
  } break;
  default:
    assert(0);
  }
}

Handle<Value> Image::Generic_convert(void* pData) {
  GenericData* data = (GenericData*) pData;
  Handle<Value> aResult = Undefined();
  switch (data->action) {
  case eNew3: 
  case eWriteFile:
    aResult = ((Image*) data->retVal.pointer)->handle_;
    break;
  case eWrite1:
  case eWrite2:
  case eWrite3: {
    Magick::Blob* aBlob = (Magick::Blob*) data->retVal.pointer;
    aResult = Buffer::New((const char*) aBlob->data(), aBlob->length())->handle_;
  } break;
  }
  delete data;
  return aResult;
}

