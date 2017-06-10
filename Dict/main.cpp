#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Dict.h"

int main()
{	
	trie t;
	t.insert("aswe");
	t.insert("intji");
	system("pause");
}

bool is_prime(int x)
{
	int j; 
	for (j = 2; j < sqrt(x); j++)
		if (!(x % j))
			return false;
	return true;
}
void sum()
{
	int i, s = 0;
	for (i = 1; i <= 100; i++)
		s = s + i;
}
void aver()
{
	int grades[5] = { 90, 80, 86, 75, 95 }, i, s=0;
	for (i = 0; i < 5; i++)
		s = s + grades[i];
	s = s / 5;
}
void func(int k)
{
	int a[20], i, num;
	scanf_s("%d", &num);
	for (i = 0; num != 0 && i < 20; i++)
	{
		int s = num % k; //取余数
		num =num / k; //取商 
		a[i] = s;
	}
	for (i--; i >= 0; i--)
		printf("%d", a[i]);
}
/*										 i				
	11 / 2 = 5...1			   [0][1][2][3][4]    
	5  / 2 = 2...1    a[20] = { 1, 1, 0, 1, 0, 0, 0...}
	2  / 2 = 1...0
	1  / 2 = 0...1
*/