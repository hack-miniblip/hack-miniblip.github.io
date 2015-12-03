// miniblip play sound - capacitative + keyboard out

#include "mbed.h"
#include "USBKeyboard.h"
#include "neopixel.h"

#define THRESHOLD   2
#define TOUCH_N     5


// Matrix led output pin
#define DATA_PIN P0_9

AnalogIn   ain0(P0_22);

void generate(neopixel::Pixel * out, uint32_t index, uintptr_t extra)
{
    uint32_t brightness = (index + extra) >> 3;
    out->red   = ((index + extra) & 0x1) ? brightness : 0;
    out->green = ((index + extra) & 0x2) ? brightness : 0;
    out->blue  = ((index + extra) & 0x4) ? brightness : 0;
}

Ticker tick;
USBKeyboard keyboard;

uint8_t       key_map[] = {'h', 'o', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', UP_ARROW, RIGHT_ARROW, DOWN_ARROW, ' '};
uint8_t       key_map2[] = {'U', 'n', ' ', 'a', 'b', 'r', 'a', 'z', 'o', '!', '!', '\n'};
PinName       touch_pin[] = {P0_12, P0_14, P0_13, P0_15, P0_11};
DigitalInOut *p_touch_io[TOUCH_N];

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
            keyboard.putc(key_map[i]);
                            
                }
    }
}

int main()
{

 wait_ms(800);
    
    /*
    
    for (int i = 0; i < TOUCH_N; i++) {
        p_touch_io[i] = new DigitalInOut(touch_pin[i]);
        p_touch_io[i]->mode(PullDown);
        p_touch_io[i]->output();
        p_touch_io[i]->write(1);
    }
    
    tick.attach(detect, 1.0 / 40.0);
    
    while(1) {
        // do something
        wait(1);
    }
    
    */

    for (int i = 0; i < 20; i++) {
        keyboard.putc(key_map2[i-1]);
        wait_ms(200);
        
        }
        
    keyboard.printf("My miniblip is writiting you!! hackaton #hackminiblip :) \n");
    
    wait_ms(200);
    
    
    // Turn off miniblip buzzer
    PwmOut speaker(P0_8);
    speaker=0.0;
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);

    uint32_t offset = 0;
    uint32_t i = 1;
    while (1) {
        float pot = ain0.read()*100;
        array.update(generate, 64, offset++);
        
        //Play Sound
        float note=500+(i*100);
        speaker.period(1.0/note);           
        speaker = float(i)/50.0;
        
        i++;
        if (i>10) i=1;
        // Rainbow delay
        wait_ms(pot);
    }
        
}
