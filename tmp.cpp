#include <stdio.h>
#include <stdlib.h>

#define M 100
struct node {
	int i, j, v;
};

struct tripletable {
	struct node S[M];
	int m, n, t;
};


struct tripletable* create() {
	int i;
	struct tripletable* head = (struct tripletable*) malloc(sizeof(struct tripletable));
	scanf("%d%d%d", &(head->m), &(head->n), &(head->t));

	for (i = 0; i < head->t; i++)
		scanf("%d%d%d", &(head->S[i].i), &(head->S[i].j), &(head->S[i].v));
	return head;

}


void print(struct tripletable* head) {
	int i;
	for (i = 0; i < head->t; i++)
		printf("%d %d %d\n", (head->S[i].i), (head->S[i].j), (head->S[i].v));
}

struct tripletable* trans(struct tripletable* t1) {
	int i, p, j, q, k;
	int num[100];
	int cpot[100];
	struct tripletable* t2 = (struct tripletable*) malloc(sizeof(struct tripletable));
	t2->m = t1->n;
	t2->n = t1->m;
	t2->t = t1->t;
	if (t1->t) {
		for (i = 0; i < t1->n; i++) num[i] = 0;
		for (i = 0; i < t1->t; i++) {
			k = t1->S[i].j;
			++num[k];
		}
		cpot[0] = 0;
		for (i = 1; i < t1->n; i++)
				cpot[i] = cpot[i - 1] + num[i - 1];
		for (p = 0; p < t1->t; p++) {
			j = t1->S[p].j;
			q = cpot[j];
			t2->S[q].i = t1->S[p].j;
			t2->S[q].j = t1->S[p].i;
			t2->S[q].v = t1->S[p].v;
			cpot[j]++;
		}

	}
	return t2;
}

int main() {
	struct tripletable* head, * t2;
	head = create();
	t2 = trans(head);
	print(t2);
	return 0;
}