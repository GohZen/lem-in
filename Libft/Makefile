lib = libft

fcts =  ft_strlen \
		ft_memmove \
		ft_isdigit \
		ft_memcpy \
	 	ft_strlcpy \
	    ft_isalpha \
		ft_strlcat \
		ft_isalnum \
		ft_isprint \
		ft_memset \
		ft_isascii \
		ft_bzero \
		ft_toupper \
		ft_tolower \
		ft_strchr \
		ft_strrchr \
		ft_strncmp \
		ft_memchr \
		ft_memcmp \
		ft_strnstr \
		ft_atoi \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_striteri \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \

GCC	= gcc

Flags	= -Wall -Wextra -Werror

LIB_A		= $(lib).a
C_FILES		= $(fcts:%=%.c)
OBJ_FILES	= $(fcts:%=%.o)
NAME		= $(LIB_A)

$(NAME):
	$(GCC) $(Flags) -c $(C_FILES) -I./
	ar -rc $(LIB_A) $(OBJ_FILES)

all: $(NAME)

clean:
	rm -f $(NAME)
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
