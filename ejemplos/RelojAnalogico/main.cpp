// miniblip play sound - capacitative + keyboard out

#include "mbed.h"
#include "USBKeyboard.h"
#include "neopixel.h"  

#define ANALOG_POTENTIOMETER P0_22
#define DATA_PIN P0_9
#define THRESHOLD   2
#define TOUCH_N     2

 
AnalogIn   ain(ANALOG_POTENTIOMETER);   
Ticker tick;
USBKeyboard keyboard;
uint8_t       key_map[] = {'a', 'f', 'd', 'g', 'd', 'h', 'j', 'k', 'l', ';', '\'', '\n'};
PinName       touch_pin[] = {P0_14, P0_12};
DigitalInOut *p_touch_io[TOUCH_N];

int modo=10;
DigitalIn boton_avanzar(P0_23); //Define boton_avanzar

Serial pc(USBTX, USBRX); // Define serial TX RX
 
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
            if(i==1){
                modo=0;
            }
            else if(i==0){
                modo=3;
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
        fill_pixel(vector,2,1,0,0,30);  
        }
    else if (i == 1 || i == 2){
        fill_pixel(vector,1,1,0,0,30);  
        }
    else if (i == 3){
        fill_pixel(vector,1,2,0,0,30);  
        }
    else if (i == 4 || i == 5){
        fill_pixel(vector,1,3,0,0,30);  
        }
    else if (i == 6){
        fill_pixel(vector,2,3,0,0,30);  
        }
    else if (i == 7 || i == 8){
        fill_pixel(vector,3,3,0,0,30);  
        }
    else if (i == 9){
        fill_pixel(vector,3,2,0,0,30);  
        }
    else if (i == 10 || i == 11){
        fill_pixel(vector,3,1,0,0,30);  
        }
}

void manecilla_minutos(neopixel::Pixel vector[25], int i){
    if(i==0){
        //12
        fill_pixel(vector,2,0,0,30,0);
        fill_pixel(vector,2,1,0,30,0);   
    }
    else if(i == 1){
        //1
        fill_pixel(vector,1,0,0,30,0);
        fill_pixel(vector,1,1,0,30,0);  
    }
    else if(i == 2){
        //2
        fill_pixel(vector,0,1,0,30,0);
        fill_pixel(vector,1,1,0,30,0);
    }
    else if(i == 3){
        //3
        fill_pixel(vector,0,2,0,30,0);
        fill_pixel(vector,1,2,0,30,0);
    }
    else if(i == 4){
        fill_pixel(vector,1,3,0,30,0);
        fill_pixel(vector,0,3,0,30,0);
    }
    else if(i == 5){
        fill_pixel(vector,1,3,0,30,0);
        fill_pixel(vector,1,4,0,30,0);
    }
    else if(i == 6){
        fill_pixel(vector,2,3,0,30,0);
        fill_pixel(vector,2,4,0,30,0);
    }
    else if(i == 7){
        fill_pixel(vector,3,3,0,30,0);
        fill_pixel(vector,3,4,0,30,0);
    }
    else if(i == 8){
        fill_pixel(vector,3,3,0,30,0);
        fill_pixel(vector,4,3,0,30,0);
    }
    else if(i == 9){
        fill_pixel(vector,3,2,0,30,0);
        fill_pixel(vector,4,2,0,30,0);
    }
    else if(i == 10){
        fill_pixel(vector,3,1,0,30,0);
        fill_pixel(vector,4,1,0,30,0);
    }
    else if(i == 11){
        fill_pixel(vector,3,1,0,30,0);
        fill_pixel(vector,3,0,0,30,0);
    }    
}

void dibuja_numero(neopixel::Pixel vector[25], int i){
    
    if(i==1){
            
        fill_pixel(vector,2,0,0,30,0);
        fill_pixel(vector,2,1,0,30,0);
        fill_pixel(vector,2,2,0,30,0);
        fill_pixel(vector,2,3,0,30,0);
        fill_pixel(vector,2,4,0,30,0);
        
        fill_pixel(vector,0,4,0,30,0);
        fill_pixel(vector,1,4,0,30,0);
        fill_pixel(vector,3,4,0,30,0);
        fill_pixel(vector,4,4,0,30,0);
        
        fill_pixel(vector,3,1,0,30,0);
        fill_pixel(vector,4,2,0,30,0);
        
    }
    
    else if(i==2){
            
        fill_pixel(vector,2,3,0,30,0);  
        fill_pixel(vector,1,2,0,30,0);
        fill_pixel(vector,0,1,0,30,0);
        fill_pixel(vector,1,0,0,30,0);            
        fill_pixel(vector,2,0,0,30,0);
        fill_pixel(vector,3,0,0,30,0);
        fill_pixel(vector,4,1,0,30,0);
        
        fill_pixel(vector,0,4,0,30,0);
        fill_pixel(vector,1,4,0,30,0);
        fill_pixel(vector,3,4,0,30,0);
        fill_pixel(vector,2,4,0,30,0);
        fill_pixel(vector,4,4,0,30,0);
        
    }
    
    else if(i==3){
            

        fill_pixel(vector,0,1,0,30,0);
        fill_pixel(vector,1,2,0,30,0);
        fill_pixel(vector,3,2,0,30,0);
        fill_pixel(vector,2,2,0,30,0);
        fill_pixel(vector,4,2,0,30,0);
        
        fill_pixel(vector,1,0,0,30,0);
        fill_pixel(vector,3,0,0,30,0);
        fill_pixel(vector,2,0,0,30,0);
        fill_pixel(vector,4,0,0,30,0);

        fill_pixel(vector,0,3,0,30,0);
        fill_pixel(vector,1,4,0,30,0);
        fill_pixel(vector,3,4,0,30,0);
        fill_pixel(vector,2,4,0,30,0);
        fill_pixel(vector,4,4,0,30,0);
        
    }
    
    
}

int main()
{
    //Estados de la manecillas
    int estado_horas = 0;
    int estado_minutos = 0;
    
    for (int i = 0; i < TOUCH_N; i++) {
        p_touch_io[i] = new DigitalInOut(touch_pin[i]);
        p_touch_io[i]->mode(PullDown);
        p_touch_io[i]->output();
        p_touch_io[i]->write(1);
    }
    
    tick.attach(detect, 1.0 / 40.0);
    
    PwmOut speaker(P0_8);
    speaker=0.0;
    
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);

    neopixel::Pixel vector[25];
    void_matrix(vector);
    fill_pixel(vector,2,2,30,0,0);
    array.update(vector, 64);
    while (1) {
        
        //Modo reloj analogico
        if(modo==3){
            for(int i=0; i < 3000;i++){ 
                
                if(boton_avanzar){
                    estado_minutos = (estado_minutos+1)%12;  
                    if(estado_minutos == 0)
                        estado_horas = (estado_horas+1)%12;
                }
                
                void_matrix(vector);
                fill_pixel(vector,2,2,30,0,0);
                manecilla_minutos(vector, estado_minutos);
                manecilla_horas(vector, estado_horas);
                array.update(vector, 64);
                wait_ms(100);
            }
            estado_minutos = (estado_minutos+1)%12;
            if(estado_minutos == 0)
                estado_horas = (estado_horas+1)%12;
        }
        
        //Modo cronometro
        if(modo==0){
            float pot = ain.read() * 100.0f;
            void_matrix(vector);
            
            if(pot<33){
                dibuja_numero(vector,1);
                if(boton_avanzar){
                    modo++;
                    estado_horas = 0;
                }
            }
            
            else if(pot >=33 && pot <66){
            
                dibuja_numero(vector,2);
                if(boton_avanzar){
                    modo++;
                    estado_horas = 1;
                }
            
            }
            else{
                dibuja_numero(vector,3);
                if(boton_avanzar){
                    modo++;
                    estado_horas = 2;                
                }
            }
            array.update(vector, 64);
        }
        
        if (modo==1){
            void_matrix(vector);
            fill_pixel(vector,2,2,30,0,0);

            manecilla_minutos(vector, estado_minutos);
            manecilla_horas(vector, estado_horas);
            array.update(vector, 64);
            wait_ms(5000);
            
            if(estado_minutos == 1){
                if(estado_horas==0){    
                    modo=2;
                }
                else            
                    estado_horas = (estado_horas+11)%12;
            }
            estado_minutos = (estado_minutos+11)%12;
        }
        
        if(modo==2){
            speaker=10.0;
            estado_horas=0;
            estado_minutos=0;
            void_matrix(vector);
            fill_pixel(vector,2,2,30,0,0);
            manecilla_minutos(vector, estado_minutos);
            manecilla_horas(vector, estado_horas);
            array.update(vector, 64);
        }
    }
}