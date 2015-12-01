// potenciometro controla la matriz
// moviendo filas de leds
#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25


struct ball {
   int8_t x;
   int8_t vx;
   int8_t y;
   int8_t vy;
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
    serial.printf("%d,%d",x,y);
    setPixel(x*5+y,red,green,blue);
}

#define XMIN 0
#define YMIN 0
#define XMAX 4
#define YMAX 4

#define NBALLS 4

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

    b->x+=b->vx;
    b->y+=b->vy;

    bordea(b);
}

void mueve(ball *bolas, int length)
{
    for(int i=0;i<length;i++)
    {
        move(bolas+i);
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

struct ball ballR,ballG,ballB,ballW;


ballR.p.red=55;
ballR.x=0;
ballR.y=4;
ballR.vx=1;
ballR.vy=1;
ballG.p.green=55;
ballG.x=1;
ballG.y=3;
ballG.vx=0;
ballG.vy=1;
ballB.p.blue=55;
ballB.x=3;
ballB.y=1;
ballB.vx=1;
ballB.vy=0;
ballW.p.green=55;
ballW.p.red=55;
ballW.p.blue=55;
ballW.x=2;
ballW.y=2;
ballW.vx=1;
ballW.vy=2;


ball balls[3]={ballR,ballG,ballB};

        neopixel::PixelArray array(MATRIX_PIN);

 //   serial.printf("Hello world!\n");
    while(true) {

             borra(balls,NBALLS);
             mueve(balls,NBALLS);
             pinta(balls,NBALLS);


        array.update(buffer, NLEDS);
        wait_ms(400);
    }

}
