# NeoPixelGridStreamer
Processing and Arduino files to allow video streaming over USB from a desktop to a microcontroller connected to a low-res grid of NeoPixels

## How to use
You need a desktop/laptop with Processing installed, connected over USB to a microcontroller. This example leverages an Adafruit Feather M4.

### Processing_VideoToSerial
* Update this script to point to the microcontroller's serial connection, the NeoPixel grid's configuration, and a video file to play
* This is a "live-stream" so only run the Processing script once the microcontroller is set up

### Arduino_PixelStream
* This was tested with an Adafruit Feather M4 controller
* Very little needs to be updated in this file, just LED_PIN and LED_COUNT. The rest is handled in the Processing script above
