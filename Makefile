NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
SOURCE = main.c ls_util.c ft_getopt.c ls_path_walk.c ls_ftree.c ls_show.c \
		ls_cmpname.c ls_cmptime1.c ls_flags.c ls_print_col.c ft_strmode.c \
		ls_cmptime2.c ls_print_long.c ls_print_stream.c ls_parse_opt.c \
		ls_print_util.c ls_ftree_free.c ls_show_ugf.c ft_ls.c
HEADER = ft_ls.h ft_getopt.h ft_hash.h

INCLUDES = -Iincludes -I$(LIBFT_DIR)includes

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/
LIB = -lft

VPATH = srcs includes

OBJ = $(SOURCE:.c=.o)
OBJ_DIR = obj/
OBJECT = $(patsubst %.o, $(OBJ_DIR)%.o, $(OBJ))

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJECT)
	@echo "\033[1;3;34m"
	gcc $(FLAGS) $(OBJECT) $(INCLUDES) -L$(LIBFT_DIR) $(LIB) -o $@
	@echo "\033[23;32m--[ "$(NAME) ]-- successfully compiled"\033[0m"

$(LIBFT) :
	@echo "\033[33;3m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0m"

$(OBJ_DIR)%.o : %.c $(HEADER)
	@echo "\033[36;3m\c"
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0m\c"

clean :
	@make -C $(LIBFT_DIR) clean
	@find $(OBJ_DIR) -type f -not -name '.gitkeep' -delete

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re : fclean all
