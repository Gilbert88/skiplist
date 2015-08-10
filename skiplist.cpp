#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std;

struct SkipNode
{
	/* data */
	int val;
	int level;
	SkipNode* forward[1];
};

class Skip_list
{
public:
	Skip_list();
	~Skip_list();
	/* data */
	SkipNode* search(int value);
	SkipNode* insert(int value);
	//ool remove(int value);

private:
	int maxlevel;
	SkipNode* head;
	int randomLevel();
	SkipNode* createNode(int value, int level);
	void adjustHead(int newLevel);
};

Skip_list::Skip_list(){
	head = new SkipNode();
	head->level = 0;
	head->forward[0] = NULL;
	maxlevel = 0;
}

Skip_list::~Skip_list(){
	SkipNode* ptr = head;
	SkipNode* pre = ptr;
	while(pre->forward[0]){
		ptr = ptr->forward[0];
		delete pre;
		pre = ptr;
	}
	delete ptr;
}

int Skip_list::randomLevel(){
	int level = 0;
	while(rand() % 2 == 0)
		level++;
	return level;
}

SkipNode* Skip_list::createNode(int value, int level){
	SkipNode* node = (SkipNode*) operator new(sizeof(SkipNode) + sizeof(SkipNode*)*level);
	if(node == NULL) return node;

	node->val = value;
	node->level = level;
	for(int i = 0; i <= level; i++){
		node->forward[i] = NULL;
	}
	return node;
}

void Skip_list::adjustHead(int newLevel){
	SkipNode* node = (SkipNode*) operator new(sizeof(SkipNode) + sizeof(SkipNode*)*newLevel);
	for(int i = 0; i <= newLevel; i++)
		node->forward[i] = NULL;
	memcpy(node->forward, head->forward, sizeof(SkipNode*)*(maxlevel+1));
	delete head;
	head = node;
}

SkipNode* Skip_list::insert(int value){
	int newLevel = randomLevel();
	if(newLevel > maxlevel){
		adjustHead(newLevel);
		maxlevel = newLevel;
	}
	SkipNode* node = head;
	SkipNode** update = new SkipNode*[maxlevel+1];
	for(int i = maxlevel; i >= 0; i--){
		while(node->forward[i] && node->forward[i]->val < value)
			node = node->forward[i];
		update[i] = node;
	}
	node = createNode(value, newLevel);
	for(int i = 0; i <= newLevel; i++){
		node->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = node;
	}
	delete[] update;
	return node;
}

SkipNode* Skip_list::search(int value){
	SkipNode* node = head;
	for(int i = maxlevel; i >= 0; i--){
		while(node->forward[i] && node->forward[i]->val < value)
			node = node->forward[i];
	}
	node = node->forward[0];
	if(!node || node->val != value)
		return NULL;
	else
		return node;
}

int main(){
	Skip_list sl;
	for(int i = 0 ; i < 100; i++)
		sl.insert(i);
	SkipNode* node = sl.search(99);
	if(node)
		cout << "found 99" << endl;
	else
		cout << "not found 99" << endl;
	node = sl.search(101);
	if(node)
		cout << "found 101" << endl;
	else
		cout << "not found 101" << endl;
}
