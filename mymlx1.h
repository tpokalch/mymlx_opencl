
typedef	struct	s_mlx
{
	int ID;
	int width;
	GLFWwindow *window;
}		mlx;

const char *vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in int aColor;\n"
	"in int gl_VertexID;\n"
	"out vec3 outColor;\n"

	"uniform int width;\n"

	"vec3 rgb(int c)\n"
	"{\n"
	"	vec3 ret;\n"

		"ret.x = c / (65536);\n"
		"c = c - ret.x * 65536;\n"
		"ret.y = c / (256);\n"
		"c = c - ret.y * 256;\n"
		"ret.z = c;\n"
		"return (ret);\n"
	"}\n"

	"void main()\n"
	"{\n"
		"gl_Position = vec4(gl_VertexID % width, gl_VertexID / width, 0, 1);\n"
		"outColor = rgb(aColor);\n"
	"}\0"

const char *fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 outColor;\n"

	"void main()\n"
	"{\n"
		"FragColor = vec4(outColor, 1);\n"
	"}\0"

unsigned int    compileShader(const unsigned int &type, const char* &source)
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
		std::cout << "ERROR::SHADER::";

		if (type == GL_VERTEX_SHADER)
			std::cout << "VERTEX";
		else if (type == GL_FRAGMENT_SHADER)
			std::cout << "FRAGMENT";
		else if (type == GL_GEOMETRY_SHADER)
			std::cout << "GEOMETRY";
		else
			std::cout << "UNKNOWN_TYPE";
		std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return (thisShader);
}

int	compileProgram(const char *vertexShaderSource, const char *fragmentShaderSorce)
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	int ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return (ID);
}



void	*mymlx_init()
{
//	this causes a leak
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//	must do in mac, othrwise window == NULL
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	mlx *MLX = (mlx *)malloc(sizeof(mlx));
	MLX->ID = compileProgram(vertexShaderSource, fragmentShaderSource);
	return ((void *)MLX);
}

			//	not used
void	*mymlx_new_window(void *mlx_ptr, int width, int height, const char *name)
{
	GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL)
	{
		glfwTerminate();
		throw "Couldn't open window";
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw "GLAD failed";
	}
//	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);

/*	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
*/
	((mlx *)mlx_ptr)->width = width;
	((mlx *)mlx_ptr)->window = window;

	return ((void *)window);
}

void	*mymlx_new_image(void *mlx_ptr, int width, int height)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 1, GL_INT, GL_FALSE, sizeof(int), (void *)0);

	int	*vertices = (int *)malloc(sizeof(int) * width * height);
	return ((void *)vertices);
}


//				not used		not use			not		used
void	mymlx_put_image_to_window(void *mlx_ptr, void *win_ptr, int *img_ptr, int ignore1, int ignore2)
{
//	is this the same as model.draw?
//	no, same as updateVertices()
	glBufferData(GL_ARRAY_BUFFER, sizeof(img_ptr), img_ptr, GL_DYNAMIC_DRAW);
}

void	mymlx_loop(void *mlx_ptr)
{
	mlx *MLX = (mlx *)mlx_ptr;
	int numberofpixels = width * height;
	while (!glfwWindowShouldClose(MLX->window))
	{
		processInput(MLX->window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width_location = glGetUniformLocation(myShader.ID, "width");
		glUniform1i(width_location, width);

		glUseProgram(MLX->ID);

		glDrawArrays(GL_POINTS, 0, numberofpixels);
	}
}

















