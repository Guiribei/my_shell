# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 19:44:22 by coder             #+#    #+#              #
#    Updated: 2022/12/07 16:47:08 by etachott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = prompt.c main.c signal.c env.c env_utils.c executor.c pathing.c clear.c recreate_envp.c join.c
OBJS = ${SRCS:%.c=$(PATH_OBJS)%.o}	
LIBS = libft.a
PATH_SRCS = ./sources/
PATH_OBJS = ./objects/
PATH_LIBS = ./libs/libft

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -I ./include/ $(OBJS) $(PATH_LIBS)/$(LIBS) -lrt -lm -lreadline -o $(NAME)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
	mkdir -p $(PATH_OBJS)
	cc $(CFLAGS) -I./include/ -c $< -o $@

$(LIBS):
	make -C $(PATH_LIBS)
	
clean:
	rm -rf $(PATH_OBJS) 
	make clean -C $(PATH_LIBS)
fclean: clean
	rm -f $(NAME)
	make fclean -C $(PATH_LIBS)
re: fclean all

.PHONY: all clean fclean re
