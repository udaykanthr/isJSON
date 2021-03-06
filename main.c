#include "isjson.h"
#include <stdio.h>
#include <string.h>

char *js = "{\"test\": \"testdata\", \"token2\" : {\"test\": \"test1\"}, \"arraty\": [\"test\", \"test\", \"ert\"]}";
int main() {

  int isJson = 0;
  printf("Scanning...\n");
  for (int i=0;i< strlen(js); i++) {
    isJson = buildJSONString(js[i]);
  }

    if (isJson) {
      printf("JSON detected: %s\n", getBuffer());
    } else {
      printf("INVALID json data:\n");
    }
  return 0;
}
