
#pragma OPENCL EXTENSION cl_intel_printf : enable

//#include <math.h>
//#include "mymlx.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include "libft/libft.h"
//#include <strings.h>


#define WIDTH 200
#define HEIGHT 100
#define HEIGHT_2 50
#define WIDTH_2 100



#define TASK 20
#define STRIPS HEIGHT / TASK
#define CORES 2
#define M_T 6.28318530718f
#define MAX_REC 4
#define RECORD_VIDEO 0

//typedef	struct	s_vector t_vector;


typedef struct s_vector
{
	float x;
	float y;
	float z;
//	int	len;
}			t_vector;



typedef struct		s_global t_global;
typedef	struct		s_object t_object;
typedef	struct		s_objecthit t_objecthit;
typedef struct		s_dstpst	t_dstpst;

typedef	struct		s_colbri
{
	t_vector col;
	int	bri;
}			t_colbri;


int				brg(t_vector rgb);
int				inside_cone(t_vector p, t_object o, t_global *g);
float				tarasDot(t_vector a, t_vector b);
t_vector			diff(t_vector a, t_vector b);
t_vector			sum(t_vector a, t_vector b);
t_vector			norm(t_vector a);
int					color(int b, t_vector c);
t_vector			scale(float a, t_vector b);
void				ginit(t_global *g);
void				init_plane(t_vector *ctr, int i, t_global *g);
void				init_cylinder(t_vector *ctr, int i, t_global *g);
void				init_sphere(t_vector *ctr, int i, t_global *g);
void				init_spheror(t_vector *ctr, int i, t_global *g);
void				init_cone(t_vector *ctr, int i, t_global *g);
void				init_tri(t_vector *ctr, int i, t_global *g);
void				init_complex(t_vector *ctr, int i, t_global *g);


int					check_arg(char **argv, int argc, t_global *g, t_vector *ctr);
int					usage(void);
int					arg_valid(char **argv);
int					fill_objects(t_vector *ctr, char **argv, t_global *g);
void				fill_obj(char **argv, int n, t_global *g);
void				vectorify(void *obj_coord, char **argv);
int					is_coords(char *argv);
int					putstr(char *s, int ret);
void				free_arr(char **arr);
int					init_objects(t_vector *ctr, char **argv, t_global *g);
int					obj_traver(char **argv, char *c);
void				init_rays(t_vector ****ray);
void				init_hits(t_objecthit ***hits);
int					key_press(int kk, void *param);
void				copy_tcps(t_global *g);
void				copy(t_global *tcps, t_global *g);
int					move_obj(int kk, t_global *g);
int					move_phys(int keycode, t_global *g);
void				move_cam(char s, t_global *g);
int				campos(t_global *g);
int					free_hits(t_global *g);
int					start_threads(void *f, t_global *g);
int					mouse_move(int x, int y, void *param);
void				debug(t_global *g);
void				*move(void *p);
void				*toimg(void *tcp);

void				objecthit(t_dstpst *ret, t_vector st, t_vector end, __global t_object *obj, int objc, t_global *g);

t_dstpst			hit_plane(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g);
t_dstpst			hit_sphere(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g);
t_dstpst			hit_cylinder(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g);
t_dstpst			hit_cone(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g);
t_dstpst			hit_tri(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g);
t_dstpst			hit_complex(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g);

t_colbri				simple_bright_plane(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri				bright_plane(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					bright_sphere(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					simple_bright_sphere(t_vector st, t_vector hit, t_object *obj, t_global *g);

t_colbri					bright_cylinder(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					simple_bright_cylinder(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					bright_cone(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					simple_bright_cone(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					bright_tri(t_vector st, t_vector hit, t_object *obj, t_global *g);
t_colbri					simple_bright_tri(t_vector st, t_vector hit, t_object *obj, t_global *g);


t_vector			get_normal_sphere(t_vector point, __global t_object *obj);
t_vector			get_normal_plane(t_vector point, __global t_object *obj);
t_vector			get_normal_cyl(t_vector point, t_object *obj);
t_vector			get_normal_cone(t_vector point, t_object *obj);




void				alias(int *dst, int *a, int w, int h, int xmax, int ymax);

t_dstpst			*NANI(t_dstpst *t);
void					obstructed(t_colbri *i, t_vector hit, t_vector *hitli, t_vector reflrayv, t_object obj, t_global *g);
t_vector			tarasRotate(t_vector ray, t_vector angle);
void				init_vector(t_vector *current, float x, float y, float z);
int				con(t_global *g);
t_vector			rgb(int c);
t_vector			base(t_vector c);
int				pinside(t_vector p, t_vector bd1, t_vector bd2, t_vector bd3, t_vector nr, t_global *g);
void				screen(int *a, int w, int h, t_global *g);

t_vector			tarasCross(t_vector a, t_vector b);
float				det(t_vector a, t_vector b);
void				stretch(int *a, int d, int h);
void				smooth(int *a, int w, int h, int xmax, int ymax, t_global *g);
void				save_im(int *a, int *b, int w, int h);
t_vector			base255(t_vector);
void				white(int *a, int w, int h, int c);
t_vector			**initialize_points(int height);
t_vector			**create_points(char *filename, t_vector *ptdim, t_global *g);
void				free_points(t_vector **pts);
float				mymod(float x, int m);
float				myacos(t_vector ax, t_vector v, t_vector nrm, t_global *g);
int				myintmod(int x, int m);
int				left(t_vector a, t_vector b, t_vector nrm, t_global *g);
float				tothe2(float x, int e);

void		do_tile_sphere(t_vector hit, t_object *obj, t_global *g);
void		do_re(t_vector refl, t_vector hit, t_vector *retcol, t_object obj, t_global *g);
void		do_trans(t_vector st, t_vector hit, t_colbri *ret, t_object obj, t_global *g);


void		do_spec(t_colbri *ret, t_vector hit, t_vector nrm, t_vector reflrayv, t_object obj, t_global *g);

void		do_1_spec(t_colbri *tmp, t_colbri *ret, t_vector *hitli, t_vector reflrayv, t_object obj, int i, t_global *g);
float		len2(t_vector a);

typedef	struct		s_tile
{
	int bpp;
	int sz_l;
	int e;
	int w;
	int h;
	int w2;
	int h2;
	int mipq;
	int *data_ptr;
	t_vector *vectile;
	void *ptr;
}			t_tile;

typedef struct		s_object
{
	char			*name;
	int				id;
	int				cam_pos;
	t_dstpst		(*hit)(t_vector, t_vector, t_vector, t_object, t_global *g);
	t_colbri				(*bright)(t_vector, t_vector, t_object *, struct s_global *);
	t_colbri				(*simple_bright)(t_vector, t_vector, t_object *, struct s_global *);
	t_vector				(*get_normal)(t_vector, t_object *);


	t_vector		bd1;
	t_vector		bd2;
	t_vector		bd3;
	t_vector		base[3];
	t_vector		nr;
	t_vector		real_nr;
	t_tile			tile[15];
	t_tile			normal_map;
	__global t_vector		*ctr;
	t_vector		ang;
	t_vector		color;
	int				rd;
	int				rd2;
	float				rd_1; // 1 / rd
	void			(*prop[3])();
	t_vector		**pts;
	__global t_object		*tris;
	float			re;
	float			trans;
	int			spec;
	int			soft;
	t_vector		ptdim;
	t_object		*frame;
	t_vector		box[8];
}		t_object;

struct		s_dstpst
{
	float	dst;
	float	pst;
	t_object obj;
};

typedef	struct		s_objecthit
{
	t_object obj;
	t_vector hit;
}				t_objecthit;

typedef struct		s_global
{
	void 			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*data_ptr;
	int				bpp;
	int				sz_l;
	int				e;
	int				light_switch;
	t_dstpst		cone[2];
	t_vector		_0015;
	t_vector		white;
	t_vector		base[3];
	t_vector		*ray;
	__global t_vector		*li;
	__global t_vector		*cam_pos;
	float			*liz;
	__global t_vector		*angle;
	t_vector		*normal;
	__global t_object		*obj;
	t_object		*all_obj;
	t_objecthit		***hits;
	t_vector		***rays;
	int				objn;
	int				argc;
	int				core;
	int				prim;
	int				ambient;
	int				my_line;
	int				*line_taken;//size of number of tasks
	int				mip_map;
	int				lights;
	t_vector			*hitli;
	t_vector			*savehitli;
	t_vector			prev;
	float				*cosa;
	t_vector			*ctrli;
	int					*recursion;
	t_global		*tcps[CORES];
}				t_global;


//////////////////////////////////////////////////////////////////////////////////
//				LINALG1.C					//
//////////////////////////////////////////////////////////////////////////////////

float           myacos(t_vector ax, t_vector v, t_vector nrm, t_global *g)
{
	float ret;

	ret = acos(tarasDot(ax, v));
        if (ret > M_PI_F || left(v, ax, nrm, g))
	{
		return (M_T - ret);
	}
	return (ret);
}

void		init_vector(t_vector *i, float x, float y, float z)
{
	i->x = x;
	i->y = y;
	i->z = z;
}

t_vector		tarasCross(t_vector a, t_vector b)
{
	t_vector ret;

	ret.x = a.z * b.y - a.y * b.z;
	ret.y = a.x * b.z - a.z * b.x;
	ret.z = a.y * b.x - a.x * b.y;

//	ret = scale(-1, ret);
	return (ret);
}

int			left(t_vector a, t_vector b, t_vector nr, t_global *g)
{
	return (tarasDot(tarasCross(b, a), nr) >= -0.000004f);
}

int			pinside(t_vector p, t_vector bd1, t_vector bd2, t_vector bd3, t_vector nr, t_global *g)
{
	t_vector bd[3];
	t_vector pt[3];

	bd[0] = diff(bd2, bd1);
	bd[1] = diff(bd3, bd2);
	bd[2] = diff(bd1, bd3);
	pt[0] = diff(p, bd1);
	pt[1] = diff(p, bd2);
	pt[2] = diff(p, bd3);
	return (left(pt[0], bd[0], nr, g)
		&& left(pt[2], bd[2], nr, g)
		&& left(pt[1], bd[1], nr, g));
}

float			det(t_vector a, t_vector b)
{
	return (a.x * b.z - a.z * b.x);
}

t_vector		tarasRotate(t_vector ray, t_vector angle)
{
	t_vector ret;
	t_vector cxcycz;
	t_vector sxsysz;
	t_vector opt;
	t_vector row[3];

	if (angle.x == 0 && angle.y == 0 && angle.z == 0)
		return (ray);
	init_vector(&cxcycz, cos(angle.x), cos(angle.y), cos(angle.z));
	init_vector(&sxsysz, sin(angle.x), sin(angle.y), sin(angle.z));
	init_vector(&opt, cxcycz.z * sxsysz.x,
	cxcycz.z * cxcycz.x, sxsysz.z * sxsysz.y);
	init_vector(&row[0], cxcycz.z * cxcycz.y,  -sxsysz.z * cxcycz.x
	+ opt.x * sxsysz.y, sxsysz.z * sxsysz.x + opt.y * sxsysz.y);
	init_vector(&row[1], sxsysz.z * cxcycz.y, opt.y
	+ opt.z * sxsysz.x, -opt.x + opt.z * cxcycz.x);
	init_vector(&row[2], -sxsysz.y, cxcycz.y * sxsysz.x, cxcycz.y * cxcycz.x);
	init_vector(&ret, tarasDot(row[0], ray), tarasDot(row[1], ray), tarasDot(row[2], ray));
	return (ret);
}

float				len2(t_vector a)
{
	return (tarasDot(a, a));
}

float				tothe2(float x, int e)
{
	int i;

	i = -1;
	while (++i < e)
		x = x * x;
	return (x);
}

t_dstpst			*NANI(t_dstpst *t)
{
	t->dst = NAN;
	t->obj.id = -1;
	return (t);
}

//////////////////////////////////////////////////////////////////////////////////
//				LIN_ALG.C					//
//////////////////////////////////////////////////////////////////////////////////

t_vector	scale(float a, t_vector b)
{
	b.x *= a;
	b.y *= a;
	b.z *= a;
	return (b);
}

float		tarasDot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	norm(t_vector a)
{
	float leng;

	leng = sqrt(tarasDot(a, a));
	a.x = a.x / (float)leng;
	a.y = a.y / (float)leng;
	a.z = a.z / (float)leng;
	return (a);
}

t_vector	sum(t_vector a, t_vector b)
{
	a.x = b.x + a.x;
	a.y = b.y + a.y;
	a.z = b.z + a.z;
	return (a);
}

t_vector	diff(t_vector a, t_vector b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;
	a.z = a.z - b.z;
	return (a);
}



//////////////////////////////////////////////////////////////////////////
//				COLOR.C					//
//////////////////////////////////////////////////////////////////////////


int			brg(t_vector a)
{
//	return (a.z + a.y * 256 + a.x * 65536);
	return (((unsigned int)a.x << 16) +
		((unsigned int)a.y << 8) +
		((unsigned int)a.z));
}

t_vector	rgb(int c)
{
	t_vector	ret;

	unsigned int a = c;

	ret.x = (a >> 16);
	a = (a & (0x00FFFF));
	ret.y = (a >> 8);
	a = (a & (0x0000FF));
	ret.z = a;

	return (ret);
}

t_vector	base255(t_vector dir)
{
	dir.x = dir.x / (float)255;
	dir.y = dir.y / (float)255;
	dir.z = dir.z / (float)255;
	return (dir);
}

t_vector	base(t_vector dir)
{
	float		max;

	max = fmax(dir.x, fmax(dir.y, dir.z));
	dir.x = dir.x / (float)max;
	dir.y = dir.y / (float)max;
	dir.z = dir.z / (float)max;
	return (dir);
}

int			color(int b, t_vector v)
{
//	v = base(c);
	v.x = round(b * v.x); //taraschange to round for opencl
	v.y = round(b * v.y);
	v.z = round(b * v.z);

	v.x = ((unsigned int)v.x << 16);
	v.y = ((unsigned int)v.y << 8);
	return(v.x + v.y + v.z);
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//							HITS.C				      	//
//////////////////////////////////////////////////////////////////////////////////////////////////

int 		hit_quad(t_vector st, t_vector end,  t_vector ray, t_vector quad[4], t_global *g)
{
	t_vector tri[2][3];
	t_object obj[2];


	tri[0][0] = quad[0];
	tri[0][1] = quad[1];
	tri[0][2] = quad[2];

	tri[1][0] = quad[1];
	tri[1][1] = quad[2];
	tri[1][2] = quad[3];

//	obj[0].nr = norm(tarasCross(diff(tri[0][0], tri[0][2]), diff(tri[0][1], tri[0][2])));
//	obj[1].nr = norm(tarasCross(diff(tri[1][0], tri[1][2]), diff(tri[1][1], tri[1][2])));

	obj[0].bd1 = tri[0][0];
	obj[0].bd2 = tri[0][1];
	obj[0].bd3 = tri[0][2];

	obj[1].bd1 = tri[1][0];
	obj[1].bd2 = tri[1][1];
	obj[1].bd3 = tri[1][2];
	t_dstpst hit[2];

	hit[0] = hit_tri(st, end, ray, obj[0], g);
	hit[1] = hit_tri(st, end, ray, obj[1], g) ;

	return ((hit[0].dst > 0 || hit[0].dst <= 0) || (hit[1].dst > 0 || hit[1].dst <= 0));
}

int		hit_box(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_vector	quad[6][4];

	quad[0][0] = obj.box[0];
	quad[0][1] = obj.box[1];
	quad[0][2] = obj.box[2];
	quad[0][3] = obj.box[3];

	quad[1][0] = obj.box[0];
	quad[1][1] = obj.box[1];
	quad[1][2] = obj.box[4];
	quad[1][3] = obj.box[5];


	quad[2][0] = obj.box[1];
	quad[2][1] = obj.box[2];
	quad[2][2] = obj.box[5];
	quad[2][3] = obj.box[6];

	quad[3][0] = obj.box[3];
	quad[3][1] = obj.box[7];
	quad[3][2] = obj.box[6];
	quad[3][3] = obj.box[2];

	quad[4][0] = obj.box[4];
	quad[4][1] = obj.box[5];
	quad[4][2] = obj.box[6];
	quad[4][3] = obj.box[7];

	quad[5][0] = obj.box[0];
	quad[5][1] = obj.box[4];
	quad[5][2] = obj.box[7];
	quad[5][3] = obj.box[3];

/*	int hit[6];
	int i = 0;
	while (i < 6)
	{
		hit[i] = hit_quad(stm  ray, quad[i]);
		printf("
		i++;

	}
*/
	return (hit_quad(st, end, ray, quad[0], g) ||
		hit_quad(st, end, ray, quad[1], g) ||
		hit_quad(st, end, ray, quad[2], g) ||
		hit_quad(st, end, ray, quad[3], g) ||
		hit_quad(st, end, ray, quad[4], g) ||
		hit_quad(st, end, ray, quad[5], g));
}

t_dstpst	hit_complex(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_dstpst t;
	t_dstpst framecheck;

	framecheck = hit_sphere(st, end, ray, *(obj.frame), g);
	if (framecheck.obj.id == -1)
	{
		return (*(NANI(&t)));
	}

//	else
//		return (framecheck);

	objecthit(&t, st, end, obj.tris, obj.rd, g);
	if (t.obj.id == -1)
		return (*(NANI(&t)));
//	t.obj = obj;

	return (t);
}

t_dstpst	hit_plane(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_dstpst t;

//	int test = obj.base[1].z || tarasDot(ray, obj.base[1]);
//	printf("obj.base[1].z %f\n", obj.base[1].z);
//	printf("inside HIT_PLANE %d, %d\n", get_global_id(0), 0);
//	printf("dot %f\n", tarasDot(ray, obj.base[1]));

//	return t;
//	if (/*obj.ctr->y == -200  || obj.base[1].x || obj.base[1].y || */obj.base[1].z || tarasDot(ray, obj.base[1]))
/*	if (obj.base[1].z)
		return t;
	else if (tarasDot(ray, obj.base[1]))
		return t;
*/
//	printf("obj base 1 %f\n", obj.base[1].y);
//	printf("denominator %f\n", tarasDot(ray, obj.base[1]));
	t.dst = -tarasDot(diff(st, *obj.ctr), obj.base[1]) / tarasDot(ray, obj.base[1]);
//	return t;
	if (t.dst < 0.0000001f || isinf(t.dst))
		return(*NANI(&t));
	t.obj = obj;
	t.pst = obj.cam_pos;
	return (t);
}

t_dstpst		hit_sphere(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_vector	dx[2];
	t_vector	abc;
	float det;
	t_dstpst t;

	t.pst = 0;
	dx[0] = ray;
	dx[1] = diff(st, *obj.ctr);
	abc.x= tarasDot(dx[0], dx[0]);
	abc.y= 2 * tarasDot(dx[1], dx[0]);
	abc.z= tarasDot(dx[1], dx[1]) - obj.rd2;
	det = abc.y* abc.y- 4 * abc.x* abc.z;
	if (det < 0)
		return (*(NANI(&t)));
	t.dst = (-abc.y- sqrt(det)) /(2 * abc.x);
	//t.pst is called for every pixel, optimize to check only
	//once!
	if (t.dst <= 0.000001f && (t.pst = 1))
		t.dst = (-abc.y+ sqrt(det)) / (2 * abc.x);
	if (t.dst <= 0.000001f)
		return (*NANI(&t));
	t.obj = obj;
	return (t);
}

t_dstpst		hit_cylinder(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_vector d;
	t_vector po[4];
	t_dstpst t;
	t_global p;

	p = *g;
	t.pst = 0;
	po[0] = ray;
	po[3] = diff(st, *obj.ctr);
	d.y = tarasDot(po[0], obj.base[1]);
	d.x = tarasDot(po[3], obj.base[1]);
	po[2].x = tarasDot(po[0], po[0]) - d.y * d.y;
	po[2].y = 2 * (tarasDot(po[0], po[3]) - d.y * d.x);
	po[2].z = tarasDot(po[3], po[3]) - d.x * d.x - obj.rd2;
	d.z = po[2].y * po[2].y - 4 * po[2].x * po[2].z;
	if (d.z < 0)
		return (*NANI(&t));
	t.dst = (-po[2].y - sqrt(d.z)) /(2 * po[2].x);
	if (t.dst < 0.000001f && (t.pst = 1))
		t.dst = (-po[2].y + sqrt(d.z)) /(2 * po[2].x);
	if (t.dst < 0.0000001f)
		return (*(NANI(&t)));
	t.obj = obj;
	return (t);
}

t_dstpst	hit_tri(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_dstpst t;
	t_global p;
	t_dstpst framecheck;

	p = *g;
	t.dst = tarasDot(diff(obj.bd1, st), obj.base[1]) / tarasDot(ray, obj.base[1]);
	if (t.dst < 0.000001f)
	{
		return(*NANI(&t));
	}
	t_vector hit = sum(scale(t.dst, ray), st);

	if (!pinside(sum(scale(t.dst, ray), st), obj.bd1, obj.bd2, obj.bd3, obj.base[1], g))
	{
		return(*NANI(&t));
	}
	t.obj = obj;
	return (t);
}

t_dstpst		hit_cone(t_vector st, t_vector end,  t_vector ray, t_object obj, t_global *g)
{
	t_vector dx[2];
	t_vector dvxvdet;
	t_vector abc;
	t_global p;
	float ret;
	float min;

	p = *g;
	dx[0] = diff(st, *obj.ctr);
	dx[1] = ray;
	dvxvdet.x = tarasDot(dx[1], obj.base[1]);
	dvxvdet.y = tarasDot(dx[0], obj.base[1]);
	abc.x   = tarasDot(dx[1], dx[1]) - (1 + obj.rd2) *dvxvdet.x * dvxvdet.x;
	abc.y = 2 * (tarasDot(dx[1], dx[0]) - (1 + obj.rd2) * dvxvdet.x * dvxvdet.y);
	abc.z = tarasDot(dx[0], dx[0]) - (1 + obj.rd2) * dvxvdet.y * dvxvdet.y;
	dvxvdet.z = abc.y * abc.y - 4 * abc.x * abc.z;
	if (dvxvdet.z < 0)
		return (*NANI(&g->cone[0]));
	g->cone[0].dst = (-abc.y - sqrt(dvxvdet.z)) /(2 * abc.x);
	g->cone[1].dst = (-abc.y + sqrt(dvxvdet.z)) /(2 * abc.x);
	ret = fmin(g->cone[0].dst, g->cone[1].dst);
	if (ret < 0.000001f)
	{
		g->cone[0].dst = fmax(g->cone[1].dst, g->cone[0].dst);
		if (g->cone[0].dst < 0.0000001f)
			return (*NANI(&g->cone[0]));
		g->cone[0].pst = 1;
		g->cone[0].obj = obj;
		return (g->cone[0]);
	}
	else
	{
		g->cone[0].obj = obj;
		g->cone[0].dst = ret;
//		g->con[0].pst = 0;//no need, 0 int the beginning
		return (g->cone[0]);
	}
	return(g->cone[0]);
}

/////////////////////////////////////////////////////////////////////////////////////
//					BRIGHTS.C				   //
/////////////////////////////////////////////////////////////////////////////////////

t_colbri		refl(t_vector refl, t_vector hit, t_object obj, t_global *g)
{
	t_dstpst	temp;
	t_objecthit	reflobj;
	t_colbri	ret;

	objecthit(&temp, hit, sum(refl, hit), g->obj, g->argc + 1, g);
	reflobj.hit = sum(scale(temp.dst, refl), hit);
	reflobj.obj = temp.obj;
	if (reflobj.obj.id == -1)
	{
		init_vector(&ret.col, 0, 0, 0);
		ret.bri = 0;
		return (ret);
	}
	ret = reflobj.obj.bright(hit, reflobj.hit, &reflobj.obj, g);
	ret.col = scale(ret.bri / (float)255, ret.col);
	return (ret);
}

void		do_re(t_vector reflrayv, t_vector hit, 
		t_vector *reocol, t_object obj, t_global *g)
{
	t_colbri reflcolbri;
	t_vector tileocolo;

	tileocolo = *reocol;
//	if (g->recursion[obj.id] < MAX_REC)
	{
		reflcolbri = refl(reflrayv, hit, obj, g);
		*reocol = reflcolbri.col;
		*reocol = sum(scale(1 - obj.re, tileocolo),
			scale(obj.re, reflcolbri.col));
	}
}

//can be done faster
t_vector		reflray(t_vector st, t_vector end, t_vector nrm, t_global *g)
{
	t_vector	ray;
	t_vector	refl;
	t_vector	rayx;

	ray = diff(end, st);
	rayx = diff(ray, scale(tarasDot(ray, nrm), nrm));
	refl = diff(scale(2, rayx), ray);
	return (refl);
}



t_colbri		trans(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_dstpst	temp;
	t_colbri	ret;
	t_objecthit	transobj;
	t_vector	ray;

	ray = diff(hit, st);
	objecthit(&temp, hit, sum(ray, hit), g->obj, g->argc + 1, g);
	transobj.hit = sum(scale(temp.dst, ray), hit);
	transobj.obj = temp.obj;
	if (transobj.obj.id == -1)
	{
		init_vector(&ret.col, 0, 0, 0);
		ret.bri = g->ambient;
		return (ret);
	}
	ret = transobj.obj.bright(hit, transobj.hit, &transobj.obj, g);
	return (ret);
}

void		do_trans(t_vector st, t_vector hit, t_colbri *ret,
	t_object obj, t_global *g)
{
	t_colbri transo;
	int		origbri;

	origbri = ret->bri;
	if (g->recursion[obj.id] > MAX_REC)
		return ;
	transo = trans(st, hit, obj, g);
	transo.col = sum(scale(1 - obj.trans, ret->col),
		scale(obj.trans, transo.col));
	ret->col = transo.col;
	ret->bri = transo.bri * obj.trans + origbri * (1 - obj.trans);
}

void		init_hitli(t_vector *hitli, t_vector hit, t_global *g)
{
	int i;

	i = 0;
	while (i < g->lights)
	{
		hitli[i] = diff(g->li[i], hit);
		i++;
	}
}

void		init_bri(int *bri, t_vector *hitli, t_vector nrm, t_global *g)
{
	int i;

	i = 0;
	*bri = 0;
	while (i < g->lights)
	{
		*bri += fmax(round(255 * tarasDot(norm(hitli[i]), nrm)), g->ambient);
		i++;
	}
	*bri = round(*bri / (float)g->lights);
}
/*
int		inside_cone(t_vector p, t_object obj, t_global *g)
{
	float		axdst;
	float		cirad;
	t_vector	ptoaxproj;
	t_vector	ptoaxperp;
	t_vector	op;
	t_global	*a;

	a = g;
	op = diff(p, *obj.ctr);
	if (tarasDot(op, op) < 0.001)
		return (0);
	axdst = tarasDot(op, obj.base[1]);
	cirad = axdst * obj.rd2;
	ptoaxproj = scale(axdst, obj.base[1]);
	ptoaxperp = diff(op, ptoaxproj);
	return (tarasDot(ptoaxperp, ptoaxperp) - cirad * cirad <= 0);
}

t_colbri	simple_bright_cone(t_vector st, t_vector hit, t_object *obj,
	t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];

	init_hitli(hitli, hit, g);
	if (inside_cone(*g->cam_pos, *obj, g))
	{
		if (!inside_cone(*g->li, *obj, g))
			ret.bri = g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);
	}
	else if (inside_cone(*g->li, *obj, g))
		ret.bri = g->ambient;
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	ret.col = obj->color;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
	return (ret);
}

void		do_tile_cone(
	t_vector hit, t_object *obj, t_global *g)
{
	float		x;
	float		y;
	t_vector	proj;
	t_tile		*objtile;

	objtile = obj->tile;
	proj = diff(obj->nr, scale(tarasDot(obj->base[1], obj->nr), obj->base[1]));
	proj = norm(proj);
	x = objtile[0].w2 * (1 * M_1_PI *
		myacos(proj, obj->base[2], obj->base[1], g));
	y = mymod(1 - tarasDot(obj->base[1], diff(hit, *obj->ctr)), objtile[0].h);
	obj->color = *(objtile[0].vectile
		+ round(y) * objtile[0].w + round(x));
}


t_vector	get_normal_cone(t_vector point, t_object *obj)
{
	t_vector hit0;
	t_vector ret;

	hit0 = diff(point, *obj->ctr);
	ret = norm(diff(hit0, scale(tarasDot(hit0, obj->base[1]) *
		(1 + obj->rd2), obj->base[1])));
	return (ret);
}

t_colbri	bright_cone(t_vector st, t_vector hit, t_object *obj, t_global *g)
{
	t_vector	hit0;
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;

	g->recursion[obj->id]++;
	hit0 = diff(hit, *obj->ctr);
	obj->nr = norm(diff(hit0, scale(tarasDot(hit0, obj->base[1]) *
		(1 + obj->rd2), obj->base[1])));
	init_hitli(hitli, hit, g);
	if (inside_cone(*g->cam_pos, *obj, g))
	{
		obj->nr = scale(-1, obj->nr);
		if (!inside_cone(*g->li, *obj, g))
			ret.bri = g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);
	}
	else if (inside_cone(*g->li, *obj, g))
		ret.bri = g->ambient;
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->re || obj->spec)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->tile[0].data_ptr)
		do_tile_cone(hit, obj, g);
	ret.col = obj->color;
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
	g->recursion[obj->id] = 0;
	return (ret);
}

t_colbri	simple_bright_cylinder(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;

	init_hitli(hitli, hit, g);
	if (obj->cam_pos)
	{
		if (obj->hit(*g->cam_pos, *g->li,
			diff(*g->li, *g->cam_pos), *obj, g).dst < 1)
			ret.bri = g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);	
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	ret.col = obj->color;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
	return (ret);
}

void	do_tile_cyl(t_vector hit, t_vector ctrhit,
	 t_object *obj, t_global *g)
{
	float		x;
	float		y;
	t_vector	proj;
	float		xdst;

	proj = diff(obj->nr, scale(tarasDot(obj->base[1], obj->nr), obj->base[1]));
//	proj = norm(proj);
//for correct straight

//ctrhit used only here
	xdst = tarasDot(obj->base[1], ctrhit);

//for all rotations

	x = obj->tile[0].w2 *(1 - M_1_PI
		 * myacos(proj, obj->base[0], obj->base[1], g));
	y = myintmod(xdst, obj->tile[0].h);
	if (y == 0)
		y = 1;
	obj->color = *(obj->tile[0].vectile +
		round(y) * obj->tile[0].w + round(x));
}

t_vector	get_normal_cyl(t_vector point, t_object *obj)
{
	t_vector ctrhit;
	t_vector ret;

	ctrhit = diff(point, *obj->ctr);
	ret = scale(tarasDot(ctrhit, obj->base[1]), obj->base[1]);
	ret = norm(diff(ctrhit, ret));	
	return ret;
}

t_colbri	bright_cylinder(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_vector	ctrhit;
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;

	g->recursion[obj->id]++;
	ctrhit = diff(hit, *obj->ctr);
	obj->nr = scale(tarasDot(ctrhit, obj->base[1]), obj->base[1]);
	obj->nr = norm(diff(ctrhit, obj->nr));
	init_hitli(hitli, hit, g);
	if (obj->cam_pos)
	{
		obj->nr = scale(-1, obj->nr);
		if (obj->hit(*g->cam_pos, *g->li,
			diff(*g->li, *g->cam_pos), *obj, g).dst < 1)
			ret.bri = g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->tile[0].data_ptr)
		do_tile_cyl(hit, ctrhit, obj, g);
	ret.col = obj->color;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
	g->recursion[obj->id] = 0;
	return (ret);
}
*/
void		do_1_spec(t_colbri *tmp, t_colbri *ret, t_vector *hitli,
	t_vector reflrayv, t_object obj, int i, t_global *g)
{
	g->cosa[i] = tarasDot(norm(hitli[i]), norm(reflrayv));
	if (g->cosa[i] > 0)
	{
		g->cosa[i] = tothe2(g->cosa[i], obj.spec);
//				dirty trick, see central for explenation of do_1_spec
		tmp->col = sum(tmp->col, sum(scale(255 * g->cosa[i] / ret->bri, g->white),
					scale((1 -  g->cosa[i]), ret->col)));
	}
	else
//		do same thing as if cosa == 0
		tmp->col = sum(tmp->col, ret->col);

}

void		do_spec(t_colbri *ret, t_vector hit, t_vector nrm,
	t_vector reflrayv, t_object obj, t_global *g)
{
	float		cosa;
	float		cosa3;
	int			i;
	t_colbri	tmp;
	t_vector	hitli[1/*g->lights*/];

	i = -1;
	while (++i < g->lights)
		hitli[i] = diff(g->li[i], hit);
	init_vector(&tmp.col, 0, 0, 0);
	i = -1;
	while (++i < g->lights)
		do_1_spec(&tmp, ret, hitli, reflrayv, obj, i, g);
	tmp.col = scale(1 / (float)g->lights, tmp.col);
	ret->col = tmp.col;
}
/*
t_colbri	simple_bright_sphere(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri		ret;
	t_vector		reflrayv;
	t_vector		hitli[g->lights];
	t_vector		ctrli;
	init_hitli(hitli, hit, g);
	if (obj->cam_pos)
	{
		ctrli = diff(*g->li, *obj->ctr);
		if ((tarasDot(ctrli, ctrli) > obj->rd2) && (ret.bri = g->ambient))
			ret.col = obj->color;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);	
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	ret.col = obj->color;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
	return (ret);
}

void		do_tile_sphere(t_vector hit, t_object *obj, t_global *g)
{
	t_vector	ctrhit;
	t_vector	proj;
	float		x;
	float		y;
	t_tile		*tile;

	tile = obj->tile;
	ctrhit = diff(hit, *obj->ctr);
//	ctrhit = obj->nr; /real_nr!

	proj = diff(ctrhit, scale(tarasDot(obj->base[1], ctrhit), obj->base[1]));
	proj = norm(proj);
	y = tile[0].h * M_1_PI * acos(tarasDot(obj->nr, obj->base[1]));
	x = tile[0].w2 * M_1_PI * myacos(proj, obj->base[2], obj->base[1], g);
	if (round(x) >= tile[0].w2)
		x--;
	obj->color = *(tile[0].vectile
		+ round(y) * tile[0].w + round(x));
}

void	    do_normal_map_sphere(t_vector hit, t_object *obj, t_global *g)
{
	t_vector	ctrhit;
	t_vector	proj;
	t_vector angle;
	float	  x;
	float	  y;
	t_tile	  normalmap;
	normalmap = obj->normal_map;
//	ctrhit = diff(hit, *obj->ctr);
	ctrhit = obj->nr;
	proj = diff(ctrhit, scale(tarasDot(obj->base[1], ctrhit), obj->base[1]));
	proj = norm(proj);

//	angle between y axis and the normal
	angle.x = acos(tarasDot(obj->nr, obj->base[1]));
//	angle.y = 0;
//	angle.z = 0;
//	angle between projection of the normal on the x z axis
//	and z axis counting counter clockwise when looking from the top
		
	angle.y = -myacos(proj, obj->base[2], obj->base[1], g);
	angle.z = 0;


	y = normalmap.h * M_1_PI * angle.x;
	x = normalmap.w2 * M_1_PI * angle.y;
	if (round(x) >= normalmap.w2)
		x--;
	obj->nr = *(normalmap.vectile
		+ round(y) * normalmap.w + round(x));


//	obj->nr = tarasRotate(obj->nr, angle);
//	obj->nr.x = -obj->nr.x;
//	*retorig = *(obj->normal_map.vectile +
//	round(y) * obj->normal_map.w + round(x));




//	printf("normal is %f,%f,%f\n", obj->nr.x, obj->nr.y, obj->nr.z);
}
*/
t_vector	get_normal_sphere(t_vector hit, __global t_object *obj)
{
	return (scale(obj->rd_1, diff(hit, *obj->ctr)));
}

t_colbri	bright_sphere(t_vector st, t_vector hit, t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[/*g->lights*/1];

//	g->recursion[obj->id]++;
	init_hitli(hitli, hit, g);
	obj->nr = obj->real_nr = scale(obj->rd_1, diff(hit, *obj->ctr));

//	normal must be inited before lighting calculation
//	if (obj->normal_map.data_ptr)
//		do_normal_map_sphere(hit, obj, g);

//	if (con(g))
//		printf("cam: %f, %f, %f, li: %f, %f, %f angle: %f,%f,%f\n",g->cam_pos->x, g->cam_pos->y, g->cam_pos->z, g->li->x, g->li->y, g->li->z, g->angle->x, g->angle->y, g->angle->z);
	if (obj->cam_pos)
	{
		obj->nr = scale(-1, obj->nr);
		if (len2(diff(*g->li, *obj->ctr)) > obj->rd2)
			ret.bri = g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);	
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
/*	if (obj->tile[0].data_ptr)
		do_tile_sphere(hit, obj, g);
*/	ret.col = obj->color;
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
//	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
//	g->recursion[obj->id] = 0;
	return (ret);
}
/*
t_colbri		simple_bright_plane(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];

	init_hitli(hitli, hit, g);
	init_bri(&ret.bri, hitli, obj->nr, g);
	ret.col = obj->color;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);
	obstructed(&ret, hit, hitli, reflrayv, *obj, g);
	return (ret);
}

void			do_normal_map_plane(t_vector *retorig, t_vector hit,
	t_object *obj, t_global *g)
{
	t_vector	ctrhit;
	int			x;
	int			y;

	ctrhit = diff(hit, *obj->ctr);
	x = mymod(ctrhit.x, obj->normal_map.w);
	y = mymod(ctrhit.z, obj->normal_map.h);
	*retorig = *(obj->normal_map.vectile +
	round(y) * obj->normal_map.w + round(x));

}



void			do_tile_plane(t_colbri *retorig, t_vector hit,
	t_object *obj, t_global *g)
{
	t_vector	ctrhit;
	int			x;
	int			y;

//	printf("doing tile plane\n");
	ctrhit = diff(hit, *obj->ctr);
//	printf("hit is %f,%f,%f\n", hit.x, hit.y, hit.z);
	x = mymod(ctrhit.x, obj->tile[0].w);
	y = mymod(ctrhit.z, obj->tile[0].h);
//	printf("x,y is %d,%d\n%f,%f\n", x, y, ctrhit.x, ctrhit.z);

	retorig->col = *(obj->tile[0].vectile +
	round(y) * obj->tile[0].w + round(x));

//	obj->color = *(tile[0].vectile
//		+ round(y) * tile[0].w + round(x));

//	printf("tile plane done\n");
	obj->color = retorig->col;
}
*/
t_vector	get_normal_plane(t_vector point, __global t_object *obj)
{
	return (obj->base[1]);
}

t_colbri		bright_plane(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[/*g->lights*/1];

//	g->recursion[obj->id]++;
	init_hitli(hitli, hit, g);


//	if (obj->normal_map.data_ptr)
//		do_normal_map_plane(&obj->nr, hit, obj, g);
//	else
		obj->nr = obj->base[1];

//	changed campos to invert obj base //message не актуально
	if (obj->cam_pos)
	{
//		obj->base[1] = scale(-1, obj->base[1]);
		obj->nr = scale(-1, obj->nr);
	}
	init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
//	if (obj->tile[0].data_ptr)
//		do_tile_plane(&ret, hit, obj, g);
/*	
	else if ((int)(round(fabs(hit.x) / (float)80) % 2)
		== (int)(round(fabs(hit.z) / (float)80) % 2))
		init_vector(&obj->color, 0,0.5f, 0.5f);
*/
//		init_vector(&obj->color, 1,1, 1);

	ret.col = obj->color;
	if (obj->re)
		do_re(reflrayv, hit, &ret.col, *obj, g);
	if (obj->trans)
		do_trans(st, hit, &ret, *obj, g);	
//	obstructed(&ret, hit, hitli, reflrayv, *obj, g);

//	g->recursion[obj->id] = 0;
	return (ret);
}



void	debug(t_global* g)
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
				&& g->data_ptr[(j + 1) * HEIGHT + i + 1] == 0
				&& g->data_ptr[(j - 1) * HEIGHT + i - 1] == 0
				&& g->data_ptr[(j + 1) * HEIGHT + i - 1] == 0
				&& g->data_ptr[(j - 1) * HEIGHT + i + 1] == 0)
				g->data_ptr[j * HEIGHT + i] = 0;
			i++;
		}
		j++;
	}
}

void	save_im(int* a, int* c, int w, int h)
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

	ret = fmod((float)x, (float)m);
	if (x >= 0)
		return (ret);
	return (ret + m);
}


float	mymod(float x, int m)
{
	float ret;

	ret = fmod((float)x, (float)m);
	if (x >= 0)
		return (ret);
	return (ret + m);
}

int		mid_col(int* a, int w, int h, int x, int y)
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
	vret.x = round(vret.x);
	vret.y = round(vret.y);
	vret.z = round(vret.z);
	//	ret = ret / s;
	return (/*ret*/brg(vret));
}

void	rewrite_pix(int* a, int* o, int x, int y, int w, int h, int xmax, int ymax, t_global* g)
{
	t_vector mid_col;
	int			ran;
	int			ywx;

	ywx = y * w + x;
	ran = 1;
	mid_col = rgb(*(o + ywx));
	g->ray->x = x - h / 2;
	g->ray->y = -y + w / 2;

	if (x >= xmax + 1 || y >= xmax + 1)
		return;
	//	if (x > 0)
	{
		mid_col = sum(rgb(*(o + y * w + myintmod(x - 1, xmax))), mid_col);
		ran++;
	}
	//	if (x < w - 1)
	{
		mid_col = sum(rgb(*(o + y * w + myintmod(x + 1, xmax))), mid_col);
		ran++;



	}
	//	if (y > 0)
	{
		mid_col = sum(rgb(*(o + myintmod(y - 1, ymax) * w + x)), mid_col);
		ran++;



	}
	//	if (y < h - 1)
	{
		mid_col = sum(rgb(*(o + myintmod(y + 1, ymax) * w + x)), mid_col);
		ran++;



	}
	//	if (y < h - 1 && (x < w - 1))
	{
		mid_col = sum(rgb(*(o + myintmod(y + 1, ymax) * w + myintmod(x + 1, xmax))), mid_col);
		ran++;


	}
	//	if (y < h - 1 && (x > 0))
	{
		mid_col = sum(rgb(*(o + myintmod(y + 1, ymax) * w + myintmod(x - 1, xmax))), mid_col);

		ran++;



	}
	//	if (y > 0 && (x < w + 1))
	{
		mid_col = sum(rgb(*(o + myintmod(y - 1, ymax) * w + myintmod(x + 1, xmax))), mid_col);

		ran++;



	}
	if (y > 0 && x > 0)
	{
		//		mid_col = sum(rgb(*(o + ywx - w - 1)), mid_col);
		mid_col = sum(rgb(*(o + myintmod(y - 1, ymax) * w + myintmod(x - 1, xmax))), mid_col);

		ran++;



	}
	mid_col = scale(1 / (float)ran, mid_col);
	mid_col.x = round(mid_col.x);
	mid_col.y = round(mid_col.y);
	mid_col.z = round(mid_col.z);

	*(a + ywx) = brg(mid_col);
}


void	smooth(int* a, int w, int h, int xmax, int ymax, t_global* g)
{
	int i;
	int j;
	//int* orig;
	int orig[WIDTH * HEIGHT + 1];

	i = 0;
	j = 0;
	//orig = (int*)malloc(sizeof(int) * w * h + 1);
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

void		alias(int* dst, int* a, int w, int xmax, int ymax, int h)
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
			*(dst + j * (w)+i) = mid_col(a, w, h, 2 * i, 2 * j);
			i++;
		}
		j++;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																CENTRAL.C								   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void	obstructed(t_colbri *cur, t_vector hit, t_vector *hitli, t_vector reflrayv, t_object obj, t_global *g)
{
	//gamma correct
//	cur->bri = 255.0 * pow(cur->bri/255.0, 0.66);


	int i = 0;
//	int	objn;
	t_vector nrm;
	int	iobjn[2];
	float cosa[/*g->lights*/1];
	t_dstpst	t;
	t_vector ray;
	t_colbri tmp;
	int	obsc = 0; // how many ones there are in obss. from how many lights it is shielded
	int obss[/*g->lights*/1]; // used in do 1 spec. obss[i] == 1 if that obect is obstructed from light[i]
	int	specscal;
	float soft[/*g->lights*/1];
//	int	darken[g->lights];
	t_vector obstructed;
	/*bzero(obss, sizeof(int) * g->lights);
	bzero(soft, sizeof(float) * g->lights);
	bzero(cosa, sizeof(float) * g->lights);
*/
	obss[0]=0;
	soft[0]=0;
	cosa[0]=0;

	init_vector(&tmp.col, 0, 0, 0);
	cosa[0] = 0;
	obj.nr = nrm;
	while(i < g->lights)
	{
		ray = hitli[i];
		iobjn[0] = 0;
		iobjn[1] = g->prim;
		while (++iobjn[0] < g->argc + 1)
		{
			if (iobjn[1] == 0)
				iobjn[1] = (iobjn[1] + 1) % (g->argc + 1);
			if (obj.id != g->obj[iobjn[1]].id)
			{
				if (g->obj[iobjn[1]].id == 1)
					t = hit_plane(hit, g->li[i], ray, g->obj[iobjn[1]], g);
				else
					t = hit_sphere(hit, g->li[i], ray, g->obj[iobjn[1]], g);
				if (t.dst /*/ sqrt(tarasDot(ray, ray))*/ < 0.000001f)
				{
					i++;
					break;
				}
				if (t.dst < 1)
				{
					if (obj.soft)
					{
						obstructed = sum(scale(t.dst, ray), hit);
//						t_vector ctrhit = diff(obstructed,  *g->obj[iobjn[1]].ctr); 

//						segfailt here if object is complex. object must be a triangle
						if (g->obj[iobjn[1]].id == 1)
							soft[i] = fmax((float)soft[i], (float)fmax((float)0, (float)tarasDot(norm(get_normal_plane(obstructed, &g->obj[iobjn[1]])), norm(ray))));
						else
							soft[i] = fmax((float)soft[i], (float)fmax((float)0, (float)tarasDot(norm(get_normal_sphere(obstructed, &g->obj[iobjn[1]])), norm(ray))));

//						soft[i] = fmax((float)0, (float)-tarasDot(norm(g->obj[iobjn[1]].get_normal(obstructed, &g->obj[iobjn[1]])), norm(ray)));

//						soft[i] = tarasDot(norm(g->obj[iobjn[1]].get_normal(obstructed, &g->obj[iobjn[1]])), norm(ray));
//						soft[i] = tothe2(soft[i], obj.soft);
//						soft[i] = sqrt(soft[i]);
//						soft[i] = pow(soft[i], 1.5);

//						float soft = normal_to_the_obhect * hitli, so between 0 and 1
					}
					g->prim = iobjn[1];
					obsc++;
					obss[i] = 1;
					if (!obj.soft)// if soft shadwos need to look on all obstructions
						break;
				}
			}
			iobjn[1] = (iobjn[1] + 1) % (g->argc + 1);
		}
		if (obj.soft)
			soft[i] = tothe2(soft[i], obj.soft);
		i++;
	}

	i = -1;
	if (obj.spec)
	{
		while (++i < g->lights)
//			if (obss[i] == 0)
			{
//				do_1_spec(&tmp, cur, hitli, reflrayv, obj, i, g);
			cosa[i] = tarasDot(norm(hitli[i]), norm(reflrayv));

//						soft ^ n for more difussion
			cosa[i] = fmax((float)0, (float)(cosa[i] - soft[i] * soft[i]));

		if (cosa[i] > 0)
		{
/*			float cosai2 = cosa[i] * cosa[i];
			float cosai4 = cosai2 * cosai2;
*/			float m = 0.2f;
			float a = acos(cosa[i]);

//			cosa[i] = exp(-a * a/ (m * m));
//			cosa[i] =  1/(M_PI_F * m * m * cosai4) * exp(-1/(m * m) * (1/cosai2 - 1));
			cosa[i] = tothe2(cosa[i], obj.spec);

				//dirty trick to make it look like
//				the specular white light is mixed
//				with the color after the color is mixed
//				with brightness. here it is divided by bri
//				so that it cancels out when bri * col
//				in recalc
//				doesn't work when multipple hard shadows
//			tmp.col = sum(tmp.col, sum(scale(255 * cosa[i] / (cur->bri / g->lights), g->white),
			tmp.col = sum(tmp.col, sum(scale(255 * cosa[i] / (cur->bri), g->white),
				scale((1 - cosa[i]), cur->col)));
		}
		else
//			do same thing as if cosa == 0
       		         tmp.col = sum(tmp.col, cur->col);
		}
		if (obsc < g->lights || obj.soft)
		{
			if (!obj.soft)
				specscal = g->lights - obsc;
			else
				specscal = g->lights;
			tmp.col = scale(1 / (float)specscal, tmp.col);
			cur->col = tmp.col;
		}
	}
	if (obsc > 0) //if it is obscured from at least 1 of the lights
	{
		//bug: when plane takes soft
		//shadows from sphere and the
		//light is inside sphere
		//the plane isn't obstructed fully from
		//light by sphere
		if (obj.soft) // DRAWS SOFT SHADOWS
		{
			int briscale;
			briscale = (cur->bri - g->ambient) /(g->lights );
			i = -1;
			while (++i < g->lights)
			{
				cur->bri = cur->bri - briscale * (soft[i] );
//				when soft == 1, bri is the darkest
			}
		}//		DRAWS REGUALR SHADOWS
		else
			cur->bri = g->ambient + ((g->lights - obsc) * (cur->bri - g->ambient) / (float)g->lights);
	}
}

void	objecthit(t_dstpst *ret, t_vector st, t_vector end, __global t_object *obj, int objc, t_global *g)
{
	int i;
	int legal_hit;
	t_dstpst t_crt;
	float closest_tmp;
	t_vector ray;

	i = 0;
	legal_hit = 0;
	ray = diff(end, st);
	while (++i < objc)
	{
		if (obj[i].id == 1)
			t_crt = hit_plane(st, end, ray, obj[i], g);
		else
			t_crt = hit_sphere(st, end, ray, obj[i], g);
		if ((t_crt.dst >= 0.0001f) && (!legal_hit || t_crt.dst < closest_tmp))
		{
			legal_hit = 1;
			closest_tmp = t_crt.dst;
			*ret = t_crt;
			ret->obj.cam_pos = t_crt.pst;
 		}
	}
	if (!legal_hit)
//		ret->obj.name = NULL;
		ret->obj.id = -1;
}


__kernel void recalc(
		const unsigned int	count,
		__global unsigned int		*data_ptr,
		__global t_object	*obj,
		__global t_vector	*li,
		__global t_vector	*cam_pos,
		__global t_vector	*angle,
		__global t_vector	*base,
		__global t_vector	*ctr
)
{
	int i = get_global_id(0);

	if(i < count)
	{
/*		if (obj[2].id != 2)
		{
			data_ptr[i] = i;
			return ;   
		}
*/

//		t_object lobj[3];
//		t_vector li_cam_angle_base_ctr[4];
//		t_vector objctr[2];

		int x = i % WIDTH;
		int y = i / WIDTH;
		t_global g;

//		g.li = &li_cam_angle_base_ctr[0];
//		g.cam_pos = &li_cam_angle_base_ctr[1];
//		g.angle = &li_cam_angle_base_ctr[2];

//		g.base[0] = &li_cam_angle_base_ctr[3];
//		g.base[1] = &li_cam_angle_base_ctr[4];
//		g.base[2] = &li_cam_angle_base_ctr[5];
//		g.ctr[3] = &li_cam_angle_base_ctr[3];
//		g.obj = obj;


//		data_ptr[i] = i;
//		return ;   

//		obj[1].ctr = &objctr[1];
//		obj[2].ctr = &objctr[2];

/*		if (obj[2].id != 2)
		{
			data_ptr[i] = i * i;
			return ;   
		}

*/


//		data_ptr[i] = i;
//		return ;   



		obj[1].ctr = ctr + 1;
		obj[2].ctr = ctr + 2;

//		data_ptr[i] = i;
//		return ;   

//		g.obj = lobj;


		g.obj = obj;
/*		g.obj[0] = obj[0];
		g.obj[1] = obj[1];
		g.obj[2] = obj[2];
*/
//		data_ptr[i] = i;
//		return ;   

/*		*g.cam_pos = *cam_pos;
		*g.li = *li;
		*g.angle = *angle;
*/
		g.cam_pos = cam_pos;
		g.li = li;
		g.angle = angle;

		g.argc = 2;
		g.lights = 1;

//		data_ptr[i] = i;
//		return ;   


		init_vector(&g.base[0], 1, 0, 0);
		init_vector(&g.base[1], 0, 1, 0);
		init_vector(&g.base[2], 0, 0, 1);
		g.prim = 0;
		g.ambient = 65;
//		g.data_ptr = data_ptr;

		t_vector ray;
		t_dstpst ret;
		t_colbri bright;
//		g.obj[1] = *(obj + 1);
		init_vector(&ray, x - WIDTH_2, HEIGHT_2 - y, WIDTH / (float)2000 * 1600);
		ray = tarasRotate(ray, *g.angle);

//		*g.obj[1].ctr = ctr[1];
//		*g.obj[2].ctr = ctr[2];

/*		if (g.obj[1].ctr->y == -200.0f)
		{
			data_ptr[i] = i * i * i;
			return ;   
		}
		else
			data_ptr[i] = 0xFF0000;
		return ;
*/


		
//		printf("calling objecthit %d\n", i);
/*		printf("center 1 is %f,%f,%f\n", ctr[1].x, ctr[1].y, ctr[1].z);
		printf("obj center 1 is %f,%f,%f\n", g.obj[1].ctr->x, g.obj[1].ctr->y, g.obj[1].ctr->z);
*/

//		printf("id is %d\n", get_global_id(0));
/*		if (g.obj[1].ctr->y == -200.0f)
		{
			data_ptr[i] = i;
			return ;   
		}
*/
//		else
//			data_ptr[i] = 0xFF0000;	
//		return ;	
//		printf("id is %d\n", get_global_id(0));
//		return ;


		objecthit(&ret, *g.cam_pos, sum(ray, *g.cam_pos), g.obj, g.argc + 1, &g);
		printf("%d", ret.obj.id);
		if (ret.obj.id == 1)
			data_ptr[i] = 0x00FF00;
		else
			data_ptr[i] = 0x0000FF;
		return ;   



		if (ret.obj.id != -1)
			{
//				printf("gettin bright\n");
				if (ret.obj.id == 1)
					bright = bright_plane(*g.cam_pos, sum(scale(ret.dst, ray), *g.cam_pos), &ret.obj, &g);
				else
					bright = bright_sphere(*g.cam_pos, sum(scale(ret.dst, ray), *g.cam_pos), &ret.obj, &g);
	
				data_ptr[i] = color(bright.bri, bright.col);
			}
			else
				data_ptr[i] = 0xFF0000;
	}
}

