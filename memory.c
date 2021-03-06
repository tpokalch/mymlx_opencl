
#include "rtv1.h"

int		free_hits(t_global *g)
{
	int i;
	int j;

	i = -1;
	while (++i < HEIGHT && (j = -1))
		while(++j < WIDTH)
			free(*(*(g->hits + i) + j));
	i = -1;
	while (++i < HEIGHT)
		free(*(g->hits + i));
	free(g->hits);
	i = -1;
	while (++i < HEIGHT && (j = -1))
		while(++j < WIDTH)
			free(*(*(g->rays + i) + j));
	i = -1;
	while (++i < HEIGHT)
		free(*(g->rays + i));
	free(g->rays);

	i = -1;
        while (++i < CORES)
        {
                printf("freeing %d thread\n", i);
                free(g->tcps[i]->recursion);
                free(g->tcps[i]->cosa);
                free(g->tcps[i]);
        }
        // free objects and agragated resources, if any
        printf("free complex\n");
        i = 0;
        while (++i < g->argc + 1)
        {
                if (g->obj[i].name == complex)
                        free(g->obj[i].pts);
        }
        free(g->obj);
	free(g->li);
	free(g->liz);

	clReleaseMemObject(g->cl.d_data_ptr);
	clReleaseMemObject(g->cl.d_angle);
	clReleaseMemObject(g->cl.d_li);
//	clReleaseProgram(g->cl.program);
	clReleaseKernel(g->cl.ko_vadd);
	clReleaseCommandQueue(g->cl.commands);
//	clReleaseContext(context);
	return (1);
}

void		copy_obj(t_object *t, t_object *g)
{
	t = g;
//	t->tile = g->tile;
}
	
void		copy(t_global *tcps, t_global *g)
{
	tcps->win_ptr = g->win_ptr;
	tcps->mlx_ptr = g->mlx_ptr;
	tcps->img_ptr = g->img_ptr;
	tcps->data_ptr = g->data_ptr;
	tcps->bpp = g->bpp;
	tcps->sz_l = g->sz_l;
	tcps->e = g->e;
	tcps->core = g->core;
	tcps->light_switch = g->light_switch;
	tcps->ray = g->ray;
	tcps->angle = g->angle;
	tcps->normal = g->normal;
	tcps->li = g->li;
	tcps->cam_pos = g->cam_pos;

//	copy_obj(tcps->obj, g->obj);

	tcps->obj = g->obj;

	tcps->objn = g->objn;
	tcps->argc = g->argc;
	tcps->core = g->core;
	tcps->hits = g->hits;
	tcps->rays = g->rays;
	tcps->prim = g->prim;
	tcps->cone[0] = g->cone[0];
	tcps->cone[1] = g->cone[1];
	tcps->ambient = g->ambient;
	tcps->base[0] = g->base[0];
	tcps->base[1] = g->base[1];
//	tcps->base[1].y = -1;
	tcps->base[2] = g->base[2];

	tcps->line_taken = g->line_taken;
//	tcps->e1 = g->e1;
//	tcps->sz_l1 = g->sz_l1;
//	tcps->bpp1 = g->bpp1;
//	tcps->tile_data_ptr = g->tile_data_ptr;
	tcps->mip_map = g->mip_map;
	tcps->recursion = g->recursion;
	tcps->lights = g->lights;
	tcps->white = g->white;
	tcps->hitli = (t_vector *)malloc(sizeof(t_vector) * g->lights);
	tcps->savehitli = (t_vector *)malloc(sizeof(t_vector) * g->lights);
	tcps->cosa = (float *)malloc(sizeof(float) * g->lights);
	tcps->recursion = (int *)malloc(sizeof(int) * (g->argc + 1));
	ft_bzero(tcps->recursion, sizeof(int) * (g->argc + 1));
	//	tcps->ctrli = (t_vector *)malloc(sizeof(t_vector) * g->lights);
}

void		copy_tcps(t_global *g)
{
	int i;

	i = -1;
	while (++i < CORES)
	{
		copy(g->tcps[i], g);
		g->tcps[i]->core = i;
	}
}

void		init_hits(t_objecthit ***hits)
{
	int i;
	int j;

	i = -1;
	while (++i < HEIGHT)
		*(hits + i) = (t_objecthit **)malloc(sizeof(t_objecthit) * WIDTH + 1);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while(++j < WIDTH)
			*(*(hits + i) + j)= (t_objecthit *)malloc(sizeof(t_objecthit));
	}
}

void		init_rays(t_vector ****ray)
{
	int i;
	int j;

	(*ray) = (t_vector ***)malloc(sizeof(t_vector **) * HEIGHT + 1);
	i = -1;
	while (++i < HEIGHT)
		*(*ray + i) = (t_vector **)malloc(sizeof(t_vector) * WIDTH + 1);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while(++j < WIDTH)
			*(*(*ray + i) + j)= (t_vector *)malloc(sizeof(t_vector));
	}
}
