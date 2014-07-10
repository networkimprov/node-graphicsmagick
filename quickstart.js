var lGM = require('./graphicsmagick.js');

lGM.on('connect', function() {
  console.log('gm library ready');
  lGM.Image(new lGM.Geometry({width: 3, height: 4}), new lGM.Color({red: 0.5, green: 0, blue: 0}), function(err, img1) {
    console.log('Image create err: ' + err);
    lGM.quit();
  });
});

lGM.on('status', function(msg) {
  console.log(msg);
});

lGM.on('error', function(msg) {
  console.log(msg);
});

lGM.on('disconnect', function() {
  console.log('gm quit');
});

lGM.init(null);

setTimeout(function() {
  for (var i = 0; i < 200; i++)
    new Buffer(1000000);
}, 1000);
