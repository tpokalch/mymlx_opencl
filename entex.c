
#include "rtv1.h"

void check_error(cl_int err, const char* operation, char* filename, int line);
#define checkError(E, S) check_error(E,S,__FILE__,__LINE__)

void	debug(t_global *g)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (j < HEIGHT - 1)
	{
		i = 1;
		while (i < WIDTH - 1)
		{
			if ((g->data_ptr[j * HEIGHT + i + 1] == 0
			&& g->data_ptr[j * HEIGHT + i - 1] == 0)
			&& g->data_ptr[(j - 1) * HEIGHT + i] == 0
			&& g->data_ptr[(j + 1) * HEIGHT + i] == 0
			&& g->data_ptr[(j + 1)* HEIGHT + i + 1] == 0
			&& g->data_ptr[(j - 1) * HEIGHT + i - 1] == 0
			&& g->data_ptr[(j + 1) * HEIGHT + i - 1] == 0
			&& g->data_ptr[(j - 1) * HEIGHT + i + 1] == 0)
				g->data_ptr[j * HEIGHT + i] = 0;
			i++;
		}
		j++;
	}
}

void	save_im(int *a, int *c, int w, int h)
{
	int i = 0;
	int j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			*(c + j * w + i) = *(a + j * w + i);
			i++;
		}
		j++;
	}
}

int	myintmod(int x, int m)
{
	int ret;

	ret = fmod(x, m);
	if (x >= 0)
		return (ret);
	return (ret + m);
}


float	mymod(float x, int m)
{
	float ret;

	ret = fmod(x, m);
	if (x >= 0)
		return (ret);
	return (ret + m);
}

int		mid_col(int *a, int w, int h, int x, int y)
{
	t_vector vret;
	int s;
	int ret;

	s = 1;
//	ret = *(a + y * w + x);
	vret = rgb(*(a + y * w + x));
	if (x < w - 1)
	{
//		ret = ret + *(a + y * w + x + 1);
		vret = sum(vret, rgb(*(a + y * w + x + 1)));
		s++;
	}
	if (y < h - 1)
	{
		vret = sum(vret, rgb(*(a + y * w + x + w)));
//		ret = ret + *(a + (y + 1) * w + x);
		s++;
	}
	if (y < h - 1 && y < h - 1)
	{
		vret = sum(vret, rgb(*(a + y * w + x + 1 + w)));
//		ret = ret + *(a + (y + 1) * w + x + 1);
		s++;
	}
	vret = scale(1 / (float)s, vret);
	vret.x = lround(vret.x);
	vret.y = lround(vret.y);
	vret.z = lround(vret.z);
//	ret = ret / s;
	return (/*ret*/brg(vret));
}

void	rewrite_pix(int *a, int *o, int x, int y, int w, int h, int xmax, int ymax, t_global *g)
{
	t_vector mid_col;
	int			ran;
	int			ywx;

	ywx = y * w + x;
	ran = 1;
	mid_col = rgb(*(o + ywx));
	g->ray->x = x - h / 2;
	g->ray->y = -y + w / 2;

	if (x >= xmax + 1|| y >= xmax + 1)
		return ;
//	if (x > 0)
	{
		mid_col = sum(rgb(*(o + y * w + myintmod(x - 1, xmax))), mid_col);
		ran++;
	}
//	if (x < w - 1)
	{
		mid_col = sum(rgb(*(o + y * w + myintmod(x + 1, xmax))), mid_col);
		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
//	if (y > 0)
	{
		mid_col = sum(rgb(*(o + myintmod(y - 1, ymax) * w + x)), mid_col);
		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
//	if (y < h - 1)
	{
		mid_col = sum(rgb(*(o + myintmod(y + 1, ymax) * w + x)), mid_col);
		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
//	if (y < h - 1 && (x < w - 1))
	{
		mid_col = sum(rgb(*(o + myintmod(y + 1, ymax) * w + myintmod(x + 1, xmax))), mid_col);
		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
//	if (y < h - 1 && (x > 0))
	{
		mid_col = sum(rgb(*(o + myintmod(y + 1, ymax) * w + myintmod(x - 1, xmax))), mid_col);

		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
//	if (y > 0 && (x < w + 1))
	{
		mid_col = sum(rgb(*(o + myintmod(y - 1, ymax) * w + myintmod(x + 1, xmax))), mid_col);

		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
	if (y > 0 && x > 0)
	{
//		mid_col = sum(rgb(*(o + ywx - w - 1)), mid_col);
		mid_col = sum(rgb(*(o + myintmod(y - 1, ymax) * w + myintmod(x - 1, xmax))), mid_col);

		ran++;
//		if (con(g))
//			printf("sum is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);


	}
	mid_col = scale(1 / (float)ran, mid_col);
	mid_col.x = lround(mid_col.x);
	mid_col.y = lround(mid_col.y);
	mid_col.z = lround(mid_col.z);


	if (con(g))
	{
//		printf("after scale is %f,%f,%f\n", mid_col.x, mid_col.y, mid_col.z);
//		printf("rgbbgr %f,%f,%f\n", rgb(brg(mid_col)).x, rgb(brg(mid_col)).y, rgb(brg(mid_col)).z);
	}
	*(a + ywx) = brg(mid_col);
}


void	smooth(int *a, int w, int h, int xmax, int ymax, t_global *g)
{
	int i;
	int j;
	int *orig;

	i = 0;
	j = 0;
	orig = (int *)malloc(sizeof(int) * w * h + 1);
	save_im(a, orig, w, h);
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			rewrite_pix(a, orig, i, j, w, h, xmax, ymax, g);
			i++;
		}
		j++;
	}
}

void		alias(int *dst, int *a, int w, int xmax, int ymax, int h)
{
	int mid;
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < h / 2 && j < xmax)
	{
		i = 0;
		while (i < w / 2 && i < xmax)
		{
			*(dst + j * (w  ) + i) = mid_col(a, w, h, 2 * i, 2 * j);
			i++;
		}
		j++;
	}
}

extern int fd;

int		start_threads(void *f, t_global *g)
{
//#if 0
	// Execute the kernel over the entire range of our 1d input data set
	// letting the OpenCL runtime choose the work-group size
	size_t global = g->cl.count;
	printf("enque nd range buffer\n");
	int err = clEnqueueNDRangeKernel(g->cl.commands, g->cl.ko_vadd, 1, NULL, &global, NULL, 0, NULL, NULL);
	checkError(err, "Enqueueing kernel");

	// Wait for the g->cl.commands to complete before stopping the timer
	printf("executing...\n");
	err = clFinish(g->cl.commands);
	printf("done\n");
//	checkError(err, "Waiting for kernel to finish");

	// Read back the results from the compute device
	printf("reading back to the host\n");
	err = clEnqueueReadBuffer(g->cl.commands, g->cl.d_data_ptr, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT, g->data_ptr, 0, NULL, NULL);
	printf("done\n");
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to read output array!\n%s\n", err_code(err));
		exit(1);
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
//#endif
#if 0
	// Execute the kernel over the entire range of our 1d input data set
	// letting the OpenCL runtime choose the work-group size


	size_t global = g->cl.count;
	int err = clEnqueueNDRangeKernel(g->cl.commands, g->cl.ko_vadd, 1, NULL, &global, NULL, 0, NULL, NULL);
	checkError(err, "Enqueueing kernel");

	// Wait for the g->cl.commands to complete before stopping the timer
	printf("running commands...\n");
	err = clFinish(g->cl.commands);
	checkError(err, "Waiting for kernel to finish");


	// Read back the results from the compute device
	//err = clEnqueueReadBuffer( g->cl.commands, g->cl.d_data_ptr, CL_TRUE, 0, sizeof(float) * count, h_c, 0, NULL, NULL );  
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to read output array!\n%s\n", err_code(err));
		exit(1);
	}

	// Test the results
	int correct = 0;
	float tmp;

/*	for(int i = 0; i < count; i++)
	{
		tmp = h_a[i] + h_b[i];	 // assign element i of a+b to tmp
		tmp -= h_c[i];			 // compute deviation of expected and output result
		if(tmp*tmp < TOL*TOL)		// correct if square deviation is less than tolerance squared
			correct++;
		else {
			printf(" tmp %f h_a %f h_b %f h_c %f \n",tmp, h_a[i], h_b[i], h_c[i]);
		}
	}

	// summarise results
	printf("C = A+B:  %d out of %d results were correct.\n", correct, count);
*/
	// cleanup then shutdown
/*	clReleaseMemObject(d_a);
	clReleaseMemObject(d_b);
	clReleaseMemObject(d_c);
/
	clReleaseProgram(program);
	clReleaseKernel(g->cl.ko_vadd);
	clReleaseCommandQueue(g->cl.commands);
	clReleaseContext(context);

	free(h_a);
	free(h_b);
	free(h_c);
*/
#endif
}
