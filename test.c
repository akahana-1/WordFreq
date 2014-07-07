#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include "wordlist.h"
#include "wordbtree.h"
#include "wordarray.h"

#define MAXLEN 1024

int main(int argc, char** argv){
	regex_t preg;
	char *pattern = "[[:alnum:]]+";
	regmatch_t *pmatch;
	size_t nmatch;
//	WordTree* btree = NULL;
//	WordList* list = NULL;
//	Word* array = NULL;
	char buf[MAXLEN];
	
	if(regcomp(&preg, pattern, REG_EXTENDED|REG_NEWLINE) != 0) exit(1);
	nmatch = preg.re_nsub + 1;
	pmatch = malloc(sizeof(regmatch_t) * nmatch);

	while(scanf("%s", buf) != -1){
		if(regexec(&preg, buf, nmatch, pmatch, 0) != 0){
			printf("Regular Expression is Uncompleted.\n");
		}
		else{
			int i, j;
			for(i = 0;i < nmatch;++i){
				for(j = pmatch[i].rm_so; j < pmatch[i].rm_eo;++j){
					printf("%c", buf[i]);
				}
				printf("\n");
			}
		}
//		btree = treeInsert(btree, buf);
//		array = arrayInsert(array, buf);
//		list = listInsert(list, buf);
	}
//	printf("%d\n", treeAllWordCount(btree));
//	treeAllWordFreq(btree, treeAllWordCount(btree));
//	printf("%d\n", arrayAllWordCount(array));
//	printf("%d\n", listAllWordCount(list));
//	listAllWordFreq(list, listAllWordCount(list));
	return 0;
}
