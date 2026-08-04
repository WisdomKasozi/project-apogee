// Project Apogee — Flight Computer
// Hardened Passive Telemetry Logger (Tare Calibration Method)
// Sensors: BMP388 (I2C), MPU-6050 (I2C), MicroSD (SPI)

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_MPU6050.h>

const int chipSelect = 4; // Verify if your CS is 4 or 10

Adafruit_BMP3XX bmp;
Adafruit_MPU6050 mpu;
File dataFile;

unsigned long startTime;
unsigned long lastFlushTime = 0;
float groundOffset = 0; // This will hold your exact desk height token

void setup() {
  Serial.begin(115200); 
  
  Wire.begin();
  Wire.setClock(400000); 
  
  if (!bmp.begin_I2C()) { while (1); }
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  
  if (!mpu.begin()) { while (1); }
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G); 
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  if (!SD.begin(chipSelect)) { while (1); }
  
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(F("time_ms,relative_alt_m,accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z"));
  } else {
    while (1);
  }
  
  // Warm up and let the sensor stabilize
  delay(1000); 
  
  // TARE CALIBRATION: Average 20 raw readings for a bulletproof baseline
  float totalAltitude = 0;
  int validReadings = 0;
  
  while (validReadings < 20) {
    if (bmp.performReading()) {
      totalAltitude += bmp.readAltitude(1013.25); // Get raw altitude calculation
      validReadings++;
      delay(30);
    }
  }
  groundOffset = totalAltitude / 20.0; // Lock in your exact desk baseline
  
  startTime = millis();
}

void loop() {
  if (!bmp.performReading()) { return; }
  
  // Get raw altitude and subtract the baseline to force a perfect 0.00
  float rawAltitude = bmp.readAltitude(1013.25);
  float relativeAltitude = rawAltitude - groundOffset;
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  unsigned long timestamp = millis() - startTime;
  
  // Log directly to SD card
  dataFile.print(timestamp);           dataFile.print(',');
  dataFile.print(relativeAltitude, 2); dataFile.print(','); 
  dataFile.print(a.acceleration.x, 2); dataFile.print(',');
  dataFile.print(a.acceleration.y, 2); dataFile.print(',');
  dataFile.print(a.acceleration.z, 2); dataFile.print(',');
  dataFile.print(g.gyro.x, 2);         dataFile.print(',');
  dataFile.print(g.gyro.y, 2);         dataFile.print(',');
  dataFile.println(g.gyro.z, 2);
  
  if (millis() - lastFlushTime >= 500) {
    dataFile.flush();
    lastFlushTime = millis();
  }
  
  // Monitor relative altitude locally
  Serial.print(timestamp); 
  Serial.print(F(" | Relative Alt: ")); 
  Serial.print(relativeAltitude, 2);
  Serial.print(F("m | AccelZ: "));
  Serial.println(a.acceleration.z, 2);
  
  delay(20); 
}