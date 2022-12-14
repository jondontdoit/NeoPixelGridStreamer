// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 256

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

byte buff[3];
byte s = 0;
byte c = 0;
byte b_last = 0;
byte r = false, f = false;
int p = 0;

// setup() function -- runs once at startup --------------------------------

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)

  SerialUSB.begin(115200);
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

  if (SerialUSB.available()) {
    
    byte b = SerialUSB.read();

    // Identify the new frame tag
    if (b == 255 && b == b_last) {
      s++;
      if (s > 3) f = true;
    } else {
      s = 0;
    }
    b_last = b;

    // Once the new frame tag has passed
    if (f == true && s == 0) {
      f = false;
      r = true;
      p = 0;
      c = 0;
    }

    if (r == true) {
      buff[c] = b;
      c++;

      // If we have R, G, and B values for a pixel
      if (c > 2) {
        uint32_t clr = strip.Color(buff[0], buff[1], buff[2]);
        buff[0] = 0; buff[1] = 0; buff[2] = 0; 
        c = 0;
  
        strip.setPixelColor(p, clr);
        p++;
        //if (p % 16 == 0) p++;
        
        if (p >= LED_COUNT) {
          strip.show();   // Send the updated pixel colors to the hardware.
          r = false;
        }
      }
    }
    
  }
}
