#include <IRremote.h>

#define IR_PIN 6
IRrecv irrecv(IR_PIN);

void setup()
{
	Serial.begin(9600);   // Status message will be sent to PC at 9600 baud
	irrecv.enableIRIn();  // Start the receiver
}

void printIRButton(decode_results& irresults)
{
	Serial.println(irresults.value, HEX);
}

void loop()
{
	decode_results irresults;
	if (irrecv.decode(&irresults))
	{
		printIRButton(irresults);
		irrecv.resume();
	}

}
