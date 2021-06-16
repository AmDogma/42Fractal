#include "fractol.h"
	
void mondelbrot(double moveX, double moveY, t_mlx *data)
{
  //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
  double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
  int maxIterations = 300; //after how much iterations the function should stop

  //pick some values for the constant c, this determines the shape of the Julia Set
  cRe = -0.7;
  cIm = 0.27015;

  //loop through every pixel
  for(int y = 0; y < 600; y++)
  for(int x = 0; x < 800; x++)
  {
    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    newRe = 1.5 * (x - 800 / 2) / (0.5 * data->zoom * 800) + (moveX/data->zoom);
    newIm = (y - 600 / 2) / (0.5 * data->zoom * 800) + (moveY/data->zoom);
    //i will represent the number of iterations
    int i;
    //start the iteration process
    for(i = 0; i < maxIterations; i++)
    {
      //remember value of previous iteration
      oldRe = newRe;
      oldIm = newIm;
      //the actual iteration, the real and imaginary part are calculated
      newRe = oldRe * oldRe - oldIm * oldIm + cRe;
      newIm = 2 * oldRe * oldIm + cIm;
      //if the point is outside the circle with radius 2: stop
      if((newRe * newRe + newIm * newIm) > 2) break;
    }
    //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
   // color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
    //draw the pixel
    mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFFFFFFFF + ((i%28 * 8) * (255 * (i < maxIterations)))); 
  }
  //make the Julia Set visible and wait to exit
}

int	mouse_key(int event, int x, int y, t_mlx *data)
{
	printf("Mou = %d, x = %d, y = %d", event, x, y);
	if (event == 5)
		data->zoom += 1;
	if (event == 4 && data->zoom > 0.0001)
		data->zoom -= 1;
	if (x < 400)
	mlx_clear_window(data->mlx, data->mlx_win);
	mondelbrot(0, 0, data);	
	return (0);
}

int key_key(int event, t_mlx *data)
{
	printf("KEY = %d", event);
	if (event == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win); // почему сегается?
		exit(0);
	}
	if (event == 126)
		data->move_g += 0.2;
	if (event == 125) 
		data->move_g -= 0.2;
	if (event == 124)
		data->move_h -= 0.2;
	if (event == 123)
		data->move_h += 0.2;
	mlx_clear_window(data->mlx, data->mlx_win);
	mondelbrot(data->move_h, data->move_g, data);	
	return (0);
}	

int	main(void)
{
	t_mlx	data;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 800, 600, "Fractol");
	data.zoom = 1.0001;
	data.move_g = 0;
	data.move_h = 0;
	mondelbrot(0, 0, &data);
	mlx_key_hook(data.mlx_win, key_key, &data);
	mlx_mouse_hook(data.mlx_win, mouse_key, &data);
	mlx_loop(data.mlx);
}

// gcc  -lmlx -framework OpenGL -framework AppKit main.c && ./a.out 
//-Imlx 