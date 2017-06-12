#include <ctype.h>
#include <stack>
#include <iostream>
#include <direct.h>
#include <fstream>
#include "dict.h"

int get_index(char c)
{
	return int(c) - 97;
};
bool is_num(string c)
{
	for (auto i : c)
		if (!isdigit(i))
			return false;
	return true;
}
vector<string> split(const string &s, const string &seperator) 
{
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size())
	{
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) 
		{
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) 
				{
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) 
		{
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) 
				{
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) 
		{
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}
int str_to_int(string num)
{
	stack<int> container;
	bool minus = false;
	for (auto i : num)
	{
		if (!isdigit(i) && i != '-')
			return NULL;
		if (i == '-')
	}
}

node::node(char c, node * parent, bool exi, int freq, int index)
{
	char_ = c;
	parent_ = parent;
	exist_ = exi;
	freq_ = freq;
	index_ = index;
	child_.resize(26);
	for (int i = 0; i < 26; i++)
		child_[i] = nullptr;
}

void node::set_child(node *& r)
{
	int i = get_index(r->_char());
	child_[i] = r;
}

node * node::next() const
{
	if (!isalpha(char_))
		return nullptr;
	for (int i = get_index(char_) + 1; i < 26; i++)
		if (parent_->child()[i] != nullptr)
			return parent_->child()[i];
	return nullptr;
}

node * node::first() const
{
	for (int i = 0; i < 26; i++)
		if (child_[i] != nullptr)
			return child_[i];
	return nullptr;
}

trie::trie()
{
	node *r = new node('\0', nullptr);
	root_ = r;
	size_ = 0;
	char path[1000];
	_getcwd(path, 1000);
	path_ = path;
}

trie::trie(string file)
{
	node *r = new node('\0', nullptr);
	root_ = r;
	size_ = 0;
	char path[1000];
	_getcwd(path, 1000);
	path_ = path;
	generat_tree_by_file(file);
}

void trie::delete_(node * r)
{
	node* p = r->first();
	node* n = r->next();
	if (p != nullptr)
		delete_(p);
	if (n != nullptr)
		delete_(n);
	delete r;
}

node * trie::find(string word, bool ins)
{
	node *r = root_;
	bool has_ins = false;
	for (auto i : word)
		if (islower(i))
			i += 32;
	for (auto i : word)
	{
		int index = get_index(i);
		if (r->child()[index] == nullptr && ins)
		{
			node* new_node = new node(i, r);
			r->set_child(new_node);
			has_ins = true;
		}
		else if (r->child()[index] == nullptr && !ins)
			return nullptr;
		r = r->child()[index];
		r->add_freq();
	}
	if (has_ins)
		size_++;
	if (!r->exist())
		r->set_exist();
	return r;
}

void trie::eraser(string word)
{
	node *p = find(word), *t;
	if (p != nullptr)
	{
		t = p->parent();
		while (t != root_ && !t->exist())
		{
			delete p;
			p = t;
			t = t->parent();
		}
		delete p;
		size_--;
	}

}

void trie::insert_from_file(string word, int index)
{
	node* p = find(word, true);
	if (p->index() == -1)
		p->set_index(index);
}

void trie::list_print(node * r) const
{
	if (r->exist())
	{
		stack<char> word;
		node* temp = r;
		while (temp != root_)
		{
			word.push(temp->_char());
			temp = temp->parent();
		}
		while (!word.empty())
		{
			cout << word.top();
			word.pop();
		}
		cout << "  ";
	}
	if (r->first() != nullptr)
		list_print(r->first());
	if (r->next() != nullptr)
		list_print(r->next());
}

vector<string> trie::preshow(string words) const
{
	node* p = root_;
	for (auto i : words)
		p = p->child()[get_index(i)];	
	vector<node*> word_nodes;
	vector<string> word_list;
	if (p == nullptr)
		return word_list;
	vector<node*> exist_list;
	for (auto i : p->child())
		if (i != nullptr)
			exist_list.push_back(i);
	for (auto i : exist_list)
	{
		list_node(i, word_nodes);
		sort_by_freq(word_nodes, 0, word_nodes.size() - 1); 
		//每次使用同一个vector排序的设计是将排序算法独立与逻辑
		//需要优化时只更新排序算法而不发生逻辑变动
	}
	for (int i=0; i < word_nodes.size(); i++)
		for (int j = i + 1; j < word_nodes.size(); j++)
		{
			if (word_nodes[j] == word_nodes[i])
			{
				delete_item(word_nodes, word_nodes[j]);
				j--;
			}
		}
	//int count = 0, i = 0;
	//while (count < 10 && i < word_nodes.size())
	for (int i = 0; i < 10; i++)
	{
		string word = word_of_node(word_nodes[i]);
		/*for (int j = 0; j < word_list.size(); j++)
		{
			if (word_list[j] == word)
			{
				if (i++ >= word_nodes.size())
					word = word_of_node(word_nodes[i]);
				else
					continue;
				j--;
			}
		}*/
		word_list.push_back(word);
		//count++;
	}
		
	return word_list;
}

void trie::generat_tree_by_file(string file)
{
	if (file == "\0")
		file = path_ + "\\wordlist.txt";
	ifstream infile;
	infile.open(file.c_str());
	if (!infile)
		return;
	string line;
	while (getline(infile, line))
	{
		vector<string> line_part = split(line, " ");
		string word = line_part[1];
		if (is_num(word))
			return;
		insert_from_file(word, line_part[0]);
	}
}

void trie::list(node * r, vector<string>& v) const
{
	if (r->exist())
		v.push_back(word_of_node(r));
	if (r->first() != nullptr)
		list(r->first(), v);
	if (r->next() != nullptr)
		list(r->next(), v);
}

void trie::list_node(node* r, vector<node*> & v) const
{
	if (r->exist())
		v.push_back(r);
	if (r->first() != nullptr)
		list_node(r->first(), v);
	if (r->next() != nullptr)
		list_node(r->next(), v);
}

void trie::sort_by_freq(vector<node*>& v, int begin, int end) const 
{
	int i;
	if (begin < end)
	{
		partition(v, begin, end, i);
		sort_by_freq(v, begin, i - 1);
		sort_by_freq(v, i + 1, end);
	}
}

void trie::partition(vector<node*>& v, int begin, int end, int & cutpoint) const
{
	node* temp = v[begin];
	while (begin != end)
	{
		while (begin < end
			&& v[end]->freq() < temp->freq())
			end--;
		if (begin < end)
		{
			v[begin] = v[end];
			begin++;
		}
		while (begin < end
			&& v[begin]->freq() > temp->freq())
			begin++;
		if (begin < end)
		{
			v[end] = v[begin];
			end--;
		}
	}
	v[begin] = temp;
	cutpoint = begin;
}

string trie::word_of_node(node * n) const
{
	stack<char> word;
	string s = "\0";
	node* temp = n;
	while (temp != root_)
	{
		word.push(temp->_char());
		temp = temp->parent();
	}
	while (!word.empty())
	{
		s += word.top();
		word.pop();
	}
	return s;
}

void trie::delete_item(vector<node*> & list, node* item) const
{
	vector<node*>::iterator it = list.begin();
	while (it != list.end())
	{
		if ((*it) == item)
		{
			list.erase(it);
			return;
		}
		else
			it++;
	}
};
