#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

struct Note
{
	char name;
	float frequency;
};

// list of notes that will be used.
#define NUM_NOTES 3
struct Note notes[NUM_NOTES] =
{
	{'C', 130.82f},
	{'D', 146.83f},
	{'E', 164.81f}
};

// function for drawing out the notes, and highlighting the note the user selected
void draw_notes(char active_note)
{
	for (int i=0; i<NUM_NOTES; i++)
	{
		if (notes[i].name == active_note)
		{
			// highlights the active note red
			attron(COLOR_PAIR(1));
			mvprintw(getmaxy(stdscr)-NUM_NOTES+i, 1, "%c: %f", notes[i].name, notes[i].frequency);
			attroff(COLOR_PAIR(1));
		}
		else
		{
			// colors the rest of the notes white.
			attron(COLOR_PAIR(0));
			mvprintw(getmaxy(stdscr)-NUM_NOTES+i, 1, "%c: %f", notes[i].name, notes[i].frequency);
			attroff(COLOR_PAIR(0));
		}
	}

	// makes any changes visible, or whatever. I don't even know if I need this,
	// but I feel like I do. I will leave it here for now.
	refresh();
}

int main()
{
	// init curses
	initscr();
	refresh();
	noecho();

	// color stuff
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	// puts the notes down, with a number that won't highlight any notes. (maybe
	// i will change it so that a note will be always active.)
	draw_notes(0);

	// TODO create a callback function or something so that the sound generator
	//   knows what frequency to play the tone at.
	
	// main input loop, self explanetory (hopefully)
	char quit = 1;
	while (quit)
	{
		char input = getch();
		
		switch (input)
		{
			case 'c' :
				draw_notes('C');
				break;
			case 'd' :
				draw_notes('D');
				break;
			case 'e' :
				draw_notes('E');
				break;
			case 'q' :
				quit = 0;
				break;
			
		}
	}

	// clean up and exit
	endwin();
	return 0;
}
