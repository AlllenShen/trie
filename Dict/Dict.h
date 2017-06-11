#ifndef DICT_H
#define DICT_H
#include <string>
#include <vector>
using namespace std;

int get_index(char);
vector<string> split(const string &, const string &);

class node
{
private:
	char char_;
	bool exist_;
	int freq_;
	int index_;
	vector<node*> child_;
	node* parent_;
public:
	node(char c='\0',node* parent=nullptr, 
			bool exi=false, int freq=0, int index=-1);
	char _char() { return char_; };
	bool exist() { return exist_; };
	void set_exist() { exist_ = true; }
	int freq() { return freq_; };
	void add_freq() { freq_++; };
	int index() { return index_; };
	vector<node*> child() { return child_; };
	node* parent() { return parent_; };
	node* next() const;
	node* first() const;
	void set_child(node*& r);
};
	
class trie
{
private:
	node* root_;
	int size_;
	
public:
	trie();
	~trie() { delete_(root_); };
	void delete_(node* r);
	node* find(string word, bool ins = false);
	void eraser(string word);
	void insert(string word) { find(word, true); };
	vector<string>::iterator list(vector<string> & v) const
	{
		list(root_, v);
		vector<string>::iterator it = v.begin();
		return it;
	};
	void list(node* r) const;
	void preshow(string words) const;
	void dump();
	void load();
	void generat_tree_by_text();
	void generat_index();
	void list(node* r, vector<string> & v) const;
};

#endif // !DICT_H
