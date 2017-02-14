#include <toneAC.h>

//www.elegoo.com
//2016.06.13

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

int lastSound = 0;
int zeroCount = 0;
int tonePlayed = 0;

void loop() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  int therReading = uS / US_ROUNDTRIP_CM;
  int toneMax = 4937;
  int toneMin = 31;
  unsigned long toneFinal = 0;
  if(therReading > 8 && therReading < 56)
    {
      if(therReading < 12) {
        toneFinal =  1047;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 16) {
        toneFinal =  988;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 20) {
        toneFinal =  880;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 24) {
        toneFinal =  784;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 32) {
        toneFinal =  698;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 40) {
        toneFinal =  659;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 48) {
        toneFinal =  587;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
      else if(therReading < 56) {
        toneFinal =  523;
        lastSound =  toneFinal;
        playTone(toneFinal);
        return;
      }
    }
    else {
      if(zeroCount == 20) {
          zeroCount = 0;
          lastSound = 0;
          playTone(0);
        }
       else {
          lastSound = lastSound;
          zeroCount ++;
          playTone(lastSound);
        }
      
      }
  
}

void playTone(int value) {
  if(tonePlayed != value) {
      toneAC(0);
      delay(13);
    }
  Serial.println(value); 
  toneAC(value);
  tonePlayed = value;
  delay(29);
  //toneAC(0);
  //delay(7);
}

void loopOld() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  int therReading = uS / US_ROUNDTRIP_CM;
  int toneMax = 4937;
  int toneMin = 31;
  unsigned long toneFinal = 0;
  if(therReading != 0)
    {
      toneFinal =  toneMax /  therReading;
      if(toneFinal < toneMin) {
        toneFinal = toneMin;
        lastSound = toneFinal;
        }
    }
    else {
      if(zeroCount == 40) {
          zeroCount = 0;
          toneFinal = 0;
        }
       else {
          toneFinal = lastSound;
          zeroCount ++;
        }
      
      }
  Serial.println(toneFinal); 
  toneAC(toneFinal);
  delay(66);
  toneAC(0);
  delay(9);
}
