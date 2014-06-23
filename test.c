#include <stdio.h>
#include <stdlib.h>
#include "wordlist.h"

#define MAXLEN 1024

int main(){
	WordList* root = NULL;
	char buf[MAXLEN];
	
	while(scanf("%s", buf) != -1){
		root = listInsert(root, buf);
	}
	printf("%d\n", listAllWordCount(root));
	return 0;
}
