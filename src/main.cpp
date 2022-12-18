/*
  NeoTree
  -------

  Want to program via USB? Make sure to select "env:usb" as PlatformIO environment on the bottom!

*/


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


const uint8_t LED_PIN = PB0; // works!
const uint8_t BTN = PB1; // BTN to GND
const uint8_t NUM_LEDS = 15;
const uint8_t LONG_PRESS_CNT = 20;

unsigned long BTN_PRESS_CNT,GLOBAL_CNT;
byte MODE,SUBMODE = 0;


//const uint8_t LED_PIN = PB1; // Builtin-LED; red is yellow?!
//const uint8_t LED_PIN = PB2; // works!
//const uint8_t LED_PIN = PB3; // works! USB D-; LED white at start
//const uint8_t LED_PIN = PB4; // works! USB D+; LED white at start
//const uint8_t LED_PIN = PB5; // DOES NOT WORK!

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint8_t getRandomPixel();
uint16_t getRandomInt(uint16_t max);

/*
    ### ANIMATIONS ###
*/

void ani_rainbow(uint8_t mul = 1) {
  static float offset;
  offset = offset + 4.0/(SUBMODE+1);
  uint8_t offs = round(offset);
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.ColorHSV((offs+mul*i*(256/NUM_LEDS))<<8,255,255)); 
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255,255,255));
}

void ani_rainbow_white_h(uint8_t mul = 1) {
  static float offset;
  offset = offset + 4.0/(SUBMODE+1);
  uint8_t offs = round(offset);
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.ColorHSV((offs+mul*i*(256/NUM_LEDS))<<8,255,255)); 
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255,255,255));
  strip.setPixelColor(2, strip.Color(175,175,175));
  strip.setPixelColor(3, strip.Color(175,175,175));
  strip.setPixelColor(6, strip.Color(175,175,175));
  strip.setPixelColor(9, strip.Color(175,175,175));
  strip.setPixelColor(12, strip.Color(175,175,175));
}

void ani_rainbow_white_v(uint8_t mul = 1) {
  static float offset;
  offset = offset + 4.0/(SUBMODE+1);
  uint8_t offs = round(offset);
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.ColorHSV((offs+mul*i*(256/NUM_LEDS))<<8,255,255)); 
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255,255,255));
  /*
  strip.setPixelColor(0, strip.Color(175,175,175));
  strip.setPixelColor(2, strip.Color(175,175,175));
  strip.setPixelColor(5, strip.Color(175,175,175));
  strip.setPixelColor(6, strip.Color(175,175,175));
  strip.setPixelColor(7, strip.Color(175,175,175));
  strip.setPixelColor(9, strip.Color(175,175,175));
  strip.setPixelColor(11, strip.Color(175,175,175));
  */
  strip.setPixelColor(0, strip.Color(175,175,175));
  strip.setPixelColor(3, strip.Color(175,175,175));
  strip.setPixelColor(5, strip.Color(175,175,175));
  strip.setPixelColor(7, strip.Color(175,175,175));
  strip.setPixelColor(11, strip.Color(175,175,175));
  strip.setPixelColor(12, strip.Color(175,175,175));
}


void ani_solid_color() {
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.ColorHSV(((SUBMODE*20)%256)<<8,255,255));
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255,255,255));
}

void white_sparkles() {
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(0, 0, 0));
  if((GLOBAL_CNT % (2 + SUBMODE)) == 0) {
    strip.setPixelColor( getRandomPixel() , strip.Color(255, 255, 255));
  }
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255, 255, 255));
}

void random_colors() {
  if((GLOBAL_CNT % (2 + SUBMODE)) == 0) {
    strip.setPixelColor( getRandomPixel() , strip.ColorHSV(getRandomInt(255)<<8,255,255) );
  }
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255, 255, 255));
}

/*
    ### OTHER STUFF ###
*/

uint8_t getRandomPixel() {
  return floor( rand()/(RAND_MAX/(NUM_LEDS-1)) );
}

uint16_t getRandomInt(uint16_t max) {
  return floor( rand()/(RAND_MAX/(max+1)) );
}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif   
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring 
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both 
  long result = (high<<8) | low; 
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

void showChargingLevel() {
  long vcc = readVcc(); // Vcc in millivolts
  if(vcc >= 3200) {
    vcc = vcc - 3200; // 3200-4200 -> 0-1000
    vcc = vcc*NUM_LEDS; 
    vcc = vcc/1000; // 0-15
    if(vcc > NUM_LEDS) vcc = NUM_LEDS; // clamp to NUM_LEDS
  } else {
    vcc = 0;
  }
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(50, 0, 0)); // all red
  for(uint8_t i=0; i<vcc; i++) strip.setPixelColor(i, strip.Color(0, 50, 0)); // vcc amount green leds
  strip.show(); 
}

void btnCheck() {
  // Check Button press
  if(digitalRead(BTN) == 0) {
    strip.setPixelColor(NUM_LEDS-1, strip.Color(10, 10, 10));
    BTN_PRESS_CNT++;
    if(BTN_PRESS_CNT%LONG_PRESS_CNT == 0) {
      // Long press action every ~second
      SUBMODE++;
      strip.setPixelColor(NUM_LEDS-1, strip.Color(255, 255, 255));
    }
  } else {
    if(BTN_PRESS_CNT > 1 && BTN_PRESS_CNT < LONG_PRESS_CNT) {
      // Single press action
      MODE++;
      SUBMODE = 0; // reset Sub-Mode when changing to next mode/animation
      GLOBAL_CNT = 0;
      strip.setPixelColor(NUM_LEDS-1, strip.Color(255, 255, 255));
    }
    BTN_PRESS_CNT = 0;
  }
}

void setup() {
  // put your setup code here, to run once:
  cli(); // Disable interrupts
  //CLKPR = (1<<CLKPCE); // Prescaler enable
  //CLKPR = 0x00; // Clock division factor 8 (0011)
  sei(); // Enable interrupts
  //delay(1e3);
  pinMode(BTN,INPUT_PULLUP);
  strip.begin();
  strip.setBrightness(10);
  strip.show(); // Initialize all pixels to 'off'
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(30, 30, 30)); strip.show(); delay(500);  // all white - pixel test
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(0, 0, 0)); strip.show(); delay(50); // all off
  showChargingLevel();
  delay(1000);
}


void loop() {
  switch (MODE) {
    case __COUNTER__: ani_rainbow(); break;
    case __COUNTER__: ani_rainbow_white_h(); break;
    case __COUNTER__: ani_rainbow_white_v(); break;
    case __COUNTER__: ani_rainbow(0); break;
    case __COUNTER__: ani_rainbow_white_h(0); break;
    case __COUNTER__: ani_rainbow_white_v(0); break;
    case __COUNTER__: ani_rainbow(7); break;
    case __COUNTER__: ani_rainbow_white_h(7); break;
    case __COUNTER__: ani_rainbow_white_v(7); break;
    case __COUNTER__: ani_solid_color(); break;
    case __COUNTER__: white_sparkles(); break;
    case __COUNTER__: random_colors(); break;
    default: MODE = 0; break;
  }  
  GLOBAL_CNT++; // global frame count, used for some animations
  btnCheck();
  strip.show(); 
  delay(33); // ~30fps
}