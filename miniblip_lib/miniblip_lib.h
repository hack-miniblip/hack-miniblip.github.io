#ifndef miniblip_lib
#define miniblip_lib

#define MATRIX_PIN P0_9
#define LDR_PIN P0_16
#define SPEAKER_PIN P0_8
#define POTENCIOMETER_PIN P0_22
#define BUTTON_PIN P0_23
#define RESET_PIN P0_1

#define NLEDS 25



void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue);

#endif
