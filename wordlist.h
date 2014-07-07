#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct wordlist{
	//保存する単語
	char* word;
	//単語の出現回数
	int count;
	//次のノードへのポインタ
	struct wordlist* next;
}WordList;

WordList* listInsert(WordList*, const char*);
int listWordCount(WordList*, const char*);
int listAllWordCount(const WordList*);
double listWordFreq(WordList*, const char*);
void listAllWordFreq(WordList*, int);

//リストに内容を追加する.
//param: p リストの要素を示すポインタ.
//param: _word リストに追加する文字列.
//return 要素を追加した後のリストのポインタ
WordList* listInsert(WordList* p, const char* _word){
	if(p == NULL){
		WordList* ham = (WordList*)malloc(sizeof(WordList));
		ham->word = (char*)malloc(sizeof(char) * (strlen(_word) + 1));
		strcpy(ham->word, _word);
		ham->count = 1;
		ham->next = NULL;
		return ham;
	}
	else if(strcmp(p->word, _word) == 0){
		++p->count;
		return p;
	}
	else{
		p->next = listInsert(p->next, _word);
		return p;
	}
}

//リストに特定の文字列が保存されているかを調べる.
//param: p リストの要素を示すポインタ.
//param: _word 検索対象の文字列.
//return 文字列が追加されていればその出現回数を, そうでなければ-1
int listWordCount(WordList* p, const char* _word){
	if(p == NULL) return -1;
	if(strcmp(p->word, _word) == 0){
		return p->count;
	}
	else{
		return listWordCount(p->next, _word);
	}
}

//リストに保存されている文字列の出現回数の合計を返す.
//param: p リストの要素を示すポインタ
int listAllWordCount(const WordList* p){
	if(p == NULL) return 0;
	else return p->count + listAllWordCount(p->next);
}

//リストに保存されている特定の文字列の出現頻度を返す.
//param: p リストの要素を示すポインタ
//param: word 出現頻度を調べる文字列
//return 文字列が存在すればその文字列の出現頻度, そうでなければ-1
double listWordFreq(WordList* p, const char* _word){
	int s = listAllWordCount(p), a = listWordCount(p, _word);
	if(a < 0) return (double)a;
	else return a / (double)s;
}

//リストの各要素の文字列の出現頻度を求める.
//param: p 要素が格納されているリストのポインタ
//param: sum リストに格納されている文字列の出現回数の合計
void listAllWordFreq(WordList* p,int sum){
	if(p == NULL) return;
	double f = p->count / (double)sum;
	printf("%s : %.5f\n", p->word, f * 100);
	listAllWordFreq(p->next, sum);
	return;
}
