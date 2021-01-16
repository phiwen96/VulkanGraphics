#pragma once
#include "BinaryTree.hpp"


struct Token
{
      virtual double eval (BinaryTree<Token>&) = 0;
};



struct Number : Token
{
      double m_number;
      Number (double number) : m_number (number) {
            
      }
      virtual double eval (BinaryTree<Token>&){
            cout << "number: " << m_number << endl;
            return m_number;
      }
};

struct Plus : Token
{
//      Token* m_left;
//      Token* m_right;
      virtual double eval (BinaryTree<Token>& tree){
            cout << "+" << endl;
//            return 0;
            if (tree.m_left == nullptr)
                  cout << "oops" << endl;
            return tree.m_left->m_element->eval(*tree.m_left) + tree.m_right->m_element->eval(*tree.m_right);
      }
};

struct Minus : Token
{
      Token* m_left;
      Token* m_right;
      virtual double eval (BinaryTree<Token>& tree){
            return tree.m_left->m_element->eval(*tree.m_left) - tree.m_right->m_element->eval(*tree.m_right);
      }
};
