# *********************************************** #
#      ____  ____ ___  ____ _____  ____ ______    #
#     / __ \/ __ `__ \/ __ `/ __ \/ __ `/ ___/    #
#    / /_/ / / / / / / /_/ / / / / /_/ / /        #
#    \____/_/ /_/ /_/\__,_/_/ /_/\__,_/_/         #
#                                                 #
#    Makefile                                     #
#    By: omanar <omanar@student.1337.ma>          #
#    Created: 2022/08/15 07:08 PM by omanar 	  #
#                                                 #
# *********************************************** #

NAME	=	cub3D
RM		=	rm -f
CC		=	gcc -Wall -Wextra -Werror -Iincludes -I libs/libft/includes
DEBUG	=	-g -fsanitize=address
MLXFLG	=	-lmlx -framework OpenGL -framework AppKit
LIBFT	=	libs/libft/libft.a
SRCS	=	srcs/cub3D.c $(LIBFT) \
			srcs/parsing/parsing.c srcs/parsing/parsing_utils.c srcs/parsing/map_parsing.c \
			srcs/parsing/line_parsing.c srcs/parsing/line_parsing_utls.c \
			srcs/get_next_line/get_next_line.c srcs/get_next_line/get_next_line_utils.c \
			srcs/utils/initializing.c srcs/utils/setup.c srcs/utils/utils.c srcs/utils/error_handler.c\
			srcs/raycasting/projection.c srcs/raycasting/raycasting.c srcs/raycasting/raycasting_utils.c \

define HEADER_M
   ______      __   _____ ____ 
  / ____/_  __/ /_ |__  // __ \\
 / /   / / / / __ \\ /_ </ / / /
/ /___/ /_/ / /_/ /__/ / /_/ / 
\\____/\\__,_/_.___/____/_____/  
endef
export HEADER_M

all: header_m $(NAME)

header_m:
	@echo "\033[0;33m$$HEADER_M\033[0m\n"

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libs/libft

$(NAME): $(SRCS) $(LIBFT)
	@echo "\033[0;36m</ Compiling Cub3D >\033[0m"
	@$(CC) $(MLXFLG) $(SRCS) -o $(NAME)
	@echo "\033[1;32mCub3D has been compiled!\033[0m\n"

run: all
	@echo "\033[1;32m</ Running... >\033[0m\n"
	@./$(NAME) maps/simple.cub

debug: all
	@$(CC) $(MLXFLG) $(DEBUG) $(SRCS) -o $(NAME)
	@echo "\033[1;31m</ YOU ARE IN DEBUG MODE! >\033[0m\n"

clean:
	@make clean -C libs/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libs/libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re header_m
