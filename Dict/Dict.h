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
	void set_freq(int f) { freq_ = f; };
	int index() { return index_; };
	void set_index(int i) { index_ = i; };
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
	string path_;
	string word_path_;
public:
	trie();
	trie(string file);
	~trie() { dump();  delete_(root_); };
	void delete_(node* r);
	node* find(string word, bool ins = false);
	void eraser(string word);
	void insert_from_file(string word, int index, int freq=0);
	void insert_new(string word, string prope,
						string meanning, string file="\0");
	using vec_str_iter = vector<string>::iterator;
	vec_str_iter list_iter(vector<string> & v) const
	{
		list(root_, v);
		vector<string>::iterator it = v.begin();
		return it;
	};
	void list_print(node* r) const;
	vector<string> preshow(string words) const;
	void dump();
	void load();
	void generat_tree_by_file(string file="\0");
	void list(node* r, vector<string> & v) const;
	void list_node(node* r, vector<node*> & v) const;
	void sort_by_freq(vector<node*> & v, 
						int begin, int end) const;
	void partition(vector<node*> & v, 
					int begin, int end, int & cutpoint) const;
	string word_of_node(node* n) const;
	vector<string> get_mean(string word);
	string word_of_line(string line);
};

#endif // !DICT_H
