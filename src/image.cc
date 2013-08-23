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

//Actions for Image::Generic_process. Each method will set the action and it will be processed accordingly.
enum {
  eNew1, eNew2, eNew3,
  eWrite1, eWrite2, eWrite3,
  eWriteFile,
};

static int kNew1[] = { eEnd };
static int kNew2[] = { eObjectGeometry, eObjectColor, -eFunction, eEnd };
static int kNew3[] = { eString, -eFunction, eEnd };
static SetType kNewSetType[] = { { kNew1, eNew1}, { kNew2, eNew2}, { kNew3, eNew3}, { NULL, 0 } };
Handle<Value> Image::New(const Arguments& args) {
  HandleScope scope;
  Image* that = new Image();
  that->Wrap(args.This());
  int aOpt[1];
  if (checkArguments(kNew1, args, aOpt)) {
    try {
      that->setImage(new Magick::Image());
    } catch (std::exception& err) {
      return ThrowException(Exception::Error(String::New(err.what())));
    }
    return args.This();
  }
  return generic_check_start<Image>(args, kNewSetType, NULL, 1);
}

static int kWriteFile[] = { eString, -eFunction, eEnd };
Handle<Value> Image::WriteFile(const Arguments& args) {
  return generic_check_start<Image>(eWriteFile, args, kWriteFile);
}

static int kWrite1[] = { eString, -eFunction, eEnd };
static int kWrite2[] = { -eFunction, eEnd };
static int kWrite3[] = { eString, eUint32, -eFunction, eEnd };
static SetType kWriteSetType[] = { { kWrite1, eWrite1}, { kWrite2, eWrite2}, { kWrite3, eWrite3}, { NULL, 0 } };
Handle<Value> Image::Write(const Arguments& args) {
  return generic_check_start<Image>(args, kWriteSetType);
}

void Image::Generic_process(void* pData, void* pThat) {
  GenericFunctionCall* data = (GenericFunctionCall*) pData;
  Image* that = (Image *) pThat;
  switch (data->action) {
  case eNew2:
    that->setImage(new Magick::Image(((Geometry*) data->val[0].pointer)->get(), *((Magick::Color*) data->val[1].pointer)));
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
  GenericFunctionCall* data = (GenericFunctionCall*) pData;
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

