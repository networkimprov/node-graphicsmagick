node-graphicsmagick
===================

Node.js binding for the [GraphicsMagick](http://www.graphicsmagick.org/) library.  
In development.

#API
The API tries to mimick the API of [Magick++](http://www.graphicsmagick.org/Magick++/index.html)

##Geometry
JSON object which provides convenient means to specify a geometry information. Similar to [this](http://www.graphicsmagick.org/Magick++/Geometry.html). Contains:
* width - Width, Uint32 value.
* height - Height, Uint32 value.
* xOff - X offset from origin, Uint32 value, default 0.
* yOff - Y offset from origin, Uint32 value, default 0.
* xNegative  - Sign of X offset negative? (X origin at right), Boolean value, default false.
* xNegative  - Sign of Y offset negative? (Y origin at bottom), Boolean value, default false.
* percent - Width and height are expressed as percentages, Boolean value, optional.
* aspect - Resize without preserving aspect ratio, Boolean value, optional.
* greater - Resize if image is greater than size (>), Boolean value, optional.
* less - Resize if image is less than size (<), Boolean value, optional.

**GeometryToString(Geometry obj)**  
Returns a geometry string encoding.

**StringToGeometry(String str)**  
Returns a Geometry object from a geometry string.

##Color
JSON object which provides information about color. Can take the form of ColorQuantum, ColorRGB, ColorGray, ColorMono, ColorHSL or ColorYUV. Similar to [this](http://www.graphicsmagick.org/Magick++/Color.html).

###ColorRGB
Representation of an RGB color in floating point. All color arguments have a valid range of 0.0 - 1.0. Contains:
* red - Red color, Number value.
* green - Green color, Number value.
* blue - Blue color, Number value.
* alpha - Alpha level (range OpaqueOpacity=0 to TransparentOpacity=1), Number value, optional.

###ColorQuantum
It is a simple container class for the pixel red, green, blue, and alpha values scaled to fit GraphicsMagick's Quantum (number of bits in a color component value) size.  The maximum value that a Quantum can attain is specified by a constant value represented by the MaxRGB. Contains:
* redQuantum - Red color (range 0 to MaxRGB), Uint32 value.
* greenQuantum - Green color (range 0 to MaxRGB), Uint32 value.
* blueQuantum - Blue color (range 0 to MaxRGB), Uint32 value.
* alphaQuantum - Alpha level (range OpaqueOpacity=0 to TransparentOpacity=MaxRGB), Uint32 value, optional.

###ColorGray
Representation of a grayscale color (in RGB colorspace). Grayscale is simply RGB with equal parts of red, green, and blue. All arguments have a valid range of 0.0 - 1.0. Contains:
* shade - Shade color, Number value.
* alpha - Alpha level (range OpaqueOpacity=0 to TransparentOpacity=1), Number value, optional.

###ColorMono
Representation of a black/white pixel (in RGB colorspace). Color arguments are constrained to 'false' (black pixel) and 'true' (white pixel):
* mono - Black or white pixel, Boolean value.
* alpha - Alpha level (range OpaqueOpacity=0 to TransparentOpacity=1), Number value, optional.

###ColorHSL
Representation of a color in Hue/Saturation/Luminosity (HSL) colorspace. All arguments have a valid range of 0.0 - 1.0. Contains:
* hue  - Hue color, Number value.
* saturation - Saturation color, Number value.
* luminosity - Luminosity color, Number value.
* alpha - Alpha level (range OpaqueOpacity=0 to TransparentOpacity=1), Number value, optional.

###ColorYUV
Representation of a color in YUV colorspace (used to encode color for television transmission). Argument are:
* Y - 0.0 through 1.0, Number value.
* U - -0.5 through 0.5, Number value.
* V - -0.5 through 0.5, Number value.

##Image
Image is the representation of an image.  

###Constructors

**Image( )**  
Default constructor  

**Image( Geometry size, Color color )**  
Construct a blank image canvas of specified size and color  

**TODO** Image( const std::string &imageSpec_ );  
Construct from image file or image specification  
    
**TODO** Image ( const Blob &blob_ );  
Construct Image from in-memory BLOB  

**TODO** Image ( const Blob &blob_, const Geometry &size_ );  
Construct Image of specified size from in-memory BLOB  

**TODO** Image ( const Blob &blob_, const Geometry &size, const unsigned int depth );  
Construct Image of specified size and depth from in-memory BLOB  

**TODO** Image ( const Blob &blob_, const Geometry &size, const unsigned int depth_, const std::string &magick_ );  
Construct Image of specified size, depth, and format from in-memory BLOB  

**TODO** Image ( const Blob &blob_, const Geometry &size, const std::string &magick_ );  
Construct Image of specified size, and format from in-memory BLOB  

**TODO** Image ( const unsigned int width_, const unsigned int height_, const std::string &map_, const StorageType type_, const void *pixels_ );  
Construct an image based on an array of raw pixels, of specified type and mapping, in memory  

###Image operations

**adaptiveThreshold ( Uint32 width, Uint32 height[, Uint32 offset = 0] )**  
Local adaptive threshold image http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm  
width x height define the size of the pixel neighborhood  
offset - constant to subtract from pixel neighborhood mean  

**addNoiseChannel ( ChannelType channel, NoiseType noiseType)**  
**addNoise ( NoiseType  )**  
Add noise to image with specified noise type  

**TODO** affineTransform ( const DrawableAffine &affine )  
Transform image by specified affine (or free transform) matrix.  

**annotate ( String text, Geometry location )**  
Annotate using specified text, and placement location    

**annotate ( String text, GravityType gravity[, Geometry boundingArea][, Number degrees] )**  
Annotate with text using specified text, bounding area, placement gravity, and rotation.

**blur ( [Number radius = 0.0][, Number sigma = 1.0] )**  
**blurChannel ( ChannelType channel[, Number radius = 0.0][, Number sigma = 1.0] )**  
Blur image with specified blur factor.  
The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  
The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**border ( [Geometry geometry = borderGeometryDefault] )**  
Border image (add border to image).  

**cdl ( String cdl )**  
Bake in the ASC-CDL, which is a convention for the for the exchange of basic primary color grading information between for the exchange of basic primary color grading information between equipment and software from different manufacturers.  It is a useful transform for other purposes as well.  

##Constants

####ChannelType
UndefinedChannel  
RedChannel  
CyanChannel  
GreenChannel  
MagentaChannel  
BlueChannel  
YellowChannel  
OpacityChannel  
BlackChannel  
MatteChannel  
AllChannels  
GrayChannel  

####Geometry
borderGeometryDefault






