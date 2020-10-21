#include <complex>
#include <cstdint>
// You must include the gterm header
#include "gterm.h"

using namespace std;

constexpr int32_t WIDTH = 100;
constexpr int32_t HEIGHT = 75;

constexpr double XMIN = -1.5;
constexpr double XMAX = 0.75;

constexpr double YMIN = -1;
constexpr double YMAX = 1;

uint8_t mandelbrot(double x, double y){
    complex<double> c0(x, y);
    complex<double> c = 0;

    for(int32_t i = 1; i < 1000; i++){
        if(abs(c) > 2){
            // Convert from RGB to the 8bit gterm color
            return gt_get_color(255, 0, 0);
        }
        c = c * c + c0;
    }

    return gt_get_color(0, 0, 0);
}

int main(){

    // Initialize the screen with width, height and square pixels
    gt_screen *screen = gt_init_screen(WIDTH, HEIGHT, true);

    for(int32_t x = 0; x < WIDTH; x++){
        for(int32_t y = 0; y < HEIGHT; y++){
            // Set a pixel to a given color
            gt_set_pixel(screen, x, y, mandelbrot( XMIN + x/(WIDTH - 1.0) * (XMAX - XMIN), YMIN + y/(HEIGHT - 1.0) * (YMAX - YMIN) ));
        }
    }
    
    // Render the actual image
    gt_refresh(screen);

    // Free the gterm screen structure
    gt_free_screen(screen);
    
    return 0;
}