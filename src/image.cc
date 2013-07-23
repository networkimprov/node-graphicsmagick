#include "node_graphicsmagick.h"

Persistent<FunctionTemplate> Image::constructor_template;

void Image::Init(Handle<Object> target) {
  constructor_template = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Image"));

  target->Set(String::NewSymbol("Image"), constructor_template->GetFunction());
}

static int kNewImage[] = { eEnd };
Handle<Value> Image::New(const Arguments& args) {
  HandleScope scope;
  int aOpt[0];
  if (!checkArguments(kNewImage, args, aOpt))
    return throwSignatureErr(kNewImage);

  Image* that;
  try {
    that = new Image();
  } catch (std::exception& err) {
    return ThrowException(v8::Exception::Error(String::New(err.what())));
  }
  that->Wrap(args.This());
  return args.This();
}
