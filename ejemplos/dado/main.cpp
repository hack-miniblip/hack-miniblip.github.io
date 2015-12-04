// miniblip led dado 
// JCristobal version, original Alberto Pigante from https://developer.mbed.org/users/pighixxx/code/blip_dado/
// Now all faces can win (not ones always win) and wait sequence reduced

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

#define ANALOG_PHOTO P0_16
#define ANALOG_POTENTIOMETER P0_22
#define ANALOG_BUZZER P0_8
#define DIGITAL_CIRCLE P0_12

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

int dado_1[5][5] = {
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,1,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};

int dado_2[5][5] = {
{0,0,0,0,1},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{1,0,0,0,0}
};
    
int dado_3[5][5] = {
{0,0,0,0,1},
{0,0,0,0,0},
{0,0,1,0,0},
{0,0,0,0,0},
{1,0,0,0,0}
};

int dado_4[5][5] = {
{1,0,0,0,1},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{1,0,0,0,1}
};
 
int dado_5[5][5] = {
{1,0,0,0,1},
{0,0,0,0,0},
{0,0,1,0,0},
{0,0,0,0,0},
{1,0,0,0,1}
};
 
int dado_6[5][5] = {
{1,0,0,0,1},
{0,0,0,0,0},
{1,0,0,0,1},
{0,0,0,0,0},
{1,0,0,0,1}
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
    
    // Pushbutton
    DigitalIn pushbutton(P0_23);
    
    neopixel::Pixel vector[25];
    void_matrix(vector);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);
    int posLed=0;
    int cred=10;
    int cblue=10;
    int cgreen=10;
    while (1) {
        // Wait screen
        int posx=posLed%5;
        int posy=int(posLed/5);
        fill_pixel(vector,posx,posy,cred,cblue,cgreen);
        array.update(vector, 64);
        wait_ms(30); 
        posLed++;
        if (posLed>24) {
            cred=int(rand()%50);
            cblue=int(rand()%50);
            cgreen=int(rand()%50);
            posLed=0;
        } 
        // Wait button
        if(pushbutton){
            posLed=0;
            float pot = ain.read() * 100.0f;
            int startdelay=10;
            int face=1;             // ones always win
            face = rand() % 6 + 1;  // Let's give a chance to others
            int red=50;
            while (1) {
                if (startdelay>300+(pot*3)) red=200;
                switch(face) {
                    case 1:
                        drawVector(dado_1,vector,red,200-red,200-red);
                        break;
                    case 2:
                        drawVector(dado_2,vector,red,200-red,200-red);
                        break;
                    case 3:
                        drawVector(dado_3,vector,red,200-red,200-red);
                        break;
                    case 4:
                        drawVector(dado_4,vector,red,200-red,200-red);
                        break;
                    case 5:
                        drawVector(dado_5,vector,red,200-red,200-red);
                        break;
                    case 6:
                        drawVector(dado_6,vector,red,200-red,200-red);
                        break;
                }
                array.update(vector, 64);
                if (startdelay>300+(pot*3)) break;
                face++;
                startdelay=startdelay+50;
                if (face>6) face=1;
                wait_ms(startdelay);
                
            }
            speaker=5.0;
            wait_ms(1000);
            speaker=0.0;
            wait_ms(2500);
        }
    }
}
