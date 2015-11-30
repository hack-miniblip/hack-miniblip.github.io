#define NLEDS 25

AnalogIn   ain(P0_22);

unsigned int counter = 0;   
USBSerial serial;

neopixel::Pixel buffer[NLEDS];
PwmOut speaker(P0_8);

void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}

int main()
{
    // Turn off miniblip buzzer
    speaker=0.0;

    serial.printf("Hello world!\n");    
    while(true) {   
        float pot = ain.read();
        serial.printf("mini blip is alive for %i seconds.\n", counter);
        serial.printf("Pot: %3.3f%%\n", pot);
        counter++;  
    
        int rgb = floor(255*pot); 
        neopixel::PixelArray array(MATRIX_PIN);
        for(int i=0;i<NLEDS;i++) {
            setPixel(i, rgb, 255-rgb, rgb);
        }
                
        array.update(buffer, NLEDS); 

    }
    
}// miniblip led matrix demo
