# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/25 10:26:44 by mgorczan          #+#    #+#              #
#    Updated: 2018/11/25 12:03:30 by mgorczan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = *.c
OBJ = *.o
FLAG = -Wall -Wextra -Werror
SRC_PRTF = ft_printf/ft_printf.c ft_printf/other_function.c ft_printf/output.c ft_printf/flags_and_precision.c ft_printf/output_symbol.c ft_printf/output_unsigned_digit.c ft_printf/output_sign_digit.c ft_printf/specifiers_digit.c ft_printf/specifiers_symbol.c ft_printf/conversion.c ft_printf/output_float.c ft_printf/specifiers_float.c ft_printf/ft_printf.c ft_printf/other_function.c ft_printf/output.c ft_printf/flags_and_precision.c ft_printf/output_symbol.c ft_printf/output_unsigned_digit.c ft_printf/output_sign_digit.c ft_printf/specifiers_digit.c ft_printf/specifiers_symbol.c ft_printf/conversion.c ft_printf/output_float.c ft_printf/specifiers_float.c
# OBJ_PRTF = $(SRC_PRTF:.c=.o)
all: $(NAME)
$(NAME):
	@gcc $(FLAG) -c $(SRC) $(SRC_PRTF)
	@ar rc $(NAME) $(OBJ) $(OBJ_PRTF) $(OBJ_PRTF)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean $(NAME)