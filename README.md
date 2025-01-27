# Tetris204
Ce projet a été réalisé dans le cadre du cours IN204. Le but du projet est de programmer une version du jeu Tetris en C++.
Les fonctionnalités classiques ont été implémentées, ainsi qu'un mode multijoueur.

## Installation de SFML
Ce projet utilise la bibliothèque SFML pour l'affichage, le réseau et le son. Elle doit être installée pour la compilation. Tout le projet a été développé sur Linux Mint (base Ubuntu).

Pour installer la bibliothèque SFML avec apt (et build-essential pour le compilateur) :
``sudo apt install libsfml-dev build-essential
``
## Compilation et exécution
Pour compiler et exécuter le projet, après avoir installé SFML :

Cloner le projet
``git clone https://github.com/gabrielcdv/Tetris204.git
``

Compiler :
```
cd Tetris204
make
```
Lancer le jeu :
``./launcher.x
``

## Comment jouer
Quand ``./launcher.x`` est exécuté, le lanceur s'ouvre et propose plusieurs options.

### Jouer en solo
Pour jouer en solo, il suffit de cliquer sur "Singleplayer", la partie se lance  immédiatement.*

### Jeu en multijoueur
Pour jouer avec un autre joueur, il faut être sur le même réseau (ou ouvrir le port 5300 publiquement).
L'un des joueurs doit cliquer sur "Host Server". Le programme est alors en attente de connexion du deuxième joueur

Le deuxième joueur doit renseigner l'ip du premier dans la zone de texte puis cliquer sur "Join Server". La partie est alors lancée pour les deux joueurs.


## Déroulement d'une partie
Ce qui suit est commun au mode de jeu solo et multijoueur.
### Déplacement des pièces
Les touches utiles pour jouer sont :
- `Flèche gauche/droite` : Déplace la pièce qui tombe dans la direction voulue.
- `Flèche bas` : Déplace la pièce d'une case vers le bas.
- `Q` : Effectue une rotation vers la gauche
- `D` : Effectue une rotation vers la droite
- `Espace` : Envoie la pièce aussi bas que possible, instantanément.

### Score et niveau
Le calcul du score et du niveau est effectué selon [cette référence](https://perso.ensta-paris.fr/~bmonsuez/Cours/lib/exe/fetch.php?media=in204:Projet%20informatique%20TETRIS.pdf).

### Fin d'une partie
Une partie en solo se termine quand il n'est plus possible de faire apparaître une pièce.

Une partie en multijoueur se termine dès qu'un joueur déclare forfait (ferme le jeu) ou se retrouve bloqué.

## Changer la taille de la grille
Dans la version actuelle du projet, il n'est pas possible de configurer les dimensions de la grille depuis l'interface graphique.
Cependant, il est possible de faire cette modification dans le code, et il tient compte de ces dimensions pour produire une fenêtre de taille aussi grande que possible bien dimensionnée.
Il suffit de modifier les paramètres `GRID_HEIGHT` et `GRID_WIDTH` dans les premières lignes de `launcher.cpp`