#Parser.C 

La fichier parser.c a pour but de: 

traiter la ligne de commande entrée par l'utilisateur 

la découper en "mots" (tokens) 

préparer les structures de données nécessaires pour exécuter les commandes spécifiées. 

#Functions 

##fonction trim  

int trim(char* str) 

  

La fonction trim élimine les espaces au début et à la fin d'une chaîne de caractères. 

###Paramètres 

str : La chaîne de caractères à traiter. 

  

###Retour 

Retourne 1 si l'opération s'est déroulée avec succès, 0 sinon. 

##fonction clean 

int clean(char* str) 

  

La fonction clean élimine les doublons d'espaces dans une chaîne de caractères. 

###Paramètres 

str : La chaîne de caractères à traiter. 

###Retour 

Retourne 1 si l'opération s'est déroulée avec succès, 0 sinon. 

##fonction seperate 

int separate_s(char* str, char* s, size_t max) 

  

La fonction separate_s ajoute d'éventuels espaces autour de certains caractères spéciaux dans la ligne de commande. 

##Paramètres 

	str : La chaîne de caractères à traiter. 

	s : La chaîne spécifiant les caractères autour desquels des espaces doivent être ajoutés. 

	max : La taille maximale de la chaîne résultante. 

  

###Retour 

	Retourne 1 si l'opération s'est déroulée avec succès, 0 sinon. 

##fonction substenv  

int substenv(char* str, size_t max) 

La fonction substenv traite les variables d'environnement dans la ligne de commande. 

prend en paramètre une chaine de caractères et remplace les mots du type  

$NOM ou ${NOM} par la variable d’environnement de nom correspondant 

###Paramètres 

    str : La chaîne de caractères à traiter. 

    max : La taille maximale de la chaîne résultante. 

  

###Retour 

    Retourne 1 si l'opération s'est déroulée avec succès, 0 sinon. 

##fonction strcut 

La fonction strcut découpe la ligne de commande en tokens en utilisant un séparateur . 

##Paramètres 

  

    str : La chaîne de caractères à découper. 

    sep : Le séparateur à utiliser. 

    tokens : Un tableau de chaînes pour stocker les mots découpés. 

    max : La taille maximale du tableau de chaînes. 

  

##Retour 

    Retourne le nombre de mots découpés. 

##fonction strcut_s 

int strcut_s(char* str, char sep, char** tokens, size_t max) 

  

La fonction strcut_s est une version optionnelle de strcut qui gère les quotes simples et doubles. 

##Paramètres 

    str : La chaîne de caractères à découper. 

    sep : Le séparateur à utiliser. 

    tokens : Un tableau de chaînes pour stocker les mots découpés. 

    max : La taille maximale du tableau de chaînes. 

##Retour 

    Retourne le nombre de mots découpés. 

#Remarque 

ces fonctions vont être utilisées dans la main pour modifier directement les chaines de caractère passée en paramètre (les commande) 

