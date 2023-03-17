#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

char* input;

// free the memory
void clear() {
	free(input);
}

// accept input with limit length, only visible character is permitted
void getString(char* term, int length){
	if (length <= 0) {
		printf("The length of input must be larger than 0.\n");
		return;
	}
	int code;
	int position = 0;
	char key;
	input = (char*)malloc((length+1) * sizeof(char));
	memset(input, '\0', (length + 1) * sizeof(char));
	printf("Please input %s, with max length %d.\n", term, length);
	while (true) {
		// get a keyboard input
		code = _getch(); 
		// deal with function key, such as F1 to F12
		if (code == 0 || code == -32) {
			code = _getch();
		}
		// deal with enter, end loop
		else if(code == 13) {
			printf("\n");
			break;
		}
		// deal with backspace, remove the last input character
		else if (code == 8) {
			// if the length of the input is larger than 0
			if(position>0){
				position--;
				printf("\b \b");
				input[position] = '\0';
			}
		}
		// only visible character is permitted 
		else if (code >= 32 && code <= 126) {
			key = (char)code;
			// if the length of the input is less than limit length
			if (position < length) {
				printf("%c", key);
				input[position] = key;
				position++;
			}
			// if the length of the input equals to limit length
			else {
				printf("\b \b%c", key);
				position--;
				input[position] = key;
				position++;
			}
		}
	}
}
