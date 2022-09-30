#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <iomanip>
#include <stack>

using ll = long long;

struct A {
	float a;
	char opt;
	int type;

	A(char o, float d) : a(d), opt(o) {
		if (o != ' ')type = 1;
	}

	A() {}
};

double getd(std::string str) {
	int l = str.length();
	double ret = 0;
	int flag = 0;
	if (str[0] == '-' || str[0] == '+')flag = 1;
	int dot = 0;
	for (int i = flag; i < l; i++) {
		if (str[i] == '.') {
			dot = i;
			break;
		}
		ret = ret * 10 + str[i] - '0';
	}
	if (dot) {
		double z = 1;
		for (int i = dot + 1; i < l; i++) {
			z *= 0.1;
			ret += z * (str[i] - '0');
		}
	}
	if (str[0] == '-')ret *= -1;
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<A> ord;
	std::string str;
	while (std::cin >> str) {
		if (str == "+")ord.emplace_back('+', 0);
		else if (str == "-")ord.emplace_back('-', 0);
		else if (str == "*")ord.emplace_back('*', 0);
		else if (str == "/")ord.emplace_back('/', 0);
		else ord.emplace_back(' ', getd(str));
	}
	std::stack<A> s;
	std::reverse(ord.begin(), ord.end());
	for (int i = 0; i < ord.size(); ++i) {
		A temp = ord[i];
		if (temp.type == 0) {
			s.push(temp);
		} else {
			A num1 = s.top();
			s.pop();
			A num2 = s.top();
			s.pop();
			A res;
			res.type = 0;
			if (temp.opt == '+') {
				res.a = num1.a + num2.a;
			} else if (temp.opt == '-') {
				res.a = num1.a - num2.a;
			} else if (temp.opt == '*') {
				res.a = num1.a * num2.a;
			} else if (temp.opt == '/') {
				if (num2.a == 0) {
					std::cout << "ERROR\n";
					return 0;
				}
				res.a = num1.a / num2.a;
			}
			s.push(res);
		}
//		i--;
	}
	std::cout << std::fixed << std::setprecision(1) << s.top().a;
	return 0;
}