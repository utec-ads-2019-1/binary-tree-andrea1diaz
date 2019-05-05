#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"

template <typename T>
class Iterator {
    private:
        Node<T> *current;

    public:
        Iterator() : current(nullptr) {};

        Iterator(Node<T> *node) : current(node) {};

        Iterator<T> operator=(Iterator<T> other) {
          return this->current = other.current;
        }

        bool operator!=(Iterator<T> other) {
          return !(this->current == other.current);
        }

        Iterator<T> operator++() {
          this->current = this->current->next;
          return *this;
        }

        Iterator<T> operator--() {
          
        }

        T operator*() {
            return this->current->data;
        }
};

#endif
