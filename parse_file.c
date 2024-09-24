#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define INIT_BUFF_SIZE 256
#define BUFFER_SIZE 1024
#define LINE_TAB_SIZE 10

int is_line_empty(const char *line) {
    return line[0] != '\0'; 
}

int free_parsed_map(char **parsed_file, int line_count){
    for (int i = 0; i < line_count; i++) {
        free(parsed_file[i]);  
    }
    free(parsed_file);
    return 1;
}

char **parse_map(int *line_count) {
    size_t buffer_size = INIT_BUFF_SIZE;
    size_t line_length = 0;
    size_t tab_lines_capacity = LINE_TAB_SIZE;
    *line_count = 0;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    char *line = malloc(INIT_BUFF_SIZE); // Allocation initiale pour une ligne
    if (!line) {
        perror("Erreur: can't malloc line in parse_map");
        exit(EXIT_FAILURE);
    }
    char **lines = malloc(LINE_TAB_SIZE * sizeof(char *));  // Allocation initiale pour le tableau de lignes
    if (!lines) {
        perror("Erreur d'allocation");
        free(line);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            char c = buffer[i];

            if (c == '\n') {
                line[line_length] = '\0';

                if (!is_line_empty(line)) {
                    fprintf(stderr, "Erreur : ligne non conforme ou vide\n");
                    free(line);
                    for (int j = 0; j < *line_count; j++) {
                        free(lines[j]);
                    }
                    free(lines);
                    exit(EXIT_FAILURE);
                }

                // Vérifier si nous devons redimensionner le tableau
                if (*line_count >= (int)tab_lines_capacity) {
                    size_t new_capacity = tab_lines_capacity * 2;
                    char **new_lines = malloc(new_capacity * sizeof(char *));
                    if (!new_lines) {
                        perror("Erreur d'allocation");
                        free(line);
                        for (int j = 0; j < *line_count; j++) {
                            free(lines[j]);
                        }
                        free(lines);
                        exit(EXIT_FAILURE);
                    }

                    // Copier les lignes existantes dans le nouveau tableau
                    for (size_t j = 0; j < tab_lines_capacity; j++) {
                        new_lines[j] = lines[j];
                    }
                    free(lines);
                    lines = new_lines; // Mettre à jour le pointeur
                    tab_lines_capacity = new_capacity;
                }

                // Allocation manuelle pour la nouvelle ligne
                lines[*line_count] = malloc((line_length + 1) * sizeof(char));
                if (!lines[*line_count]) {
                    perror("Erreur d'allocation");
                    free(line);
                    for (int j = 0; j < *line_count; j++) {
                        free(lines[j]);
                    }
                    free(lines);
                    exit(EXIT_FAILURE);
                }
                memcpy(lines[*line_count], line, line_length + 1); // Copier la ligne
                (*line_count)++; // Incrémenter le compteur de lignes
                line_length = 0;  // Réinitialiser la longueur pour la prochaine ligne
            } else {
                // Ajouter le caractère à la ligne
                if (line_length + 1 >= buffer_size) {
                    // Augmenter la taille du buffer
                    buffer_size *= 2; // Doubler la taille
                    char *new_line = malloc(buffer_size);
                    if (!new_line) {
                        perror("Erreur d'allocation");
                        free(line);
                        exit(EXIT_FAILURE);
                    }
                    memcpy(new_line, line, line_length); // Copier l'ancien contenu
                    free(line); // Libérer l'ancien buffer
                    line = new_line; // Mettre à jour le pointeur
                }
                line[line_length++] = c;  // Ajouter le caractère
            }
        }
    }

    // Traiter la dernière ligne si elle ne se termine pas par un saut de ligne
    if (line_length > 0) {
        line[line_length] = '\0'; // Terminer la chaîne
        if (!is_line_empty(line)) {
            fprintf(stderr, "Erreur : ligne non conforme ou vide\n");
            free(line);
            for (int j = 0; j < *line_count; j++) {
                free(lines[j]); // Libérer les lignes précédemment allouées
            }
            free(lines);
            exit(EXIT_FAILURE);
        }
        // Ajouter la dernière ligne au tableau
        lines[*line_count] = malloc((line_length + 1) * sizeof(char)); // Allocation manuelle
        if (!lines[*line_count]) {
            perror("Erreur d'allocation");
            free(line);
            free(lines);
            exit(EXIT_FAILURE);
        }
        memcpy(lines[*line_count], line, line_length + 1); // Copier la ligne
        (*line_count)++;
    }

    free(line); // Libérer la mémoire allouée pour la ligne
    return lines; // Retourner le tableau de lignes
}

