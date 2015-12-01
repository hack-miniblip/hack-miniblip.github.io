// miniblip led matrix demo
/* Este programa enciende un led u otro moviendo el potenciómetro, 
 * y se enciende rojo, verde o azul según la luz que le llegue a 
 * la célula fotovoltaica. */



#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define NLEDS 25
AnalogIn ain(P0_22);
AnalogIn luz(P0_16);

void generate(neopixel::Pixel * out, uint32_t index, uintptr_t extra)
{
    uint32_t brightness = (index + extra) >> 3;
    out->red   = ((index + extra) & 0x1) ? brightness : 0;
    out->green = ((index + extra) & 0x2) ? brightness : 0;
    out->blue  = ((index + extra) & 0x4) ? brightness : 0;
}

neopixel::PixelArray array(DATA_PIN);
neopixel::Pixel buffer[NLEDS];

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

int main() {
    while (true) {
        int nled = floor(ain.read()*25);
        
        if (luz > 0.8) setPixel(nled, 0, 0, 30);
        else if (luz > 0.5) setPixel(nled, 30, 0, 0);
        else  setPixel(nled, 0, 30, 0);
        
        for (int i = 0; i<NLEDS; i++) {
            if (i != nled) {
                setPixel(i, 0, 0, 0);
                wait_ms(1);
            }
        }
        wait_ms(10);
        array.update(buffer, NLEDS);
    }
/*    for (int i=0; i<NLEDS; i++) {
        setPixel(i, 0, 255, 0);
        wait_ms(10);
        }
    array.update(buffer, NLEDS);
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
        //speaker.period(1.0/note);           
        //speaker = float(i)/50.0;
        
        i++;
        if (i>10) i=1;
        // Rainbow delay
        wait_ms(100);
    }*/
}
