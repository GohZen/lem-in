#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../Libft/libft.h"

#define INIT_BUFF_SIZE 256
#define BUFFER_SIZE 1024
#define LINE_TAB_SIZE 20

int is_line_empty(const char *line) {
    return line[0] == '\0'; 
}

void *safe_malloc(size_t size, char **to_free, int line_count) {
    void *ptr_malloc = malloc(size);
    if (!ptr_malloc) {
        perror("Erreur: Malloc allocation failed");
        if (to_free != NULL) {
            for (int i = 0; i < line_count; i++) {
                free(to_free[i]);
            }
            free(to_free);
        }
        exit(EXIT_FAILURE);
    }
    return ptr_malloc;
}

int free_parsed_map(char **parsed_file, int line_count){
    for (int i = 0; i < line_count; i++) {
        //printf("%s\n", parsed_file[i]);
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

    char *line = safe_malloc(INIT_BUFF_SIZE, NULL, 0);  // Allocation initiale pour une ligne
    char **lines = safe_malloc(LINE_TAB_SIZE * sizeof(char *), NULL, 0);  // Allocation initiale pour le tableau de lignes

    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            char c = buffer[i];

            if (c == '\n') {  // SI NOUVELLE LIGNE -----------------
                line[line_length] = '\0';

                if (is_line_empty(line)) {
                    fprintf(stderr, "Erreur: ligne non conforme ou vide\n");
                    free(line);
                    free_parsed_map(lines, *line_count);
                    exit(EXIT_FAILURE);
                }

                if (*line_count >= (int)tab_lines_capacity) {  // REDIMENSIONNER TABLEAU SI NECESSAIRE
                    size_t new_capacity = tab_lines_capacity * 2;
                    char **new_lines = safe_malloc(new_capacity * sizeof(char *), lines, *line_count);
                    for (size_t j = 0; j < tab_lines_capacity; j++) {
                        new_lines[j] = lines[j];
                    }
                    free(lines);
                    lines = new_lines;  // METTRE A JOUR POINTEUR
                    tab_lines_capacity = new_capacity;          
                }

                lines[*line_count] = safe_malloc((line_length + 1) * sizeof(char), lines, *line_count);
                ft_memcpy(lines[*line_count], line, line_length + 1);  // Copier la ligne
                (*line_count)++;  // Incrémenter le compteur de lignes
                line_length = 0;  // Réinitialiser la longueur pour la prochaine ligne
            } else {
                if (line_length + 1 >= buffer_size) {
                    buffer_size *= 2;
                    char *new_line = safe_malloc(buffer_size, lines, *line_count);
                    ft_memcpy(new_line, line, line_length);  // Copier l'ancien contenu
                    free(line);  // Libérer l'ancien buffer
                    line = new_line;  // Mettre à jour le pointeur
                }
                line[line_length++] = c;  // Ajouter le caractère
            }
        }
    }

    if (line_length > 0) {
        line[line_length] = '\0';
        if (is_line_empty(line)) {
            fprintf(stderr, "Erreur : ligne non conforme ou vide\n");
            free(line);
            free_parsed_map(lines, *line_count);
            exit(EXIT_FAILURE);
        }
        lines[*line_count] = safe_malloc((line_length + 1) * sizeof(char), lines, *line_count);
        ft_memcpy(lines[*line_count], line, line_length + 1);
        (*line_count)++;
    }
    free(line);

    return lines;
}

