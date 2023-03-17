#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH	512

/*
 *	accept input from keyboard, 
 *	only visible character is permitted
 */ 
char* getInput(bool password){
	int code;
	int position = 0;
	char key;
	char *input = (char*) malloc(MAX_LENGTH * sizeof(char));
	memset(input, '\0', MAX_LENGTH);
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
			if (position < MAX_LENGTH) {
				if (password) {
					printf("*");
				}
				else {
					printf("%c", key);
				}
				input[position] = key;
				position++;
			}
			// if the length of the input equals to limit length
			else {
				if (!password) {
					printf("\b \b%c", key);
				}
				position--;
				input[position] = key;
				position++;
			}
		}
	}
	return input;
}

/* 
 *	get input char array, 
 *	with visible input,
 *	field information,
 *	and limited length between min and max.
 *	run looply until the limitation is satisfied.
 */
char* getString(char* field, int min, int max) {
	char* input;
	while (true) {
		printf("Please input %s (%d - %d characters):", field, min, max);
		input = getInput(false);
		int length = strlen(input);
		if (length < min || length > max) {
			printf("The %s should have %d - %d characters.\n", field, min, max);
			printf("Your input has %d characters. Try agian.\n", length);
			free(input);
		}
		else {
			break;
		}
	}
	return input;
}

/*
 *	get string input,
 *	with invisible input(*),
 *	and limited length between min and max.
 *	run looply until the limitation is satisfied.
 */
char* getPassword(int min, int max) {
	char* input;
	while (true) {
		printf("Please input password (%d - %d characters):", min, max);
		input = getInput(true);
		int length = strlen(input);
		if (length < min || length > max) {
			printf("The password should have %d - %d characters.\n", min, max);
			printf("Your password has %d characters. Try agian.\n", length);
			free(input);
		}
		else {
			break;
		}
	}
	return input;
}

/*
 *	determine whether the content of char array is a number.
 */
bool isNumber(const char* value) {
	int i = 0;
	int dot = 0;
	if (value[0] == '-') {
		i = 1;
	}
	for (; i < strlen(value); i++) {
		if (!isdigit(value[i])) {
			if (value[i] == '.') {
				dot++;
			}
			else {
				return false;
			}
		}
	}

	if (dot > 1) {
		return false;
	}
	return true;
}

/*
 *	get number input,
 *	with field information,
 *	and limited value between min and max.
 */
double getNumber(char* field, double min, double max) {
	char* input;
	double value;
	while (true) {
		printf("Please input %s (%f to %f):", field, min, max);
		input = getInput(false);
		if (isNumber(input)) {
			value = atof(input);
			free(input);
			if (value < min || value > max) {
				printf("The %s should be between %f to %f.\n", field, min, max);
				printf("Your input is %f. Try agian.\n", value);
			}
			else {
				break;
			}
		}
		else {
			printf("Your input is not a number. Try agian.\n");
		}
	}
	return value;
}