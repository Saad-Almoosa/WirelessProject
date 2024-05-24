#include<SoftwareSerial.h>
/* Create object named My_Bluetooth of the class SoftwareSerial */
SoftwareSerial My_Bluetooth(4, 5); /* (Rx,Tx) */

#define IR_Pin         9   // define pin 4 for the IR Sensor
#define Red_LED        10  // define pin 5 for the Red LED
#define Yellow_LED     11  // define pin 6 for the Yellow LED
#define Green_LED      12  // define pin 7 for the Green LED
#define Buzzer         3   // define pin 8 for the Buzzer

bool Mode = 0;    // 0 : Auto, 1 : Manual
char Order = 'A'; // R:Red, G:Green, Y:Yellow, A: Auto Mode

void setup()
{
  pinMode(IR_Pin, INPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  
  digitalWrite(Red_LED, LOW);    // Red is OFF
  digitalWrite(Yellow_LED, LOW); // Yellow is OFF
  digitalWrite(Green_LED, LOW);  // Green is OFF
  noTone(Buzzer);                // Buzzer is OFF
  
  /* Define baud rate for software serial communication */
  My_Bluetooth.begin(9600);
  /* Define baud rate for serial communication */
  Serial.begin(9600);
  delay(500);
  Serial.println("\nWelcome!");
}

void loop()
{
  /* If data is available on serial port */
  if (My_Bluetooth.available())
  {
    Order = My_Bluetooth.read();
    Serial.print("input is: ");
    Serial.println(Order);
    
    if (Order == 'A')
    {
      Mode = 0;   // Switch to Auto Mode.
    }
    else if ((Order == 'R') || (Order == 'G') || (Order == 'Y'))
    {
      Mode = 1;   // Switch to Manual Mode.
    }
  }

  Serial.print("Mode is: ");
  Serial.println(Mode);
  // Check Mode
  if (Mode == 0) // Auto Mode
  {
    // Check IR sensor 
    if (digitalRead(IR_Pin) == LOW)  // Car is Detected
    {
      Serial.println("IR is ON!");
      digitalWrite(Green_LED, HIGH); // Green is ON
      digitalWrite(Red_LED, LOW);    // Red is OFF
      digitalWrite(Yellow_LED, LOW); // Yellow is OFF
      tone(Buzzer, 1000);            // Buzzer is ON
      while (digitalRead(IR_Pin) == LOW)  // while Car is Detected
      {
        delay(100);
      }

      delay(3000);                   // Wait for 7 Seconds
      digitalWrite(Yellow_LED, HIGH);// Yellow is ON
      digitalWrite(Red_LED, LOW);    // Red is OFF
      digitalWrite(Green_LED, LOW);  // Green is OFF
      noTone(Buzzer);                // Buzzer is OFF
      delay(1000);                   // Wait for 3 Seconds
      
      digitalWrite(Red_LED, HIGH);   // Red is ON
      digitalWrite(Yellow_LED, LOW); // Yellow is OFF
      digitalWrite(Green_LED, LOW);  // Green is OFF
      noTone(Buzzer);                // Buzzer is OFF
    }
    else // No Car is Detected
    {
      Serial.println("IR is OFF!");
      digitalWrite(Red_LED, HIGH);   // Red is ON
      digitalWrite(Yellow_LED, LOW); // Yellow is OFF
      digitalWrite(Green_LED, LOW);  // Green is OFF
      noTone(Buzzer);                // Buzzer is OFF
    }
  }
  else // Manual Mode
  {
    if (Order == 'R') // Red is ON
    {
      digitalWrite(Red_LED, HIGH);   // Red is ON
      digitalWrite(Yellow_LED, LOW); // Yellow is OFF
      digitalWrite(Green_LED, LOW);  // Green is OFF
      noTone(Buzzer);                // Buzzer is OFF
    }
    else if (Order == 'G') // Green is ON
    {
      digitalWrite(Green_LED, HIGH); // Green is ON
      digitalWrite(Red_LED, LOW);    // Red is OFF
      digitalWrite(Yellow_LED, LOW); // Yellow is OFF
      tone(Buzzer, 1000);            // Buzzer is ON
    }
    else if (Order == 'Y') // Yellow is ON
    {
      digitalWrite(Yellow_LED, HIGH);// Yellow is ON
      digitalWrite(Red_LED, LOW);    // Red is OFF
      digitalWrite(Green_LED, LOW);  // Green is OFF
      noTone(Buzzer);                // Buzzer is OFF
    }
  }
  delay(500);
}