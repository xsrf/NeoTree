#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


const uint8_t LED_PIN = PB0; // works!
const uint8_t BTN = PB1; // BTN to GND
const uint8_t NUM_LEDS = 15;

//const uint8_t LED_PIN = PB1; // Builtin-LED; red is yellow?!
//const uint8_t LED_PIN = PB2; // works!
//const uint8_t LED_PIN = PB3; // works! USB D-; LED white at start
//const uint8_t LED_PIN = PB4; // works! USB D+; LED white at start
//const uint8_t LED_PIN = PB5; // DOES NOT WORK!

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  cli(); // Disable interrupts
  //CLKPR = (1<<CLKPCE); // Prescaler enable
  //CLKPR = 0x00; // Clock division factor 8 (0011)
  sei(); // Enable interrupts
  //delay(1e3);
  pinMode(BTN,INPUT_PULLUP);
  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'
}

void ani_rainbow() {
  static uint8_t offset;
  static uint16_t aniDelay = 50;
  offset = offset + 4;
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.ColorHSV((offset+i*(256/NUM_LEDS))<<8,255,255)); 
  strip.setPixelColor(NUM_LEDS-1, strip.Color(255,255,255)); 
  strip.setBrightness(10);
  strip.show(); 
  delay(aniDelay);
  if(!digitalRead(BTN)) aniDelay += 5;
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


void loop() {
  // put your main code here, to run repeatedly:
  //for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(50, 0, 0)); strip.show(); delay(50); 
  //for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(0, 50, 0)); strip.show(); delay(50); 
  //for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(0, 0, 50)); strip.show(); delay(50); 
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(10, 10, 10)); strip.show(); delay(500); 
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(0, 0, 0)); strip.show(); delay(50); 
  long vcc = readVcc();
  if(vcc >= 3200) {
    vcc = vcc - 3200;
    vcc = vcc*NUM_LEDS;
    vcc = vcc/1000;
    if(vcc > NUM_LEDS) vcc = NUM_LEDS;
  } else {
    vcc = 0;
  }
  for(uint8_t i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(50, 0, 0));
  for(uint8_t i=0; i<vcc; i++) strip.setPixelColor(i, strip.Color(0, 50, 0)); 
  strip.show(); 
  delay(1000);   
  while(1) ani_rainbow();
}