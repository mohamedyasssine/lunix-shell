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

int trim(char* str) {// retourne 1 si bien 0 sinon
  if (!str)
    return 0;
  int taille=strlen(str);
  if(!taille)
    return 0;
  while(taille>0 && str[taille-1]==' ')
  {
    str[taille-1]='\0';
    taille--;
  }
  int debut=0;
  while(str[debut]==' ' && debut<taille)
    debut++;

  if(debut==taille) 
    str[0]='\0';
  else{
    if(debut>0){
      for (int i = 0; i < taille; i++)
        str[i]=str[i+debut];

      str[taille-debut]='\0';
    }
  } 
  return 1;   
}

int clean(char* str) {// retourne 1 si bien 0 sinon
  if(!str)
    return 0;
  int taille=strlen(str);
  if(!taille)
    return 0;
  int i,j;
  for (i = 0, j = 0; i < taille; i++)
  {
    if (str[i]!=' ' || (i>0 && str[i-1]!=' '))
    {
      str[j]=str[i];
      j++;
    }
  }
  str[j]='\0';

  return 1;
}

int separate_s(char* str, char* s, size_t max) {
  int taille_str=strlen(str) ;
  int taille_s=strlen(s);

  if(taille_str>max)
    return 0;
  char* tpm=malloc(max);
  int ind_tpm=0;
  char c;
  if(!tpm)
    return 0;
  for (int i = 0; i < taille_str; i++)
  {
    if(ind_tpm+1 > max )
      return 0;

    c=str[i];
    if (strchr(s,c))
    {
      if(i==0)
      {
        if(c!=str[i+1])
        {
          tpm[ind_tpm++]=c;
          tpm[ind_tpm++]=' ';
        }else
          tpm[ind_tpm++]=c;
      }
      else
      { 
        if(i==taille_str-1)
          if (str[i-1]!=' ' && c!=str[i-1])
          {
            tpm[ind_tpm++]=' ';
            tpm[ind_tpm++]=c;
          }
          else
            tpm[ind_tpm++]=c;
        else{
          if (str[i-1]==' ' && str[i+1]==' ')
          {
            tpm[ind_tpm++]=c;
          }else
          {
            if(str[i-1]==' ' ){
              if(c!=str[i+1])
              {
                tpm[ind_tpm++]=c;
                tpm[ind_tpm++]=' ';
              }else
                tpm[ind_tpm++]=c;
            }
            else{
              if (str[i+1]==' ')
              {
                if(c!=str[i-1])
                {
                  tpm[ind_tpm++]=' ';
                  tpm[ind_tpm++]=c;
                }
                else
                  tpm[ind_tpm++]=c;
              }
              else{
                if(c!=str[i+1] && c!=str[i-1])
                {
                  tpm[ind_tpm++]=' ';
                  tpm[ind_tpm++]=c;
                  tpm[ind_tpm++]=' ';
                }
                else{
                  if(c==str[i+1])
                  {
                    tpm[ind_tpm++]=' ';
                    tpm[ind_tpm++]=c;
                  }
                  else
                  {
                    tpm[ind_tpm++]=c;
                    tpm[ind_tpm++]=' ';
                  }
                }
              }
            }
          }
        }  
      }
    }
    else
      tpm[ind_tpm++]=c;
  }
  tpm[ind_tpm++]='\0';
  strcpy(str,tpm);
  free(tpm);

  return 1;
}

int substenv(char* str, size_t max) {

  char* dollar_sign = str;
  char* var_start; 
  char* var_end; 
  while ((dollar_sign = strchr(dollar_sign, '$')) != NULL) {
    var_start = ++dollar_sign;

    // Recherche de la fin du nom de la variable
    var_end = var_start;
    while (*var_end != ' ' &&  *var_end!='\0'){
      var_end++;
    }
    if (var_end!=var_start)
    {
      // on creer une chaine tampon
      int taille_tmp=var_end - var_start;
      char tmp[taille_tmp + 1];

      strncpy(tmp,var_start,taille_tmp);
      tmp[taille_tmp+1]='\0';
      char* valeur=getenv(tmp) ;
      if (valeur !=NULL)
      {
        // Remplacement de la variable d'environnement dans la chaîne
        int taille_valeur= strlen(valeur);
        int replacement = taille_valeur < (max - (var_start - str)) ? taille_valeur : (max - (var_start - str));
        // Décalage du reste de la chaîne
        int remaining = strlen(var_end);
        if (remaining > replacement) {
            memmove(var_start + replacement, var_end, remaining+1);
        }
        strncpy(var_start-1, valeur, replacement);
      }
    }
    if (strlen(str) >= max) {
      str[max] = '\0';
    }
  }
  return 0;  
}

int strcut(char* str, char sep, char** tokens, size_t max) {
  int compteur = 0;  // Compteur de mots
  char* token = strtok(str, &sep);
  
  // Parcours de la chaîne en utilisant strtok
  while (token != NULL && compteur < max-1) {
    tokens[compteur++] = token;
    token = strtok(NULL, &sep);
  }
  // Si max n'est pas atteint, le dernier élément est NULL
  tokens[compteur] = NULL;
  
  return compteur;
}

// Optionnel
int strcut_s(char* str, char sep, char** tokens, size_t max) {
  int compteur = 0;  // Compteur de mots
    char* token = strtok(str, "\'\"");
    
    // Parcours de la chaîne en utilisant strtok
    while (token != NULL && compteur < max-1) {
      if (strcmp(token,".")!=0)
      {
        tokens[compteur] = token;
      }
      token = strtok(NULL, "\'\"");
      compteur++;
    }
    // Si max n'est pas atteint, le dernier élément est NULL
    tokens[compteur] = NULL;
    
    return compteur;
}
