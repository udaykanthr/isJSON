#ifndef ISJSON_H
#define ISJSON_H

#define BUFFSIZE 300
char json_string[BUFFSIZE];

void flush();
int buildJSONString(char c);
char* getBuffer();

#endif // ISJSON_H 

