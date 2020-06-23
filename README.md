# Web assembly playground

Contient :
1. un dossier pour la consommation de JS dans du C.
1. un dossier pour la consommation de C dans du JS.
1. un dossier pour la consommation de WASM sans l'utilisation d'**[emscripten][emscriptenLink]**.
1. un dossier comparant les performances de deux fonctions de determination de nombres premier, l'une en JS, l'autre en Assembly.
1. un petit projet d'animation de formes via canvas mélangeant JS et WA.

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
- `O1` un facteur de compression (non négligeable pour réduire la taille du WASM qui passera sur le réseau).
- `f1` le nom des functions C à exporter (y ajouter le caractère `_`).

## Interet

Les WA apportent plusieurs interet :
- elles peuvent colmater des implémentation manquantes au JS présentent dans d'autres langages.
- elles peuvent permettre la consommation de code/librairies pré-existant en C et ayant déjà fait leurs preuves.
- elles peuvent donner accès à de meilleurs performances lors de calculs numériques.

[emscriptenLink]: https://emscripten.org/docs/getting_started/downloads.html
[emscriptenInstallLink]: https://emscripten.org/docs/getting_started/downloads.html