Los leds son de tipo WS2812, direccionables individualmente y conectados por SPI

Utiliza la librería [PixelArray](https://developer.mbed.org/users/JacobBramley/code/PixelArray/) (derivada de Neopixel de Adafruit)


Para definir un color se usa una estructura llamada PixelArray

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

Podemos actualizar un pixel con cualquiera de los 2 métodos update

update(generator) donde generator es una función que hace los cambios al array

update(Pixel[] array, longitud)

donde decimos los nuevos valores de los pixels
