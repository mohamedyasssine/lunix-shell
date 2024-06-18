#Mini shell 
ce projet est un mini shell contient deux dossier principale:
'src' 
'doc'
##Structure de Projet
-Un sous-dossier 'Src':contient les fichier de code source de projet .h et .c
-Un sous-dossier 'doc':contient la documentation de code
-Un fichier Makefile permettra de le compiler
-Un fichier exemples contenant une liste de commandes testées 
## Utilisation
Pour utiliser le mini shell, suivez ces étapes :
1)décompresser le fichier "shell-Diamanka_Aloui.zip"
2)accéder au répertoire shell-Diamanka_Aloui via votre terminal 
3)exécuter la commande make pour compiler 
4)executer  la commande ./minishell
## Documentation du Codes
- `doc/parser.md`: explique l'objectif  de fichier parser.c et le contenu de ses fonctions.
- `doc/builtin.md`: Explique l'objectif de fichier builtin.c et le contenu de ses fonction 
	et sa relation avec les autre fichier source.
- `doc/cmd.md`: Explique l'objectif de fichier cmd.c et le contenu de ses fonction et sa 
	relation avec les autre fichier source.
- `doc/main.md`: explique le point d'entrée au programme(la boucle principale de shell) 
	et comment on a implementer les fonction des builtin.c,cmd.c et parser.c .
