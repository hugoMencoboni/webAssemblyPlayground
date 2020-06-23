#include <stdio.h>
#include <emscripten.h>

EM_JS(int, jsFactoriel, (int n), {
    let result = 0;
    while (n > 0) {
        result += n;
        n--
    }

    return result;
});

int main() {
    printf("emcc consumeJSinC.c -s WASM=1 -O1 -o consumeJSinC.js\n");
    
    emscripten_run_script("console.log('consol log JS from C')");

    int param = 10;
    int res = jsFactoriel(param);
    
    //emscripten_debugger();
    //emscripten_log(EM_LOG_WARN, "debugger tools");

    printf("Factoriel de %d: %d\n", param, res);

    return 1;
}