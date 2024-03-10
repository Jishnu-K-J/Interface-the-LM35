#include<TimerOne.h>              // library for timer1
#define Led_pin 13                // Onboard Led pin 
#define Lm35_pin A0                 // Analog pin for Lm35 temperature sensor

unsigned long interval_1 = 250000;     // interval for blinking led in 250 milliseconds
unsigned long interval_2 = 500000;     // interval for blinking led in 500 milliseconds
bool led_state = 0;                 // variable to led state
float temperature;                // variable to store temperature

void setup() 
{
  pinMode(Led_pin, OUTPUT);     // Set the Led pin as an output
  pinMode(Lm35_pin, INPUT);     // Set the LM35 pin as an input
  Timer1.initialize(interval_1);     // Initialize Timer1 for interval_1(250 milliseconds)
  Timer1.attachInterrupt(timer_isr);      // Attach the interrupt service routine
  Serial.begin(9600);                   // to begin the serial monitor
}

void loop() 
{
  int temp_adc_val;                         // variable to store sensor value
  temp_adc_val = analogRead(Lm35_pin);            // Reading the value from lm35 sensor
  temperature = (temp_adc_val * (5.0 / 1024.0));      // Convert the analog value into voltage
  temperature = temperature * 100.0;               // Convert the voltage into temperature
  toggle_interval();                            // function for setting the timer1 interval
  
  // Print the temperature in serial monitor
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
}

void timer_isr()        // function for led blinking
{
  led_state = !led_state;             // Toggle the led_state
  digitalWrite(Led_pin,led_state);      // Toggle the state of the LED
}

void toggle_interval()      // function for setting the timer1 interval
{
  if (temperature < 30)
  {
    Timer1.setPeriod(interval_1);      // setting the timer1 interval to interval_1(250 milliseconds)
  } 
  else 
  {
    Timer1.setPeriod(interval_2);      // setting the timer1 interval to interval_2(500 milliseconds)
  }
}
