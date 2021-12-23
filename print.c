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

void initialize_editor()
//Initialize curses
{
	initscr();						//Initialize screen and curses mode
	if (!has_colors())				//Check to see if the console supports colored print, if not, then execute the following segment
	{
		endwin();									//Un-initialize the window
		fprintf(stderr, "ERROR: This console does not support colored printing\n");	//Provide an error message
		exit(1);									//Exit the application
	}
	start_color();						//Otherwise, carry on wayward, initialize color and print the outline to the editor
	init_pair(EDITOR_SCHEME, COLOR_BLACK, COLOR_WHITE);	//Initialize color pair of black text on a white background (for editor)
	init_pair(BOUNDARY_SCHEME, COLOR_BLACK, COLOR_CYAN);	//Initialize color pair of black text on a cyan background (for top and bottom boundaries)
	keypad(stdscr, true);
	cbreak();
	curs_set(1);
}

void border_line_print(int r, char *t, struct Window *w)
/*Print a Cyan line at row "r" with text "t", with
 *restrictions of Window "w"
 */
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

void content_line_print(int r, struct Window *w, struct Cursor *c)
/*Print line at row "r" with text "t", with restrictions and
 *contents of Window "w", using cursor position x,y
 */
{
	long i = 0, j;
	
	attrset(COLOR_PAIR(EDITOR_SCHEME));		//Turn on attribute for the boundary color scheme
	move(r+1, 0);					//Set cursor to the beginning of the line for the y-position "row" -- all being relative to editor bounds

	j = get_line_number_pos(r+w->top, w->contents);
	if (r==c->y)
		j += (long) c->x-(c->x%w->width)-floor(c->x/w->width);
	
	for (; i < w->width-1 && j+i < get_end_of_line(j, w->contents); i++)	//Repeat the following code segment until the rest of the bar is full
	{
		if(w->contents[j+i]!='\t')
			addch(w->contents[j+i]);
		else
			addch(' ');
	}
	if (i==w->width-1)
		addch('>');
}

void print_contents(struct Window *w, struct Cursor *c, struct File *f)
//Used to print all of the regular editor contents
{
	int i=0;
	while (i<w->height-2)
	{
		content_line_print(i, w, c);
		i++;
	}
	move(c->y-w->top+1, c->x%w->width);
}

bool msg_box(struct Window *w, char *msg)
/*A very cimple continue/cancel message
 *window
 */
{
	attrset(COLOR_PAIR(BOUNDARY_SCHEME));
	move(0,0);
	for(int i=0; i<=w->height*w->width; i++) addch(' ');
	move(floor(w->height/2),0);
	printw(msg);
	move(floor(w->height/2)+1,0);
	printw("Press enter to continue and backspace to cancel.");
	switch (getch())
	{
		case '\n':
			return true;
			break;
		case KEY_BACKSPACE:
			return false;
			break;
	}
	return NULL;
}

void dialog(struct Window *w, char *prompt, char *msg)
/*Prints a string msg on the top line
 *and prompt on the bottom. Used equally
 *for drawing the regular editor as well
 *as for various prompts
 */
{
	attrset(COLOR_PAIR(EDITOR_SCHEME));
	move(0, 0);
	for (int i = 0; i < w->height * w->width; i++) printw(" ");
	
	border_line_print(0, msg, w);	
	border_line_print(w->height-1, prompt, w);
	move(w->height-1, strlen(prompt));
}

void run_mode(int *m, struct Window *w, struct Cursor *c, struct File *f)
/*Prints to the console the coresponding output
 *based upon the current given mode of operation
 */
{
	switch (*m)
	{
		case EDIT_MODE:
			dialog(w, "[Ctrl+c] Quit  [F1] Save  [F2] Save as  [F3] Open  [F4] New  [F5] Delete line", "Unnamed Text Editor");
			print_contents(w, c, f);
			get_input(w, c, f);
			break;
		case NOT_SAVED:
			if(msg_box(w, "File not saved! Do you want to continue?"))
			{
				strcpy(f->path, "");
				*m=svdmd;
			}
			else
				*m=EDIT_MODE;
			break;
		case OPEN_FILE:
			dialog(w, "File path:", "Open File");
			if(!dialog_input(w,f->path))
			{
				open_file(w,f);
				*m=EDIT_MODE;
			}
			break;
		case NEW_FILE:
			dialog(w, "File path:", "New File");
			if(!dialog_input(w,f->path))
			{
				new(w,c,f);
				f->fp = fopen(f->path, "w");
				if (f->fp)
				{
					f->ro=false;
					fclose(f->fp);
				}
				*m=EDIT_MODE;
			}
			break;
		case DEL_LINE:
			dialog(w, "Line number:", "Delete Line");
			if(!dialog_input(w,ln))
			{
				del_line(atoi(ln)-1, w->contents);
				*m=EDIT_MODE;
			}
			break;
		case SAVE_AS:
			dialog(w, "File path:", "Save As");
			if(!dialog_input(w,f->path))
			{
				save(w, f);
				*m=EDIT_MODE;
			}
			break;
	}
}

