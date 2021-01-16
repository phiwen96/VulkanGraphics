#pragma once
#include "Token.hpp"
#include "BinaryTree.hpp"


template <class Context>
struct State
{
public:
      State (Context& context) : m_context (context), m_tokens (context.m_tokens) {}
      State (State* other) : m_context (other->m_context), m_tokens (other->m_tokens) {
            
      }
      
      virtual void process (char ch);
      virtual void process (int i);
      virtual ~State(){}
protected:
      Context& m_context;
      BinaryTree<Token>* m_tokens;
};





template <class Context>
struct NumberState : State<Context>
{
      using Base = State<Context>;
      int tio;
      int m_number;
      NumberState (int i, Base*);
      virtual ~NumberState(){}
      virtual void process (char ch);
      virtual void process (int i);
private:
      void finish(){
            Base::m_tokens -> m_element = new Number (m_number);
      }
};



template <class Context>
struct SignState : State<Context>
{
      using Base = State<Context>;
      SignState (Base* base) : Base (base) {
//            base -> m_tokens = new
      }
      virtual void process (int i) {
            BinaryTree<Token>* plus = new BinaryTree<Token> (Base::m_context.m_tokens->m_parent, Base::m_context.m_tokens, new Plus, nullptr);
//            Base::m_context.m_tokens -> m_parent -> m_right = plus;
            Base::m_context.m_tokens -> m_parent = plus;
//            Base::m_context.m_tokens -> m_parent = plus;
//            Base::m_context.m_tokens = plus;
            
            plus -> m_right = new BinaryTree<Token> (plus, nullptr, nullptr, nullptr);
            Base::m_context.m_tokens = plus -> m_right;

            Base::m_context.changeState (new NumberState<Context> (i, this));
      }
      
};





template <class Context>
void State<Context>::process (char ch)
{
      //      cout << "State::process " << ch << endl;
      if (ch - '0' >= 0 and ch - '0' <= 9)
      {
            m_context.changeState (new NumberState<Context> (ch-'0', this));
      }
      else if (ch >= 'a' and ch <= 'z'){
            cout << "char" << endl;
      }
      else {
            
      }
}

template <class Context>
void State<Context>::process (int i)
{
      m_context.changeState (new NumberState<Context> (i, this));
}

template <class Context>
NumberState<Context>::NumberState (int i, State<Context>* other) : State<Context>(other), m_number (i), tio (0)
{
      
}

template <class Context>
void NumberState<Context>::process (char ch)
{
      if (ch == '+') {
            Base::m_context.m_tokens -> m_element = new Number (m_number);
            Base::m_context.changeState (new SignState<Context> (this));
      }
      if (ch == '\n'){
            Base::m_context.m_tokens -> m_element = new Number (m_number);
            Base::m_context.m_tokens = Base::m_context.m_tokens -> m_parent;
      }
      
}

template <class Context>
void NumberState<Context>::process (int i)
{
      m_number *= 10;
      m_number += i;
}
