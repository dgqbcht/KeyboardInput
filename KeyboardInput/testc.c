#include "keyboardinputc.h"

void testGetch();
void testGetInput();
void testGetString();
void testGetPassword();

int main() {
	//testGetInput();
	//testGetString();
	testGetPassword();
	return EXIT_SUCCESS;
}

/*
 * to find code of a keyboard input
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
 * test function getInput
 */
void testGetInput() {
	char* content = getInput(false);
	printf("Length of input is: %d\n", strlen(content));	
	printf("Visible input is: %s\n", content);
	free(content);
	content = getInput(true);
	printf("Length of input is: %d\n", strlen(content));
	printf("Invisible input is: %s\n", content);
	free(content);
}

/*
 * test function getString
 */
void testGetString() {
	char* content = getString("username", 4, 8);
	printf("Length of input is: %d\n", strlen(content));
	printf("Visible input is: %s\n", content);
	free(content);
}

/*
 *test function getPassword
 */
void testGetPassword() {
	char* content = getPassword(4, 8);
	printf("Length of input is: %d\n", strlen(content));
	printf("Visible input is: %s\n", content);
	free(content);
	
}