# inf3172-tp2 #
tp2 hiver 2017 UQAM réalisé par Michael Vincent

Turbo-Shell est un shell rudimentaire. Il a été développé en langage C. Il ne s'agit pas d'une simulation. Les commandes du shell ont un réel impact sur la machine où le shell est executé.

## Le Shell ##
Le nom de l'exécutable est "tsh" pour Turbo-Shell. Il peut executer quelques commandes simples telle que:

### qui fait partie du shell ###
* __cd__ : Comme sous Unix, la commande ___cd___ sert à changer le répertoire de travail du shell. Cette commande
reçoit en paramètre le chemin relatif ou absolu vers le répertoire cible. La commande cd peut
également recevoir .. pour remonter d'un niveau dans la hiérarchie de répertoires. La commande "cd
.." appliquée sur le répertoire racine n'a aucun effet et n'affiche aucun message d'erreur. Si le
répertoire cible n'existe pas, un message d'erreur est affiché.

* __cdir__ : La commande ___cdir___ ne prend aucun paramètre. Elle affiche le chemin absolu du répertoire courant du
shell.

* __exit__ : La commande ___exit___ ne prend aucun paramètre. Elle met fin à l'exécution du shell.

### Les autres exécutables ###
Toutes ces commandes s'exécute dans un nouveau processus. Le ___stdout___ du nouveau processus est affiché par le shell.

* __new <nom de fichier>__ : La commande ___new___ sert à créer un nouveau fichier texte vide. Le paramètre est un chemin relatif ou absolu vers le fichier à créer. Une erreur de création doit afficher un message à l'écran.

```
tsh> new inf3172/tp1/source.c
Fichier créé
tsh> new inf3172/tp1/source.c
Impossible de créer le fichier
tsh>
```

* __list <-d>__ : La commande ___list___ sert à afficher la liste des fichiers ou répertoires dans le répertoire courant du
shell. Sans l'option ___-d___, on affiche les fichiers. Avec l'option ___-d___, on affiche les répertoires. Les
fichiers et répertoires cachés sont également affichés, mais on n'affiche pas les répertoires "." et "..".

```
tsh> list
Fichiers de /usr/kc932134/inf3172
tp1.c
tp1.h
makefile
tsh>
tsh> list -d
Sous-répertoires de /usr/kc932134/inf3172
tp1
tp2
notes
test
tsh>
```

* __rmall <nom du répertoire>__ : La commande ___rmall____ supprime un répertoire et tout son contenu récursivement (tous les sous-répertoires) sans demander de confirmation. Le nom du répertoire peut être un chemin relatif ou absolu. Si le répertoire est inexistant, un message est affiché. Si l'utilisateur ne possède pas les droits pour supprimer le répertoire, un message est affiché et le contenu doit reste intacte.

```
tsh> rmall inf3172
Répertoire supprimé
tsh> rmall inf3172
Répertoire introuvable
tsh> rmall /dev
Permissions insuffisantes
tsh>
```

* __newdir <nom du répertoire>__ : La commande ___newdir___ sert à créer un nouveau répertoire vide. Le paramètre est un chemin relatif ou absolu vers le répertoire à créer. Une erreur de création affiche un message à l'écran.
```
tsh> newdir inf3172/tp1
Répertoire créé
tsh> newdir inf3172/tp1
Impossible de créer le répertoire
tsh>
```

* __size <nom du répertoire>__ : La commande ___size___ doit calculer le nombre de fichier dans le répertoire et la taille du répertoire, c'est-à-dire la somme de la taille de tous les fichiers qu'il contient, peu importe la profondeur. Le paramètre est un chemin relatif ou absolu vers le répertoire où calculer la taille. Un message est affiché si le répertoire est inexistant.

```
tsh> size
Le répertoire /usr/kc932134/inf3172 contient 32 fichiers pour un
total de 4578845 octets.
tsh> size temp
Répertoire introuvable
```

* __fin <nbLignes> <fichier>__ : La commande ___fin___ sert à afficher un certain nombre de lignes d'un fichier à partir de la fin du fichier. Le paramètre nbLignes est le nombre de lignes à afficher, ce doit être un entier positif. Le paramètre fichier est un chemin relatif ou absolu vers le fichier à lire. Une erreur est affichée si le fichier est inexistant.

```
tsh> fin 5 inf3172/tp1/source.c
Fichier introuvable
tsh> fin 3 inf3172/tp1/sourceTP1.c
// fin normale du programme
exit(0);
}
tsh> fin test fichier.txt
Argument invalide
tsh>
```

* __tsh__ : La commande ___tsh___ ne prend aucun parametre. Lorsque lancé à l'intérieur du programme ___tsh___, cela ouvre un autre shell enfant lié au parent.
```
tsh> tsh
tsh> exit
tsh> exit
```
