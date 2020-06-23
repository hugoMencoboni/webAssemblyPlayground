#include <stdio.h>
#include <emscripten.h>

EM_JS(int, isPrimeJS, (int num), {
    for(let i = 2; i < num; i++) {
        if(!num % i) {
        return false;
        }
    }

    return num !== 0 && num !== 1;
});

int isPrime(int num) {
    for(int i = 2; i < num; i++) {
        if(num % i == 0) {
            return 0;
        }
    }

    return (num != 0 && num != 1) ? 1 : 0;
}