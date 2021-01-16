#pragma once


namespace ph::data_structures{




template <class Element>
class stack
{
      using self = stack<Element>;
      
private:
      Element* m_element;
      self*    m_rest;
      
public:
      bool empty () const {
            return m_rest == nullptr and m_element == nullptr;
      }
      Element& top () {
            return *m_element;
      }
      self& pop () {
            assert (!empty());
            return *m_rest;
      }
      
      friend self makeStack (Element const& element, self st) {
            
            return {};
      }
      
      stack () : m_element (nullptr), m_rest (nullptr) {
            
      }
      stack (Element const& element) : m_element (new Element(element)), m_rest (new self) {
            
      }
      
      // pushes "element" on top of stack
      stack (Element const& element, self push) : m_element (new Element(element)), m_rest (new self(push)){
            cout << push << endl;
//            *m_rest->m_element = element;
//            swap (*this, push);
//            swap (m_element, push.m_element);
            
            
            /**
                  2
             1
             */
            
//            cout << push << endl;
//            m_rest = new self(push);
            
//            cout << "{" << endl;
//            cout << "\t" << *this << endl;
//            cout << "\t" << push << endl;
//            cout << "}" << endl;
//            swap (*this, push);
//
//            cout << "{" << endl;
//            cout << "\t" << *this << endl;
//            cout << "\t" << push << endl;
//            cout << "}" << endl;
//            cout << *m_rest << endl;
            
      }
      stack (self const& other) : m_element (nullptr), m_rest (nullptr) {
            if (other.m_element != nullptr)
                  m_element = new Element (*other.m_element);
            if (other.m_rest != nullptr)
                  m_rest = new self (*other.m_rest);
      }
      stack (self&& other) : stack () {
            swap (*this, other);
      }
      
      friend void swap (self& lhs, self& rhs) {
            using std::swap;
            swap (lhs.m_element, rhs.m_element);
            swap (lhs.m_rest, rhs.m_rest);
      }
      friend ostream& operator<<(ostream& os, self const& s) {
            if ( !s.empty() ) {
                  os << *s.m_element << " " << *s.m_rest;
            }
            return os;
      }
      
};




}
