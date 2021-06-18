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

int rows, columns, y, x;

int cursor_pos[2];

string file_location, file_contents, editor_contents, filename;

bool writeable, file_changed;

void initialize_editor()	//Initialize the UI of the text editor
{
	initscr();						//Initialize screen and curses mode
	if (has_colors() == FALSE)						//Check to see if the console supports colored print, if not, then execute the following segment
	{
		endwin();							//Un-initialize the window
		fprintf(stderr, "TEXT: This console does not support colored printing\n");	//Provide an error message stating that it does not support colored printing
		exit(1);							//Exit the application
	}
	start_color();						//Otherwise, carry on wayward, initialize color and print the outline to the editor
	getmaxyx(stdscr, rows, columns);			//Get the dimensions of current screen (stdscr) and place those values into variables "rows" and "columns" defined in CORAL_H
	init_pair(EDITOR_SCHEME, COLOR_BLACK, COLOR_WHITE);	//Initialize color pair of black text on a white background (for editor)
	init_pair(BOUNDARY_SCHEME, COLOR_BLACK, COLOR_CYAN);	//Initialize color pair of black text on a cyan background (for top and bottom boundaries)
	line_print(0, TOP_WIDTH);				//Print a Cyan line from the given y position (0, representing the first line) and with the given width
	print_bar(tBAR);
	line_print(rows - BOTTOM_WIDTH, BOTTOM_WIDTH);		//With '0' being the first row, the variable "rows" minus one should represent the last row in the given console
	print_bar(bBAR);
	attrset(COLOR_PAIR(EDITOR_SCHEME));			//Set color pair for editor (black text on white background)
	move(TOP_WIDTH, 0);
	for (int i = 0; i < (rows - (BOTTOM_WIDTH + TOP_WIDTH)) * columns; i++)			//For as many times as there are pixels in the editor space, repeat the following segment
		printw(" ");						//Print blank spaces (with a black on white color scheme, so as to print a blank white canvas)
	move(TOP_WIDTH, 0);
	if (file_location != NULL)
	{
		//Print contents
	}
	getch();
	refresh();
	clear();
	refresh();
}

void line_print(int r, int w)	//Print a Cyan line beginning on row "r" with a width of "w"
{
	int row = r;				//Set the variable "row" equal to the original inputed "r" value
	attron(COLOR_PAIR(BOUNDARY_SCHEME));	//Turn on attribute for the boundary color scheme
	for (int i = 0; i < w; i++)			//Repeat the following code segment "width" times to print the amount of lines equal to the "width" variable
	{
		move(row, 0);				//Set cursor to the beginning of the line for the y-position "row"
		for (int i = 0; i < columns; i++)		//Repeat this code segment until the cursor has reached the end of the line
			printw(" ");				//Print the background color (Cyan) without any characters in the foreground
		row++;					//Increase the value of "row" by one
	}
	move(r, 0);				//Move the cursor back to the beginning of the line of the first row printed
	attroff(COLOR_PAIR(BOUNDARY_SCHEME)); 	//Turn off attribute for the boundary color scheme
}

void print_bar(string s)
{
	attron(COLOR_PAIR(BOUNDARY_SCHEME));	//Turn on attribute for the boundary color scheme
	printw(s);
	attroff(COLOR_PAIR(BOUNDARY_SCHEME)); 	//Turn off attribute for the boundary color scheme
}

