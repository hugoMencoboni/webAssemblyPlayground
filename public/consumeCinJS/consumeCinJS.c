#include <stdio.h>
#include <string.h>

int main() {
    // emcc consumeCinJS.c -s WASM=1 -O1 -s EXPORTED_FUNCTIONS="['_main','_getNum','_getDoubleNum','_getStr']" -o consumeCinJS.js\n
    return 5;
}

int getNum() {
    return 55;
}

int getDoubleNum( int a ) {
    return a*2;
}

char * getStr(char * name) {
    char * result = "Salut ";
    strcat(result, name);
    return result;
}