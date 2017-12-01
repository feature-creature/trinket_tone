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



// my tone array will be dynamically built via potentiometer input


/*************************************************
* Music Content is stored in the following array.
* PROGMEM is needed because of the large data size.
* "Prelude in C" Well-Tempered Clavier, J.S.Bach
*************************************************/
#define NOTECOUNT 544 // length of array


// progmem needed for large array. why?
#include <avr/pgmspace.h> // needed for PROGMEM
PROGMEM const uint16_t noteArray[] = {
  C4, E4, G4, C5, E5, G4, C5, E5, //measures 1-2, notes 1-32
  C4, E4, G4, C5, E5, G4, C5, E5,
  C4, D4, A4, D5, F5, A4, D5, F5,
  C4, D4, A4, D5, F5, A4, D5, F5,
  B3, D4, G4, D5, F5, G4, D5, F5, //measures 3-4, notes 33-64
  B3, D4, G4, D5, F5, G4, D5, F5,
  C4, E4, G4, C5, E5, G4, C5, E5,
  C4, E4, G4, C5, E5, G4, C5, E5,

  C4, E4, A4, E5, A5, A4, E5, A5, //measures 5-6, notes 65-96
  C4, E4, A4, E5, A5, A4, E5, A5,
  C4, D4, FS4, A4, D5, FS4, A4, D5,
  C4, D4, FS4, A4, D5, FS4, A4, D5,

  B3, D4, G4, D5, G5, G4, D5, G5, //measures 7-8, notes 97-128
  B3, D4, G4, D5, G5, G4, D5, G5,
  B3, C4, E4, G4, C5, E4, G4, C5,
  B3, C4, E4, G4, C5, E4, G4, C5,

  A3, C4, E4, G4, C5, E4, G4, C5, //measures 9-10, notes 129-160
  A3, C4, E4, G4, C5, E4, G4, C5,
  D3, A3, D4, FS4, C5, D4, FS4, C5,
  D3, A3, D4, FS4, C5, D4, FS4, C5,

  G3, B3, D4, G4, B4, D4, G4, B4, //measures 11-12, notes 161-192
  G3, B3, D4, G4, B4, D4, G4, B4,
  G3, AS3, E4, G4, CS5, E4, G4, CS5,
  G3, AS3, E4, G4, CS5, E4, G4, CS5,
  F3, A3, D4, A4, D5, D4, A4, D5, //measures 13-14, notes 193-224
  F3, A3, D4, A4, D5, D4, A4, D5,
  F3, GS3, D4, F4, B4, D4, F4, B4,
  F3, GS3, D4, F4, B4, D4, F4, B4,

  E3, G3, C4, G4, C5, C4, G4, C5, //measures 15-16, notes 225-256
  E3, G3, C4, G4, C5, C4, G4, C5,
  E3, F3, A3, C4, F4, A3, C4, F4,
  E3, F3, A3, C4, F4, A3, C4, F4,

  D3, F3, A3, C4, F4, A3, C4, F4, //measures 17-18, notes 257-288
  D3, F3, A3, C4, F4, A3, C4, F4,
  G2, D3, G3, B3, F4, G3, B3, F4,
  G2, D3, G3, B3, F4, G3, B3, F4,
  C3, E3, G3, C4, E4, G3, C4, E4, //measures 19-20, notes 289-320
  C3, E3, G3, C4, E4, G3, C4, E4,
  C3, G3, AS3, C4, E4, AS3, C4, E4,
  C3, G3, AS3, C4, E4, AS3, C4, E4,
  F2, F3, A3, C4, E4, A3, C4, E4, //measures 21-22, notes 321-352
  F2, F3, A3, C4, E4, A3, C4, E4,
  FS2, C3, A3, C4, DS4, A3, C4, DS4,
  FS2, C3, A3, C4, DS4, A3, C4, DS4,
  GS2, F3, B3, C4, D4, B3, C4, D4, //measures 23-24, notes 353-384
  GS2, F3, B3, C4, D4, B3, C4, D4,
  G2, F3, G3, B3, D4, G3, B3, D4,
  G2, F3, G3, B3, D4, G3, B3, D4,

  G2, E3, G3, C4, E4, G3, C4, E4, //meaures 25-26, notes 385-416
  G2, E3, G3, C4, E4, G3, C4, E4,
  G2, D3, G3, C4, F4, G3, C4, F4,
  G2, D3, G3, C4, F4, G3, C4, F4,
  G2, D3, G3, B3, F4, G3, B3, F4, //measures 27-28, notes 417-448
  G2, D3, G3, B3, F4, G3, B3, F4,
  G2, DS3, A3, C4, FS4, A3, C4, FS4,
  G2, DS3, A3, C4, FS4, A3, C4, FS4,
  G2, E3, G3, C4, G4, G3, C4, G4, //measures 29-30, notes 449-480
  G2, E3, G3, C4, G4, G3, C4, G4,
  G2, F3, G3, C4, F4, G3, C4, F4,
  G2, F3, G3, C4, F4, G3, C4, F4,
  G2, F3, G3, B3, F4, G3, B3, F4, //measures 31-32, notes 481-512
  G2, F3, G3, B3, F4, G3, B3, F4,
  C2, C3, G3, AS3, E4, G3, AS3, E4,
  C2, C3, G3, AS3, E4, G3, AS3, E4,
  C2, C3, F3, A3, C4, F4, C4, A3, //measures 33-34, notes 513-544
  C4, A3, F3, A3, F3, D3, F3, D3,
  C2, B2, G4, B4, D5, F5, D5, B4,
  D5, B4, G4, B4, D4, F4, E4, D4,
};

// the 'volatile' variable qualifier directs the compiler to load the unsigned 32-bit integer from RAM (not from a storage register)
volatile uint32_t toggle_count;

void setup(){
  pinMode(1, OUTPUT); // enable OUTPUT (PB1, #1)
  PlayBach(); // Music!
  pinMode(1, INPUT); // disable OUTPUT
}

void loop(){
  // only play once from setup
}


// TrinketTone:
// Generate a square wave on a given frequency & duration
// Call with frequency (in hertz) and duration (in milliseconds).
// Uses Timer1 in CTC mode (“Clear on Timer Compare Match" mode).
// Generated tone is non-blocking,
// so routine immediately returns while tone is playing.

void TrinketTone(uint16_t frequency, uint32_t duration){
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
  // Duration will be tracked by timer1 ISR
  toggle_count = frequency * duration / 500;
  OCR1C = ocr - 1; // Set the OCR
  bitWrite(TIMSK, OCIE1A, 1); // enable interrupt
}

// Timer1 Interrupt Service Routine:
// Keeps track of note duration via toggle counter
// When correct time has elapsed, counter is disabled

ISR(TIMER1_COMPA_vect){
  if (toggle_count != 0) // done yet?
    toggle_count--; // no, keep counting
  else // yes,
    TCCR1 = 0x90; // stop the counter
}

// PlayBach:
// Plays "Prelude in C", which is held in noteArray
// Uses PROGMEM to store array, due to large size

void PlayBach(){
  int len = 150; // modify for speed
  int dly = 190; // modify for articulation
  for (int count = 0; count < NOTECOUNT; count++){
    TrinketTone( pgm_read_word( &noteArray[count] ), len);
    delay(dly);
    // slow down (rit.) at end.
    if ((count > 512) and (count < 540)) {
      len += 3;
      dly += 5;
    }
  }
  TrinketTone(C4, 1500); // final note
  delay(1500);
}
