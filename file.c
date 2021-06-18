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

void file_open(string s)
{
    static unsigned long int size;		//Initialize temporary variable
    static FILE *file;		//Initialize FILE data type //en français ~ fichier
    file = fopen(s, "r+");
    if (file)
    {
    	writeable = true;
    }
    else
    {
    	writeable = false;
    }
    fclose(file);
    file = fopen(s, "r");		//Open the named file in Read-Only mode
    if (file)
    {
    	fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
        file_location = s;
		if (strrchr(file_location, '/') != NULL)
		{
			filename = strrchr(file_location, '/') + 1;
		}
		else
		{
			filename = file_location;
		}
		char cont[size];
		for (int i = 0; i < size; i++)
		{
			cont[i] = (char) fgetc(file);
		}
		file_contents = cont;
		editor_contents = cont;
		fclose(file);
    }
    else
	{
		fprintf(stderr, "ERROR: Cannot read %s%s", filename, "!\n");
		exit(1);
	}
}

void file_save()
{
	if (file_location != NULL)
	{
		if (writeable = true)
		{
			FILE *file;		//Initialize FILE data type
    		file = fopen(file_location, "w");
    		fputs(editor_contents, file);
    		fclose(file);
		}
		else
		{
			//file_saveAs();
		}
	}
	else
	{
		//file_saveAs();
	}
}

