node-graphicsmagick
===================

Node.js bindings for the [GraphicsMagick](http://www.graphicsmagick.org/) library.  
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


