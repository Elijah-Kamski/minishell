SRCS = ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_strlen.c \
       ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_calloc.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_split.c \
       ft_itoa.c \
       ft_strmapi.c \
       ft_striteri.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_strncat.c \
       ft_count_words.c \
       ft_numlen.c \
       ft_isspace.c \
       ft_lstnew.c \
       ft_lstadd_front.c \
       ft_lstsize.c \
       ft_lstlast.c \
       ft_lstadd_back.c \
       ft_lstdelone.c \
       ft_lstclear.c \
       ft_lstiter.c \
       ft_lstmap.c \
       \
       ft_printf.c\
       ft_printf_aux.c\
       \
       get_next_line.c \
       get_next_line_utils.c

OBJS = $(patsubst %.c,libft_obj/%.o,$(SRCS))

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@ar rcs $(NAME) $(OBJS)
	@echo "$(NAME) compiled successfully!"

libft_obj/%.o: %.c | libft_obj
	@$(CC) $(CFLAGS) -c $< -o $@

libft_obj:
	@mkdir -p libft_obj

clean:
	@$(RM) -r libft_obj

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
