#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;
using std::cout;
using std::endl;

// 定义TrieTree类
class TrieTree {
private:
    // 定义TrieNode结构体
    struct TrieNode {
        int pass;                       // 经过该节点的单词数
        int end;                        // 以该节点结尾的单词数
        vector<TrieNode*> next;         // 指向26个小写字母的子节点指针

        // 构造函数
        TrieNode() : pass(0), end(0), next(26, nullptr) {}

        // 析构函数，递归删除子节点
        ~TrieNode() {
            for (int i = 0; i < 26; ++i) {
                if (next[i] != nullptr) {
                    delete next[i];
                    next[i] = nullptr;
                }
            }
        }
    };

    typedef TrieNode Node; // 简化类型名

private:
    Node* root; // 根节点

public:
    // 构造函数
    TrieTree() {
        root = new TrieNode();
    }

    // 析构函数
    ~TrieTree() {
        delete root;
    }

    // 插入单词
    void insert(const string& word) {
        if (word.empty()) return; // 空字符串不处理

        Node* node = root;
        node->pass++; // 根节点的pass增加

        for (char ch : word) {
            if (ch < 'a' || ch > 'z') {
                // 非小写字母字符，忽略或处理错误
                // 这里选择忽略非小写字母字符
                continue;
            }
            int index = ch - 'a';
            if (node->next[index] == nullptr) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
            node->pass++;
        }
        node->end++;
    }

    // 搜索单词出现次数
    int search(const string& word) const {
        if (word.empty()) return 0;

        Node* node = root;
        for (char ch : word) {
            if (ch < 'a' || ch > 'z') {
                // 非小写字母字符，单词不存在
                return 0;
            }
            int index = ch - 'a';
            if (node->next[index] == nullptr) {
                return 0;
            }
            node = node->next[index];
        }
        return node->end;
    }

    // 前缀查询，返回以pre为前缀的单词数
    int startsWith(const string& pre) const {
        if (pre.empty()) return 0;

        Node* node = root;
        for (char ch : pre) {
            if (ch < 'a' || ch > 'z') {
                // 非小写字母字符，前缀不存在
                return 0;
            }
            int index = ch - 'a';
            if (node->next[index] == nullptr) {
                return 0;
            }
            node = node->next[index];
        }
        return node->pass;
    }

    // 删除单词
    void remove(const string& word) {
        if (search(word) == 0) return; // 单词不存在，无法删除

        Node* node = root;
        node->pass--; // 根节点的pass减少

        // 记录遍历路径上的节点，用于可能的回溯删除
        vector<Node*> path;
        path.push_back(node);

        for (char ch : word) {
            if (ch < 'a' || ch > 'z') {
                // 非小写字母字符，无法删除
                return;
            }
            int index = ch - 'a';
            Node* nextNode = node->next[index];
            nextNode->pass--;
            path.push_back(nextNode);
            node = nextNode;
        }

        node->end--; // 单词结尾计数减少

        // 从后向前检查是否需要删除节点
        for (int i = word.size(); i >= 1; --i) {
            Node* currentNode = path[i];
            if (currentNode->pass == 0) {
                // 当前节点的pass为0，删除该节点
                Node* parentNode = path[i - 1];
                int index = word[i - 1] - 'a';
                delete parentNode->next[index];
                parentNode->next[index] = nullptr;
            } else {
                // 当前节点的pass不为0，其他单词仍在使用该节点
                break;
            }
        }
    }
};

// 测试用例
int main() {
    TrieTree trie;

    // 插入单词
    trie.insert("apple");
    trie.insert("apple");
    trie.insert("app");

    // 搜索单词出现次数
    cout << "apple 出现次数: " << trie.search("apple") << endl; // 输出 2
    cout << "app 出现次数: " << trie.search("app") << endl;     // 输出 1
    cout << "ap 出现次数: " << trie.search("ap") << endl;       // 输出 0

    // 前缀查询
    cout << "以 'ap' 为前缀的单词数: " << trie.startsWith("ap") << endl; // 输出 3

    // 删除单词
    trie.remove("apple");
    cout << "删除一个 'apple' 后，apple 出现次数: " << trie.search("apple") << endl; // 输出 1

    trie.remove("apple");
    cout << "删除一个 'apple' 后，apple 出现次数: " << trie.search("apple") << endl; // 输出 0

    trie.remove("app");
    cout << "删除一个 'app' 后，app 出现次数: " << trie.search("app") << endl; // 输出 0

    // 进一步测试
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bandana");

    cout << "banana 出现次数: " << trie.search("banana") << endl;   // 输出 1
    cout << "band 出现次数: " << trie.search("band") << endl;       // 输出 1
    cout << "bandana 出现次数: " << trie.search("bandana") << endl; // 输出 1
    cout << "以 'ban' 为前缀的单词数: " << trie.startsWith("ban") << endl; // 输出 3

    trie.remove("band");
    cout << "删除一个 'band' 后，band 出现次数: " << trie.search("band") << endl; // 输出 0
    cout << "以 'ban' 为前缀的单词数: " << trie.startsWith("ban") << endl; // 输出 2

    trie.remove("banana");
    cout << "删除一个 'banana' 后，banana 出现次数: " << trie.search("banana") << endl; // 输出 0
    cout << "以 'ban' 为前缀的单词数: " << trie.startsWith("ban") << endl; // 输出 1

    trie.remove("bandana");
    cout << "删除一个 'bandana' 后，bandana 出现次数: " << trie.search("bandana") << endl; // 输出 0
    cout << "以 'ban' 为前缀的单词数: " << trie.startsWith("ban") << endl; // 输出 0

    // 边界测试
    trie.insert(""); // 插入空字符串，不应影响Trie
    cout << "插入空字符串后，search('') 出现次数: " << trie.search("") << endl; // 输出 0
    cout << "插入空字符串后，startsWith('') 出现次数: " << trie.startsWith("") << endl; // 输出 0

    trie.remove(""); // 删除空字符串，不应影响Trie
    cout << "删除空字符串后，search('') 出现次数: " << trie.search("") << endl; // 输出 0

    // 插入包含非小写字母的单词
    trie.insert("Apple"); // 大写'A'，应被忽略
    cout << "插入 'Apple' 后，search('Apple') 出现次数: " << trie.search("Apple") << endl; // 输出 0
    cout << "插入 'Apple' 后，search('apple') 出现次数: " << trie.search("apple") << endl; // 输出 0

    trie.insert("apple");
    cout << "重新插入 'apple' 后，search('apple') 出现次数: " << trie.search("apple") << endl; // 输出 1

    return 0;
}
