# pixels

* Los leds son de tipo WS2812, direccionables individualmente y conectados por SPI

* Utiliza la librería [PixelArray](https://developer.mbed.org/users/JacobBramley/code/PixelArray/) (derivada de Neopixel de Adafruit)

* Para definir un color se usa una estructura llamada PixelArray


    struct Pixel {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

* Existen otras librerías que facilitan el uso como [easyNeo](https://developer.mbed.org/users/dannellyz/code/easyNeo/file/2d59dae9531d/easyNeo.h)

* Podemos actualizar un pixel con cualquiera de los 2 métodos update

    * update(generator) donde generator es una función que hace los cambios al array [Ejemplo de pighixxx](https://developer.mbed.org/users/pighixxx/code/blip_rainbow/file/2d84c8262139/main.cpp)

    * update(Pixel[] array, longitud)

    donde decimos los nuevos valores de los pixels

    Ejemplo de actualización por array


      #include "mbed.h"
      #include "neopixel.h"

      #define DATA_PIN P0_9
      #define NLEDS 25

      // Mal ejemplo de como programar cuando tienes poca memoria
      neopixel::Pixel buffer[NLEDS];

      void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue)
      {
          buffer[posicion].red=red;
          buffer[posicion].green=green;
          buffer[posicion].blue=blue;
      }

      int main() {

          neopixel::PixelArray array(DATA_PIN);

          for(int tono=0;tono<256;tono+=10)
          {
            for(int i=0;i<NLEDS;i++)
            {
               setPixel(i,tono,tono,tono);
             }
             array.update(buffer, NLEDS);
          }
      }
