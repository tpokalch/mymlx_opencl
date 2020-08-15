
#include "mymlx.h"
#include <math.h>

t_fun_and_arg	user_pointer;


const char *vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in int aColor;\n"
//	"layout (location = 0) in vec3 aPos;\n"

//	"in int gl_VertexID;\n"
	"out vec3 outColor;\n"

	"uniform int width;\n"
	"uniform int height;\n"

	"vec3 rgb(int c)\n"
	"{\n"
/*	"       vec3 ret;\n"

		"int x = c / 65536;\n"
		"int b = c - x * 65536;\n"
		"int y = b / 256;\n"
		"int a = b - y * 256;\n"
		"int z = a;\n"

		"ret.x = x;\n"
		"ret.y = y;\n"
		"ret.z = z;\n"
*/
		"vec3		ret;\n"

//		"uint g = uint(-5);\n"
//		"if (g == uint(4294967291))\n"
//		"	return (vec3(1, 0, 0));\n"

		"uint a = uint(c);\n"
//a = //0x00FFFFFF

//0x00FFFFFF
		"a = a & uint(0x00FFFFFF);\n"

		"uint x = (a & uint(0x00FF0000));\n"
		"x = x >> 16;\n"

		"uint y = (a & uint(0x0000FF00));\n"
		"y = y >> 8;\n"

		"uint z = (a & uint(0x000000FF));\n"
		"z = z >> 0;\n"

//(a >> 0);\n"

		"ret.z = z;\n"
		"ret.y = y;\n"
		"ret.x = x;\n"
/*		"if (a > uint(255) || y > uint(255) || x > uint(255))\n"
		"{\n"
			"ret.z = ret.x = ret.y = 0;\n"
		"}\n"
*/
		"ret.x /= 255.0;\n"
		"ret.y /= 255.0;\n"
		"ret.z /= 255.0;\n"

/*
		"ret.x /= 255.0;\n"
		"ret.y /= 255.0;\n"
		"ret.z /= 255.0;\n"

*/

		"return (ret);\n"
	
	"}\n"

	"void main()\n"
	"{\n"
		"float xpixel = (gl_VertexID % width);\n"
		"float ypixel = (gl_VertexID / width);\n"

//		now xpixel and ypixel are in the range [0, 1]
		"xpixel = xpixel  / float(width);\n"
		"ypixel = ypixel  / float(height);\n"

//		now [-1, 1]
		"xpixel = 2 * xpixel - 1;\n"	
		"ypixel = -2 * ypixel + 1;\n"

		"gl_Position = vec4(xpixel, ypixel, 0, 1);\n"
//		"gl_Position = vec4(0, 0, 0, 1);\n"
 //   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"outColor = rgb(aColor);\n"
//		"outColor = vec3(1, 0, 0);\n"
	"}\0";

const char *fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 outColor;\n"

	"void main()\n"
	"{\n"

		"FragColor = vec4(outColor, 1);\n"
//		"FragColor = vec4(1, 0, 0, 1);\n"

	"}\0";

unsigned int    compileShader(const unsigned int type, const char* source)
{
	unsigned int thisShader;
	thisShader = glCreateShader(type);
	glShaderSource(thisShader, 1, &source, NULL);
	glCompileShader(thisShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(thisShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(thisShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::");
		if (type == GL_VERTEX_SHADER)
			printf("VERTEX");
		else if (type == GL_FRAGMENT_SHADER)
			printf("FRAGMENT");
		else if (type == GL_GEOMETRY_SHADER)
			printf("FRAGMENT");
		else if (type == GL_GEOMETRY_SHADER)
			printf("GEOMETRY");
		else
			printf("UNKNOWN_TYPE");
		printf("::COMPILATION_FAILED\n");
		printf("%s\n", infoLog);
	}
	return (thisShader);
}

int     compileProgram(const char *vertexShaderSource, const char *fragmentShaderSorce)
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	int ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n");
		printf("%s\n", infoLog);
	}

	glUseProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	printf("SUCCES COMPILE\n");
	return (ID);
}



void    *mlx_init()
{
//	user_pointer = malloc(sizeof(t_fun_and_arg));

	user_pointer.f[0] = NULL;
//      this causes a leak

	glfwInit();
	printf("glfwinit\n");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//      must do in mac, othrwise window == NULL
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	mlx *MLX = (mlx *)malloc(sizeof(mlx));
	return ((void *)MLX);
}

			//      not used
void    *mlx_new_window(void *mlx_ptr, int width, int height, const char *name)
{
	
	GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL)
	{
		glfwTerminate();
		printf("Couldn't open window\n");
		return (NULL);
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("GLAD failed");
		return (NULL);
	}

	printf("deref\n");
 	int ID = compileProgram(vertexShaderSource, fragmentShaderSource);
	printf("compiled\n");
	((mlx *)mlx_ptr)->ID = ID;

//      glEnable(GL_DEPTH_TEST);
//	this is sizecallback
//	glViewport(0, 0, width, height);

/*      glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
*/
	((mlx *)mlx_ptr)->width = width;
	((mlx *)mlx_ptr)->height = height;
	((mlx *)mlx_ptr)->window = window;

	return ((void *)window);
}
  /*  float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
*/

void    *mlx_new_image(void *mlx_ptr, int width, int height)
{


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	int     *img_ptr = (int *)malloc(sizeof(int) * width * height);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * width * height, (void *)img_ptr, GL_DYNAMIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 1, GL_FLOAT /*WHY NOT INT?*/, GL_FALSE, sizeof(int), (void *)0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

 	glEnableVertexAttribArray(0);

	return ((void *)img_ptr);


}

void    *mlx_get_data_addr(void *img_ptr, int *bpp, int *sz_l, int *e)
{
	*bpp = sizeof(int);
	*sz_l = 50;     //MAY HAVE PROBLEMS
	*e = 0;
	return (img_ptr);
}

//			      not used		not use		 not	     used
void    mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, int *img_ptr, int ignore1, int ignore2)
{
//      is this the same as model.draw?
//      no, same as updateVertices()
	mlx MLX = *(mlx *)mlx_ptr;
	int width = MLX.width;
	int height = MLX.height;
//	for (int i = 0; i < MLX.width * MLX.height; i++)
	{
		printf("img_ptr[i] is %d\n", img_ptr[width / 2 + width * height / 2]);
	}
	printf("puting i,age\n");
	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * MLX.width * MLX.height, img_ptr, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, MLX.width * MLX.height);
	glfwSwapBuffers(MLX.window);

//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("inside key callback\n");
	if (action == 0)
		return ;
	t_fun_and_arg *user_pointer = (t_fun_and_arg *)glfwGetWindowUserPointer(window);
//	key_press(key, param);
	user_pointer->f[2](key, user_pointer->param);
}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	printf("inside callback cursor is %f,%f\n", x, y);
	t_fun_and_arg *user_pointer = (t_fun_and_arg *)glfwGetWindowUserPointer(window);
//	key_press(key, param);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * 1000, img_ptr, GL_DYNAMIC_DRAW);
	printf("address in callback %p\n", user_pointer->param);
	(user_pointer->f[6])(lround(x), lround(y), user_pointer->param);
	glDrawArrays(GL_POINTS, 0, 1203);
}

//					ignore i
void	mlx_hook(void *win_ptr, int n, int i, int (*f) (), void *param)
{
//	t_fun_and_arg	user_pointer;
	user_pointer.f[n] = f;
	user_pointer.param = param;


	glfwSetWindowUserPointer((GLFWwindow *)win_ptr, &user_pointer);
	if (n == 2)
		glfwSetKeyCallback(win_ptr, key_callback);
//	else if (n == 4)
//		glfwSetMouseButtonCallback(win_ptr, mouse_button_callback);
	else if (n == 6)
		glfwSetCursorPosCallback(win_ptr, cursor_position_callback);
}

void	mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param)
{
	mlx *MLX = (mlx *)mlx_ptr;

	GLFWwindow *window = MLX->window;
	user_pointer.f[0] = f;
	user_pointer.param = param;
	glfwSetWindowUserPointer(window, &user_pointer);
}

void    processInput(GLFWwindow *window)
{
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, 1);
        //returns GLFW_RELEASE otherwise
	t_fun_and_arg *user_pointer = (t_fun_and_arg *)glfwGetWindowUserPointer(window);
	if (user_pointer->f[0])
		user_pointer->f[0](user_pointer->param);
}

void    mlx_loop(void *mlx_ptr)
{
	printf("looping\n");
	mlx *MLX = (mlx *)mlx_ptr;
	int numberofpixels = MLX->width * MLX->height;

	while (!glfwWindowShouldClose(MLX->window))
	{
//		printf("drawing loop\n");
//		printf("%d\n", numberofpixels);

		processInput(MLX->window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	        glClear(GL_COLOR_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int widthlocation = glGetUniformLocation(MLX->ID, "width");
		glUniform1i(widthlocation, MLX->width);

		int heightlocation = glGetUniformLocation(MLX->ID, "height");
		glUniform1i(heightlocation, MLX->height);



		glUseProgram(MLX->ID);
		glDrawArrays(GL_POINTS, 0, numberofpixels);

//		glDrawArrays(GL_POINTS, 0, 3);
		glfwSwapBuffers(MLX->window);
		glfwPollEvents();
	}
}














