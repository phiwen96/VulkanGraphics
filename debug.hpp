#pragma once


#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)


#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

#define       NUMARGS(...)  (sizeof((char const*[]){0, ##__VA_ARGS__})/sizeof(char const*)-1)
#define CONCAT(x,...) ( ( (NUMARGS(#__VA_ARGS__) > 0) ) ?  (STRINGIZE(TOKENPASTE2(x, __VA_ARGS__))) : ("då") )

#define IS_LOWER( x ) ( ( (x >= 'a') && (x <= 'z') ) ?  1 : 0 )
//#define debug Debug(__func__)()


#define debug Debug TOKENPASTE2(debug_, __LINE__){__func__, __LINE__};TOKENPASTE2(debug_, __LINE__)
//#define debug Debug TOKENPASTE2(debug_, __LINE__){__func__};TOKENPASTE2(debug_, __LINE__)
#define om(x) Debug TOKENPASTE2(debug_, __LINE__){__func__, __LINE__, #x};if(bool(x))

template <size_t N>
struct Indent {
      int curr;
      char* begin;
      char * end;
      Indent () : curr (1), begin((char*) malloc(1 * sizeof(char))) {
            end = begin;
            *end = '\0';
      }
      Indent (int i) : curr (i), begin((char*) malloc(((N * i) + 1) * sizeof(char))) {
            end = begin + (N * curr);
            memset(begin, ' ', (N * i));
            *end = '\0';
            //            ind[N*i] = '\0';
      }
      Indent& operator++ (int) {
            begin = (char*) realloc(begin, ((end-begin) + N)* (sizeof(char)));
            for(char* i = end; i < end + N; ++i)
            *i = ' ';
            ++curr;
            end += N;
            *end = '\0';
            return *this;
      }
      Indent& operator-- (int) {
            begin = (char*) realloc(begin, ((end-begin) - N)* (sizeof(char)));
            //            for(char* i = end; i < end + N; ++i)
            //            *i = ' ';
            --curr;
            end -= N;
            *end = '\0';
            return *this;
      }
      Indent& operator+= (Indent other) {
            begin = (char*) realloc(begin, ((end-begin) + (other.end-other.begin) + 1)* (sizeof(char)));
            memmove(end, other.begin, (other.end - other.begin + 1) * sizeof(char));
            curr += other.curr;
            end += other.end - other.begin;
            //            ind[N * curr] = '\0';
            return *this;
      }
      friend ostream& operator<< (ostream& os, Indent const& i)
      {
            os << i.begin;
            return os;
      }
};

#define dbug
struct Debug : public ostream {
      inline static int tot = 1;
      Indent<4> ind;
      int const line;
      
      template <typename T>
      friend Debug& operator<<(Debug& d, const T& v)
      {
            
            
#ifdef dbug
            static_cast<std::ostream&>(d) << d.ind << v << endl;
#endif
            return d;
      }
      
      
      template <class... T>
      Debug (char const* fun, int line, T const&... t) : fun(fun), ind (tot++), line(line), ostream(cout.rdbuf()){
#ifdef dbug
            cout << line;
            //            if (tot > 2)
            //            {
            //                  cout << ind;
            //            } else
            //            {
            //                  cout << ind << fun;
            //            }
            ((cout << ind << t << " "), ...);
            cout << endl;
            
            //            ((cout << ind << t << " "), ...);
#endif
            //            cout << endl;
      }
      
      //      Debug (char const* fun, int line, char const* s) : fun(fun), ind (tot++), line(line), ostream(cout.rdbuf()){
      //#ifdef dbug
      //            if (tot > 1)
      //            {
      //                  cout << ind << line;
      //            } else
      //            {
      //                  cout << ind << fun << " " << endl;
      //                  cout << s << endl;
      //            }
      //
      //            //            ((cout << ind << t << " "), ...);
      //#endif
      //            //            cout << endl;
      //      }
      ~Debug () {
            --tot;
      }
      char const* fun;
      Debug& operator>>(char const* c) {
            cout << c;
            return *this;
      }
};
