// potenciometro controla la matriz 
// moviendo filas de leds 
#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25

AnalogIn   ain(P0_16);

AnalogIn   ainpo(P0_22);

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

    serial.printf("Hello world!\n");    
    while(true) {   
        float pot = ain.read();
        //pot = pot/100;
        int num_led = floor((pot-0.75)*100);
        if (num_led > 24){
            num_led= 24;
            }
        if (num_led < 0){
            num_led= 0;
            }

        float potenciometro = ainpo.read();

        int rojo = floor((potenciometro)*100);
        int azul = floor(100 - (potenciometro)*100);
        int verde = 0; //floor(poti*brillo);
        
        serial.printf("mini blip is alive for %i seconds.\n", counter);
        serial.printf("Pot: %3.3f%%\n", pot);
        counter++;  

        
         neopixel::PixelArray array(MATRIX_PIN);
        for(int i=0;i<NLEDS;i++) {
            setPixel(i, 0, 0, 0);
            setPixel(num_led, rojo, verde, azul);
        }
   
        array.update(buffer, NLEDS); 

    }
    
}
