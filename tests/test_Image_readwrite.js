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
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
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
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.adaptiveThreshold()',
    obj: 'img',
    method: 'adaptiveThreshold',
    parameters: [ 2, 2 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == 'fb943e102d2983dd7feed643e243c44a'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.addNoiseChannel',
    obj: 'img',
    method: 'addNoiseChannel',
    parameters: [ gm.ChannelType.RedChannel, gm.NoiseType.GaussianNoise ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) != 'fb943e102d2983dd7feed643e243c44a'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.addNoise',
    obj: 'img',
    method: 'addNoise',
    parameters: [ gm.NoiseType.GaussianNoise ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) != 'fb943e102d2983dd7feed643e243c44a'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.annotate(text, location)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', new gm.Geometry({ width: 10, height: 10}) ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) != 'cae23729a69e667f5bd6b33e34cdf3a5'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.annotate(text, location, gravity)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', new gm.Geometry({ width: 10, height: 10}), gm.GravityType.WestGravity ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) != 'cae23729a69e667f5bd6b33e34cdf3a5'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.annotate(text, location, gravity, degrees)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', new gm.Geometry({ width: 10, height: 10}), gm.GravityType.WestGravity, 30 ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) != 'cae23729a69e667f5bd6b33e34cdf3a5'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.annotate(text, gravity)',
    obj: 'img',
    method: 'annotate',
    parameters: [ 'text', gm.GravityType.WestGravity ],
    result: function(err, result, fn) { if (err != null && err.search('library is not available') != -1) console.log(err); fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) != 'cae23729a69e667f5bd6b33e34cdf3a5'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.blur()',
    obj: 'img',
    method: 'blur',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '761d370caf17d72cabba75415277e0a9'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.blurChannel(RedChannel)',
    obj: 'img',
    method: 'blurChannel',
    parameters: [ gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == 'ab3b2165fcccb9e9469368f3ce945313'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.border(BorderGeometryDefault)',
    obj: 'img',
    method: 'border',
    parameters: [ new gm.Geometry(gm.BorderGeometryDefault) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '1f58ee8cfe0dfc6d13a8f2d1ffefa1c9'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.channel(RedChannel)',
    obj: 'img',
    method: 'channel',
    parameters: [ gm.ChannelType.RedChannel ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == 'a0a7d142e37e832811a40774894e3abc'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
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
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == 'c4aa4c5647a81e5f9565f6baac6d130b'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.charcoal()',
    obj: 'img',
    method: 'charcoal',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '173f650c860a70de422eb21e0fc00d88'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.chop(geometry)',
    obj: 'img',
    method: 'chop',
    parameters: [ new gm.Geometry({ width: 20, height: 20, xOff: 50, yOff: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == 'a8e778773313ba662befa3b4a81ba45f'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.colorize( red, green, blue, pen)',
    obj: 'img',
    method: 'colorize',
    parameters: [ 50, 40, 80, new gm.Color({red: 0.5, green: 0, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '032fbaaeedc332917eb7a9dc9180b6ab'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.colorize( opacity, pen )',
    obj: 'img',
    method: 'colorize',
    parameters: [ 60, new gm.Color({red: 0.5, green: 0, blue: 0}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '3b94bfc8b228494619cadec070203fca'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.contrast( sharpen )',
    obj: 'img',
    method: 'contrast',
    parameters: [ 10 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '811e207ad4c5a4d33c3dc9c5c7566117'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.crop(geometry)',
    obj: 'img',
    method: 'crop',
    parameters: [ new gm.Geometry({ width: 20, height: 20, xOff: 50, yOff: 50}) ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '6617958064f7aeb456e44e9ba4fabfbe'); }
  },
  {
    name: "img = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img = img; fn(err); });
    }
  },
  {
    name: 'img.cycleColormap( amount )',
    obj: 'img',
    method: 'cycleColormap',
    parameters: [ 64 ],
    result: function(err, result, fn) { fn(err == null); }
  },
  {
    name: 'img.write(BMP)',
    obj: 'img',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && CreateMD5(gm.BlobToBuffer(result)) == '4c8cb212849035f33d745e984be6acbd'); }
  },

  {
    name: 'img.writeFile()',
    obj: 'img',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/temp.bmp' ],
    result: function(err, result, fn) { fn(err == null); }
  }
]
