#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <vector>
#include <fstream>
#include <list>
#include <iomanip>
#include <numeric>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ms(s) memset(s, 0, sizeof(s))
const int inf = 0x3f3f3f3f;
const int N = 3e5 + 10;


bool isLeap(int y) {
	return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

int daysOfMonth(int y, int m) {
	int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (m != 2)
		return day[m - 1];
	else
		return 28 + isLeap(y);
}

int daysOfDate(int year, int month, int day) {
	for (int y = 1; y < year; y++)
		day += 365 + isLeap(y);
	for (int m = 1; m < month; m++)
		day += daysOfMonth(year, month);
	return day;
}


void solve() {
	string s;
	cin >> s;
	int sum = 0, year = 0, mon = 0, day = 0, f = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != '/') {
			s[i] -= '0';
			sum *= 10;
			sum += s[i];
		} else {
			if (f == 0) year = sum;
			else if (f == 1) mon = sum;
			sum = 0;
			f++;
		}
	}
	day = sum;
	//cout << year << mon <<day << endl;
	int x = daysOfDate(year, mon, day) - daysOfDate(2000, 1, 1);
	std::cerr << x << '\n';
	if (x % 5 == 0 || x % 5 == 1 || x % 5 == 2) {
		cout << "Fishing" << endl;
	} else cout << "Resting" << endl;

}

int main() {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}