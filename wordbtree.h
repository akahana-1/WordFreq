#include <string.h>
#include <stdlib.h>

typedef struct bnode{
	//保存する単語
	char* word;
	//単語の出現回数.
	int count;
	//次のノードへのポインタ
	//strcmp(this->word, word) < 0でleft, そうでないときright
	struct bnode* left;
	struct bnode* right;
}WordTree;

WordTree* treeInsert(WordTree*, const char*);
int treeWordCount(WordTree*, const char*);
int treeAllWordCount(WordTree*);
double treeWordFreq(WordTree*, const char*);

//二分探索木に要素を追加する.
//param: p 二分探索木の要素を示すポインタ
//param: _word 二分探索木に追加する文字列
//return 要素を追加した後の二分探索木のポインタ
WordTree* treeInsert(WordTree* p, const char* _word){
	int res;
	if(p == NULL){
		WordTree* ham = (WordTree*)malloc(sizeof(WordTree));
		ham->count = 1;
		ham->left = NULL;
		ham->right = NULL;
		ham->word = (char*)malloc(sizeof(char) * (strlen(_word) + 1));
		strcpy(ham->word, _word);
		return ham;
	}
	res = strcmp(p->word, _word);
	if(res == 0){
		++p->count;
	}
	else if(res < 0){
		p->left = treeInsert(p->left, _word);
	}
	else{
		p->right = treeInsert(p->right, _word);
	}
	return p;
}

//二分探索木に特定の文字列が保存されているかを調べる.
//param: p 二分探索木の要素を示すポインタ
//param: _word 検索対象の文字列
//return 文字列が二分探索木内に存在すれば出現回数を, そうでなければ-1を返す.
int treeWordCount(WordTree* p, const char* _word){
	int res;
	if(p == NULL) return -1;
	res = strcmp(p->word, _word);
	if(res == 0){
		return p->count;
	}
	else if(res < 0){
		return treeWordCount(p->left, _word);
	}
	else{
		return treeWordCount(p->right, _word);
	}
}

//二分探索木に保存されている文字列の出現回数の合計を返す.
//param: p 二分探索木の要素を示すポインタ.
//return そのノードから下位のノードで構成される二分木における合計値.
int treeAllWordCount(WordList* p){
	if(p == NULL) return 0;
	else return p->count + treeAllWordCount(p->left) + treeAllWordCount(p->right);
}

//二分探索木に保存されている特定の文字列の出現頻度を返す.
//param: p 二分探索木の要素を示すポインタ.
//param: _word 出現頻度を調べる文字列
//return 文字列が存在すればその文字列の出現頻度, そうでなければ-1
double treeWordFreq(WordTree* p, const char* _word){
	int s = treeAllWordCount(p), a = treeWordCount(p, _word);
	if(a < 0) return (double)a;
	else return a / (double)s;
}
