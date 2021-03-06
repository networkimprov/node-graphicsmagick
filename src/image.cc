#include "node_graphicsmagick.h"
#include <node_buffer.h>

Persistent<FunctionTemplate> Image::constructor_template;

void Image::Init(Handle<Object> target) {
  constructor_template = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Image"));

  // Operations
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
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "compare", Compare);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "composite", Composite);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "compositeGeometry", CompositeGeometry);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "compositeGravity", CompositeGravity);
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
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "floodFillTexture", FloodFillTexture);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "flop", Flop);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "frame", Frame);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "gamma", Gamma);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "gaussianBlur", GaussianBlur);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "gaussianBlurChannel", GaussianBlurChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "haldClut", HaldClut);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "implode", Implode);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "level", Level);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "levelChannel", LevelChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "magnify", Magnify);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "map", Map);
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
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "quantumOperator", QuantumOperator);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "raise", Raise);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "randomThreshold", RandomThreshold);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "randomThresholdChannel", RandomThresholdChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "read", Read);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "reduceNoise", ReduceNoise);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "roll", Roll);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "rotate", Rotate);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "sample", Sample);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "scale", Scale);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "segment", Segment);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "shade", Shade);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "sharpen", Sharpen);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "sharpenChannel", SharpenChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "shave", Shave);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "shear", Shear);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "solarize", Solarize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "spread", Spread);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "stegano", Stegano);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "stereo", Stereo);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "strip", Strip);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "swirl", Swirl);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "texture", Texture);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "threshold", Threshold);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "transform", Transform);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "transparent", Transparent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "trim", Trim);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "unsharpmask", Unsharpmask);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "unsharpmaskChannel", UnsharpmaskChannel);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "wave", Wave);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "write", Write);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "writeFile", WriteFile);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "zoom", Zoom);

  // Attributes and Options
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "adjoin", Adjoin);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "antiAlias", AntiAlias);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "animationDelay", AnimationDelay);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "animationIterations", AnimationIterations);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "attribute", Attribute);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "backgroundColor", BackgroundColor);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "backgroundTexture", BackgroundTexture);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "baseColumns", BaseColumns);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "baseFilename", BaseFilename);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "baseRows", BaseRows);

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

  Local<Object> aCompositeOperator = Object::New();
  aCompositeOperator->Set(String::NewSymbol("AddCompositeOp"), Integer::New(Magick::AddCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("AtopCompositeOp"), Integer::New(Magick::AtopCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("BumpmapCompositeOp"), Integer::New(Magick::BumpmapCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("ClearCompositeOp"), Integer::New(Magick::ClearCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("ColorizeCompositeOp"), Integer::New(Magick::ColorizeCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyBlueCompositeOp"), Integer::New(Magick::CopyBlueCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyCompositeOp"), Integer::New(Magick::CopyCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyGreenCompositeOp"), Integer::New(Magick::CopyGreenCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyOpacityCompositeOp"), Integer::New(Magick::CopyOpacityCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyRedCompositeOp"), Integer::New(Magick::CopyRedCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("DarkenCompositeOp"), Integer::New(Magick::DarkenCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("DifferenceCompositeOp"), Integer::New(Magick::DifferenceCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("DisplaceCompositeOp"), Integer::New(Magick::DisplaceCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("DissolveCompositeOp"), Integer::New(Magick::DissolveCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("HueCompositeOp"), Integer::New(Magick::HueCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("InCompositeOp"), Integer::New(Magick::InCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("LightenCompositeOp"), Integer::New(Magick::LightenCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("LuminizeCompositeOp"), Integer::New(Magick::LuminizeCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("MinusCompositeOp"), Integer::New(Magick::MinusCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("ModulateCompositeOp"), Integer::New(Magick::ModulateCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("MultiplyCompositeOp"), Integer::New(Magick::MultiplyCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("NoCompositeOp"), Integer::New(Magick::NoCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("OutCompositeOp"), Integer::New(Magick::OutCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("OverCompositeOp"), Integer::New(Magick::OverCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("OverlayCompositeOp"), Integer::New(Magick::OverlayCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("PlusCompositeOp"), Integer::New(Magick::PlusCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("SaturateCompositeOp"), Integer::New(Magick::SaturateCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("ScreenCompositeOp"), Integer::New(Magick::ScreenCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("SubtractCompositeOp"), Integer::New(Magick::SubtractCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("ThresholdCompositeOp"), Integer::New(Magick::ThresholdCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("UndefinedCompositeOp"), Integer::New(Magick::UndefinedCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("XorCompositeOp"), Integer::New(Magick::XorCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyCyanCompositeOp"), Integer::New(Magick::CopyCyanCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyMagentaCompositeOp"), Integer::New(Magick::CopyMagentaCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyYellowCompositeOp"), Integer::New(Magick::CopyYellowCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("CopyBlackCompositeOp"), Integer::New(Magick::CopyBlackCompositeOp), ReadOnly);
  aCompositeOperator->Set(String::NewSymbol("DivideCompositeOp"), Integer::New(Magick::DivideCompositeOp), ReadOnly);
  target->Set(String::NewSymbol("CompositeOperator"), aCompositeOperator);

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

  Local<Object> aQuantumOperator = Object::New();
  aQuantumOperator->Set(String::NewSymbol("AddQuantumOp"), Integer::New(Magick::AddQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("AndQuantumOp"), Integer::New(Magick::AndQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("AssignQuantumOp"), Integer::New(Magick::AssignQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("DivideQuantumOp"), Integer::New(Magick::DivideQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("LShiftQuantumOp"), Integer::New(Magick::LShiftQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("MultiplyQuantumOp"), Integer::New(Magick::MultiplyQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("OrQuantumOp"), Integer::New(Magick::OrQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("RShiftQuantumOp"), Integer::New(Magick::RShiftQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("SubtractQuantumOp"), Integer::New(Magick::SubtractQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("ThresholdQuantumOp"), Integer::New(Magick::ThresholdQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("ThresholdBlackQuantumOp"), Integer::New(Magick::ThresholdBlackQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("ThresholdWhiteQuantumOp"), Integer::New(Magick::ThresholdWhiteQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("XorQuantumOp"), Integer::New(Magick::XorQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NoiseGaussianQuantumOp"), Integer::New(Magick::NoiseGaussianQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NoiseImpulseQuantumOp"), Integer::New(Magick::NoiseImpulseQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NoiseLaplacianQuantumOp"), Integer::New(Magick::NoiseLaplacianQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NoiseMultiplicativeQuantumOp"), Integer::New(Magick::NoiseMultiplicativeQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NoisePoissonQuantumOp"), Integer::New(Magick::NoisePoissonQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NoiseUniformQuantumOp"), Integer::New(Magick::NoiseUniformQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("NegateQuantumOp"), Integer::New(Magick::NegateQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("GammaQuantumOp"), Integer::New(Magick::GammaQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("DepthQuantumOp"), Integer::New(Magick::DepthQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("LogQuantumOp"), Integer::New(Magick::LogQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("MaxQuantumOp"), Integer::New(Magick::MaxQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("MinQuantumOp"), Integer::New(Magick::MinQuantumOp), ReadOnly);
  aQuantumOperator->Set(String::NewSymbol("PowQuantumOp"), Integer::New(Magick::PowQuantumOp), ReadOnly);
  target->Set(String::NewSymbol("QuantumOperator"), aQuantumOperator);

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
  eCompare,
  eComposite, eCompositeGeometry, eCompositeGravity,
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
  eFloodFillTexture1, eFloodFillTexture2, eFloodFillTexture3, eFloodFillTexture4,
  eFlop,
  eFrame1, eFrame2,
  eGamma1, eGamma2,
  eGaussianBlur,
  eGaussianBlurChannel,
  eHaldClut,
  eImplode,
  eLevel,
  eLevelChannel,
  eMagnify,
  eMap,
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
  eQuantumOperator1, eQuantumOperator2,
  eRaise,
  eRandomThreshold,
  eRandomThresholdChannel,
  eRead1, eRead2, eRead3, eRead4, eRead5, eRead6, eRead7,
  eReduceNoise1, eReduceNoise2,
  eRoll1, eRoll2,
  eRotate,
  eSample,
  eScale,
  eSegment,
  eShade,
  eSharpen,
  eSharpenChannel,
  eShave,
  eShear,
  eSolarize,
  eSpread,
  eStegano,
  eStereo,
  eStrip,
  eSwirl,
  eTexture,
  eThreshold,
  eTransform,
  eTransparent,
  eTrim,
  eUnsharpmask,
  eUnsharpmaskChannel,
  eWave,
  eWrite1, eWrite2, eWrite3,
  eWriteFile,
  eZoom,

  eAdjoin1, eAdjoin2,
  eAntiAlias1, eAntiAlias2,
  eAnimationDelay1, eAnimationDelay2,
  eAnimationIterations1, eAnimationIterations2,
  eAttribute1, eAttribute2,
  eBackgroundColor1, eBackgroundColor2,
  eBackgroundTexture1, eBackgroundTexture2,
  eBaseColumns,
  eBaseFilename,
  eBaseRows
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

static int kCompare[] = { eObjectImage, -eFunction, eEnd };
Handle<Value> Image::Compare(const Arguments& args) {
  return generic_check_start<Image>(eCompare, args, kCompare);
}

static int kComposite[] = { eObjectImage, eUint32, eUint32, -eInt32, -eFunction, eEnd };
Handle<Value> Image::Composite(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetInt32(Magick::InCompositeOp);
  return generic_check_start<Image>(eComposite, args, kComposite, aDefaults);
}

static int kCompositeGeometry[] = { eObjectImage, eObjectGeometry, -eInt32, -eFunction, eEnd };
Handle<Value> Image::CompositeGeometry(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetInt32(Magick::InCompositeOp);
  return generic_check_start<Image>(eCompositeGeometry, args, kCompositeGeometry, aDefaults);
}

static int kCompositeGravity[] = { eObjectImage, eInt32, -eInt32, -eFunction, eEnd };
Handle<Value> Image::CompositeGravity(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetInt32(Magick::InCompositeOp);
  return generic_check_start<Image>(eCompositeGravity, args, kCompositeGravity, aDefaults);
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

static int kFloodFillTexture1[] = { eUint32, eUint32, eObjectImage, -eFunction, eEnd };
static int kFloodFillTexture2[] = { eObjectGeometry, eObjectImage, -eFunction, eEnd };
static int kFloodFillTexture3[] = { eUint32, eUint32, eObjectImage, eObjectColor, -eFunction, eEnd };
static int kFloodFillTexture4[] = { eObjectGeometry, eObjectImage, eObjectColor, -eFunction, eEnd };
static SetType kFloodFillTextureSetType[] = { { kFloodFillTexture1, eFloodFillTexture1 }, { kFloodFillTexture2, eFloodFillTexture2 }, { kFloodFillTexture3, eFloodFillTexture3 }, { kFloodFillTexture4, eFloodFillTexture4 }, { NULL, 0 } };
Handle<Value> Image::FloodFillTexture(const Arguments& args) {
  return generic_check_start<Image>(args, kFloodFillTextureSetType);
}

static int kFlop[] = { -eFunction, eEnd };
Handle<Value> Image::Flop(const Arguments& args) {
  return generic_check_start<Image>(eFlop, args, kFlop);
}

static int kFrame1[] = { -eObjectGeometry, -eFunction, eEnd };
static int kFrame2[] = { eUint32, eUint32, -eUint32, -eUint32, -eFunction, eEnd };
static SetType kFrameSetType[] = { { kFrame1, eFrame1 },  { kFrame2, eFrame2 }, { NULL, 0 } };
Handle<Value> Image::Frame(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults1[1];
  GenericFunctionCall::GenericValue aDefaults2[2];
  GenericFunctionCall::GenericValue* aDefaultsArr[2] = { aDefaults1, aDefaults2 };
  aDefaults1[0].SetPointer(NULL, eObjectGeometry);
  aDefaults2[0].SetUint32(6);
  aDefaults2[1].SetUint32(6);
  return generic_check_start<Image>(args, kFrameSetType, aDefaultsArr);
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

static int kHaldClut[] = { eObjectImage, -eFunction, eEnd };
Handle<Value> Image::HaldClut(const Arguments& args) {
  return generic_check_start<Image>(eHaldClut, args, kHaldClut);
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

static int kMap[] = { eObjectImage, -eBoolean, -eFunction, eEnd };
Handle<Value> Image::Map(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetBool(false);
  return generic_check_start<Image>(eMap, args, kMap, aDefaults);
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

static int kQuantumOperator1[] = { eInt32, eInt32, eNumber, -eFunction, eEnd };
static int kQuantumOperator2[] = { eInt32, eInt32, eUint32, eUint32, eInt32, eInt32, eNumber, -eFunction, eEnd };
static SetType kQuantumOperatorSetType[] = { { kQuantumOperator1, eQuantumOperator1 },  { kQuantumOperator2, eQuantumOperator2 }, { NULL, 0 } };
Handle<Value> Image::QuantumOperator(const Arguments& args) {
  return generic_check_start<Image>(args, kQuantumOperatorSetType);
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

static int kRead1[] = { eString, -eFunction, eEnd };
static int kRead2[] = { eObjectGeometry, eObjectColor, -eFunction, eEnd };
static int kRead3[] = { eObjectBlob, -eFunction, eEnd };
static int kRead4[] = { eObjectBlob, eObjectGeometry, -eFunction, eEnd };
static int kRead5[] = { eObjectBlob, eObjectGeometry, eUint32, -eFunction, eEnd };
static int kRead6[] = { eObjectBlob, eObjectGeometry, eUint32, eString, -eFunction, eEnd };
static int kRead7[] = { eObjectBlob, eObjectGeometry, eString, -eFunction, eEnd };
static SetType kReadSetType[] = { { kRead1, eRead1}, { kRead2, eRead2}, { kRead3, eRead3}, { kRead4, eRead4}, { kRead5, eRead5}, { kRead6, eRead6}, { kRead7, eRead7}, { NULL, 0 } };
Handle<Value> Image::Read(const Arguments& args) {
  return generic_check_start<Image>(args, kReadSetType);
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

static int kSegment[] = { -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Segment(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(1);
  aDefaults[1].SetNumber(1.5);
  return generic_check_start<Image>(eSegment, args, kSegment, aDefaults);
}

static int kShade[] = { -eNumber, -eNumber, -eBoolean, -eFunction, eEnd };
Handle<Value> Image::Shade(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[3];
  aDefaults[0].SetNumber(30);
  aDefaults[1].SetNumber(30);
  aDefaults[2].SetBool(false);
  return generic_check_start<Image>(eShade, args, kShade, aDefaults);
}

static int kSharpen[] = { -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Sharpen(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(0);
  aDefaults[1].SetNumber(1);
  return generic_check_start<Image>(eSharpen, args, kSharpen, aDefaults);
}

static int kSharpenChannel[] = { eInt32, -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::SharpenChannel(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(0);
  aDefaults[1].SetNumber(1);
  return generic_check_start<Image>(eSharpenChannel, args, kSharpenChannel, aDefaults);
}

static int kShave[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Shave(const Arguments& args) {
  return generic_check_start<Image>(eShave, args, kShave);
}

static int kShear[] = { eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::Shear(const Arguments& args) {
  return generic_check_start<Image>(eShear, args, kShear);
}

static int kSolarize[] = { -eNumber, -eFunction, eEnd };
Handle<Value> Image::Solarize(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetNumber(50);
  return generic_check_start<Image>(eSolarize, args, kSolarize, aDefaults);
}

static int kSpread[] = { -eUint32, -eFunction, eEnd };
Handle<Value> Image::Spread(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetUint32(3);
  return generic_check_start<Image>(eSpread, args, kSpread, aDefaults);
}

static int kStegano[] = { eObjectImage, -eFunction, eEnd };
Handle<Value> Image::Stegano(const Arguments& args) {
  return generic_check_start<Image>(eStegano, args, kStegano);
}

static int kStereo[] = { eObjectImage, -eFunction, eEnd };
Handle<Value> Image::Stereo(const Arguments& args) {
  return generic_check_start<Image>(eStereo, args, kStereo);
}

static int kStrip[] = { -eFunction, eEnd };
Handle<Value> Image::Strip(const Arguments& args) {
  return generic_check_start<Image>(eStrip, args, kStrip);
}

static int kSwirl[] = { eNumber, -eFunction, eEnd };
Handle<Value> Image::Swirl(const Arguments& args) {
  return generic_check_start<Image>(eSwirl, args, kSwirl);
}

static int kTexture[] = { eObjectImage, -eFunction, eEnd };
Handle<Value> Image::Texture(const Arguments& args) {
  return generic_check_start<Image>(eTexture, args, kTexture);
}

static int kThreshold[] = { eNumber, -eFunction, eEnd };
Handle<Value> Image::Threshold(const Arguments& args) {
  return generic_check_start<Image>(eThreshold, args, kThreshold);
}

static int kTransform[] = { eObjectGeometry, -eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Transform(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[1];
  aDefaults[0].SetPointer(NULL, eObjectGeometry);
  return generic_check_start<Image>(eTransform, args, kTransform, aDefaults);
}

static int kTransparent[] = { eObjectColor, -eFunction, eEnd };
Handle<Value> Image::Transparent(const Arguments& args) {
  return generic_check_start<Image>(eTransparent, args, kTransparent);
}

static int kTrim[] = { -eFunction, eEnd };
Handle<Value> Image::Trim(const Arguments& args) {
  return generic_check_start<Image>(eTrim, args, kTrim);
}

static int kUnsharpmask[] = { eNumber, eNumber, eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::Unsharpmask(const Arguments& args) {
  return generic_check_start<Image>(eUnsharpmask, args, kUnsharpmask);
}

static int kUnsharpmaskChannel[] = { eInt32, eNumber, eNumber, eNumber, eNumber, -eFunction, eEnd };
Handle<Value> Image::UnsharpmaskChannel(const Arguments& args) {
  return generic_check_start<Image>(eUnsharpmaskChannel, args, kUnsharpmaskChannel);
}

static int kWave[] = { -eNumber, -eNumber, -eFunction, eEnd };
Handle<Value> Image::Wave(const Arguments& args) {
  GenericFunctionCall::GenericValue aDefaults[2];
  aDefaults[0].SetNumber(25);
  aDefaults[1].SetNumber(150);
  return generic_check_start<Image>(eWave, args, kWave, aDefaults);
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

static int kZoom[] = { eObjectGeometry, -eFunction, eEnd };
Handle<Value> Image::Zoom(const Arguments& args) {
  return generic_check_start<Image>(eZoom, args, kZoom);
}

static int kAdjoin1[] = { eBoolean, -eFunction, eEnd };
static int kAdjoin2[] = { -eFunction, eEnd };
static SetType kAdjoinSetType[] = { { kAdjoin1, eAdjoin1}, { kAdjoin2, eAdjoin2}, { NULL, 0 } };
Handle<Value> Image::Adjoin(const Arguments& args) {
  return generic_check_start<Image>(args, kAdjoinSetType);
}

static int kAntiAlias1[] = { eBoolean, -eFunction, eEnd };
static int kAntiAlias2[] = { -eFunction, eEnd };
static SetType kAntiAliasSetType[] = { { kAntiAlias1, eAntiAlias1}, { kAntiAlias2, eAntiAlias2}, { NULL, 0 } };
Handle<Value> Image::AntiAlias(const Arguments& args) {
  return generic_check_start<Image>(args, kAntiAliasSetType);
}

static int kAnimationDelay1[] = { eUint32, -eFunction, eEnd };
static int kAnimationDelay2[] = { -eFunction, eEnd };
static SetType kAnimationDelaySetType[] = { { kAnimationDelay1, eAnimationDelay1}, { kAnimationDelay2, eAnimationDelay2}, { NULL, 0 } };
Handle<Value> Image::AnimationDelay(const Arguments& args) {
  return generic_check_start<Image>(args, kAnimationDelaySetType);
}

static int kAnimationIterations1[] = { eUint32, -eFunction, eEnd };
static int kAnimationIterations2[] = { -eFunction, eEnd };
static SetType kAnimationIterationsSetType[] = { { kAnimationIterations1, eAnimationIterations1}, { kAnimationIterations2, eAnimationIterations2}, { NULL, 0 } };
Handle<Value> Image::AnimationIterations(const Arguments& args) {
  return generic_check_start<Image>(args, kAnimationIterationsSetType);
}

static int kAttribute1[] = { eString, eString, -eFunction, eEnd };
static int kAttribute2[] = { eString, -eFunction, eEnd };
static SetType kAttributeSetType[] = { { kAttribute1, eAttribute1}, { kAttribute2, eAttribute2}, { NULL, 0 } };
Handle<Value> Image::Attribute(const Arguments& args) {
  return generic_check_start<Image>(args, kAttributeSetType);
}

static int kBackgroundColor1[] = { eObjectColor, -eFunction, eEnd };
static int kBackgroundColor2[] = { -eFunction, eEnd };
static SetType kBackgroundColorSetType[] = { { kBackgroundColor1, eBackgroundColor1}, { kBackgroundColor2, eBackgroundColor2}, { NULL, 0 } };
Handle<Value> Image::BackgroundColor(const Arguments& args) {
  return generic_check_start<Image>(args, kBackgroundColorSetType);
}

static int kBackgroundTexture1[] = { eString, -eFunction, eEnd };
static int kBackgroundTexture2[] = { -eFunction, eEnd };
static SetType kBackgroundTextureSetType[] = { { kBackgroundTexture1, eBackgroundTexture1}, { kBackgroundTexture2, eBackgroundTexture2}, { NULL, 0 } };
Handle<Value> Image::BackgroundTexture(const Arguments& args) {
  return generic_check_start<Image>(args, kBackgroundTextureSetType);
}

static int kBaseColumns[] = { -eFunction, eEnd };
Handle<Value> Image::BaseColumns(const Arguments& args) {
  return generic_check_start<Image>(eBaseColumns, args, kBaseColumns);
}

static int kBaseFilename[] = { -eFunction, eEnd };
Handle<Value> Image::BaseFilename(const Arguments& args) {
  return generic_check_start<Image>(eBaseFilename, args, kBaseFilename);
}

static int kBaseRows[] = { -eFunction, eEnd };
Handle<Value> Image::BaseRows(const Arguments& args) {
  return generic_check_start<Image>(eBaseRows, args, kBaseRows);
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
  case eCompare:           data->retVal.SetBool(that->getImage().compare(((Image*) data->val[0].pointer)->getImage()));                                                                    break;
  case eComposite:         that->getImage().composite(((Image*) data->val[0].pointer)->getImage(), data->val[1].uint32, data->val[2].uint32, (Magick::CompositeOperator) data->val[3].int32); break;
  case eCompositeGeometry: that->getImage().composite(((Image*) data->val[0].pointer)->getImage(), ((Geometry*) data->val[1].pointer)->get(), (Magick::CompositeOperator) data->val[2].int32); break;
  case eCompositeGravity:  that->getImage().composite(((Image*) data->val[0].pointer)->getImage(), (Magick::GravityType) data->val[1].int32, (Magick::CompositeOperator) data->val[2].int32); break;
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
  case eFloodFillTexture1: that->getImage().floodFillTexture(data->val[0].uint32, data->val[1].uint32, ((Image*) data->val[2].pointer)->getImage());                                       break;
  case eFloodFillTexture2: that->getImage().floodFillTexture(((Geometry*) data->val[0].pointer)->get(), ((Image*) data->val[1].pointer)->getImage());                                      break;
  case eFloodFillTexture3: that->getImage().floodFillTexture(data->val[0].uint32, data->val[1].uint32, ((Image*) data->val[2].pointer)->getImage(), ((Color*) data->val[3].pointer)->get()); break;
  case eFloodFillTexture4: that->getImage().floodFillTexture(((Geometry*) data->val[0].pointer)->get(), ((Image*) data->val[1].pointer)->getImage(), ((Color*) data->val[2].pointer)->get()); break;
  case eFlop:              that->getImage().flop();                                                                                                                                        break;
  case eFrame1:            that->getImage().frame(data->val[0].pointer ? ((Geometry*) data->val[0].pointer)->get() : Magick::frameGeometryDefault);                                        break;
  case eFrame2:            that->getImage().frame(data->val[0].uint32, data->val[1].uint32, data->val[2].uint32, data->val[3].uint32);                                                     break;
  case eGamma1:            that->getImage().gamma(data->val[0].dbl);                                                                                                                       break;
  case eGamma2:            that->getImage().gamma(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl);                                                                                   break;
  case eGaussianBlur:      that->getImage().gaussianBlur(data->val[0].dbl, data->val[1].dbl);                                                                                              break;
  case eGaussianBlurChannel: that->getImage().gaussianBlurChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl);                                           break;
  case eHaldClut:          that->getImage().haldClut(((Image*) data->val[0].pointer)->getImage());                                                                                         break;
  case eImplode:           that->getImage().implode(data->val[0].dbl);                                                                                                                     break;
  case eLevel:             that->getImage().level(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl);                                                                                   break;
  case eLevelChannel:      that->getImage().levelChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl, data->val[3].dbl);                                  break;
  case eMagnify:           that->getImage().magnify();                                                                                                                                     break;
  case eMap:               that->getImage().map(((Image*) data->val[0].pointer)->getImage(), data->val[1].boolean);                                                                        break;
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
  case eQuantumOperator1:  that->getImage().quantumOperator((Magick::ChannelType) data->val[0].int32, (Magick::QuantumOperator) data->val[1].int32, data->val[2].dbl);                            break;
  case eQuantumOperator2:  that->getImage().quantumOperator(data->val[0].int32, data->val[1].int32, data->val[2].uint32, data->val[3].uint32, (Magick::ChannelType) data->val[4].int32, (Magick::QuantumOperator) data->val[5].int32, data->val[6].dbl); break;
  case eRaise:             that->getImage().raise(data->val[0].pointer ? ((Geometry*) data->val[0].pointer)->get() : Magick::raiseGeometryDefault, data->val[1].boolean);                  break;
  case eRandomThreshold:   that->getImage().randomThreshold(((Geometry*) data->val[0].pointer)->get());                                                                                    break;
  case eRandomThresholdChannel: that->getImage().randomThresholdChannel(((Geometry*) data->val[0].pointer)->get(), (Magick::ChannelType) data->val[1].int32);                              break;
  case eRead1:              that->getImage().read(*data->val[0].string);                                                                                                                   break;
  case eRead2:              that->getImage().read(((Geometry*) data->val[0].pointer)->get(), ((Color*) data->val[1].pointer)->get());                                                      break;
  case eRead3:              that->getImage().read(((Blob*) data->val[0].pointer)->get());                                                                                                  break;
  case eRead4:              that->getImage().read(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get());                                                       break;
  case eRead5:              that->getImage().read(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get(), data->val[2].uint32);                                  break;
  case eRead6:              that->getImage().read(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get(), data->val[2].uint32, *data->val[3].string);            break;
  case eRead7:              that->getImage().read(((Blob*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get(), *data->val[2].string);                                 break;
  case eReduceNoise1:      that->getImage().reduceNoise();                                                                                                                                 break;
  case eReduceNoise2:      that->getImage().reduceNoise(data->val[0].dbl);                                                                                                                 break;
  case eRoll1:             that->getImage().roll(((Geometry*) data->val[0].pointer)->get());                                                                                               break;
  case eRoll2:             that->getImage().roll(data->val[0].uint32, data->val[1].uint32);                                                                                                break;
  case eRotate:            that->getImage().rotate(data->val[0].dbl);                                                                                                                      break;
  case eSample:            that->getImage().sample(((Geometry*) data->val[0].pointer)->get());                                                                                             break;
  case eScale:             that->getImage().scale(((Geometry*) data->val[0].pointer)->get());                                                                                              break;
  case eSegment:           that->getImage().segment(data->val[0].dbl, data->val[1].dbl);                                                                                                   break;
  case eShade:             that->getImage().shade(data->val[0].dbl, data->val[1].dbl, data->val[2].boolean);                                                                               break;
  case eSharpen:           that->getImage().sharpen(data->val[0].dbl, data->val[1].dbl);                                                                                                   break;
  case eSharpenChannel:    that->getImage().sharpenChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl);                                                  break;
  case eShave:             that->getImage().shave(((Geometry*) data->val[0].pointer)->get());                                                                                              break;
  case eShear:             that->getImage().shear(data->val[0].dbl, data->val[1].dbl);                                                                                                     break;
  case eSolarize:          that->getImage().solarize(data->val[0].dbl);                                                                                                                    break;
  case eSpread:            that->getImage().spread(data->val[0].uint32);                                                                                                                   break;
  case eStegano:           that->getImage().stegano(((Image*) data->val[0].pointer)->getImage());                                                                                          break;
  case eStereo:            that->getImage().stereo(((Image*) data->val[0].pointer)->getImage());                                                                                           break;
  case eStrip:             that->getImage().strip();                                                                                                                                       break;
  case eSwirl:             that->getImage().swirl(data->val[0].dbl);                                                                                                                       break;
  case eTexture:           that->getImage().texture(((Image*) data->val[0].pointer)->getImage());                                                                                          break;
  case eThreshold:         that->getImage().threshold(data->val[0].dbl);                                                                                                                   break;
  case eTransform:         
    if (data->val[1].pointer) that->getImage().transform(((Geometry*) data->val[0].pointer)->get(), ((Geometry*) data->val[1].pointer)->get());
    else that->getImage().transform(((Geometry*) data->val[0].pointer)->get());
    break;
  case eTransparent:       that->getImage().transparent(((Color*) data->val[0].pointer)->get());                                                                                           break;
  case eTrim:              that->getImage().trim();                                                                                                                                        break;
  case eUnsharpmask:       that->getImage().unsharpmask(data->val[0].dbl, data->val[1].dbl, data->val[2].dbl, data->val[3].dbl);                                                           break;
  case eUnsharpmaskChannel: that->getImage().unsharpmaskChannel((Magick::ChannelType) data->val[0].int32, data->val[1].dbl, data->val[2].dbl, data->val[3].dbl, data->val[4].dbl);         break;
  case eWave:              that->getImage().wave(data->val[0].dbl, data->val[1].dbl);                                                                                                      break;
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
  case eZoom:              that->getImage().zoom(((Geometry*) data->val[0].pointer)->get());                                                                                               break;
  case eAdjoin1:           that->getImage().adjoin(data->val[0].boolean);                                                                                                                  break;
  case eAdjoin2:           data->retVal.SetBool(that->getImage().adjoin());                                                                                                                break;
  case eAntiAlias1:        that->getImage().antiAlias(data->val[0].boolean);                                                                                                               break;
  case eAntiAlias2:        data->retVal.SetBool(that->getImage().antiAlias());                                                                                                             break;
  case eAnimationDelay1:   that->getImage().animationDelay(data->val[0].uint32);                                                                                                           break;
  case eAnimationDelay2:   data->retVal.SetUint32(that->getImage().animationDelay());                                                                                                      break;
  case eAnimationIterations1: that->getImage().animationIterations(data->val[0].uint32);                                                                                                   break;
  case eAnimationIterations2: data->retVal.SetUint32(that->getImage().animationIterations());                                                                                              break;
  case eAttribute1:        that->getImage().attribute(*data->val[0].string, *data->val[1].string);                                                                                         break;
  case eAttribute2:        data->retVal.SetString(that->getImage().attribute(*data->val[0].string));                                                                                       break;
  case eBackgroundColor1:  that->getImage().backgroundColor(((Color*) data->val[0].pointer)->get());                                                                                       break;
  case eBackgroundColor2:  data->retVal.SetPointer(new Magick::Color(that->getImage().backgroundColor()), ePointer);                                                                       break;
//    Magick::Color *aBgColor = that->getImage().backgroundColor();

//    Local<Value> aColorExt[] = { External::New(aBgColor) };
/*    Handle<Value> aColor = Color::constructor_template->GetFunction()->NewInstance(1, aColorExt);
    data->retVal.SetPointer((void*) GetInstance<Color>(aColor), eObjectColor);
    ((Color*) data->retVal.pointer)->Reference();
*/
  case eBackgroundTexture1: that->getImage().backgroundTexture(*data->val[0].string);                                                                                                      break;
  case eBackgroundTexture2: data->retVal.SetString(that->getImage().backgroundTexture());                                                                                                  break;
  case eBaseColumns:       data->retVal.SetUint32(that->getImage().baseColumns());                                                                                                         break;
  case eBaseFilename:      data->retVal.SetString(that->getImage().baseFilename());                                                                                                        break;
  case eBaseRows:          data->retVal.SetUint32(that->getImage().baseRows());                                                                                                            break;
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
  case eComposite:
  case eCompositeGeometry:
  case eCompositeGravity:
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
  case eFloodFillTexture1:
  case eFloodFillTexture2:
  case eFloodFillTexture3:
  case eFloodFillTexture4:
  case eFlop:
  case eFrame1:
  case eFrame2:
  case eGamma1:
  case eGamma2:
  case eGaussianBlur:
  case eGaussianBlurChannel:
  case eHaldClut:
  case eImplode:
  case eLevel:
  case eLevelChannel:
  case eMagnify:
  case eMap:
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
  case eQuantumOperator1:
  case eQuantumOperator2:
  case eRaise:
  case eRandomThreshold:
  case eRandomThresholdChannel:
  case eRead1:
  case eRead2:
  case eRead3:
  case eRead4:
  case eRead5:
  case eRead6:
  case eRead7:
  case eReduceNoise1:
  case eReduceNoise2:
  case eRoll1:
  case eRoll2:
  case eRotate:
  case eSample:
  case eScale:
  case eSegment:
  case eShade:
  case eSharpen:
  case eSharpenChannel:
  case eShave:
  case eShear:
  case eSolarize:
  case eSpread:
  case eStegano:
  case eStereo:
  case eStrip:
  case eSwirl:
  case eTexture:
  case eThreshold:
  case eTransform:
  case eTransparent:
  case eTrim:
  case eUnsharpmask:
  case eUnsharpmaskChannel:
  case eWave:
  case eWriteFile:
  case eZoom:
  case eAdjoin1:
  case eAntiAlias1:
  case eAnimationDelay1:
  case eAnimationIterations1:
  case eAttribute1:
  case eBackgroundColor1:
  case eBackgroundTexture1:
    aResult = ((Color*) data->retVal.pointer)->handle_;
    break;
  case eWrite1:
  case eWrite2:
  case eWrite3: {
    Magick::Blob* aBlob = (Magick::Blob*) data->retVal.pointer;
    aResult = Blob::constructor_template->GetFunction()->NewInstance();
    GetInstance<Blob>(aResult)->set(aBlob);
  } break;
  case eChannelDepth2:
  case eAnimationDelay2:
  case eAnimationIterations2:
  case eBaseColumns:
  case eBaseRows:
    aResult = Uint32::New(data->retVal.uint32);
    break;
  case eCompare:
  case eAdjoin2:
  case eAntiAlias2:
    aResult = Boolean::New(data->retVal.boolean);
    break;
  case eAttribute2:
  case eBackgroundTexture2:
  case eBaseFilename:
    aResult = String::New(data->retVal.string->c_str());
    break;
  case eBackgroundColor2:
    Magick::Color* aBgColor = (Magick::Color*) data->retVal.pointer;
    Local<Value> aColorExt[] = { External::New(aBgColor) };
    aResult = Color::constructor_template->GetFunction()->NewInstance(1, aColorExt);
    break;
  }
  delete data;
  return aResult;
}

