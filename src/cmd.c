/*
  Projet minishell - Licence 3 Info - PSI 2023
 
  Nom :
  Prénom : 
  Num. étudiant : 
  Groupe de projet : 8
  Date :
 
  Gestion des processus(implementation)
 
 */
#include "cmd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int exec_cmd(cmd_t* p) {

  pid_t pid_fils = fork();
  if (pid_fils == 0)
  {
      //p->pid=getpid();
      if (p->stdin != STDIN_FILENO) { //stdin_fileno est le descripteur standars pour l'entrée standard stdin
        if (dup2(p->stdin, STDIN_FILENO) == -1) { //redirection de descripteir entrée standard sion generer erreur avec la code dup2
            perror("Erreur sur la duplication de STDIN_FILENO"); 
            exit(EXIT_FAILURE);
        }
        close(p->stdin);
        //et dans le cas dune pipe
      }
      if (p->stdout != STDOUT_FILENO) {  //stdout_fileno est le descripteur standard pour la sortie standard stdout
        if (dup2(p->stdout, STDOUT_FILENO) == -1) {//redirection de descripteir sortie standard sinon generer erreur avec la code dup2
            perror("Erreur sur la duplication de STDOUT_FILENO");  
            exit(EXIT_FAILURE);
        }
        close(p->stdout);
      }
      if (p->stderr != STDERR_FILENO) { //sterr_fileno est le descripteur standars pour la sortie standard des erreurs sterrr
        if (dup2(p->stderr, STDERR_FILENO) == -1) { //redirection du descripteur sortie d'erreur sinon generer erreur avec la code dup2
            perror("Erreur sur la duplication de STDERR_FILENO");
            exit(EXIT_FAILURE);
        }
        close(p->stderr);
      }
      if(execvp(p->path,p->argv)==-1) 
        p->status=-1;
  }
  else 
  {
    if (!p->wait) { //tester si le processus est en avant plan le prossessus pére va attendre
      int status;
      if (wait(&status)==-1){
        perror("waitpid");
        return -1; //Erreur lors de l'attente pour que le prossecus en avant plant compléte
      }
    }
  }
    //*la fermeture des descripteurs
  int i=0;
  while(i<MAX_CMD_SIZE && p->fdclose[i]!=-1){
    close(p->fdclose[i++]);
  }
  /*les next next_success et next_failure c'est leurs leurs traitements dans la fonction 
    de exec_cmd et surtout je pense en fonction de la valeur de status*/
  if(p->status==-1)
  {
    p->next_success=NULL;
  }
  else{
    p->next_failure=NULL;
  }

  return 0;
}

int init_cmd(cmd_t* p) {
    if (p == NULL) {
        return -1;
    }
    //initialisation des 
    p->pid = -1;
    p->status = 0;
    p->stdin = STDIN_FILENO;
    p->stdout = STDOUT_FILENO;
    p->stderr = STDERR_FILENO;
    p->wait=0;//arriere ou avant avec la valeur 0 car la valeur par defaut est avant plan
    p->path = NULL;
    p->next = NULL;
    p->next_failure = NULL;
    p->next_success = NULL;
    for (int i = 0; i < MAX_CMD_SIZE; i++) { //cette loop sert à initialiser les argument de commande et sert à initialiser les tableau de descripteur
        p->argv[i] = NULL;
        p->fdclose[i] = -1;
    }
   return 0;
}

/*la faut etre tres serieux car c'est le moteur du projet*/
int parse_cmd(char* tokens[], cmd_t* cmds, size_t max) {
 int idx_tok=0;
 int idx_proc=0;
 int idx_arg=0;
 int idx_fd=0;

 while(idx_tok<max && tokens[idx_tok]!=NULL)
 {
    cmds[idx_proc].path=(char*)malloc(strlen(tokens[idx_tok])+1);
    strcpy(cmds[idx_proc].path,tokens[idx_tok++]);
    idx_fd=0;
    idx_arg=0;
    cmds[idx_proc].argv[idx_arg]=(char*)malloc(strlen(tokens[idx_tok-1])+1);
    strcpy(cmds[idx_proc].argv[idx_arg++],tokens[idx_tok-1]);
    
    while(idx_tok<max && tokens[idx_tok]!=NULL)
    {
      if(strcmp(tokens[idx_tok],";")==0)
      {
          cmds[idx_proc].next=&cmds[idx_proc];
          break;
      }else
      {
        if(strcmp(tokens[idx_tok],"&")==0){
            cmds[idx_proc].wait=1;
            break;
        }
        else
        {
          if(strcmp(tokens[idx_tok],">")==0){
              cmds[idx_proc].stdout=open(tokens[++idx_tok], O_WRONLY|O_CREAT|O_TRUNC,0644);
              if(cmds[idx_proc].stdout==-1)     
              {
                  perror("Probreme de redirection\n");
                  return -1;    
              }
              cmds[idx_proc].fdclose[idx_fd++]=cmds[idx_proc].stdout;
          }
          else
          {
            if(strcmp(tokens[idx_tok],"<")==0)
            {
                cmds[idx_proc].stdin=open(tokens[++idx_tok], O_RDONLY,0644);
                if(cmds[idx_proc].stdin==-1)     
                {
                    perror("Probreme de redirection\n");
                    return -1;    
                }
                cmds[idx_proc].fdclose[idx_fd++]=cmds[idx_proc].stdin;
            }
            else
            {  
              if(strcmp(tokens[idx_tok],"2>")==0){
                  cmds[idx_proc].stderr=open(tokens[++idx_tok], O_WRONLY | O_CREAT | O_TRUNC,0644);
                  if(cmds[idx_proc].stderr==-1)     
                  {
                      perror("Probreme de redirection\n");
                      return -1;    
                  }
                  cmds[idx_proc].fdclose[idx_fd++]=cmds[idx_proc].stderr;
              }
              else 
              {   
                if(strcmp(tokens[idx_tok],">>")==0){
                    cmds[idx_proc].stdout=open(tokens[++idx_tok], O_WRONLY | O_APPEND | O_CREAT ,0644);
                    if(cmds[idx_proc].stdout==-1)     
                    {
                        perror("Probreme de redirection\n");
                        return -1;    
                    }
                    cmds[idx_proc].fdclose[idx_fd++]=cmds[idx_proc].stdout;
                }
                else
                {  
                  if(strcmp(tokens[idx_tok],"<<")==0){//pas bon
                      cmds[idx_proc].stdin=open(tokens[++idx_tok], O_WRONLY | O_APPEND | O_CREAT ,0644);
                      if(cmds[idx_proc].stdin==-1)     
                      {
                          perror("Probreme de redirection\n");
                          return -1;    
                      }
                      cmds[idx_proc].fdclose[idx_fd++]=cmds[idx_proc].stdin;
                  }
                  else
                  {
                    if(strcmp(tokens[idx_tok],"2>>")==0){
                        cmds[idx_proc].stderr=open(tokens[++idx_tok], O_WRONLY | O_APPEND| O_CREAT ,0644);
                        if(cmds[idx_proc].stderr==-1)     
                        {
                            perror("Probreme de redirection\n");
                            return -1;    
                        }
                        cmds[idx_proc].fdclose[idx_fd++]=cmds[idx_proc].stderr;
                    }
                    else
                    {
                      if(strcmp(tokens[idx_tok],"&&")==0)
                      {
                          cmds[idx_proc].next_success=&cmds[idx_proc+1];
                          break;
                      }
                      else
                      {
                        if(strcmp(tokens[idx_tok],"||")==0)
                        {
                            cmds[idx_proc].next_failure=&cmds[idx_proc+1];
                            break;
                        }
                        else
                        {
                          if(strcmp(tokens[idx_tok],"|")==0)
                          {
                              int tube[2];
                              if(pipe(tube)==-1){
                                  perror("Probleme de redirection");
                                  return -1;
                              }
                              cmds[idx_proc].stdout=tube[1];
                              cmds[idx_proc].fdclose[idx_fd++]=tube[1];
                              cmds[idx_proc+1].stdin=tube[0];
                              cmds[idx_proc+1].fdclose[idx_fd++]=tube[0];
                              //y'a til pas des chose a fermer
                              break;
                          }
                          else
                          {
                            if(strcmp(tokens[idx_tok],"=")==0)
                            {
                              cmds[idx_proc].argv[idx_arg]=(char*)malloc(strlen(tokens[++idx_tok])-1);
                              strncpy(cmds[idx_proc].argv[idx_arg++],tokens[idx_tok]+1,strlen(tokens[idx_tok])-2);
                            }
                            else
                            {
                              //les arguments de de la commandes
                              cmds[idx_proc].argv[idx_arg]=(char*)malloc(strlen(tokens[idx_tok])+1);
                              strcpy(cmds[idx_proc].argv[idx_arg++],tokens[idx_tok]);
                            }
                          } 
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      idx_tok++;                                        
    }
    idx_tok++;
    idx_proc++;
  }
  return idx_proc;
}
