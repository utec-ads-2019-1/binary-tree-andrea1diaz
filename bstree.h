#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T>
class BSTree {
    private:
        Node<T> *root;

    public:
        BSTree() : root(nullptr) {};

        // Node<T>* find_func(Node<T>* node, T data) {
        //   if (node == NULL) {
        //     return NULL;
        //   }
        //
        //
        //   if (data < node->data) {
        //     node->left = find_func(node->left, data);
        //   }
        //
        //
        //   if (data > node->data) {
        //     node->right = find_func(node->right, data);
        //   }
        //
        //   if (data == node->data) {
        //     std::cout << "node found: " << node->data << '\n';
        //     return true;
        //   }
        //
        //   else {
        //     return false;
        //   }
        // }


        // bool find(T data) {
        //   std::cout << "recived: " << tmp << '\n';
        //
        //   if(find_func(root, data)) {
        //     return true;
        //   }
        //
        //   std::cout << "FOUND!" << '\n';
        //   return false;
        // }

        bool find(T data) {
          Node<T>* tmp = root;

          while (tmp != NULL) {
            if (data < tmp->data) {
              if (tmp->left == NULL) return false;
              tmp = tmp->left;
            }


            if (data > tmp->data) {
              if (tmp->right == NULL) return false;
              tmp = tmp->right;
            }

            if (data == tmp->data) {
              return true;
            }
          }

          return false;
        }


        Node<T>* insert_func(Node<T>* node, T data) {
          if (node == NULL) {
            node = new Node<T>;
            root = node;
            root->left = NULL;
            root->right = NULL;
            root->data = data;
          }


          if (data < node->data) {
            node->left = insert_func(node->left, data);
            root = node;
          }


          if (data > node->data) {
            node->right = insert_func(node->right, data);
            root = node;
          }

          return node;
        }


        bool insert(T data) {
          Node<T>* tmp = insert_func(root, data);

          if (tmp != NULL) {
            return true;
          }


          else {
            return false;
          }
        }

        Node<T>* min_node(Node<T>* node) {
          if (node == NULL) {
            return NULL;
          }

          if (node->left == NULL) {
            return node;
          }

          return min_node(node->left);
        }


        Node<T>* max_node(Node<T>* node) {
          if (node != NULL) {
            while (node->right != NULL) {
              node = node->right;
            }
          }

          return node;
        }


        Node<T>* remove_aux(Node<T>* node, T data) {
          if (node == NULL)  {
            return node;
          }


          if (data < node->data) {
            node->left = remove_aux(node->left, data);
          }

          else if (data > node->data) {
            node->right = remove_aux(node->right, data);
          }


          else {
            Node<T>* tmp = node;

            if (root->left == NULL && node->right == NULL) {
        			delete node;
        			node = NULL;
        		}

            else if (node->left == NULL) {
              node = node->right;
        			delete tmp;
        		}

        		else if (node->right == NULL) {
              node = node->left;
        			delete tmp;
        		}

            else {
              node->data = min_node(node->right)->data;
              node->right = remove_aux(node->right, node->data);
            }
          }

          return node;
        }


        bool remove(T data) {
          if (remove_aux(root, data)) {
            return true;
          }

          else {
            return false;
          }
        }


        unsigned int count(Node<T>* node) {
          if (node == NULL) {
            return 0;
          }

          unsigned int left = count(node->left);
          unsigned int right = count(node->right);

          return (left + right + 1);
        }


        unsigned int size() {
          if (root == NULL) {
            return 0;
          }

          unsigned int n = count(root);

          return n;
        }


        void traversePreOrder_aux(Node<T>* node) {
          if (node != NULL) {
            std::cout << node->data << std::endl;
            traversePreOrder_aux(node->left);
            traversePreOrder_aux(node->right);
          }
        }


        void traversePreOrder() {
          traversePreOrder_aux(root);
        }


        void traverseInOrder_aux(Node<T>* node) {
          if (node != NULL) {
            traverseInOrder_aux(node->left);
            std::cout << node->data << std::endl;
            traverseInOrder_aux(node->right);
          }
        }


        void traverseInOrder() {
          traverseInOrder_aux(root);
        }


        void traversePostOrder_aux(Node<T>* node) {
          if (node != NULL) {
            traversePostOrder_aux(node->left);
            traversePostOrder_aux(node->right);
            std:cout << node->data << std::endl;
          }
        }

        void traversePostOrder() {
          traversePostOrder_aux(root);
        }

        Iterator<T> begin() {
          return Iterator<T>(root);
        }

        Iterator<T> end() {
          return Iterator<T>(max_node(root));
        }

        void destroy(Node<T>* node) {
          if (node != NULL) {
            destroy(node->left);
            destroy(node->right);
            delete(node);
          }

          node = NULL;
        }

        ~BSTree() {
          destroy(root);
        }
};

#endif
