
// Import FastLED
#include <FastLED.h>

// Define number of LED's on a light strip
#define N_LEDS 300

// Led array
CRGB leds[ N_LEDS ];

// Time as a uint8_t to make it much easier to use with CHSV( ) 
uint8_t time = 0;

// Run on start
void setup ( )
{

    // Add LED array to FastLED
    FastLED.addLeds< NEOPIXEL, 6 > ( leds, 300 );

}

// Run after setup ( )
void loop ( )
{

    // Set every LED to the same color
    // Color is just the rainbow at time
    for ( int i = 0; i < N_LEDS; i++ )
    {
        leds[i] = CHSV( time, 255, 255 );
    }

    // Update the LED's
    FastLED.show( );

    // Add to time variable and delay
    time += 1;
    delay( 10 );

}
