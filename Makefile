NAME = minishell
PATH_SRC = ./sources/
PATH_SRCS = ./sources/builtins/
PATH_SORCS = ./sources/parser/
PATH_OBJ = ./objects/

SRC = prompt.c \
	  main.c \
	  signal.c \
	  env_utils.c \
	  executor.c \
	  pathing.c \
	  clear.c \
	  recreate_envp.c \
	  join.c \
	  env.c \
	  export.c \
	  unset.c \
	  echo.c \
	  pwd.c \
	  cd.c \
	  utils.c \
	  exit.c \
	  init.c \
	  error.c \
	  ft_atoi_long.c \
	  expand_variables.c \
	  tokenize.c \
	  count_tokens.c \
	  count_tokens_utils.c \
	  allocate_tokens.c \
	  allocate_tokens_utils.c \
	  fill_tokens.c \
	  fill_tokens_utils.c \
	  syntax.c \
	  command.c \
	  is_builtin.c \
	  split_cmds.c \
	  heredoc.c \
	  is_token.c


OBJ = ${SRC:%.c=$(PATH_OBJ)%.o}

INCLUDE = -I ./includes/
LIBFT = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
LINKERS = -lrt -lm -lreadline

all:		$(NAME)

$(NAME): 	$(LIBFT) $(OBJ)
	@cc $(FLAGS) $(OBJ) $(LIBFT) $(LINKERS) -o $(NAME)

$(LIBFT):
	@make all --no-print-directory -C ./libft/

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	cc $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Objects creation done!\033[0m"

$(PATH_OBJ)%.o: $(PATH_SRCS)%.c
	cc $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Objects creation done!\033[0m"

$(PATH_OBJ)%.o: $(PATH_SORCS)%.c
	cc $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Objects creation done!\033[0m"

clean:
	@make clean --no-print-directory -C ./libft/
	@rm -rf $(PATH_OBJ)
	@echo "\33[1;93m[SUCCESS] Objects removal done!\33[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean --no-print-directory -C ./libft/
	@echo "\033[1;93m[SUCCESS] Removal done!\33[0m"

re: fclean all
	
incendio: fclean
	git add .
	git commit -m "Emergency commit"
	git push

.PHONY: all clean fclean re incendio
