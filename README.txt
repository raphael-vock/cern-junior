// Lomàn Vezin & Raphaël Vock
// Projet de Programmation, EPFL BA2, mai 2019

Ce projet porte sur la simulation relativiste d'un accélérateur de particules. Nous l'avons nommé "CERN Junior" en l'honneur du plus grand accélérateur de particules au monde.

Les fichiers |REPONSES.PDF|, |CONCEPTION.pdf|, |JOURNAL.pdf|, (ainsi que leur code source LaTeX si ça intéresse) et le fichier |TODO.txt| achevé se trouvent dans |misc|.

Dans ce document nous allons détailler la structure du code source ainsi que le fonctionnement des exécutables.

------------------------------------------------------------------------
0. COMPILATION
------------------------------------------------------------------------

Après s'être placé dans le répertoire |src| du projet dans une session du terminal, la compilation se fait en saisissant la commande suivante (sans le '$') :

$ qmake & make

**** Erreur de linker sur les machines du CO ***

À cause du linker « archaïque » présent dans les machines du CO, la compilation des modules |particle_test| et |cern-junior-cpp| provoquent des erreurs de linker qui nous demeurent à ce jour mystérieux. Par défaut nous ne les incluons donc pas dans compilation, mais nous avons laissé le code source ainsi que des captures d'écran de leur fonctionnement sur des machines plus compétentes. Nous nous désolons de ne pas avoir réglé le problème mais nous insistons bien sur le fait que c'est a priori une erreur lié à la plateforme et non au code/conception.

*************************************************


------------------------------------------------------------------------
1. STRUCTURE DU CODE SOURCE
------------------------------------------------------------------------
En ordre de dépendance, voici les différents modules et leur utilité :

* Le répertoire |general| contient les classes très abstraites liées aux objets et à leur représentation.

* Le répertoire |vector3d| contient la classe Vector3D ainsi que quelques autres classes auxiliaires.

* Le répertoire |physics| contient les classes liées aux particules, aux faisceaux et à la gestion des voisins, aux éléments, à l'accélérateur. Il contient de plus deux namespace utiles : cernjunior qui permet de construire l'accélérateur par défaut que nous avons utilisé dans notre simulateur ; et cli ("command-line interface") qui contient certaines fonctions sollicités lors de l'interaction avec l'utilisateur via la console.

* Le répertoire |exerciceP12| contient tout un tas de classes liées à la représentation graphique des objets via OpenGL ainsi que les interactions via Qt.

* Le répertoire |consolewidget| contient les classes analogues (mais sensiblement plus simples) pour la représentation textuelle.

* Le répertoire |color| contient la classe RGB qui est sollicitée par les classes Particle et Accelerator.

* Le répertoire |misc| contient des namespace contenant des exceptions (excptn) et des constantes : de la simulation (simcst) ainsi que de la physique (phcst).

Les répertoires présents mais non mentionnés ici seront expliqués par la suite.


------------------------------------------------------------------------
2. DISPOSITION DES EXÉCUTABLES
------------------------------------------------------------------------

Après la compilation (cf. 0) et si tout ce passe bien, un certain nombre d'exécutables sera créé :

	* |src/exerciceP12/cern-junior| est le programme graphique : le fruit principal de ce projet. Nous expliquons son fonctionnement dans la partie suivante.

	* |src/cern-junior-text/cern-junior-text| est l'analogue en "mode texte".

	* Le répertoire |src/tests| contient un certain nombre de tests correspondant à un certain nombre d'exercices :

		- vector_test => exercice P1
		- particle_test => exercice P5 (voir note plus haut sur sa compilation)
		- accelerator_test => exercice P10

------------------------------------------------------------------------
3. UTILISATION DU PROGRAMME
------------------------------------------------------------------------

Pour avoir accès à toutes les fonctionnalités du programme principal, il faut le lancer depuis le terminal (et non depuis l'IDE Qt). On pourra saisir, par exemple, les commandes

$ cd src/exerciceP12
$ ./cern-junior

1. Vous aurez, en ouvrant le programme, la possibilité de choisir une configuration de particules par défaut ou de créer la vôtre.

1.1. Si vous choisissez la seconde option, vous pourrez ajouter un nombre arbitraire de faisceaux via la console, puis vous aurez le choix du type de particule, de leur nombre, la nature de leur distribution, les paramètres de la distribution, et enfin le facteur d'agrandissement des macro-particules.

(Rappelons ici que sur les machines du CO il vaut mieux être très conservateur sur le nombre total de particules (≤ 10), bien cela ne représente pas les performances du programme sur un ordinateur générique.)

Dès que vous choisirez de ne plus rajouter de faisceau, vous aurez la possibilité de voir une liste des commandes, en français ou en anglais.

2. Une fois la fenêtre graphique ouverte, la simulation sera lancée.

3. Vous serez placé par défaut dans le point de vue libre. Vous pourrez donc changer de position (resp. de perspective) à l'aide des touches W-A-S-D (resp. la souris + clic gauche). Vous pouvez vriller autour d'un axe avec les touches 'Q' et 'E'.

3.1. Vous pouvez changer de point de vue à l'aide des touches 1-2-3 :

* La touche '1' correspond au point de vue 1ère personne, qui suit le point de vue d'une particule dans l'accélérateur. Appuyez sur 'W' (resp. 'S') pour passer à la suivante (resp. précédente).
* La touche '3' correspond au point de vue 3ème personne, qui suivra une particule depuis l'extérieur. Mêmes touches que ci-dessus pour changer de particule.
* La touche '2' permet de repasser au point de vue libre.

4. Pour accélérer (resp. décélérer) le pas de la simulation, vous pouvez à tout moment appuyez sur la touche '+' (resp. '=')

5. Pour entrer/sortir du "mode matrix" (qui permet de visualiser le fonctionnement de l'octree), appuyer sur la touche 'M'.

6. Quittez le programme à tout moment en faisant Ctrl-W (Windows/Linux) ou Cmd-W (Mac).
