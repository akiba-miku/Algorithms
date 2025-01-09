template<class K, class V>
class AVLTree{

public:
  void add(K key, V value){
    Node* node = new Node(key, value);
    this->root = add(this->root, node);
  }
  bool contains(K key){
    return serach(root, key)!=NIL;
  }
  void remove(K key){
    
  }
private:
  void up(Node* node){
    node->size = node->left->size+node->right->size;
    node->height = max(node->left->height, node->right->height)+1;
  }
  Node* leftRotate(Node *node){
    Node* r = node->right;
    node->right = r->left;
    r->left = node;
    up(node);
    up(r);
    return r;
  }

  Node* rightRotate(Node* node){
    Node* l = node->left;
    node->left = l->right;
    l->right = node;
    up(node);
    up(l);
    return l;
  }

  Node* maintain(Node* node){
    int lh = node->left->height;
    int rh = node->right->height;
    if(lh-rh>1){
      if(node->left->right->height>node->left->left->height){
        node->left = leftRotate(node->left);
      }
      node = rightRotate(node);
    }else if(rh-lh>1){
      if(node->right->left->height>node->right->right->height){
        node->right = rightRotate(node->right);
      }
      node = leftRotate(node);
    }
    up(node);
    return node;
  }

  Node *add(Node* head, Node* node){
    if(head==NIL){
      return NIL;
    }
    if(head->key==node->key){
      head->count++;
    }else if(head->key>node->key){
      head->left = add(head->left, node);
    }else{
      head->right = add(head->right, node);
    }
    up(head);
    return maintain(head);
  }

  Node* search(Node* head, K key){
    if(head==NIL){
      return nullptr;
    }
    if(head->key==key){
      return head;
    }else if(head->key>key){
      return search(head->left, key);
    }else{
      return search(head->right, key);
    }
  }
private:
  struct Node{
    Node *left;
    Node *right;
    K key;
    V value;
    int count;
    int size;
    int height;

    Node(K key,V value):left(nullptr),right(nullptr),key(key),value(value),count(1),size(1),height(1){}
  };

  Node *root = nullptr;
  Node *NIL = new Node(new K(), new V());
};
