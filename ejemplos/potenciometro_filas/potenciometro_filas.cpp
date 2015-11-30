// potenciometro controla la matriz 
// moviendo filas de leds 
#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25

AnalogIn   ain(P0_22);

unsigned int counter = 0;   
USBSerial serial;

neopixel::Pixel buffer[NLEDS];
PwmOut speaker(P0_8);

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

int main()
{

 //   serial.printf("Hello world!\n");    
    while(true) {   
        float pot = ain.read();
        
        int num_led = floor(pot*4);
        if (num_led > 4){
            num_led= 4;
            }
        
 //       serial.printf("mini blip is alive for %i seconds.\n", counter);
 //       serial.printf("Pot: %3.3f%%\n", pot);
        counter++;  
        float poti = 1;
        float brillo = 10;
        int rojo = floor(poti*brillo);
        int verde = floor(poti*brillo);
        int azul = floor(poti*brillo);
        neopixel::PixelArray array(MATRIX_PIN);
        for(int i=0;i<NLEDS;i++) {
            setPixel(i, 0, 0, 0);
        }
             for(int ii=0;ii<5;ii++) {
             setPixel(ii, 0, 0, 0);
             setPixel((num_led * 5) + ii, rojo, verde, azul);
            }            
                
        array.update(buffer, NLEDS); 

    }
    
}

