#include "keyboardinputc.h"

void testGetch();
void testGetString();

int main() {
	//testGetch();
	testGetString();

	// free the memory
	clear();
	return EXIT_SUCCESS;
}

// to find code of a key input
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

// test function getString
void testGetString() {
	getString("username",0);
	if (NULL != input) {
		printf("Your input is: %s", input);
	}
}