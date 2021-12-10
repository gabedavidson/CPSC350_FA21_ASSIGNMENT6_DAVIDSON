#ifndef BST_H
#define BST_H
#include <iostream>

using namespace std;

template <class T>
class TreeNode{
  public:
    TreeNode();
    TreeNode(T k);
    virtual ~TreeNode();

    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

template <class T>
TreeNode<T>::TreeNode(){
  left = NULL;
  right = NULL;
  key = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T k){
  left = NULL;
  right = NULL;
  key = k;
}

template <class T>
TreeNode<T>::~TreeNode(){
  left = NULL;
  right = NULL;
}

template <class T>
class BST{
  public:
    BST();
    virtual ~BST();
    void insert(T val);
    T search(T val);
    bool contains(T val);
    bool deleteNode(T k);
    bool isEmpty();

    T* getMin();
    T* getMax();
    TreeNode<T> *getSuccessor(TreeNode<T> *d); // d represents the node we are going to delete
    void printNodes();
    void recPrint(TreeNode<T> *node);
    int getSize() { return size; }

  private:
    TreeNode<T> *root;
    int size;
};

template <class T>
BST<T>::BST(){
  root = NULL;
  size = 0;
}

template <class T>
BST<T>::~BST(){
}

template <class T>
void BST<T>::recPrint(TreeNode<T> *node){
  if (node == NULL){
    return;
  }
  recPrint(node->left);
  cout << node->key << endl;
  recPrint(node->right);
}

template <class T>
void BST<T>::printNodes(){
  recPrint(root);
}

template <class T>
bool BST<T>::isEmpty(){
  return (root == NULL);
}

template <class T>
T* BST<T>::getMin(){
  if (isEmpty()){
    return NULL;
  }
  TreeNode<T> *curr = root;
  while (curr->left != NULL){
    curr = curr->left;
  }
  return &(curr->key);
}

template <class T>
T* BST<T>::getMax(){
  if (isEmpty()){
    return NULL;
  }
  TreeNode<T> *curr = root;
  while (curr->right != NULL){
    curr = curr->right;
  }
  return &(curr->key);
}

template <class T>
void BST<T>::insert(T val){
  TreeNode<T> *node = new TreeNode<T>(val);
  ++size;

  if (isEmpty()){
    root = node;
  }
  else {
    TreeNode<T> *curr = root;
    TreeNode<T> *parent = NULL;

    while (true){
      parent = curr;

      if (val < curr->key){
        curr = curr->left;
        if (curr == NULL){
          parent->left = node;
          break;
        }
      }
      else {
        curr = curr->right;
        if (curr == NULL){
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <class T>
T BST<T>::search(T val){
  if (isEmpty()){
    throw runtime_error("Database is empty");
  }
    TreeNode<T> *curr = root;

    while (val != curr->key){
      if (val < curr->key){
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
      if (curr == NULL){
        throw runtime_error("None found");
      }
    }
    return curr->key;
}

template <class T>
bool BST<T>::contains(T val){
  if (isEmpty()){
    return false;
  }

  TreeNode<T> *curr = root;

  while (curr->key != val){
    if (val < curr->key){
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
    if (curr == NULL){
      return false;
    }
  }
  return true;
}

template <class T>
bool BST<T>::deleteNode(T k){
  if (isEmpty()){
    return false;
  }

  TreeNode<T> *curr = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;

  while (curr->key != k){
    parent = curr;
    if (k < curr->key){
      isLeft = true;
      curr = curr->left;
    }
    else {
      isLeft = false;
      curr = curr->right;
    }
    if (curr == NULL){
      return false;
    }
  }

  // no children, is leaf node
  if (curr->left == NULL && curr->right == NULL){
    if (curr == root){
      root = NULL;
    }
    else if (isLeft){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }
  else if (curr->right == NULL){
    // node to delete has a left child
    if (curr == root){
      root = curr->left;
    }
    else if (isLeft){
      parent->left = curr->left;
    }
    else {
      parent->right = curr->left;
    }
  }
  else if (curr->left == NULL){
    // node to delete has a right child
    if (curr == root){
      root = curr->right;
    }
    else if (isLeft){
      parent->left = curr->right;
    }
    else {
      parent->right = curr->right;
    }
  }
  else {
    // node to delete has two children
    TreeNode<T> *successor = getSuccessor(curr);
    if(curr == root){
      root = successor;
    }
    else if(isLeft){
      parent->left = successor;
    }
    else{
      parent->right = successor;
      successor->left = curr->left;
      curr->left = NULL;
      curr->right = NULL;
    }
    delete curr;
    return true;

  }
}

template<class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;
  TreeNode<T> *curr = d->right;
  while(curr!=NULL){
      sp = successor;
      successor = curr;
      curr = curr->left;
  }
  //we found successor but we need to make sure successor is a descendent of the right child
  if(successor!= d->right){
      sp->left = successor->right;
      successor->right = d->right;
  }
  return successor;

}

#endif
