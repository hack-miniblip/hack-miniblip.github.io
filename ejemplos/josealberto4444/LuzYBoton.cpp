// miniblip led matrix demo
/* La intensidad de la luz varía y cambia el led que se enciende
 * cuando se pulsa el botón.*/


#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define NLEDS 25
AnalogIn potenc(P0_22);
AnalogIn luz(P0_16);
DigitalIn boton(P0_23);
PwmOut speaker(P0_8);

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
    int i=4;
    while (true) {
        
        //for (int i = 0; i<NLEDS; i++) {
            int intensidad = floor(luz.read()*30);
            if (boton.read() == 1) {
                i = (i + 1)%25;
                wait_ms(100);
            }
            setPixel(i, intensidad, intensidad, intensidad);
            for (int j = 0; j<NLEDS; j++) {
                if (j != i) {
                    setPixel(j, 0, 0, 0);
                    wait_ms(1);
                }
            }
            wait_ms(1);
        //}
        array.update(buffer, NLEDS);
    }
}
