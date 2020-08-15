# mymlx
Simulating MiniLibX library using OpenGL to port it to systems other than MacOS.

The MiniLibX library creates windows, manages events and draws pixels. This is a 'simulation' of the features of mlx written using OpenGL to port it to other systems.
Currently it is not a complete simulation. Here is the list of it's main weaknesses:

1. Only mouse_move and key_press events are supported.
2. GLFW and MacOS graphics api don't share keycodes for the same keys, so if you want to press ESC, press the '5' key.
3. Do not mlx_new_image() before mlx_new_window(). Mlx allows this, but this library does not.
4. mlx_xpm_file_to_image() doesn't work, so no tiles.
5. It is much slower than MLX.

How to use:
1. You need only mymlx.c and mymlx.h files from this repository.
2. Download GLFW implementation of OpenGL and GLAD loader.
3. Change #include <mlx.h> to #include "mymlx.h"
4. Move call to mlx_new_window() to a place before mlx_new_image() in your mlx application
5. Compile with glad.c, mymlx.c, and link dynamic libs. In my case -l glfw.3.3 -l GLEW.2.1.0
6. You might need to delete all mentions of mlx functions not supported, like xpm file loading and events.
7. Keep in mind that all keycodes are shuffled now.
