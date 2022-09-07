# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svrielin <svrielin@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/07 14:21:16 by svrielin      #+#    #+#                  #
#    Updated: 2022/09/07 17:51:03 by svrielin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	so_long
CC				:=	gcc
CFLAGS			?=	-Wall -Wextra -Werror 
INCLUDE_FLAGS	?=	-I include -lglfw3 -framework Cocoa	-framework OpenGL -framework IOKit
#################################Project_files##################################
SRC_DIR			:=	./src
SRC_FILES		:=	so_long.c main.c
OBJ_DIR			:=	./obj
OBJ_FILES		:=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
MLXDIR			:= ./MLX42
LIBMLX42		:= $(MLXDIR)/libmlx42.a

ifdef DEBUG
CFLAGS	+=	-g
NAME = so_long_debug
endif

all: $(NAME)

# $@ filename of the target $^ all prerequisites
# r: uses replacement for the objects files while inserting the files member into archive
# c: create the library if it does not exist
$(NAME): $(OBJ_FILES) $(LIBMLX42)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $^ -o $(NAME)
	@echo "Executable so_long is ready"

# -p: if parent dirs do not exist, generate them to accommodate 
# gcc -c: compile but not link the file, makes the result an object file
# $< the first prerequisite
# gcc -o: name of the output file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
#	@echo "Object files and directory created"

$(LIBMLX42):
	make -C $(MLXDIR)

clean:
	@rm -f $(OBJ_FILES) 
	@rm -df $(OBJ_DIR)
	@echo "Object files and directory removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Library libft removed"

re: fclean all

.PHONY: clean fclean
