#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector <char>a, b;
	vector <int>c;
	char ch;
	while(cin.get(ch))
	{
		if(ch != ' ')
		{
			a.push_back(ch);
		}
		else
		{
			break;
		}
	}
	while(cin.get(ch))
	{
		if(ch != '\n')
		{
			b.push_back(ch);
		}
		else
		{
			break;
		}
	}
	bool flag = 0;
	int i, j, k, sum;
	while(a.size() > b.size())
	{
		b.insert(b.begin(),	'0');
	}
	while(a.size() < b.size())
	{
		a.insert(a.begin(), '0');
	}
	for(i = a.size()-1, j = b.size()-1; i >=0 && j >= 0; i--, j--)
	{
		if(flag == 0)
		{
			sum = int(a[i]) + int(b[j]) - 96;
		}
		else
		{
			sum = int(a[i]) + int(b[j]) - 96 + 1;
		}
		if(sum >= 10)
		{
			c.push_back(sum-10);
			flag = 1;
		}
		else
		{
			c.push_back(sum);
			flag = 0;
		}
	}
	if(flag == 1)
	{
		cout << 1;
	}
	for(k = c.size()-1; k >= 0; k--)
	{
		cout << c[k];
	}
	return 0;
}