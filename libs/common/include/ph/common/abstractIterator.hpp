#pragma once

template <class T, class iterator>
class AbstractIterator : public IteratorFacade<AbstractIterator<T, iterator>, T>
{
public:
      using size_type         = size_t;
      using value_type        = T;
      using reference         = value_type&;
      using const_reference   = value_type const&;
      using pointer           = value_type*;
      using const_pointer     = value_type const*;
      using pointer_const     = value_type * const;
      
      virtual reference dereference () const = 0;
      virtual void increment () = 0;
      virtual bool equals (iterator const& other) const = 0;
      virtual bool less (iterator const& other) const = 0;
};