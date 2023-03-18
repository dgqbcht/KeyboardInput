#include "keyboardinputc.h"

void testGetch();
void testGetInput();
void testGetString();
void testGetPassword();
void testGetNumber();

int main() {
	//testGetch();
	//testGetInput();
	//testGetString();
	//testGetPassword();
	//testGetNumber();
	
	return EXIT_SUCCESS;
}

/*
 *	to find code of a keyboard input
 */ 
void testGetch() {
	printf("Press any key.\n");
	char key;
	while (true) {
		key = _getch();
		printf("Your input is: %c\n", key);
		printf("Code is: %d\n", (int)key);
		if ((int)key == 13) {
			break;
		}
	}
}

/*
 *	test function getInput
 */
void testGetInput() {
	char* content = getInput(false);
	// visible mode
	printf("Length of input is: %d\n", (int)strlen(content));	
	printf("Visible input is: %s\n", content);
	free(content);
	// invisible mode
	content = getInput(true);
	printf("Length of input is: %d\n", (int)strlen(content));
	printf("Invisible input is: %s\n", content);
	free(content);
}

/*
 *	test function getString
 */
void testGetString() {
	int min = 4;
	int max = 8;
	int top = 1;
	int left = 4;
	char* content = getString("username", min, max, top, left);
	printf("\033[%dCLength of input is: %d\n",left, (int)strlen(content));
	printf("\033[%dCVisible input is: %s\n",left, content);
	free(content);
}

/*
 *	test function getPassword
 */
void testGetPassword() {
	int min = 4;
	int max = 8;
	int top = 1;
	int left = 4;
	char* content = getPassword(min, max, top, left);
	printf("\033[%dCLength of input is: %d\n", left, (int)strlen(content));
	printf("\033[%dCVisible input is: %s\n", left, content);
	free(content);
	
}

/*
 * test function get number 
 */
void testGetNumber() {
	int min = -273.15;
	int max = 300;
	int top = 1;
	int left = 4;
	double value = getNumber("temperature", min, max, top, left);
	printf("The value is: %f\n", value);
}

