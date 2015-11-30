include "mbed.h"


#define MUTE  0.0
#define END   1.0

//-- Notes and frequencies (Hz)
#define DO_4  261.626
#define MI_4  329.628 
#define SOL_4 391.995 
#define SI_4  493.883
#define DO_5  523.251

//-- Tempo
#define TEMPO 200

//-- Default volume
#define VOL 0.4

//-- Notes for the imperial march. MUTE means silence.  END for marking the end
float notes[] = {MI_4, MUTE, MI_4, MUTE, MI_4, MUTE, DO_4, SOL_4, MI_4, MUTE, DO_4,  SOL_4,  MI_4, MUTE, 
                 SI_4, MUTE, SI_4, MUTE, SI_4, MUTE, DO_5, SOL_4, MI_4, MUTE, DO_4,  SOL_4,  MI_4, END};
                 
//--  Notes duration                 
float tempo[] = {2   ,    1,    2,    1,    2,   1,    2,     1,    2,    1,    2,      1,     2,    3,  
                 2   ,    1,    2,    1,    2,   1,    2,     1,    2,    1,    2,      1,     2,    0};

//-- Declare speaker object
PwmOut speaker(P0_8);

void play()
{
  int i=0;
  
  //-- Reproduce all the notes in the list
  while(notes[i] != END) {
    
    //-- If silence, turn of the PWM
    if (notes[i] == MUTE) {
      speaker = 0.0;
    }
    else {
      speaker.period(1.0/notes[i]);  //-- Note
      speaker = VOL;                 //-- Set the volume
    }  
    
    //-- Note duration
    wait_ms(TEMPO * tempo[i]);
    
    //-- Move to the next note
    i++;
  }  
  
  //-- Turn off the speacker
  speaker = MUTE;
}

int main()
{
    //-- Play the song!!
    play();
    
    //-- Do nothing more
    while(1) ;
}


