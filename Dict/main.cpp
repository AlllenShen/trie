#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Dict.h"

int main()
{	
	string file = "\0";
	trie t(file);
	/*vector<string> v = t.preshow("ab");
	t.find("abuse");
	t.find("abroad");
	vector<string> m = t.preshow("ab");*/
	vector<string> m = t.get_mean("abnormal");
	system("pause");
}

