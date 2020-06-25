# Web assembly playground

Contient :
1. **[une page][JSinCLink]** dédiée à la consommation de JS dans du C.
1. **[une page][CinJSLink]** dédiée à la consommation de C dans du JS.
1. **[une page][WASMLink]** dédiée à la consommation de WASM sans l'utilisation d'**[emscripten][emscriptenLink]**.
1. **[une page][PerfLink]** dédiée à la comparaison de performances entre JS et WebAssembly.
1. **[une page][CanvasLink]** dédiée à l'animation de formes via canvas mélangeant JS et WA.

## Mise en place

Nécessite l'intallation d'**[emscripten][emscriptenInstallLink]**.

Après l'installation, activer **[emscripten][emscriptenLink]** via la commande `emsdk_env.bat` dans le repertoir téléchargé.

L'application passe par un server Express car le passage par le protocol HTTP est nécessaire à la consomation de WA.

Pour lancer le serveur, lancer `npm run start`.

## Génération de WASM

**[emscripten][emscriptenInstallLink]** est utilisé dans ce projet pour générer des fichiers js et leurs WAMS sur la base de fichiers C via la commande :

`emcc file.c -s WASM=1 -O1 -s EXPORTED_FUNCTIONS="['_f1,_f2,...']" -o file.js`

avec :
- `file.c` le fichier C à convertir.
- `file.js` le nom du fichier JS qui sera généré et consommé.
- `f1` le nom des functions C à exporter (y ajouter le caractère `_`).
- `On` un facteur de compression (non négligeable pour réduire la taille du WASM qui passera sur le réseau).
- `f1` le nom des functions C à exporter (y ajouter le caractère `_`).

## Interet

Les WA apportent plusieurs interet :
- elles peuvent colmater des implémentation manquantes au JS présentent dans d'autres langages.
- elles peuvent permettre la consommation de code/librairies pré-existant en C et ayant déjà fait leurs preuves.
- elles peuvent donner accès à de meilleurs performances lors de calculs numériques.

Pour plus de détail : **[WebAssembly: How and why][webassemblyLink]**.

[JSinCLink]: https://hugomencoboni.github.io/webassemblyplayground/public/consumeCinJS/index.html
[CinJSLink]: https://hugomencoboni.github.io/webassemblyplayground/public/consumeJSinC/index.html
[WASMLink]: https://hugomencoboni.github.io/webassemblyplayground/public/consumeWithoutEmscripten/index.html
[PerfLink]: https://hugomencoboni.github.io/webassemblyplayground/public/fibonacci/index.html
[CanvasLink]: https://hugomencoboni.github.io/webassemblyplayground/public/canvasBox/index.html

[emscriptenLink]: https://emscripten.org/docs/getting_started/downloads.html
[emscriptenInstallLink]: https://emscripten.org/docs/getting_started/downloads.html
[webassemblyLink]: https://blog.logrocket.com/webassembly-how-and-why-559b7f96cd71/
