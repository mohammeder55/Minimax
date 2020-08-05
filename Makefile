minimax: minimax.c
	gcc -Wall -Werror -Wextra -Wshadow minimax.c -o minimax
	gcc -shared -fPIC -Wall -Werror -Wextra -Wshadow minimax.c -o minimax.so

t: t.c
	gcc -Wall -Werror -Wextra -Wshadow t.c -o t