SRCS	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		  ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		  ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
		  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
		  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_B	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS_BB	= ft_numlen_bonus.c

INC_DIR = ../../inc

OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

OBJS_BB	= ${SRCS_BB:.c=.o}

NAME	= libft.a

GCC		= gcc
RM		= rm -f
MAKELIB	= ar rc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	@${GCC} ${CFLAGS} -I ${INC_DIR} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	@${MAKELIB} ${NAME} ${OBJS}

bonus:	${OBJS} ${OBJS_B} ${OBJS_BB}
	${MAKELIB} ${NAME} ${OBJS} ${OBJS_B} ${OBJS_BB}

all:	${NAME}

clean:
	@${RM} ${OBJS} ${OBJS_B} ${OBJS_BB}

fclean:	clean
	@${RM} ${NAME}

re:	fclean all

.PHONY:	bonus all clean fclean re
