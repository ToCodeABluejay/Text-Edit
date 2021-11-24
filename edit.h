#ifndef EDIT_H
#define EDIT_H

//Include necessary headers and libraries for the application
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

//Define minimum width and height
#define MIN_WIDTH	40
#define MIN_HEIGHT	80

//Define color schemes
#define EDITOR_SCHEME	1
#define BOUNDARY_SCHEME	2

//Define our data-structures
struct Window
{
	int width, height, top;
	char *contents;
};

struct Cursor
{
	int x, y;
};

struct File
{
	char *filename;
	FILE fp;
	char *contents;
	bool open;
	bool ro;
};

struct Change
{
	int line;
	char *text;
	struct Change *prev;
	struct Change *next;
};

//Define our functions
void initialize_editor();							//Initialize NCurses and color mode
void print_editor(struct Window *w);						//Prints the editor sans file contents
void print_contents(struct Window *w, struct Cursor *c, struct File *f);	//Prints the inner contents of the editor
void line_print(int r, char *t, struct Window *w);				//Print a Cyan line at row "r" with text "t", with restrictions of Window "w"

#endif /* EDIT_H */
