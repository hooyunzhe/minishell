NAME		= minishell

SRC_DIR		= src/minishell
OBJ_DIR		= obj
LIBFT_DIR	= src/libft
INC_DIR		= inc

SRC_FILES	= main.c minishell.c parser.c init_env.c env_lstfunc.c env_functions.c\
			  directory.c param_lstfunc.c param_newfunc.c free.c signals.c mini_echo.c\
			  handle_error.c executor.c mini_exit.c

OBJ_FILES	= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}

GCC			= gcc
CFLAGS		= -Wall -Wextra -Werror
SANITIZE	= -fsanitize=address -g3
RM			= rm -f

LIBFT		= $(LIBFT_DIR)/libft.a
LIBRARIES	= -L${LIBFT_DIR} -lft -lreadline -L/usr/local/opt/readline/lib

INC_RL		= -I/usr/local/opt/readline/include

all:	$(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
	@$(GCC) $(CFLAGS) -I $(INC_DIR) $(INC_RL) -c $< -o $@

$(LIBFT):
	@make -C ${LIBFT_DIR}

${NAME}:	${LIBFT} ${OBJ_FILES}
	@${GCC} -o ${NAME} ${OBJ_FILES} $(LIBRARIES) $(CFLAGS)
	#@${GCC} -o ${NAME} ${OBJ_FILES} $(LIBRARIES) $(SANITIZE) $(CFLAGS)

test: re
	@./$(NAME) 

clean:
	@${RM} ${OBJ_DIR}
	make clean -C ${LIBFT_DIR}

fclean:
	@${RM} ${NAME}
	@${RM} ${OBJ_FILES}
	@make fclean -C ${LIBFT_DIR}

re:	fclean all

.PHONY: all clean fclean re
