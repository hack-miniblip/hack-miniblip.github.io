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

    #define AD0 P0_11
    #define AD1 P0_12
    #define AD2 P0_13
    #define AD3 P0_14
    #define AD4 P0_15

# Sonidos

    PwmOut speaker(SPEAKER_PIN); // el P0_8
    float note=440;
    speaker.period(1.0/note);  // Usamos el periodo, inverso de la frecuencia          
    speaker = 50.0;  // establecemos el volumen


# Lectura de valores analógicos

El LPC11u24 tiene 8 adc de los que MiniBip tiene disponibles 7 (el octavo está conectado al botón y solo se usa como digital)

    5 contactos circulares
      AD0 en P0.11
      AD1 en P0.12
      AD2 en P0.13
      AD3 en P0.14
      AD4 en P0.15
    LDR en P0.16
    Potenciómetro en P0.22


## Potenciometro

    AnalogIn   ain(POTENCIOMETER_PIN);
    float valorPot=ain.read();

# Escritura por el puerto serie

    // Importamos la librería USBDevice
    #include "USBSerial.h"

    USBSerial serial;

    serial.printf("Hello world!\n");

    // Podemos usar el ejemplo en python ./ejemplos/leds_serial_potenciometro_buzzer/pythonserial.py
    // Podemos usar cualquier program monitor serie como Putty o minicom

# Lectura del puerto serie

    // Importamos la librería USBDevice
    #include "USBSerial.h"

    USBSerial serial;

    char* readBuffer;

    serial.scanf("%s",readBuffer);

    // OJO: scanf es bloqueante, así que el main loop no continuará hasta que sea lea algo.
    // Para tener algo que leer, se pueden enviar datos por el puerto serie con 'echo 1 > /dev/ttyACM0'

# Botones

    // Definimos el pin como entrada
    DigitalIn pushbutton(BUTTON_PIN);

    // Definimos el pin como PWM
    PwmOut speaker(P0_8);

    while(true){

      if(pushbutton){ // Al pulsar suena
          speaker=10.0;
      }else{
          speaker=0.0;    
      }
    }
# Map convertir un valor de un intervalo [in_min,in_max] a su valor proporcional en otro intervalo [out_min,out_max]


    long map(long x, long in_min, long in_max, long out_min, long out_max)
    {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

# Matriz de Leds

Disponemos de 25 leds, que podemos direccionar desde el 0 al 24 con la librería PixelArray

Podemos añadir más leds conectando la entrada al pin LDOut
