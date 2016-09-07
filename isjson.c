#include "isjson.h"
#include <stdio.h>
#include <string.h>

uint8_t pc;
uint8_t parser[50];
uint8_t p =0;
uint8_t json_len = 0;
uint8_t isClear = 0;

void push(uint8_t c) {
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

uint8_t buildJSONString(uint8_t c) {

  if (isClear) {
    flush();
  }
  uint8_t isJ = 0;
  if (c == '{') {
    push(c);
    p++;
    parser[p-1] = c;
  } else if (p >= 1 && c == '}' && parser[p-1] == '{') {
    push(c);
    p--;
  } else if (p >= 1 && c != '}' && parser[p-1] == '{') {
    push(c);
  }

  // JSON detected.
  if (json_len > 0 && p == 0) {
    isJ = 1;
  }
  return isJ;
}

uint8_t* getBuffer() {
  isClear = 1;
  return json_string;
}
