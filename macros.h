#pragma once


/**
 rename file with rename (from, to)
 remove file with remove (file)

 cout << __DATE__ << endl;
 cout << __TIME__ << endl;
 cout << __STDCPP_THREADS__ << endl;
 cout << __COUNTER__ << endl;
 cout << __COUNTER__ << endl;
 cout << __COUNTER__ << endl;
 */



//#define USE_STRING
#if defined (USE_INT)
using Number = int;
#elif defined (USE_STRING)
using Number = string;
#endif // USE_SOCKETS.



void jkf5(string s){
      cout << "kansdknasknda" << " " << s << endl;
}

#define test(a,b) a##b("km")
#define print(a) cout<<#a<<endl
#define MACRO(a) printf(#a)
#define WIDTH 80
#define ADD( X, Y ) ((X) + (Y))

#define ASSERT(a) if(!(a))\
{cout << "fail " << __FILE_NAME__ << " " << __LINE__ << "\n";}

#if !defined(__cplusplus)
#error C++ compiler required.
#endif

int run()
{
      ADD(2, 3);
#undef ADD
      
      test(jkf,5);
      print(MPI_Finalize());
      MACRO(hej kmk int a = 3);
      
      
}



// Demonstrates functionality of __FUNCTION__, __FUNCDNAME__, and __FUNCSIG__ macros
void exampleFunction()
{
      
      printf("Function name: %s\n", __FUNCTION__);
      printf("Decorated function name: %s\n", __FUNCDNAME__);
      printf("Function signature: %s\n", __FUNCSIG__);
      
      // Sample Output
      // -------------------------------------------------
      // Function name: exampleFunction
      // Decorated function name: ?exampleFunction@@YAXXZ
      // Function signature: void __cdecl exampleFunction(void)
}



#define CHECK_NESTED_FUNC(fName) \
template <typename, typename, typename = std::void_t<>> \
struct _has_##fName \
: public std::false_type {}; \
\
template <typename Class, typename Ret, typename... Args> \
struct _has_##fName<Class, Ret(Args...), \
std::void_t<decltype(std::declval<Class>().fName(std::declval<Args>()...))>> \
: public std::is_same<decltype(std::declval<Class>().fName(std::declval<Args>()...)), Ret> \
{}; \
\
template <typename Class, typename Signature> \
using has_##fName = _has_##fName<Class, Signature>;

#define HAS_NESTED_FUNC(Class, Func, Signature) has_##Func<Class, Signature>::value


class Foo
{
public:
      void Bar(int, const char *) {}
};

CHECK_NESTED_FUNC(Bar);  // generate required metafunctions









