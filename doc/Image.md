#Image
Image is the representation of an image.  
Unless otherwise specified, all the methods return the Image object for chaining.  

###Constructors

**Image( )**  
Default constructor  

**Image( Geometry size, Color color )**  
Construct a blank image canvas of specified size and color  

**Image( String imageSpec[, Function callback] )**   
Construct from image file or image specification. If the functions is supplied the creation of the object is done asynchronously.  
 
**Image ( Blob blob[, Function callback] )**  
Construct Image from in-memory Buffer.  

**Image ( Blob blob, Geometry size[, Function callback] )**  
Construct Image of specified size from in-memory Buffer.  

**Image ( Blob blob, Geometry size, Uint32 depth[, Function callback] )**  
Construct Image of specified size and depth from in-memory Buffer.  

**Image ( Blob blob, Geometry size, Uint32 depth, String magick[, Function callback] )**  
Construct Image of specified size, depth, and format from in-memory Buffer.  

**Image ( Blob blob, Geometry size, String magick[, Function callback] )**  
Construct Image of specified size, and format from in-memory Buffer.  

**TODO** Image ( Uint32 width, Uint32 height, String map, const StorageType type, const void *pixels )  
Construct an image based on an array of raw pixels, of specified type and mapping, in memory  

###Image operations

Unless otherwise specified, all the methods in image operations have an sync variant, [method]Async, which throw the error and return the second function parameter, if available, or the Image object, for chaining.  
**TODO** add examples.  

**adaptiveThreshold ( Uint32 width, Uint32 height[, Uint32 offset = 0], Function callback)**  
Local adaptive threshold image http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm  
width x height define the size of the pixel neighborhood  
offset - constant to subtract from pixel neighborhood mean  

**addNoiseChannel ( ChannelType channel, NoiseType noiseType, Function callback)**  
**addNoise ( NoiseType, Function callback)**  
Add noise to image with specified noise type  

**TODO** affineTransform ( const DrawableAffine &affine )  
Transform image by specified affine (or free transform) matrix.  

**annotate ( String text, Geometry location, Function callback)**  
Annotate using specified text, and placement location 

**annotate ( String text, Geometry location, GravityType gravity, Function callback)**  
Annotate using specified text, bounding area, and placement gravity  

**annotate ( String text, Geometry location, GravityType gravity, Number degrees, Function callback)**  
Annotate with text using specified text, bounding area, placement gravity, and rotation.  

**annotate ( String text, GravityType gravity, Function callback)**  
Annotate with text (bounding area is entire image) and placement gravity.  

**blur ( [Number radius = 0.0][, Number sigma = 1.0], Function callback)**  
**blurChannel ( ChannelType channel[, Number radius = 0.0][, Number sigma = 1.0], Function callback)**  
Blur image with specified blur factor.  
The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  
The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**border ( Geometry geometry, Function callback)**  
Border image (add border to image).  

**cdl ( String cdl, Function callback)**  
Bake in the ASC-CDL, which is a convention for the for the exchange of basic primary color grading information between for the exchange of basic primary color grading information between equipment and software from different manufacturers.  It is a useful transform for other purposes as well.  

**channel ( ChannelType channel, Function callback)**  
Extract channel from image  

**channelDepth ( ChannelType channel, Uint32 depth, Function callback)**  
Set modulus channel depth.  

**channelDepth ( ChannelType channel, Function callback)**  
Returns modulus channel depth.  

**charcoal ( [Number radius = 0.0][, Number sigma = 1.0], Function callback)**  
Charcoal effect image (looks like charcoal sketch). The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**chop ( Geometry geometry, Function callback)**  
Chop image (remove vertical or horizontal subregion of image).  

**colorize ( Uint32 opacityRed, Uint32 opacityGreen, Uint32 opacityBlue, Color penColor, Function callback)**  
Colorize image with pen color, using specified percent opacity for red, green, and blue quantums.  

**colorize ( Uint32 opacity, Color penColor, Function callback)**  
Colorize image with pen color, using specified percent opacity.  

**TODO** colorMatrix (NumberArrayOfArray color_matrix, Function callback)  
Apply a color matrix to the image channels.  The user supplied matrix may be of order 1 to 5 (1x1 through 5x5).  
For example: colorMatrix( [ [ 1, 1], [ 1, 1] ])  

**comment ( String comment, Function callback)**  
Comment image (add comment string to image).  

**compare ( Image img, Function callback)**  
Compare current image with another image. Sets meanErrorPerPixel, normalizedMaxError, and normalizedMeanError in the current image.  
Returns wether the images are identical.  

**composite ( Image compositeImage, Uint32 xOffset, Uint32 yOffset[, CompositeOperator compose = InCompositeOp], Function callback)**  
**compositeGeometry ( Image compositeImage, Geometry offset[, CompositeOperator compose = InCompositeOp], Function callback)**  
**compositeGravity ( Image compositeImage, GravityType gravity[, CompositeOperator compose = InCompositeOp], Function callback)**  
Compose an image onto another at specified offset and using specified algorithm.  

**contrast ( Uint32 sharpen, Function callback)**  
Contrast image (enhance intensity differences in image).  

**convolve ( NumberArrayOfArray kernel, Function callback)**  
Convolve image.  Applies a user-specified convolution to the image.  
For example: convolve( [ [ 1, 1], [ 1, 1] ])  

**crop ( Geometry geometry, Function callback)**  
Crop image (subregion of original image).  

**cycleColormap ( Uint32 amount, Function callback)**  
Cycle image colormap.  

**despeckle ( Function callback)**  
Despeckle image (reduce speckle noise).  
 
**TODO** void display ( )  
Display image on screen.  

**TODO** void draw ( const Drawable &drawable )  
Draw on image using a single drawable.  
 
**TODO** void draw ( const std::list<Magick::Drawable> &drawable )  
Draw on image using a drawable list.  

**edge ( [Number radius = 0.0], Function callback)**  
Edge image (hilight edges in image).  

**emboss ( [Number radius = 0.0][, Number sigma = 1.0])**  
Emboss image (hilight edges with 3D effect). The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**enhance ( Function callback)**  
Enhance image (minimize noise).  

**equalize ( Function callback)**  
Equalize image (histogram equalization).  

**erase ( Function callback)**  
Erase image to current "background color".  

**flip ( Function callback)**  
Flip image (reflect each scanline in the vertical direction).  

**floodFillColor( Uint32 x, Uint32 y, Color fillColor, Function callback)**  
**floodFillColor( Geometry point, Color fillColor, Function callback)**  
Flood-fill color across pixels that match the color of the target pixel and are neighbors of the target pixel. Uses current fuzz setting when determining color match.  

**floodFillColor( Uint32 x, Uint32 y, Color fillColor, Color borderColor, Function callback)**  
**floodFillColor( Geometry point, Color fillColor, Color borderColor, Function callback)**  
Flood-fill color across pixels starting at target-pixel and stopping at pixels matching specified border color. Uses current fuzz setting when determining color match.  

**floodFillOpacity ( Uint32 x, Uint32 y, Uint32 opacity, PaintMethod method, Function callback)**  
Floodfill pixels matching color (within fuzz factor) of target pixel(x,y) with replacement opacity value using method.  

**floodFillTexture( Uint32 x, Uint32 y, Image texture, Function callback)**  
**floodFillTexture( Geometry point, Image texture, Function callback)**  
Flood-fill texture across pixels that match the color of the target pixel and are neighbors of the target pixel. Uses current fuzz setting when determining color match.  

**floodFillTexture( Uint32 x, Uint32 y, Image texture, Color borderColor, Function callback)**  
**floodFillTexture( Geometry point, Image texture, Color borderColor, Function callback)**  
Flood-fill texture across pixels starting at target-pixel and stopping at pixels matching specified border color. Uses current fuzz setting when determining color match.  

**flop ( Function callback)**  
Flop image (reflect each scanline in the horizontal direction).  

**frame ( [Geometry geometry = frameGeometryDefault], Function callback)**  
**frame ( Uint32 width, Uint32 height[, Int32 innerBevel = 6][, Int32 outerBevel = 6], Function callback)**  
Frame image  

**gamma ( Number gamma, Function callback)**  
**gamma ( Number gammaRed, Number gammaGreen, Number gammaBlue, Function callback)**  
Gamma correct image.  

**gaussianBlur ( Number width, Number sigma, Function callback)**  
**gaussianBlurChannel ( ChannelType channel, Number width,Number sigma, Function callback)**  
Gaussian blur image. The number of neighbor pixels to be included in the convolution mask is specified by 'width'. The standard deviation of the gaussian bell curve is specified by 'sigma'.  

**haldClut ( Image clutImage, Function callback)**  
Apply a color lookup table (Hald CLUT) to the image.  

**implode ( Number factor, Function callback)**  
Implode image (special effect).  

**label ( String label, Function callback)**  
Label image.  

**level ( Number black_point, Number white_point[, Number mid_point=1.0], Function callback)**  
Level image. Adjust the levels of the image by scaling the colors falling between specified white and black points to the full available quantum range. The parameters provided represent the black, mid (gamma), and white points.  The black point specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point (gamma) specifies a gamma correction to apply to the image. White point specifies the lightest color in the image.  Colors brighter than the white point are set to the maximum quantum value. The black and white point have the valid range 0 to MaxRGB while mid (gamma) has a useful range of 0 to ten.  

**levelChannel ( ChannelType channel, Number black_point, Number white_point[, Number mid_point=1.0], Function callback)**  
Level image channel. Adjust the levels of the image channel by scaling the values falling between specified white and black points to the full available quantum range. The parameters provided represent the black, mid (gamma), and white points. The black point specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point (gamma) specifies a gamma correction to apply to the image. White point specifies the lightest color in the image. Colors brighter than the white point are set to the maximum quantum value. The black and white point have the valid range 0 to MaxRGB while mid (gamma) has a useful range of 0 to ten.  

**magnify ( Function callback)**  
Magnify image by integral size.  

**map ( Image mapImage[, Boolean dither = false], Function callback)**  
Remap image colors with closest color from reference image.  

**matteFloodfill ( Color target , Uint32 opacity, Int32 x, Int32 y, PaintMethod method, Function callback)**  
Floodfill designated area with replacement opacity value.  

**medianFilter ( [Number radius = 0.0], Function callback)**  
Filter image by replacing each pixel component with the median color in a circular neighborhood.  

**minify ( Function callback)**  
Reduce image by integral size.  

**modulate ( Number brightness, Number saturation, Number hue, Function callback)**  
Modulate percent hue, saturation, and brightness of an image. Modulation of saturation and brightness is as a ratio of the current value (1.0 for no change). Modulation of hue is an absolute rotation of -180 degrees to +180 degrees from the current position corresponding to an argument range of 0 to 2.0 (1.0 for no change).  

**motionBlur ( Number radius, Number sigma, Number angle, Function callback)**  
Motion blur image with specified blur factor The radius_ parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma_ parameter specifies the standard deviation of the Laplacian, in pixels. The angle_ parameter specifies the angle the object appears to be comming from (zero degrees is from the right).  

**negate ( [Boolean grayscale = false], Function callback)**  
Negate colors in image.  Set grayscale to only negate grayscale values in image.  

**normalize ( Function callback)**  
Normalize image (increase contrast by normalizing the pixel values to span the full range of color values).  

**oilPaint ( [Number radius = 3.0], Function callback)**  
Oilpaint image (image looks like oil painting).  

**opacity ( Uint32 opacity, Function callback)**  
Set or attenuate the opacity channel in the image. If the image pixels are opaque then they are set to the specified opacity value, otherwise they are blended with the supplied opacity value.  The value of opacity_ ranges from 0 (completely opaque) to MaxRGB. The constants OpaqueOpacity and TransparentOpacity are available to specify completely opaque or completely transparent, respectively.  

**opaque ( Color opaqueColor, Color penColor, Function callback)**  
Change color of opaque pixel to specified pen color.  

**ping ( String imageSpec, Function callback )**  
**ping ( Blob blob, Function callback )**  
Ping is similar to read except only enough of the image is read to determine the image columns, rows, and filesize.  Access the columns(), rows(), and fileSize() attributes after invoking ping.  The image data is not valid after calling ping.  

**quantize ( [Boolean measureError = false], Function callback)**  
Quantize image (reduce number of colors).  

**quantumOperator ( ChannelType channel, QuantumOperator operator, double rvalue, Function callback)**  
**quantumOperator ( Int32 x, Int32 y, Uint32 columns, Uint32 rows, ChannelType channel, QuantumOperator operator, Number rvalue, Function callback)**  
Apply an arithmetic or bitwise operator to the image pixel quantums.  

**TODO** process ( std::string name, Int32 argc, char **argv )  
Execute a named process module using an argc/argv syntax similar to that accepted by a C 'main' routine. An exception is thrown if the requested process module doesn't exist, fails to load, or fails during execution.  

**raise ( [Geometry geometry = raiseGeometryDefault][, Boolean raisedFlag = false], Function callback)**  
Raise image (lighten or darken the edges of an image to give a 3-D raised or lowered effect).  

**randomThreshold( Geometry thresholds, Function callback)**  
**randomThresholdChannel( Geometry thresholds, ChannelType channel, Function callback)**  
Changes the value of individual pixels based on the intensity of each pixel compared to a random threshold.  The result is a low-contrast, two color image.  The thresholds argument is a geometry containing LOWxHIGH thresholds.  If the string contains 2x2, 3x3, or 4x4, then an ordered dither of order 2, 3, or 4 will be performed instead.  If a channel argument is specified then only the specified channel is altered.  This is a very fast alternative to 'quantize' based dithering.  

**read ( String imageSpec, Function callback )**  
Read single image frame into current object.  

**read ( Geometry size, String imageSpec, Function callback)**  
Read single image frame of specified size into current object.  

**read ( Blob blob, Function callback )**  
Read single image frame from in-memory Buffer.  

**read ( Blob blob, Geometry &size, Function callback )**  
Read single image frame of specified size from in-memory Buffer.  

**read ( Blob blob, Geometry  &size, Uint32 depth, Function callback )**  
Read single image frame of specified size and depth from in-memory Buffer.  

**read ( Blob blob, Geometry  &size, Uint32 depth, String magick, Function callback )**  
Read single image frame of specified size, depth, and format from in-memory Buffer.  

**read ( Blob blob, Geometry  &size, String magick, Function callback )**  
Read single image frame of specified size, and format from in-memory Buffer.  

**TODO** read ( Uint32 width, Uint32 height, String map, const StorageType  type, const void *pixels )  
Read single image frame from an array of raw pixels, with specified storage type (ConstituteImage), e.g. image.read( 640, 480, "RGB", 0, pixels ).

**reduceNoise ( Function callback)**  
**reduceNoise ( Number order, Function callback)**  
Reduce noise in image using a noise peak elimination filter.  

**roll ( Geometry roll, Function callback)**  
**roll ( Uint32 columns, Uint32 rows, Function callback)**  
Roll image (rolls image vertically and horizontally) by specified number of columnms and rows).  

**rotate ( Number degrees, Function callback)**  
Rotate image counter-clockwise by specified number of degrees.  

**sample ( Geometry geometry, Function callback)**
Resize image by using pixel sampling algorithm.  

**scale ( Geometry geometry, Function callback)**  
Resize image by using simple ratio algorithm.  

**segment ( [Number clusterThreshold = 1.0][, Number smoothingThreshold = 1.5], Function callback)**  
Segment (coalesce similar image components) by analyzing the histograms of the color components and identifying units that are homogeneous with the fuzzy c-means technique.  Also uses QuantizeColorSpace and Verbose image attributes.  

**shade ( [Number azimuth = 30][, Number elevation = 30][, Boolean colorShading = false], Function callback)**  
Shade image using distant light source.  

**sharpen ( [Number radius = 0.0][, Number sigma = 1.0], Function callback)**  
**sharpenChannel ( ChannelType channel[, Number radius = 0.0][, Number sigma = 1.0], Function callback)**  
Sharpen pixels in image. The radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.  The sigma parameter specifies the standard deviation of the Laplacian, in pixels.  

**shave ( Geometry geometry, Function callback)**  
Shave pixels from image edges.  

**shear ( Number xShearAngle, Number yShearAngle, Function callback)**  
Shear image (create parallelogram by sliding image by X or Y axis).  

**solarize ( [Number factor = 50.0], Function callback)**  
Solarize image (similar to effect seen when exposing a photographic film to light during the development process).

**spread ( [Uint32 amount = 3], Function callback)**  
Spread pixels randomly within image by specified ammount.  

**stegano ( Image watermark, Function callback)**  
Add a digital watermark to the image (based on second image).  

**stereo ( Image rightImage, Function callback)**  
Create an image which appears in stereo when viewed with red-blue glasses (Red image on left, blue on right).  

**strip ( Function callback)**  
Remove all profiles and text attributes from the image.  

**swirl ( Number degrees, Function callback)**  
Swirl image (image pixels are rotated by degrees).  

**texture ( Image texture, Function callback)**  
Channel a texture on image background.  

**threshold ( Number threshold, Function callback)**  
Threshold image channels (below threshold becomes black, above threshold becomes white). The range of the threshold parameter is 0 to MaxRGB.  

**transform ( Geometry imageGeometry[, Geometry cropGeometry], Function callback)**  
Transform image based on image and crop geometries.  

**transparent ( Color color, Function callback)**  
Add matte image to image, setting pixels matching color to transparent.  

**trim ( Function callback)**  
Trim edges that are the background color from the image.  

**type ( ImageType type, Function callback)**  
Image representation type (also see type attribute).  

**unsharpmask ( Number radius, Number sigma, Number amount, Number threshold, Function callback)**  
**unsharpmaskChannel ( ChannelType channel, Number radius, Number sigma, Number amount, Number threshold, Function callback)**  
Replace image with a sharpened version of the original image using the unsharp mask algorithm.
* radius - the radius of the Gaussian, in pixels, not counting the center pixel.
* sigma -  the standard deviation of the Gaussian, in pixels.
* amount - the percentage of the difference between the original and the blur image that is added back into the original.
* threshold - the threshold in pixels needed to apply the diffence amount.

**wave ( [Number amplitude = 25.0][, Number wavelength = 150.0], Function callback)**  
Map image pixels to a sine wave.  
 
**writeFile ( String imageSpec, Function callback )**  
Write single image frame to a file.  

**write ( Function callback )**  
**write ( String magick, Function callback )**  
**write ( String magick, Uint32 depth, Function callback )**  
Write single image frame to in-memory Buffer, with optional format and adjoin parameters.  
The callback function is called with error and the Buffer as parameters.  
The sync method returns the Buffer.  

**TODO**  write ( Int32 x, Int32 y, Uint32 columns, Uint32 rows, String& map, const StorageType type, void *pixels )  
Write single image frame to an array of pixels with storage type specified by user (DispatchImage), e.g. image.write( 0, 0, 640, 1, "RGB", 0, pixels )  

**zoom ( Geometry geometry, Function callback)**  
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
**Image fillPattern ( )**  
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

**iccColorProfile( Buffer colorProfile )**  
**Buffer iccColorProfile( )**  
ICC color profile (Buffer).  

**interlaceType ( InterlaceType interlace )**  
**InterlaceType interlaceType ( )**  
Type of interlacing to use.  

**iptcProfile( Buffer iptcProfile )**  
**Buffer iptcProfile( )**  
IPTC profile (Buffer).  

**isValid ( Boolean isValid )**  
**Boolean isValid ( )**  
Does object contain valid image?  

**String label ( )**  
Image label.  

**magick ( String magick )**  
**String magick ( )**  
File type magick identifier (.e.g "GIF").  

**matte ( Boolean matteFlag )**  
**Boolean matte ( )**  
Image supports transparency (matte channel).  

**matteColor ( Color matteColor )**  
**Color matteColor ( )**  
Transparent color.  

**Number meanErrorPerPixel ( )**  
The mean error per pixel computed when an image is color reduced.  

**modulusDepth ( Uint32 modulusDepth )**  
**Uint32 modulusDepth ( )**  
Image modulus depth (minimum number of bits required to support red/green/blue components without loss of accuracy).  

**Geometry montageGeometry ( )**  
Tile size and offset within an image montage.  

**monochrome ( Boolean monochromeFlag )**  
**Boolean monochrome ( )**  
Transform image to black and white.  

**Number normalizedMaxError ( )**  
The normalized max error per pixel computed when an image is color reduced.  

**Number normalizedMeanError ( )**  
The normalized mean error per pixel computed when an image is color reduced.  

**orientation ( OrientationType orientation )**  
**OrientationType orientation ( )**  
Image orientation.  

**page ( Geometry pageSize )**  
**Geometry page ( )**  
Preferred size and location of an image canvas.  

**penColor ( Color penColor )**  
**Color penColor ( )**  
Pen color (deprecated, don't use any more).  

**penTexture ( Image penTexture )**  
**Image penTexture ( )**  
Pen texture image (deprecated, don't use any more).  

**pixelColor ( Uint32 x, Uint32 y, Color color )**  
**Color pixelColor ( Uint32 x, Uint32 y )**  
Get/set pixel color at location x & y.  

**profile( String  name,  Buffer colorProfile )**  
Add or remove a named profile to/from the image. Remove the profile by passing an empty Blob (e.g. Blob()) **TODO**. Valid names are "*", "8BIM", "ICM", "IPTC", or a user/format-defined profile name.  

**Buffer profile( String  name )**  
Retrieve a named profile from the image. Valid names are: "8BIM", "8BIMTEXT", "APP1", "APP1JPEG", "ICC", "ICM", & "IPTC" or an existing user/format-defined profile name.  

**quality ( Uint32 quality )**  
**Uint32 quality ( )**  
JPEG/MIFF/PNG compression level (default 75).  

**quantizeColors ( Uint32 colors )**  
**Uint32 quantizeColors ( )**  
Maximum number of colors to quantize to.

**quantizeColorSpace ( ColorspaceType colorSpace )**  
**ColorspaceType  quantizeColorSpace ( )**  
Colorspace to quantize in.  

**quantizeDither ( Boolean ditherFlag )**  
**Boolean quantizeDither ( )**  
Dither image during quantization (default true).  

**quantizeTreeDepth ( Uint32 treeDepth )**  
**Uint32 quantizeTreeDepth ( )**  
Quantization tree-depth.  

**renderingIntent ( RenderingIntent renderingIntent )**  
**RenderingIntent renderingIntent ( )**  
The type of rendering intent.  

**resolutionUnits ( ResolutionType resolutionUnits )**  
**ResolutionType  resolutionUnits ( )**  
Units of image resolution.  

**Uint32 rows ( )**  
The number of pixel rows in the image.  

**scene ( Uint32 scene )**  
**Uint32 scene ( )**  
Image scene number.  

**String signature ( [Boolean force = false] )**  
Image signature.  Set force to true in order to re-calculate the signature regardless of whether the image data has been modified.  

**size ( Geometry geometry )**  
**Geometry size ( )**  
Width and height of a raw image.  

**TODO**  statistics ( ImageStatistics *statistics )  
Obtain image statistics. Statistics are normalized to the range of 0.0 to 1.0 and are output to the specified ImageStatistics structure.  

**strokeAntiAlias( Boolean flag )**  
**Boolean strokeAntiAlias( )**  
enabled/disable stroke anti-aliasing.  

**strokeColor ( Color strokeColor )**  
**Color strokeColor ( )**  
Color to use when drawing object outlines.  

**strokeDashArray ( NumberArray strokeDashArray )**  
**NumberArray strokeDashArray ( )**  
Specify the pattern of dashes and gaps used to stroke paths. The strokeDashArray represents an array of numbers that specify the lengths of alternating dashes and gaps in pixels. If an odd number of values is provided, then the list of values is repeated to yield an even number of values.  

**strokeDashOffset ( Number strokeDashOffset )**  
**Number strokeDashOffset ( )**  
While drawing using a dash pattern, specify distance into the dash pattern to start the dash (default 0).  

**strokeLineCap ( LineCap lineCap )**  
**LineCap strokeLineCap ( )**  
Specify the shape to be used at the end of open subpaths when they are stroked. Values of LineCap are UndefinedCap, ButtCap, RoundCap, and SquareCap.  

**strokeLineJoin ( LineJoin lineJoin )**  
**LineJoin strokeLineJoin ( )**  
Specify the shape to be used at the corners of paths (or other vector shapes) when they are stroked. Values of LineJoin are UndefinedJoin, MiterJoin, RoundJoin, and BevelJoin.  

**strokeMiterLimit ( Uint32 miterLimit )**  
**Uint32 strokeMiterLimit ( )**  
Specify miter limit. When two line segments meet at a sharp angle and miter joins have been specified for 'lineJoin', it is possible for the miter to extend far beyond the thickness of the line stroking the path. The miterLimit' imposes a limit on the ratio of the miter length to the 'lineWidth'. The default value of this parameter is 4.  

**strokePattern ( Image strokePattern )**  
**Image strokePattern ( )**  
Pattern image to use while stroking object outlines.  

**strokeWidth ( Number strokeWidth )**  
**Number strokeWidth ( )**  
Stroke width for drawing vector objects (default one).  

**subImage ( Uint32 subImage )**  
**Uint32 subImage ( )**  
Subimage of an image sequence.  

**subRange ( Uint32 subRange )**  
**Uint32 subRange ( )**  
Number of images relative to the base image.  

**textEncoding ( String encoding )**  
**String textEncoding ( )**  
**TODO** may alwais be utf8? Annotation text encoding (e.g. "UTF-16")  

**tileName ( String tileName )**  
**String tileName ( )**  
Tile name.  

**Number totalColors ( )**  
Number of colors in the image.  

**transformOrigin ( Number x, Number y )**  
Origin of coordinate system to use when annotating with text or drawing.  

**transformRotation ( Number angle )**  
Rotation to use when annotating with text or drawing.  

**transformReset ( )**  
Reset transformation parameters to default.  

**transformScale ( Number sx_, Number sy )**  
Scale to use when annotating with text or drawing.  

**transformSkewX ( Number skewx )**  
Skew to use in X axis when annotating with text or drawing.  

**transformSkewY ( Number skewy )**  
Skew to use in Y axis when annotating with text or drawing.  

**ImageType type ( )**  
Image representation type.  

**verbose ( Boolean verboseFlag )**  
**Boolean verbose ( )**  
**TODO**  Print detailed information about the image.  

**view ( String view )**  
**String view ( )**  
FlashPix viewing parameters.  

**x11Display ( String display )**  
**String x11Display ( )**  
X11 display to display to, obtain fonts from, or to capture image from.  

**Number xResolution ( )**  
x resolution of the image.  

**Number yResolution ( )**  
y resolution of the image.  

###Low-level Pixel Access Routines

**TODO**
