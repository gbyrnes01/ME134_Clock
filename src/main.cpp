#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

const char* ssid = "50BostonAve";
const char* pass = "5715500301";

// NTP server details
const char* ntpServer = "pool.ntp.org";

// Eastern Time Zone (UTC - 5 hours, or UTC - 4 hours during Daylight Saving Time)
const long  gmtOffset_sec = -5 * 3600;    // GMT offset in seconds
const int   daylightOffset_sec = 3600;    // Daylight saving time offset in seconds

const int clockwise_sequence[4][4] = {{HIGH, LOW, HIGH, LOW},
                                {LOW, HIGH, HIGH, LOW},
                                {LOW, HIGH, LOW, HIGH},
                                {HIGH, LOW, LOW, HIGH}};

const int counterclockwise_sequence[4][4] = { {HIGH, LOW, LOW, HIGH},
                                        {LOW, HIGH, LOW, HIGH},
                                        {LOW, HIGH, HIGH, LOW},
                                        {HIGH, LOW, HIGH, LOW}};

int spinPhase = 0;
int spinDelayMS = 10;
const int stepperPins[4] = {3,4,5,6};


void initTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Time synchronized with NTP server.");
}

tm* LocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  
  // Print formatted time
  Serial.println(&timeinfo, "Current local time: %A, %B %d %Y %H:%M:%S");
  return &timeinfo;
}

void spin(int cycles) {
  for (int i = 0; i < cycles; i++) {
    digitalWrite(stepperPins[0], clockwise_sequence[spinPhase][0]);
    digitalWrite(stepperPins[1], clockwise_sequence[spinPhase][1]);
    digitalWrite(stepperPins[2], clockwise_sequence[spinPhase][2]);
    digitalWrite(stepperPins[3], clockwise_sequence[spinPhase][3]);
    delay(spinDelayMS);

    spinPhase++;
    if (spinPhase == 4) {
      spinPhase = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.println("hello");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  initTime();
}

void loop() {
  
  LocalTime();
  delay(1000);
  
}

