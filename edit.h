/* "edit.h" - Gabriel Bauer (@ToCodeABluejay)
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

#ifndef EDIT_H
#define EDIT_H

//Include necessary headers and libraries for the application
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

	//Define data type "string"
	typedef char* string;

	//Define necessary constants

    #define tBAR "Unnamed Text Editor"
    #define bBAR "[Esc] Quit  [F1] Help  [F2] Save  [F3] Open  [F4] New  [F5] Delete line"

		//Color schemes
		#define EDITOR_SCHEME	1
		#define BOUNDARY_SCHEME	2

	#define TOP_WIDTH		1	//Defines how many rows wide the top bar is
	#define BOTTOM_WIDTH	1	//Defines how many rows wide the bottom bar is 
	
	#define MIN_WIDTH		90	//Defines the minimum width of console
	#define MIN_HEIGHT		60	//Defines the minimum height of console

	/* Application version A-D, with A being the major version, B
	 * being the minor version, C being the patch version, and D being
	 * the stage in the release cycle, source branch, or patch version
	 */
    #define VER_A       0
    #define VER_B       0
    #define VER_C       0
    #define VER_D       "PRE-ALPHA"

 	//Define necessary variables
    
 	extern int rows, columns, y, x;
    
    extern int cursor_pos[2];		//Initialize array for x and y cursor positions

	void initialize_editor();	//Define function to print boarders to screen

	void line_print(int r, int w);	//Define function to print blank line from a given y;

	void print_bar(string s);	//Prints a given string with the boundary color scheme
    
    void file_open(string s);
    
    void file_save();
    
    void file_saveAs();

	extern string file_location, file_contents, editor_contents, filename;

	extern bool writeable, file_changed;
   

#endif /* EDIT_H */
