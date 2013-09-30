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
  {
    name: 'img.writeFile()',
    obj: 'img',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/temp.bmp' ],
    result: function(err, result, fn) { fn(err == null); }
  }
]
