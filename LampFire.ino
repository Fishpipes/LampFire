// This is my version of the Fire2012
// Modified 01/29/2015 by David Steward
// Added a double string of LEDs
// Modified 02/27/15 added LCD control of light patterens

#include <FastLED.h>

#define LED_PIN     1
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    71

#define BRIGHTNESS  255

//Default is 60
#define FRAMES_PER_SECOND 15

// Single strip of 72 LEDs
// Define each Side of strip
int h;

// Set the Hues
int hues;

// Direction for Right side of LEDs
int directions;

CRGB leds[NUM_LEDS];

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  100

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 75

CRGBPalette16 gPal;

#include <LiquidCrystal.h>
#include <DFR_Key.h>
 
// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
//States for the menu.
DFR_Key keypad;

int localKey = 0;

// Menu pointer
int location;

String keyString = "";

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lamp Fire");
   
   // Setup the LEDs 
   delay(3000); // sanity delay
   FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness( BRIGHTNESS );
   directions = 1;
   hues = 1;
   location = 1;
}
 
void loop() {
  clearPrintTitle();
  // Get Key
  localKey = keypad.getKey();
  
   if (localKey == 1){
     selectMenu();}
   else {
   displayMenu();} 
   
   // What do we do with a key
   if (localKey == 3) {
     location = location - 1;
     if (location < 1){
       location = 10;}}
     
   if (localKey == 4){
     location = location + 1;  
      if (location > 10){
      location = 1;}}
 
   delay (150);
   
   // Select which light sequence to run
   switch (hues) {
     case 1: Fire(); break;
     case 2: Fire(); break;
     case 3: Fire(); break;
     case 4: Fade(); break;
     case 5: Fire(); break;
     case 6: Fire(); break;
     case 7: One(); break;
     case 8: Growing(); break;
   }
     
}
 
//Display Menu Option based on Index.
void displayMenu() {
     switch (location) {
      case 1:
        clearPrintTitle(); lcd.print ("-> Synch LEDs"); break;
      case 2:
        clearPrintTitle(); lcd.print ("-> Center LEDs"); break;
      case 3:
        clearPrintTitle(); lcd.print ("-> Random Fire"); break;
      case 4:
        clearPrintTitle(); lcd.print ("-> Green Fire");  break;
      case 5:
        clearPrintTitle(); lcd.print ("-> Wild Fire"); break;
      case 6:
       clearPrintTitle(); lcd.print ("-> Blue Fire"); break;       
      case 7:
       clearPrintTitle(); lcd.print ("-> Sea Fire"); break;
      case 8:
       clearPrintTitle(); lcd.print ("-> Fade"); break;        
      case 9:
       clearPrintTitle(); lcd.print ("-> One"); break;
      case 10:
       clearPrintTitle(); lcd.print ("-> Growing"); break;
    }
}
 
//Print a basic header on Row 1.
void clearPrintTitle() {
  lcd.clear();
  lcd.setCursor(0,0);
  switch (hues) {
      case 1:
        lcd.print ("Wild Fire "); UpDn(directions); break;
      case 2:
        lcd.print ("Blue Fire "); UpDn(directions); break;
      case 3:
        lcd.print ("Sea Fire "); UpDn(directions); break;
      case 4:
        lcd.print ("Fade "); UpDn(directions); break;
      case 5:
        lcd.print ("Green Fire "); UpDn(directions); break; 
     case 6:
        lcd.print ("Random Fire "); UpDn(directions); break;
     case 7:
        lcd.print ("One "); UpDn(directions); break;
     case 8:
        lcd.print ("Growing "); UpDn(directions); break;
        
       }       
  lcd.setCursor(0,1);
}

//Print direction of right LEDs
void UpDn(int directions){
  if (directions == 1){
    lcd.print ("Up");}
  if (directions == 2){
    lcd.print ("Dn");}
}

//Show the selection on Screen.
void selectMenu() {
   switch (location) {
       case 1:
        clearPrintTitle();
        lcd.print ("Synch LEDs");
        //Leave the Hue alone but Synch both rows
        directions = 1;
        break;
       case 2:
        clearPrintTitle();
        lcd.print ("Center LEDs");
        //Leave the Hue alone but Synch both rows
        directions = 2;
        break;
       case 3:
        clearPrintTitle();
        lcd.print ("Random Fire");
        //Set the hue to RandomFire
        hues = 6;
        break;
      case 4:
        clearPrintTitle();
        lcd.print ("Green Fire");
        //Set the Hue to Green fire
        hues = 5;
        gPal = CRGBPalette16( CRGB::Yellow, CRGB::Green, CRGB::Black);
        break;
      case 5:
        clearPrintTitle();
        lcd.print ("Wild Fire");
        //Set the Hue to Green fire
        hues = 1;
        gPal = HeatColors_p;
        break;
      case 6:
        clearPrintTitle();
        lcd.print ("Blue Fire");
        //Set the Hue to Blue/Aqua fire
        hues = 2;
        gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
        break;
      case 7:
        clearPrintTitle();
        lcd.print ("Sea Fire");
        //Set the Hue to SeaGreen fire
        hues = 3;
        gPal = CRGBPalette16( CRGB::Black, CRGB::SeaGreen, CRGB::Orange);
        break;        
      case 8:
        clearPrintTitle();
        lcd.print ("Fade");
        //Fade the LEDs in and out
        hues = 4;
        break;
      case 9:
        clearPrintTitle();
        lcd.print ("One");
        //One LED at a time
        hues = 4;
        break;
      case 10:
        clearPrintTitle();
        lcd.print ("Grow");
        //Grow the LEDs one at a time
        hues = 4;
        break;
    }
    delay(150);
}

// Random Palette for Fire2012
void Fire()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());
  
     if (hues == 6) {
     static uint8_t hue = 0;
       hue++;
       CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
       CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
       gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);
     }

     Fire2012WithPalette(); // run simulation frame, using palette colors
  
     FastLED.show(); // display this frame
     FastLED.delay(1000 / FRAMES_PER_SECOND);
}


void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];
  
  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    // Set number to range of half NUM_LEDS
    for( int j = 0; j < (NUM_LEDS/2); j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      // Right side bottom is number 1 led
            byte colorindex = scale8( heat[j], 240);
            
       // Set color for Left side      
      leds[j] = ColorFromPalette( gPal, colorindex);
      
      // Decide which direct the Right side is moving
      if (directions == 1) { 
        
      // Right side bottom is number 72 led. top is 35
      // This order sets both sides in synch
      h = 71 - j;
      }
      
      else {
      // Right side bottom is number 72 led, top is 35
      // This order sets right top to bottom and left bottom to top
      h = j + 34;
      }
      
      // Set color for Right side
      leds[h] = ColorFromPalette( gPal, colorindex);
     
  }
    
}

void One() {
  
  // one at a time
  for(int j = 0; j < 3; j++) {
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      memset(leds, 0, NUM_LEDS * 3);
      switch(j) {
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
      }
      FastLED.show();
      delay(10);
    }
  }
}

void Growing() {
  // growing/receeding bars
  for(int j = 0; j < 3; j++) {
    memset(leds, 0, NUM_LEDS * 3);
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      switch(j) {
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
      }
      FastLED.show();
      delay(10);
    }
    for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
      switch(j) {
        case 0: leds[i].r = 0; break;
        case 1: leds[i].g = 0; break;
        case 2: leds[i].b = 0; break;
      }
      FastSPI_LED.show();
      delay(1);
    }
  }
}  

void Fade() {
  // Fade in/fade out
  for(int j = 0; j < 3; j++ ) {
    memset(leds, 0, NUM_LEDS * 3);
    for(int k = 0; k < 256; k++) {
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) {
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastLED.show();
      delay(10);
    }
    for(int k = 255; k >= 0; k--) {
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) {
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastLED.show();
      delay(10);
    }
  }
}  
