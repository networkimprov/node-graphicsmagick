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

**TODO** Image( String imageSpec )  
Construct from image file or image specification  
 
**TODO** Image ( const Blob &blob )  
Construct Image from in-memory BLOB  

**TODO** Image ( const Blob &blob, Geometry size )  
Construct Image of specified size from in-memory BLOB  

**TODO** Image ( const Blob &blob, Geometry size, Uint32 depth )  
Construct Image of specified size and depth from in-memory BLOB  

**TODO** Image ( const Blob &blob, Geometry size, Uint32 depth, String magick )  
Construct Image of specified size, depth, and format from in-memory BLOB  

**TODO** Image ( const Blob &blob, Geometry size, String magick )  
Construct Image of specified size, and format from in-memory BLOB  

**TODO** Image ( Uint32 width, Uint32 height, String map, const StorageType type, const void *pixels )  
Construct an image based on an array of raw pixels, of specified type and mapping, in memory  

###Image operations

**TODO: Unless otherwise specified, all the methods return the Image object for chaining.**
**TODO: Unless otherwise specified, all the methods in image operations have an async variant, [method]Async.**

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

**channel ( ChannelType channel )**  
Extract channel from image  

**channelDepth ( ChannelType channel, Uint32 depth )**  
Set modulus channel depth.  

**channelDepth ( ChannelType channel )**  
Returns modulus channel depth.  

**charcoal ( [Number radius = 0.0][, Number sigma = 1.0] )**  
Charcoal effect image (looks like charcoal sketch). The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**chop ( Geometry geometry )**  
Chop image (remove vertical or horizontal subregion of image).  

**colorize ( Uint32 opacityRed, Uint32 opacityGreen, Uint32 opacityBlue, Color penColor )**  
Colorize image with pen color, using specified percent opacity for red, green, and blue quantums.  

**colorize ( Uint32 opacity, Color penColor )**  
Colorize image with pen color, using specified percent opacity.  

**colorMatrix (NumberArrayOfArray color_matrix )**  
Apply a color matrix to the image channels.  The user supplied matrix may be of order 1 to 5 (1x1 through 5x5).  
For example: colorMatrix( [ [ 1, 1], [ 1, 1] ])  

**comment ( String comment )**  
Comment image (add comment string to image).  

**compare ( Image img )**  
Compare current image with another image. Sets meanErrorPerPixel, normalizedMaxError, and normalizedMeanError in the current image.  
Returns wether the images are identical.  

**composite ( Image compositeImage, Uint32 xOffset, Uint32 yOffset[, CompositeOperator compose = InCompositeOp] )**  
**composite ( Image compositeImage, Geometry offset[, CompositeOperator compose = InCompositeOp] )**  
**composite ( Image compositeImage, GravityType gravity[, CompositeOperator compose = InCompositeOp] )**  
Compose an image onto another at specified offset and using specified algorithm.  

**contrast ( Uint32 sharpen )**  
Contrast image (enhance intensity differences in image).  

**convolve ( NumberArrayOfArray kernel )**  
Convolve image.  Applies a user-specified convolution to the image.  
For example: convolve( [ [ 1, 1], [ 1, 1] ])  

**crop ( Geometry geometry )**  
Crop image (subregion of original image).  

**cycleColormap ( Uint32 amount )**  
Cycle image colormap.  

**despeckle ( )**  
Despeckle image (reduce speckle noise).  
 
**TODO** void display ( )  
Display image on screen.  

**TODO** void draw ( const Drawable &drawable )  
Draw on image using a single drawable.  
 
**TODO** void draw ( const std::list<Magick::Drawable> &drawable )  
Draw on image using a drawable list.  

**edge ( [Number radius = 0.0] )**  
Edge image (hilight edges in image).  

**emboss ( [Number radius = 0.0][, Number sigma = 1.0])**  
Emboss image (hilight edges with 3D effect). The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**enhance ( )**  
Enhance image (minimize noise).  

**equalize ( )**  
Equalize image (histogram equalization).  

**erase ( )**  
Erase image to current "background color".  

**flip ( )**  
Flip image (reflect each scanline in the vertical direction).  

**floodFillColor( Uint32 x, Uint32 y, Color fillColor )**  
**floodFillColor( Geometry point, Color fillColor )**  
Flood-fill color across pixels that match the color of the target pixel and are neighbors of the target pixel. Uses current fuzz setting when determining color match.  

**floodFillColor( Uint32 x, Uint32 y, Color fillColor, Color borderColor )**  
**floodFillColor( Geometry point, Color fillColor, Color borderColor )**  
Flood-fill color across pixels starting at target-pixel and stopping at pixels matching specified border color. Uses current fuzz setting when determining color match.  

**floodFillOpacity ( Uint32 x, Uint32 y, Uint32 opacity, PaintMethod method )**  
Floodfill pixels matching color (within fuzz factor) of target pixel(x,y) with replacement opacity value using method.  

**floodFillTexture( Uint32 x, Uint32 y, Image texture )**  
**floodFillTexture( Geometry point, Image texture )**  
Flood-fill texture across pixels that match the color of the target pixel and are neighbors of the target pixel. Uses current fuzz setting when determining color match.  

**floodFillTexture( Uint32 x, Uint32 y, Image texture, Color borderColor )**  
**floodFillTexture( Geometry point, Image texture, Color borderColor )**  
Flood-fill texture across pixels starting at target-pixel and stopping at pixels matching specified border color. Uses current fuzz setting when determining color match.  

**flop ( )**  
Flop image (reflect each scanline in the horizontal direction).  

**frame ( [Geometry geometry = frameGeometryDefault] )**  
**frame ( Uint32 width, Uint32 height[, Int32 innerBevel = 6][, Int32 outerBevel = 6] )**  
Frame image  

**gamma ( Number gamma )**  
**gamma ( Number gammaRed, Number gammaGreen, Number gammaBlue )**  
Gamma correct image.  

**gaussianBlur ( Number width, Number sigma )**  
**gaussianBlurChannel ( ChannelType channel, Number width,Number sigma )**  
Gaussian blur image. The number of neighbor pixels to be included in the convolution mask is specified by 'width'. The standard deviation of the gaussian bell curve is specified by 'sigma'.  

**implode ( Number factor )**  
Implode image (special effect).  

**haldClut ( Image clutImage )**  
Apply a color lookup table (Hald CLUT) to the image.  

**label ( String label )**  
Label image.  

**level ( Number black_point, Number white_point[, Number mid_point=1.0] )**  
Level image. Adjust the levels of the image by scaling the colors falling between specified white and black points to the full available quantum range. The parameters provided represent the black, mid (gamma), and white points.  The black point specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point (gamma) specifies a gamma correction to apply to the image. White point specifies the lightest color in the image.  Colors brighter than the white point are set to the maximum quantum value. The black and white point have the valid range 0 to MaxRGB while mid (gamma) has a useful range of 0 to ten.  

**levelChannel ( ChannelType channel, Number black_point, Number white_point[, Number mid_point=1.0] )**  
Level image channel. Adjust the levels of the image channel by scaling the values falling between specified white and black points to the full available quantum range. The parameters provided represent the black, mid (gamma), and white points. The black point specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point (gamma) specifies a gamma correction to apply to the image. White point specifies the lightest color in the image. Colors brighter than the white point are set to the maximum quantum value. The black and white point have the valid range 0 to MaxRGB while mid (gamma) has a useful range of 0 to ten.  

**magnify ( )**  
Magnify image by integral size.  

**map ( Image mapImage[, Boolean dither = false] )**  
Remap image colors with closest color from reference image.  

**matteFloodfill ( Color target , Uint32 opacity, Int32 x, Int32 y, PaintMethod method )**  
Floodfill designated area with replacement opacity value.  

**medianFilter ( [Number radius = 0.0] )**  
Filter image by replacing each pixel component with the median color in a circular neighborhood.  

**minify ( )**  
Reduce image by integral size.  

**modulate ( Number brightness, Number saturation, Number hue )**  
Modulate percent hue, saturation, and brightness of an image. Modulation of saturation and brightness is as a ratio of the current value (1.0 for no change). Modulation of hue is an absolute rotation of -180 degrees to +180 degrees from the current position corresponding to an argument range of 0 to 2.0 (1.0 for no change).  

**motionBlur ( Number radius, Number sigma, Number angle )**  
Motion blur image with specified blur factor The radius_ parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma_ parameter specifies the standard deviation of the Laplacian, in pixels. The angle_ parameter specifies the angle the object appears to be comming from (zero degrees is from the right).  

**negate ( [Boolean grayscale = false] )**  
Negate colors in image.  Set grayscale to only negate grayscale values in image.  

**normalize ( )**  
Normalize image (increase contrast by normalizing the pixel values to span the full range of color values).  

**oilPaint ( [Number radius = 3.0] )**  
Oilpaint image (image looks like oil painting).  

**opacity ( Uint32 opacity )**  
Set or attenuate the opacity channel in the image. If the image pixels are opaque then they are set to the specified opacity value, otherwise they are blended with the supplied opacity value.  The value of opacity_ ranges from 0 (completely opaque) to MaxRGB. The defines OpaqueOpacity and TransparentOpacity are available to specify completely opaque or completely transparent, respectively.  

**opaque ( Color opaqueColor, Color penColor )**  
Change color of opaque pixel to specified pen color.  

**TODO** ping ( String imageSpec )  
**TODO** ping ( const Blob &blob )  
Ping is similar to read except only enough of the image is read to determine the image columns, rows, and filesize.  Access the columns(), rows(), and fileSize() attributes after invoking ping.  The image data is not valid after calling ping.  

**quantize ( [Boolean measureError = false] )**  
Quantize image (reduce number of colors).  

**quantumOperator ( ChannelType channel, QuantumOperator operator, double rvalue )**  
**quantumOperator ( Int32 x, Int32 y, Uint32 columns, Uint32 rows, ChannelType channel, QuantumOperator operator, Number rvalue )**  
Apply an arithmetic or bitwise operator to the image pixel quantums.  

**TODO** process ( std::string name, Int32 argc, char **argv )  
Execute a named process module using an argc/argv syntax similar to that accepted by a C 'main' routine. An exception is thrown if the requested process module doesn't exist, fails to load, or fails during execution.  

**raise ( [Geometry geometry = raiseGeometryDefault][, Boolean raisedFlag = false] )**  
Raise image (lighten or darken the edges of an image to give a 3-D raised or lowered effect).  

**randomThreshold( Geometry thresholds )**  
**randomThresholdChannel( Geometry thresholds, ChannelType channel )**  
Changes the value of individual pixels based on the intensity of each pixel compared to a random threshold.  The result is a low-contrast, two color image.  The thresholds argument is a geometry containing LOWxHIGH thresholds.  If the string contains 2x2, 3x3, or 4x4, then an ordered dither of order 2, 3, or 4 will be performed instead.  If a channel argument is specified then only the specified channel is altered.  This is a very fast alternative to 'quantize' based dithering.  

**TODO** read ( String imageSpec )  
Read single image frame into current object.  

**read ( Geometry size, String imageSpec )**  
Read single image frame of specified size into current object.  

**TODO** read ( const Blob &blob )  
Read single image frame from in-memory BLOB.  

**TODO** read ( const Blob &blob, Geometry &size )  
Read single image frame of specified size from in-memory BLOB.  

**TODO** read ( const Blob &blob, Geometry  &size, Uint32 depth )  
Read single image frame of specified size and depth from in-memory BLOB.  

**TODO** read ( const Blob &blob, Geometry  &size, Uint32 depth, String  &magick )  
Read single image frame of specified size, depth, and format from in-memory BLOB.  

**TODO** read ( const Blob &blob, Geometry  &size, String  &magick )  
Read single image frame of specified size, and format from in-memory BLOB.  

**TODO** read ( Uint32 width, Uint32 height, String map, const StorageType  type, const void *pixels )  
Read single image frame from an array of raw pixels, with specified storage type (ConstituteImage), e.g. image.read( 640, 480, "RGB", 0, pixels ).

**reduceNoise ( )**  
**reduceNoise ( Number order )**  
Reduce noise in image using a noise peak elimination filter.  

**roll ( Geometry roll )**  
**roll ( Uint32 columns, Uint32 rows )**  
Roll image (rolls image vertically and horizontally) by specified number of columnms and rows).  

**rotate ( Number degrees )**  
Rotate image counter-clockwise by specified number of degrees.  

**sample ( Geometry geometry )**
Resize image by using pixel sampling algorithm.  

**scale ( Geometry geometry )**  
Resize image by using simple ratio algorithm.  

**segment ( [Number clusterThreshold = 1.0][, Number smoothingThreshold = 1.5] )**  
Segment (coalesce similar image components) by analyzing the histograms of the color components and identifying units that are homogeneous with the fuzzy c-means technique.  Also uses QuantizeColorSpace and Verbose image attributes.  

**shade ( [Number azimuth = 30][, Number elevation = 30][, Boolean colorShading = false] )**  
Shade image using distant light source.  

**sharpen ( [Number radius = 0.0][, Number sigma = 1.0] )**  
**sharpenChannel ( ChannelType channel[, Number radius = 0.0][, Number sigma = 1.0] )**  
Sharpen pixels in image. The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**shave ( Geometry geometry )**  
Shave pixels from image edges.  

**shear ( Number xShearAngle, Number yShearAngle )**  
Shear image (create parallelogram by sliding image by X or Y axis).  

**solarize ( [Number factor = 50.0] )**  
Solarize image (similar to effect seen when exposing a photographic film to light during the development process).

**spread ( [Uint32 amount = 3] )**  
Spread pixels randomly within image by specified ammount.  

**stegano ( Image watermark )**  
Add a digital watermark to the image (based on second image).  

**stereo ( Image rightImage )**  
Create an image which appears in stereo when viewed with red-blue glasses (Red image on left, blue on right).  

**strip ( )**  
Remove all profiles and text attributes from the image.  

**swirl ( Number degrees )**  
Swirl image (image pixels are rotated by degrees).  

**texture ( Image texture )**  
Channel a texture on image background.  

**threshold ( Number threshold )**  
Threshold image channels (below threshold becomes black, above threshold becomes white). The range of the threshold parameter is 0 to MaxRGB.  

**transform ( Geometry imageGeometry[, Geometry cropGeometry] )**  
Transform image based on image and crop geometries.  

**transparent ( Color color )**  
Add matte image to image, setting pixels matching color to transparent.  

**trim ( )**  
Trim edges that are the background color from the image.  

**type ( ImageType type )**  
Image representation type (also see type attribute).  

**unsharpmask ( Number radius, Number sigma, Number amount, Number threshold )**  
**unsharpmaskChannel ( ChannelType channel, Number radius, Number sigma, Number amount, Number threshold )**  
Replace image with a sharpened version of the original image using the unsharp mask algorithm.
* radius - the radius of the Gaussian, in pixels, not counting the center pixel.
* sigma -  the standard deviation of the Gaussian, in pixels.
* amount - the percentage of the difference between the original and the blur image that is added back into the original.
* threshold - the threshold in pixels needed to apply the diffence amount.

**wave ( [Number amplitude = 25.0][, Number wavelength = 150.0] )**  
Map image pixels to a sine wave.  
 
**TODO** write ( String imageSpec )  
Write single image frame to a file.  

**TODO** write ( Blob *blob )  
**TODO** write ( Blob *blob, String magick )  
**TODO** write ( Blob *blob, String magick, Uint32 depth )  
Write single image frame to in-memory BLOB, with optional format and adjoin parameters.  

**TODO**  write ( Int32 x, Int32 y, Uint32 columns, Uint32 rows, String& map, const StorageType type, void *pixels )  
Write single image frame to an array of pixels with storage type specified by user (DispatchImage), e.g. image.write( 0, 0, 640, 1, "RGB", 0, pixels )  

**zoom ( Geometry geometry )**  
Zoom image to specified size.  

###Image Attributes and Options

**adjoin ( Boolean flag )**  
**Boolean adjoin ( )**  
Join images into a single multi-image file.  

**antiAlias( Boolean flag )**  
**Boolean antiAlias( )**  
Anti-alias Postscript and TrueType fonts (default true).  

**animationDelay ( Uint32 delay )**  
**Uint32 animationDelay ( )**  
Time in 1/100ths of a second which must expire before displaying the next image in an animated sequence.  

**animationIterations ( Uint32 iterations )**  
**Uint32 animationIterations ( )**  
Number of iterations to loop an animation (e.g. Netscape loop extension) for.  

**attribute ( String name, String value )**  
**String attribute ( String name )**  
Access/Update a named image attribute.  

**backgroundColor ( Color color )** 
**Color backgroundColor ( )**  
Image background color.  

**backgroundTexture (String backgroundTexture )**  
**String backgroundTexture ( )**  
Name of texture image to tile onto the image background.  

**Uint32 baseColumns ( )**  
Base image width (before transformations).  

**String baseFilename ( )**  
Base image filename (before transformations).  

**Uint32 baseRows ( )**  
Base image height (before transformations).  

**borderColor ( Color color )**  
**Color borderColor ( )**  
Image border color.  

**Geometry boundingBox ( )**  
Return smallest bounding box enclosing non-border pixels. The current fuzz value is used when discriminating between pixels. This is the crop bounding box used by crop(Geometry(0,0));  

**boxColor ( Color boxColor )**  
**Color boxColor ( )**  
Text bounding-box base color (default none).  

**TODO** static void cacheThreshold ( Uint32 threshold )  
Pixel cache threshold in megabytes.  Once this memory threshold is exceeded, all subsequent pixels cache operations are to/from disk.  This setting is shared by all Image objects.  

**chromaBluePrimary ( Number x, Number y )**  
**TODO** chromaBluePrimary ( double *x, double *y )  
Chromaticity blue primary point (e.g. x=0.15, y=0.06).  

**chromaGreenPrimary ( Number x, Number y )**  
**TODO** chromaGreenPrimary ( double *x, double *y )  
Chromaticity green primary point (e.g. x=0.3, y=0.6).  

**chromaRedPrimary ( Number x, Number y )**  
**TODO** chromaRedPrimary ( double *x, double *y )  
Chromaticity red primary point (e.g. x=0.64, y=0.33).  

**chromaWhitePoint ( Number x, Number y )**  
**TODO** chromaWhitePoint ( double *x, double *y )  
Chromaticity white point (e.g. x=0.3127, y=0.329).  

**classType ( ClassType class )**  
**ClassType classType ( )**  
Image class (DirectClass or PseudoClass).  
NOTE: setting a DirectClass image to PseudoClass will result in the loss of color information if the number of colors in the image is greater than the maximum palette size (either 256 or 65536 entries depending on the value of QuantumDepth when ImageMagick was built).  

**clipMask ( Image clipMask )**  
**Image clipMask ( )**  
Associate a clip mask with the image. The clip mask must be the same dimensions as the image. Pass an invalid image to unset an existing clip mask.  

**colorFuzz ( Number fuzz )**  
**Number colorFuzz ( )**  
Colors within this distance are considered equal.  

**colorMap ( Uint32 index, Color color )**  
**Color colorMap ( Uint32 index )**  
Color at colormap position index.  

**colorMapSize ( Uint32 entries )**  
**Uint32 colorMapSize ( )**  
Colormap size (number of colormap entries).  

**colorSpace( ColorspaceType colorSpace )**  
**ColorspaceType  colorSpace ( )**  
Image Color Space.  

**Uint32 columns ( )**
Image width.  

**String comment ( )**  
Image comment.  

**compose ( CompositeOperator compose )**  
**CompositeOperator compose ( )**  
Composition operator to be used when composition is implicitly used (such as for image flattening).  

**compressType ( CompressionType compressType )**  
**CompressionType compressType ( )**  
Compression type.  

**TODO**  debug ( Boolean flag )  
**Boolean debug ( )**  
Enable printing of debug messages from ImageMagick.  

**defineValue ( String magick, String key, String value )**  
**String defineValue ( String magick, String key )**  
Tagged image format define (set/access coder-specific option) The magick option specifies the coder the define applies to.  The key option provides the key specific to that coder.  The value option provides the value to set (if any). See the defineSet() method if the key must be removed entirely.  

**defineSet ( String magick, String key, bool flag )**  
**Boolean defineSet ( String magick, String key )**  
Tagged image format define. Similar to the defineValue() method except that passing the flag value 'true' creates a value-less define with that format and key. Passing the flag value 'false' removes any existing matching definition. The method returns 'true' if a matching key exists, and 'false' if no matching key exists.  

**density ( Geometry geomery )**  
**Geometry density ( )**  
Vertical and horizontal resolution in pixels of the image.  

**depth ( Uint32 depth )**  
**Uint32 depth ( )**  
Image depth (bits allocated to red/green/blue components).  

**String directory ( )**
Tile names from within an image montage.

**endian ( const EndianType endian )**  
**EndianType  endian ( )**  
Endianness (little like Intel or big like SPARC) for image formats which support endian-specific options.  

**fileName ( String fileName )**  
**String fileName ( )**
Image file name.  

**TODO** off_t   fileSize ( )  
Number of bytes of the image on disk.  

**fillColor ( Color fillColor )**  
**Color fillColor ( )**  
Color to use when filling drawn objects.  

**fillRule ( FillRule fillRule )**  
**FillRule fillRule ( )**  
Rule to use when filling drawn objects.  

**fillPattern ( Image fillPattern )**  
**Image fillPattern ( void  )**  
Pattern to use while filling drawn objects.  

**filterType ( FilterTypes filterType )**  
**FilterTypes filterType ( )**  
Filter to use when resizing image.  

**font ( String font )**  
**String font ( )**  
Text rendering font.  

**fontPointsize ( Number pointSize )**  
**Number fontPointsize ( )**  
Font point size.  

**TODO** fontTypeMetrics( String text, TypeMetric *metrics )  
Obtain font metrics for text string given current font, pointsize, and density settings.  

**String format ( )**  
Long image format description.  

**Number gamma ( )**  
Gamma level of the image.  

**Geometry geometry ( )**
Preferred size of the image when encoding.  

**gifDisposeMethod ( Uint32 disposeMethod )**  
**Uint32 gifDisposeMethod ( )**  
GIF disposal method.  

**TODO** iccColorProfile( const Blob &colorProfile )  
**TODO** Blob iccColorProfile( )  
ICC color profile (BLOB).  

**interlaceType ( InterlaceType interlace )**  
**InterlaceType interlaceType ( )**  
Type of interlacing to use.  





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








