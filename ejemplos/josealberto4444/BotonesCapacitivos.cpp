// miniblip led matrix demo

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define NLEDS 25
AnalogIn potenc(P0_22);
AnalogIn luz(P0_16);
AnalogIn arriba(P0_14);
AnalogIn abajo(P0_12);
AnalogIn izquierda(P0_13);
AnalogIn derecha(P0_11);
DigitalIn boton(P0_23);

neopixel::PixelArray array(DATA_PIN);
neopixel::Pixel buffer[NLEDS];

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

int main() {
    int i=12;
    while (true) {
        int intensidad = floor(luz.read()*30);
        /*if (arriba.read() > 0.5) {
            i = (i + 5)%25;
            wait_ms(200);
        }
        if (abajo.read() > 0.5) {
            i = (i - 5)%25;
            wait_ms(200);
        }
        if (izquierda.read() > 0.5) {
            i = (i - 1)%25;
            wait_ms(200);
        }
        if (arriba.read() > 0.5) {
            i = (i + 5)%25;
            wait_ms(200);
        }*/
        setPixel(i, intensidad, intensidad, intensidad);
        for (int j = 0; j<NLEDS; j++) {
            if (j != i) {
                setPixel(j, 0, 0, 0);
                wait_ms(1);
            }
        }
        wait_ms(1);
        array.update(buffer, NLEDS);
    }
}
