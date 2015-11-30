// potenciometro controla la matriz
// moviendo filas de leds
#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25


struct ball {
   uint8_t x;
   uint8_t y;
   neopixel::Pixel p;
};




AnalogIn   ain(P0_22);

unsigned int counter = 0;
USBSerial serial;

neopixel::Pixel buffer[NLEDS];


void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

void setPixel(uint8_t x,uint8_t y, uint8_t red, uint8_t green, uint8_t blue) {
    setPixel(x*5+y,red,green,blue);
}

#define XMIN 0
#define YMIN 0
#define XMAX 4
#define YMAX 4

// Ajustamos la posicin segun los bordes
void bordea(ball *b)
{
    if(b->x>XMAX)
        b->x=XMIN;


    if(b->y>YMAX)
        b->y=YMIN;
}


// Movemos la bola, ahora mismo sin v, solo +1,+1
void move(ball *b)
{

    b->x+=+1;
    b->y+=+1;

    bordea(b);
}

void mueve(ball *bolas, int length)
{
    for(int i=0;i<length;i++)
    {
    move((bolas+i));
   }
}



void pinta (ball * bolas,int length)
{
    for(int i=0;i<length;i++)
    {
        ball *bola=(bolas+i);
        setPixel(bola->x,bola->y,bola->p.red,bola->p.green,bola->p.blue);
    }
}

void borra (ball * bolas,int length)
{
    for(int i=0;i<length;i++)
    {
        ball *bola=(bolas+i);
        setPixel(bola->x,bola->y,0,0,0);
    }
}

int main()
{

struct ball ballR,ballG,ballB;
ball balls[3]={ballR,ballG,ballB};

ballR.p.red=255;
ballR.x=0;
ballR.y=4;
ballG.p.green=255;
ballG.x=1;
ballG.y=3;
ballB.p.blue=255;
ballB.x=3;
ballB.y=1;

        neopixel::PixelArray array(MATRIX_PIN);

 //   serial.printf("Hello world!\n");
    while(true) {

             borra(balls,3);
             mueve(balls,3);
             pinta(balls,3);


        array.update(buffer, NLEDS);
        wait_ms(200);
    }

}
