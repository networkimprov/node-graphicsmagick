#include "../node_modules/lode/src/lode.h"
#include <stdio.h>
#include <string>

static char sReplyErr[] = "{'_id':'%s','error':%d}"; // response templates
static char sReplyErrStr[] = "{'_id':'%s','error':'%s'}";

const char* initialize(int argc, char* argv[]) {
  char* aReplies[] = { sReplyErr, sReplyErrStr, NULL };
  for (int i=0; aReplies[i]; ++i)
    flipQuote(aReplies[i]); // flip ' & " characters
  // initialize the library
  return NULL;
}

static const char* sQid[] = {"_id", NULL}; // JsonQuery inputs
static const char* sQop[] = {"op", NULL};
static const char* sQdata[] = {"data", NULL};
static const char* sQref[] = {"ref", NULL};
static const char* sQref2[] = {"ref2", NULL};

void handleMessage(JsonValue* op, ThreadQ* q) {
  JsonQuery aQ(op);
  JsonValue* aId = aQ.select(sQid).next();
  JsonValue* aOp = aQ.select(sQop).next();
  char aTmp[2048];
  int aLen=0;
  if (aOp && aOp->isString()) {
    // call library
    if (!strcmp((char*)aOp->s.buf, "Image")) {
      aLen = snprintf(aTmp, sizeof(aTmp), sReplyErrStr, aId->s.buf, "not yet implemented");
    } else if (!strcmp((char*)aOp->s.buf, "ImageFree")) {
      aLen = snprintf(aTmp, sizeof(aTmp), sReplyErrStr, aId->s.buf, "not yet implemented");
    }
  }
  if (aLen <= 0 || aLen > (int)sizeof(aTmp)) {
    aLen = snprintf(aTmp, sizeof(aTmp), sReplyErr, aId->s.buf, aLen);
  }
  q->postMsg(aTmp, aLen);
}

