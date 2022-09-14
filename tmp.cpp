#include<iostream>
#include<stack>

using namespace std;

int main() {
    stack<int> s;
    int e;
    int N, d;
    cin >> N >> d;
    if (d == 2 || d == 8 || d == 16) {
        while (N) {
            s.push(N % d);   //将N与d求余得到的d进制数压入栈
            N = N / d;
        }
    }
    while (!s.empty()) {

        e = s.top();  //获取栈顶元素e

        s.pop();    //弹出栈顶元素
        if (e >= 10)
            cout << char('a' + e - 10);
        else
            cout << e;
    }
    cout << endl;
    return 0;
}