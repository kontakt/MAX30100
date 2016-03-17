#include "MAX30100.h"  
#include <Wire.h>

MAX30100 sensor;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  sensor.begin(pw1600, i4, sr100 );
}

void loop() {
  sensor.readSensor();  
  Serial.println(runningAverage(sensor.HR));
  delay(10);
}

long runningAverage(int M) {
  #define LM_SIZE 15
  static int LM[LM_SIZE];      // LastMeasurements
  static byte index = 0;
  static long sum = 0;
  static byte count = 0;

  // keep sum updated to improve speed.
  sum -= LM[index];
  LM[index] = M;
  sum += LM[index];
  index++;
  index = index % LM_SIZE;
  if (count < LM_SIZE) count++;

  return sum / count;
}
