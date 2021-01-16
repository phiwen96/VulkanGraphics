#pragma once

template <class T>
struct BinaryTree
{
      
      using self = BinaryTree<T>;
      T* m_element;
      BinaryTree<T>* m_left;
      BinaryTree<T>* m_right;
      BinaryTree<T>* m_parent;
      
      BinaryTree () : m_parent (nullptr), m_element (nullptr), m_left (nullptr), m_right (nullptr) {
            
      }
      BinaryTree (T const& element) : m_parent (nullptr), m_element (new T(element)), m_left (nullptr), m_right (nullptr){
            
      }
      BinaryTree (BinaryTree<T>* parent) : m_parent (parent), m_element (nullptr), m_left (nullptr), m_right (nullptr){
            
      }
      BinaryTree (self* parent, self* left, T* element, self* right) : m_parent (parent), m_left (left), m_element (element), m_right (right) {
            if (left != nullptr)
            left->m_parent = this;
            if (right != nullptr)
            right->m_parent = this;
      }
      
      ~BinaryTree () {
            delete m_element;
            delete m_left;
            delete m_right;
      }
      
};
