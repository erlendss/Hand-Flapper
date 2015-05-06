/*
 * Firmata is a generic protocol for communicating with microcontrollers
 * from software on a host computer. It is intended to work with
 * any host computer software package.
 *
 * To download a host software package, please clink on the following link
 * to open the download page in your default browser.
 *
 * http://firmata.org/wiki/Download
 */

/* Supports as many analog inputs and analog PWM outputs as possible.
 *
 * This example code is in the public domain.
 */
#include <Firmata.h>
#include <Tone.h>
Tone tone1;
Tone tone2;

//høytaler og fotocelle 1
byte analogPin1 = 0;
int photocellPin1 = 0;
int speakerA = 9;

//høytaler og fotocelle 2
byte analogPin2 = 1;
int photocellPin2 = 1;
int speakerB = 11;
 


void analogWriteCallback(byte pin, int value)
{
  if (IS_PIN_PWM(pin)) {
    pinMode(PIN_TO_DIGITAL(pin), OUTPUT);
    analogWrite(PIN_TO_PWM(pin), value);
  }
}

void setup()
{
  Firmata.setFirmwareVersion(0, 1);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.begin(57600);
  tone1.begin(speakerA);
  tone2.begin(speakerB);
}

void loop()
{
  while (Firmata.available()) {
    Firmata.processInput();
  }
  // do one analogRead per loop, so if PC is sending a lot of
  // analog write messages, we will only delay 1 analogRead
  Firmata.sendAnalog(analogPin1, analogRead(analogPin1));
  Firmata.sendAnalog(analogPin2, analogRead(analogPin2));
  analogPin1 = analogPin1 + 1;
  if (analogPin1 >= TOTAL_ANALOG_PINS) analogPin1 = 0;
    analogPin2 = analogPin2 + 1;
  if (analogPin2 >= TOTAL_ANALOG_PINS) analogPin2 = 0;
  
  int reading1 = analogRead(photocellPin1);
  int reading2 = analogRead(photocellPin2);
  
  
  int pitch1 = 250 + reading1 / 4;
  int pitch2 = 250 + reading2 / 4;
  
tone1.play(pitch2);
tone2.play(pitch1);

}

