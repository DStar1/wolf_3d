NAME = wolf3d

FLAGS = -Wall -Wextra -Werror -g

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRC_FILES = main.c map.c helpers.c hooks.c raycasting.c move.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
LNK  = -L $(LIBFT_DIR)

GIT = "test"

.SILENT:

all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc -I $(INC_DIR) -I $(LIBFT_DIR) -g -fsanitize=address -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	printf "\033[32m%s\n\033[0m" "Compiling..."
	gcc -g -fsanitize=address -o $(NAME) $(OBJ) $(LNK) -lm $(LIBFT_DIR)/libft.a minilibx/libmlx.a -framework OpenGL -framework AppKit
	printf "\033[32m[ ✔ ] %s\n\033[0m" "Created $(NAME)"

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	printf "\033[31m[ ✔ ] %s\n\033[0m" "Cleaned $(NAME)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	printf "\033[31m[ ✔ ] %s\n\033[0m" "Fcleaned $(NAME)"

re: fclean all

git:
	make fclean
	git add .
	git commit -m '$(GIT)'
	git push

.PHONY: all clean fclean re
