Le fichier main.c constitue l'interface principale du minishell. 
Il contient les différentes étapes du traitement des commandes et de leur exécution.
#Description : 
La fonction main est la fonction principale du minishell. Elle implémente la boucle principale qui 
maintient l'exécution du shell et coordonne le traitement des commandes.
##Boucle Principale :

  La boucle while(1) maintient l'exécution du shell jusqu'à ce que l'utilisateur décide de le quitter.
##Prompt :

    Le prompt "$" est affiché pour indiquer que le shell est prêt à accepter une nouvelle commande.
##Lecture de la Ligne de Commande :

    La fonction fgets est utilisée pour lire une ligne de l'entrée standard (clavier) dans le buffer cmdline. 
    La ligne lue est ensuite traitée.
##Traitement de la Ligne de Commande :
 on utilise les fonction des fichier parser.c pour traiter la ligne de command :
 telles que la suppression des espaces inutiles, l'ajout d'espaces autour des opérateurs, la suppression des doublons d'espaces et le traitement des variables d'environnement.
##Découpage de la Ligne :

La fonction strcut est utilisée pour découper la ligne en "mots" (cmdtoks) en
 utilisant un séparateur (par défaut, un espace).
##Traduction en Structures cmd_t :
on utilise parse_cmd de fichier cmd.c
    La fonction parse_cmd traduit les "mots" en structures cmd_t représentant les commandes.
##exécussion de la commande
Exécuter les commandes dans l'ordre en fonction des opérateurs
si la commande est interne on va appeler la fonction builtin de fichier builtin.c
sinon on va appeler la fonction exec_cmd 
#Fin du Programme 

