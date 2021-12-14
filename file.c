/* "file.c" - Gabriel Bauer (@ToCodeABluejay)
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

bool not_saved(struct Window *w)
{
	while (true)
	{
		attrset(COLOR_PAIR(BOUNDARY_SCHEME));
		move(0,0);
		for(int i=0; i<=w->height*w->width; i++) addch(' ');
		move(floor(w->height/2),0);
		printw("File not saved! Do you want to continue?");
		move(floor(w->height/2)+1,0);
		printw("Press enter to continue and backspace to cancel.");
		refresh();
		switch (getch())
		{
			case '\n':
				return true;
				break;
			case '\b':
				return false;
				break;
		}
	}
}

int open_dialog(struct Window *w, struct Cursor *c, struct File *f)
{
	bool isdial = true;
	/*if (!f->saved)	<-- remove comment when implementation ready
		isdial = not_saved(w);*/
	while (isdial)
	{
		border_line_print(w->height-1, "File path:", w);
		move(w->height-1, 10);
		isdial = dialog_input();
		refresh();
	}
}
