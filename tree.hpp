#pragma once
#include <ph/common/vec.hpp>


namespace ph::data_structures
{
template <class... T>
using Array = ph::vec<T...>;


template <size_t, class...>
struct Tree;







template <class value_type>
class Tree<0, value_type>
{
      using reference = value_type&;
      using reference_const = value_type const&;
      using rreference = value_type&&;
      using self = Tree<0, value_type>;
      
public:
      bool leaf () const {return true;}
      Tree (reference_const value) : m_value (value) {}
      Tree (rreference value) : m_value (std::move(value)) {cout<<"hi"<<endl;}
      
      friend ostream& operator<< (ostream& os, self const& s) {
            os << s.m_value;
            return os;
      }
      
private:
      value_type m_value;
};

template <class T>
using Leaf = Tree<0, T>;



template <size_t N, class T>
struct Tree<N, T>// : Leaf<T>
{
      using Leaf = Leaf<T>;
      using array = std::array<T, N>;
      
      bool leaf () const {return m_children == nullptr;}
      
      template <class... U>
      Tree (T t, U... u) : m_children( new array{t, u...} ) {
            
      }
      
//      T& operator[] (unsigned int i) {
//            assert(!leaf() and i < ((array*)m_children)->size());
//            return (*m_children)[i];
//      }
protected:
      
      void* m_children;
};



template <class T>
Tree (T) -> Tree<0, T>;

template <class... T>
Tree (T...) -> Tree <sizeof...(T), std::common_type_t<T...>>;

//template <size_t N, class T, class... U>
//Tree (Tree<N, T>, U...) -> Tree<sizeof...(U)+1, Tree<>





template <class...>
class tree;

template <class T>
class tree<T>
{
      using value_type           = T;
      using reference            = value_type&;
      using reference_const      = value_type const&;
      using self                 = tree<T>;
      using self_reference       = self&;
      using self_reference_const = self const&;
      
      
      
      
public:
      tree&         parent      ();
      Array<tree>   children    ();
      tree&         root        ();
      bool          isRoot      ()                        const;
      bool          leaf        ()                        const;
      
      ////////////////////////////////////////////////////////////////
      /// @brief number of edges to root
      ////////////////////////////////////////////////////////////////
      int           depth       ()                        const;
      
      
      
      //////////////////
      /// TOIMPLEMENT
      //////////////////
      
      bool          descendant  (self_reference_const)    const;
      bool          ancestor    (self_reference_const)    const;
      
      ////////////////////////////////////////////////////////////////
      /// @brief the maximum length of a path in the tree
      ////////////////////////////////////////////////////////////////
      int           height      ()                        const;
      
      ////////////////////////////////////////////////////////////////
      /// @brief number of nodes in the tree
      ////////////////////////////////////////////////////////////////
      int           size        ()                        const;
      
      tree (reference_const);
          
      
private:
      tree*         m_parent;
      Array<tree>   m_children;
      value_type    m_value;
};







template <class T>
                tree<T>::tree (reference_const value) : m_parent (nullptr), m_children (0), m_value (value) {
            
}

template <class T>
tree<T>&         tree<T>::parent      () {
      assert(m_parent != nullptr);
      return *m_parent;
}

template <class T>
Array<tree<T>>   tree<T>::children    () {
      return m_children;
}

template <class T>
tree<T>&         tree<T>::root        () {
      if (m_parent == nullptr)
            return *this;
      return m_parent -> root();
}

template <class T>
bool             tree<T>::isRoot      ()     const   {
      return m_parent == nullptr;
}

template <class T>
bool             tree<T>::leaf        ()     const   {
      return m_children.size () == 0;
}

template <class T>
int              tree<T>::depth       ()    const   {
      if (m_parent == nullptr) return 0;
      return 1 + m_parent -> depth();
}





template <class...>
class quad;



template <class T>
class tree<quad<T>> : public Tree<4, T>
{
      using Tree<4, T>::Tree;
};













}
