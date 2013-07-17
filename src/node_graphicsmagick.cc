#include <Magick++.h>

#include <node.h>
#include <v8.h>

using namespace v8;
using namespace node;

using namespace std;
using namespace Magick;

void init(Handle<Object> exports) {

  InitializeMagick(NULL);

}

NODE_MODULE(node_graphicsmagick, init);
