#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_LENGTH	512

#define FG_BLACK		0
#define FG_BLUE			1
#define FG_GREEN		2
#define FG_LAKEBLUE		3
#define FG_RED			4
#define FG_PURPLE		5
#define FG_YELLOW		6
#define FG_WHITE		7
#define FG_GRAY			8
#define FG_LIGHTBLUE	9
#define FG_LIGHTGREEN	10
#define FG_CYAN			11
#define FG_LIGHTRED		12
#define FG_LAVENDER		13
#define FG_LIGHTYELLOW	14
#define FG_BRIGHTWHITE	15

#define BG_BLUE			16
#define BG_GREEN		32
#define BG_LAKEBLUE		48
#define BG_RED			64
#define BG_PURPLE		80
#define BG_YELLOW		96
#define BG_WHITE		112
#define BG_GRAY			128
#define BG_LIGHTBLUE	144
#define BG_LIGHTGREEN	160
#define BG_CYAN			176
#define BG_LIGHTRED		192
#define BG_LAVENDER		208
#define BG_LIGHTYELLOW	224
#define BG_BRIGHTWHITE	240


HANDLE output;
CONSOLE_SCREEN_BUFFER_INFO csbi;


/*
 * accept input from keyboard, 
 * only visible character is permitted.
 * enable password mode with argument [true]
 */ 
char* getInput(const bool password){
	int code;
	int position = 0;
	char key;
	char *input = (char*) malloc(MAX_LENGTH * sizeof(char));
	memset(input, '\0', MAX_LENGTH);
	while (true) {
		// get a keyboard input
		code = _getch(); 
		// deal with function key, such as F1 to F12
		if (code == 0 || code == -32 || code == 224) {
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
 * get input char array, 
 * with visible input,
 * field information,
 * and limited length between min and max.
 * Display content start with [top] line below previous line,
 * and after [left] blank characters.
 * run looply until the limitation is satisfied.
 */
char* getString(const char* field, const int min, const int max, const int top, const int left) {
	char* input;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(output, &csbi);
	csbi.dwCursorPosition.X = left;
	csbi.dwCursorPosition.Y = csbi.dwCursorPosition.Y + top;
	while (true) {
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		printf("Please input %s (%d - %d characters):", field, min, max);
		input = getInput(false);
		int length = (int)strlen(input);
		if (length < min || length > max) {
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(output, csbi.dwCursorPosition);
			printf("The %s should have %d - %d characters.\n", field, min, max);
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(output, csbi.dwCursorPosition);
			printf("Your input has %d characters. Try agian.\n", length);
			csbi.dwCursorPosition.Y++;
			free(input);
		}
		else {
			break;
		}
	}
	return input;
}


/*
 * get string input,
 * with invisible input(*),
 * and limited length between min and max.
 * display content start with [top] line below previous line,
 * and after [left] blank characters.
 * run looply until the limitation is satisfied.
 */
char* getPassword(const int min, const int max, const int top, const int left) {
	char* input;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(output, &csbi);
	csbi.dwCursorPosition.X = left;
	csbi.dwCursorPosition.Y = csbi.dwCursorPosition.Y + top;
	while (true) {
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		printf("Please input password (%d - %d characters):", min, max);
		input = getInput(true);
		int length = (int)strlen(input);
		if (length < min || length > max) {
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(output, csbi.dwCursorPosition);
			printf("The password should have %d - %d characters.\n", min, max);
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(output, csbi.dwCursorPosition);
			printf("Your password has %d characters. Try agian.\n", length);
			csbi.dwCursorPosition.Y++;
			free(input);
		}
		else {
			break;
		}
	}
	return input;
}

/*
 * determine whether the content of char array is a number.
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
 * get number input,
 * with field information,
 * and limited value between min and max.
 * display content start with [top] line below previous line,
 * and after [left] blank characters.
 * run looply until the limitation is satisfied.
 */
double getNumber(const char* field, const double min, const double max, const int top, const int left) {
	char* input;
	double value;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(output, &csbi);
	csbi.dwCursorPosition.X = left;
	csbi.dwCursorPosition.Y = csbi.dwCursorPosition.Y + top;
	while (true) {
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		printf("Please input %s (%f to %f):", field, min, max);
		input = getInput(false);
		csbi.dwCursorPosition.Y++;
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		if (isNumber(input)) {
			value = atof(input);
			free(input);
			if (value < min || value > max) {
				printf("The %s should be between %f to %f.\n", field, min, max);
				csbi.dwCursorPosition.Y++;
				SetConsoleCursorPosition(output, csbi.dwCursorPosition);
				printf("Your input is %f. Try agian.\n", value);
				csbi.dwCursorPosition.Y++;
			}
			else {
				break;
			}
		}
		else {
			printf("Your input is not a number. Try agian.\n");
			csbi.dwCursorPosition.Y++;
		}
	}
	return value;
}

/*
 * change output color,
 * available background color is in common.h, start with BG_
 * available foreground color is in common.h, start with FG_
 */
void setOutputColor(int background, int foreground) {
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, background | foreground);
}

/*
 * reset output color to black background and white foreground
 */
void resetOutputColor() {
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, FG_WHITE);
}