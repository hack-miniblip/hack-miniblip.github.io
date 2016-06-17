# hack-miniblip.github.io

Hackea la MiniBlip, repo para el hackatón CircoLab/BQ/Miniblip

Puedes ver este contenido en versión [web](http://hack-miniblip.github.io/).

La [miniblip es](https://github.com/bqlabs/miniBLIP) una placa creada
por [BQ](http://github.com/bqlabs) para *wearables* y lo que
surja. Tiene dos botones, 5 botones capacitivos y un array de
leds. Está basada en un ARM Cortex-M0 a 48MHz, el LPC11U24 que incluye 32KB FLASH y 8KB RAM y funciona a 48MHz ([más detalles](https://developer.mbed.org/platforms/mbed-LPC11U24/#features))

## Cómo comenzar

Conecta la placa a tu USB. Si pulsas el botón rectangular más cercano al
USB *mientras estás enchufándolo* se pondrá en "modo programación" y aparecerá en tu ordenador como
un USB drive. El fichero ``firmware.bin`` será el que habrá que sustituir
por tus propios ficheros cuando los compiles.

## Creando y compilando un fichero.

Se usa el [entorno de desarrollo MBED](http://developer.mbed.org). Lo
primero es darse de alta en el mismo.

Se trabaja sobre el [compilador](https://developer.mbed.org/compiler/)
para compilar los ficheros. El tipo de plataforma es **MBED LPC11U24**,
será la que hay que seleccionar cuando se crea un nuevo proyecto.

Podemos empezar por los
[proyectos del autor de la placa, Alberto Piganti](https://developer.mbed.org/users/pighixxx/),
por ejemplo,
[`blip_rainbow`](https://developer.mbed.org/users/pighixxx/code/blip_rainbow/). Se
importa en el compilador pulsando en "Import this program", recordando
seleccionar la plataforma anterior si te lo pide e importando las
librerías, en este caso PixelLibrary, también si lo pide.

Se compila pulsando en el botón correspondiente y se descarga el
fichero.

## Guardando el fichero en la placa


1. Mira donde se ha montado la placa escribiendo    

```shell
	mount
```

2. Una vez sabemos donde está nuestra miniblip (en mi caso /dev/sdb)    

```shell
	sudo dd if=nuevo_firmware.bin of=/dev/sdb bs=512 seek=4 conv=notrunc
```

3. Finalmente, desmontamos la miniblip, bien con el entorno gráfico o con terminal

```
umount /dev/sdb

```

Usando el script [miniblip_loader](Scripts/miniblip_loader.sh) podemos cargar nuestros programas automáticamente    
```shell
	$ miniblip_loader.sh + [firmware.bin]`
```

### **OJO:** Si a veces ya no se monta en ningun puerto, reiniciad.

## Y listo

Al conectar de nuevo el sistema empezará a funcionar el nuevo
programa.

## Binarios

Puedes ver los binarios en [este repositorio](https://github.com/hack-miniblip/apps/). Si quieres subir el tuyo propio, haz un *fork*, [incorpora tu binario siguiendo las instrucciones](https://github.com/hack-miniblip/apps/blob/master/README.md) y haz un pull request.

## Para añadir a este repo

Hacer un fork. Una vez hecho

	git remote add upstream git@github.com:hack-miniblip/hack-miniblip.github.io.git

(o equivalente en `https`).

Y recordad antes de hacer cualquier cambio y subirlo

	git pull upstream master

Podéis hacer un pull request a este repo o un simple enlace a este README.

## Un cookbook

[Cookbook](cookbook.md) con cosillas

## Compilándolo en local

Te puedes descargar el programa completo del entorno pulsando con el
botón de la derecha y dándole a "Export program", pero necesitarás
algo más para compilar.

En [este tutorial](http://gnuarmeclipse.github.io/toolchain/install/)
vienen instrucciones para crear el entorno de programación local. 

1. Instálate el entorno de programación siguiendo
   [estas instrucciones](https://launchpad.net/gcc-arm-embedded). En
   esa página hay enlaces a un PPA (para instalación y actualización
   desde repo) o te lo puedes bajar en .zip. En algunas versiones de
   Ubuntu no será necesario, basta con hacer

	sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi

2. Descomprime el .zip que te hayas bajado del entorno en un fichero. Edita el `Makefile` y edita esta línea para poner

    GCC_BIN = /usr/bin/

que es donde se instala el compilador.

Puede que te dé algún problema del estilo

```
/usr/bin/../lib/gcc/arm-none-eabi/4.9.3/../../../../arm-none-eabi/bin/ld: colorines.elf section `.text' will not fit in region `FLASH'
/usr/bin/../lib/gcc/arm-none-eabi/4.9.3/../../../../arm-none-eabi/bin/ld: region `FLASH' overflowed by 208 bytes
```

En cuyo caso tendrás que recortar el tamaño del fichero, quitando variables e info de depuración, por ejemplo.

Si no te da ningún problema, te generará un `.bin`. Ya casi estás. Tendrás que pillarte el [programa `crcset.c`](Scripts/crcset.c) y compilarlo. Este programa pone los bits de comprobación correctamente, para evitar el error que sale al final:

    *****
	***** You must modify vector checksum value in *.bin and *.hex files.
	*****

Con eso, ya haces

	./crcset nombre-del-programa.bin

¡Y ya estás listo! El programa `crcset` está incluido en este repo.

En el
[repositorio de CirCoLab](https://github.com/circolab/miniblip_examples)
tienes también un ejemplo, `colorines`, con todos los ficheros
necesarios. Simplemente edita el programa `main.cpp` en ese directorio
y escribe Make para crear el fichero de salida; aún así, tendrás que
tener los compiladores necesarios instalados.
