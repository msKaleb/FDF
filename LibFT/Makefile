# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 17:34:47 by msoria-j          #+#    #+#              #
#    Updated: 2023/04/13 16:49:28 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define HEADER

██╗     ██╗██████╗ ███████╗████████╗
██║     ██║██╔══██╗██╔════╝╚══██╔══╝
██║     ██║██████╔╝█████╗     ██║   
██║     ██║██╔══██╗██╔══╝     ██║   
███████╗██║██████╔╝██║        ██║   
╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝   
                                    
endef
export HEADER

SRCS			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
					ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
					ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
					ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
					ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c\
					ft_strnstr.c ft_strrchr.c ft_strtrim.c \
					ft_substr.c ft_tolower.c ft_toupper.c\
					ft_fprintf/ft_fprintf.c ft_fprintf/ft_itoa_u.c \
					ft_fprintf/print_var.c ft_fprintf/change_base.c \
					get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c
					
OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
					ft_lstadd_back_bonus.c ft_lstlast_bonus.c \
					ft_lstdelone_bonus.c ft_lstsize_bonus.c\
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
					
BONUS_OBJS		= $(BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

#Define colors for output
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
RED='\033[31m'
CYAN='\033[36m'
MAGENTA="\033[35m"
BLUE="\033[34m"
ITALIC="\033[3m"

ifndef VERBOSE
	MAKEFLAGS += --silent
#	MAKEFLAGS += --no-print-directory
endif

all:			$(NAME)

pre-build:
				@echo $(CYAN) "$$HEADER" $(NONE)
				@echo $(GREEN)$(ITALIC) "	Compiling $(NAME)..."$(NONE)

pre-build-bonus:
				@echo $(BLUE) "$$HEADER" $(NONE)
				@echo $(MAGENTA)$(ITALIC) "	Compiling $(NAME) (Bonus)..."$(NONE)
				
$(NAME):		pre-build $(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				@echo $(RED)$(ITALIC) "	cleaning object files..." $(NONE)
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				@echo $(RED)$(ITALIC) "	removing $(NAME) file..." $(NONE)
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			pre-build-bonus $(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus