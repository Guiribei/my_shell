NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -I. -c -g3
CC = gcc 
FILES = ft_envcmp.c \
		ft_isalpha.c \
		ft_isalpha_under.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_strlen.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_bzero.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strndup.c \
		ft_strnstr.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strmapi.c \
		ft_split.c \
		ft_get_next_line.c \
		ft_atold.c \
		ft_getenv.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_matrixcpy.c \
		ft_strcmp.c


OBJFILES = $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJFILES)
	@ar rcs $@ $^

$(OBJFILES): $(FILES)
	@$(CC) $(CFLAGS) $^
	
clean:
	@rm -f $(OBJFILES)

fclean: clean 
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
