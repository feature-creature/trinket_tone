// ----------
// metadata
// ----------
// Simplified tone generator using Timer1 on the ATtiny85 chip
// Author: Luke Demarest <luke@demare.st>
// Date: 2017.12.01
// Hardware: Adafruit Trinket (AVR ATtiny85)
// Software: Arduino 1.6.4
// ----------
// references
// ----------
// This software is based on Bruce Hall's Trinket Tone Generator,
// which is loosely based on the Arduino Tone Library,
// Name:    TTone, a "Trinket" tone generator
// Author:  Bruce E. Hall <bhall66@gmail.com>
// ----------


/*************************************************
* Note Pitch Defined Constants
*************************************************/
// from arduino documentation:
// #define is a useful C component that allows the programmer to give a name to a constant value before the program is compiled.
// Defined constants in arduino don’t take up any program memory space on the chip.
// The compiler will replace references to these constants with the defined value at compile time.

// This can have some unwanted side effects though,
// if for example, a constant name that had been #defined is included in some other constant or variable name.
// In that case the text would be replaced by the #defined number (or text).

// In general, the const keyword is preferred for defining constants and should be used instead of #define.

#define B0 31
#define C1 33
#define CS1 35
#define D1 37
#define DS1 39
#define E1 41
#define F1 44
#define FS1 46
#define G1 49
#define GS1 52
#define A1 55
#define AS1 58
#define B1 62
#define C2 65
#define CS2 69
#define D2 73
#define DS2 78
#define E2 82
#define F2 87
#define FS2 93
#define G2 98
#define GS2 104
#define A2 110
#define AS2 117
#define B2 123
#define C3 131
#define CS3 139
#define D3 147
#define DS3 156
#define E3 165
#define F3 175
#define FS3 185
#define G3 196
#define GS3 208
#define A3 220
#define AS3 233
#define B3 247
#define C4 262
#define CS4 277
#define D4 294
#define DS4 311
#define E4 330
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define A4 440
#define AS4 466
#define B4 494
#define C5 523
#define CS5 554
#define D5 587
#define DS5 622
#define E5 659
#define F5 698
#define FS5 740
#define G5 784
#define GS5 831
#define A5 880
#define AS5 932
#define B5 988
#define C6 1047
#define CS6 1109
#define D6 1175
#define DS6 1245
#define E6 1319
#define F6 1397
#define FS6 1480
#define G6 1568
#define GS6 1661
#define A6 1760
#define AS6 1865
#define B6 1976
#define C7 2093
#define CS7 2217
#define D7 2349
#define DS7 2489
#define E7 2637
#define F7 2794
#define FS7 2960
#define G7 3136
#define GS7 3322
#define A7 3520
#define AS7 3729
#define B7 3951
#define C8 4186
#define CS8 4435
#define D8 4699
#define DS8 4978


/*************************************************
* Note Duration Constants (not used in Ttone)
*************************************************/
#define FN 1 // 64th note
#define TN 2 // 32nd note
#define DTN 3 // dotted 32nd note
#define SN 4 // 16th note
#define DSN 6 // dotted 16th note
#define EN 8 // 8th note
#define DEN 12 // dotted 8th note
#define QN 16 // quarter note
#define DQN 24 // dotted quarter note
#define HN 32 // half note
#define DHN 48 // dotted half note
#define WN 64 // whole note
#define DWN 96 // dotted whole note


const uint16_t noteArray[] = {
  B0,
  C1,
  CS1,
  D1,
  DS1,
  E1,
  F1,
  FS1,
  G1,
  GS1,
  A1,
  AS1,
  B1,
  C2,
  CS2,
  D2,
  DS2,
  E2,
  F2,
  FS2,
  G2,
  GS2,
  A2,
  AS2,
  B2,
  C3,
  CS3,
  D3,
  DS3,
  E3,
  F3,
  FS3,
  G3,
  GS3,
  A3,
  AS3,
  B3,
  C4,
  CS4,
  D4,
  DS4,
  E4,
  F4,
  FS4,
  G4,
  GS4,
  A4,
  AS4,
  B4,
  C5,
  CS5,
  D5,
  DS5,
  E5,
  F5,
  FS5,
  G5,
  GS5,
  A5,
  AS5,
  B5,
  C6,
  CS6,
  D6,
  DS6,
  E6,
  F6,
  FS6,
  G6,
  GS6,
  A6,
  AS6,
  B6,
  C7,
  CS7,
  D7,
  DS7,
  E7,
  F7,
  FS7,
  G7,
  GS7,
  A7,
  AS7,
  B7,
  C8,
  CS8,
  D8,
  DS8
};
//#include <avr/power.h>
// the 'volatile' variable qualifier directs the compiler to load the unsigned 32-bit integer from RAM (not from a storage register)
volatile uint32_t toggle_count;

const int ledPin = 1;
int capPotVal;
int capPotMin = 1023;
int capPotMax = 0;

void setup() {
//  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  pinMode(ledPin, OUTPUT);

  // calibrate soft pot
  indicateCalibrate();
  while (millis() < 10500) {
    capPotVal = analogRead(1);
    if (capPotVal > capPotMax) {
      capPotMax = capPotVal;
    }
    if (capPotVal < capPotMin) {
      capPotMin = capPotVal;
    }
  }
  indicateCalibrate();

}

void loop() {
  // capacitive touch potentiometer @ 5V : from 1/3 Vcc to 2/3 Vcc
  // 341 - 683
  // pin 4 (physically on the board) is referenced as pin 2 in the 'analogRead' context
  capPotVal = analogRead(1);
  int potMap = constrain(map(capPotVal, capPotMin, capPotMax - (capPotMax / 15), 0, 88), 0, 88);
  //  int potMap = map(capPotVal, 0, 1023, 0, 88);
  //  beep(ledPin, noteArray[potMap], 1000);
  //  delay(100);
  if (potMap < 75) {
    playMusic(potMap);
    //    beep(ledPin, noteArray[potMap], 100);
    //    delay(100);
  }
}


// If you have a speaker connected to an output pin running analogOut(),
// you’ll get a changing loudness, but a constant tone.
// To change the tone, you need to change the frequency.

// TrinketTone:
// Generate a square wave on a given frequency & duration
// Call with frequency (in hertz) and duration (in milliseconds).
// Uses Timer1 in CTC mode (“Clear on Timer Compare Match" mode).
// Generated tone is non-blocking,
// so routine immediately returns while tone is playing.

void TrinketTone(uint16_t frequency, uint32_t duration) {
  // scan through prescalars to find the best fit
  uint32_t ocr = F_CPU / frequency / 2;
  uint8_t prescalarBits = 1;
  while (ocr > 255) {
    prescalarBits++;
    ocr /= 2;
  }
  // CTC mode; toggle OC1A pin; set prescalar
  TCCR1 = 0x90 | prescalarBits;

  // Calculate note duration in terms of toggle count
  //Duration will be tracked by timer1 ISR
  toggle_count = frequency * duration / 500;
  OCR1C = ocr - 1; // Set the OCR
  bitWrite(TIMSK, OCIE1A, 1); // enable interrupt
}


// Timer1 Interrupt Service Routine:
// Keeps track of note duration via toggle counter
// When correct time has elapsed, counter is disabled

ISR(TIMER1_COMPA_vect) {
  if (toggle_count != 0) // done yet?
    toggle_count--; // no, keep counting
  else // yes,
    TCCR1 = 0x90; // stop the counter
}

void playMusic(int noteSelected) {
  int len = 1000; // modify for speed (?)
  int dly = 100; // modify for articulation
  TrinketTone(noteArray[noteSelected], len);
  delay(dly);
}

void indicateCalibrate() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPin, HIGH);
    delay(50 * (6 - i));
    digitalWrite(ledPin, LOW);
    delay(50 * (6 - i));
  }
}

// The sound-producing function
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ // http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
  int  x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }
}
