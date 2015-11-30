# Haciendo una pausa

       wait_ms(100); // Milisegundos


# Defines de los pines

#define MATRIX_PIN P0_9
#define LDR_PIN P0_16
#define SPEAKER_PIN P0_8
#define POTENCIOMETER_PIN P0_22
#define BUTTON_PIN P0_23
#define RESET_PIN P0_1

#define NLEDS 25

# Sonidos

PwmOut speaker(SPEAKER_PIN); // el P0_8

float note=440;
speaker.period(1.0/note);           
speaker = 50.0;


# Lectura de valores analógicos

## Potenciometro

AnalogIn   ain(POTENCIOMETER_PIN);

float valorPot=ain.read();
