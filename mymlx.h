
#include <glad/glad.h>
//GLAD should be included before GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#ifndef MYMLX_H
# define MYMLX_H

#define A_KEY 65
#define S_KEY 83
#define D_KEY 68
#define F_KEY 70
#define W_KEY 87
#define SPACE_KEY 32
#define ESC_KEY 5
#define J_KEY 74
#define K_KEY 75
#define L_KEY 76
#define I_KEY 73
#define O_KEY 79
#define BRA_KEY 43
#define KET_KEY 47
#define UP_KEY 265
#define DOWN_KEY 264
#define LEFT_KEY 263
#define RIGHT_KEY 262
#define H_KEY 72
#define G_KEY 71
#define R_KEY 82
#define T_KEY 84



typedef struct  s_mlx
{
        int width;
        int height;

        GLFWwindow *window;
	int ID;
}               mlx;

typedef struct	s_fun_and_arg
{
	int (*f[10])();
	void *param;
}		t_fun_and_arg;

unsigned int    compileShader(const unsigned int type, const char* source);
int     compileProgram(const char *vertexShaderSource, const char *fragmentShaderSorce);

void    *mlx_init();
void    *mlx_new_window(void *mlx_ptr, int width, int height, const char *name);
void    *mlx_new_image(void *mlx_ptr, int width, int height);
void    *mlx_get_data_addr(void *img_ptr, int *bpp, int *sz_l, int *e);
void    mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, int *img_ptr, int ignore1, int ignore2);
void    mlx_loop(void *mlx_ptr);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double x, double y);
void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif



