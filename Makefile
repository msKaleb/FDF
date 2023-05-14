# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 09:00:15 by msoria-j          #+#    #+#              #
#    Updated: 2023/05/14 12:40:35 by msoria-j         ###   ########.fr        #
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

OS		=	$(shell uname -s)

NAME	=	fdf

SRC		=	main.c \
			utils.c \
			graphics.c \
			trig.c \
			trig_utils.c \
			map_utils.c \
			mlx_utils.c \
			frame_map.c
			
OBJ		=	$(SRC:.c=.o)

CC		=	gcc

LIBFT	=	LibFT/libft.a

# Define flags according to OS
ifeq ($(OS), Linux)
# Linux
	ECHO = echo -e
	CCOBJ = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
	FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLXDIR = mlx_linux/
	MLX = $(MLXDIR)libmlx_Linux.a
else ifeq ($(OS), Darwin)
# Mac (-lm compiler option)
	ECHO = echo
	CCOBJ = -Wall -Wextra -Werror -Imlx -c $< -o $@
	FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLXDIR = mlx/
	MLX = $(MLXDIR)libmlx.a
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
			@make bonus -sC LibFT/
			$(ECHO) $(CYAN) "$$HEADER" $(NONE)
			$(ECHO) $(GREEN)$(ITALIC) "	Compiling $(NAME)..."$(NONE)
			@make -sC $(MLXDIR)

%.o: %.c
	 		$(CC) $(CCOBJ)

$(NAME):	pre-build $(OBJ)
			$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
			$(ECHO) $(BRIGHT_WHITE)$(BOLD)"\tDone!"$(NONE)

clean:
			$(RM) $(OBJ)
			@make clean -sC LibFT/
			make clean -sC $(MLXDIR)
			
fclean:		clean
			$(RM) $(NAME)
			@make fclean -sC LibFT/

re:			fclean $(NAME)

.PHONY:		all clean fclean re