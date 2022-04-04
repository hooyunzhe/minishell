NAME		= minishell

SRC_DIR		= src/minishell
OBJ_DIR		= obj
LIBFT_DIR	= src/libft
INC_DIR		= inc

SRC_FILES	= main.c minishell.c parser.c init.c free.c append.c

OBJ_FILES	= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}

GCC			= gcc
CFLAGS		= -Wall -Wextra -Werror
SANITIZE	= -g fsanitize=address
RM			= rm -f

LIBFT		= $(LIBFT_DIR)/libft.a
LIBRARIES	= -L${LIBFT_DIR} -L/usr/local/opt/readline/lib -lft -lreadline

all:	$(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
	$(GCC) $(CFLAGS) -I $(INC_DIR) -I/usr/local/opt/readline/include -c $< -o $@

$(LIBFT):
	make -C ${LIBFT_DIR}

${NAME}:	${LIBFT} ${OBJ_FILES}
	${GCC} -o ${NAME} ${OBJ_FILES} $(LIBRARIES)

test: all
	@./$(NAME) 

clean:
	${RM} ${OBJ_DIR}
	make clean -C ${LIBFT_DIR}

fclean:
	${RM} ${NAME}
	${RM} ${OBJ_FILES}
	make fclean -C ${LIBFT_DIR}

re:	fclean all

.PHONY: all clean fclean re