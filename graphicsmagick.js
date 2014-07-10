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


/*
signature example:
[
  [{type: 'function', key: 'callback'}],
  [{type: 'Geometry', msg: 'geometry1'}, {type: 'Color', msg: 'color1'}, {type: 'function', key: 'callback'}]
] //TODO: explain

a library specific object must have:
  string type - the type og the object
  number ref - the reference which will be sent to the lode shell
  object jsObj - the object which will be stringified and sent to the lode shell if ref is not found
*/
function parseArguments(initialMsg, signatures, args) {
  //TODO: treat optional args
  if (initialMsg !==null && typeof initialMsg != 'object') throw new Error('invalid initialMsg');
  var aParsedArgs = {};
  if (initialMsg !== null) aParsedArgs.msg = JSON.parse(JSON.stringify(initialMsg));
  //finding the matching signature
  var aSignature = null;
  for (var sigN = 0; sigN < signatures.length; sigN++) {
    if (args.length != signatures[sigN].length) continue;
    var aMatch = true;
    for (var argN = 0; argN < signatures[sigN].length; argN++) {
      var aArgType = typeof args[argN];
      if (aArgType == 'object' && 'type' in args[argN]) aArgType = args[argN].type;
      if (signatures[sigN][argN].type != aArgType) {
        aMatch = false;
        break;
      }      
    }
    if (aMatch) {
      aSignature = signatures[sigN];
      break;
    }
  }

  if (aSignature == null) {
    //no signature matchet, throw error
    throw new Error('arguments are ...'); //TODO
  }

  for (var argN = 0; argN < aSignature.length; argN++) {
    if ('key' in aSignature[argN]) {
      if (typeof aSignature[argN].key != 'string') throw new Error('invalid key');
      aParsedArgs[aSignature[argN].key] = args[argN];
    } else if ('msg' in aSignature[argN]) {
      if (!('msg' in aParsedArgs)) aParsedArgs.msg = {};
      if (aSignature[argN].type == 'string')
        aParsedArgs.msg[aSignature[argN].msg] = args[argN];
      else if (aSignature[argN].type == 'object')
        aParsedArgs.msg[aSignature[argN].msg] = JSON.stringify(args[argN]);
      else if ('ref' in args[argN]) 
        aParsedArgs.msg[aSignature[argN].msg] = JSON.stringify({ref: args[argN].ref});
      else if ('jsObj' in args[argN])
        aParsedArgs.msg[aSignature[argN].msg] = JSON.stringify({jsObj: args[argN].jsObj});
      else
        throw new Error('internal error');
    }
  }
  return aParsedArgs;
}

//creates ref and loderef from the existing jsObj
//TODO: explain better
function getPersistantMethod(opCreate, opFree) {
  if (typeof opCreate != 'string' && typeof opFree != 'string')
    throw new Error("arguments are string, string");
  return function(callback) {
    if (!('jsObj' in this)) throw new Error('no jsObj in object');
    if (!('callingPersistent' in this)) this.callingPersistent = false;
    if (callingPersistent) throw new Error("Calling persistent multiple times concurently");
    this.callingPersistent = true;
    var aLodeMsg = {op: opCreate};
    aLodeMsg.jsObj = jsObj;
    if ('ref' in this) aLodeMsg.ref = ref; //use the current existing lode ref
    delete this.ref; //the C++ object is invalid until it is reset;
    lode.call(sLib, aLodeMsg, function(err, data) {
      this.callingPersistent = false;
      if (err) { callback(err); return; }
      if ('error' in data) { callback(data.error); return; }
      if ('ref' in aLodeMsg)
        this.ref = aLodeMsg.ref;
      else
        this.ref = data.ref;
      if (!('loderef' in this)) {
        aLodeRefCnt++;
        this.lodeRef = lLR.LodeRef(function(){
          lode.call(sLib, {op: opFree, ref:ref}, function(err, data){ aLodeRefCnt--; checkQuit(); });
        });
      }
    });
  }
}



module.exports.Image = function() {
  var aParsedArgs = parseArguments({op: 'Image'},
    [
      [{type: 'function', key: 'callback'}],
      [{type: 'Geometry', msg: 'geometry1'}, {type: 'Color', msg: 'color1'}, {type: 'function', key: 'callback'}]
    ],
    arguments
  );
  lode.call(sLib, aParsedArgs.msg, function(err, data) {
    if (err) { aParsedArgs.callback(err); return; }
    if ('error' in data) { aParsedArgs.callback(data.error); return; }
    aParsedArgs.callback(null, new ImageClass(data.ref));
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


module.exports.Geometry = GeometryClass;
function GeometryClass() {
  var aParsedArgs = parseArguments(null,
    [
      [],
      [{type: 'object', key: 'obj'}],
      [{type: 'string', key: 'str'}]
    ],
    arguments
  );
  this.type = 'Geometry';
  this.jsObj = aParsedArgs;
}

//TODO: method to update the jsObj

GeometryClass.prototype.persistent = getPersistantMethod('GeometryCreate', 'GeometryFree');


module.exports.Color = ColorClass;
function ColorClass() {
  var aParsedArgs = parseArguments(null,
    [
      [{type: 'object', key: 'obj'}],
    ],
    arguments
  );
  this.type = 'Color';
  this.jsObj = aParsedArgs;
}

ColorClass.prototype.persistent = getPersistantMethod('ColorCreate', 'ColorFree');

