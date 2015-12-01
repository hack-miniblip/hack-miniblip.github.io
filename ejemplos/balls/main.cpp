// potenciometro controla la matriz
// moviendo filas de leds
#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25

#define ANALOG_POTENTIOMETER P0_22

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
    // bordes circulares
    /*
    if(b->x>XMAX)
        b->x=XMIN;


    if(b->y>YMAX)
        b->y=YMIN;
        */

     // Rebotan en la pared

    if(b->y>YMAX)
    {
        b->y=YMAX;
        b->vy=-b->vy;
        }

    if(b->y<YMIN)
    {
        b->y=YMIN;
        b->vy=-b->vy;
        }

    if(b->x>XMAX)
    {
        b->x=XMAX;
        b->vx=-b->vx;
        }

    if(b->x<XMIN)
    {
        b->x=XMIN;
        b->vx=-b->vx;
        }
}


// Movemos la bola, ahora mismo sin v, solo +1,+1
void mueve(ball *b)
{

    b->x+=b->vx;
    b->y+=b->vy;

    bordea(b);
}

void pinta (ball * bola)
{
    setPixel(bola->x,bola->y,bola->p.red,bola->p.green,bola->p.blue);
}

void borra (ball * bola)
{
    setPixel(bola->x,bola->y,0,0,0);
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
ballW.x=1;
ballW.y=1;
ballW.vx=1;
ballW.vy=2;


ball balls[NBALLS]={ballR,ballG,ballB,ballW};

        neopixel::PixelArray array(MATRIX_PIN);


    while(true) {

             for(int i=0;i<NBALLS; i++)
             {
                borra(&(balls[i]));
                mueve(&(balls[i]));
                pinta(&(balls[i]));
            }

        array.update(buffer, NLEDS);
        float pot = ain.read() * 500.0f;
        wait_ms(pot);
    }

}
