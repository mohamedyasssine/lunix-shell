/*
  Projet minishell - Licence 3 Info - PSI 2023
 
  Nom :Diamanka
  Prénom :Mamadou
  Num. étudiant :22312921
  Groupe de projet :binome 8
  Date :31/10/2023
 
  Parsing de la ligne de commandes utilisateur (implémentation).
 
 */
#include "parser.h"
#include "cmd.h"
#include "builtin.h"

int main(int argc, char* argv[]) {
  char cmdline[MAX_LINE_SIZE]; // buffer des lignes de commandes
  char* cmdtoks[MAX_CMD_SIZE]; // "mots" de la ligne de commandes
  cmd_t cmds[MAX_CMD_SIZE];
  cmd_t* current;
  int nb_cmd;
  char sep=' ';

  while (1) {

    // Effacer les contenus de cmdline, cmdtoks et cmds
    memset(cmdline,0,sizeof(cmdline));
    
    // Initialiser les valeurs par défaut dans cmds (stdin, stdout, stderr, ...)
    for (int i = 0; i < MAX_CMD_SIZE; ++i)
    {
      init_cmd(&cmds[i]);
      cmdtoks[i]=NULL;
    }
    // Afficher un prompt
    printf("$ ");
    
    // Lire une ligne dans cmdline - Attention fgets enregistre le \n final
    if (fgets(cmdline, MAX_LINE_SIZE, stdin)==NULL) break;
    cmdline[strlen(cmdline)-1]='\0';
    
    // Traiter la ligne de commande
    //   - supprimer les espaces en début et en fin de ligne
    trim(cmdline);

    //   - ajouter d'éventuels espaces autour de ; ! || && & ...
    separate_s(cmdline,";|&<>=", MAX_LINE_SIZE);

    //   - supprimer les doublons d'espaces
    clean(cmdline);

    //   - traiter les variables d'environnement
    substenv(cmdline,MAX_LINE_SIZE);
    
    // Découper la ligne dans cmdtoks
    strcut(cmdline,sep, cmdtoks, MAX_CMD_SIZE);
    // Traduire la ligne en structures cmd_t dans cmds
  
    nb_cmd=parse_cmd(cmdtoks,cmds, MAX_CMD_SIZE);
    // Les commandes sont chaînées en fonction des séparateurs
    //   - next -> exécution inconditionnelle
    //   - next_success -> exécution si la commande précédente réussit
    //   - next_failure -> exécution si la commande précédente échoue

    // Exécuter les commandes dans l'ordre en fonction des opérateurs
    // de flux
    current=cmds;
    for (int i = 0; i < nb_cmd; ++i)
    {
      // Lancer la commande
      if (current)
      {
        if (is_builtin(current->path))
          builtin(current);
        else
          exec_cmd(current);
      }
      //traitement des next
      current++;
    }
  }
  fprintf(stderr, "\nGood bye!\n");

  return 0;
}
