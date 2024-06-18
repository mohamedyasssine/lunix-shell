#cmd 
cmd.h:contient les entetes des fonction et la structure de commande qu'est composé de 

  la structure de représentation d'une commande à lancer.

  pid :processus identidier si 0 c'est à dire code unique par chaque processus ce code est 0 si le processus est fils 
      sinon une valeur de processus pére
  status:contient le status de la commande aprés l'execussion si elle est executée avec succée ou pas
  stdin, stdout, stderr:stdin est les descripteur de fichier pour redirection les sorite standard et l'entreé
      standard d'un commande
  wait:variable contient 1 si le programme doit attendre l'execussion de prossecus fils en avant plat ou 0 sinon
  fdclose:tableau des descripteurs de fichier qui indique quelle descripteur doit etre fermé avant d'executer une cmd
  next:pointeur vers prochain commande a executer
  next_success:pointeur vers prochain comande à executer en cas de succées
  next_failure:pointeur vers prochain cmd à executer en cas d'erreur
#cmd.c
#function 
##exec_cmd
execute la commande et faire la redirection des descripteurs si nécessaires 
On crée un nouveau processus, on détourne
  éventuellement les entrée/sorties.
  On conserve le PID dans la structure du processus
  appelant (le minishell).
  On attend si la commande est lancée en "avant-plan"
  et on initialise le code de retour.
  elle prend en paramétre la cmd 
retourne 0 si tous passe bien ou -1 sinon
##init_cmd
permet d'initialiser la structure de commande
elle prend en paramétre la cmd 
retourne 0 si tous passe bien ou -1 sinon
##parse_cmd
int parse_cmd(char* tokens[], cmd_t* cmds, size_t max)
c'est la fonction la plus importante dans le projet
La fonction parse_cmd prend une liste de tokens représentant une ligne de commande et 
génère une liste de structures cmd_t qui représentent les différentes commandes à exécuter, ainsi que leurs paramètres associés.
et changer à chaque fois selon le token la structure de commande associé.
###Paramètres

    tokens[] : Un tableau de chaînes de caractères représentant les tokens de la ligne de commande.
    cmds : Un tableau de structures cmd_t pour stocker les commandes analysées.
    max : La taille maximale des tableaux cmds et tokens.

###Retour

    Retourne le nombre de commandes générées avec succès. En cas d'erreur, retourne -1.
###Détails

    La fonction parcourt la liste de tokens pour créer les structures cmd_t correspondant à chaque commande ainsi que ses paramètres.
    Elle gère les opérateurs de redirection (>, <, 2>, >>, <<, 2>>) en ouvrant les fichiers appropriés et en configurant les descripteurs de fichiers associés.
    Elle prend en charge les opérateurs de contrôle de flux (&&, ||, ;, &) en configurant les liens entre les différentes commandes.
    Les commandes et leurs paramètres sont stockés dans le tableau cmds.
    En cas d'erreur lors de l'ouverture des fichiers de redirection, la fonction affiche un message d'erreur via perror et retourne -1.


