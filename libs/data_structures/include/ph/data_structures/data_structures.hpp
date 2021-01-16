#pragma once
#include <ph/common/array.hpp>
template <class value_type>
class träd
{
      using reference_const = value_type const&;
      using pointer = value_type*;
      using self = träd<value_type>;
      using arr = ph::array<träd<value_type>>;
      
public:
      bool leaf () const {return m_children == nullptr;}
      
      
      träd (reference_const value) : m_children (nullptr), m_value (value) {}
      
      template <class... U>
      träd (reference_const value, self const& n1, U const&... u) : m_children (new arr{n1, u...}), m_value (value) {
            
      }
      
      friend ostream& operator<< (ostream& os, self const& s) {
            os << s.m_value << endl;
            
            if ( s.m_children ) {
                  for (int i = 0; i < s.m_children->size(); ++i)
                  os << "\t" << (*s.m_children)[i];
            }
            return os;
      }
      
private:
      arr* m_children;
      value_type m_value;
};

template <class... T>
träd (T...) -> träd<common_type_t<T...>>;
