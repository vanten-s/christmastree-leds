
// Import FastLED
#include <FastLED.h>

// Define number of LED's on a light strip
#define N_LEDS 300

// Define brightness
#define BRIGHNTESS 100


// Led array
CRGB leds[ N_LEDS ];

// Time as a uint8_t to make it much easier to use with CHSV( ) 
uint8_t time = 0;

// Time as a long int to make it easier to use over longer periods
long int longTime = 0;

// Color for color specific operations
CRGB color = CRGB(0, 89, 117);

// What mode are we using right now
int mode = 0;

// Define n points
#define N_POINTS 3

// Points for use with slowlights
float points[N_POINTS];

// Hue for color
int color_hue;

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

void lightNeighbours ( float p )
{
    int closest = round( p );
    for ( int i = closest; i < closest + 10; i++ ) 
    {
        leds[i] = CHSV( color_hue, 255, BRIGHNTESS*1/(1+i-p) );
    }
}

// Slow lights
int slowlights ( )
{

    // Clear
    black( );

    // Loop over points
    for ( int i = 0; i < N_POINTS; i++ )
    {
        Serial.println( points[ i ] );
        lightNeighbours( points[ i ] );
        // float changeAmount = random( 0, 10 ) / 10.0;
        // points[ i ] += changeAmount;
    }

}

// Define number of modes
#define N_MODES 5

// Define array of int functions
int ( *modes[ N_MODES ] )( ) = { rainbow_solid, blink, black, solid, slowlights };

// Run on start
void setup ( )
{

    // Init serial communication
    Serial.begin( 9600 );
    Serial.println( "Begin" );

    // Add LED array to FastLED
    FastLED.addLeds< NEOPIXEL, 6 > ( leds, 300 );
   
    for ( int i = 0; i < N_POINTS; i++ )
    {
        float place = (float)random( 0, N_LEDS );
        Serial.println( place );
        points[i] = place;
    }

}

// Run Continuosly after setup ( )
void loop ( )
{

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
    modes[mode]( );

    // Update the real life LED's
    FastLED.show( );

    // Add to time variable and delay 10 ms
    time += 1;
    delay( 20 );

    // Protocol
    // First byte, '0': then switch mode to the number in the next 3 bytes. '1': then the next 3 bytes determines color in ASCII encoded decimal between 0-360

    // If unread msg exists
    if ( Serial.available( ) > 0 )
    {
        char buf[5] = "0000";
        Serial.readBytesUntil( '\n', buf, 5 );
        Serial.println( buf );
        String str = String( buf );
        switch ( str[0] )
        {
            case '0':
                Serial.println( "Changing Mode!" );
                str = str.substring( 1 );
                mode = str.toInt( );
                break;
            case '1':
                Serial.println( "Changing Color!" );
                str = str.substring( 1 );
                int hue360 = str.toInt( );
                uint8_t hue = 255 * ((float)hue360) / 360;
                color_hue = hue;
                color = CHSV( hue, 255, BRIGHNTESS );
                break;
        }
    }

}
