#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


#include "fsr.hpp"
#include "piezo.hpp"
#include "joySwitch.hpp"

// Pin definitions
#define PITCHUPPIN 12
#define PITCHDOWNPIN 11
#define RATEUPPIN 10
#define RATEDOWNPIN 9
#define FSRPIN A2
#define PIEZO1PIN A3
#define PIEZO2PIN A4

joySwitch pitchUp(PITCHUPPIN);
joySwitch pitchDown(PITCHDOWNPIN);
joySwitch rateUp(RATEUPPIN);
joySwitch rateDown(RATEDOWNPIN);

piezo chord1(PIEZO1PIN);
piezo chord2(PIEZO2PIN);

// Pitch state variables
uint8_t chord1Pitch;
uint8_t chord2Pitch;

// Midi Parameters
uint8_t pitch = 64;
uint8_t rate = 64;

fsr noteTrigger(FSRPIN);
bool noteState = false;

unsigned int counter = 0;

struct MySettings : public midi::DefaultSettings
{
  static const long BaudRate = 115200;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);



void setup() {
  MIDI.begin();

  pinMode(13, OUTPUT);
  pinMode(PITCHUPPIN, INPUT_PULLUP);
  pinMode(PITCHDOWNPIN, INPUT_PULLUP);
  pinMode(RATEUPPIN, INPUT_PULLUP);
  pinMode(RATEDOWNPIN, INPUT_PULLUP);
}

void loop() {
  // Force Sensitive Resistor Checking
  if ( noteTrigger.next() == 1 )
  {
    MIDI.sendNoteOn( pitch, 64, 1);
    noteState = true;
  }
  else if ( noteTrigger.next() == 2)
  {
    MIDI.sendNoteOff(pitch, 64, 1);
    noteState = false;
  }

  // Check for pitch up message
  if (pitchUp.next())
  {
    if (pitch >= 127)
    {
      pitch = 0;
    }
    else
    {
      pitch++;
    }
    MIDI.sendControlChange(10, pitch, 1);
    if (noteState)
    {
      MIDI.sendNoteOff(pitch - 1, 64, 1);
      MIDI.sendNoteOn( pitch, 64, 1);
    }
  }

  // Check for pitch down message
  if (pitchDown.next())
  {
    if (pitch <= 0)
    {
      pitch = 127;
    }
    else
    {
      pitch--;
    }
    MIDI.sendControlChange(10, pitch, 1);
    if (noteState)
    {
      MIDI.sendNoteOff(pitch + 1, 64, 1);
      MIDI.sendNoteOn( pitch, 64, 1);
    }
  }

  // Check for rate up message
  if (rateUp.next())
  {
    if (rate >= 127)
    {
      rate = 0;
    }
    else
    {
      rate += 5;
    }
    MIDI.sendControlChange(11, rate, 1);
  }

  // Check for rate down message
  if (rateDown.next())
  {
    if (rate <= 0)
    {
      rate = 127;
    }
    else
    {
      rate -= 5;
    }
    MIDI.sendControlChange(11, rate, 1);
  }

  // Check piezo
  if (chord1.next() == 1)
  {
    MIDI.sendNoteOn(pitch, 70, 2);
    chord1Pitch = pitch;
  }
  else if( chord1.next() == 2)
  {
    MIDI.sendNoteOff(chord1Pitch, 70, 2);
  }

  // Check piezo
  if (chord2.next() == 1)
  {
    MIDI.sendNoteOn(pitch - 12, 70, 2);
    chord2Pitch = pitch - 12;
  }
  else if( chord2.next() == 2)
  {
    MIDI.sendNoteOff(chord2Pitch, 70, 2);
  }  
}
