#pragma once

template <class Derived, class Value, class Reference = Value&, class Distance = std::ptrdiff_t>
class IteratorFacade
{
public:
      using value_type        = typename std::remove_const_t<Value>;
      using reference         = Reference;
      using pointer           = value_type*;
      using difference_type   = Distance;
//      using iterator_category = Category;
      
      reference operator * () {
            return asDerived().dereference();
      }
      Derived& operator ++ () {
            asDerived().increment();
            return asDerived();
      }
      Derived operator ++ (int) {
            Derived result (asDerived());
            result.increment();
            return result;
      }
      friend bool operator == (IteratorFacade const& lhs, IteratorFacade const& rhs) {
            return lhs.asDerived().equals (rhs.asDerived());
      }
      friend bool operator != (IteratorFacade const& lhs, IteratorFacade const& rhs) {
            return ! (lhs == rhs);
      }
      friend bool operator < (IteratorFacade const& lhs, IteratorFacade const& rhs) {
            return lhs.asDerived().less (rhs.asDerived());
      }
      
private:
      Derived& asDerived () {
            return *static_cast<Derived*>(this);
      }
      Derived const& asDerived () const {
            return *static_cast<Derived const*>(this);
      }
};
