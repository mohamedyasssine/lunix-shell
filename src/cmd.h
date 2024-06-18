/*
  Projet minishell - Licence 3 Info - PSI 2023
 
  Nom :Aloui
  Prénom Mohamed Yassine
  Num. étudiant :23805860 
  Groupe de projet :Binôme 8
  Date :31/10/2023
 
  Gestion des processus.
 
 */
#ifndef PROCESSUS_H_INCLUDED
#define PROCESSUS_H_INCLUDED

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_CMD_SIZE    256

//#include "processus.h"
/*
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
*/
typedef struct cmd_t {
  pid_t pid;
  int status;
  int stdin, stdout, stderr;
  int wait;
  char* path;
  char* argv[MAX_CMD_SIZE];
  int fdclose[MAX_CMD_SIZE];
  struct cmd_t* next;
  struct cmd_t* next_success;
  struct cmd_t* next_failure;
} cmd_t;

/*
  Lancer la commande en fonction des attributs de
  la structure et initialiser les champs manquants.
 
  On crée un nouveau processus, on détourne
  éventuellement les entrée/sorties.
  On conserve le PID dans la structure du processus
  appelant (le minishell).
  On attend si la commande est lancée en "avant-plan"
  et on initialise le code de retour.
  On rend la main immédiatement sinon.
 
  p : un pointeur sur la structure contenant les
      informations pour l'exécution de la commande.
 
  Retourne 0 ou un code d'erreur.
 */

int exec_cmd(cmd_t* p);

  /*
    Initialiser une structure cmd_t avec les
    valeurs par défaut.
  
    p : un pointeur sur la structure à initialiser
  
    Retourne 0 ou un code d'erreur.
  */

  int init_cmd(cmd_t* p);

/*
  Remplit le tableau de commandes en fonction du contenu
  de tokens.
    Ex : {"ls", "-l", "|", "grep", "^a", NULL} =>
         {{path = "ls",
           argv = {"ls", "-l", NULL},
           bg = 1,
           ...},
          {path = "grep",
           argv = {"grep", "^a", NULL},
           bg = 0,
           ...}}
  tokens : le tableau des éléments de la ligne de
           commandes (peut être modifié)
  cmds : le tableau dans lequel sont stockés les
         différentes structures représentant le
         commandes.
  max : le nombre maximum de commandes dans le tableau

  Retourne 0 ou un code d'erreur.
 */
int parse_cmd(char* tokens[], cmd_t* cmds, size_t max);


#endif //PROCESSUS_H_INCLUDED


