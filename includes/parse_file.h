#ifndef PARSE_FILE_H
# define PARSE_FILE_H

typedef struct s_parsed_data {
    char *start;                    
    char *end;                      
    char **comments;                
    int comment_count;              
}              t_parsed_data;

t_parsed_data *init_parsed_data(char **to_free, int line_count);
char **parse_map(int *line_count);
int free_parsed_map(char **parsed_file, int line_count);
void define_parsed_elem(char **parsed_file, int line_count, t_parsed_data *parsed_data);


#endif