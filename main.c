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

int main(int argc, char *argv[])
{
	//Initialize all of our core data structures in memory
	struct Window *w = malloc(sizeof(struct Window));
	char m[61] = "Hello, world!!\n The quick brown fox jumps over the lazy dog!";
	w->contents = m;
	w->top = 0;
	
	struct Cursor *c = malloc(sizeof(struct Cursor));
	c->x=15, c->y=1; c->abs=30;		//Make sure our cursor is initialized at position (0, 0)
	
	struct File *f = malloc(sizeof(struct File));
	
	struct Change *ch = malloc(sizeof(struct Change));
	
	initialize_editor();
	while(1)
	{
 		print_editor(w);
 		print_contents(w, c, f);
 		move(c->y+1, c->x);
 		get_input(w, c);
		refresh();
		clear();
	}
}

