#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<map>

using namespace std;

const int N = 100;

int n, m;

void handle_line(string &s)
{
	char last = '?';
	for (int i = 0; i < m; ++i) {
		if (s[i] == '?') {
			s[i] = last;
		}
		else {
			last = s[i];
		}
	}
	for (int i = m - 1; i >= 0; --i) {
		if (s[i] == '?') {
			s[i] = last;
		}
		else {
			last = s[i];
		}
	}
}

string s[N];

void work()
{
	cin >> n >> m;
	string qs;
	for (int i = 1; i <= m; ++i) {
		qs.push_back('?');
	}
	int st = -1;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		if (s[i] != qs) {
			st = i;
		}
	}
	handle_line(s[st]);
	for (int i = st - 1; i >= 1; --i) {
		if (s[i] == qs) {
			s[i] = s[i + 1];
		}
		else {
			handle_line(s[i]);
		}
	}
	for (int i = st + 1; i <= n; ++i) {
		if (s[i] == qs) {
			s[i] = s[i - 1];
		}
		else {
			handle_line(s[i]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << s[i] << endl;
	}
}

int main()
{
	freopen("my.in", "r", stdin);
	freopen("out.txt", "w", stdout);

	int q;
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		printf("Case #%d:\n", i);
		work();
	}
	return 0;
}
