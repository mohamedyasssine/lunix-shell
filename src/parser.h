/*
  Projet minishell - Licence 3 Info - PSI 2023
 
  Nom :Diamanka
  Prénom :Mamadou
  Num. étudiant :22312921
  Groupe de projet :binome 8
  Date :31/10/2023
 
  Parsing de la ligne de commandes utilisateur (implémentation).
 
 */
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_LINE_SIZE   1024
#define MAX_CMD_SIZE    256

/*
  Voir le TP sur les chaînes de caractères.
  Commentaires à compléter.
*/
/*Prend en parametre une chaine de caractere et 
  elimine tous les espaces au debut et a la fin de celle-ci

  str:est la chaine de caractere
*/  
int trim(char* str);

/*Prend en parametre une chaine de caractere et 
  elimine tous les doublons d'espaces dans celle-ci
*/
int clean(char* str);

/* prend en paramètre une chaîne de caractères et ajoute 
  des espaces autour de toutes les occurrences des 
  caractères d'une chaîne lorsqu'il n'y a pas d'espace et sans 
  ajouter d'espace au début ou à la fin. Une taille maximale est 
  également passée, l'opération arrête avant que la capacité soit dépassée
*/
int separate_s(char* str, char* s, size_t max);

/*prend en paramètre une chaine de caractères et remplace les mots du type 
$NOM ou ${NOM} par la variable d’environnement de nom correspondant si elle 
existe. Si elle n’existe pas, la substitution n’est pas effectuée. Une taille 
maximale est également passée, la chaîne finale ne dépassera pas cette taille(\0 compris)
*/
int substenv(char* str, size_t max);

/* 
prend en paramètre une chaine de caractère  et un tableau de chaines et qui découpe
la chaine sur un caractère choisi en ses différents « mots » dans un tableau 
de chaînes terminé par NULL. Une taille maximale est passée, l'opération s'arrête lorsqu'elle est atteinte
(NULL compris). La fonction renvoie le nombre de mots.
*/
int strcut(char* str, char sep, char** tokens, size_t max);

// Optionnel
/* modifiée de la fonction strcut qui découpe en un seul mot 
tous les caractères situés entre " ou '.
*/
int strcut_s(char* str, char sep, char** tokens, size_t max);


#endif //PARSER_H_INCLUDED
