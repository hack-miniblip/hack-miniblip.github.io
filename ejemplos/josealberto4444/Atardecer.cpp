// miniblip led matrix demo
/* Según el sensor de luminosidad, aparecen distintos soles 
 * y distintas lunas, como si atardeciera.*/

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define NLEDS 25
AnalogIn potenc(P0_22);
AnalogIn luz(P0_16);
DigitalIn boton(P0_23);
PwmOut speaker(P0_8);

neopixel::PixelArray array(DATA_PIN);
neopixel::Pixel buffer[NLEDS];

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

void sol2() {
    int encendidos[17] = {0,2,4,6,7,8,10,11,12,13,14,16,17,18,20,22,24};
    int apagados[8] = {1,3,5,9,15,19,21,23};
    for (int i=0; i<17; i++) {
        setPixel(encendidos[i], 30, 30, 0);
        wait_ms(1);
    }
    for (int i=0; i<8; i++) {
        setPixel(apagados[i], 0, 0, 0);
        wait_ms(1);
    }
    array.update(buffer, NLEDS);
}

void sol1() {
    int encendidos[5] = {7,11,12,13,17};
    int apagados[20] = {1,2,3,4,5,6,8,9,10,14,15,16,18,19,20,21,22,23,24};
    for (int i=0; i<5; i++) {
        setPixel(encendidos[i], 20, 15, 0);
        wait_ms(1);
    }
    for (int i=0; i<20; i++) {
        setPixel(apagados[i], 0, 0, 0);
        wait_ms(1);
    }
    array.update(buffer, NLEDS);
}

void sol0() {
    int encendidos[1] = {12};
    int apagados[24] = {1,2,3,4,5,6,7,8,9,10,11,13,14,15,16,17,18,19,20,21,22,23,24};
    for (int i=0; i<1; i++) {
        setPixel(encendidos[i], 10, 5, 0);
        wait_ms(1);
    }
    for (int i=0; i<24; i++) {
        setPixel(apagados[i], 0, 0, 0);
        wait_ms(1);
    }
    array.update(buffer, NLEDS);
}

void luna0() {
    int encendidos[3] = {7,11,17};
    int apagados[22] = {1,2,3,4,5,6,8,9,10,12,14,15,16,18,19,20,21,22,23,24};
    for (int i=0; i<3; i++) {
        setPixel(encendidos[i], 6, 0, 10);
        wait_ms(1);
    }
    for (int i=0; i<22; i++) {
        setPixel(apagados[i], 0, 0, 0);
        wait_ms(1);
    }
    array.update(buffer, NLEDS);
}

void luna1() {
    int encendidos[14] = {1,2,3,5,6,7,10,11,15,16,17,21,22,23};
    int apagados[11] = {4,8,9,12,13,14,18,19,20,24};
    for (int i=0; i<14; i++) {
        setPixel(encendidos[i], 10, 0, 15);
        wait_ms(1);
    }
    for (int i=0; i<11; i++) {
        setPixel(apagados[i], 0, 0, 0);
        wait_ms(1);
    }
    array.update(buffer, NLEDS);
}

int main() {
    while (true) {
        if(luz.read() > 0.9) sol2();
        else if(luz.read() > 0.8) sol1();
        else if(luz.read() > 0.7) sol0();
        else if(luz.read() > 0.6) luna0();
        else luna1();
    }
}
