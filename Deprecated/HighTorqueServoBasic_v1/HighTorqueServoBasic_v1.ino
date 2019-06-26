   
// Include Libraries
#include "Arduino.h"
#include "Servo.h"


// Pin Definitions
#define SERVOMD_PIN_SIG  2


// object initialization
Servo servoMD;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    servoMD.attach(SERVOMD_PIN_SIG);
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    for(int i=0;i<180;i++){
    delay(5);                             
    servoMD.write(i);                      
    }

    for(int i=180;i>0;i--){
    delay(5);                              // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoMD.write(i);    // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.                              // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.                 // 6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    
    
}
