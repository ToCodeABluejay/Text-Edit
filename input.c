/* "input.c" - Gabriel Bauer (@ToCodeABluejay)
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

void repos_x(struct Window *w, struct Cursor *c)
/*When the cursor's x-position is greater than the
 *length of the given line, move the cursor back
 *to the end of the given line
 */
{
	int max, pos=get_line_number_pos(c->y, w->contents);
	max=get_end_of_line(pos, w->contents);
	if (c->x>max-pos)
	{
		c->x=max-pos;
		c->abs=max;
	}
	else
		c->abs=pos+c->x;
}

void key_up(struct Window *w, struct Cursor *c)
/*When in edit-mode and the up arrow key is pressed,
 *do this
 */
{
	if (c->y>0)
	{
		if(c->y==w->top)
			w->top--;
		c->y--;
		repos_x(w, c);
	}
	else
		beep();
}

void key_down(struct Window *w, struct Cursor *c)
/*When in edit-mode and the down arrow key is pressed,
 *do this
 */
{
	if (get_line_number_pos(c->y+1, w->contents)!=EOF)
	{
		if(c->y-w->top==w->height-3)
			w->top++;
		c->y++;
		repos_x(w, c);
	}
	else
		beep();
}

void key_right(struct Window *w, struct Cursor *c)
/*When in edit-mode and the right arrow key is pressed,
 *do this
 */
{
	if (w->contents[c->abs]!='\n'&&w->contents[c->abs]!='\0')
	{
		c->x++; c->abs++;
	}
	else if (w->contents[c->abs]=='\n')
	{
		c->x=0; c->y++; c->abs++;
	}
	else
		beep();
}

void key_left(struct Window *w, struct Cursor *c)
/*When in edit-mode and the left arrow key is pressed,
 *do this
 */
{
	int i = get_line_number_pos(c->y, w->contents);
	i += c->x;
	if (w->contents[i-1]!='\n'&&w->contents[i-1])
	{
		c->x--; c->abs--;
	}
	else if (w->contents[i-1]=='\n')
	{
		c->y--;
		int max, pos=get_line_number_pos(c->y, w->contents);
		max=get_end_of_line(pos, w->contents)-pos;
		c->x=max;
		c->abs=pos+max;
	}
	else if (!w->contents[i-1])
		beep();
}

void get_input(struct Window *w, struct Cursor *c, struct File *f)
/*When in edit-mode and getting user input,
 *do this
 */
{
	int k;
	switch(k = getch())
	{
		case KEY_UP:
			key_up(w, c);
			break;
		case KEY_DOWN:
			key_down(w, c);
			break;
		case KEY_LEFT:
			key_left(w, c);
			break;
		case KEY_RIGHT:
			key_right(w, c);
			break;
		case KEY_F(1):
			save(w, f);
			break;
		case KEY_F(2):
			mode=SAVE_AS;
			break;
		case KEY_F(3):
			svdmd=OPEN_FILE;
			if (f->saved)
				mode=svdmd;
			else
				mode=NOT_SAVED;
			break;
		case KEY_F(4):
			svdmd=NEW_FILE;
			if (f->saved)
				mode=svdmd;
			else
				mode=NOT_SAVED;
			break;
		case KEY_F(5):
			strcpy(ln, "");
			mode=DEL_LINE;
			break;
		case KEY_BACKSPACE:
			del_char(w, c);
			f->saved=false;
			break;
		case KEY_RESIZE:
			if (c->y>(w->top+w->height))
				w->top+=c->y-(w->top+w->height)+1;
			break;
		default:
			ins_char(c->abs, (char) k, w->contents);
			c->abs++;
			if (k!='\n')
				c->x++;
			else
			{
				c->x=0; c->y++;
			}
			f->saved=false;
			break;
	}
}

int dialog_input(struct Window *w, char *str)
/*When recieving input from a prompt
 *as opposed to the regular EDIT_MODE
 *use this function instead of get_input
 */
{
	int i=strlen(str);
	int k;
	
	printw(str);
	switch(k = getch())
	{
		case '\n':
			str[i]='\0';
			return 0;
			break;
		case KEY_BACKSPACE:
			i--;
			str[i]='\0';
			break;
		case KEY_RESIZE:
			break;
		default:
			str[i] = (char) k;
			i++;
			break;
	}
	return 1;
}
