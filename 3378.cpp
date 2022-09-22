#include<iostream>

using namespace std;

const int N = 1e6+100;

int heap[N],arr[N],now,tail;

void push(int k)
{
	heap[++tail] = k;
	now = tail;
	while(now>1){
		if(heap[now] >= heap[now / 2])return;
		swap(heap[now],heap[now / 2]);
		now /= 2;
	}
}

int pop(){
	int res =heap[1];
	heap[1] = heap[tail--];
	tail = now = 0;
	while(now * 2 <= tail){
		int nxt = now * 2;
		if(nxt < tail && heap[nxt+1] < heap[nxt])nxt++;
		if(heap[now] <= heap[nxt])return res;
		swap(heap[now],heap[nxt]);
		now = nxt;
	}
}

int main(){
	int n;
	cin>>n;
	tail = 0;
	while(n--){
		int x;
		cin>>x;
		if(x == 1){
			int y;
			cin>>y;
			push(y);
		} else if(x==2){
			cout<<heap[1]<<endl;
		}else {
			pop();
		}
	}
}