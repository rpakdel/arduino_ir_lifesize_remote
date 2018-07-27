#include <IRremote.h>
#include "lifesize-buttons.h"

#define RECEIVER_PIN 6
IRrecv irrecv(RECEIVER_PIN);

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn();
    Serial.println("Press a button");
}

void printButton(Button button)
{
    int buttonIndex = (int)button;
    Serial.print(buttonLabel[buttonIndex]);
}

void printlnButton(Button button)
{
    int buttonIndex = (int)button;
    Serial.println(buttonLabel[buttonIndex]);
}

Button getButton(unsigned int code)
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (code == codes1[i] || code == codes2[i])
        {
            return Button(i);
        }
    }
    return Undefined;
}

unsigned int decodeIR(decode_results *results)
{
    byte result[16];

    for (int k = 0; k < 16; k++)
    {
        result[k] = 0;
    }

    if (results->rawlen != 36)
    {
        //Serial.print("Wrong number of pulses");
        //Serial.println(results->rawlen);
        return (int)codes1[Invalid];
    }


    int bit_index = 0;

    // pulse 0 is time since last pulse
    // pulse 1 and 2 are start
    // last pulse is stop
    // we only look at even pulses
    int len = results->rawlen - 1;
    for (int i = 3; i < len; i = i + 2)
    {
        // current pulse
        unsigned long  x = results->rawbuf[i] * USECPERTICK;
        // next pulse
        unsigned long  n = results->rawbuf[i + 1] * USECPERTICK;

        // print timing
        //Serial.print(x);
        //Serial.print("-");
        //Serial.println(n);
        if (x >= 1000 && x <= 2000)
        {
            // low, check next pulse
            if (n >= 2000 && n < 3000)
            {
                // next pulse is long, got a 1
                result[bit_index] = 1;
            }
            else if (n < 1000)
            {
                result[bit_index] = 0;
            }
        }
        bit_index++;
    }

    unsigned int value = 0;
    for (int j = 0; j < 16; j++)
    {
        // print value in binary
        // Serial.print(result[j]);
        value |= result[j] << (15 - j);
    }
    //Serial.println();
    //Serial.println(value, HEX);
    return value;
}

void  loop()
{
    decode_results results;
    if (irrecv.decode(&results))
    {
        unsigned int code = decodeIR(&results);
        Serial.print(code, HEX);
        Serial.print(" -> ");
        Button button = getButton(code);
        //Serial.println(button);
        printlnButton(button);
        irrecv.resume();
    }
}
