#include "edit.h"

void initialize_editor()									//Initialize NCurses
{
	initscr();										//Initialize screen and curses mode
	if (has_colors() == FALSE)				//Check to see if the console supports colored print, if not, then execute the following segment
	{
		endwin();									//Un-initialize the window
		fprintf(stderr, "ERROR: This console does not support colored printing\n");	//Provide an error message stating that it does not support colored printing
		exit(1);									//Exit the application
	}
	start_color();						//Otherwise, carry on wayward, initialize color and print the outline to the editor
	init_pair(EDITOR_SCHEME, COLOR_BLACK, COLOR_WHITE);	//Initialize color pair of black text on a white background (for editor)
	init_pair(BOUNDARY_SCHEME, COLOR_BLACK, COLOR_CYAN);	//Initialize color pair of black text on a cyan background (for top and bottom boundaries)
}

void print_editor(struct Window *w)
{
	getmaxyx(stdscr, w->height, w->width);	//Get the dimensions of current screen (stdscr) and place those values into the Window structure
	
	attrset(COLOR_PAIR(EDITOR_SCHEME));			//Set color pair for editor (black text on white background)
	move(0, 0);
	for (int i = 0; i < w->height * w->width; i++) printw(" ");
	
	line_print(0, "Unnamed Text Editor", w);			//Print a Cyan line from the given y position (0, representing the first line) and with the given width
	line_print(w->height - 1, "[Esc] Quit  [F1] Help  [F2] Save  [F3] Open  [F4] New  [F5] Delete line", w);	//With '0' being the first row, the variable "rows" minus one should represent the last row in the given console
}

void print_contents(struct Window *w, struct Cursor *c, struct File *f)
{
	
}

void line_print(int r, char *t, struct Window *w)	//Print a Cyan line at row "r" with text "t", with restrictions of Window "w"
{
	attrset(COLOR_PAIR(BOUNDARY_SCHEME));		//Turn on attribute for the boundary color scheme
	move(r, 0);					//Set cursor to the beginning of the line for the y-position "row"
	printw(t);					//Print the given message
	for (int i = strlen(t); i < w->width; i++)	//Repeat the following code segment until the rest of the bar is full
	{
		printw(" ");			//Print the rest without any characters in the foreground
	}
	move(r, 0);					//Move the cursor back to the beginning of the line of the first row printed
}
