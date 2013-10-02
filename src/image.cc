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
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "despeckle", Despeckle);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "edge", Edge);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "emboss", Emboss);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "enhance", Enhance);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "equalize", Equalize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "erase", Erase);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "flip", Flip);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "floodFillColor", FloodFillColor);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "floodFillOpacity", FloodFillOpacity);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "flop", Flop);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "gamma", Gamma);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "gaussianBlur", GaussianBlur);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "gaussianBlurChannel", GaussianBlurChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "implode", Implode);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "level", Level);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "levelChannel", LevelChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "magnify", Magnify);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "matteFloodfill", MatteFloodfill);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "medianFilter", MedianFilter);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "minify", Minify);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "modulate", Modulate);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "motionBlur", MotionBlur);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "negate", Negate);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "normalize", Normalize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "oilPaint", OilPaint);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "opacity", Opacity);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "opaque", Opaque);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "quantize", Quantize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "raise", Raise);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "randomThreshold", RandomThreshold);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "randomThresholdChannel", RandomThresholdChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "reduceNoise", ReduceNoise);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "roll", Roll);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "rotate", Rotate);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "sample", Sample);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "scale", Scale);
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

  Local<Object> aPaintMethod = Object::New();
  aPaintMethod->Set(String::NewSymbol("PointMethod"), Integer::New(Magick::PointMethod), ReadOnly);
  aPaintMethod->Set(String::NewSymbol("ReplaceMethod"), Integer::New(Magick::ReplaceMethod), ReadOnly);
  aPaintMethod->Set(String::NewSymbol("FloodfillMethod"), Integer::New(Magick::FloodfillMethod), ReadOnly);
  aPaintMethod->Set(String::NewSymbol("FillToBorderMethod"), Integer::New(Magick::FillToBorderMethod), ReadOnly);
  aPaintMethod->Set(String::NewSymbol("ResetMethod"), Integer::New(Magick::ResetMethod), ReadOnly);
  target->Set(String::NewSymbol("PaintMethod"), aPaintMethod);

  target->Set(String::NewSymbol("OpaqueOpacity"), Integer::New(OpaqueOpacity), ReadOnly);
  target->Set(String::NewSymbol("TransparentOpacity"), Integer::New(TransparentOpacity), ReadOnly);

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
  eDespeckle,
  eEdge,
  eEmboss,
  eEnhance,
  eEqualize,
  eErase,
  eFlip,
  eFloodFillColor1, eFloodFillColor2, eFloodFillColor3, eFloodFillColor4,
  eFloodFillOpacity,
  eFlop,
  eGamma1, eGamma2,
  eGaussianBlur,
  eGaussianBlurChannel,
  eImplode,
  eLevel,
  eLevelChannel,
  eMagnify,
  eMatteFloodfill,
  eMedianFilter,
  eMinify,
  eModulate,
  eMotionBlur,
  eNegate,
  eNormalize,
  eOilPaint,
  eOpacity,
  eOpaque,
  eQuantize,
  eRaise,
  eRandomThreshold,
  eRandomThresholdChannel,
  eReduceNoise1, eReduceNoise2,
  eRoll1, eRoll2,
  eRotate,
  eSample,
  eScale,
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

static int kDespeckle[] = { -eFunction, eEnd };
Handle<Value> Image::Despeckle(const Arguments& args) {
  return generic_check_start<Image>(eDespeckle, args, kDespeckle);
}

static int kEdge[] = { -eNumber, -eFunction, eEnd };
Handle<Value> Image::Edge(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetNumber(0);
  return generic_check_start<Image>(eEdge, args, kEdge, aDefaults);
}

static int kEmboss[] = { -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Emboss(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(0);
  aDefaults[1].SetNumber(1);
  return generic_check_start<Image>(eEmboss, args, kEmboss, aDefaults);
}

static int kEnhance[] = { -eFunction, eEnd };
Handle<Value> Image::Enhance(const Arguments& args) {
  return generic_check_start<Image>(eEnhance, args, kEnhance);
}

static int kEqualize[] = { -eFunction, eEnd };
Handle<Value> Image::Equalize(const Arguments& args) {
  return generic_check_start<Image>(eEqualize, args, kEqualize);
}

static int kErase[] = { -eFunction, eEnd };
Handle<Value> Image::Erase(const Arguments& args) {
  return generic_check_start<Image>(eErase, args, kErase);
}

static int kFlip[] = { -eFunction, eEnd };
Handle<Value> Image::Flip(const Arguments& args) {
  return generic_check_start<Image>(eFlip, args, kFlip);
}

static int kFloodFillColor1[] = { eUint32, eUint32, eObjectColor, -eFunction, eEnd };
static int kFloodFillColor2[] = { eObjectGeometry, eObjectColor, -eFunction, eEnd };
static int kFloodFillColor3[] = { eUint32, eUint32, eObjectColor, eObjectColor, -eFunction, eEnd };
static int kFloodFillColor4[] = { eObjectGeometry, eObjectColor, eObjectColor, -eFunction, eEnd };
static SetType kFloodFillColorSetType[] = { { kFloodFillColor1, eFloodFillColor1}, { kFloodFillColor2, eFloodFillColor2}, { kFloodFillColor3, eFloodFillColor3}, { kFloodFillColor4, eFloodFillColor4}, { NULL, 0 } };
Handle<Value> Image::FloodFillColor(const Arguments& args) {
  return generic_check_start<Image>(args, kFloodFillColorSetType);
}

static int kFloodFillOpacity[] = { eUint32, eUint32, eUint32, eInt32, -eFunction, eEnd };
Handle<Value> Image::FloodFillOpacity(const Arguments& args) {
  return generic_check_start<Image>(eFloodFillOpacity, args, kFloodFillOpacity);
}

static int kFlop[] = { -eFunction, eEnd };
Handle<Value> Image::Flop(const Arguments& args) {
  return generic_check_start<Image>(eFlop, args, kFlop);
}

static int kGamma1[] = { eNumber, -eFunction, eEnd };
static int kGamma2[] = { eNumber, eNumber, eNumber, -eFunction, eEnd };
static SetType kGammaSetType[] = { { kGamma1, eGamma1 }, { kGamma2, eGamma2 }, { NULL, 0 } };
Handle<Value> Image::Gamma(const Arguments& args) {
  return generic_check_start<Image>(args, kGammaSetType);
}

static int kGaussianBlur[] = { eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::GaussianBlur(const Arguments& args) {
  return generic_check_start<Image>(eGaussianBlur, args, kGaussianBlur);
}

static int kGaussianBlurChannel[] = { eInt32, eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::GaussianBlurChannel(const Arguments& args) {
  return generic_check_start<Image>(eGaussianBlurChannel, args, kGaussianBlurChannel);
}

static int kImplode[] = { eNumber, -eFunction, eEnd };
Handle<Value> Image::Implode(const Arguments& args) {
  return generic_check_start<Image>(eImplode, args, kImplode);
}

static int kLevel[] = { eNumber, eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Level(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetNumber(1);
  return generic_check_start<Image>(eLevel, args, kLevel, aDefaults);
}

static int kLevelChannel[] = { eInt32, eNumber, eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::LevelChannel(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetNumber(1);
  return generic_check_start<Image>(eLevelChannel, args, kLevelChannel, aDefaults);
}

static int kMagnify[] = { -eFunction, eEnd };
Handle<Value> Image::Magnify(const Arguments& args) {
  return generic_check_start<Image>(eMagnify, args, kMagnify);
}

static int kMatteFloodfill[] = { eObjectColor, eUint32, eInt32, eInt32, eInt32, -eFunction, eEnd };
Handle<Value> Image::MatteFloodfill(const Arguments& args) {
  return generic_check_start<Image>(eMatteFloodfill, args, kMatteFloodfill);
}

static int kMedianFilter[] = { -eNumber, -eFunction, eEnd };
Handle<Value> Image::MedianFilter(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetNumber(0);
  return generic_check_start<Image>(eMedianFilter, args, kMedianFilter, aDefaults);
}

static int kMinify[] = { -eFunction, eEnd };
Handle<Value> Image::Minify(const Arguments& args) {
  return generic_check_start<Image>(eMinify, args, kMinify);
}

static int kModulate[] = { eNumber, eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::Modulate(const Arguments& args) {
  return generic_check_start<Image>(eModulate, args, kModulate);
}

static int kMotionBlur[] = { eNumber, eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::MotionBlur(const Arguments& args) {
  return generic_check_start<Image>(eMotionBlur, args, kMotionBlur);
}

static int kNegate[] = { -eBoolean, -eFunction, eEnd };
Handle<Value> Image::Negate(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetBool(false);
  return generic_check_start<Image>(eNegate, args, kNegate, aDefaults);
}

static int kNormalize[] = { -eFunction, eEnd };
Handle<Value> Image::Normalize(const Arguments& args) {
  return generic_check_start<Image>(eNormalize, args, kNormalize);
}

static int kOilPaint[] = { -eNumber, -eFunction, eEnd };
Handle<Value> Image::OilPaint(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetNumber(3);
  return generic_check_start<Image>(eOilPaint, args, kOilPaint, aDefaults);
}

static int kOpacity[] = { eUint32, -eFunction, eEnd };
Handle<Value> Image::Opacity(const Arguments& args) {
  return generic_check_start<Image>(eOpacity, args, kOpacity);
}

static int kOpaque[] = { eObjectColor, eObjectColor, -eFunction, eEnd };
Handle<Value> Image::Opaque(const Arguments& args) {
  return generic_check_start<Image>(eOpaque, args, kOpaque);
}

static int kQuantize[] = { -eBoolean, -eFunction, eEnd };
Handle<Value> Image::Quantize(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetBool(false);
  return generic_check_start<Image>(eQuantize, args, kQuantize, aDefaults);
}

static int kRaise[] = { -eObjectGeometry, -eBoolean, -eFunction, eEnd };
Handle<Value> Image::Raise(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetPointer(NULL, eObjectGeometry);
  aDefaults[1].SetBool(false);
  return generic_check_start<Image>(eRaise, args, kRaise, aDefaults);
}

static int kRandomThreshold[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::RandomThreshold(const Arguments& args) {
  return generic_check_start<Image>(eRandomThreshold, args, kRandomThreshold);
}

static int kRandomThresholdChannel[] = { eObjectGeometry, eInt32, -eFunction, eEnd };
Handle<Value> Image::RandomThresholdChannel(const Arguments& args) {
  return generic_check_start<Image>(eRandomThresholdChannel, args, kRandomThresholdChannel);
}

static int kReduceNoise1[] = { -eFunction, eEnd };
static int kReduceNoise2[] = { eNumber, -eFunction, eEnd };
static SetType kReduceNoiseSetType[] = { { kReduceNoise1, eReduceNoise1 },  { kReduceNoise2, eReduceNoise2 }, { NULL, 0 } };
Handle<Value> Image::ReduceNoise(const Arguments& args) {
  return generic_check_start<Image>(args, kReduceNoiseSetType);
}

static int kRoll1[] = { eObjectGeometry, -eFunction, eEnd };
static int kRoll2[] = { eUint32, eUint32, -eFunction, eEnd };
static SetType kRollSetType[] = { { kRoll1, eRoll1 }, { kRoll2, eRoll2 }, { NULL, 0 } };
Handle<Value> Image::Roll(const Arguments& args) {
  return generic_check_start<Image>(args, kRollSetType);
}

static int kRotate[] = { eNumber, -eFunction, eEnd };
Handle<Value> Image::Rotate(const Arguments& args) {
  return generic_check_start<Image>(eRotate, args, kRotate);
}

static int kSample[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Sample(const Arguments& args) {
  return generic_check_start<Image>(eSample, args, kSample);
}

static int kScale[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Scale(const Arguments& args) {
  return generic_check_start<Image>(eScale, args, kScale);
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
  case eDespeckle:         that->getImage().despeckle();                                                                                                                                   break;
  case eEdge:              that->getImage().edge(data->val[0].dbl);                                                                                                                        break;
  case eEmboss:            that->getImage().emboss(data->val[0].dbl, data->val[1].dbl);                                                                                                    break;
  case eEnhance:           that->getImage().enhance();                                                                                                                                     break;
  case eEqualize:          that->getImage().equalize();                                                                                                                                    break;
  case eErase:             that->getImage().erase();                                                                                                                                       break;
  case eFlip:              that->getImage().flip();                                                                                                                                        break;
  case eFloodFillColor1:   that->getImage().floodFillColor(data->val[0].uint32, data->val[1].uint32, ((Color*) data->val[2].pointer)->get());                                              break;
  case eFloodFillColor2:   that->getImage().floodFillColor(((Geometry*) data->val[0].pointer)->get(), ((Color*) data->val[1].pointer)->get());                                             break;
  case eFloodFillColor3:   that->getImage().floodFillColor(data->val[0].uint32, data->val[1].uint32, ((Color*) data->val[2].pointer)->get(), ((Color*) data->val[3].pointer)->get());      break;
  case eFloodFillColor4:   that->getImage().floodFillColor(((Geometry*) data->val[0].pointer)->get(), ((Color*) data->val[1].pointer)->get(), ((Color*) data->val[2].pointer)->get());     break;
  case eFloodFillOpacity:  that->getImage().floodFillOpacity(data->val[0].uint32, data->val[1].uint32, data->val[2].uint32, (Magick::PaintMethod) data->val[3].int32);                     break;
  case eFlop:              that->getImage().flop();                                                                                                                                        break;
  case eGamma1:            that->getImage().gamma(data->val[0].dbl);                                                                                                                       break;
  case eGamma2:            that->getImage().gamma(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl);                                                                                   break;
  case eGaussianBlur:      that->getImage().gaussianBlur(data->val[0].dbl, data->val[1].dbl);                                                                                              break;
  case eGaussianBlurChannel: that->getImage().gaussianBlurChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl);                                           break;
  case eImplode:           that->getImage().implode(data->val[0].dbl);                                                                                                                     break;
  case eLevel:             that->getImage().level(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl);                                                                                   break;
  case eLevelChannel:      that->getImage().levelChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl, data->val[3].dbl);                                  break;
  case eMagnify:           that->getImage().magnify();                                                                                                                                     break;
  case eMatteFloodfill:    that->getImage().matteFloodfill(((Color*) data->val[0].pointer)->get(), data->val[1].uint32, data->val[2].int32, data->val[3].int32, (Magick::PaintMethod) data->val[4].int32); break;
  case eMedianFilter:      that->getImage().medianFilter(data->val[0].dbl);                                                                                                                break;
  case eMinify:            that->getImage().minify();                                                                                                                                      break;
  case eModulate:          that->getImage().modulate(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl);                                                                                break;
  case eMotionBlur:        that->getImage().motionBlur(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl);                                                                              break;
  case eNegate:            that->getImage().negate(data->val[0].boolean);                                                                                                                  break;
  case eNormalize:         that->getImage().normalize();                                                                                                                                   break;
  case eOilPaint:          that->getImage().oilPaint(data->val[0].dbl);                                                                                                                    break;
  case eOpacity:           that->getImage().opacity(data->val[0].uint32);                                                                                                                  break;
  case eOpaque:            that->getImage().opaque(((Color*) data->val[0].pointer)->get(), ((Color*) data->val[1].pointer)->get());                                                        break;
  case eQuantize:          that->getImage().quantize(data->val[0].boolean);                                                                                                                break;
  case eRaise:             that->getImage().raise(data->val[0].pointer ? ((Geometry*) data->val[0].pointer)->get() : Magick::raiseGeometryDefault, data->val[1].boolean);                  break;
  case eRandomThreshold:   that->getImage().randomThreshold(((Geometry*) data->val[0].pointer)->get());                                                                                    break;
  case eRandomThresholdChannel: that->getImage().randomThresholdChannel(((Geometry*) data->val[0].pointer)->get(), (Magick::ChannelType) data->val[1].int32);                              break;
  case eReduceNoise1:      that->getImage().reduceNoise();                                                                                                                                 break;
  case eReduceNoise2:      that->getImage().reduceNoise(data->val[0].dbl);                                                                                                                 break;
  case eRoll1:             that->getImage().roll(((Geometry*) data->val[0].pointer)->get());                                                                                               break;
  case eRoll2:             that->getImage().roll(data->val[0].uint32, data->val[1].uint32);                                                                                                break;
  case eRotate:            that->getImage().rotate(data->val[0].dbl);                                                                                                                      break;
  case eSample:            that->getImage().sample(((Geometry*) data->val[0].pointer)->get());                                                                                             break;
  case eScale:             that->getImage().scale(((Geometry*) data->val[0].pointer)->get());                                                                                              break;
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
  case eCharcoal:
  case eChop:
  case eColorize1:
  case eColorize2:
  case eComment:
  case eContrast:
  case eCrop:
  case eCycleColormap:
  case eDespeckle:
  case eEdge:
  case eEmboss:
  case eEnhance:
  case eEqualize:
  case eErase:
  case eFlip:
  case eFloodFillColor1:
  case eFloodFillColor2:
  case eFloodFillColor3:
  case eFloodFillColor4:
  case eFloodFillOpacity:
  case eFlop:
  case eGamma1:
  case eGamma2:
  case eGaussianBlur:
  case eGaussianBlurChannel:
  case eImplode:
  case eLevel:
  case eLevelChannel:
  case eMagnify:
  case eMatteFloodfill:
  case eMedianFilter:
  case eMinify:
  case eModulate:
  case eMotionBlur:
  case eNegate:
  case eNormalize:
  case eOilPaint:
  case eOpacity:
  case eOpaque:
  case eQuantize:
  case eRaise:
  case eRandomThreshold:
  case eRandomThresholdChannel:
  case eReduceNoise1:
  case eReduceNoise2:
  case eRoll1:
  case eRoll2:
  case eRotate:
  case eSample:
  case eScale:
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

