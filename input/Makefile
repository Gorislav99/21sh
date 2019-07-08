NAME =  minishell
PRINT = libft/libft.a
SRC = minishell.c temp/split_line.c temp/launch_command.c temp/environ.c temp/built_in.c temp/other_function.c temp/init_shell.c input/input.c temp/write_arg.c temp/lenght_word.c input/spec_key.c input/history_session.c vector/vector.c
#FLAG = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)
OBJ = *.o

CG = \033[92m
all: start $(NAME)
$(NAME):
	@make -sC libft/
	@gcc  -c $(FLAG) $(SRC) 
	@gcc  -g -ltermcap -o   $(NAME) $(OBJ) -L. $(PRINT)
	@rm *.o
	@echo "\r$(CY)--------------------------------------------------- GO --------------------------------------------------------"
start:
	@echo "\r$(CG)compile...																			  "
	@echo "	-------------------------------------------------------------------------------------------------------"
	@echo "	|	                000|             000|               00|       	         	              |	"
	@echo "	|	000000000000|          000000|           000000|    00|  	00000|   00|	    00|       | "
	@echo "	|	000  00  000|	000|   00  00|   000|    000|       000000|	00|      00|	    00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|      0000|    00  00|	00000|   00|        00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|        000|   00  00|	00|  	 00|	    00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|    000000|    00  00|	00000|   0000000|   0000000|  |	"
	@echo "	-------------------------------------------------------------------------------------------------------"
clean:
	@make clean -sC libft/
	@rm -rf $(OBJ)
fclean: clean
	@make fclean -sC libft/
	@rm -rf $(NAME)
re: fclean all clean