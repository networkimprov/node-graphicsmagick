var gm = require('../graphicsmagick.js');
var fs = require('fs');
var path = require('path');
var crypto = require('crypto');

function CreateMD5(buff) {
  var aMD5 = crypto.createHash('md5');
  aMD5.update(buff);
  var aMD5Hex = aMD5.digest('hex');
  console.log(aMD5Hex);
  return aMD5Hex;
}

function NewImageFromFile( img,  file ) {
  return {
    name: img + " = new Image('" + file + "');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects[img] = new gm.Image(aTestsDir + '/' + file); fn(null);
      } else
        new gm.Image(aTestsDir + '/' + file, function(err, image) { objects[img] = image; fn(err); });
    }
  };
}

function CompareImageWithMD5(img,  md5, equals ) {
  return  {
    name: img + '.write(BMP)',
    obj: img,
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && ((typeof(equals) == 'boolean' && !equals) ? CreateMD5(gm.BlobToBuffer(result)) != md5 : CreateMD5(gm.BlobToBuffer(result)) == md5)); }
  };
}

var aTestsDir = path.dirname(module.filename);

exports.name = 'Image Read / Write';
exports.tests = [
  {
    name: 'img = new Image(new Geometry({width: 3, height: 4}), new Color({red: 0.5, green: 0, blue: 0}));',
    fatal: true,
    action: function(objects, sync, fn) { objects.img = new gm.Image(new gm.Geometry({width: 3, height: 4}), new gm.Color({red: 0.5, green: 0, blue: 0})); fn(null) }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && gm.BlobToBuffer(result).toString('base64') == 'Qk1OAAAAAAAAAD4AAAAoAAAAAwAAAAQAAAABAAEAAAAAABAAAABtCwAAbQsAAAIAAAACAAAAAAB/AAAAAAAAAAAAAAAAAAAAAAAAAAAA'); }
  },
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.writeFile()',
    obj: 'img',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/img1.1.bmp' ],
    result: function(err, result, fn) { fn(err == null && fs.readFileSync(aTestsDir + '/files/img1.1.bmp').toString('base64') == fs.readFileSync(aTestsDir + '/files/img1.bmp').toString('base64')); }
  }, {
    name: 'img = new Image(buffer);',
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(new gm.Blob(new Buffer('Qk1OAAAAAAAAAD4AAAAoAAAAAwAAAAQAAAABAAEAAAAAABAAAABtCwAAbQsAAAIAAAACAAAAAAB/AAAAAAAAAAAAAAAAAAAAAAAAAAAA', 'base64'))); fn(null);
      } else
        new gm.Image(new gm.Blob(new Buffer('Qk1OAAAAAAAAAD4AAAAoAAAAAwAAAAQAAAABAAEAAAAAABAAAABtCwAAbQsAAAIAAAACAAAAAAB/AAAAAAAAAAAAAAAAAAAAAAAAAAAA', 'base64')), function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && gm.BlobToBuffer(result).toString('base64') == 'Qk1OAAAAAAAAAD4AAAAoAAAAAwAAAAQAAAABAAEAAAAAABAAAABtCwAAbQsAAAIAAAACAAAAAAB/AAAAAAAAAAAAAAAAAAAAAAAAAAAA'); }
  },
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.adaptiveThreshold()',
    obj: 'img',
    method: 'adaptiveThreshold',
    parameters: [ 2, 2 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'fb943e102d2983dd7feed643e243c44a'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.addNoiseChannel',
    obj: 'img',
    method: 'addNoiseChannel',
    parameters: [ gm.ChannelType.RedChannel, gm.NoiseType.GaussianNoise ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.addNoise',
    obj: 'img',
    method: 'addNoise',
    parameters: [ gm.NoiseType.GaussianNoise ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.annotate(text, location)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', new gm.Geometry({ width: 10, height: 10}) ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.annotate(text, location, gravity)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', new gm.Geometry({ width: 10, height: 10}), gm.GravityType.WestGravity ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.annotate(text, location, gravity, degrees)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', new gm.Geometry({ width: 10, height: 10}), gm.GravityType.WestGravity, 30 ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.annotate(text, gravity)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', gm.GravityType.WestGravity ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.blur()',
    obj: 'img',
    method: 'blur',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '761d370caf17d72cabba75415277e0a9'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.blurChannel(RedChannel)',
    obj: 'img',
    method: 'blurChannel',
    parameters: [ gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'ab3b2165fcccb9e9469368f3ce945313'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.border(BorderGeometryDefault)',
    obj: 'img',
    method: 'border',
    parameters: [ new gm.Geometry(gm.BorderGeometryDefault) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '1f58ee8cfe0dfc6d13a8f2d1ffefa1c9'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.channel(RedChannel)',
    obj: 'img',
    method: 'channel',
    parameters: [ gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'a0a7d142e37e832811a40774894e3abc'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.channelDepth(RedChannel)',
    obj: 'img',
    method: 'channelDepth',
    parameters: [ gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null && result == 8); }
  },
  {
    name: 'img.channelDepth(RedChannel, 4)',
    obj: 'img',
    method: 'channelDepth',
    parameters: [ gm.ChannelType.RedChannel, 1 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'c4aa4c5647a81e5f9565f6baac6d130b'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.charcoal()',
    obj: 'img',
    method: 'charcoal',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '173f650c860a70de422eb21e0fc00d88'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.chop(geometry)',
    obj: 'img',
    method: 'chop',
    parameters: [ new gm.Geometry({ width: 20, height: 20, xOff: 50, yOff: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'a8e778773313ba662befa3b4a81ba45f'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.colorize( red, green, blue, pen)',
    obj: 'img',
    method: 'colorize',
    parameters: [ 50, 40, 80, new gm.Color({red: 0.5, green: 0, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '032fbaaeedc332917eb7a9dc9180b6ab'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.colorize( opacity, pen )',
    obj: 'img',
    method: 'colorize',
    parameters: [ 60, new gm.Color({red: 0.5, green: 0, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '3b94bfc8b228494619cadec070203fca'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.contrast( sharpen )',
    obj: 'img',
    method: 'contrast',
    parameters: [ 10 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '811e207ad4c5a4d33c3dc9c5c7566117'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.crop(geometry)',
    obj: 'img',
    method: 'crop',
    parameters: [ new gm.Geometry({ width: 20, height: 20, xOff: 50, yOff: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '6617958064f7aeb456e44e9ba4fabfbe'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.cycleColormap( amount )',
    obj: 'img',
    method: 'cycleColormap',
    parameters: [ 64 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '4c8cb212849035f33d745e984be6acbd'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.despeckle( )',
    obj: 'img',
    method: 'despeckle',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '143dd3b1098b7d2a16c43e2175d2ae35'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.edge( )',
    obj: 'img',
    method: 'edge',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'e3121de572804f63ac96bf6123d6e3fe'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.emboss( )',
    obj: 'img',
    method: 'emboss',
    parameters: [ 3 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '981eb3df6e3f12e3a071970e83d2560c'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.enhance( )',
    obj: 'img',
    method: 'enhance',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '6d002ee2c0274d464b4cf87c96c6f8cb'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.equalize( )',
    obj: 'img',
    method: 'equalize',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '064aa203c926a970f58ef21a738ec15c'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.erase( )',
    obj: 'img',
    method: 'erase',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '1b6a51e15790142f7af773748e613d35'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.flip( )',
    obj: 'img',
    method: 'flip',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '34de497b14a1d21940dd1f5445fee074'),
  NewImageFromFile('img', 'files/img2.bmp'),
  {
    name: 'img.floodFillColor( x, y, fillColor )',
    obj: 'img',
    method: 'floodFillColor',
    parameters: [ 1, 1, new gm.Color({red: 0, green: 1, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '3d80459a9df1117a7abfec5d7f7931a1'),
  NewImageFromFile('img', 'files/img2.bmp'),
  {
    name: 'img.floodFillColor( geometry, fillColor )',
    obj: 'img',
    method: 'floodFillColor',
    parameters: [ new gm.Geometry({width: 1, height: 1}), new gm.Color({red: 0, green: 1, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '3d80459a9df1117a7abfec5d7f7931a1'),
  NewImageFromFile('img', 'files/img2.bmp'),
  {
    name: 'img.floodFillColor( x, y, fillColor, borderColor )',
    obj: 'img',
    method: 'floodFillColor',
    parameters: [ 1, 1, new gm.Color({red: 0, green: 1, blue: 0}), new gm.Color({red: 0, green: 0, blue: 1}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '3d80459a9df1117a7abfec5d7f7931a1'),
  NewImageFromFile('img', 'files/img2.bmp'),
  {
    name: 'img.floodFillColor( point, fillColor, borderColor )',
    obj: 'img',
    method: 'floodFillColor',
    parameters: [ new gm.Geometry({width: 1, height: 1}), new gm.Color({red: 0, green: 1, blue: 0}), new gm.Color({red: 0, green: 0, blue: 1}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '3d80459a9df1117a7abfec5d7f7931a1'),
  NewImageFromFile('img', 'files/img2.bmp'),
  {
    name: 'img.floodFillOpacity( x, y, opacity, method )',
    obj: 'img',
    method: 'floodFillOpacity',
    parameters: [ 1, 1, 1, gm.PaintMethod.PointMethod ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '21fc45da645a0fc76ef3bee4bf5851a4'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.flop( )',
    obj: 'img',
    method: 'flop',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '824d8e9384ff479ee73b1b753b7dedca'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.gamma( gamma )',
    obj: 'img',
    method: 'gamma',
    parameters: [ 0.5 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '54b66a13822775f2d4561fc23c764227'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.gamma( gammaRed, gammaGreen, gammaBlue )',
    obj: 'img',
    method: 'gamma',
    parameters: [ 0.5, 0.1, 0.7 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '1ee2549b7d6291705dd4b10c935a1c18'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.gaussianBlur( width, sigma )',
    obj: 'img',
    method: 'gaussianBlur',
    parameters: [ 3.5, 2.1 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'd9eb1e5d68825a3fe364a198301a2d28'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.gaussianBlurChannel( channel, width, sigma )',
    obj: 'img',
    method: 'gaussianBlurChannel',
    parameters: [ gm.ChannelType.RedChannel, 3.5, 2.1 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '67c7eb1e9577b7301e928afe69bab75e'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.implode( factor )',
    obj: 'img',
    method: 'implode',
    parameters: [ 3 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '3ac295c2f8252b72fd8e5cc7804ff9bd'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.level( black_point, white_point )',
    obj: 'img',
    method: 'level',
    parameters: [ 0.5, 0.8 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '622790ea64185e7b57a336856fd611ca'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.levelChannel( channel, black_point, white_point )',
    obj: 'img',
    method: 'levelChannel',
    parameters: [ gm.ChannelType.RedChannel, 0.5, 0.8 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '33e97492fb03344cb6d5cdcdd8302793'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.magnify( )',
    obj: 'img',
    method: 'magnify',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'f8e7f2ef0d7d3ed2560b543e9e1c4ebd'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.matteFloodfill( target, opacity, x, y, method )',
    obj: 'img',
    method: 'matteFloodfill',
    parameters: [ new gm.Color({red: 0.5, green: 0, blue: 0}), 80, 10, 10, gm.PaintMethod.PointMethod ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '018a59c1b6e02789afdb9635fdfbbae2'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.medianFilter( radius )',
    obj: 'img',
    method: 'medianFilter',
    parameters: [ 15 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '52e8dea3479b1be278691903f94516c1'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.minify( )',
    obj: 'img',
    method: 'minify',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'caa78e4ba531f8cf448816ff9845ecc8'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.modulate( brightness, saturation, hue )',
    obj: 'img',
    method: 'modulate',
    parameters: [ 55, 75, 90],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '45fbddf06212cade89c53372c65f0db7'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.motionBlur( radius, sigma, angle )',
    obj: 'img',
    method: 'motionBlur',
    parameters: [ 3, 6, 50],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '8aad78c94360f66f19634df4173d9e1b'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.negate( )',
    obj: 'img',
    method: 'negate',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'c0717046d28ff0238c9022da245ffdca'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.normalize( )',
    obj: 'img',
    method: 'normalize',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '605c398dc2c36e1783f0d914932d1b3b'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.oilPaint( )',
    obj: 'img',
    method: 'oilPaint',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '8b26949ffb8c6708c706a943ff882555'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.opacity( opacity )',
    obj: 'img',
    method: 'opacity',
    parameters: [ Math.round((gm.TransparentOpacity + gm.OpaqueOpacity) / 2) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'bff76eedfe61f59be57c56bf9f9af284'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.opaque( opopaqueColor, penColor )',
    obj: 'img',
    method: 'opaque',
    parameters: [ new gm.Color({red: 0.5, green: 0, blue: 0}), new gm.Color({red: 0, green: 0, blue: 1}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false), //TODO: fix test
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.quantize( )',
    obj: 'img',
    method: 'quantize',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '183085f7701f1cb456705a6a5a5c0e7d'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.raise( )',
    obj: 'img',
    method: 'raise',
    parameters: [ true ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'b6612d195caa071ecc33681aa5be0b1a'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.randomThreshold( thresholds )',
    obj: 'img',
    method: 'randomThreshold',
    parameters: [ new gm.Geometry({width: 2, height: 2}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'b0753b8ba98b94da6a36f4b00a2663e2'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.randomThresholdChannel( thresholds, channel )',
    obj: 'img',
    method: 'randomThresholdChannel',
    parameters: [ new gm.Geometry({width: 2, height: 2}), gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'ee12adb03278679d86b498d28148152a'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.reduceNoise( order )',
    obj: 'img',
    method: 'reduceNoise',
    parameters: [ 5 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '112aa525a6d44f3646833094314cc277'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.roll( roll )',
    obj: 'img',
    method: 'roll',
    parameters: [ new gm.Geometry({xOff: 50, yOff: 80}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '507a2a830e58930d4912e1758baca023'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.roll( columns, rows )',
    obj: 'img',
    method: 'roll',
    parameters: [ 50, 80 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '507a2a830e58930d4912e1758baca023'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.rotate( degrees )',
    obj: 'img',
    method: 'rotate',
    parameters: [ 53.2 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'b34b44f24f6af0c012eff328f5eac202'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.sample( geometry )',
    obj: 'img',
    method: 'sample',
    parameters: [ new gm.Geometry({width: 80}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '2e5e4081f44f6c074bc7334833779a71'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.scale( geometry )',
    obj: 'img',
    method: 'scale',
    parameters: [ new gm.Geometry({width: 80}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '91aac0fcf3226fea07f2097c358f3906'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.segment( )',
    obj: 'img',
    method: 'segment',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '44146106fb54225259d46a091bf728ee'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.shade( )',
    obj: 'img',
    method: 'shade',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '93d1f5fd71614d030e49512427c1606b'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.sharpen( )',
    obj: 'img',
    method: 'sharpen',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'a7c901252ac7628bb8d3062f6abfbfde'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.sharpenChannel( channel )',
    obj: 'img',
    method: 'sharpenChannel',
    parameters: [ gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '95f9d70a0747df09d821cd842888b362'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.shave( geometry )',
    obj: 'img',
    method: 'shave',
    parameters: [ new gm.Geometry({width: 80, height: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cf34dfd45f5e33c0e0705866a17cb7ab'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.shear( xShearAngle, yShearAngle )',
    obj: 'img',
    method: 'shear',
    parameters: [ 45, 90 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '9864b827808ee4d7f92fa48e77fbb831'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.solarize( )',
    obj: 'img',
    method: 'solarize',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'f05ef17673bce27b33a59cfcd983fe54'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.spread( )',
    obj: 'img',
    method: 'spread',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.strip( )',
    obj: 'img',
    method: 'strip',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false), //TODO: fix test
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.swirl( degrees )',
    obj: 'img',
    method: 'swirl',
    parameters: [ 45 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.threshold( degrees )',
    obj: 'img',
    method: 'threshold',
    parameters: [ 128 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'caf97821adbd3eb860fbfdcb5f6aeec9'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.transform( imageGeometry )',
    obj: 'img',
    method: 'transform',
    parameters: [ new gm.Geometry({width: 80, height: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'e2021c4609297ee2218e3064f171a316'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.transparent( color )',
    obj: 'img',
    method: 'transparent',
    parameters: [ new gm.Color({red: 1, green: 0, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '4d915e9064483e273b44793ca43d8ae4'), //TODO: check test
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.trim( )',
    obj: 'img',
    method: 'trim',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'cae23729a69e667f5bd6b33e34cdf3a5', false), //TODO: fix test
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.unsharpmask( radius, sigma, amount, threshold )',
    obj: 'img',
    method: 'unsharpmask',
    parameters: [ 2, 3, 30, 0.1 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '7d3d1df789a1e49527a6f0f7619b7440'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.unsharpmaskChannel( channel, radius, sigma, amount, threshold )',
    obj: 'img',
    method: 'unsharpmaskChannel',
    parameters: [ gm.ChannelType.RedChannel, 2, 3, 30, 0.1 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '32bd36f6abf19bf01d47c51dd205ec70'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.wave( )',
    obj: 'img',
    method: 'wave',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', '8eda00c3a4bdf89e1afb5cdf4d29c408'),
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.zoom( imageGeometry )',
    obj: 'img',
    method: 'zoom',
    parameters: [ new gm.Geometry({width: 80, height: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  CompareImageWithMD5('img', 'e2021c4609297ee2218e3064f171a316'),
  {
    name: 'img.writeFile()',
    obj: 'img',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/temp.bmp' ],
    result: function(err, result, fn) { fn(err == null); }
  }
]
