var lode = require('./node_modules/lode/lode.js');
var lLR = require('./node_modules/lode/build/Release/node_loderef.node');
var sLib = __dirname+'/graphicsmagick_lode.so';
var sEvents = {};

module.exports.on = function(event, callback) {
  if (typeof event !== 'string' || typeof callback !== 'function')
    throw new Error('arguments are: String event, Function callback');
  sEvents[event] = callback;
};

module.exports.init = function(params) {
  lode.load(sLib, params, function(op, data) {
    if (sEvents[op])
      return sEvents[op](data);
    if (op === 'error')
      throw data;
  });
};

var aLodeRefCnt = 0;
var aQuitCalled = false;
module.exports.quit = function() {
  aQuitCalled = true;
  if (aLodeRefCnt == 0) lode.unload(sLib);
}
function checkQuit() {
  if (aQuitCalled && aLodeRefCnt == 0) module.exports.quit();
}


module.exports.Image = function(callback) {
  if (typeof callback !== 'function')
    throw new Error('arguments are: String s, Function callback');
  lode.call(sLib, {op:'Image'}, function(err, data) {
    if (err) { callback(err); return; }
    if ('error' in data) { callback(data.error); return; }
    callback(null, new ImageClass(data.ref));
  });
};

function ImageClass(ref) {
  this.type = 'Image';
  this.ref = ref;
  aLodeRefCnt++;
  this.lodeRef = lLR.LodeRef(function(){
    lode.call(sLib, {op:'ImageFree', ref:ref}, function(err, data){ aLodeRefCnt--; checkQuit(); });
  });
}


