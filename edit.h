/* "edit.h" - Gabriel Bauer (@ToCodeABluejay)
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
#ifndef EDIT_H
#define EDIT_H

//Include necessary headers and libraries for the application
#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <sys/stat.h>
#ifdef __OpenBSD__
#include <unistd.h>
#endif

//Define color schemes
#define EDITOR_SCHEME	1
#define BOUNDARY_SCHEME	2

//Our different operating modes
#define EDIT_MODE	0
#define NOT_SAVED	1
#define OPEN_FILE	2
#define NEW_FILE	3
#define SAVE_AS		4
#define DEL_LINE	5

//Define our data-structures
struct Window
{
	int width, height, top;
	char *contents;
};

struct Cursor
{
	int x, y, abs;
};

struct File
{
	char path[PATH_MAX];
	char filename[NAME_MAX];
	FILE *fp;
	bool ro;
	bool saved;
};

/*struct Change		//Not implemented, possibly later
{
	int line;	//Line of the change
	char *ot;	//Old text of the line
	char *nt;	//New text of the line
	struct Change *prev;
	struct Change *next;
};*/

extern int mode, svdmd;
extern char ln[NAME_MAX];

//Define our functions

//print.c
void initialize_editor();							//Initialize NCurses and color mode
void border_line_print(int, char *, struct Window *);			//Print a Cyan line at row "r" with text "t", with restrictions of Window "w"
void content_line_print(int, struct Window *, struct Cursor *);	//Print line at row "r" with text "t", with restrictions and contents of Window "w", using cursor position x,y
void print_contents(struct Window *, struct Cursor *, struct File *);	//Prints the inner contents of the editor
void dialog(struct Window *, char *, char *);
bool msg_box(struct Window *, char *);
void run_mode(int *, struct Window *, struct Cursor *, struct File *);

//text.c
int get_line_number_pos(int, char *);					//Gets the position of the line number 'line' in text 'text'
int get_end_of_line(int, char *);
unsigned long long array_size(int);
void ins_char(int, char, char *);
void del_char(struct Window *, struct Cursor *);
void del_line(int, char *);

//input.c
void get_input(struct Window *, struct Cursor *, struct File *);
void key_left(struct Window *, struct Cursor *);
int dialog_input(struct Window *, char *);

//file.c
void open_file(struct Window *, struct File *);
void save(struct Window *, struct File *);
void new(struct Window *, struct Cursor *, struct File *);

#endif /* EDIT_H */
