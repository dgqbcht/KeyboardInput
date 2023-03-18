#include "keyboardinputc.h"

void testGetInput();
void testGetString();
void testGetPassword();
void testGetNumber();
void testColor();

int main() {
	//testGetch();
	//testGetInput();
	//testGetString();
	//testGetPassword();
	//testGetNumber();
	//testColor();
	return EXIT_SUCCESS;
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
	double min = -273.15;
	double max = 300;
	int top = 1;
	int left = 4;
	double value = getNumber("temperature", min, max, top, left);
	printf("The value is: %f\n", value);	
}

/*
 *	test functoion setOutputColor and resetOutputColor
 */
void testColor() {
	printf("This is a original message.\n");
	setOutputColor(BG_LIGHTYELLOW, FG_BLUE);
	printf("This is a message after color changed.\n");
	setOutputColor(BG_WHITE, FG_BLACK);
	printf("This is a message after color changed again.\n");
	resetOutputColor();
	printf("This is a message after color reset.\n");
}