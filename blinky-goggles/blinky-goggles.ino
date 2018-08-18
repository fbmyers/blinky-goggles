/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

// This sketch is intended to be used with the neopixel1 control
// surface in Adafruit's Bluefruit LE Connect mobile application.
//
// - Compile and flash this sketch to the nRF52 Feather
// - Open the Bluefruit LE Connect app
// - Switch to the neopixel1 utility
// - Click the 'connect' button to establish a connection and
//   send the meta-data about the pixel layout
// - Use the neopixel1 utility to update the pixels on your device

/* NOTE: This sketch required at least version 1.1.0 of Adafruit_neopixel1 !!! */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <bluefruit.h>

#define NEOPIXEL_VERSION_STRING "Neopixel v2.0"
#define LEFT_PIN                     7   /* Pin used to drive the neopixel1s */
#define RIGHT_PIN                     16   /* Pin used to drive the neopixel1s */

#define MAXCOMPONENTS  4
uint8_t *pixelBuffer = NULL;
uint8_t width = 0;
uint8_t height = 0;
uint8_t stride;
uint8_t componentsValue;
bool is400Hz;
uint8_t components = 3;     // only 3 and 4 are valid values

Adafruit_NeoPixel neopixel1 = Adafruit_NeoPixel();
Adafruit_NeoPixel neopixel2 = Adafruit_NeoPixel();

// BLE Service
BLEDis  bledis;
BLEUart bleuart;


///////
// blinky vars from greg...

// define universal constants
const float pi = 3.14159; 
const float tau = pi*2;

// define global parameters
const int pause = 20;
const int PIN = 3;
const int NPIN = 16;
const byte VALMAX = 31;
const byte VALMIN = 3;
const float DTHETA = tau/64.;

// define derived parameters
const byte VALAVG = ((float)VALMAX + (float)VALMIN)/2.0;
const byte VALAMP = (float)VALMAX - (((float)VALMAX + (float)VALMIN)/2.0);

// initialize arrays of 0-255 values for brightness and colors
byte vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte sats[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte hues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

boolean reset;

byte valSpinN = 1;
byte valSpinIncr = 1;

byte valSpinVals[]  = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38};
byte valSpinSteps[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte valSpinInds[]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float theta;
float dtheta = tau/64.;
byte j;

byte nCycles;




void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit Bluefruit neopixel1 Test");
  Serial.println("--------------------------------");

  Serial.println();
  Serial.println("Please connect using the Bluefruit Connect LE application");
  
  // Config neopixel1s
  neopixel1.begin();
  neopixel2.begin();
  
  // Init Bluefruit
  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Bluefruit52");
  Bluefruit.setConnectCallback(connect_callback);

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather52");
  bledis.begin();  

  // Configure and start BLE UART service
  bleuart.begin();

  // Set up and start advertising
  startAdv();

  // Setup Neopixels
  setupNeopixels();
  
  // Setup blinky
  setupSpinner();
}

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // Include bleuart 128-bit uuid
  Bluefruit.Advertising.addService(bleuart);

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void connect_callback(uint16_t conn_handle)
{
  char central_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);

  Serial.println("Please select the 'neopixels' tab, click 'Connect' and have fun");
}

void loop()
{
  // Echo received data
  if ( Bluefruit.connected() && bleuart.notifyEnabled() )
  {
    int command = bleuart.read();

    switch (command) {
      case 'V': {   // Get Version
          commandVersion();
          break;
        }
  
      case 'S': {   // Setup dimensions, components, stride...
          commandSetup();
          break;
       }

      case 'C': {   // Clear with color
          commandClearColor();
          break;
      }

      case 'B': {   // Set Brightness
          commandSetBrightness();
          break;
      }
            
      case 'P': {   // Set Pixel
          commandSetPixel();
          break;
      }
  
      case 'I': {   // Receive new image
          commandImage();
          break;
       }

    }
  }
  else { // Run Greg's routine
      Serial.println("Running auto blinky...");
      updateSpinner();
  }
}

void swapBuffers()
{
  uint8_t *base_addr = pixelBuffer;
  int pixelIndex = 0;
  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++) {
      if (components == 3) {
        neopixel1.setPixelColor(pixelIndex, neopixel1.Color(*base_addr, *(base_addr+1), *(base_addr+2)));
        neopixel2.setPixelColor(pixelIndex, neopixel2.Color(*base_addr, *(base_addr+1), *(base_addr+2)));
        
      }
      else {
        neopixel1.setPixelColor(pixelIndex, neopixel1.Color(*base_addr, *(base_addr+1), *(base_addr+2), *(base_addr+3) ));
        neopixel2.setPixelColor(pixelIndex, neopixel2.Color(*base_addr, *(base_addr+1), *(base_addr+2), *(base_addr+3) ));
        
      }
      base_addr+=components;
      pixelIndex++;
    }
    pixelIndex += stride - width;   // Move pixelIndex to the next row (take into account the stride)
  }
  neopixel1.show();
  neopixel2.show();
  

}

void commandVersion() {
  Serial.println(F("Command: Version check"));
  sendResponse(NEOPIXEL_VERSION_STRING);
}

#define NUM_LEDS 16

void setupNeopixels() {

  stride = 8;
  is400Hz = false; 

  neoPixelType pixelType;
  pixelType = NEO_GRB + NEO_KHZ800;

  
  if (pixelBuffer != NULL) {
      delete[] pixelBuffer;
  }

  pixelBuffer = new uint8_t[NUM_LEDS*3]; //each EYE is 16 LEDs
  
  neopixel1.updateLength(NUM_LEDS);
  neopixel1.updateType(pixelType);
  neopixel1.setPin(LEFT_PIN);

  neopixel2.updateLength(NUM_LEDS);
  neopixel2.updateType(pixelType);
  neopixel2.setPin(RIGHT_PIN);
  
  // Done
  //sendResponse("OK");
}

//deprecated, but may be required for app to work...
void commandSetup() {
  setupNeopixels();
  sendResponse("OK");
}

void commandSetBrightness() {
  Serial.println(F("Command: SetBrightness"));

   // Read value
  uint8_t brightness = bleuart.read();

  // Set brightness
  neopixel1.setBrightness(brightness);
  neopixel2.setBrightness(brightness);

  // Refresh pixels
  swapBuffers();

  // Done
  sendResponse("OK");
}

void commandClearColor() {
  Serial.println(F("Command: ClearColor"));

  // Read color
  uint8_t color[MAXCOMPONENTS];
  for (int j = 0; j < components;) {
    if (bleuart.available()) {
      color[j] = bleuart.read();
      j++;
    }
  }

  // Set all leds to color
  int size = width * height;
  uint8_t *base_addr = pixelBuffer;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < components; j++) {
      *base_addr = color[j];
      base_addr++;
    }
  }

  // Swap buffers
  Serial.println(F("ClearColor completed"));
  swapBuffers();


  if (components == 3) {
    Serial.printf("\tclear (%d, %d, %d)\n", color[0], color[1], color[2] );
  }
  else {
    Serial.printf("\tclear (%d, %d, %d, %d)\n", color[0], color[1], color[2], color[3] );
  }
  
  // Done
  sendResponse("OK");
}

void commandSetPixel() {
  Serial.println(F("Command: SetPixel"));

  // Read position
  uint8_t x = bleuart.read();
  uint8_t y = bleuart.read();

  // Read colors
  uint32_t pixelOffset = y*width+x;
  uint32_t pixelDataOffset = pixelOffset*components;
  uint8_t *base_addr = pixelBuffer+pixelDataOffset;
  for (int j = 0; j < components;) {
    if (bleuart.available()) {
      *base_addr = bleuart.read();
      base_addr++;
      j++;
    }
  }

  // Set colors
  uint32_t neopixelIndex = y*stride+x;
  uint8_t *pixelBufferPointer = pixelBuffer + pixelDataOffset;
  uint32_t color;
  if (components == 3) {
    color = neopixel1.Color( *pixelBufferPointer, *(pixelBufferPointer+1), *(pixelBufferPointer+2) );
    color = neopixel2.Color( *pixelBufferPointer, *(pixelBufferPointer+1), *(pixelBufferPointer+2) );
    
    Serial.printf("\tcolor (%d, %d, %d)\n",*pixelBufferPointer, *(pixelBufferPointer+1), *(pixelBufferPointer+2) );
  }
  else {
    color = neopixel1.Color( *pixelBufferPointer, *(pixelBufferPointer+1), *(pixelBufferPointer+2), *(pixelBufferPointer+3) );
    color = neopixel2.Color( *pixelBufferPointer, *(pixelBufferPointer+1), *(pixelBufferPointer+2), *(pixelBufferPointer+3) );
    
    Serial.printf("\tcolor (%d, %d, %d, %d)\n", *pixelBufferPointer, *(pixelBufferPointer+1), *(pixelBufferPointer+2), *(pixelBufferPointer+3) );    
  }
  neopixel1.setPixelColor(neopixelIndex, color);
  neopixel1.show();
  neopixel2.setPixelColor(neopixelIndex, color);
  neopixel2.show();
  // Done
  sendResponse("OK");
}

void commandImage() {
  Serial.printf("Command: Image %dx%d, %d, %d\n", width, height, components, stride);
  
  // Receive new pixel buffer
  int size = width * height;
  uint8_t *base_addr = pixelBuffer;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < components;) {
      if (bleuart.available()) {
        *base_addr = bleuart.read();
        base_addr++;
        j++;
      }
    }

/*
    if (components == 3) {
      uint32_t index = i*components;
      Serial.printf("\tp%d (%d, %d, %d)\n", i, pixelBuffer[index], pixelBuffer[index+1], pixelBuffer[index+2] );
    }
    */
  }

  // Swap buffers
  Serial.println(F("Image received"));
  swapBuffers();

  // Done
  sendResponse("OK");
}

void sendResponse(char const *response) {
    Serial.printf("Send Response: %s\n", response);
    bleuart.write(response, strlen(response)*sizeof(char));
}

