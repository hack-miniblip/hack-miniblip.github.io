//tamagotchi minimalista
//instrucciones:
/*
Hay tres estados: pequeño verde, mediano azul, grande rojo
Hay tres botones de pod:
dos verdes: 
- comer: cada tres veces que se pulse el boton pasa a un estado superior, de verde pequeño a azul mediano y rojo grande.
- ejercicio: inverso a comer, va un estado abajo. EL objetivo es estar en un estado azul mediano y recolectar corazones. Cada
vez que haces ejercicio en este estado salen corazones y los coleccionas, pero tras 4 veces, vuelve al estado pequeño verde 
y debes comer otra vez. te sale la lista de corazones cada vez que lo haces.
uno rojo:
-medicina: vuelves automaticamente al estado verde pequeño, pero pierdes un corazón.
COSAS POR AÑADIR:
-los circulos tactiles para cambiar los colores
-añadir que salgan los corazones
- algo con el sensor de luz...
*/
//CODIGO:
#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define ANALOG_POTENTIOMETER P0_22


//Ticker tick;

AnalogIn   ain(ANALOG_POTENTIOMETER);
DigitalIn pushbutton(P0_23);




void void_matrix(neopixel::Pixel* aux, int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

//Si color = 1 --> rojo. Si color = 2 --> azul Si color = 3 --> azul
void encenderLed(neopixel::Pixel* aux,int posicion,int color){
    
    if(color == 1){
        aux[posicion].red = 0x11;
        aux[posicion].blue = 0x00;
        aux[posicion].green = 0x00;
    }else if(color == 2){
        aux[posicion].red = 0x00;
        aux[posicion].blue = 0x11;
        aux[posicion].green = 0x00;
    }else if(color == 3){
        aux[posicion].red = 0x00;
        aux[posicion].blue = 0x00;
        aux[posicion].green = 0x11;        
    }else if(color == 4){
        aux[posicion].red = 0x00;
        aux[posicion].blue = 0x00;
        aux[posicion].green = 0x00; 
        
    }
}

void corazon(neopixel::Pixel* aux){
    int color=1;
    void_matrix(aux);
    encenderLed(aux,0,color);
    encenderLed(aux,1,color);    
    encenderLed(aux,3,color);
    encenderLed(aux,4,color);
    encenderLed(aux,5,color);
    encenderLed(aux,6,color);
    encenderLed(aux,7,color);
    encenderLed(aux,8,color);
    encenderLed(aux,9,color);
    encenderLed(aux,10,color);
    encenderLed(aux,11,color);
    encenderLed(aux,12,color);
    encenderLed(aux,13,color);
    encenderLed(aux,14,color);
    encenderLed(aux,18,color);
    encenderLed(aux,17,color);
    encenderLed(aux,16,color);
    encenderLed(aux,22,color);    
    
}

//Si color = 1 --> rojo. Si color = 2 --> azul Si color = 3 --> azul
void one(neopixel::Pixel* aux,int color){
    
    void_matrix(aux);
    encenderLed(aux,4,color);
    //encenderLed(aux,14,color);    
    //encenderLed(aux,24,color);
    
}
void two(neopixel::Pixel* aux,int color){
    
    void_matrix(aux);
    //encenderLed(aux,4,color);
    encenderLed(aux,14,color);    
    //encenderLed(aux,24,color);
    
}
void three(neopixel::Pixel* aux,int color){
    
    void_matrix(aux);
    //encenderLed(aux,4,color);
    //encenderLed(aux,14,color);    
    encenderLed(aux,24,color);
    
}

void p1(neopixel::Pixel* aux,int color){
    
    void_matrix(aux);
    encenderLed(aux,17,color);
    
    }
    
void p2(neopixel::Pixel* aux,int color){
    void_matrix(aux);
    encenderLed(aux,17,color);
    encenderLed(aux,12,color);
    encenderLed(aux,11,color);
    encenderLed(aux,16,color);
    
    }
void p3(neopixel::Pixel* aux,int color){
    void_matrix(aux);
    encenderLed(aux,17,color);
    encenderLed(aux,12,color);
    encenderLed(aux,11,color);
    encenderLed(aux,16,color);
    encenderLed(aux,7,color);
    encenderLed(aux,6,color);
    encenderLed(aux,5,color);
    encenderLed(aux,10,color);
    encenderLed(aux,15,color);
    
    }
    
void bl(neopixel::Pixel* aux){
    void_matrix(aux);
    encenderLed(aux,0,4);
    }
    
void cuenta(neopixel::Pixel* aux, int cu){
    void_matrix(aux);
for(int i=0; i<cu; i++){
    encenderLed(aux,i,1);
    }    
}

int main() {
    bool control=true;
    int i;
    DigitalIn(DATA_PIN, PullDown);
    neopixel::Pixel vector[25];
    
    neopixel::PixelArray array(DATA_PIN);
    int con=1;
    int con2=0;
    int con3=0;
    int cor=0; //corazones
    
    while(control){
        float pot = ain.read() * 100.0f;
        if(pot == 0){
        con3=0;
        one(vector,2);
        array.update(vector,25);
        if(pushbutton){
                con2++;
                
        if(con2>3&&con2<6){
                p2(vector,2);
                array.update(vector,25);
                wait_ms(500);
                con=2;}
        else if(con2>5){
                p3(vector,1);
                array.update(vector,25);
                wait_ms(500);
                con=3;
                
        }else{
        p1(vector,3);
        array.update(vector,25);
        wait_ms(500);
        con=1;    
        }
        }
            
        }else if(pot > 0 && pot <50){
            
            two(vector,2);
            array.update(vector,25);
            if(pushbutton){
                con3++;
                if(con==1){
                    p1(vector,3);
                    array.update(vector,25);
                    wait_ms(500);
                    bl(vector);
                    array.update(vector,25);
                    wait_ms(500);
                }
                if(con==2){
                    p2(vector,3);
                    array.update(vector,25);
                    wait_ms(500);
                    bl(vector);
                    array.update(vector,25);
                    wait_ms(500);
                    corazon(vector);
                    array.update(vector,25);
                    wait_ms(500);
                    cor++;
                    bl(vector);
                    array.update(vector,25);
                    wait_ms(300);
                    cuenta(vector,cor);
                    array.update(vector,25);
                    wait(1);
                }
                if(con==3){
                    p3(vector,1);
                    array.update(vector,25);
                    wait_ms(500);
                    bl(vector);
                    array.update(vector,25);
                    wait_ms(500);
                }
                
                if(con3>3){
                  if(con!=1){
                      con=con-1;
                      }
                }
                
            }
            
                
        }else{
            con3=0;
            three(vector,1);
            array.update(vector,25);
            if(pushbutton){
                   cor=cor-1; //si le medicas, te quiere un poco menos :( 
                   if(con==3){
                    p3(vector,1);
                    array.update(vector,25);
                    wait_ms(500);
                    bl(vector);
                    array.update(vector,25);
                    wait_ms(500);
                    p2(vector,1);
                    array.update(vector,25);
                    wait_ms(500);
                    con=2;
                    con2=4;
                    }
            }
            
                
            
            }
            
            wait_ms(500);
    
    }
    
    
    
    
    
}
