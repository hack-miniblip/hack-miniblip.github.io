// miniblip led matrix demo

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9


/*
fill_pixel es una función que, pasado un buffer, coloca en la posición (x,y) el color rpg dado
*/


void fill_pixel(neopixel::Pixel buffer[25], int x, int y, int red, int green, int blue){
    
    if(x<0) x=0;
    if(x>4) x=4;
    if(y<0) y=0;
    if(y>4) y=4;
       

    int posicion=x+y*5;
    buffer[posicion].red=red;
    buffer[posicion].green=green;
    buffer[posicion].blue=blue;
}

/*
void_matrix coge una matriz y la "apaga" (pone todos sus colores a 0)
*/


void void_matrix(neopixel::Pixel aux[25], int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
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

    // Generamos el array y lo vaciamos
    neopixel::Pixel vector[25];
    void_matrix(vector);
    //Introducimos varios colores de prueba
    fill_pixel(vector,0,0,255,0,0);
    fill_pixel(vector,1,1,255,0,0);
    fill_pixel(vector,2,2,0,255,0);
    fill_pixel(vector,3,3,255,0,0);
    fill_pixel(vector,4,4,255,0,0);
    fill_pixel(vector,0,4,0,0,255);
    fill_pixel(vector,1,3,0,0,255);
    fill_pixel(vector,3,1,0,0,255);
    fill_pixel(vector,4,0,0,0,255);
    
    
    while (1) {
        array.update(vector, 64);
        
    }
}
