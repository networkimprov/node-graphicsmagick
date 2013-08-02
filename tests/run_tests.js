var lTesting = require('./testing');
var nFs = require('fs');
var nPath = require('path');

var aAllFiles = nFs.readdirSync(nPath.dirname(module.filename));
var aTestData = [];
for (var i=0; i < aAllFiles.length; i++) {
  if (aAllFiles[i].match(/^test_.*\.js$/g))
    if (process.argv.length < 3 || aAllFiles[i].match(process.argv[2]))
      aTestData.push(require('./' + aAllFiles[i]));
}

var aResults = [];

doTest(0, true);
function doTest(i, sync) {
  if(i < aTestData.length) {
    var aTest = aTestData[i];
    lTesting.runTests(aTest.name + (sync ? ' - sync' : ' - async'), aTest.tests, sync, function (err, result) {
      if (!err) {
        console.log();
        aResults.push([aTest.name + (sync ? ' - sync' : ' - async'), result.okN, result.failN, result.fatalN]);
      }
      doTest(i + !sync, !sync);
    });
    return;
  }
  console.log('Summary: ok fail fatal   name');
  for (var ir = 0; ir < aResults.length; ir++) {
    console.log(aResults[ir][1]+' '+aResults[ir][2]+' '+aResults[ir][3]+'   '+aResults[ir][0]);
  }
}
