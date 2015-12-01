/* Prueba de los LEDS para MINIBLIP

Funcionalidad 0, suena la escala y muestra caras 

(Versión de EL SONRISAS de @fergunet https://github.com/hack-miniblip/hack-miniblip.github.io/tree/master/ejemplos/El_Sonrisas )

Usa la función fill_pixel de @javacasm, que está en https://github.com/hack-miniblip/hack-miniblip.github.io/blob/master/ejemplos/iluminandoLetras/main.cpp
*/
// miniblip led matrix demo

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

#define ANALOG_PHOTO P0_16
#define ANALOG_POTENTIOMETER P0_22
AnalogIn   ain(ANALOG_POTENTIOMETER);

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

void void_matrix(neopixel::Pixel aux[25], int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

int sonrisa[5][5] = {
{0,1,0,1,0},
{0,1,0,1,0},
{0,0,0,0,0},
{1,0,0,0,1},
{0,1,1,1,0}
};

int sonrisaTriste[5][5] = {
{0,1,0,1,0},
{0,1,0,1,0},
{0,0,0,0,0},
{0,1,1,1,0},
{1,0,0,0,1}
};

int sonrisaRegular[5][5] = {
{0,1,0,1,0},
{0,1,0,1,0},
{0,0,0,0,0},
{1,1,1,1,1},
{0,0,0,0,0}
};   

 

void drawVector(int theArray[5][5], neopixel::Pixel * vectorPixel, int r, int g, int b){
    for(int i = 0;i<5;i++){
        for(int j = 0; j<5;j++){
            if(theArray[i][j] == 1)
                fill_pixel(vectorPixel,i,j,r,g,b);
            else
                fill_pixel(vectorPixel,i,j,0,0,0); 
        }
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

    neopixel::Pixel vector[25];
    void_matrix(vector);
    

    
    int tiempo = 1000;
    uint32_t i = 1;
    
    while (1) {
        
        //Play Sound
        float note=500+(i*100);
        speaker.period(1.0/note);           
        speaker = float(i)/50.0;
        
        i++;
        if (i>10) i=1;
        
        // Mostramos las caras
        array.update(vector, 64);
        drawVector(sonrisaTriste,vector,255,0,0);
        wait_ms(tiempo);
        
        array.update(vector, 64);
        drawVector(sonrisaRegular,vector,0,0,255);
        wait_ms(tiempo);
        
        array.update(vector, 64);
        drawVector(sonrisa,vector,0,255,0);
        wait_ms(tiempo);
        
        if(tiempo!=100){
            // empieza la locura
            tiempo = tiempo - 100;
        }
        
    }
}