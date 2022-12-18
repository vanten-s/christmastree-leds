
// Import FastLED
#include <FastLED.h>

// Define number of LED's on a light strip
#define N_LEDS 300

// Define number of modes
#define N_MODES 4

// Define brightness
#define BRIGHNTESS 100

// Led array
CRGB leds[ N_LEDS ];

// Time as a uint8_t to make it much easier to use with CHSV( ) 
uint8_t time = 0;

// Color for color specific operations
CRGB color = CRGB(0, 89, 117);

// What mode are we using right now
int mode = 0;

// Uniform solid rainbow across all LED's
int rainbow_solid ( )
{

    // Set every LED to the same color
    // Color is just the rainbow at time
    for ( int i = 0; i < N_LEDS; i++ )
    {
        leds[i] = CHSV( time, 255, BRIGHNTESS );
    }

    // Succes
    return 1;

}

// Mode for making the tree go crazy
int blink ( )
{

    // Set every LED to a random hue
    for ( int i = 0; i < N_LEDS; i++ )
    {
        leds[i] = CHSV( random8( ), 255, BRIGHNTESS );
    }

    // Succes
    return 1;

}

// Mode for just black so I dont have to manually turn it off
int black ( )
{

    // Set every LED to black
    for ( int i = 0; i < N_LEDS; i++ )
    {
        leds[i] = CRGB( 0, 0, 0 );
    }

    // Succes
    return 1;

}

// Normal solid color
int solid ( )
{

    // Set every LED to color
    for ( int i = 0; i < N_LEDS; i++ )
    {
        leds[i] = color;
    }


    // Succes
    return 1;

}

// Define array of int functions
int ( *modes[ N_MODES ] )( ) = { rainbow_solid, blink, black, solid };

// Run on start
void setup ( )
{

    // Init serial communication
    Serial.begin( 9600 );
    Serial.println("Begin");

    // Add LED array to FastLED
    FastLED.addLeds< NEOPIXEL, 6 > ( leds, 300 );

}

// Run Continuosly after setup ( )
void loop ( )
{

    // Protocol
    // First byte, '0': then switch mode to the number in the next 6 bytes. '1': then the next 9 bytes determines color in ASCII encoded 8-bit decimal

    // If unread msg exists
    if ( Serial.available( ) > 0 )
    {
        String str;
        switch ( (char)Serial.read( ) )
        {
            case '0':
                str = Serial.readStringUntil( '\n' );
                mode = str.toInt( );
                break;
            case '1':
                str = Serial.readStringUntil( '\n' );
                int r = str.substring( 0, 3 ).toInt( );
                int g = str.substring( 3, 6 ).toInt( );
                int b = str.substring( 6, 9 ).toInt( );
                Serial.println(r);
                Serial.println(g);
                Serial.println(b);
                color = CRGB( r, g, b );
                break;
        }
    }

    // Read msg ( old )
    /*if ( Serial.available( ) > 0 )
    {
        mode += 1;
        mode = mode % N_MODES;
        Serial.println( mode );
        while ( Serial.available( ) > 0 )
        {
          Serial.read( );
        }
    }*/

    // Update LED array
    modes[mode]();

    // Update the real life LED's
    FastLED.show( );

    // Add to time variable and delay 10 ms
    time += 1;
    delay( 10 );

}
