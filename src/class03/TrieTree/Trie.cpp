#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
const int N = 1e6 + 10;
int tree[N][26];
int pass[N], end[N];
int cnt;
void build() {
    cnt = 1;
}
void clear() {
    for (int i = 1; i <= cnt; i++) {
        std::fill(tree[i], tree[i] + 26, 0);
        pass[i] = end[i] = 0;
    }
}
int search(std::string& word) {
    int cur = 1;
    for (int i = 0, path; i < word.size(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return end[cur];
}
int prefixNumber(std::string& word) {
    int cur = 1;
    for (int i = 0, path; i < word.size(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return pass[cur];
}
void insert(std::string& word) {
    int cur = 1;
    pass[cur]++;
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
    end[cur]++;
}

void remove(std::string& word) {
    if (search(word) == 0) return ;
    int cur = 1;
    pass[cur]--;
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';
        if (--pass[tree[cur][path]] == 0) {
            tree[cur][path] = 0;
            return ;
        }
        cur = tree[cur][path];
    }
    end[cur]--;
}
int main() {
    int n;
    scanf("%d", &n);
    int op;
    std::string word;
    build();
    for (int i = 0; i < n; i++) {
        std::cin >> op >> word;
        if (op == 1) {
            insert(word);
        } else if (op == 2) {
            remove(word);
        } else if (op == 3) {
            printf("%s\n", search(word) > 0 ? "YES" : "NO");
        } else {
            printf("%d\n", prefixNumber(word));
        }
    }
    clear();
    return 0;
}