# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 09:00:15 by msoria-j          #+#    #+#              #
#    Updated: 2023/04/22 17:34:47 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO: 
# Compile mlx library trhough this Makefile, instead of using their ./configure script.
# Change compilation flags according to the OS in which is being run.

define HEADER

███████╗██████╗ ███████╗
██╔════╝██╔══██╗██╔════╝
█████╗  ██║  ██║█████╗  
██╔══╝  ██║  ██║██╔══╝  
██║     ██████╔╝██║     
╚═╝     ╚═════╝ ╚═╝     

endef
export HEADER

# $@ = Name of the target
# $< = First prerequisite name - in this case, in $(SRC)
ifeq ($(shell uname -s), Darwin)
	# mac
	CFLAGS = -Wall -Wextra -Werror -Imlx -c $< -o $@
else ifeq ($(shell uname -s), Linux)
	# Linux
	CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
endif

CFLAGS	=	-Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3

OS		=	$(shell uname -s)

NAME	=	fdf

SRC		=	main.c

OBJ		=	$(SRC:.c=.o)

CC		=	gcc

LIBFT	=	libft/libft.a

FLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz # check path to X11 in mac
# CFLAGS	=	-Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3

# If on Linux, use the flag -e for echo command
ifeq ($(OS), Linux)
	ECHO = echo -e
else
	ECHO = echo
endif

#Define colors for output
COLOR='\033['
NONE=$(COLOR)0m
GREEN=$(COLOR)32m
GRAY=$(COLOR)37m
RED=$(COLOR)31m
CYAN=$(COLOR)36m
MAGENTA=$(COLOR)35m
BLUE=$(COLOR)34m
ITALIC=$(COLOR)3m
BOLD=$(COLOR)1m
BRIGHT_WHITE=$(COLOR)97m

ifndef VERBOSE
	MAKEFLAGS += --silent
#	MAKEFLAGS += --no-print-directory
endif

all:		$(NAME)

pre-build:
			@make -sC libft/
			$(ECHO) $(CYAN) "$$HEADER" $(NONE)
			$(ECHO) $(GREEN)$(ITALIC) "	Compiling $(NAME)..."$(NONE)

%.o: %.c
	 		$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME):	pre-build $(OBJ)
			$(CC) $(FLAGS) $(OBJ) $(LIBFT) libmlx_Linux.a -o $(NAME)
			$(ECHO) $(BRIGHT_WHITE)$(BOLD)"\tDone!"$(NONE)

clean:
			$(RM) $(OBJ)
			@make clean -sC libft/
			
fclean:		clean
			$(RM) $(NAME)
			@make fclean -sC libft/

re:			fclean $(NAME)

.PHONY:		all clean fclean re