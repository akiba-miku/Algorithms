#include<iostream>
#include<vector>
#include<string>

using std::vector;
using std::string;

class TrieTree{
private:
  struct TrieNode{
    int pass;
    int end;
    vector<TrieNode*> next;
    TrieNode():pass(0),end(0),next(26,nullptr){};
    ~TrieNode(){
      for(int i=0;i<26;i++){
        if(next[i]!=nullptr){
          delete next[i];
        }
      }
    }
  };
  typedef TrieNode Node;
private:
  Node *root;
public:
  TrieTree():root(nullptr){
    root = new TrieNode();
  }
  ~TrieTree(){
    delete root;
  }
  void insert(string word){
    Node* node = root;
    node->pass++;
    for(int i=0,index;i<word.size();i++){
      index = word[i]-'a';
      if(node->next[index]==nullptr){
        node->next[index]=new TrieNode();
      }
      node = node->next[index];
      node->pass++;
    }
    node->end++;
  }

  int search(string word){
    Node* node = root;
    for(int i=0,index;i<word.size();i++){
      index = word[i]-'a';
      if(node->next[index]==nullptr){
        return 0;
      }
      node = node->next[index];
    }
    return node->end;
  }

  int startsWith(string pre){
    Node* node = root;
    for(int i=0,index;i<pre.size();i++){
      index = pre[i] - 'a';
      if(node->next[index]==nullptr){
        return 0;
      }
      node = node->next[index];
    }
    return node->pass;
  }

  void delete(string word){

  }
};
int main(){

  return 0;
}