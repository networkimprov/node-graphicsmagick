#include "node_graphicsmagick.h"
#include <node_buffer.h>

Persistent<FunctionTemplate> Image::constructor_template;

void Image::Init(Handle<Object> target) {
  constructor_template = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Image"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "adaptiveThreshold", AdaptiveThreshold);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "addNoiseChannel", AddNoiseChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "addNoise", AddNoise);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "annotate", Annotate);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "blur", Blur);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "blurChannel", BlurChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "border", Border);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "cdl", Cdl);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "channel", Channel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "channelDepth", ChannelDepth);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "charcoal", Charcoal);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "chop", Chop);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "colorize", Colorize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "comment", Comment);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "contrast", Contrast);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "crop", Crop);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "cycleColormap", CycleColormap);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "write", Write);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "writeFile", WriteFile);
  target->Set(String::NewSymbol("Image"), constructor_template->GetFunction());

  //todo: move to separate file, create doc
  Local<Object> aChannelType = Object::New();
  aChannelType->Set(String::NewSymbol("UndefinedChannel"), Integer::New(Magick::UndefinedChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("RedChannel"), Integer::New(Magick::RedChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("CyanChannel"), Integer::New(Magick::CyanChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("GreenChannel"), Integer::New(Magick::GreenChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("MagentaChannel"), Integer::New(Magick::MagentaChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("BlueChannel"), Integer::New(Magick::BlueChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("YellowChannel"), Integer::New(Magick::YellowChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("OpacityChannel"), Integer::New(Magick::OpacityChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("BlackChannel"), Integer::New(Magick::BlackChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("MatteChannel"), Integer::New(Magick::MatteChannel), ReadOnly);
  aChannelType->Set(String::NewSymbol("AllChannels"), Integer::New(Magick::AllChannels), ReadOnly);
  aChannelType->Set(String::NewSymbol("GrayChannel"), Integer::New(Magick::GrayChannel), ReadOnly);
  target->Set(String::NewSymbol("ChannelType"), aChannelType);

  Local<Object> aGravityType = Object::New();
  aGravityType->Set(String::NewSymbol("ForgetGravity"), Integer::New(Magick::ForgetGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("NorthWestGravity"), Integer::New(Magick::NorthWestGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("NorthGravity"), Integer::New(Magick::NorthGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("NorthEastGravity"), Integer::New(Magick::NorthEastGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("WestGravity"), Integer::New(Magick::WestGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("CenterGravity"), Integer::New(Magick::CenterGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("EastGravity"), Integer::New(Magick::EastGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("SouthWestGravity"), Integer::New(Magick::SouthWestGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("SouthGravity"), Integer::New(Magick::SouthGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("SouthEastGravity"), Integer::New(Magick::SouthEastGravity), ReadOnly);
  aGravityType->Set(String::NewSymbol("StaticGravity"), Integer::New(Magick::StaticGravity), ReadOnly);
  target->Set(String::NewSymbol("GravityType"), aGravityType);

  Local<Object> aNoiseType = Object::New();
  aNoiseType->Set(String::NewSymbol("UniformNoise"), Integer::New(Magick::UniformNoise), ReadOnly);
  aNoiseType->Set(String::NewSymbol("GaussianNoise"), Integer::New(Magick::GaussianNoise), ReadOnly);
  aNoiseType->Set(String::NewSymbol("MultiplicativeGaussianNoise"), Integer::New(Magick::MultiplicativeGaussianNoise), ReadOnly);
  aNoiseType->Set(String::NewSymbol("ImpulseNoise"), Integer::New(Magick::ImpulseNoise), ReadOnly);
  aNoiseType->Set(String::NewSymbol("LaplacianNoise"), Integer::New(Magick::LaplacianNoise), ReadOnly);
  aNoiseType->Set(String::NewSymbol("PoissonNoise"), Integer::New(Magick::PoissonNoise), ReadOnly);
  aNoiseType->Set(String::NewSymbol("RandomNoise"), Integer::New(Magick::RandomNoise), ReadOnly);
  target->Set(String::NewSymbol("NoiseType"), aNoiseType);

}

//Actions for Image::Generic_process. Each method will set the action and it will be processed accordingly.
enum {
  eNew1, eNew2, eNew3, eNew4, eNew5, eNew6, eNew7, eNew8,
  eAdaptiveThreshold,
  eAddNoiseChannel,
  eAddNoise,
  eAnnotate1, eAnnotate2, eAnnotate3, eAnnotate4,
  eBlur,
  eBlurChannel,
  eBorder,
  eCdl,
  eChannel,
  eChannelDepth1, eChannelDepth2,
  eCharcoal,
  eChop,
  eColorize1, eColorize2,
  eComment,
  eContrast,
  eCrop,
  eCycleColormap,
  eWrite1, eWrite2, eWrite3,
  eWriteFile,
};

static int kNew1[] = { eEnd };
static int kNew2[] = { eObjectGeometry, eObjectColor, -eFunction, eEnd };
static int kNew3[] = { eString, -eFunction, eEnd };
static int kNew4[] = { eObjectBlob, -eFunction, eEnd };
static int kNew5[] = { eObjectBlob, eObjectGeometry, -eFunction, eEnd };
static int kNew6[] = { eObjectBlob, eObjectGeometry, eUint32, -eFunction, eEnd };
static int kNew7[] = { eObjectBlob, eObjectGeometry, eUint32, eString, -eFunction, eEnd };
static int kNew8[] = { eObjectBlob, eObjectGeometry, eString, -eFunction, eEnd };
static SetType kNewSetType[] = { { kNew1, eNew1}, { kNew2, eNew2}, { kNew3, eNew3}, { kNew4, eNew4}, { kNew5, eNew5}, { kNew6, eNew6}, { kNew7, eNew7}, { kNew8, eNew8}, { NULL, 0 } };
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

static int kAdaptiveThreshold[] = { eUint32, eUint32, -eUint32, -eFunction, eEnd };
Handle<Value> Image::AdaptiveThreshold(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetUint32(0);
  return generic_check_start<Image>(eAdaptiveThreshold, args, kAdaptiveThreshold, aDefaults);
}

static int kAddNoiseChannel[] = { eInt32, eInt32, -eFunction, eEnd };
Handle<Value> Image::AddNoiseChannel(const Arguments& args) {
  return generic_check_start<Image>(eAddNoiseChannel, args, kAddNoiseChannel);
}

static int kAddNoise[] = { eInt32, -eFunction, eEnd };
Handle<Value> Image::AddNoise(const Arguments& args) {
  return generic_check_start<Image>(eAddNoise, args, kAddNoise);
}

static int kAnnotate1[] = { eString, eObjectGeometry, -eFunction, eEnd };
static int kAnnotate2[] = { eString, eObjectGeometry, eInt32, -eFunction, eEnd };
static int kAnnotate3[] = { eString, eObjectGeometry, eInt32, eNumber, -eFunction, eEnd };
static int kAnnotate4[] = { eString, eInt32, -eFunction, eEnd };
static SetType kAnnotateSetType[] = { { kAnnotate1, eAnnotate1 }, { kAnnotate2, eAnnotate2 }, { kAnnotate3, eAnnotate3 }, { kAnnotate4, eAnnotate4 }, { NULL, 0 } };
Handle<Value> Image::Annotate(const Arguments& args) {
  return generic_check_start<Image>(args, kAnnotateSetType);
}

static int kBlur[] = { -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Blur(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(0);
  aDefaults[1].SetNumber(1);
  return generic_check_start<Image>(eBlur, args, kBlur, aDefaults);
}

static int kBlurChannel[] = { eInt32, -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::BlurChannel(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(0);
  aDefaults[1].SetNumber(1);
  return generic_check_start<Image>(eBlurChannel, args, kBlurChannel, aDefaults);
}

static int kBorder[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Border(const Arguments& args) {
  return generic_check_start<Image>(eBorder, args, kBorder);
}

static int kCdl[] = { eString, -eFunction, eEnd };
Handle<Value> Image::Cdl(const Arguments& args) {
  //todo: write test
  return generic_check_start<Image>(eCdl, args, kCdl);
}

static int kChannel[] = { eInt32, -eFunction, eEnd };
Handle<Value> Image::Channel(const Arguments& args) {
  return generic_check_start<Image>(eChannel, args, kChannel);
}

static int kChannelDepth1[] = { eInt32, eUint32, -eFunction, eEnd };
static int kChannelDepth2[] = { eInt32, -eFunction, eEnd };
static SetType kChannelDepthSetType[] = { { kChannelDepth1, eChannelDepth1}, { kChannelDepth2, eChannelDepth2}, { NULL, 0 } };
Handle<Value> Image::ChannelDepth(const Arguments& args) {
  return generic_check_start<Image>(args, kChannelDepthSetType);
}

static int kCharcoal[] = { -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Charcoal(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(0);
  aDefaults[1].SetNumber(1);
  return generic_check_start<Image>(eCharcoal, args, kCharcoal, aDefaults);
}

static int kChop[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Chop(const Arguments& args) {
  return generic_check_start<Image>(eChop, args, kChop);
}

static int kColorize1[] = { eUint32, eUint32, eUint32, eObjectColor, -eFunction, eEnd };
static int kColorize2[] = { eUint32, eObjectColor, -eFunction, eEnd };
static SetType kColorizeSetType[] = { { kColorize1, eColorize1}, { kColorize2, eColorize2}, { NULL, 0 } };
Handle<Value> Image::Colorize(const Arguments& args) {
  return generic_check_start<Image>(args, kColorizeSetType);
}

static int kComment[] = { eString, -eFunction, eEnd };
Handle<Value> Image::Comment(const Arguments& args) {
  return generic_check_start<Image>(eComment, args, kComment);
}

static int kContrast[] = { eUint32, -eFunction, eEnd };
Handle<Value> Image::Contrast(const Arguments& args) {
  return generic_check_start<Image>(eContrast, args, kContrast);
}

static int kCrop[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Crop(const Arguments& args) {
  return generic_check_start<Image>(eCrop, args, kCrop);
}

static int kCycleColormap[] = { eUint32, -eFunction, eEnd };
Handle<Value> Image::CycleColormap(const Arguments& args) {
  return generic_check_start<Image>(eCycleColormap, args, kCycleColormap);
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
  data->retVal.pointer = that;
  switch (data->action) {
  case eNew2:              that->setImage(new Magick::Image(((Geometry*) data->val[0].pointer)->get(), ((Color*) data->val[1].pointer)->get()));                                           break;
  case eNew3:              that->setImage(new Magick::Image(*data->val[0].string));                                                                                                        break;
  case eNew4:              that->setImage(new Magick::Image(((Blob*) data->val[0].pointer)->get()));                                                                                       break;
  case eNew5:              that->setImage(new Magick::Image(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get()));                                            break;
  case eNew6:              that->setImage(new Magick::Image(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get(), data->val[2].uint32));                       break;
  case eNew7:              that->setImage(new Magick::Image(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get(), data->val[2].uint32, *data->val[3].string)); break;
  case eNew8:              that->setImage(new Magick::Image(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get(), *data->val[2].string));                      break;
  case eAdaptiveThreshold: that->getImage().adaptiveThreshold(data->val[0].uint32, data->val[1].uint32, data->val[2].uint32);                                                              break;
  case eAddNoiseChannel:   that->getImage().addNoiseChannel((Magick::ChannelType) data->val[0].int32, (Magick::NoiseType) data->val[1].int32);                                             break;
  case eAddNoise:          that->getImage().addNoise((Magick::NoiseType) data->val[0].int32);                                                                                              break;
  case eAnnotate1:         that->getImage().annotate(*data->val[0].string, ((Geometry*) data->val[1].pointer)->get());                                                                     break;
  case eAnnotate2:         that->getImage().annotate(*data->val[0].string, ((Geometry*) data->val[1].pointer)->get(), (Magick::GravityType) data->val[2].int32);                           break;
  case eAnnotate3:         that->getImage().annotate(*data->val[0].string, ((Geometry*) data->val[1].pointer)->get(), (Magick::GravityType) data->val[2].int32, data->val[3].dbl);         break;
  case eAnnotate4:         that->getImage().annotate(*data->val[0].string, (Magick::GravityType) data->val[1].int32);                                                                      break;
  case eBlur:              that->getImage().blur(data->val[0].dbl, data->val[1].dbl);                                                                                                      break;
  case eBlurChannel:       that->getImage().blurChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl);                                                     break;
  case eBorder:            that->getImage().border(((Geometry*) data->val[0].pointer)->get());                                                                                             break;
  case eCdl:               that->getImage().cdl(*data->val[0].string);                                                                                                                     break;
  case eChannel:           that->getImage().channel((Magick::ChannelType) data->val[0].int32);                                                                                             break;
  case eChannelDepth1:     that->getImage().channelDepth((Magick::ChannelType) data->val[0].int32, data->val[1].uint32);                                                                   break;
  case eChannelDepth2:     data->retVal.uint32 = that->getImage().channelDepth((Magick::ChannelType) data->val[0].int32);                                                                  break;
  case eCharcoal:          that->getImage().charcoal(data->val[0].dbl, data->val[1].dbl);                                                                                                  break;
  case eChop:              that->getImage().chop(((Geometry*) data->val[0].pointer)->get());                                                                                               break;
  case eColorize1:         that->getImage().colorize(data->val[0].uint32, data->val[1].uint32, data->val[2].uint32, ((Color*) data->val[3].pointer)->get());                               break;
  case eColorize2:         that->getImage().colorize(data->val[0].uint32, ((Color*) data->val[1].pointer)->get());                                                                         break;
  case eComment:           that->getImage().comment(*data->val[0].string);                                                                                                                 break;
  case eContrast:          that->getImage().contrast(data->val[0].uint32);                                                                                                                 break;
  case eCrop:              that->getImage().crop(((Geometry*) data->val[0].pointer)->get());                                                                                               break;
  case eCycleColormap:     that->getImage().cycleColormap(data->val[0].uint32);                                                                                                            break;
  case eWriteFile:         that->getImage().write(*data->val[0].string);                                                                                                                   break;
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
  case eNew4:
  case eNew5:
  case eNew6:
  case eNew7:
  case eNew8:
  case eAdaptiveThreshold:
  case eAddNoiseChannel:
  case eAddNoise:
  case eAnnotate1:
  case eAnnotate2:
  case eAnnotate3:
  case eAnnotate4:
  case eBlur:
  case eBlurChannel:
  case eBorder:
  case eCdl:
  case eChannel:
  case eChannelDepth1:
  case eWriteFile:
    aResult = ((Image*) data->retVal.pointer)->handle_;
    break;
  case eWrite1:
  case eWrite2:
  case eWrite3: {
    Magick::Blob* aBlob = (Magick::Blob*) data->retVal.pointer;
    aResult = Blob::constructor_template->GetFunction()->NewInstance();
    GetInstance<Blob>(aResult)->set(aBlob);
  } break;
  case eChannelDepth2:
    aResult = Uint32::New(data->retVal.uint32);
    break;
  }
  delete data;
  return aResult;
}

