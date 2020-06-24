#include <stdio.h>
#include <emscripten.h>

EM_JS(int, fibJS, (int n), {
    if (n < 2) {
        return n;
    } else {
        return fibJS(n-1) + fibJS(n-2);
    }
});

int fib(int n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n-1) + fib(n-2);
    }
}