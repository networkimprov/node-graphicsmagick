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

exports.name = 'Image Attributes and Options';
exports.tests = [
  NewImageFromFile('img', 'files/img1.bmp'),
  {
    name: 'img.adjoin(flag)',
    obj: 'img',
    method: 'adjoin',
    parameters: [ false ],
    result: function(err, result, fn) { fn(err == null); }
  }, {
    name: 'img.adjoin()',
    obj: 'img',
    method: 'adjoin',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null && !result); }
  }, {
    name: 'img.adjoin(flag)',
    obj: 'img',
    method: 'adjoin',
    parameters: [ true ],
    result: function(err, result, fn) { fn(err == null); }
  }, {
    name: 'img.adjoin()',
    obj: 'img',
    method: 'adjoin',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null && result); }
  },
  {
    name: 'img.antiAlias(flag)',
    obj: 'img',
    method: 'antiAlias',
    parameters: [ false ],
    result: function(err, result, fn) { fn(err == null); }
  }, {
    name: 'img.antiAlias()',
    obj: 'img',
    method: 'antiAlias',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null && !result); }
  }, {
    name: 'img.antiAlias(flag)',
    obj: 'img',
    method: 'antiAlias',
    parameters: [ true ],
    result: function(err, result, fn) { fn(err == null); }
  }, {
    name: 'img.antiAlias()',
    obj: 'img',
    method: 'antiAlias',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null && result); }
  },
  {
    name: 'img.animationDelay(delay)',
    obj: 'img',
    method: 'animationDelay',
    parameters: [ 100 ],
    result: function(err, result, fn) { fn(err == null); }
  }, {
    name: 'img.animationDelay()',
    obj: 'img',
    method: 'animationDelay',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null && result == 100); }
  },
{
    name: 'img.animationIterations(iterations)',
    obj: 'img',
    method: 'animationIterations',
    parameters: [ 100 ],
    result: function(err, result, fn) { fn(err == null); }
  }, {
    name: 'img.animationIterations()',
    obj: 'img',
    method: 'animationIterations',
    parameters: [ ],
    result: function(err, result, fn) { fn(err == null && result == 100); }
  }
]
