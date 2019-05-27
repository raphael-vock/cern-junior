// Lomàn Vezin & Raphaël Vock
// Projet de Programmation, EPFL BA2, mai 2019

Ce projet porte sur la simulation relativiste d'un accélérateur de particules. Nous l'avons nommé "CERN Junior" en l'honneur du plus grand accélérateur de particules au monde.

Les fichiers |réponses.pdf|, |conception.pdf|, |journal.pdf| (ainsi que leur code source LaTeX si ça intéresse) se trouvent dans |misc|.

Dans ce document nous allons détailler la structure du code source ainsi que le fonctionnement des exécutables.

------------------------------------------------------------------------
0. COMPILATION
------------------------------------------------------------------------

Après s'être placé dans le répertoire |src| du projet dans une session du terminal, la compilation se fait en saisissant la commande suivante (sans le '$') :

$ qmake & make

------------------------------------------------------------------------
1. STRUCTURE DU CODE SOURCE
------------------------------------------------------------------------
En ordre de dépendance, voici les différents modules et leur utilité :

* Le répertoire |general| contient les classes très abstraites liées aux objets et à leur représentation.

* Le répertoire |vector3d| contient la classe Vector3D ainsi que quelques autres classes auxiliaires.

* Le répertoire |physics| contient les classes liés aux particules, aux faisceaux et à la gestion des voisins.

* Le répertoire |accelerator| contient les classes liés aux éléments et à l'accélérateur. Il contient de plus deux namespace utiles : cernjunior qui permet de construire l'accélérateur par défaut que nous avons utilisé dans notre simulateur ; et cli ("command-line interface") qui contient des fonctions utiles à l'interaction avec l'utilisateur via la console.

* Le répertoire |exerciceP12| contient tout un tas de classes liées à la représentation graphique des objets via OpenGL ainsi que les interactions via Qt.

* Le répertoire |consolewidget| contient les classes analogues (mais sensiblement plus simples) pour la représentation textuelle.

* Le répertoire |color| contient la classe RGB qui est sollicitée par les classes Particle et Accelerator

* Le répertoire |misc| contient des namespace contenant des exceptions (excptn)et des constantes : de la simulation (simcst) ainsi que de la physique (phcst)

Les répertoires présents mais non mentionnés ici seront expliqués par la suite.

------------------------------------------------------------------------
2. DISPOSITION DES EXÉCUTABLES
------------------------------------------------------------------------

Après la compilation (cf. 0) et si tout ce passe bien, un certain nombre d'exécutables sera créé :

	* |src/exerciceP12/cern-junior| est le programme graphique : le fruit principal de ce projet. Nous expliquons son fonctionnement dans II.

	* |src/exerciceP10/cern-junior| est l'analogue en "mode texte".

	* Le répertoire |src/tests| contient un certain nombre de tests correspondant à un certain nombre d'exercices :
		- vector_test => exercice P1
		- particle_test => exercice P5
		- accelerator_test => exercice P10

------------------------------------------------------------------------
3. UTILISATION DU PROGRAMME
------------------------------------------------------------------------

Nous allons détailler ici l'utilisation du programme principal (qui, pour rappel, se trouve à l'emplacement |src/exerciceP12/cern-junior|.

1. Vous aurez, en ouvrant le programme, la possibilité de choisir une configuration de particules par défaut ou d'en créer une autre.

1.1. Si vous choisissez la second option, vous pourrez ajouter un nombre arbitraire de faisceaux via la consolele choix du type de particule, leur nombre, leur énergie médiane, la nature de la distribution, les paramètres de la distribution, et enfin le facteur d'agrandissement des macroparticules.

Dès que vous choisirez de ne plus rajouter de faisceau, la simulation sera lancée.

2. Une fois la fenêtre principale ouverte, appuyez deux fois sur la touche espace pour lancer la simulation.

3. Vous serez placé par défaut dans le point de vue libre. Vous pourrez donc changer de position (resp. de point de vue) grâce aux touches W-A-S-D (resp. la souris). Vous pouvez vriller autour d'un axe avec les touches Q-E.

3.1. Vous pouvez changer de point de vue à l'aide des touches 1-2-3.
* La touche 1 correspond au point de vue 1ère personne, qui suit le point de vue d'une particule dans l'accélérateur. Appuyez sur 'W' (resp. S) pour passer à la suivante (resp. précédente).
* La touche 3 correspond au point de vue 3ème personne, qui suivra une particule depuis l'extérieur. Mêmes touches pour changer de particule.
* La touche 2 permet de repasser au point de vue libre.

4. Pour accélérer (resp. décélérer) le pas de la simulation, vous pouvez à tout moment appuyez sur la touche '+' (resp. '-')

5. Pour passez en "mode matrix" et visualiser le fonctionnement de l'octree, appuyer sur la touche 'M'. C'est la même touche pour y ressortir.

6. Bien entendu, on peut quitter le programme à tout moment en faisant Ctrl-W (Windows/Linux) ou Cmd-W (Mac)



***** Une note sur le choix des paramètres ******

Certaines contraintes absolues (e.g. la vitesse de la lumière) pèsent sur le déroulement de la simulation. C'est pourquoi certaines combinaisons de paramètres peuvent mener à des situations surprenantes (e.g. disparition spontannée des particules). Cela s'explique généralement par le fait que la situation en question est non phyique (e.g. facteur gamma imaginaire ou vitesse supérieure à c). Or il est difficile de distinguer a priori les cas où cela peut se produire.

C'est pourquoi dans l'interface de création de faisceaux nous mis des paramètres recommandés qui mènent la plupart du temps à des résultats agréables à l'œil.

*************************************************


Sur ce, bon visionnement !
