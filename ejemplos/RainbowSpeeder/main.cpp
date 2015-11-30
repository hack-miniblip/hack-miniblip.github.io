
#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define ANALOG_POTENTIOMETER P0_22
AnalogIn   ain(ANALOG_POTENTIOMETER);


void generate(neopixel::Pixel * out, uint32_t index, uintptr_t extra)
{
    uint32_t brightness = (index + extra) >> 3;
    out->red   = ((index + extra) & 0x1) ? brightness : 0;
    out->green = ((index + extra) & 0x2) ? brightness : 0;
    out->blue  = ((index + extra) & 0x4) ? brightness : 0;
}

int main()
{
    // Turn off miniblip buzzer
    PwmOut speaker(P0_8);
    speaker=0.0;
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);

    uint32_t offset = 0;
    uint32_t i = 1;
    while (1) {
        array.update(generate, 64, offset++);

        //Play Sound
        float note=500+(i*100);
        speaker.period(1.0/note);
        speaker = float(i)/50.0;

        i++;
        if (i>10) i=1;
        // Rainbow delay
        float pot = ain.read();
        wait_ms(100*pot);
    }
}
