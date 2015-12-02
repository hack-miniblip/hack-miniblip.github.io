//Código para la  #hackminiblip

#include "mbed.h"
#include "neopixel.h"
#include <ctype.h>

// Matrix led output pin
#define DATA_PIN P0_9
#define ANALOG_POTENTIOMETER P0_22
AnalogIn   ain(ANALOG_POTENTIOMETER);

/*
Función: wait_potenciometro
Parámetros: tiempo (int)
Descripción: Dado un tiempo, en milisegundos, aplicaremos, usando el potenciómetro, un cambio en la velocidad, desde 0 hasta la variable tiempo
*/

void wait_potenciometro(int tiempo){
        // Rainbow delay
        float pot = ain.read();
        wait_ms(tiempo*pot);
}

/*
Declaramos esta matriz para hacer el ticker tape, ya que, para evitar problemas de memoria utilizaremos una matriz dinámica
*/

const int TAM=(25+5)*3; //3 letras con sus separadores
neopixel::Pixel frase[TAM]; 

/*
Función: fill_pixel
Parámetros: buffer[] (Pixel), x (int), y (int), red (int), green (int), blue (int), prol (int), retardo (int)
Descripción: Almacenamos en la posición (x,y) de la matriz de leds (el buffer el pixeles) la tupla rgb (red, green, blue)
Ampliación: Podemos utilizar las variables prol (de prolongación) y retardo para lo siguiente:
			Con prol decimos si queremos añadirlo a la derecha de la matriz, cuantas veces (preparado para matrices de 5x5i con i perteneciente a los naturales.
			Con retardo le decimos si queremos dejar alguna columna vacía, es util porque a la hora de meter letras podemos dejar espacio entre estas.
*/

void fill_pixel(neopixel::Pixel buffer[], int x, int y, int red, int green, int blue, int prol=0, int retardo=0){
   
    int orden=x+retardo;
    while(orden>=5){
        orden-=5;
        prol++;
    }

    int posicion=orden+y*5 + 25*prol;
    buffer[posicion].red=red;
    buffer[posicion].green=green;
    buffer[posicion].blue=blue;
   
}

/*
Función: void_matrix
Parámetros: aux[] (Pixel), tam (int)
Descripción: "Apagamos" una matriz de pixeles (la ponemos a 0)
Ampliación: Podemos decirle el tamaño que tiene la matriz, para poder vaciar también matrices distintas de las 5x5 por defecto
*/

void void_matrix(neopixel::Pixel aux[25], int tam=25){
   
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

/*
Función: merge_matrix
Parámetros: letra[25] (Pixel), frase[] (Pixel), posicion (int), retardo (int)
Descripción: introducimos la matriz letra dentro de la matriz frase en la posición indicada.
Ampliación: Podemos darle también un retardo para generar separación entre letras
*/

void merge_matrix(neopixel::Pixel letra[25], neopixel::Pixel frase[], int posicion, int retardo=0){
    int i=0;
    for(int y=0;y<5;y++)
        for(int x=0;x<5;x++){
            fill_pixel(frase,x,y,letra[i].red,letra[i].green,letra[i].blue,posicion, retardo);
            i++;
        }
        
}

/*
Función: get_pixel
Parámetros: frase[] (Pixel), x (int), y (int)
Descripción: Nos devuelve el Pixel de la posición (x,y) de la matriz frase
*/

neopixel::Pixel get_pixel(neopixel::Pixel frase[],int x, int y){
    int i=0;
    while(x>=5){
        i++;
        x-=5;
    }
    int posicion= x+y*5 + 25*i;
    return frase[posicion];
}

/*
Función: extraer_matriz
Parámetros: frase[] (Pixel), salida[25] (Pixel), posicion (int)
Descripción: Copia la submatriz 5x5 de la posición correspondiente de frase y la almacena en salida
*/

void extraer_matriz(neopixel::Pixel frase[],neopixel::Pixel salida[25],int posicion){
    int i=0;
    for(int y=0;y<5;y++)
        for(int x=posicion; x<5+posicion;x++){
            salida[i]=get_pixel(frase,x,y);
            i++;
        }
}
/*
Función: extraer_matriz_bucle
Parámetros: frase[] (Pixel), salida[25] (Pixel), posicion (int)
Descripción: Hace lo mismo que extraer_matriz, solo que si posicion fuera a generar una violación de segmento empieza por el principio
*/
void extraer_matriz_bucle(neopixel::Pixel frase[],neopixel::Pixel salida[25],int posicion){
    int i=0;
    for(int y=0;y<5;y++)
        for(int x=posicion; x<5+posicion;x++){
            if(x<TAM/5)
                salida[i]=get_pixel(frase,x,y);
            else
                salida[i]=get_pixel(frase,x-TAM/5,y);
            i++;
        }
}


/*
Función: generaLetra
Parámetros: vector[] (Pixel), letra (char), red (int), green (int), blue (int)
Descripción: Genera una matriz 5x5 que representa el carácter almacenado en letra y lo guarda en vector con la configuración rgb introducida
r: intensidadRojo
g: intensidadVerde
b: intensidadAzul
*/
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
    //unsigned char gn[5]={0x98, 0xA8, 0xA8, 0xA8, 0xC8};         // es la ñ
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

/*
Función: iluminaTexto
Parámetros: cadena[] (char), array (PixelArray)
Descripción: Imprime una cadena letra a letra por parpadeo
*/

void iluminaTexto(char cadena[], neopixel::PixelArray array){
     
       //Creamos un vector de pixeles.
       neopixel::Pixel letra[25];
        //Inicializamos el vector a 0
        void_matrix(letra);
       
        for(int i=0; i<strlen(cadena); i++){
            //Generamos la letra en el vector letra       
            generaLetra(letra, tolower(cadena[i]), 30, 0 , 0 );
            //Iluminamos la matriz
            array.update(letra, 25);
            //Esperamos un seg
            
            wait_potenciometro(1000);
            //Reseteamos la matriz
            void_matrix(letra);
            //Iluminamos la matriz a 0 (no la iluminamos = "la apagamos")
            array.update(letra, 25);
            //Esperamos otro segundo.  
            wait_potenciometro(300);
        }
        wait_potenciometro(600);
       
       
}   

/*
Función: iluminaFrase
Parámetros: cadena[] (char), array (PixelArray)
Descripción: Hace lo mismo que iluminaTexto pero en vez de parpadeo, aplica el método ticker tape
*/

void iluminaFrase(char cadena[], neopixel::PixelArray array){
     
       //Creamos un vector de pixeles.
       int tamano = (strlen(cadena)+1)*25;//(strlen(cadena)+1)*25 si queremos que tenga una separación al final
       neopixel::Pixel letra[25];
       neopixel::Pixel aux[25];
       int transposiciones;
        //Inicializamos el vector a 0
        void_matrix(letra);
        void_matrix(aux);
        void_matrix(frase,TAM);
        
    
        for(int i=0; i<3; i++){
            //Generamos la letra en el vector letra       
            generaLetra(letra, tolower(cadena[i]), 30, 0 , 0);
            merge_matrix(letra,frase,i,i);
            void_matrix(letra);
        }
        
        int voy_por=3;
        int sig=0;
        
        transposiciones=(strlen(cadena)-1)*5+strlen(cadena);// añadir +1 si queremos que tenga una separación al final
        

        for(int i=0;i<transposiciones;i++){
            extraer_matriz_bucle(frase,aux, i%18);
            //Iluminamos la matriz
            array.update(aux, 25);
            //Esperamos un seg
            wait_potenciometro(300);
            if(i!=0 && i%6==0 && cadena[voy_por]!='\0'){
                void_matrix(letra);
                generaLetra(letra, tolower(cadena[voy_por]), 30, 0 , 0);
                merge_matrix(letra,frase,sig,sig);
                if(sig==2)
                    sig=0;
                else
                    sig++;
                voy_por++;
            }
            //Reseteamos la matriz
            void_matrix(aux);
        }
        wait_potenciometro(600);
    
       
} 

int main()
{
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    //Se está creando un objeto de tipo PixelArray y se está nombrando como array a la que se le está pasando DATA_PIN
    neopixel::PixelArray array(DATA_PIN);
   
    char todo[] = "abcdefghijklmnopqrstuvwxyz";
    char greeting[] = "hackingminiblip";
    while(1)
        iluminaFrase(greeting, array);
	//iluminaTexto(greeting, array);
}
