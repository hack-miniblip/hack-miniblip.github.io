// miniblip play sound - capacitative + keyboard out

#include "mbed.h"
#include "USBKeyboard.h"
#include "neopixel.h"      

#define ANALOG_POTENTIOMETER P0_22
#define DATA_PIN P0_9
#define THRESHOLD   2
#define TOUCH_N     5
 
AnalogIn   ain(ANALOG_POTENTIOMETER);   
Ticker tick;
USBKeyboard keyboard;
uint8_t       key_map[] = {'a', 'f', 'd', 'g', 'd', 'h', 'j', 'k', 'l', ';', '\'', '\n'};
PinName       touch_pin[] = {P0_15, P0_14, P0_13, P0_12, P0_11};
DigitalInOut *p_touch_io[TOUCH_N];
int modo=10;
 
uint16_t touch_data[TOUCH_N] = {0, };
 
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
            if(i==3){
                modo=0;
            }
            else if(i==1){
                modo=1;
            }
        } else if (0x80 == touch_data[i]) {     // Last 7 measurement is under the threshold, touch is released
        }
    }
}

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

/*                               */
/*         ZONA TRIMMER          */
/*                               */
int uno[5][5] = {
{0,0,0,0,1},
{0,0,0,0,1},
{1,1,1,1,1},
{0,1,0,0,1},
{0,0,1,0,0}
};

int dos[5][5] = {
{0,1,0,0,1},
{1,0,1,0,1},
{1,0,0,1,1},
{1,0,0,0,1},
{0,1,0,0,1}
};

int tres[5][5] = {
{1,0,0,0,1},
{1,1,0,1,1},
{1,0,1,0,1},
{1,0,0,0,1},
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




/*                               */
/*         RELLENO RELOJ         */
/*                               */

void void_matrix(neopixel::Pixel aux[25], int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

void manecilla_horas(neopixel::Pixel vector[25], int i){
    if (i == 0){
        fill_pixel(vector,2,1,0,0,255);  
        }
    else if (i == 1 || i == 2){
        fill_pixel(vector,1,1,0,0,255);  
        }
    else if (i == 3){
        fill_pixel(vector,1,2,0,0,255);  
        }
    else if (i == 4 || i == 5){
        fill_pixel(vector,1,3,0,0,255);  
        }
    else if (i == 6){
        fill_pixel(vector,2,3,0,0,255);  
        }
    else if (i == 7 || i == 8){
        fill_pixel(vector,3,3,0,0,255);  
        }
    else if (i == 9){
        fill_pixel(vector,3,2,0,0,255);  
        }
    else if (i == 10 || i == 11){
        fill_pixel(vector,3,1,0,0,255);  
        }
}

void manecilla_minutos(neopixel::Pixel vector[25], int i){
    if(i==0){
        fill_pixel(vector,2,0,0,255,0);
        fill_pixel(vector,2,1,0,255,0);   
    }
    else if(i == 1){
        fill_pixel(vector,1,0,0,255,0);
        fill_pixel(vector,1,1,0,255,0);  
    }
    else if(i == 2){
        fill_pixel(vector,0,1,0,255,0);
        fill_pixel(vector,1,1,0,255,0);
    }
    else if(i == 3){
        fill_pixel(vector,0,2,0,255,0);
        fill_pixel(vector,1,2,0,255,0);
    }
    else if(i == 4){
        fill_pixel(vector,1,3,0,255,0);
        fill_pixel(vector,0,3,0,255,0);
    }
    else if(i == 5){
        fill_pixel(vector,1,3,0,255,0);
        fill_pixel(vector,1,4,0,255,0);
    }
    else if(i == 6){
        fill_pixel(vector,2,3,0,255,0);
        fill_pixel(vector,2,4,0,255,0);
    }
    else if(i == 7){
        fill_pixel(vector,3,3,0,255,0);
        fill_pixel(vector,3,4,0,255,0);
    }
    else if(i == 8){
        fill_pixel(vector,3,3,0,255,0);
        fill_pixel(vector,4,3,0,255,0);
    }
    else if(i == 9){
        fill_pixel(vector,3,2,0,255,0);
        fill_pixel(vector,4,2,0,255,0);
    }
    else if(i == 10){
        fill_pixel(vector,3,1,0,255,0);
        fill_pixel(vector,4,1,0,255,0);
    }
    else if(i == 11){
        fill_pixel(vector,3,1,0,255,0);
        fill_pixel(vector,3,0,0,255,0);
    }    
}


int main()
{
    //Estados de la manecillas
    int estado_horas = 0;
    int estado_minutos = 0;
    
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

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);

    neopixel::Pixel vector[25];
    void_matrix(vector);
    fill_pixel(vector,2,2,255,0,0);
    array.update(vector, 64);
    while (1) {
        
        //Modo reloj analogico
        if(modo==0){
            void_matrix(vector);
            fill_pixel(vector,2,2,255,0,0);
            manecilla_minutos(vector, estado_minutos);
            manecilla_horas(vector, estado_horas);
        
            if(estado_minutos == 11)
                estado_horas = (estado_horas+1)%12;
        
            estado_minutos = (estado_minutos+1)%12;

            array.update(vector, 64);
            wait_ms(1000);
        }
        
        //Modo cronometro
        if(modo==1){
            float pot = ain.read() * 100.0f;
            
            if(pot<33)
                drawVector(uno,vector,0,0,255);
            else if(pot >=33 && pot <66)
                drawVector(dos,vector,0,255,0);
            else
                drawVector(tres,vector,255,0,0);
        }
    }
}