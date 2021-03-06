/* "main.c" - Gabriel Bauer (@ToCodeABluejay)
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

int mode=EDIT_MODE, svdmd;
char ln[NAME_MAX]="";

int main(int argc, char *argv[])
{
	#ifdef __OpenBSD__
	pledge("stdio rpath wpath cpath tty", NULL);
	#endif
	
	//Initialize all of our core data structures in memory
	struct Window *w = malloc(sizeof(struct Window));
	w->contents = calloc(1,array_size(0)*sizeof(char));
	w->top = 0;
	
	struct Cursor *c = malloc(sizeof(struct Cursor));
	c->x=0, c->y=0; c->abs=0;		//Make sure our cursor is initialized at position (0, 0)
	
	struct File *f = malloc(sizeof(struct File));
	strncpy(f->path, "", PATH_MAX);
	strncpy(f->filename, "", NAME_MAX);
	f->ro=true;
	f->saved=true;
	
	if (argc>1)
	{
		strcpy(f->path, argv[1]);
		open_file(w, f);
	}
	
	//Initialize curses
	initialize_editor();
	while(1)	//Run until user quits application
	{
		getmaxyx(stdscr, w->height, w->width); //Get the dimensions of current screen (stdscr) and place those values into the Window structure
		run_mode(&mode, w, c, f);	//Print to the console according to our mode of operation
		refresh();
		clear();
	}
}

