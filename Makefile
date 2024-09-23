NAME		=	so_long

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g3

FLAG		=	-DGL_SILENCE_DEPRECATION

LIBFT_PATH	=	./libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_FILE	=	libmlx.a
MLX_PATH	=	./minilibx-linux/
MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))
MLX_FLAG	=	-lX11 -lXext

C_FILE		=	map.c				\
				map_checker.c		\
				dfs.c		\
				map_checker_utils.c		\
				render.c			\
				render_mouv.c		\
				set.c				\
				texture.c			\
				utils.c				\

SRC_DIR		=	./core/
INC_DIR		=	./includes/

SRC			=	$(addprefix $(SRC_DIR), $(C_FILE))
OBJ			=	$(SRC:.c=.o)

# Rule to convert .c files into .o files
.c.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# The main target - it depends on the object files and the libraries
$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB)
	@echo "\033[0;33m\nCOMPILING SO_LONG...\n"
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAG) -o $(NAME)
	@echo "\033[1;32m./so_long created\n"

# Compile the libft library only if needed
$(LIBFT_LIB):
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT_lib created\n"

# Compile the MLX library only if needed
$(MLX_LIB):
	@echo "\033[0;33m\nCOMPILING $(MLX_PATH)...\n"
	@make -C $(MLX_PATH)
	@echo "\033[1;32mMLX_lib created\n"

# Cleaning object files and intermediate build files
clean:
	@echo "\033[0;31mDeleting Obj file in $(MLX_PATH)...\n"
	@make clean -sC $(MLX_PATH)
	@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "\033[0;31mDeleting So_long object files...\n"
	@rm -f $(OBJ)
	@echo "\033[1;32mDone\n"

# Full clean, including the executable and libraries
fclean: clean
	@echo "\033[0;31mDeleting so_long executable...\n"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"

# Rebuild the project
re: fclean all

# Compile everything
all: $(NAME)
	@echo "\033[1;32mAll files compiled successfully.\n"

.PHONY: all clean fclean re lib mlx

