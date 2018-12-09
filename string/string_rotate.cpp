#include <iostream>
#include <string>
using namespace std;

void ReverseString(char* s, unsigned int from, unsigned int to)
{
	char temp = 0;
	while (from < to) {
		temp = s[from];
		s[from++] = s[to];
		s[to--] = temp;
	}
}

//(X'Y')' = YX
void LeftRotateString(char*s, unsigned int len, unsigned int k)
{
	k = k % len;
	ReverseString(s, 0, k-1);  
	ReverseString(s, k, len - 1);
	ReverseString(s,0,len-1);
}

/*
int main()
{
	char a[7] = "abcdef";
	LeftRotateString(a, strlen(a), 2);
	cout << strlen(a) << endl;
	for (unsigned int k = 0; k < strlen(a); ++k) {
		cout << a[k];
	}
	cout << endl;
	system("pause");
	return 0;
}
*/