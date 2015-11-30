//Código para la  #hackminiblip 

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

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

void void_matrix(neopixel::Pixel aux[25], int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

//r: intensidadRojo
//g: intensidadVerde
//b: intensidadAzul
void generaLetra(neopixel::Pixel vector[], char letra, int red, int green, int blue){

    /*
    * Cada letra tiene 5 valores en hexadecimal que representan en binario cada fila de la matrix 5x5 (aunque sobren 3 bits)
    */
    unsigned char espacio[5]={0x0, 0x0, 0x0, 0x0, 0x0};
    unsigned char a[5]={0x88, 0x88, 0xF8, 0x88, 0x70};
    unsigned char b[5]={0xF0, 0x88, 0xF0, 0x88, 0xF0};      
    unsigned char c[5]={0x78, 0x80, 0x80, 0x80, 0x78};   
    unsigned char d[5]={0xF0, 0x88, 0x88, 0x88, 0xF0};
    unsigned char e[5]={0xF8, 0x80, 0xF8, 0x80, 0xF8};
    unsigned char f[5]={0x80, 0x80, 0xE0, 0x80, 0xF8};    
    unsigned char g[5]={0x78, 0x88, 0xB8, 0x80, 0x78};
    unsigned char h[5]={0x88, 0x88, 0xF8, 0x88, 0x88};
    unsigned char i[5]={0x70, 0x20, 0x20, 0x20, 0x70};
    unsigned char j[5]={0x70, 0x88, 0x8,  0x8,  0x38};
    unsigned char k[5]={0x88, 0x88, 0xF0, 0xA0, 0x90}; 
    unsigned char l[5]={0xF8, 0x80, 0x80, 0x80, 0x80};
    unsigned char m[5]={0x88, 0x88, 0xA8, 0xD8, 0x88};
    unsigned char n[5]={0x98, 0xA8, 0xA8, 0xA8, 0xC8};
    unsigned char gn[5]={0x98, 0xA8, 0xA8, 0xA8, 0xC8};         // es la ñ
    unsigned char o[5]={0x70, 0x88, 0x88, 0x88, 0x70};
    unsigned char p[5]={0x80, 0x80, 0x78, 0x88, 0x78};
    unsigned char q[5]={0x78, 0x90, 0x90, 0x90, 0x60};
    unsigned char r[5]={0x88, 0x90, 0xF0, 0x88, 0xF0};    
    unsigned char s[5]={0xF0, 0x8,  0x70, 0x80, 0x78};
    unsigned char t[5]={0x20, 0x20, 0x20, 0x20, 0xF8};
    unsigned char u[5]={0x70,0x88,0x88,0x88,0x88};
    unsigned char v[5]={0x20,0x50,0x50,0x88,0x88};
    unsigned char w[5]={0x88,0xD8,0xA8,0x88,0x88};
    unsigned char x[5]={0x88,0x50,0x20,0x50,0x88};
    unsigned char y[5]={0x20,0x20,0x70,0x88,0x88};
    unsigned char z[5]={0xF8,0x80,0x70,0x8,0xF8};
        
    
    //unsigned char l0[0]=
    
        
    //Montamos un vector de vectores:
    unsigned char *vectorPunteros []={a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};
            
    //Con la letra recibida le restamos 26 y tenemos la posicion del vector.                        
    //Para moverlo por los vectores.  
    unsigned char *puntero; 
    if (letra==32) //Se trata de un espacio         
        puntero=espacio;
    else              
        //a= al valor 97
        puntero=vectorPunteros[(letra-'a')];
    
        
            //Vamos a recorrer todo el vector de bytes
            for(int i=0; i<5; i++){
                
                unsigned char elemento = puntero[i];
                unsigned int mask=0x80;
                //Nos movemos por 5 bits de los 8
                for(int x=0; x<5; x++){
                    if (elemento & mask)
                        fill_pixel(vector, x,i, red, green, blue);                                                                
                    //Desplazamos 1 bit
                    mask >>=1;
                }                
            }          
}    

void iluminaTexto(char cadena[], neopixel::PixelArray array){
      
       //Creamos un vector de pixeles.
       neopixel::Pixel letra[25];
        //Inicializamos el vector a 0
        void_matrix(letra);
        /*
        for(int i=0; i<25; i++){
            letra[i].red=0;
            letra[i].blue=0;
            letra[i].green=0;            
        }*/
        
        for(int i=0; i<strlen(cadena); i++){
            //Generamos la letra en el vector letra        
            generaLetra(letra, cadena[i], 30, 0 , 0 );
            //Iluminamos la matriz
            array.update(letra, 25);
            //Esperamos un seg
            wait_ms(300); 
            //Reseteamos la matriz
            void_matrix(letra);
            /*
            for(int j=0; j<25; j++){
                letra[j].red=0;
                letra[j].blue=0;
                letra[j].green=0;            
            }
            */
            //Iluminamos la matriz a 0 (no la iluminamos = "la apagamos")
            array.update(letra, 25);
            //Esperamos otro segundo.                                    
            wait_ms(30);   
        }
        wait_ms(600);
        
        
}    

int main()
{
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    //Se está creando un objeto de tipo PixelArray y se está nombrando como array a la que se le está pasando DATA_PIN
    neopixel::PixelArray array(DATA_PIN); 
    
    char greeting[] = "abcdefghijklmnopqrstuvwxyz";

    while (1) {        
        iluminaTexto(greeting, array);
    }
}
