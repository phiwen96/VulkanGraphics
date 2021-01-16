#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <tuple>
#include <filesystem>
#include "str.hpp"
using namespace std;
template <class T, size_t N>
ostream& operator<< (ostream& os, std::array<T, N> const& a){
      os << "{ ";
      for(auto const& i : a)
            os << i << " ";
      os << "}";
      return os;
}
template <class T>
ostream& operator<< (ostream& os, std::vector<T> const& v) {
      os << "{ ";
      for(auto const& i : v)
            os << i << " ";
      os << "}";
      return os;
}
template <class T, class U> ostream& operator <<(ostream& os, pair<T, U> const& u) {
      os << "{" << u.first << ", " << u.second << "}";
      return os;
}
template <class T, class U> ostream& operator <<(ostream& os, unordered_map<T, U> const& u) {
      os << "{ ";
      for(auto const& i : u)
            os << i << " ";
      os << "}";
      return os;
}

template <class T>
ostream& operator<< (ostream& os, std::list<T> const& v) {
      os << "{ ";
      for(auto const& i : v)
            os << i << " ";
      os << "}";
      return os;
}

template <class... T, size_t... I>
ostream& operator<< (ostream& os, pair<tuple<T...>, index_sequence<I...>> p){
      ((os << get<I>(p.first) << " "), ...);
      return os;
}

template <class... T>
ostream& operator<< (ostream& os, std::tuple<T...> const& t)
{
      os << "{ ";
      os << make_pair(t, make_index_sequence<sizeof...(T)>{});
      os << "}";
      return os;
}



template <class... T, size_t... I1, size_t... I2>
constexpr auto split (tuple<T...> const& t, index_sequence<I1...> ind1, index_sequence<I2...> ind2) -> decltype(auto)
{
      return make_pair(make_tuple(get<I1>(t)...), make_tuple(get<sizeof...(I1) + I2>(t)...));
}
template <size_t splitIndex, class... T, size_t N = sizeof...(T)>
constexpr auto split (tuple<T...> const& t) -> decltype(auto)
{
      constexpr size_t i = splitIndex;
      constexpr size_t j = N - splitIndex;
      return split(t, make_index_sequence<i>{}, make_index_sequence<j>{});
}
// auto [lhs, rhs] = split<mid> (t);




inline str _current_path(char const* file){
      return std::filesystem::path(file).parent_path().c_str();
}

#define current_path _current_path (__FILE__)





template <class T>
std::tuple<std::vector<T>, std::vector<T>> split (std::vector<T> const& A) {
      return {std::vector<T>(A.begin(), A.end()-(A.size()/2)), std::vector<T>(A.end()-(A.size()/2), A.end())};
}

