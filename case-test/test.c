#include <stdio.h>

int get_line_number_pos(int line, char *text)
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

int main()
{
	char test[3]="\n\nH";
	printf("%i", get_line_number_pos(2, test));
}
