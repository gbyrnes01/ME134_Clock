#include <Arduino.h>
#include <AccelStepper.h>
#include <WiFi.h>
#include <time.h>

// const char* ssid = "Tufts_Robot";
// const char* pass = "";

// // NTP server details
// const char* ntpServer = "pool.ntp.org";

// // Eastern Time Zone (UTC - 5 hours, or UTC - 4 hours during Daylight Saving Time)
// const long  gmtOffset_sec = -5 * 3600;    // GMT offset in seconds
// const int   daylightOffset_sec = 3600;    // Daylight saving time offset in seconds
const unsigned long  mircosToMin = 1000 * 1000 * 60;

// Define pin connections
const int stepPin = 4;
const int dirPin = 0; 
const int buttonPin = 22;

// Misc Constants
const unsigned long minToSteps = 20;
const unsigned long hourToSteps = minToSteps * 60;

bool button = false;
unsigned long currentStepperPosition = 0;

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);


// void initTime() {
//   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//   Serial.println("Time synchronized with NTP server.");
// }

// tm LocalTime() {
//   struct tm timeinfo;
//   if (!getLocalTime(&timeinfo)) {
//     Serial.println("Failed to obtain time");
//     return timeinfo;
//   }
  
//   // Print formatted time
//   Serial.println(&timeinfo, "Current local time: %A, %B %d %Y %H:%M:%S");
//   return timeinfo;
// }

// void setupClock(tm time) {
//   int hours = time.tm_hour;
//   int mins = time.tm_min;
//   if (hours > 12) {
//     hours = hours - 12;
//   }
//   unsigned long stepsToGo = (hours * hourToSteps) + (mins * minToSteps);
//   stepper.runToNewPosition(stepsToGo);
//   currentStepperPosition += stepsToGo;
// }


void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.println("Starting");

  // //Setup Wifi
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid);

  // Serial.println("Wifi");
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.print('.');
  //   delay(1000);
  // }
  // Serial.println(WiFi.localIP());

  // //Setup Time
  // initTime();

  //Setup Stepper
  Serial.println("Stepper Setup");
  stepper.setMaxSpeed(1000);  // Max steps per second
  stepper.setAcceleration(500);  // Steps per second^2

  Serial.println("Time Vars");
  unsigned long currentMircos = micros();
  unsigned long deltaTime = mircosToMin;

  Serial.println("Clock Setup");
  //setupClock(LocalTime());


  while (true) {
    if ((micros() - currentMircos) > deltaTime) {
      currentMircos = currentMircos + deltaTime;
      if (digitalRead(button)) {
        deltaTime = mircosToMin / 10;
      }
      else {
        deltaTime = mircosToMin;
      }
      stepper.move(minToSteps);
      currentStepperPosition =+ minToSteps;
    }
    stepper.run();
  }
}

void loop() {
  //nothing
}

