hello: hello.c
	gcc -Wall -Werror -Wextra -Wshadow hello.c -o hello

credit: credit.c
	gcc -Wall -Werror -Wextra -Wshadow credit.c -o credit

credit.so: credit.c
	gcc -shared -fPIC -Wall -Werror -Wextra -Wshadow credit.c -o credit.so

credits: credit.c
	gcc -Wall -Werror -Wextra -Wshadow credit.c -o credit
	gcc -shared -fPIC -Wall -Werror -Wextra -Wshadow credit.c -o credit.so

# some:
# 	gcc -ggdb3 -Wall -Werror -Wextra -Wshadow 

# some2:
# 	gcc -shared -fPIC
