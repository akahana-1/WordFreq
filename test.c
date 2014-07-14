#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <ctype.h>
#include "wordlist.h"
#include "wordbtree.h"
#include "wordarray.h"

#define MAXLEN 1024

void substr(const char*, char*, int, int);

int main(int argc, char** argv){
	regex_t preg;
	char *pattern = "[[:alnum:]]+";
	regmatch_t *pmatch;
	size_t nmatch;
	WordTree* btree = NULL;
	WordList* list = NULL;
	Word* array = NULL;
	char buf[MAXLEN];
	
	//正規表現マッチャの設定
	if(regcomp(&preg, pattern, REG_EXTENDED|REG_NEWLINE) != 0) exit(1);
	nmatch = preg.re_nsub + 1;
	pmatch = malloc(sizeof(regmatch_t) * nmatch);

	while(scanf("%s", buf) != -1){
		if(regexec(&preg, buf, nmatch, pmatch, 0) != 0){
			printf("Regular Expression is Uncompleted.\n");
		}
		else{
			//正規表現マッチの開始.
			int i;
			for(i = 0;i < nmatch;++i){
				char *p = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
				substr(buf, p, pmatch[i].rm_so, pmatch[i].rm_eo);
				btree = treeInsert(btree, p);
				array = arrayInsert(array, p);
				list = listInsert(list, p);
			}
		}
  }
//	printf("%d\n", treeAllWordCount(btree));
	treeAllWordFreq(btree, treeAllWordCount(btree));
//	printf("%d\n", arrayAllWordCount(array));
//	printf("%d\n", listAllWordCount(list));
	listAllWordFreq(list, listAllWordCount(list));
	return 0;
}

// 与えられた文字列のインデックスsからインデックスeまでの文字列を抜き出してpに格納する
// param: str:文字列を抜き出すための文字列
// param: p:抜き出した文字列を格納する文字列
// param: s:文字列の開始位置のインデックス
// param: e:文字列の終端位置のインデックス
void substr(const char* str, char* p,  int s, int e){
	int i;
	for(i = s;i < e;++i){
		p[i - s] = tolower( str[i] );
	}
	p[e] = '\0';
}
