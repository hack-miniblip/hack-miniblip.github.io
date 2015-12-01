// potenciometro controla la matriz 
// moviendo filas de leds 
#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25

AnalogIn   ain(P0_16);

AnalogIn   ainpo(P0_22);

unsigned int counter = 0;   

neopixel::Pixel buffer[NLEDS];
PwmOut speaker(P0_8);

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

int corazon[25] = {0,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0};
//int circulo[25] = {0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0};
//int circulo[25] = {0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0};
int circulo[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int estado = 0;
int palpito = 0;
int cuenta = 0;
int limite= 10;

int main(){


    while(true) {   

        float pot = ain.read();

        float potenciometro = ainpo.read();

        limite= floor((pot-0.9)*10) + floor(potenciometro * 5);

        neopixel::PixelArray array(MATRIX_PIN);
         
        for(int i=0;i<NLEDS;i++) {
            setPixel(i, 0, 0, 0);
            //setPixel(num_led, rojo, verde, azul);
        }
   
        if (estado == 1){
            for(int i=0;i<25;i++) {
                if (corazon[i] == 1){
                    setPixel(i, 5, 0, 0);
                }
            }
            if (cuenta > limite){
                estado= 0;
                cuenta = 0;
            }
            else {
                cuenta++;
            }
        }
   
       else {
            for(int i=0;i<25;i++) {
                if (circulo[i] == 1){
                    setPixel(i, 5, 0, 0);
                }
            }
            if (cuenta > limite){
                estado= 1;
                cuenta = 0;
            }
            else {
                cuenta++;
            }
        }
        
 /*       
        if (cuenta == 0){
            if (palpito < 4){
                limite = floor(potenciometro*10);
                palpito++;
            }
            else {
                limite = floor(potenciometro*5);
                palpito = 1;
            }
        }
 */       
        wait_ms(100);
        array.update(buffer, NLEDS); 

    }
    
}
