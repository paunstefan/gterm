/**
 * @file gterm.h
 * @author paunstefan
 * @brief Header file of gterm library.
 * @version 0.1
 * @date 2020-10-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef GTERM_H
#define GTERM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* MACROS */
#define RESET_SCREEN() printf("\x1B[2J\x1B[H")

/* Defines */
typedef struct gt_screen gt_screen;
typedef union gt_pixel gt_pixel;

/**
 * @brief Enum of the 16 basic colors.
 * 
 */
typedef enum gt_color{
    GT_BLACK = 0,
    GT_RED,
    GT_GREEN,
    GT_YELLOW,
    GT_BLUE,
    GT_PURPLE,
    GT_CYAN,
    GT_GRAY,
    GT_HGRAY,
    GT_HRED,
    GT_HGREEN,
    GT_HYELLOW,
    GT_HBLUE,
    GT_HPURPLE,
    GT_HCYAN,
    GT_WHITE,
    GT_END_COLOR
} gt_color;

/* Structures */
/**
 * @brief Structure for each gterm pixel.
 * 
 */
union gt_pixel
{
    struct
    {
        uint8_t character;
        uint8_t fg_color;
        uint8_t bg_color;
        uint8_t unused;
    } data;
    
    uint32_t raw_data;
};

/**
 * @brief Base structure of the gterm library.
 * 
 */
struct gt_screen
{
    uint32_t width;
    uint32_t height;
    bool square_px;

    gt_pixel *screen_buffer;
    
};


/* Forward declarations */

/**
 * @brief Allocates memory for gterm screen structure.
 * 
 * @param w Width of the screen
 * @param h Height of the screen
 * @param square True for square pixels, false for standard terminal characters.
 * @return gt_screen*
 */
gt_screen* gt_init_screen(uint32_t w, uint32_t h, bool square);

/**
 * @brief Free the gterm screen structure
 * 
 * @param screen The st_screen structure to free.
 */
void gt_free_screen(gt_screen *screen);

/**
 * @brief Refresh the image shown.
 * 
 * @param screen Pointer to gt_screen.
 */
void gt_refresh(gt_screen *screen);

/**
 * @brief Set the background color and remove everything currently on the screen.
 * 
 * @param screen Pointer to gt_screen.
 * @param bgcolor Background color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_set_background(gt_screen *screen, uint8_t bgcolor);

/**
 * @brief Set a pixel to a certain color.
 * 
 * @param screen Pointer to gt_screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param col Color, from the gt_color enum or using the gt_get_color() function.
 */
void gt_set_pixel(gt_screen *screen, uint32_t x, uint32_t y, uint8_t col);

/**
 * @brief Get the current background color of pixel.
 * 
 * @param screen Pointer to gt_screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @return uint8_t 
 */
uint8_t gt_get_bgcolor(gt_screen *screen, uint32_t x, uint32_t y);

/**
 * @brief Sets the screen to black.
 * 
 * @param screen Pointer to gt_screen.
 */
void gt_clear_screen(gt_screen *screen);

/**
 * @brief Gets an 8bit color approximation of an RGB value
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return uint8_t 
 */
uint8_t gt_get_color(uint8_t r, uint8_t g, uint8_t b);

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
void gt_print_text(gt_screen *screen, uint32_t x, uint32_t y, char *text, uint8_t color);

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
void gt_draw_rect(gt_screen *screen, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t col);

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
void gt_draw_line(gt_screen *screen, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t col);

#ifdef __cplusplus
}
#endif

#endif /* GTERM_H */
