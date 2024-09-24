#ifndef PARSE_FILE_H
# define PARSE_FILE_H

char **parse_map(int *line_count);
int free_parsed_map(char **parsed_file, int line_count);

#endif