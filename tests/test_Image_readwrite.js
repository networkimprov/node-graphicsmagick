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
    name: 'img.writeFile()',
    obj: 'img',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/temp.bmp' ],
    result: function(err, result, fn) { fn(err == null); }
  }
]
