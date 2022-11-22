# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 16:33:38 by jdasilva          #+#    #+#              #
#    Updated: 2022/11/19 21:21:29 by jdasilva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = mandatory/src/
O = mandatory/objs/
B = bonus/src/
J = bonus/objs/

NAME = pipex

SRC = $Spipex.c $Spipex_utils.c $Sft_strncmp.c $Sft_strlen.c \
	$Sft_strlcpy.c $Sft_split.c $Sft_strjoin.c $Sft_strlcat.c

OBJS = $Opipex.o $Opipex_utils.o $Oft_strncmp.o $Oft_strlen.o \
	$Oft_strlcpy.o $Oft_split.o $Oft_strjoin.o $Oft_strlcat.o 

BONUS_SRC = $Bpipex_bonus.c $Bpipex_utils_bonus.c $Bft_strncmp_bonus.c\
	$Bft_strlcpy_bonus.c $Bft_split_bonus.c\
	$Bft_strlcat_bonus.c $Bft_heredoc_bonus.c\
	$Bget_next_line_bonus.c $Bget_next_line_utils_bonus.c

BONUS_OBJS = $Jpipex_bonus.o $Jpipex_utils_bonus.o $Jft_strncmp_bonus.o\
	$Jft_strlcpy_bonus.o $Jft_split_bonus.o\
	$Jft_strlcat_bonus.o $Jft_heredoc_bonus.o\
	$Jget_next_line_bonus.o $Jget_next_line_utils_bonus.o

CC = gcc -Wall -Werror -Wextra  -g3

all: $(NAME)

$O:
	mkdir $@
	@echo "Carpeta objs creada"
$J:
	mkdir $@
	@echo "Carpeta bonus objs creada"

$(OBJS): | $O

$(OBJS): $O%.o: $S%.c
	$(CC) -c $< -o $@

$(BONUS_OBJS): | $J

$(BONUS_OBJS): $J%.o: $B%.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
		$(CC) $^ -o $@
		@echo "Compilado"
		
bonus: $(BONUS_OBJS)
	$(CC) $^ -o  $(NAME)
	@echo "Bonus Compilado"

clean:
	rm -rf $(OBJS) $(BONUS_OBJS) $O $J
	@echo "Archivos . o eliminados"
fclean: clean
	rm -rf $(NAME)
	@echo "Archivo pipex eliminado"
re: fclean all

.PHONY: all clean fclean re bonus