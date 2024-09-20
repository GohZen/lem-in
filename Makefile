NAME = lem-in

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

c_files = main.c \

GCC = gcc
Flags = -Wall -Werror -Wextra -Iincludes
C_FILES = $(c_files)
OBJ_FILES = $(c_files:.c=.o) 

all: $(LIBFT_A) $(NAME)

%.o: %.c
	$(GCC) $(Flags) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(GCC) $(Flags) -o $(NAME) $(OBJ_FILES) $(LIBFT_A) 

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR) clean  # Nettoyer aussi la libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
