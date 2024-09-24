// CONSIGNES GLOBALES DU PROJET
//
// Mettre en place une ferme a fourmis : 
// - Composée de différentes 'rooms' entre liés grace a des 'tunnels'.
// - Un 'tunnel' relie deux pièces entre elles, pas plus.
// - Une 'room' peut etre liée a une infinitée d'autre 'rooms', grace a autant de 'tunnels' que nécessaire.
// - Il faut ensuite enterrer la ferme a fourmis, de sorte que les fourmis ne triche pas et ne connaisse pas le 
//   designe de la fourmillière a l'avance.
// - Le but est de mettre en place un "Hex simulator".

// OBJECTIFS :
// - Le programme recevra les données décrivant la fourmillière via l'outut standard dans le format suivant : 
//       number_of_ant
//       the_rooms
//       the_links
// - Une fourmillière est définie par les liens suivants : 
//       ##start
//       1 23 3
//       2 16 7
//       #comment
//       3 16 3
//       4 16 5
//       5 9 3
//       6 1 5
//       7 4 8
//       ##end
//       0 9 5
//       0-4
//       0-6
//       1-3
//       4-3
//       5-2
//       3-5
//       #another comment  
//       4-2
//       2-1
//       7-6
//       7-2
//       7-4
//       6-5
//       #another comment
//
// Ce qui correspond a la représentation suivante : 
//
//            _ _ _ _ _ _ _ _
//           /                \
//   ------[5]----[3]----[1]   |
//  /                     /    |
// [6]-----[0]------[4]  /     |
//  \     _ _ _ _ _/ |  /      |
//   \   /          [2]/_ _ _ /
//    [7] _ _ _ _ _ /
//
// Il y a deux parties : 
// - Les 'rooms' définies par -> " name coord_x coord_y "
// - Les 'tunnels' définis par -> " name1-name2 "
// - Le tout peut etre coupé par des commentaires, commencant par '#'
//
// ATTENTION: Les noms des 'rooms' ne sera pas forcément un nombre, et ils ne seront pas forcément triés
//            Le nom d'une 'room' ne commencera jamais avec la lettre 'L' ni un '#'
//            Les coordonnées des 'rooms' seront toujours des int
//
// Les lignes qui commencent par '##' sont des commandes modifiant les propriétés de la ligne venant juste après
// Par exemple, '##start' donnera la position de l'entrée et '##end' celles de la sortie.
// ATTENTION: Toute commande non reconnue sera ignorée
// 
// Toute ligne ne respecant pas les consignes ou les lignes vides stopera automatiquement la lecture de la fourmillière
// ainsi que l'exécution du programme.
//
// Si il n'y a pas assez de données pour mettre en place la fourmillière il faut afficher 'ERROR'
//
// CONSIGNES GENERALE : 
// - L'exécutable devra s'appeller 'lem-in'
// - Il faut remettre un makefile. Ce makefile doit compiler tout le projet et doit contenir les regles habituelles.
// - Il est possible d'inclure sa propre libft, compilée via son propre makefile a la racine du projet. Le makefile du programme
//   devra mettre en place la libft avant de s'exécuter.
// - Le projet doit etre écrit en C
// - Il faut supporter les erreurs de manière dite 'sensitive'. Le programme ne peut pas quitter de manière inattendue. (Seg fault, bus error, double free, ...)
// - Il ne peut pas y avoir de leaks
// - Dans la partie mandatory, les fcts suivantes sont permises : 
//       - malloc
//       - free
//       - read
//       - write
//       - strerror
//       - perror
//       - exit
//
// - Il est permit d'utiliser d'autres fonctions pour gérer la partie bonus si celle ci sont justifiées durant la corrections
//
// MANDATORY PART:
// - L'objectif est de trouver le chemin le plus rapide pour faire sortir 'n' fourmis de la fourmillière
// - Le plus rapide signifie le chemin avec le moins de nombre de lignes, respectant le format d'output demandé plus bas
// - Il y a quelques contraintes, Pour arriver en premier, les fourmis devront prendre le chemin le plus court (pas forcement le plus simple)
//   Elles devront également éviter les embouteillages ainsi que de marcher sur leurs freres et soeurs.
// - Au départ, toute les fourmis se trouve a la case '##start', elles doivent rejoindre la case '##end' en un nombre de tour le plus faible possible
//   Chaque 'room' ne peut contenir qu'une seule fourmie (exepté ##start et ##end)
// - On concidère que toute les fourmis démarre du point '##start'
// - A chaque tour, on affiche uniquement les fourmies qui se sont déplacées.
// - A chaque tour, on ne peut déplacer qu'une fois chaque fourmies et au travers d'un 'tunnel' (La 'room' aqueilant une fourmie doit être vide)
// - Il faut display le résultat dans l'output standard au format suivant : 
//       number_of_ants
//       the_rooms
//       the_links
//
//       Lx-y Lz-w Lr-o ...
//
//  'x', 'z' et 'r' représente le numero des fourmies (allant de 1 a number_of_ants) et 'y', 'w' et 'o' représente les noms des 'rooms'
// - L'algorithme doit être capable d'utiliser la meilleur combinaison de chemin en accord avec le nombre de fourmies comme dans l'exemple 3
// - L'algorithme dois procèder dans un temps raisonnable, même dans le cas ou il y aurait 4000 rooms.
//   2-3 seconde est parfait, 9 secondes est moyen, 15 seconde est bien trop.
// De ce fait, la lecture et l'écriture des données doit être fait de manière otpimale
// 
// PARTIE BONUS : 
// - Mettre en place un visualizer de la fourmillière 
// - Peut etre fait en 2D (vu du dessus) ou en 3D sur base de la perspective d'une fourmie dans les tunnels
// Pour l'utiliser, il est possible d'écrire : ./lem-in < ant_farm_map.txt | ./visu-hex
// - Les coordonnées des rooms ne seront utile que dans ce cas. 

#include "Libft/libft.h"
#include <stdio.h>

#include "includes/parse_file.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    char **parsed_map;
    int line_count = 0;
    parsed_map = parse_map(&line_count);
    (void)parsed_map;
    // Afficher contenu de parsed_file
    // for (int i = 0; i < line_count; i++) {
    //    printf("Ligne %d : %s\n", i + 1, parsed_map[i]);
    // }

    free_parsed_map(parsed_map, line_count);
}