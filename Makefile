NAME = rtv1

OBJ = mymlx.o main.o lin_alg.o color.o init_data.o events.o central.o comline_obj.o check_arg.o hits.o brights.o memory.o linalg1.o entex.o create_points.o initialize_points.o free_points.o
INCLUDES = /Users/mariamayerchyk/42/exercises_opencl/Exercises/C_common
			#"C:\Users\TARAS\42\opencl\Exercises\C_common"

FLAGS = #-Wextra -Werror -Wall
all: $(NAME)

$(NAME):
#	make -C libft/ fclean && make -C libft/
	gcc -g $(FLAGS) -I libft/includes -o mymlx.o -c mymlx.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o main.o -c main.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o lin_alg.o -c lin_alg.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o color.o -c color.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o init_data.o -c init_data.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o events.o -c events.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o central.o -c central.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o comline_obj.o -c comline_obj.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o check_arg.o -c check_arg.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o brights.o -c brights.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o hits.o -c hits.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o memory.o -c memory.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o linalg1.o -c linalg1.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o entex.o -c entex.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o create_points.o -c create_points.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o initialize_points.o -c initialize_points.c
	gcc -I $(INCLUDES) -g $(FLAGS) -o free_points.o -c free_points.c

	gcc $(OBJ) -g /usr/local/src/glad.c -o rtv1 ./libft/*.c -march=x86-64 -framework OpenCL -l glfw.3.3 -I $(INCLUDES)
		#C:\src\glad.c 

clean:
#	make -C libft/ clean
	rm -rf $(OBJ)
#	del $(OBJ)


fclean: clean
#	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all
	rm -rf $(OBJ)
