#include <stdio.h>
#include <string.h>

int main() {
    // emcc consumeCinJS.c -s WASM=1 -O1 -s EXPORTED_FUNCTIONS="['_main','_getDoubleNum','_getStr']" -o consumeCinJS.js
    return 5;
}

int getDoubleNum( int a ) {
    return a*2;
}

char * getStr(char * name) {
    char * result = "Hello ";
    strcat(result, name);
    return result;
}