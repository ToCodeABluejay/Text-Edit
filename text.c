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
/*Returns the position of the line-nth line
 *in a character array 'text'*/
{
	long long i, j;
	
	if (line == 0)
		return 0;
	else
	{
		for(i=0, j=0; text[i]!='\0'; i++)
		{
			if (text[i]=='\n')
				j++;
			if (text[i]=='\n' && j==line)
				break;
		}
		if (text[i]!='\0')
			return i+1;
		else
			return EOF;
	}
}

int get_end_of_line(int start, char *text)
/*From a given start position in a char array,
 *this function returns the position of the end
 *of the given line at that position, whether the
 *line is the end of the array (aka '\0') or the
 *start of a new line (aka '\n')*/
{
	int i;
	for (i = start; text[i]!='\0' && text[i]!='\n'; i++);
	return i;
}

unsigned long long array_size(int k)
/*Base-2 dynamic array size function. It takes a length k
 *and finds the closest base of two that is equal to or
 *larger than the given k value - used to determine malloc()
 *sizes for text-content in a dynamic setting*/
{
	unsigned len = (unsigned)floor(log(k)/log(2));
	return pow(2,len+1);
}

void ins_char(int pos, char k, char *str)
/*The basic functionality of most of the editor
 *relies on this function. It is simply used to
 *insert a character into the text from the given
 *cursor position.*/
{
	if(strlen(str)==array_size(strlen(str)))
	/*If we have reached the end of the dynamic array,
	 *we make a copy of its contents and then resize
	 *the original to be double the previous size, copy
	 *the contents back in.*/
	{
		char *resize = (char*) malloc(strlen(str));
		strcpy(resize, str);
		str = realloc(str,array_size(strlen(str))*2);
		strcpy(str, resize);
	}
	//Insert the character at the given position
	char *cpy = (char*) malloc(array_size(strlen(str)));
	strncpy(cpy, str, pos);
	cpy[pos] = k;
	strcat(cpy, str+pos);
	strcpy(str, cpy);
}

