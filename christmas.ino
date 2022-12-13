
// Import FastLED
#include <FastLED.h>

// Define number of LED's on a light strip
#define N_LEDS 300

// Define number of modes
#define N_MODES 1

// Led array
CRGB leds[ N_LEDS ];

// Time as a uint8_t to make it much easier to use with CHSV( ) 
uint8_t time = 0;

// What mode are we using right now
int mode = 0;

// Uniform solid rainbow across all LED's
int rainbow_solid ( )
{

    // Set every LED to the same color
    // Color is just the rainbow at time
    for ( int i = 0; i < N_LEDS; i++ )
    {
        leds[i] = CHSV( time, 255, 255 );
    }

    // Succes
    return 1;

}

// Define array of int functions
int ( *modes[ N_MODES ] )( ) = { rainbow_solid };

// Run on start
void setup ( )
{

    // Add LED array to FastLED
    FastLED.addLeds< NEOPIXEL, 6 > ( leds, 300 );

}

// Run after setup ( )
void loop ( )
{

    modes[mode]();

    // Update the LED's
    FastLED.show( );

    // Add to time variable and delay 10 ms
    time += 1;
    delay( 10 );

}
