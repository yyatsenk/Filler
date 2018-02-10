# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/29 13:27:42 by yyatsenk          #+#    #+#              #
#    Updated: 2017/11/15 16:20:04 by yyatsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
					ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
					ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
					ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
					ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
					ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
					ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
					ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
					ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
					ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
					ft_strtrim.c ft_tolower.c ft_toupper.c ft_strlen_num.c ft_list_size.c \
					ft_whiteskip.c ft_num_of_words.c ft_strlen_until_char.c get_next_line.c
LIB_NAME = libft.h
OBJ = ./*.o
FLAG = -Wall -Wextra -Werror -c

all:$(NAME)

$(NAME):$(SRC)
	@gcc $(FLAG) $(SRC) $(LIB_NAME)
		@ar rc $(NAME) $(OBJ)
			@ranlib $(NAME)

clean:
	rm -f $(OBJ)
	find . \( -name "*~" -o -name "*.gch" -o -name ".DS_Store" \) -delete
fclean: clean
	rm -f $(NAME)
re: fclean all
