# Projet d'informatique L3
### Commande à rentrer dans le terminal Linux pour compiler :

g++ -Wall -I/usr/include/python3.10 -I/public/mphyo/bibli_fonctions main.cpp NN_library/*.cpp /public/mphyo/bibli_fonctions/bibli_fonctions.ar -lm -lpython3.10 -o main.exe

 ## Abstract
 The idea is to create a relatively simple library for Neural networks in C. The aim is to use it to solve relatively simple PDE in physics. The first version will only tackle one dimension input. Later on, a method to deal with 2D and 3D would be a nice addition.

 ## Objectif du projet
 1. Se familiariser avec le fonctionnement d'un réseau de neuronne adapté pour des approximations de fonction.
 2. S'habituer à utiliser git et github pour le développement d'un projet. 
 3. Continuer de prendre en main le C.

 ## Cahier des charges
 L'objectif étant de construire une bibliothèque pour faire des réseaux de neuronnes et pas de construire un réseau en particulier, elle devra permettre :

 1. De modifier aisément les hyperparamètres du réseau (nombre de couche, nombre de neuronnes par couche, fonction d'activation).
 2. De construire les architectures classiques (complètement relié, fonctions d'activation ReLU et SELU, réseau convolutif??)

 L'objectif principale étant de créé des PINNs, le bibliothèque devra aussi permettre :

 4. D'accéder aux dérivées partielles.
 5. De donner une solution pour l'affichage graphique -> pour l'instant, utilisation de biblifonction.

 ## Fonctionnement des fonctions
 ### Fichier main
Cette troisième version du projet correspond à l'objectif premier, entrainer des PINNs!! Le programme est pour l'instant régler pour apprendre avec uniquement l'équation différentiel (f'-f = 0 , CI f(0) = 1). Cependant, il est déjà adapter pour une fonction de cout prenant en compte des données expérimentales. 

 ### Fichier BuildNN
Fichier contenant les fonctions permettant de construire le réseau de neuronne couche par couche ou de manière automatisé pour un réseau complètement connecté. 
A modifié pour prendre en colmpte un réseau convolutif.

 Lors de la définition de W, *W[i][j]* correspond au poid de la liaison entre le neuronne j de la couche précédente vers le neuronne i de la couche suivante.

### Fichier Random
**Adapter pour des fonctions random de Linux.**
Contient les fonctions permettant d'initialiser le poids de manière aléatoire. La fonction pour une répartition équiprobable suivant les lignes directrices de [1] déjà codé. 
Potentiellement rajouter celle pour une distribution gaussienne.

### Fichier ActivationFun
Contient les différentes fonctions d'activation ainsi que leur dérivées. Pour l'instant les fonctions Relu et SELU sont codées. Rajouter tanh...

### Fichier UseNN
Contient les fonctions nécessaires pour utiliser le réseau de neuronne.

### Fichier TeachNN
Contient les fonctions permettant de calculer la fonction de cout ainsi que celle permettant de modifier les poids pour apprendre.
Les dérivées de L par rapport au poid doivent être conservé avec les poids afin de pouvoir les modifier ultérieurment. 

La fonction backAllNN a été modifié (ainsi que la structure du réseau...) afin de calculer les valeurs des dérivées sans parcourir plusieur fois le réseau de neuronne. Les dérivées sont passé de neuronne en neuronne à l'aide d'une descente de gradient dtochastique. Puis trick comme Euler pour des dérivées d'ordres plus important?

Est ce que cette méthode fonctione? L'idée m'est venue comme ca et n'a pas été trouvé dans une ressource extérieur. Guess will see...

batch[i][0] correspond à l'entrée pour la i-eme valeur du batch alors que batch[i][1] est la sortie tabulée.

trainNN0 est une première version de l'aprentissage très basique. L'idée est d'entrainer le réseau de neuronne avec une vitesse d'apprentissage constante. Le choix de cette constante devient alors crucial.

trainNNAdam permet d'entrainer le réseau de neuronne en utilisant la méthode Adam. L'idée est que à chaque étape, la direction du gradient est enregistrée et modifié de manière raisonnable pour éviter les oscillations dans l'espace des paramètres. Il est recommandée de donnée des valeurs de environ 0.9 pour gamma et de 0.999 pour beta. Des valeurs un peu inférieur seront surement necessaire pour que l'apprentissager ne prenne pas trop longtemps.

Les deux méthodes peuvent être utilisé pour entrainer ces réseau matrès loin la plus prométeuse.

## Indication sur la rédaction
L -> fonction de cout à minimiser.

NN -> neural network, abréviatioon utilisée pour désigner le réseau de neuronne ou le pointeur dessus selon les fonctions.

g -> fonctions d'activation.

df ou dfdx -> dérivé de f (parfois avec précision de la variable).

W -> matrice des poids entre les couches.

b -> matrice des "offsets" entre les couches.

## Bibliographie
[1] _Deep learning for physics research_ de Martin Erdmann, Jonas Glombitza, Gregor Kasieczka, Uwe Klemradt.