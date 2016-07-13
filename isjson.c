#include "isjson.h"
#include <stdio.h>
#include <stdlib.h>

char pc;
char parser[50];
int p =0;
int json_len = 0;

void push(char c) {
  json_len++;
  json_string[json_len-1] = c;
  pc = c;
}
int buildJSONString(char c) {

  int isJ = 0;
  if (json_len > 0 && pc != '"' && c ==  ' ')
    {
      return 0; // Ignore spaces in between seepcial chars.
    }
  else
  if (json_len == 0 && c == '{') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if (json_len == 1 && c == '"') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if(json_len == 1 && c != '"') {
    json_len = 0;
    p = 0;
  } else if (p >= 1 && c == '{' && parser[p-1] != '"') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if (p >= 1 && c != '"' && parser[p-1] == '"') {
    push(c);
  } else if (p >= 1 && c == '"' && parser[p-1] == '"') {
    push(c);
    p--;
  } else if (p >= 1 && c == '"' && parser[p-1] != '"') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if (p >= 1 && c == '}' && parser[p-1] == '{') {
    push(c);
    p--;
  } else if (p >= 1 && c != '}' && parser[p-1] == '{') {
    push(c);
  }

  // JSON in buffer is valid
  if (json_len > 0 && p == 0) {
    isJ = 1;
  }
  return isJ;
}

char* getBuffer() {
  char *buff = malloc(BUFFSIZE);
  if (buff != NULL) {
    for (int i=0; i<json_len; i++) {
      buff[i] = json_string[i];
    }
  }

  return buff;
}
