// miniblip play notes with interrupts - Not tested with led matrix
// For documentation see http://mbed.org/users/4180_1/notebook/using-a-speaker-for-audio-output/

#include "mbed.h"
#include "SongPlayer.h"

//You need SongPlayer.h created by https://developer.mbed.org/users/pighixxx/

#define DO 65.41*2*2*2
#define SI 123.47*2*2*2
#define RE 73.42*2*2*2
#define LA 110.00*2*2*2
#define SOL 98.00*2*2*2

#define silencio 100000


#define BLANCA 0.5
#define NEGRA  0.25
#define TSILENCIO 0.15

//Set up notes and durations for sample song to play
// A 0.0 duration note at end terminates song play
float note[]= {
SI,
silencio,
DO,
silencio,
RE,
silencio,
RE,
silencio,
DO,
silencio,
SI,
silencio,
LA,
silencio,
SOL,
silencio,
SOL,
silencio,
LA,
silencio,
SI,
silencio,
SI,
silencio,
LA,
0.0
};

float duration[]= {
                    BLANCA,
                    TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
NEGRA,
TSILENCIO,
BLANCA,
TSILENCIO,
BLANCA, 
0.0
                    };

int main()
{
    // Buzzer pin
    SongPlayer mySpeaker(P0_8);
    // Start song and return once playing starts
    mySpeaker.PlaySong(note,duration);
    // loops forever while song continues to play to end using interrupts
    while(1) {
        wait(.1);
    }
}


