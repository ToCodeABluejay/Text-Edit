/* "text.c" - Gabriel Bauer (@ToCodeABluejay)
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

int get_line_number_pos(int line, char *text)
{
	long long i, j;
	
	if (line == 0)
		return 0;
	else
	{
		for(i=0, j=0; text[i]!='\0'; i++)
		{
			if (text[i]=='\n' && j==line)
				break;
			else if (text[i]=='\n')
				j++;
		}
		return i;
	}
}

int get_end_of_line(int start, char *text)
{
	int i;
	for (i = start; text[i]!='\0' && text[i]!='\n'; i++);
	return i;
}

/*int get_relative_start(struct Cursor *c)
{
	return c->x - c->x_rel;
}*/

