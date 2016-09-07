#ifndef ISJSON_H
#define ISJSON_H

#include <stdint.h>

#define BUFFSIZE 300
uint8_t json_string[BUFFSIZE];

void flush();
uint8_t buildJSONString(uint8_t c);
uint8_t* getBuffer();

#endif // ISJSON_H 

