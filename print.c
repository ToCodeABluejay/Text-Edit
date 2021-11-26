/* "print.c" - Gabriel Bauer (@ToCodeABluejay)
 * 
 *Copyright (c) 2021 Gabriel Bauer (@ToCodeABluejay)
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 */
#include "edit.h"

void initialize_editor()	//Initialize NCurses
{
	initscr();						//Initialize screen and curses mode
	if (has_colors() == FALSE)				//Check to see if the console supports colored print, if not, then execute the following segment
	{
		endwin();									//Un-initialize the window
		fprintf(stderr, "ERROR: This console does not support colored printing\n");	//Provide an error message
		exit(1);									//Exit the application
	}
	start_color();						//Otherwise, carry on wayward, initialize color and print the outline to the editor
	init_pair(EDITOR_SCHEME, COLOR_BLACK, COLOR_WHITE);	//Initialize color pair of black text on a white background (for editor)
	init_pair(BOUNDARY_SCHEME, COLOR_BLACK, COLOR_CYAN);	//Initialize color pair of black text on a cyan background (for top and bottom boundaries)
}

void border_line_print(int r, char *t, struct Window *w)	//Print a Cyan line at row "r" with text "t", with restrictions of Window "w"
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

void content_line_print(int r, struct Window *w, struct Cursor *c)	//Print line at row "r" with text "t", with restrictions and contents of Window "w", using cursor position x,y
{
	int i = 0, j;
	
	//TODO: Current line print function
	/*if (r==c->y)
		current_line_print();*/
	
	attrset(COLOR_PAIR(EDITOR_SCHEME));		//Turn on attribute for the boundary color scheme
	move(r+1, 0);					//Set cursor to the beginning of the line for the y-position "row" -- all being relative to editor bounds
	
	for (j = get_line_number_pos(w->top, w->contents); i < w->width-1 && i < get_end_of_line(j, w->contents); i++)	//Repeat the following code segment until the rest of the bar is full
	{
		addch(w->contents[j+i]);
	}
	if (i==w->width-1)
		addch('>');
}

void print_editor(struct Window *w)
{
	getmaxyx(stdscr, w->height, w->width);	//Get the dimensions of current screen (stdscr) and place those values into the Window structure
	
	attrset(COLOR_PAIR(EDITOR_SCHEME));			//Set color pair for editor (black text on white background)
	move(0, 0);
	for (int i = 0; i < w->height * w->width; i++) printw(" ");
	
	border_line_print(0, "Unnamed Text Editor", w);			//Print a Cyan line from the given y position (0, representing the first line)
	border_line_print(w->height - 1, "[Esc] Quit  [F1] Help  [F2] Save  [F3] Open  [F4] New  [F5] Delete line", w);	//Print the bottom line
}

void print_contents(struct Window *w, struct Cursor *c, struct File *f)
{
	if (!w->top)
	{
	}
}
