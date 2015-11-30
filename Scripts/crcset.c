#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fw, count, crc;
    char buf[28];

    fw = open(argv[1], O_RDWR);
    // read fist 28 bytes
    read(fw, &buf, 28);

    // find 2's complement of entries 0 to 6
    for (count=0, crc=0; count < 7; count++) {
            crc += *((int*)(buf+count*4));
    }
    crc = (~crc) + 1;

    // write it at offset 0x0000001C 
    lseek(fw, 0x0000001C, SEEK_SET);
    write(fw, &crc, 4);
    close(fw);

    return 0;
}
