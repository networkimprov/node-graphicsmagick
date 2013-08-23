var gm = require('../graphicsmagick.js');
var fs = require('fs');
var path = require('path');

var aTestsDir = path.dirname(module.filename);

exports.name = 'Image Read / Write';
exports.tests = [
  {
    name: 'img1 = new Image(new Geometry({width: 3, height: 4}), {red: 0.5, green: 0, blue: 0});',
    fatal: true,
    action: function(objects, sync, fn) { objects.img1 = new gm.Image(new gm.Geometry({width: 3, height: 4}), {red: 0.5, green: 0, blue: 0}); fn(null) }
  },
  {
    name: 'img1.write(BMP)',
    obj: 'img1',
    method: 'write',
    parameters: [ 'BMP' ],
    result: function(err, result, fn) { fn(err == null && result.toString('base64') == 'Qk1OAAAAAAAAAD4AAAAoAAAAAwAAAAQAAAABAAEAAAAAABAAAABtCwAAbQsAAAIAAAACAAAAAAB/AAAAAAAAAAAAAAAAAAAAAAAAAAAA'); }
  },
  {
    name: "img2 = new Image('files/img1.bmp');",
    fatal: true,
    action: function(objects, sync, fn) {
      if (sync) {
        objects.img2 = new gm.Image(aTestsDir + '/files/img1.bmp'); fn(null);
      } else
        new gm.Image(aTestsDir + '/files/img1.bmp', function(err, img) { objects.img2 = img; fn(err); });
    }
  },
  {
    name: 'img2.writeFile()',
    obj: 'img2',
    method: 'writeFile',
    parameters: [ aTestsDir + '/files/img1.1.bmp' ],
    result: function(err, result, fn) { fn(err == null && fs.readFileSync(aTestsDir + '/files/img1.1.bmp').toString('base64') == fs.readFileSync(aTestsDir + '/files/img1.bmp').toString('base64')); }
  }
]
