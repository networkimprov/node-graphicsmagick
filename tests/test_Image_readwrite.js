var gm = require('../graphicsmagick.js');
var fs = require('fs');
var path = require('path');
var crypto = require('crypto');

function CreateMD5(buff) {
  var aMD5 = crypto.createHash('md5');
  aMD5.update(buff);
  return aMD5.digest('hex');
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
    name: 'img.border()',
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
    name: 'img.writeFile()',
    obj: 'img',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/temp.bmp' ],
    result: function(err, result, fn) { fn(err == null); }
  }
]
