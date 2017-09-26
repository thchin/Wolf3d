# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thchin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 14:48:39 by thchin            #+#    #+#              #
#    Updated: 2017/06/02 09:17:30 by thchin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = srcs/anim_npc.c\
	  srcs/anim_weapon.c\
	  srcs/clear.c\
	  srcs/copy.c\
	  srcs/dda.c\
	  srcs/dead.c\
	  srcs/event.c\
	  srcs/floor.c\
	  srcs/get.c\
	  srcs/hud.c\
	  srcs/hurt.c\
	  srcs/init.c\
	  srcs/init_sprite.c\
	  srcs/init_npc.c\
	  srcs/main.c\
	  srcs/menu.c\
	  srcs/menu_event.c\
	  srcs/move.c\
	  srcs/npc.c\
	  srcs/shot.c\
	  srcs/sprite.c\
	  srcs/sprite_direction.c\
	  srcs/print.c\
	  srcs/textures.c\
	  srcs/time.c\
	  srcs/weapon.c\

OBJ = $(SRC:.c=.o)

LIB = make -C ./libft

LIBDIR = -L./libft -lft

CFLAGS = -Wall -Werror -Wextra

MLX = -lmlx -L./minilibx_macos -framework OPENGL -framework Appkit

SDL_CFLAGS = -I ~/.brew/include -D_GNU_SOURCE=1 -D_THREAD_SAFE

SDL_LIBS = -L ~/.brew/lib -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wl,-framework,Cocoa

.PHONY: all clean

all:
	$(LIB)
	gcc -c $(SDL_CFLAGS) $(SRC)
	mv *o srcs/
	gcc $(CFLAGS) $(SDL_LIBS) -lpthread -D_REENTRANT $(LIBDIR) -o $(NAME) $(OBJ)

clean:
	$(LIB) clean
	rm -rf $(OBJ)

fclean: clean
	$(LIB) fclean
	rm -rf $(NAME)

re: fclean all
