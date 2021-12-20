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
	//Initialize all of our core data structures in memory
	struct Window *w = malloc(sizeof(struct Window));
	w->contents = calloc(1,array_size(0)*sizeof(char));
	w->top = 0;
	
	struct Cursor *c = malloc(sizeof(struct Cursor));
	c->x=0, c->y=0; c->abs=0;		//Make sure our cursor is initialized at position (0, 0)
	
	struct File *f = malloc(sizeof(struct File));
	f->saved=true;
	
	struct Change *ch = malloc(sizeof(struct Change));
	
	initialize_editor();
	while(1)
	{
		cbreak();
		curs_set(1);
		
		print_editor(w);
		switch (mode)
		{
			case EDIT_MODE:
				print_contents(w, c, f);
				get_input(w, c, f);
				break;
			case NOT_SAVED:
				if(msg_box(w, "File not saved! Do you want to continue?"))
				{
					strcpy(f->path, "");
					mode=svdmd;
				}
				else
					mode=EDIT_MODE;
				break;
			case OPEN_FILE:
				dialog(w, "File path:");
				if(!dialog_input(w,f->path))
				{
					open(w,f);
					mode=EDIT_MODE;
				}
				break;
			case NEW_FILE:
				dialog(w, "File path:");
				if(!dialog_input(w,f->path))
				{
					new(w,f,c);
					if (f->fp = fopen(f->path, "w"))
					{
						f->ro=false;
						fclose(f->fp);
					}
					mode=EDIT_MODE;
				}
				break;
			case DEL_LINE:
				dialog(w, "Line number:");
				if(!dialog_input(w,ln))
				{
					del_line(atoi(ln)-1, w->contents);
					mode=EDIT_MODE;
				}
				break;
		}
		refresh();
		clear();
	}
}

