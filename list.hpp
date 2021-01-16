#pragma once

namespace ph::data_structures
{




template <class...>
class list;




template <class T>
class doubly;


template <class Element>
class list<doubly<Element>>
{
      using self = list<doubly<Element>>;
public:
      bool empty () const {
            return m_left == nullptr and m_right == nullptr;
      }
      self& left () {
            assert (m_left != nullptr);
            return *m_left;
      }
      self& right () {
            assert (m_right != nullptr);
            return *m_right;
      }
      Element& element () {
            assert (m_element != nullptr);
            return *m_element;
      }
      
      list () : m_element (nullptr), m_right (nullptr), m_left (nullptr) {
            
      }
      list (Element const& element) : m_element (new Element (element)), m_right (nullptr), m_left (nullptr) {
            
      }
      list (self left, Element const& element, self right) : m_element (new Element (element)), m_left (new self (left)), m_right (new self (right)) {
            m_left -> m_right = this;
            m_right -> m_left = this;
      }
      list (self left, Element const& element) : m_element (new Element (element)), m_left (new self (left)), m_right (nullptr) {
            
      }
      list (Element const& element, self right) : m_element (new Element (element)), m_left (nullptr), m_right (new self (right)) {
            
      }
      list (Element const& element, self* right) : m_element (new Element (element)), m_left (nullptr), m_right (right) {
            
      }
      list (self* left, Element const& element) : m_element (new Element (element)), m_left (left), m_right (nullptr) {
            
      }
      
      list (self const& other) : list () {
            if (other.m_element != nullptr)
                  m_element = new Element (*other.m_element);
            if (other.m_left != nullptr)
                  m_left = new self (*other.m_left);
            if (other.m_right != nullptr)
                  m_right = new self (*other.m_right);
      }
      list (self&& other) : list () {
            swap (*this, other);
      }
      
      friend ostream& operator<< (ostream& os, self const& s) {
            if (s.m_right == nullptr)
                  os << *s.m_element << " ";
            else
                  os << *s.m_element << " " << *s.m_right;
            return os;
      }
      friend void swap (self& lhs, self& rhs) {
            using std::swap;
            swap (lhs.m_element, rhs.m_element);
            swap (lhs.m_left, rhs.m_right);
            swap (lhs.m_right, rhs.m_right);
      }
      
private:
      Element*    m_element;
      self*       m_right;
      self*       m_left;
      
};



template <class T>
class list<T>
{
      using Rest = list<T>;
      using self = list<T>;
      using Element = T;
      
private:
      Element*          m_element;
      self*             m_rest;
      
public:
      Element&    first () {
            assert(m_element != nullptr);
            return *m_element;
      }
      Rest&       rest () {
            assert(m_rest != nullptr);
            return *m_rest;
      }
      Element&    last () {
            assert (!empty());
            if (rest().empty())
                  return first();
            else
                  return rest().last();
      }
      
      bool        empty () const {
            return m_rest == nullptr and m_element == nullptr;
      }
      
      
      
      list () : m_element (nullptr), m_rest (nullptr) {
            
      }
      list (Element const& element) : m_element (new Element(element)), m_rest (new Rest) {
            
      }
      list (Element const& element, self const& rest) : m_element (new Element(element)), m_rest (new self(rest)) {
            
      }
      list (list&& other) : list () {
            swap (*this, other);
      }
      list (list const& other) : m_element (nullptr), m_rest (nullptr) {
            if (other.m_element != nullptr) {
                  m_element = new Element(*other.m_element);
            }
            if (other.m_rest != nullptr) {
                  m_rest = new self(*other.m_rest);
            }
      }
      ~list () {
            delete m_element;
            delete m_rest;
      }
      
      self& operator += (self other) {
            if ( empty() ) {
                  swap(*this, other);
            } else {
                  rest() += other;
            }
            return *this;
      }
      self& operator += (Element other) {
            this->operator+=(self{move(other)});
            return *this;
      }
      self& operator = (self other) {
            swap(*this, other);
            return *this;
      }
      friend void swap (list& lhs, list& rhs) {
            using std::swap;
            swap (lhs.m_element, rhs.m_element);
            swap (lhs.m_rest, rhs.m_rest);
      }
      friend ostream& operator<< (ostream& os, list const& l) {
            if ( !l.empty() ) {
                  os << *l.m_element << " " << *l.m_rest;
            }
            return os;
      }
};































}
