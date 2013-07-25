#include "node_graphicsmagick.h"

Persistent<FunctionTemplate> Image::constructor_template;

void Image::Init(Handle<Object> target) {
  constructor_template = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Image"));

  target->Set(String::NewSymbol("Image"), constructor_template->GetFunction());
}

enum {
  eNew3
};


static int kNew1[] = { eEnd };
static int kNew3[] = { eString, -eFunction, eEnd };
static int* kNewSet[] = { kNew1, kNew3 };
Handle<Value> Image::New(const Arguments& args) {
  HandleScope scope;
  int aOpt[1];
  int aSignUsed = -1;
  if (checkArguments(kNew1, args, aOpt))
    aSignUsed = 1;
  else if (checkArguments(kNew3, args, aOpt))
    aSignUsed = 3;
  else
    return throwSignatureErr(kNewSet, 2);

  Image* that = new Image();
  that->Wrap(args.This());
  try {
    switch (aSignUsed) {
    case 1: that->setImage(new Magick::Image()); break;
    case 3: generic_start<Image>(eNew3, args, kNew3); break;
    }
  } catch (std::exception& err) {
    return ThrowException(v8::Exception::Error(String::New(err.what())));
  }
  return args.This();
}

void Image::Generic_process(void* pData, void* pThat) {
  GenericData* data = (GenericData*) pData;
  Image* that = (Image *) pThat;
  switch (data->action) {
  case eNew3: that->setImage(new Magick::Image(*data->val[0].string)); data->retVal.pointer = that; break;
  default: assert(0);
  }
}

Handle<Value> Image::Generic_convert(void* pData) {
  GenericData* data = (GenericData*) pData;
  Handle<Value> aResult = Undefined();
  switch (data->action) {
  case eNew3: aResult = ((Image*) data->retVal.pointer)->handle_; break;
  }
  delete data;
  return aResult;
}

