#include "Wire.h"
#include "NewPing.h"


// Ultrasonic Sensor Pin define
#define _PIN_ULTRASONIC_VCC    4
#define _PIN_ULTRASONIC_TRIGGER   7
#define _PIN_ULTRASONIC_ECHO    6


#define _PIN_PWM_SIGNAL    11 // Aux output


// Maximum Distance is ?? cm
#define _MAX_DISTANCE  300 // cm


NewPing oultrasonicSensor(_PIN_ULTRASONIC_TRIGGER, _PIN_ULTRASONIC_ECHO, _MAX_DISTANCE);
uint16_t un16distance;


#define _PIN_ARDUINO_LED    13  // embeded  LED  Port on Arduino Pro

#define  _ULTRASONIC_HZ   10  // 1~10 Hz



void setup()
{
 Serial.begin(9600);

 pinMode(_PIN_ULTRASONIC_VCC, OUTPUT);
 digitalWrite(_PIN_ULTRASONIC_VCC, HIGH);  // Ultrasonic VCC

 pinMode(_PIN_PWM_SIGNAL, OUTPUT);
 
 pinMode(_PIN_ARDUINO_LED, OUTPUT);

}


void loop()
{
 un16distance = oultrasonicSensor.ping_cm();   // Get Distince

 Serial.print("Distince: "); Serial.print(un16distance); Serial.println("cm"); // Print

 SendPwmSignal(); // Send PWM to Pixhawk Aux

 delay(1000/ _ULTRASONIC_HZ);

}


void SendPwmSignal()
{
 bool bLED = false;

 digitalWrite(_PIN_PWM_SIGNAL, HIGH);
 delayMicroseconds(un16distance * 10);
 digitalWrite(_PIN_PWM_SIGNAL, LOW);
}
