/**
 * @file gterm.c
 * @author paunstefan
 * @brief Gterm library file.
 * @version 0.1
 * @date 2020-10-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "gterm.h"
#include <string.h>

/**
 * @brief Allocates memory for gterm screen structure.
 * 
 * @param w Width of the screen
 * @param h Height of the screen
 * @param square True for square pixels, false for standard terminal characters.
 * @return gt_screen*
 */
gt_screen* gt_init_screen(uint32_t w, uint32_t h, bool square){
    gt_screen *screen = (gt_screen*)malloc(sizeof(gt_screen));

    if(NULL == screen){
        return NULL;
    }

    screen->screen_buffer = (gt_pixel*)malloc(sizeof(gt_pixel) * (w * h));

    if(NULL == screen->screen_buffer){
        free(screen);
        return NULL;
    }

    screen->width = w;
    screen->height = h;
    screen->square_px = square;

    /* Init buffer */
    gt_clear_screen(screen);

    return screen;
}

/**
 * @brief Free the gterm screen structure
 * 
 * @param screen The st_screen structure to free.
 */
void gt_free_screen(gt_screen *screen){
    if(screen != NULL){
        free(screen->screen_buffer);
        free(screen);
    }
    screen = NULL;

    printf("\x1B[0m");
}

/**
 * @brief Refresh the image shown.
 * 
 * @param screen Pointer to gt_screen.
 */
void gt_refresh(gt_screen *screen){
    if(screen != NULL){
        RESET_SCREEN();
        for(uint32_t i = 0; i < screen->height; i++){
            for(uint32_t j = 0; j < screen->width; j++){
                printf("\x1B[48;5;%um\x1B[38;5;%um%c", 
                    screen->screen_buffer[i * screen->width + j].data.bg_color,
                    screen->screen_buffer[i * screen->width + j].data.fg_color, 
                    screen->screen_buffer[i * screen->width + j].data.character);

                if(screen->square_px){
                    printf(" ");
                }
            }
            printf("\x1B[48;5;0m\n");
        }
    }
}

/**
 * @brief Sets the screen to black.
 * 
 * @param screen Pointer to gt_screen.
 */
void gt_clear_screen(gt_screen *screen){
    if(screen != NULL){
        for(size_t i = 0; i < screen->height * screen->width; i++){
            /* Set it to black background, white foreground */
            screen->screen_buffer[i].data.bg_color = GT_BLACK;
            screen->screen_buffer[i].data.fg_color = GT_WHITE;
            screen->screen_buffer[i].data.character = ' ';
        }
    }
}

/**
 * @brief Set the background color and remove everything currently on the screen.
 * 
 * @param screen Pointer to gt_screen.
 * @param bgcolor Background color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_set_background(gt_screen *screen, uint8_t bgcolor){
    if(screen != NULL){
        for(size_t i = 0; i < screen->height * screen->width; i++){
            screen->screen_buffer[i].data.bg_color = bgcolor;
        }
    }
}

/**
 * @brief Set a pixel to a certain color.
 * 
 * @param screen Pointer to gt_screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param col Color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_set_pixel(gt_screen *screen, uint32_t x, uint32_t y, uint8_t col){
    if(screen != NULL){
        screen->screen_buffer[y * screen->width + x].data.bg_color = col;
    }
}

/**
 * @brief Get the current background color of pixel.
 * 
 * @param screen Pointer to gt_screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @return uint8_t 
 */
uint8_t gt_get_bgcolor(gt_screen *screen, uint32_t x, uint32_t y){
    if(screen != NULL){
        return screen->screen_buffer[y * screen->width + x].data.bg_color;
    }
    return 0;
}

/**
 * @brief Prints text as the foreground characters o a position on the screen.
 *        Not recommended to use for square pixel screens.
 * 
 * @param screen Pointer to gt_screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param text Text you want.
 * @param color Color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_print_text(gt_screen *screen, uint32_t x, uint32_t y, char *text, uint8_t color){
    size_t tlen = strlen(text);
    if(screen != NULL){
        if((screen->width * screen->height) > (y * screen->width + x) + tlen){
            for(uint32_t i = 0; i < tlen; i++){
                screen->screen_buffer[y * screen->width + x + i].data.character = text[i];
                screen->screen_buffer[y * screen->width + x + i].data.fg_color = color;
            }
        }
    }
}

/**
 * @brief Draw rectangle
 * 
 * @param screen Pointer to gt_screen.
 * @param x Upper left corner X coordinate
 * @param y Upper left corner Y coordinate
 * @param w Width in pixels
 * @param h Height in pixels
 * @param col Color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_draw_rect(gt_screen *screen, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t col){
    if(screen != NULL){
        if(screen->width >= (x + w) && screen->height >= (y + h)){
            for(uint32_t i = 0; i < h; i++){
                for(uint32_t j = 0; j < w; j++){
                    screen->screen_buffer[(y + i) * screen->width + (x + j)].data.bg_color = col;
                }
            }
        }
    }
}

/**
 * @brief Draw line
 * 
 * @param screen Pointer to gt_screen.
 * @param x1 Starting X coordinate
 * @param y1 Starting Y coordinate
 * @param x2 End X coordinate
 * @param y2 End Y coordinate
 * @param col Color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_draw_line(gt_screen *screen, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t col){
    if(screen == NULL){
        return;
    }
    if(x1 == x2){
        if(y2 < y1){
            uint32_t temp = y2;
            y2 = y1;
            y1 = temp;
        }
        for(uint32_t i = 0; i < (y2 - y1); i++){
            screen->screen_buffer[(y1 + i) * screen->width + x1].data.bg_color = col;
        }
    }
    else if(y1 == y2){
        if(x2 < x1){
            uint32_t temp = x2;
            x2 = x1;
            x1 = temp;
        }
        for(uint32_t i = 0; i < (x2 - x1); i++){
            screen->screen_buffer[y1 * screen->width + x1 + i].data.bg_color = col;
        }
    }
    else{
        /* Bresenham's line algorithm */
        int32_t x, y, dx, dy, dx1, dy1, px, py, xe, ye;

        dx = (int32_t)x2 - x1;
        dy = (int32_t)y2 - y1;

        dx1 = abs(dx);
        dy1 = abs(dy);

        px = 2 * dy1 - dx1;
        py = 2 * dx1 - dy1;

        if(dy1 <= dx1){
            if(dx >= 0){
                x = x1;
                y = y1;
                xe = x2;
            }else{
                x = x2;
                y = y2;
                xe = x1;
            }
            screen->screen_buffer[y * screen->width + x].data.bg_color = col;

            for(int32_t i = 0; x < xe; i++){
                x++;
                if(px < 0){
                    px = px + 2 * dy1;
                }
                else{
                    if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)){
                        y++;
                    }
                    else{
                        y--;
                    }
                    px = px + 2 * (dy1 - dx1);
                }
                screen->screen_buffer[y * screen->width + x].data.bg_color = col;
            }
        }
        else{
            if(dy >= 0){
                x = x1;
                y = y1;
                ye = y2;
            }else{
                x = x2;
                y = y2;
                ye = y1;
            }
            screen->screen_buffer[y * screen->width + x].data.bg_color = col;

            for(int32_t i = 0; y < ye; i++){
                y++;
                if(py <= 0){
                    py = py + 2 * dx1;
                }
                else{
                    if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)){
                        x++;
                    }
                    else{
                        x--;
                    }
                    py = py + 2 * (dx1 - dy1);
                }
                screen->screen_buffer[y * screen->width + x].data.bg_color = col;
            }
        }
    }
}

/**
 * @brief Gets an 8bit color approximation of an RGB value
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return uint8_t 
 */
uint8_t gt_get_color(uint8_t r, uint8_t g, uint8_t b){
    return 16 + 36 * (r / 51) + 6 * (g / 51) + (b / 51);
}