/*
 * The Game of Life
 *
 * Using 5x5 LED grid. Initial position is defined by the potenciometer
 *
 * Original code: http://www.cs.utexas.edu/users/djimenez/utsa/cs1713-3/c/life.txt
 *
 */
#include "mbed.h"
#include "neopixel.h"

/* dimensions of the screen */

#define BOARD_WIDTH	 5
#define BOARD_HEIGHT 5

// Matrix led output pin
#define MATRIX_PIN P0_9
#define NLEDS BOARD_WIDTH * BOARD_HEIGHT

// Potenciometer
AnalogIn pot(P0_22);

neopixel::Pixel buffer[NLEDS];
neopixel::PixelArray array(MATRIX_PIN);

void set_pixel(uint32_t position, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[position].red = red;
  buffer[position].green = green;
  buffer[position].blue = blue;
}

/* set everthing to random values */

void initialize_board (int board[][BOARD_HEIGHT]) {
	int	i, j;

	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++)
		board[i][j] = ! (rand() % 3);
}

/* add to a width index, wrapping around like a cylinder */

int xadd (int i, int a) {
	i += a;
	while (i < 0) i += BOARD_WIDTH;
	while (i >= BOARD_WIDTH) i -= BOARD_WIDTH;
	return i;
}

/* add to a height index, wrapping around */

int yadd (int i, int a) {
	i += a;
	while (i < 0) i += BOARD_HEIGHT;
	while (i >= BOARD_HEIGHT) i -= BOARD_HEIGHT;
	return i;
}

/* return the number of on cells adjacent to the i,j cell */

int adjacent_to (int board[][BOARD_HEIGHT], int i, int j) {
	int	k, l, count;

	count = 0;

	/* go around the cell */

	for (k=-1; k<=1; k++) for (l=-1; l<=1; l++)

		/* only count if at least one of k,l isn't zero */

		if (k || l)
			if (board[xadd(i,k)][yadd(j,l)]) count++;
	return count;
}

void play (int board[][BOARD_HEIGHT]) {
/*
	(copied this from some web page, hence the English spellings...)

	1.STASIS : If, for a given cell, the number of on neighbours is
	exactly two, the cell maintains its status quo into the next
	generation. If the cell is on, it stays on, if it is off, it stays off.

	2.GROWTH : If the number of on neighbours is exactly three, the cell
	will be on in the next generation. This is regardless of the cell's 		current state.

	3.DEATH : If the number of on neighbours is 0, 1, 4-8, the cell will
	be off in the next generation.
*/
	int	i, j, a, newboard[BOARD_WIDTH][BOARD_HEIGHT];

	/* for each cell, apply the rules of Life */

	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++) {
		a = adjacent_to (board, i, j);
		if (a == 2) newboard[i][j] = board[i][j];
		if (a == 3) newboard[i][j] = 1;
		if (a < 2) newboard[i][j] = 0;
		if (a > 3) newboard[i][j] = 0;
	}

	/* copy the new board back into the old board */

	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++) {
		board[i][j] = newboard[i][j];
	}
}

/* print the life board */

void print (int board[][BOARD_HEIGHT]) {
	int	i, j;

	for (j=0; j<BOARD_HEIGHT; j++) {
		for (i=0; i<BOARD_WIDTH; i++) {
            set_pixel(5 * i + j, 0, 0 , board[i][j] ? 50 : 0);
		}
	}

    array.update(buffer, NLEDS);
}

/* main program */

int main () {
	int	board[BOARD_WIDTH][BOARD_HEIGHT];

	srand(pot.read_u16());

	initialize_board (board);
    print (board);

	while (1) {
		print (board);
		play (board);
		wait_ms (500);
	}
}
