#include <ctype.h>
#include <stack>
#include <iostream>
#include "dict.h"

int get_index(char c)
{
	return int(c) - 97;
};

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

trie::trie()
{
	node *r = new node('\0', nullptr);
	root_ = r;
	size_ = 0;
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

void trie::list(node * r) const
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
		list(r->first());
	if (r->next() != nullptr)
		list(r->next());
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

