#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1024
#define HASHLEN 1023

typedef struct word{
	//保存する文字列
	char* word;
	//文字列の出現回数
	int count;
}Word;

Word* arrayInsert(Word*, const char*);
int arrayAllWordCount(const Word*);
void arrayAllWordFreq(const Word*, int);

//配列に内容を追加する.
//param: ary 配列の先頭を示すポインタ
//param: _word 配列に追加する文字列
//return 要素を追加した後の配列のポインタ
Word* arrayInsert(Word* ary, const char* _word){
	int i;
	if(ary == NULL){
		Word* ham = (Word*)malloc(sizeof(Word) * MAXLEN);
		for(i = 0;i < MAXLEN;++i){
			ham[i].word = NULL;
		}
		ham[0].word = (char*)malloc(sizeof(char) * (strlen(_word) + 1));
		strcpy(ham[0].word, _word);
		ham[0].count = 1;
		return ham;
	}
	else{
		for(i = 0;i < MAXLEN;++i){
			if(ary[i].word == NULL){
				ary[i].word = (char*)malloc(sizeof(char) * (strlen(_word) + 1));
				strcpy(ary[i].word, _word);
				ary[i].count = 1;
				break;
			}
			else if(strcmp(ary[i].word, _word) == 0){
				++ary[i].count;
				break;
			}
		}
		return ary;
	}
}

//配列に格納されている文字列の出現回数の合計を返す.
//param: ary 要素が格納されている配列のポインタ
int arrayAllWordCount(const Word* ary){
	int s = 0, i;
	for(i = 0;i < MAXLEN;++i){
		if(ary[i].word == NULL) break;
		else s += ary[i].count;
	}
	return s;
}

//配列の各要素の文字列の出現頻度を求める.
//param: ary 要素が格納されている配列のポインタ
//param: sum 配列に格納されている文字列の出現回数の合計
void arrayAllWordFreq(const Word* ary, int sum){
	int i;
	for(i = 0;i < MAXLEN;++i){
		if(ary[i].word == NULL) break;
		else{
			double f = ary[i].count / (double)sum;
			printf("%s : %.5f\n", ary[i].word, f * 100);
		}
	}
	return;
}
