#ifndef _NODE_GRAPHICSMAGICK_H_
#define _NODE_GRAPHICSMAGICK_H_

#include <Magick++.h>

#include "async.h"

enum ArgumentType {
  eEnd,
  eInt32,
  eUint32,
  eBoolean,
  eString,
  eObject,
  eArray,
  eBuffer,
  eObjectImage,
  eNull,
  eFunction
};

bool checkArguments(int signature[], const Arguments& args, int optionals[]);
Handle<Value> throwSignatureErr(int signature[]);
Handle<Value> throwSignatureErr(int *signatures[], int sigN);

class Image : public AsyncWrap<Image> {
public:
  static void Init(Handle<Object> target);

  static Persistent<FunctionTemplate> constructor_template;

  Magick::Image mImage;

  static void Generic_process(void* data, void* that);
  static Handle<Value> Generic_convert(void* data);

protected:
  Image() : mImage() { }
  ~Image() { }

  static Handle<Value> New(const Arguments& args);
};

#endif
