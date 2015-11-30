//Código para la  #hackminiblip 

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

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
//r: intensidadRojo
//g: intensidadVerde
//b: intensidadAzul
void generaLetra(neopixel::Pixel vector[], char letra, int r, int g, int b){

    switch(letra){
        
        //Construyendo la matriz para la letra a:
        case 'a':
            //columna 0
            fill_pixel(vector, 0,0, r, g, b);
            fill_pixel(vector, 0,1, r, g, b);
            fill_pixel(vector, 0,2, r, g, b);
            fill_pixel(vector, 0,3, r, g, b);
            //columna 1            
            fill_pixel(vector, 1,2, r, g, b);
            fill_pixel(vector, 1,4, r, g, b);            
            //columna 2
            fill_pixel(vector, 2,2, r, g, b);
            fill_pixel(vector, 2,4, r, g, b);
            //columna 3
            fill_pixel(vector, 3,2, r, g, b);
            fill_pixel(vector, 3,4, r, g, b);
            //columna 4
            fill_pixel(vector, 4,0, r, g, b);
            fill_pixel(vector, 4,1, r, g, b);
            fill_pixel(vector, 4,2, r, g, b);
            fill_pixel(vector, 4,3, r, g, b);
            break;
            
        case 'e':
            //columna 0
            fill_pixel(vector, 0,0, r, g, b);
            fill_pixel(vector, 0,1, r, g, b);
            fill_pixel(vector, 0,2, r, g, b);
            fill_pixel(vector, 0,3, r, g, b);

            break;
                        
            
        default:
            break;
    }
    
    
}    


int main()
{
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    //Se está creando un objeto de tipo PixelArray y se está nombrando como array a la que se le está pasando DATA_PIN
    neopixel::PixelArray array(DATA_PIN);

    uint32_t offset = 0;
    uint32_t i = 1;

        neopixel::Pixel letra[25];
        //Inicializamos el vector a 0
        for(int i=1; i<25; i++){
            letra[i].red=0;
            letra[i].blue=0;
            letra[i].green=0;            
        } 
        //Generamos la letra
        generaLetra(letra, 'a', 150, 0 , 0 );
        
    
    while (1) {
        //Generamos la letra en el vector letra        
        generaLetra(letra, 'a', 150, 0 , 0 );
        //Iluminamos la matriz
        array.update(letra, 25);
        //Esperamos un seg
        wait_ms(1000); 
        //Reseteamos la matriz
        for(int i=0; i<25; i++){
            letra[i].red=0;
            letra[i].blue=0;
            letra[i].green=0;            
        }
        //Iluminamos la matriz a 0 (no la iluminamos)
        array.update(letra, 25);
        //Esperamos otro segundo.                                    
        wait_ms(1000);        
    }
}
