# hack-miniblip.github.io

Hackea la MiniBlip, repo para el hackatón CircoLab/BQ/Miniblip

La [miniblip es](https://github.com/bqlabs/miniBLIP) una placa creada
por [BQ](http://github.com/bqlabs) para *wearables* y lo que
surja. Tiene dos botones, 5 botones capacitivos y un array de
leds. Está basada en un ARM Cortex-M0 a 48MHz. Incluye 32KB FLASH, 8KB RAM

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
##LINUX Actualizado funciona!

1. Mira donde se ha montado la placa escribiendo    
    `mount` 

2. Una vez sabemos donde está nuestra miniblip (en mi caso /dev/sdb)    
    `sudo dd if=nuevo_firmware.bin of=/dev/sdb bs=512 seek=4 conv=notrunc`

3. Finalmente, desmontamos la miniblip, bien con el entorno gráfico o con terminal    
    `umount /deb/sbd`


Usando el script [miniblip_loader](miniblip_loader.sh) podemos cargar nuestros programas automáticamente    
    `bash miniblip_loader.sh + [firmware.bin]`
	
	
## METODO VIEJO NO FUNCIONA CORRECTAMENTE

Se borra el fichero ``firmware.bin`` y se arrastra el nuevo fichero a la
placa.

En Linux y OSX hay que
[configurar el sistema para que monte la placa de una forma determinada](https://developer.mbed.org/handbook/Mounting-with-sync),
de forma que grabe en la misma en el momento que se escriba, no en el
momento que se desmonte. Si no no lo grabará. Para eso, tienes que hacer lo siguiente

1. Copiar [`60-miniblip.rules`](60-miniblip.rules) a `/etc/udev/rules.d/` . Es decir
```shell
	sudo cp 60-miniblip.rules /etc/udev/rules.d/
	sudo udevadm control --reload
```
2. Editar con privilegios de administrador el fichero `/etc/fstab` añadiendo
```shell
	/dev/MINIBLIP /media/<mi_nombre_de_usuario>/MINIBLIP vfat noauto,rw,user,sync 0 0
```

La primera línea crea un enlace simbólico para que el dispositivo se pueda identificar fácilmente, y la segunda lo usa para montarlo en una dirección persistente y con los privilegios necesarios.

También puedes utilizar el fichero ``install.sh`` y ejecutarlo como administrador (con ``sudo``).
```shell
chmod +x install.sh
sudo ./install.sh
```

## Y listo

Al conectar de nuevo el sistema empezará a funcionar el nuevo
programa.

## [Cookbook](cookbook.md)
