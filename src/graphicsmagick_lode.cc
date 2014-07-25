#include "../node_modules/lode/src/lode.h"
#include <Magick++.h>

#include <stdio.h>
#include <string>
#include <assert.h>

using namespace Magick;

static char sReplyErr[] = "{'_id':'%s','error':%d}"; // response templates
static char sReplyErrStr[] = "{'_id':'%s','error':'%s'}";
static char sReplyId[] = "{'_id':'%s'}";
static char sReplyObject[] = "{'_id':'%s','ref':%d}";

const char* initialize(int argc, char* argv[]) {
  char* aReplies[] = { sReplyErr, sReplyErrStr, sReplyId, sReplyObject, NULL };
  for (int i=0; aReplies[i]; ++i)
    flipQuote(aReplies[i]); // flip ' & " characters
  // initialize the library
  Magick::InitializeMagick(NULL);
  return NULL;
}

static const char* sQid[] = {"_id", NULL}; // JsonQuery inputs
static const char* sQop[] = {"op", NULL};
static const char* sQref[] = {"ref", NULL};
static const char* sQcallback[] = {"callback", NULL};
static const char* sQstr1[] = {"str1", NULL};
static const char* sQgeometry1[] = {"geometry1", NULL};
static const char* sQcolor1[] = {"color1", NULL};


void handleMessage(JsonValue* op, ThreadQ* q) {
  JsonQuery aQ(op);
  JsonValue* aId = aQ.select(sQid).next();
  JsonValue* aOp = aQ.select(sQop).next();
  char aTmp[2048];
  int aLen=0;
  if (aOp && aOp->isString()) {
    // call library
    try {
      if (!strcmp((char*)aOp->s.buf, "Image")) {
        JsonValue *aGeometry1, *aColor1;
        if ((aGeometry1 = aQ.select(sQgeometry1).next()) && ( aColor1 = aQ.select(sQcolor1).next()) && aQ.select(sQcallback).next()) {
          aLen = snprintf(aTmp, sizeof(aTmp), sReplyObject, aId->s.buf, addrToRef(new Image())); //TODO: propper image
        } else if (aQ.select(sQcallback).next()) {
          aLen = snprintf(aTmp, sizeof(aTmp), sReplyObject, aId->s.buf, addrToRef(new Image()));
        } else
          assert(0);
      } else if (!strcmp((char*)aOp->s.buf, "ImageWriteFile")) {
        JsonValue *aRef, *aStr1;
        if ((aRef = aQ.select(sQref).next()) && (aStr1 = aQ.select(sQstr1).next())) {
          addrFromRef<Image>(aRef->i)->write((const char*) aStr1->s.buf);
          aLen = snprintf(aTmp, sizeof(aTmp), sReplyId, aId->s.buf);
        } else
          assert(0);
      } else if (!strcmp((char*)aOp->s.buf, "ImageFree")) {
        JsonValue* aRef;
        if (aRef = aQ.select(sQref).next()) {
          delete addrFromRef<Image>(aRef->i);
          aLen = snprintf(aTmp, sizeof(aTmp), sReplyId, aId->s.buf);
        } else
          assert(0);
      } else
        assert(0);
    } catch (std::exception& err) {
      aLen = snprintf(aTmp, sizeof(aTmp), sReplyErrStr, aId->s.buf, err.what());
    }
  }
  if (aLen <= 0 || aLen > (int)sizeof(aTmp)) {
    aLen = snprintf(aTmp, sizeof(aTmp), sReplyErr, aId->s.buf, aLen);
  }
  q->postMsg(aTmp, aLen);
}

