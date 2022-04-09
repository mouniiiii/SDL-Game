menu:main.o Menu.o Music.o Text.o Buttons.o Background.o ennemy.o
	gcc main.o Menu.o Music.o Text.o Buttons.o Background.o ennemy.o -o menu -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o:main.c
	gcc -c main.c -g
Menu.o:Menu.c
	gcc -c Menu.c -g
Music.o:Music.c
	gcc -c Music.c -g
Text.o:Text.c
	gcc -c Text.c -g
Buttons.o:Buttons.c
	gcc -c Buttons.c -g
Background.o:Background.c
	gcc -c Background.c -g
ennemy.o:ennemy.c
	gcc -c ennemy.c -g
