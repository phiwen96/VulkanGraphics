#pragma once
#include <ph/common/vec.hpp>

namespace ph {



struct binary;

template <class...>
struct search;
template <class T, class U>
search (T, U) -> search<>;



template <>
class search<void>
{
public:
      operator int () const {
            return i;
      }
      
protected:
      search (int i) : i (i) {
            
      }
      
      int i;
};




template <>
struct search<> : search<void>
{
      template <class T, class U>
      search (T const& A, U const& X) : search<void>(Search(A, X)) {

      }
   
private:
      template <class T, class U>
      static int Search (T const& A, U const& X)
      {
            for (int i = 0; i < A.size(); ++i)
            {
                  if (X == A [i])
                        return i;
            }
            return -1;
      }
};



template <>
struct search<binary> : search<void>
{
      template <class T, class U>
      search (U const& A, T const& X) : search<void> (Binary_Search(A, X)) {}
      
private:
      template <class T, class U>
      static int Binary_Search (T const& A, U const& X)
      {
            int left = 0;
            int right = A.size() - 1;
            int mid;
/*
             Invariants
             - A [left]       <=    X
             - A [right]      >     X
             - A [mid]        <=>   X
 
            Initialization:   It is true prior to the first iteration of the loop.
 
            Maintainance:     If it is true before an iteration of the loop,
                              it remains true before the next iteration.
 
            Termination:      When the loop terminates, the invariant gives us a useful property
                              that helps show that the algorithm is correct.
*/
            
/*
             
 */
            /**
             At the start of the iteration of the while loop, the subarray A [left, right] consists of elements in
             a sorted order such that X >= A [left] and X <= A [right]
             */
            
            while (left < right)
            {
                  mid = (left + right) / 2;
                  
                  if (X > A[mid])
                  {
                        left = mid + 1;
                  }
                  
                  else
                  {
                        right = mid;
                  }
            }
            
            if (A[left] == X)
            {
                  return left;
                  
            }
            
            else
            {
                  return -1;
            }
      }
};





//template <class T>
//search (std::vector<T>) -> search<std::vector<T>>;




      
      
  


//template <template <class, class...> class Con, class T, class... U>
//int search<std::vector<T, U...>> (std::vector<T, U...> const& inp, T const& x) {
//      int left = 0;
//      int right = v1.size() - 1;
//      int mid;
//
//      while (left < right) {
//            mid = (left + right) / 2;
//            if (x > v1[mid]) {
//                  <#code#>
//            }
//      }
//}






}
