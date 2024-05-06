NAME				= minishell
INC					= .
SRC_DIR				= src/
OBJ_DIR				= src/obj/
LIBFT				= libft/libft.a

CC					= cc
CFLAGS				= -g -Wall -Werror -Wextra -I$(INC)
RM					= rm -f

MINISHELL_DIR		= \
					built_ins/cd.c \
					built_ins/echo.c \
					built_ins/env.c \
					built_ins/export.c \
					built_ins/pwd.c \
					built_ins/unset.c \
					\
					utils/cleanup.c \
					utils/env_utils.c \
					utils/heredoc.c \
					utils/redirect_quotes.c \
					utils/tokens.c \
					utils/input_utils.c \
					utils/main_loop.c \
					utils/pipe_quotes.c \
					utils/pipe_quotes2.c \
					utils/pipe_quotes3.c \
					utils/str_utils.c \
					utils/utils.c \
					\
					commands_handler.c \
					pipes.c \
					main.c \
					redirect.c

SRCS 				= $(addprefix $(SRC_DIR), $(MINISHELL_DIR))
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

start:				
	@echo "Starting the build process..."
	@make all --no-print-directory
	@echo "Build process completed."

all: $(NAME)
	@echo "Executable $(NAME) has been created successfully."

$(LIBFT):
	@make -C ./libft --no-print-directory

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)
	@echo "Executable $(NAME) has been created."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up object files..."
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./libft --no-print-directory
	@echo "Object files have been removed."

fclean: clean
	@echo "Cleaning up executable $(NAME)..."
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "Executable $(NAME) has been removed."

re: fclean all
	@echo "Rebuild process completed."

.PHONY: start all clean fclean re
