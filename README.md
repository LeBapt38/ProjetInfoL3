# Projet d'informatique L3
### Commande à rentrer dans le terminal Linux pour compiler :

g++ -Wall -I/usr/include/python3.10 -I/public/mphyo/bibli_fonctions main.cpp NN_library/*.cpp /public/mphyo/bibli_fonctions/bibli_fonctions.ar -lm -lpython3.10 -o main.exe

 ## Abstract
   The main goal of this project was to learn how to code in C and the basics behind neural networks. In order to do so, I tried to implement a really basic library for neural networks. The goal I had in mind was solving PDE's with PINN's but I only managed to approximate known function. The project was far from a failure nevertheless. I learned a lot about how to structure code, I learned to use Git and GitHub... 

 ## Objectif du projet
 1. Se familiariser avec le fonctionnement d'un réseau de neuronne adapté pour des approximations de fonction.
 2. S'habituer à utiliser git et github pour le développement d'un projet. 
 3. Continuer de prendre en main le C.

 ## Cahier des charges
 L'objectif étant de construire une bibliothèque pour faire des réseaux de neuronnes et pas de construire un réseau en particulier, elle devra permettre :

 1. De modifier aisément les hyperparamètres du réseau (nombre de couche, nombre de neuronnes par couche, fonction d'activation).
 2. De construire les architectures classiques (complètement relié, fonctions d'activation ReLU et tanh, réseau convolutif??)
 3. Laisse la possibiliité de choisir la fonction de cout.

 L'objectif principale étant de créé des PINNs, le bibliothèque devra aussi permettre :

 4. D'accéder aux dérivées partielles.
 5. De donner une solution pour l'affichage graphique.

 ## Fonctionnement des fonctions
 ### Fichier main
 L'objectif de ce premier exemple est de reproduire la fonction cosinus à partir d'une base de donnée de valeurs. Pour cela, un NN prenant en argument x et sortant une valeur avec 3 couche caché de 3 neuronnes sera considéré. Les fonctions sont choisie au plus simple : 
 - Relu pour l'activation
 - Equiproba pour l'initialisation.

 Pour l'instant je rencontre des difficultés au niveau des résultats. Un premier soucis au niveau de la remonté de gradient à demander de changer un peu les structures mais en dehors de cela, le code fonctionne. Le problmème vient surment de la gestion des hyper paramètres. J'ai déja essayer de réajuster l'initialisation afibn que les poids ne deviennent pas négatifs (marche pas avec Relu). Le nombre de neuronne par couche a aussi du être réajusté (5 -> 100)... 

 ### Fichier BuildNN
Fichier contenant les fonctions permettant de construire le réseau de neuronne couche par couche ou de manière automatisé pour un réseau complètement connecté. 
A modifié pour prendre en colmpte un réseau convolutif.

 Lors de la définition de W, *W[i][j]* correspond au poid de la liaison entre le neuronne j de la couche précédente vers le neuronne i de la couche suivante.

### Fichier Random
**Adapter pour des fonctions random de Linux.**
Contient les fonctions permettant d'initialiser le poids de manière aléatoire. La fonction pour une répartition équiprobable suivant les lignes directrices de [1] déjà codé. 
Potentiellement rajouter celle pour une distribution gaussienne.

### Fichier ActivationFun
Contient les différentes fonctions d'activation ainsi que leur dérivées. Pour l'instant la fonction Relu est codé. Rajouter tanh...

### Fichier UseNN
Contient les fonctions nécessaires pour utiliser le réseau de neuronne.

### Fichier TeachNN
Contient les fonctions permettant de calculer l'erreur quadratique moyenne ainsi que celle permettant de modifier les poids pour apprendre.
Les dérivées de L par rapport au poid doivent être conservé avec les poids afin de pouvoir les modifier ultérieurment. 

La fonction backAllNN devra être modifié ainsi que de nombreuse autre pour prendre en compte des dérivées premières. Puis trick comme Euler pour des dérivées d'ordres plus important?

batch[i][0] correspond à l'entrée pour la i-eme valeur du batch alors que batch[i][1] est la sortie tabulée.

trainNN0 est une première version de l'aprentissage très basique. L'idée est d'entrainer le réseau de neuronne avec une vitesse d'apprentissage constante. Le choix de cette constante devient alors crucial; D'autres méthodes plus précise pourront être ajouter plus tard (adam, adagrad...).

## Indication sur la rédaction
L -> fonction de cout à minimiser.

NN -> neural network, abréviatioon utilisée pour désigner le réseau de neuronne ou le pointeur dessus selon les fonctions.

g -> fonctions d'activation.

df ou dfdx -> dérivé de f (parfois avec précision de la variable).

W -> matrice des poids entre les couches.

b -> matrice des "offsets" entre les couches.

## Bibliographie
[1] _Deep learning for physics research_ de Martin Erdmann, Jonas Glombitza, Gregor Kasieczka, Uwe Klemradt.
