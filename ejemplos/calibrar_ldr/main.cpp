// potenciometro controla la matriz 
// y buzzer al mismo tiempo envia por 
// el puerto serie

#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"
#include "SongPlayer.h"
#include "notes.h"

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS 25


AnalogIn   ain0(P0_22);
AnalogIn   ain1(P0_16);
DigitalIn pushbutton(P0_23);

unsigned int counter = 0;   
USBSerial serial;

neopixel::Pixel buffer[NLEDS];
PwmOut speaker(P0_8);

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}


//Set up notes and durations for sample song to play
// A 0.0 duration note at end terminates song play
float note[18]= {8000,9000,1000,3000.5,5000.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };
                    
                    
int main()
{
    // Turn off miniblip buzzer
    //speaker=0.0;
    
    // Buzzer pin
    SongPlayer mySpeaker(P0_8);
    // Start song and return once playing starts
    //mySpeaker.PlaySong(note,duration);
    
    // loops forever while song continues to play to end using interrupts
    /*
    while(1) {
        wait(.1);
    }
    */

    serial.printf("Hello world!\n");
    DigitalIn(MATRIX_PIN, PullDown);
    
    int ldr_max = 0;
    int ldr_min = 1000;
        
    while(true) {   
        float pot = ain0.read()*24;
        float ldr = ain1.read()*1000;
        
        ldr = ldr - 850;
        //serial.printf("mini blip is alive for %i seconds.\n", counter);
        //serial.printf("Pot: %f\n", ldr);
        counter++;
        
        while (pushbutton) {
            serial.printf("Pushbutton pulsado, ldr: %f min:%d max:%d\n",ldr,ldr_min,ldr_max);
            
            if(ldr>ldr_max) ldr_max=ldr;
            if(ldr<ldr_min) ldr_min=ldr;
            }
            
        int val = map(ldr, ldr_min, ldr_max, 0, 24);
        serial.printf("LDR value mapped: %d\n", val);
    
        neopixel::PixelArray array(MATRIX_PIN);
        
        
        for(int i=0;i<NLEDS;i++) {
            setPixel(i, 0, 0, 0);
        }

        
        if (pot >= 100) pot =100;
        setPixel(val, 0, 20, 20);
        

        array.update(buffer, NLEDS);
        wait_ms(10);    
        


    }

