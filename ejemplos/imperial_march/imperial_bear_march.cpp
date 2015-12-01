// miniblip play notes with interrupts - Not tested with led matrix
// For documentation see http://mbed.org/users/4180_1/notebook/using-a-speaker-for-audio-output/

// Code from @pighixxx. The code has been modified by @unintendedbear to play the Imperial March from Star Wars.
// Notes and tempo taken from http://pasted.co/e525c1b2 and modified by me
// Needs SongPlayer.h
// Needs a sticker on the buzzer for better sound

#include "mbed.h"
#include "SongPlayer.h"

// Third and Fourth scale notes
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88

// Silence
#define silence 100000

// Tempos
#define H 1 //half 2/4
#define Q 0.4 //quarter 1/4 
#define E 0.2   //eighth 1/8
#define S 0.1 // sixteenth 1/16
#define W 2 // whole 4/4

//Set up notes and durations for sample song to play
// A 0.0 duration note at end terminates song play
float note[136]= {LA3, silence, LA3, silence, LA3, silence, C4, silence, F3, silence, LA3, silence,
                C4, silence, F3, silence, LA3, silence,
                E4, silence, E4, silence, E4, silence, C4, silence, F4, silence, Ab3, silence,
                C4, silence, F3, silence, LA3, silence,
                LA4, silence, LA3, silence, LA3, silence, LA4, silence, Ab4, silence,
                G4, silence, Gb4, silence, E4, silence, F4, silence, silence,
                Bb3, silence, Eb4, silence, D4, silence,
                Db4, silence, C4, silence, B3, silence, C4, silence, silence,
                F3, silence, Ab3, silence, F3, silence,
                LA3, silence, C4, silence, LA3, silence, E4, silence, C4, 0.0
                };
float duration[136]= {Q, E, Q, E, Q, E, E+S, S, E, S,
                    Q+S, E, E+S, S, E, S, Q+S, E,
                    Q, E, Q, E, Q, E, E+S, S, E, S,
                    Q+S, E, E+S, S, E, S, Q+S, E,
                    E, E, Q, E+S, E+S, E, Q, E, E+S, E,
                    S, S, S, S, S, S, E, E, E,
                    E+S, E, Q, E, E+S, S,
                    S, S, S, S, S, S, E, E, E,
                    E+S, E, Q, E, E+S, S,
                    E, S, Q+S, E, E+S, S, E, S, Q+S, 0.0
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


