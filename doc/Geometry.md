#Geometry
Object which provides convenient means to specify a geometry information. Similar to [this](http://www.graphicsmagick.org/Magick++/Geometry.html).  
  
**Geometry( geometryInfo )**  
geometryInfo is a JSON which contains:
* width - Width, Uint32 value.
* height - Height, Uint32 value.
* xOff - X offset from origin, Uint32 value, default 0.
* yOff - Y offset from origin, Uint32 value, default 0.
* xNegative  - Sign of X offset negative? (X origin at right), Boolean value, default false.
* yNegative  - Sign of Y offset negative? (Y origin at bottom), Boolean value, default false.
* percent - Width and height are expressed as percentages, Boolean value, optional.
* aspect - Resize without preserving aspect ratio, Boolean value, optional.
* greater - Resize if image is greater than size (>), Boolean value, optional.
* less - Resize if image is less than size (<), Boolean value, optional.

**GeometryToString(Geometry obj)**  
Returns a geometry string encoding.

**StringToGeometry(String str)**  
Returns a Geometry object from a geometry string.
