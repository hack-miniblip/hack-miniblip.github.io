// miniblip led matrix demo
 
#include "mbed.h"
#include "neopixel.h"
#include "colorbrigthness.h"

// Matrix led output pin
#define DATA_PIN P0_9
#define NLEDS 25
#define POTEN P0_22
#define BIRD 1
#define WALL 2
#define EMPTY 0
#define NUMEROCICLOSPORJUEGADA 7 //numero de ciclos de 100 ms entre cada avance del juego (Dificultad)

uint8_t tablero[NLEDS];
bool vacio = true;
uint8_t lineasBlanco=3;
bool lose = false;
neopixel::Pixel lista[NLEDS];
uint8_t bird =0;
DigitalIn   subir(P0_23);
uint8_t ciclos = 0;

//Funcion que pinta el tablero
void pintarTablero(){
    for(int j=0;j<NLEDS;j++){
        if(!lose){
            if(tablero[j]==WALL){
                lista[j].red = 0;
                lista[j].green = 255;
                lista[j].blue = 0;
            }
            else if(tablero[j]==BIRD){
                lista[j].red = 255;
                lista[j].green = 0;
                lista[j].blue = 0;
            }
            else{
                lista[j].red = 0;
                lista[j].green = 0;
                lista[j].blue = 255;
            }
        }
        else{   
            lista[j].red = 255;
            lista[j].green = 0;
            lista[j].blue = 255;
        }
    }    
}
void moverBird(){
    tablero[bird]=EMPTY;   
    if(subir){
        if(bird<4)bird++;
    }
    else if(bird!=0){
        bird--;
    }
    tablero[bird]=BIRD;   
}
void generarTablero(){
    uint8_t hueco = rand() % 5;
    //muevo el jugador
    moverBird();
    
    //compruebo si se acaba el juego
    if(tablero[bird+5]==WALL){
        lose=true;    
    }
    //Genero la posicion primera
    for(int i=0;i<5;i++){
        if(tablero[i]!=BIRD){
            tablero[i]=tablero[i+5];    
        }    
    }
    //genero el movimiento del tablero salvo la posicion ultima y la primera
    for(int i=5;i<NLEDS-5;i++){
        tablero[i]=tablero[i+5];
    }
    //Genero la ultima linea
    for(int i=0;i<5;i++){
        if(hueco==i || vacio){
            tablero[NLEDS-i-1]= EMPTY;    
        }
        else{
            tablero[NLEDS-i-1]= WALL;     
        }
    }
    if(lineasBlanco == 3){
        vacio= false;
        lineasBlanco= 0;    
    }else{
        lineasBlanco++;
        vacio=true;
    }
        
}

int main()
{
    // Turn off miniblip buzzer
    PwmOut speaker(P0_8);
    speaker=0.0;
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);
    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);    

    //Genero la variable que representa el potenciometro
    AnalogIn   ain(POTEN);

    
    for(int j=0;j<NLEDS;j++){
        tablero[j]= EMPTY;   
    }
    tablero[bird]=BIRD;   
     
    
    while (1) {
        if(ciclos==0){
            ciclos = NUMEROCICLOSPORJUEGADA;
            if(!lose)generarTablero();            
        }
        pintarTablero();
        colorbrigthness::calculatecolorMatrix(lista,NLEDS,255*ain);
        array.update(lista,NLEDS);
        ciclos--;
        wait_ms(100);        
    }
}
