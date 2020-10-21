# gterm
Minimal terminal graphics library written in C.

![Mandelbrot set](media/mandelbrot.png)

## How to use

All you need to do to use gterm in your project is add the `gterm.c` file to your project and 
include the `gterm.h` file.

Basic usage example:

```C
/*
* Initialize gterm screen struct 
* with width, height and square pixels(false if you want standard rectangular characters)
*/
gt_screen *screen = gt_init_screen(80, 50, true);

/* Set background color of the screen */
gt_set_background(screen, gt_get_color(153, 255, 0));

/* Set a specific pixel */
gt_set_pixel(screen, j, i , gt_get_color(255, 0, 0));

/* Render screen. Nothing is display before this */
gt_refresh(screen);

/* Free the screen structure */
gt_free_screen(screen);
```

For full functionality check the `gterm.h` file.

## Code examples

In the examples directory you can find code samples that use gterm.
Just go inside the directory and run make.