#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined (__LINUX__)
#error "[Compiling error] Rhino can't run on this OS."
#endif

#if !defined(__i386__)
// #error "[Compiling error] The kernel needs to be compiles with a ix86 compiler"
#endif

/** Setup the hardware text-mode colors **/
/** Set the ansi colors for usermode as constants **/
enum vga_colors {
    vga_color_black = 0,
    vga_color_blue = 1,
    vga_color_green = 2,
    vga_color_cyan = 3,
    vga_color_red = 4,
    vga_color_magenta = 5,
    vga_color_brown = 6,
    vga_color_grey = 7,
    vga_color_lightgrey = 8,
    vga_color_lightblue = 9,
    vga_color_lightgreen = 10,
    vga_color_lightcyan = 11,
    vga_color_lightred = 12,
    vga_color_lightmagenta = 13,
    vga_color_lightbrown = 14,
    vga_color_white = 15,
};

static const size_t vga_width = 80;
static const size_t vga_height = 25;

static inline uint8_t vga_entry_color( enum vga_color fg, enum vga_color bg ) {
    return fg | bg << 4;
}

static inline uint8_t vga_entry( unsigned char uc, uint8_t color ) {
    return ( uint8_t ) uc | ( uint16_t ) color  << 8;
}

size_t strlen( const char* str ) {
    size_t len = 0;
    while ( str[ len ] ) {
        len++;
    }

    return len;
}

static terminal_row;
static terminal_column;
static terminal_color;
static terminal_buffer;

void terminal_initialize ( void ) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_buffer = ( uint16_t* ) 0xB8000;
    terminal_color = vga_entry_color( vga_color_lightgrey, vga_color_black );
    for ( size_t y = 0; y < vga_height; y++ ) {
        for ( size_t x = 0; x < vga_width; x++ ) {
            const size_t index = y * vga_width + x;
            terminal_buffer[ index ] = vga_entry( '  ', terminal_color );
        }
    }

    printf("[Load the kernel] passed");

}

void terminal_setcolor ( uint8_t color ) {
    terminal_color = color;
}

void terminal_putentryat ( char c, uint8_t color, size_t x, size_t y ) {
    const size_t index = y * vga_width + x;
    terminal_buffer[ index ] = vga_entry( c, color );
}

void terminal_putchar ( char c ) {
    switch ( c ) {
        case '\n': {
                terminal_column = 0;
                terminal_row ++;
                break;
        }
    
        default: {
                const size_t index = (vga_height * terminal_row) + terminal_column; // Like before, calculate the buffer index
                terminal_buffer[index] = ((uint16_t)terminal_color << 8) | c;
                terminal_column ++;
                break;
        }
    }

    terminal_putentryat( c, terminal_color, terminal_column, terminal_row );
    if ( ++terminal_column == vga_width ) {
        terminal_column = 0;
        if ( ++terminal_row == vga_height ) {
            terminal_row = 0;
        }
    }
}

void terminal_write ( const char* data, size_t size ) {
    for ( size_t i = 0; i < size; i++ ) {
        terminal_putchar( data[ i ] );
    }
}

void terminal_writestring( const char* data ) {
    terminal_write( data, strlen( data ) );
}

void kernel_main( void ) {
    terminal_initialize( );
    terminal_writestring( "Rhino says hello from Kernel!\n\nThis operating system is beeing mantained by Timo Sarkar 2020" );
}