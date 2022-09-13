#include <iostream>
#include <vector>

template<class T>
struct node {
    T val = 0;
    node *next = nullptr;
};

template<class T>
node<T> *make_node(T val) {
    node<T> *p = new node<T>;
    p->val = val;
    return p;
}

template<class T>
struct linked_list {
    node<T> *head;
    unsigned int siz = 0;

    linked_list() { head = new node<T>; }

    linked_list(const std::vector<T> &init) : linked_list() {
        auto it = head;
        for (auto x: init) {
            it->next = make_node(x);
            it = it->next;
            ++siz;
        }
    }

    node<T> *begin() { return head->next; }

    unsigned int size() { return siz; }

    void reverse(int l, int r) {
        if (l == r) return;
        auto it = head;
        for (int i = 0; i < l; ++i) it = it->next;
        auto L = it, prev = it;
        it = it->next;
        for (int i = l; i < r; ++i) {
            auto next = it->next;
            it->next = prev;
            prev = it;
            it = next;
        }
        L->next->next = it;
        L->next = prev;
    }

    void merge(linked_list &s) {
        if (s.size() == 0) return;
        head->val = s.begin()->val;
        auto &u = head, &v = s.head;
        while (v->next != nullptr) {
            if (u->next == nullptr) {
                u->next = v->next;
                break;
            }
            if (v->next->val < u->next->val) {
                auto p = v->next->next;
                v->next->next = u->next;
                u->next = v->next;
                u = u->next;
                v->next = p;
            } else {
                u = u->next;
            }
        }
        siz += s.size();
//        s.head->next = nullptr;
        head->val = T();
    }

    ~linked_list() {
        clear();
        delete head;
    }

    void clear() {
        auto it = begin();
        while (it) {
            auto p = it;
            it = it->next;
            delete p;
        }
        siz = 0;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    linked_list<int> s(a), t(b);
    s.merge(t);
    s.reverse(0, s.size());

    for (auto it = s.begin(); it != nullptr; it = it->next) {
        std::cout << it->val << " ";
    }
    std::cout << "\n";

    return 0;
}


// input:
// 7 8
// 1 3 5 8 9 10 14
// 2 3 4 5 8 14 17 32

// output:
// 32 17 14 14 10 9 8 8 5 5 4 3 3 2 1