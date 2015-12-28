// potenciometro controla la matriz 
// y buzzer al mismo tiempo envia por 
// el puerto serie

#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25


AnalogIn   ain(P0_22);
AnalogIn   ain2(P0_14);

unsigned int counter = 0;   
USBSerial serial;

neopixel::Pixel buffer[NLEDS];

PwmOut speaker(P0_8);


void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

 void setFila(uint32_t fila, uint8_t red, uint8_t green, uint8_t blue){
     if(fila==0){
         for(int i=0;i<5;i++){
            buffer[i].red=red;
            buffer[i].green=green;
            buffer[i].blue=blue;
        }
    }
    if(fila==1){
         for(int i=5;i<10;i++){
            buffer[i].red=red;
            buffer[i].green=green;
            buffer[i].blue=blue;
        }
    }
    if(fila==2){
         for(int i=10;i<15;i++){
            buffer[i].red=red;
            buffer[i].green=green;
            buffer[i].blue=blue;
        }
    }
    if(fila==3){
         for(int i=15;i<20;i++){
            buffer[i].red=red;
            buffer[i].green=green;
            buffer[i].blue=blue;
        }
    }
    if(fila==4){
         for(int i=20;i<25;i++){
            buffer[i].red=red;
            buffer[i].green=green;
            buffer[i].blue=blue;
        }
    }
}
                
            

int main()
{
    // Turn off miniblip buzzer
    speaker=0.0;
     float pot;
     float frecuencia;
     float frecuencia2;
     float maxi=70;
     float mini=78;
     int t;
     neopixel::PixelArray array(MATRIX_PIN);

  
    while(true) {
      /* if(ain2.read()>maxi)
        maxi=ain2.read();
       if(ain2.read()<mini)
        mini=ain2.read();
    */
        frecuencia=ain2.read() * 100.0f;;
        //t++;
        //if (t==3){
           // serial.printf("Maximo: %f%%\n", maxi);
           // serial.printf("Minimo: %f%%\n", mini);
    
        t=0; //set back track to zero
        maxi=73;
        mini=78;
        //serial.printf("Frecuencia: %3.3f%%\n", frecuencia);
        //serial.printf("Frecuencia2: %f%%\n", frecuencia);
          setFila(0,0,0,frecuencia);
            setFila(1,0,0,0);
            setFila(2,0,0,0);
            setFila(3,0,0,0);
            setFila(4,0,0,0);
            array.update(buffer, NLEDS);
      //  centro(frecuencia,frecuencia,frecuencia);
        if(frecuencia>79.2){
           // rectanguloMedio(0,frecuencia,0);
            //rectanuloGrande(0,0,0);
            //centro(0,frecuencia,0);
            setFila(0,0,0,frecuencia);
            setFila(1,0,0,0);
            setFila(2,0,0,0);
            setFila(3,0,0,0);
            setFila(4,0,0,0);
            array.update(buffer, NLEDS);
        }
        if(frecuencia>79.6){
            //rectanguloMedio(0,0,frecuencia);
            //rectanuloGrande(0,0,0);
            //centro(0,0,frecuencia);
            setFila(1,0,frecuencia,0);
            setFila(2,0,0,0);
            setFila(3,0,0,0);
            setFila(4,0,0,0);
            array.update(buffer, NLEDS);
        }
        if(frecuencia>79.85){
            //rectanguloMedio(0,0,frecuencia);
            //rectanuloGrande(0,0,frecuencia);
            //centro(0,0,frecuencia);
            setFila(2,frecuencia,frecuencia,0);
            setFila(3,0,0,0);
            setFila(4,0,0,0);
            array.update(buffer, NLEDS);
        }
         if(frecuencia>80.15){
            //rectanguloMedio(0,0,frecuencia);
            //rectanuloGrande(0,0,frecuencia);
            //centro(0,0,frecuencia);
            setFila(3,frecuencia,035,001);
            setFila(4,0,0,0);
            array.update(buffer, NLEDS);
        }
        if(frecuencia>81){
             //rectanguloMedio(frecuencia,0,0);
            //rectanuloGrande(frecuencia,0,0);
            //centro(frecuencia,0,0);
            setFila(4,frecuencia,0,0);
            //setFila(3,0,0,0);
            //setFila(4,0,0,0);
            array.update(buffer, NLEDS);
            
        }
        if(frecuencia>84.6555555){
            // rectanguloMedio(frecuencia,frecuencia,frecuencia);
            //rectanuloGrande(frecuencia,frecuencia,frecuencia);
            //centro(frecuencia,frecuencia,frecuencia);
            setFila(0,frecuencia,frecuencia,frecuencia);
            setFila(1,frecuencia,frecuencia,frecuencia);
            setFila(2,frecuencia,frecuencia,frecuencia);
            setFila(3,frecuencia,frecuencia,frecuencia);
            setFila(4,frecuencia,frecuencia,frecuencia);
            array.update(buffer, NLEDS);
           // setFila(0,0,0,0);
            //setFila(1,0,0,0);
            //setFila(2,0,0,0);
            //setFila(3,0,0,0);
            //setFila(4,0,0,0);
        }          
        
        

    }
    

}
