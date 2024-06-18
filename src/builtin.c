/*
  Projet minishell - Licence 3 Info - PSI 2023
  Nom :Aloui
  Prénom :Mohamed Yassine
  Num. étudiant :23805860 
  Groupe de projet :Binôme 8
  Date :31/10/2023
  Gestion des commandes internes du minishell (implémentation).
 */
//la fonction is_builtin va comparer à chaque fois la commande avec les commande interne s'il est l'un des cmd interne il retourne 1
#include "builtin.h"


extern char** environ;
int is_builtin(const char* cmd) {
  if(strcmp(cmd,"export")==0||strcmp(cmd,"exit")==0||strcmp(cmd,"cd")==0||strcmp(cmd,"pwd")==0)
  {
    return 1;
  }
  return 0;
}

int builtin(cmd_t* cmd) {
  int retur=0;
  if(cmd==NULL)
    return -1;
  if(strcmp(cmd->path,"cd")==0)
  {
    if (cmd->argv[1] != NULL) {
      retur=cd(cmd->argv[1], cmd->stderr);
    }
  }else 
    if(strcmp(cmd->path,"export")==0)
    {
      if(cmd->argv[1]!=NULL&&cmd->argv[2]!=NULL)
      {
        retur=export(cmd->argv[1],cmd->argv[2],cmd->stderr);
      }
    }else 
      if(strcmp(cmd->path,"exit")==0)
      {
        if(cmd->argv[1]!=NULL){
          int argentier = atoi(cmd->argv[1]); //convertir l'argument en entier
          retur=exit_shell(argentier, cmd->stderr);//execussion de la fonction 
        }else
        {
          retur=exit_shell(1, cmd->stderr);
        }
      }else 
        if(strcmp(cmd->path,"pwd")==0)
        {
          pwd();
        }else 
          if(strcmp(cmd->path,"env")==0)
          {
            env();
          }
          else
          if(strcmp(cmd->path,"unset")==0)
          {
            unset(cmd->argv[1]);
          }
          else
            {
              printf("commande interne  inconnu\n");
              return -1;
            }

  return retur;
}

int cd(const char* path, int fderr) {
    if(path==NULL)
    {
        dprintf(fderr, "Erreur ,il manque le chemin \n");
        return -1;
    }
    if (chdir(path)!=0) {
        if(write(fderr, "Erreur de changement de répertoire", strlen("Erreur de changement de répertoire"))==0)
          perror("probleme\n");
        return -1;
    } 
    return 0;//réussir à changer le répertoir     
}

int export(const char* var, const char* value, int fderr) {
    if(var==NULL)
    {
        dprintf(fderr, "manque de la variable à exporter .\n");
    }
    else if (value==NULL)
    {
      dprintf(fderr,"manque la la valeur");
    }
    if(setenv(var,value,1)==0)//ajout de variable d'environement a reussi 
    {
        return 0;
    }
    else
    {
        dprintf(fderr, "erreur d'ajout de %s.\n", var);
        return -1;
    }
}
int exit_shell(int ret, int fderr) {
    
     if (ret >= 0) {
        if (fderr != STDERR_FILENO) {
            if (dup2(fderr, STDERR_FILENO) == -1) {
                perror("impossible de redirectionner la sortie standar");
                return -1; // Code d'erreur
            }
        }
        exit(ret); // Terminer le programme avec le code de retour 
       
    } else {
        exit(0);
    }
}
int unset(const char* var)
{
  if(var==NULL)
  {
    dprintf(1, "manque de la variable à supprimer .\n");
    return -1;
  }
  unsetenv(var);
  return 0;
}
void pwd()
{
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Répertoire courant : %s\n", cwd);
  } else 
      perror("Erreur lors de la récupération du répertoire courant");
  
}

void env()
{
  char* env_var;
  int index = 0;
  while ((env_var = environ[index]) != NULL) {
    printf("%s\n", env_var);
    index++;
  }
}
