#include <Wire.h>
#include <Adafruit_AMG88xx.h>

// Create the sensor object
Adafruit_AMG88xx amg;

// Create an array to hold the 64 temperature readings
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
  // Start the serial connection at the high speed the website needs
  Serial.begin(115200);
  
  // Give the serial connection a second to start up
  delay(1000); 

  Serial.println("Starting up the AMG8833 Thermal Sensor...");

  // Try to connect to the sensor (using the default address)
  bool status = amg.begin();
  if (!status) {
    Serial.println("Error: Could not find the AMG8833 sensor! Check your wiring.");
    while (1); // Freeze the code here if the sensor isn't found
  }
  
  Serial.println("Sensor found! Starting to read temperatures...");
  delay(50); // Short pause before starting the loop
}

void loop() {
  // Read all 64 pixels from the sensor and store them in the 'pixels' array
  amg.readPixels(pixels);

  // Loop through all 64 pixels and print them to the Serial port
  for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    
    // Print the temperature of the current pixel (in Celsius)
    Serial.print(pixels[i-1]);
    Serial.print(", ");
    
    // Create a new line every 8 pixels so it looks like an 8x8 grid on your screen
    if( i % 8 == 0 ) {
      Serial.println();
    }
  }
  
  // Print the specific separator the website needs to finish the frame
  Serial.println("---");

  // Wait 50 milliseconds before taking the next picture for high framerate
  delay(50);
}