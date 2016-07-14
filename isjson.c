#include "isjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pc;
char parser[50];
int p =0;
int json_len = 0;
int isClear = 0;

void push(char c) {
  json_len++;
  json_string[json_len-1] = c;
  pc = c;
}

void flush() {
  json_len = 0;
  p = 0;
  memset(json_string, 0, sizeof(json_string));
  isClear = 0;
}

int buildJSONString(char c) {

  if (isClear) {
    flush();
  }
  int isJ = 0;
  if (p > 1 && json_len > 0 && parser[p-1] != '"' && c ==  ' ')
    {
      return 0; // Ignore spaces in between seepcial chars.
    }
  else if (json_len == 0 && c == '{') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if (json_len == 1 && c == '"') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if(json_len == 1 && c != '"') {
    flush();
  } else if (p >= 1 && c != '"' && parser[p-1] == '[') {
    flush();
  } else if (p >= 1 && c == ']' && parser[p-1] == '[') {
    push(c);
    p--;
  } else if (p >= 1 && (c == '"' || c == '[' || c == '{') && parser[p-1] == ':') {
    push(c);
    parser[p-1] = c;     
  } else if (p >= 1 && !(c == '"' || c == '[' || c == '{') && parser[p-1] == ':') {
    flush();
  } else if (p >= 1 && c == '"' && parser[p-1] == ',') {
    push(c);
    parser[p-1] = c;     
  } else if (p >= 1 && c != '"' && parser[p-1] == ',') {
    flush();
  } else if (p >= 1 && (c == '{' || c == ':' || c == ',') && parser[p-1] != '"') {
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
  /* char *buff; */
  /* buff = malloc(json_len+1); */
  /* if (buff != NULL ) { */
  /*   strlcpy(buff, json_string, json_len+1); */
  /*   p =0; */
  /*   json_len = 0; */
  /*   pc = ' '; */
  /* } */
  isClear = 1;
  return json_string;
}
