NAME	=	minishell

OBJS	=	$(SRCS:.c)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

LIB		=	./libft/libft.a

SRCS 	=	ft_cmds.c ft_lstsplit_ms.c ft_parsing.c ft_utils.c \
			gb_collector.c main.c get_env.c ft_redir.c \
			ft_write_redir.c ft_join.c ft_split_ms.c \
			ft_execs.c ft_var.c ft_pipe.c ft_ret_erreur.c ft_ls.c \
			ft_lst_utils.c ft_utils2.c ft_pipe_utils.c ft_export.c \
			ft_unset.c ft_env.c ft_pipe2.c ft_fill.c ft_pipe3.c ft_utils3.c \
			ft_export_no_arg.c ft_parse_chev.c ft_parse_av.c test_directory.c \
			ft_pwd.c ft_cd.c ft_exit.c ft_join2.c ft_lstsplit_ms2.c \
			ft_lstsplit_ms3.c ft_parse_sep.c \
			ft_init_data_start.c

all		:	$(NAME)
			make wall

$(NAME) :
			cd ./libft ; make ; cd .. ;
			#gcc -o $(NAME) $(CFLAGS) $(SRCS) $(LIB)

c	:
			make clean ;
			gcc -o $(NAME) $(SRCS) $(LIB)

wall	:
			make clean ;
			gcc -o $(NAME) $(CFLAGS) $(SRCS) $(LIB)

s	:
			gcc -o $(NAME) -g3 -fsanitize=address \
			$(SRCS) $(LIB)

n		:
			norminette *.c *.h

clean	:
			cd ./libft ; make clean ; cd .. ;
			$(RM) $(OBJS) $(BONUS)

fclean	:	clean
			cd ./libft ; make fclean ; cd .. ;
			$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	clean	fclean	all
