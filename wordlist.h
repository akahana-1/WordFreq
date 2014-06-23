//#include <stdio.h>
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

//リストに存在する全ての要素のcountの合計を返す.
//param: p リストの要素を示すポインタ
int listAllWordCount(WordList* p){
	if(p == NULL) return 0;
	else return p->count + listAllWordCount(p->next);
}
