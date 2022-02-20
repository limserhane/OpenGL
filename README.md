# Projet OpenGL

* Helder LISBOA-BRITES
* Simon LALLEMAND
* Serhane LIM

--- 

Nous avons souhaité mettre en place la base d'un moteur tel que UE4 ou Unity, permettant de créer des applications simplement, sans que l'utilisateur n'ait à manipuler OpenGL. Le code à été pensé pour qu'il soit possible d'y ajouter des fonctionalités telles que :
* Une interface permettant de manipuler les transforms des objets
* Un moteur physique
* Plusieurs shaders
* Plusieurs textures par material
* ...

---

Les flèches permettent d'orienter la caméra.
Les touches A, Z, E, S, permettent respectivement de se déplacer vers la gauche, l'avant, la droite, l'arrière.
Les touches SPACE, X permettent respectivement de se déplacer vers le haut et le bas.

---

Notes :

* La cible est à compiler à partir de `projet/museum.cpp`.
* Les chemins des assets (models et textures) sont absolus. Les chemins utilisés sont définis aux lignes 21 et 22 de `projet/museum.cpp`.
* Pour être interprétées correctement par notre moteur, les textures standard doivent être flip verticalement. Le blending n'est pas géré.
* Malgré nos efforts, nous ne sommes pas parvenus à charger les materials spécifiés dans les fichiers obj lus. Il semblerait que la fonction `glimac::loadOBJ` n'accède pas non plus aux materials censés être renvoyés par la librairie `tiny_obj`.

