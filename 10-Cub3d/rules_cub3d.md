## 1. Règles communes (à respecter strictement)

* Langage : **C**.
* Respect strict de la **Norme 42** pour tous les fichiers (y compris bonus).
* Le programme ne doit pas planter (segmentation fault, bus error, double free, etc.). Si c’est le cas le projet est considéré non-fonctionnel.
* **Aucun leak** mémoire toléré : toute mémoire allouée sur la heap doit être libérée correctement.
* Si le projet demande un Makefile, il doit utiliser les flags `-Wall -Wextra -Werror` et **ne pas relinker**.
* Makefile minimal attendu : `$(NAME)`, `all`, `clean`, `fclean`, `re`.
* Pour les bonus : inclure une règle `bonus` dans le Makefile; les sources bonus doivent être séparées (suffixe `_bonus.c` / `_bonus.h`).
* Si la libft est autorisée : **copier** ses sources et son Makefile dans un dossier `libft/` à la racine. Le Makefile du projet doit appeler le Makefile de la libft puis compiler le projet.
* Rendu : tout doit être poussé sur le dépôt Git qui vous est assigné (Deepthought ne corrigera que ce qui est sur le Git).

---

## 2. Informations générales sur Cub3D (partie obligatoire)

* Nom du programme : `cub3D`.
* Argument attendu : un fichier de description de scène avec l'extension `.cub`.
* Utiliser la **MiniLibX** (version OS ou depuis sources). Si vous utilisez les sources, appliquer les mêmes règles qu'à la libft (copie et Makefile si nécessaire).
* Affichage : implémenter un ray-caster (vue subjective) pour rendre une représentation 3D "réalistique" d’un labyrinthe.
* Gestion de la fenêtre : **parfaite** (minimisation, perte/passage de focus, fermeture via croix rouge, etc.).
* Textures : afficher des textures différentes selon l’orientation du mur (NO / SO / WE / EA).
* Sol et plafond doivent pouvoir avoir des **couleurs différentes** (F et C).

### Contrôles obligatoires

* Flèches gauche/droite : rotation de la caméra.
* `W`, `A`, `S`, `D` : déplacement du joueur.
* `ESC` : fermer proprement la fenêtre et quitter.
* Clic sur la croix rouge : fermer proprement la fenêtre et quitter.

---

## 3. Format et parsing du fichier `.cub`

* Le fichier `.cub` contient : les chemins des textures (NO, SO, WE, EA), les couleurs (`F` pour floor, `C` pour ceiling), puis la **map**. La **map est toujours en dernier** dans le fichier.

* Identifiants et format (ordre strict pour chaque élément) :

  * `NO <chemin_vers_texture_nord>`
  * `SO <chemin_vers_texture_sud>`
  * `WE <chemin_vers_texture_ouest>`
  * `EA <chemin_vers_texture_est>`
  * `F R,G,B` (valeurs 0–255)
  * `C R,G,B` (valeurs 0–255)

* La **map** doit n’utiliser que ces caractères : `0`, `1`, `N`, `S`, `E`, `W`.

  * `1` = mur
  * `0` = espace vide
  * `N/S/E/W` = position initiale et orientation du joueur

* La map doit être **rectangulaire** et **fermée / entourée de murs**. Si la map n’est pas fermée → erreur.

* Les espaces (caractères ' ') dans la map sont valides et doivent être gérés correctement.

* En dehors de la map, chaque élément peut être séparé par une ou plusieurs lignes vides.

* Sauf pour la map, les informations peuvent être séparées par un ou plusieurs espaces.

### Exemple minimal de `.cub`

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
```

---

## 4. Comportement en cas d’erreur

* Si un problème de configuration ou de parsing est détecté, le programme doit quitter et afficher :

```
Error
<message explicite>
```

* Le message explicite est libre (doit aider à comprendre l’erreur : ex. "Error\nInvalid map: not closed\n").

---

## 5. Fonctions externes autorisées

* `open, close, read, write, printf, malloc, free, perror, strerror, exit`
* Toutes les fonctions de la librairie math (`-lm`).
* Toutes les fonctions de la MiniLibX.
* Libft autorisée (voir point sur copie de la libft ci‑dessus).

---

## 6. Conseils pratiques

* Crée des programmes de test locaux pour vérifier le parsing, la fermeture de la map, la gestion des erreurs, et la détection de leaks (valgrind).
* Garde le parsing et la logique de raycasting découplés autant que possible (tests unitaires plus faciles).
* Vérifie la robustesse à l’ouverture/fermeture/reprise du focus de la fenêtre (MinilibX peut être capricieuse selon l’OS).
* Documente dans le README comment lancer le programme et fournir un exemple de `.cub` minimal.

