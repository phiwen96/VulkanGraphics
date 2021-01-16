//
// Created by philip on 2020-12-05.
//

#pragma once
#include "vec.hpp"
namespace ph{
struct str : ph::vec<char>{
      using Base = ph::vec<char>;
      using Base::vec;
      
      str (char const* s) : Base (s, strlen(s)){
            
      }
      friend std::ostream& operator<< (std::ostream& os, str const& s){
            for ( int i = 0; i < s.size(); ++i )
            {
                  os << s[i];
            }
            return os;
      }
      virtual ~str(){
//            Base::~vec();
      }
      friend std::istream& getline(std::istream& inp, str& s, char delimiter = '\n'){
            char ch;
            while (inp.get(ch)){
                  s += ch;
                  if (ch == delimiter)
                        break;
            }
            return inp;
      }
      friend ph::vec<str> split (str s, char ch) {
            if (s.size() == 0)
                  return {};
            ph::vec<str> res;
//            int i = 0;
//            str news (s.size());
            int i = 0;
            while (i < s.size() and s[i] != ch)
            {
//                  news += s[i];
                  ++i;
            }
            if (i < s.size()) {
                  res += str(s.data(), i);
                  str ss (s.data() + i + 1, s.size() - i-2);
//                  std::cout << ss << std::endl;
                  res += split (ss, ch);
            } else {
                  res += s;
            }
            return res;
      }
      friend bool operator== (str const& s1, char const* s2) {
            if (s1.size() != strlen (s2))
                  return false;
            for (int i = 0; i < s1.size(); ++i) {
                  if (s1.get(i) != s2[i])
                        return false;
            }
            return true;
      }
      operator char const* () {
            char* s = new char[size()];
            
            strcpy (s, data());
            return s;
      }
      
      char const* c_str () {
            return *this;
      }
};

//struct str {
//      char* s;
//      size_t n;
//
//      char const* c_str () {
//            return s;
//      }
//
//      operator char const* () {
//            return s;
//      }
//
//      str() : s(nullptr), n(0)
//      {
//
//      }
//
//      str(str&& o)   : s(nullptr), n(0){
//            swap(*this, o);
//      }
//
//      str(str const& o) : s((char*)malloc(o.n + 1)), n (o.n){
//            memmove(s, o.s, n);
////            std::cout << "mksmdksmd" << std::endl;
//      }
//
//      str(char const* r) : s((char*)malloc(strlen(r))), n(strlen(r))
//      {
//            memmove(s, r, n * sizeof(char));
//      }
//      friend void swap(str& lhs, str& rhs)
//      {
//            using std::swap;
//            std::swap(lhs.s, rhs.s);
//            std::swap(lhs.n, rhs.n);
//      }
//
//      ~str()
//      {
//            //            if(s != nullptr)
//            free(s);
//      }
//
//      str& operator= (str other) {
//
//            swap(*this, other);
//            return *this;
//      }
//      str& operator+= (str const& other){
//
//            s = (char*) realloc(s, (n + other.n)* (sizeof(char)));
//            memmove(s + n, other.s, other.n * sizeof(char));
//            n += other.n;
//            return *this;
//      }
//      friend std::istream& getline(std::istream& inp, str& s, char delimiter = '\n'){
//
////            while(
//            return inp;
//      }
//
//      friend str operator + (str lhs, str const& rhs)
//      {
//            lhs += rhs;
//            return lhs;
//      }
//
//      friend bool operator== (str const& lhs, str const& rhs) {
//            if ( lhs.n != rhs.n )
//            {
//                  return false;
//            }
//            for(int i = 0; i < lhs.n; ++i)
//            {
//                  if ( lhs.s[i] != rhs.s[i] )
//                  {
//                        return false;
//                  }
//            }
//            return true;
//      }
//
//      friend std::ostream& operator<< (std::ostream& os, str const& s)
//      {
//            for ( int i = 0; i < s.n; ++i )
//            {
//                  os << s.s[i];
//            }
//            return os;
//      }
//};
//
//



//bool isNumber (char c) {
//
//      return c >= '0' and c <= '9';
//}
}
