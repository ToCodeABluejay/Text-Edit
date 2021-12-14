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
{
	int max, pos=get_line_number_pos(c->y, w->contents);
	max=get_end_of_line(pos, w->contents)-pos;
	if (c->x>max)
		c->x=max;
	c->abs=pos+max;
}

void key_up(struct Window *w, struct Cursor *c)
{
	if (c->y>0)
	{
		c->y--;
		repos_x(w, c);
	}
	else
		beep();
}

void key_down(struct Window *w, struct Cursor *c)
{
	if (get_line_number_pos(c->y+1, w->contents)!=EOF)
	{
		c->y++;
		repos_x(w, c);
	}
	else
		beep();
}

void key_right(struct Window *w, struct Cursor *c)
{
	int i = get_line_number_pos(c->y, w->contents);
	i += c->x;
	if (w->contents[i+1]!='\n'&&w->contents[i+1]!='\0')
	{
		c->x++; c->abs++;
	}
	else if (w->contents[i+1]=='\n')
	{
		c->x=0; c->y++;
		c->abs=get_line_number_pos(c->y, w->contents);
	}
	else
		beep();
}

void key_left(struct Window *w, struct Cursor *c)
{
	int i = get_line_number_pos(c->y, w->contents);
	i += c->x;
	if (w->contents[i-1]!='\n'&&w->contents[i-1])
	{
		c->x--; c->abs--;
	}
	else if (w->contents[i-1]=='\n')
		key_up(w, c);
	else if (!w->contents[i-1])
		beep();
}

void get_input(struct Window *w, struct Cursor *c)
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
			break;
		case KEY_F(2):
			break;
		case KEY_F(3):
			break;
		case KEY_F(4):
			break;
		case KEY_F(5):
			break;
		case KEY_RESIZE:
			break;
		case '\n':
			open_dialog(w,c, NULL);
			break;
		default:
			ins_char(c->abs, (char) k, w->contents);
			c->x++; c->abs++;
			break;
	}
}

bool dialog_input()
{
	int k;
	switch(k = getch())
	{
		case '\n':
			return false;
			break;
		case KEY_RESIZE:
			break;
		default:
			break;
	}
}
