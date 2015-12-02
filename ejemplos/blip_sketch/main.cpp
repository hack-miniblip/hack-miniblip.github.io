// miniblip sketch demo

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define TOUCH_N     2
#define ANALOG_PHOTO P0_16
#define ANALOG_POTENTIOMETER P0_22
#define ANALOG_BUZZER P0_8
#define DIGITAL_CIRCLE P0_12
#define THRESHOLD   2

PinName       touch_pin[] = {P0_14, P0_12};
DigitalInOut *p_touch_io[TOUCH_N];

AnalogIn   ain(ANALOG_POTENTIOMETER);
Ticker tick;

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

int pant[5][5] = {
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};

int pantR[5][5] = {
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};

int pantG[5][5] = {
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};

int pantB[5][5] = {
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};

int palR[15] = { 5,10,15, 0,30,30, 0, 0, 0, 5,10,30,10,10,10};
int palG[15] = { 0,10, 0,30,30, 5,10,15,20,20, 0,30, 0, 0, 0};
int palB[15] = { 0, 0,10, 0, 0, 0, 0,15,20,10,10,30,20,10,30};
int actualR=30; 
int actualG=0;
int actualB=0;

uint16_t touch_data[TOUCH_N] = {0, };
int modo=10;

// Pushbutton
DigitalIn pushbutton(P0_23);

void detect(void)
{
    for (int i = 0; i < TOUCH_N; i++) {
        uint8_t count = 0;
        DigitalInOut *touch_io = p_touch_io[i];
        
        touch_io->input();
        touch_data[i] <<= 1;
        while (touch_io->read()) {
            count++;
            if (count > THRESHOLD) {
                touch_data[i] |= 0x01;
                break;
            }
        }
        touch_io->output();
        touch_io->write(1);
        
        if (0x01 == touch_data[i]) {            // Threshold, get a touch
            if(i==1){
                modo=0;
            }
            else if(i==0){
                modo=1;
            }
        } else if (0x80 == touch_data[i]) {     // Last 7 measurement is under the threshold, touch is released
        }
    }
}

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

void drawColorPage(neopixel::Pixel buffer[25],int pag) {
    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);
    for (int i=0;i<5;i++) {
        int pCol=(pag*5)+i;
        for (int g=0; g<4; g++) {       
            fill_pixel(buffer,g,i,palR[pCol],palG[pCol],palB[pCol]);
        }
        array.update(buffer, 64);
    }     
}

void refreshScreen(neopixel::Pixel buffer[25]) {
    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);
    for (int i=0;i<25;i++) {
        int posx=i%5;
        int posy=int(i/5);    
        fill_pixel(buffer,posx,posy,pantR[posx][posy],pantG[posx][posy],pantB[posx][posy]);
    }
    array.update(buffer, 64);
}   


void selectColor(neopixel::Pixel buffer[25]) {
    neopixel::PixelArray array(DATA_PIN);
    int posLed = ain.read() * 15.0f;
    if (posLed>15) posLed=15;
    int page=int(posLed/3);
    int oldpage=page;
    drawColorPage(buffer,page);
    int oldLed=posLed;
    while (1) {
        int posLed = ain.read() * 15.0f;
        if (posLed>15) posLed=15;
        page=int(posLed/5);
        if (oldpage!=page) {
            // Draw a new color page
            drawColorPage(buffer,page);
            oldpage=page;
        }
        if (oldLed!=posLed) 
        {
            fill_pixel(buffer,5,oldLed%5,0,0,0);
            oldLed=posLed;
            fill_pixel(buffer,5,posLed%5,50,50,50);
            array.update(buffer, 64);
        }
        if(pushbutton){
            // Select color
            int elColor=(page*5)+posLed%5;
            actualR=palR[elColor];
            actualG=palG[elColor];
            actualB=palB[elColor];
            wait_ms(50);
            while (pushbutton) {wait_ms(10);}
            // Repaint
            refreshScreen(buffer);
            break;
        }
    }
}

void clearScreen(neopixel::Pixel buffer[25], bool newDraw) {
    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);
    for (int i=0;i<25;i++) {
        int posx=i%5;
        int posy=int(i/5);    
        fill_pixel(buffer,posx,posy,0,0,0);
        if (newDraw) {
            pantR[posx][posy]=0;
            pantG[posx][posy]=0;
            pantB[posx][posy]=0;
        }
    }
    array.update(buffer, 64);
}


int main()
{
    // Turn off miniblip buzzer
    PwmOut speaker(P0_8);
    speaker=0.0;
    
      for (int i = 0; i < TOUCH_N; i++) {
        p_touch_io[i] = new DigitalInOut(touch_pin[i]);
        p_touch_io[i]->mode(PullDown);
        p_touch_io[i]->output();
        p_touch_io[i]->write(1);
    }
    
    tick.attach(detect, 1.0 / 40.0);
    
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);
    

    
    neopixel::Pixel vector[25];
    void_matrix(vector);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);
    
    bool pixState=0;
    int pixCount=0;
    int OldPos = ain.read() * 26.0f;

    while (1) {
        // Read Pot
        int posLed = ain.read() * 26.0f;
        if (posLed>25) posLed=25;
        if (posLed<0) posLed=0;
        int posx=posLed%5;
        int posy=int(posLed/5);
        //fill_pixel(vector,posx,posy,actualR,actualG,actualB);
        if (pixState) fill_pixel(vector,posx,posy,50,50,50); else {
            int posx=posLed%5;
            int posy=int(posLed/5);
            int cred=pantR[posx][posy];
            int cblu=pantG[posx][posy];
            int cgreen=pantB[posx][posy];
            fill_pixel(vector,posx,posy,cred,cblu,cgreen);
        }
        if (posLed!=OldPos) {
            // Delete old pos
            int posx=OldPos%5;
            int posy=int(OldPos/5);
            int cred=pantR[posx][posy];
            int cblu=pantG[posx][posy];
            int cgreen=pantB[posx][posy];
            fill_pixel(vector,posx,posy,cred,cblu,cgreen);
            OldPos=posLed;
        }
            
        pixCount++;
        if (pixCount>8) {
            pixCount=0;
            pixState^= 1;
        }
        array.update(vector, 64);
        wait_ms(30); 
       
        // Color button
        if (modo==1) {
                clearScreen(vector,false);
                selectColor(vector);
            modo=10;
        }
              
        // Change pixel
        if(pushbutton){
            //Check
            int posx=posLed%5;
            int posy=int(posLed/5);
            int cred=pantR[posx][posy];
            int cblu=pantG[posx][posy];
            int cgreen=pantB[posx][posy];
            if (cred==0&&cblu==0&cgreen==0) {
                pantR[posx][posy]=actualR;
                pantG[posx][posy]=actualG;
                pantB[posx][posy]=actualB;
            }
            else {
                pantR[posx][posy]=0;
                pantG[posx][posy]=0;
                pantB[posx][posy]=0;  
            }  
            //fill_pixel(vector,posx,posy,cred,cblu,cgreen);
            wait_ms(50);
            while (pushbutton) {wait_ms(10);}
        }
    }
}