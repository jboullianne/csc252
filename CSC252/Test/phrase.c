#include <stdio.h>

int main(){
	
	char input;


	printf("Please enter the password\n");
	scanf("%c", &input);

	if(input == 'H'){
		printf("Phrase Accepted\n");
	}
	else{
		printf("Worng password\n");
	}
	
	return 0;

}