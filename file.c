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

void open(struct Window *w, struct File *f)
/*Opens a file, copies the contents, and
 *assesses file permissions*/
{
	struct stat f_stat;
	f->fp = fopen(f->path, "r");
	
	if (f->fp)
	{
		stat(f->path, &f_stat);
		
		if (f_stat.st_mode!=S_IWUSR)
			f->ro=false;
		else
			f->ro=true;
		
		fseek(f->fp, 0L, SEEK_END);
		unsigned long long size = array_size(ftell(f->fp));
		
		w->contents = realloc(w->contents, size*sizeof(char));
		rewind(f->fp);
		
		fread(w->contents, size, 1, f->fp);
		fclose(f->fp);
	}
}

void save(struct Window *w, struct File *f)
{
	f->fp = fopen(f->path, "w");
	
	if (f->fp)
	{
		fputs(w->contents, f->fp);
		fclose(f->fp);
		f->saved=true;
	}
	else
		mode=SAVE_AS;
}

void new(struct Window *w, struct File *f, struct Cursor *c)
{
	f->fp=NULL;
	f->ro=true;
	f->saved=true;
	
	strcpy(w->contents, "");
	
	c->x=0; c->y=0; c->abs=0;
}

