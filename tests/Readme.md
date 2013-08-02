To run a test:
 * node run_tests.js
 * node run_tests.js test_mask

To create a test batch you must 
 * create a file with the name test_*.js
 * have it export a name and an array of tests
  * exports.name = "Test batch name";
  * exports.tests = [ ... ]

Each test from the test array will be executed sequentially, both sync and async. 

The initialization/complex test:  
```
{  
  name: 'test name',
  fatal: true/false, // if true and the test fails the batch will be stopped
  action: function(objects, sync, fn) { fn(null); }
    // objects - the global objects for the batch 
    // sync - if it is the sync or async version of the tests
    // fn - the function to call with the result; if it is not null the test is considered failed
}
```

The simple test: 
```
{
  name: 'test name',
  obj: 'obj', //the object from the global objects for the batch for which the function will be called
  method: 'set_data', // the function that will be called for the object
  parameters: [ "a parameter" ], 
    // the parameters with which the function will be called;
    //for async a callback function will be added automatically
  result: function(err, result, fn) { fn(err == null); } 
    // error - the error thrown/returned after running the function
    // result - the result of running the function
    // fn - the function to call with the result of the test (true or false)
}
```
