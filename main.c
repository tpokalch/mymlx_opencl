

#include "rtv1.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "err_code.h"

#endif

int			con(t_global *g)
{
	return (shot.x == g->ray->x && shot.y == g->ray->y);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_global *g;
	t_object a;

	g = param;
//	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (button == 1)
	{
		shot.x = -WIDTH / 2 + x;
		shot.y = HEIGHT / 2 - y;
		printf("\n%f, %f\n", shot.x, shot.y);
//		a = g->obj[g->objn];
//		printf("object is %d %s %f, %f, %f\n%f,%f, %f\n", g->objn, a.name, a.ctr->x, a.ctr->y, a.ctr->z, a.nr.x, a.nr.y, a.nr.z);
		printf("\nmouse press -> realc\n");
		start_threads(recalc, g);
//		start_threads(toimg, g);
	}
	return (1);
}

int	loop(void *p)
{
	t_global *g = (t_global *)p;
	g->li->x += 10;
	*g->cam_pos = diff(*g->cam_pos, *g->normal);
	printf("loop starting threads\n");
	start_threads(move, g);
	return (1);
}

void		free_arr(char **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
	{
		printf("now freeing %s\n", *(arr + i));
		free(*(arr + i));
		i++;
	}
}

int		putstr(char *s, int ret)
{
	int i;

	i = 0;
	while (*(s + i) != '\0')
	{
		write(1, s + i, 1);
		i++;
	}
	return (ret);
}

/*
void		screen(int *a, int x, int y, t_global *g)
{
	int i = 0;
	int j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			mlx_pixel_put(g->mlx_ptr, g->win_ptr, i, j, *(a + j * x + i));
			i++;
		}
		j++;
	}
}
*/
/*
void		draw_vectile(t_vector *t, int w, int h, t_global *g)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
//			printf("we are at %d,%d\n", i, j);
			mlx_pixel_put(g->mlx_ptr, g->win_ptr, i, j, brg(scale(255, *(t + j * h + i))));
			i++;
		}
		j++;
	}
}

void		draw_func(t_global *g)
{
	int i = -WIDTH / 2;

	while (i < WIDTH / 2)
	{
		mlx_pixel_put(g->mlx_ptr, g->win_ptr, i + WIDTH / 2, HEIGHT / 2- 20 * acos(i / (float)20), 0xFFFFFF);
		i++;
	}
}
*/

void* loadfile(char* file, int* size)
{
	printf("loading file\n");
	FILE* fp;
	long lSize;
	char* buffer;

	int fd = open(file, O_RDONLY);
	printf("fd is %d\n", fd);
	close(fd);
	fp = fopen(file, "rb");
	printf("fp is %p\n", fp);
	if (!fp) perror(file), exit(1);

	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	printf("size is %d\n", lSize);
	/* allocate memory for entire content */
	buffer = calloc(1, lSize + 2);
	if (!buffer) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

	printf("readinf file\n");
	/* copy the file into the buffer */
	if (1 != fread(buffer, lSize, 1, fp))
		fclose(fp), free(buffer), fputs("entire read fails", stderr), exit(1);
	printf("file read 1\n");
	/* do your work here, buffer is a string contains the whole text */
	size = (int*)lSize;
	//buffer[*size] = '\0'; //Taras add
	fclose(fp);
	printf("file read 2\n");
	return buffer;
}

void	clinit(t_global *g, t_vector *ctr)
{
	int          err;               // error code returned from OpenCL calls

	t_object *h_obj = g->obj;       // a vector
	t_vector *h_li = g->li;       // b vector
	t_vector *h_angle = g->angle;       // angle vector
	t_vector *h_cam_pos = g->cam_pos;       // cam pos
	t_vector* h_base = g->base;
	t_vector* h_ctr = ctr;

	printf("center 1 is %d,%d,%d\n", h_ctr[0].x, h_ctr[0].y, h_ctr[0].z);
	printf("center 2 is %d,%d,%d\n", h_ctr[1].x, h_ctr[1].y, h_ctr[1].z);

	int* h_data_ptr = g->data_ptr;       // c vector (a+b) returned from the compute device

	unsigned int correct;           // number of correct results

	size_t global;                  // global domain size

	cl_device_id     device_id;     // compute device id
	cl_context       context;       // compute context
	cl_command_queue commands;      // compute command queue
	cl_program       program;       // compute program
	cl_kernel        ko_vadd;       // compute kernel



	// Fill vectors a and b with random float values

	int count = WIDTH * HEIGHT;
/*	int i = 0;

	for (i = 0; i < count; i++) {
		h_a[i] = rand() / (float)RAND_MAX;
		h_b[i] = rand() / (float)RAND_MAX;
	}
	*/
	// Set up platform and GPU device

	cl_uint numPlatforms;

	// Find number of platforms
	err = clGetPlatformIDs(0, NULL, &numPlatforms);
	checkError(err, "Finding platforms");
	if (numPlatforms == 0)
	{
		printf("Found 0 platforms!\n");
		return ;
	}
	printf("here\n");
	// Get all platforms
	printf("getting platforms\n");
	cl_platform_id Platform[numPlatforms];
	err = clGetPlatformIDs(numPlatforms, Platform, NULL);
	checkError(err, "Getting platforms");
	printf("here\n");
	// Secure a GPU
	for (int i = 0; i < numPlatforms; i++)
	{
		err = clGetDeviceIDs(Platform[i], CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
		if (err == CL_SUCCESS)
		{
			break;
		}
	}
	printf("here\n");
	if (device_id == NULL)
	checkError(err, "Finding a device");

	//err = output_device_info(device_id);
	//checkError(err, "Printing device output");

	// Create a compute context
	context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
	checkError(err, "Creating context");

	// Create a command queue
	commands = clCreateCommandQueue(context, device_id, 0, &err);
	checkError(err, "Creating command queue");
	printf("here\n");
	// Create the compute program from the source buffer

	int len;
	char* KernelSource = loadfile("./kernel.cl", &len);

	printf("creating program with source\n");
	program = clCreateProgramWithSource(context, 1, (const char**)&KernelSource, NULL, &err);
	checkError(err, "Creating program");
	printf("here\n");
	// Build the program
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		size_t len;
		char buffer[999999];

		printf("Error: Failed to build program executable!\n%s\n", err_code(err));
													//param name    param_value_size param_value
		err = clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 999999, buffer, &len);
		printf("clGetProgramBuildInf == %s\n", err_code(err));
		printf("%s\n", buffer);
		return ;
	}
	printf("here\n");
	// Create the compute kernel from the program
	ko_vadd = clCreateKernel(program, "vadd", &err);
	checkError(err, "Creating kernel");

	cl_mem d_obj;                     // device memory used for the input  a vector
	cl_mem d_li;                     // device memory used for the input  b vector
	cl_mem d_cam_pos;                     // device memory used for the input cam_pos
	cl_mem d_angle;                     // device memory used for the input cam angle
	cl_mem d_base;                     // device memory used for the bases
	cl_mem d_ctr;                     // device memory used for the bases

	//cl_mem g->cl.d_data_ptr;                     // device memory used for the output c vector

	// Create the input (a, b) and output (c) arrays in device memory
	d_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_object) * g->objn, NULL, &err);
	checkError(err, "Creating buffer d_a");

	d_li = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_vector) * 1, NULL, &err);
	checkError(err, "Creating buffer d_b");

	d_cam_pos = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_vector) * 1, NULL, &err);
	checkError(err, "Creating buffer d_cam_pos");

	d_angle = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_vector) * 1, NULL, &err);
	checkError(err, "Creating buffer d_angle");

	d_base = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_vector) * 3, NULL, &err);
	checkError(err, "Creating buffer d_base");

	d_ctr = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_vector) * g->objn, NULL, &err);
	checkError(err, "Creating buffer d_base");


	g->cl.d_data_ptr = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * count, NULL, &err);
	checkError(err, "Creating buffer d_c");

	// Write a and b vectors into compute device memory
	err = clEnqueueWriteBuffer(commands, d_obj, CL_TRUE, 0, sizeof(t_object) * g->objn, h_obj, 0, NULL, NULL);
	checkError(err, "Copying h_a to device at d_a");

	err = clEnqueueWriteBuffer(commands, d_li, CL_TRUE, 0, sizeof(t_vector) * g->lights, h_li, 0, NULL, NULL);
	checkError(err, "Copying h_b to device at d_b");

	err = clEnqueueWriteBuffer(commands, d_angle, CL_TRUE, 0, sizeof(t_vector) * g->lights, h_angle, 0, NULL, NULL);
	checkError(err, "Copying h_b to device at d_b");

	err = clEnqueueWriteBuffer(commands, d_cam_pos, CL_TRUE, 0, sizeof(t_vector) * 1, h_cam_pos, 0, NULL, NULL);
	checkError(err, "Copying h_b to device at d_b");

	err = clEnqueueWriteBuffer(commands, d_base, CL_TRUE, 0, sizeof(t_vector) * 3, h_base, 0, NULL, NULL);
	checkError(err, "Copying h_b to device at d_base");

	err = clEnqueueWriteBuffer(commands, d_ctr, CL_TRUE, 0, sizeof(t_vector) * g->objn, h_ctr, 0, NULL, NULL);
	checkError(err, "Copying h_b to device at d_ctr");

	// Set the arguments to our compute kernel
	err = clSetKernelArg(ko_vadd, 0, sizeof(cl_mem), &d_obj);
	err |= clSetKernelArg(ko_vadd, 1, sizeof(cl_mem), &d_li);
	err |= clSetKernelArg(ko_vadd, 2, sizeof(cl_mem), &d_cam_pos);
	err |= clSetKernelArg(ko_vadd, 3, sizeof(cl_mem), &d_angle);
	err |= clSetKernelArg(ko_vadd, 4, sizeof(cl_mem), &d_base);
	err |= clSetKernelArg(ko_vadd, 5, sizeof(cl_mem), &d_ctr);

	err |= clSetKernelArg(ko_vadd, 6, sizeof(cl_mem), &g->cl.d_data_ptr);
	err |= clSetKernelArg(ko_vadd, 7, sizeof(unsigned int), &count);
	printf("Setting kernel arguments\n");
	checkError(err, "Setting kernel arguments");
}

//	for the video
int fd; 

int		main(int argc, char **argv)
{
	t_global g;
	t_vector ctr[argc];
	t_vector kenobi[5];
	int h;
	int w;



//	fd = open("./video", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	h = WIDTH;
	w = HEIGHT;
	g.cam_pos = &kenobi[0];
	g.angle = &kenobi[1];
	g.ray = &kenobi[2];
	g.li = &kenobi[3];
	g.normal = &kenobi[4];
	
	printf("mlx init\n");
	//g.mlx_ptr = mlx_init();
	//g.win_ptr = mlx_new_window(g.mlx_ptr, WIDTH, HEIGHT, "window1");
	printf("ginit\n");
	ginit(&g);
	printf("check arg\n");
	if (!check_arg(argv, argc, &g, ctr))
		return (0);
	printf("new image\n");

	//g.img_ptr = mlx_new_image(g.mlx_ptr, WIDTH, HEIGHT);
	//g.data_ptr = (int *)mlx_get_data_addr(g.img_ptr, &g.bpp, &g.sz_l, &g.e);
//	g.win_ptr = mlx_new_window(g.mlx_ptr, WIDTH, HEIGHT, "window1"); must include earlier
	cl_uint numPlatforms;

	// Find number of platforms
	int err = clGetPlatformIDs(0, NULL, &numPlatforms);
	checkError(err, "Finding platforms");
	if (numPlatforms == 0)
	{
		printf("Found 0 platforms!\n");
		return 0;
	}
	else
	{
		printf("found %d platforms\n", numPlatforms);
	}
	clinit(&g, ctr);
	//copy_tcps(&g);
	printf("starting threads\n");
	start_threads(recalc, &g);
//	mlx_hook(g.win_ptr, 4, 4, mouse_press, &g);
	mlx_hook(g.win_ptr, 2, 2, key_press, &g);
	mlx_hook(g.win_ptr, 6, 6, mouse_move, &g);
//	mlx_loop_hook(g.mlx_ptr, loop, &g);
	mlx_loop(g.mlx_ptr);
}
