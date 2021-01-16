//////////////////////////////////////////////
/// TIME MACROS
//////////////////////////////////////////////
// Some definitions for calculation
#define SEC_PER_MIN             60UL
#define SEC_PER_HOUR            3600UL
#define SEC_PER_DAY             86400UL
#define SEC_PER_YEAR            (SEC_PER_DAY*365)

// extracts 1..4 characters from a string and interprets it as a decimal value
#define CONV_STR2DEC_1(str, i)  (str[i]>'0'?str[i]-'0':0)
#define CONV_STR2DEC_2(str, i)  (CONV_STR2DEC_1(str, i)*10 + str[i+1]-'0')
#define CONV_STR2DEC_3(str, i)  (CONV_STR2DEC_2(str, i)*10 + str[i+2]-'0')
#define CONV_STR2DEC_4(str, i)  (CONV_STR2DEC_3(str, i)*10 + str[i+3]-'0')

// Custom "glue logic" to convert the month name to a usable number
#define GET_MONTH(str, i)      (str[i]=='J' && str[i+1]=='a' && str[i+2]=='n' ? 1 :     \
str[i]=='F' && str[i+1]=='e' && str[i+2]=='b' ? 2 :     \
str[i]=='M' && str[i+1]=='a' && str[i+2]=='r' ? 3 :     \
str[i]=='A' && str[i+1]=='p' && str[i+2]=='r' ? 4 :     \
str[i]=='M' && str[i+1]=='a' && str[i+2]=='y' ? 5 :     \
str[i]=='J' && str[i+1]=='u' && str[i+2]=='n' ? 6 :     \
str[i]=='J' && str[i+1]=='u' && str[i+2]=='l' ? 7 :     \
str[i]=='A' && str[i+1]=='u' && str[i+2]=='g' ? 8 :     \
str[i]=='S' && str[i+1]=='e' && str[i+2]=='p' ? 9 :     \
str[i]=='O' && str[i+1]=='c' && str[i+2]=='t' ? 10 :    \
str[i]=='N' && str[i+1]=='o' && str[i+2]=='v' ? 11 :    \
str[i]=='D' && str[i+1]=='e' && str[i+2]=='c' ? 12 : 0)

// extract the information from the time string given by __TIME__ and __DATE__
#define __TIME_SECONDS__        CONV_STR2DEC_2(__TIME__, 6)
#define __TIME_MINUTES__        CONV_STR2DEC_2(__TIME__, 3)
#define __TIME_HOURS__          CONV_STR2DEC_2(__TIME__, 0)
#define __TIME_DAYS__           CONV_STR2DEC_2(__DATE__, 4)
#define __TIME_MONTH__          GET_MONTH(__DATE__, 0)
#define __TIME_YEARS__          CONV_STR2DEC_4(__DATE__, 7)

// Days in February
#define _UNIX_TIMESTAMP_FDAY(year) \
(((year) % 400) == 0UL ? 29UL : \
(((year) % 100) == 0UL ? 28UL : \
(((year) % 4) == 0UL ? 29UL : \
28UL)))

// Days in the year
#define _UNIX_TIMESTAMP_YDAY(year, month, day) \
( \
/* January */    day \
/* February */ + (month >=  2 ? 31UL : 0UL) \
/* March */    + (month >=  3 ? _UNIX_TIMESTAMP_FDAY(year) : 0UL) \
/* April */    + (month >=  4 ? 31UL : 0UL) \
/* May */      + (month >=  5 ? 30UL : 0UL) \
/* June */     + (month >=  6 ? 31UL : 0UL) \
/* July */     + (month >=  7 ? 30UL : 0UL) \
/* August */   + (month >=  8 ? 31UL : 0UL) \
/* September */+ (month >=  9 ? 31UL : 0UL) \
/* October */  + (month >= 10 ? 30UL : 0UL) \
/* November */ + (month >= 11 ? 31UL : 0UL) \
/* December */ + (month >= 12 ? 30UL : 0UL) \
)

// __get the UNIX timestamp from a digits representation
#define _UNIX_TIMESTAMP(year, month, day, hour, minute, second) \
( /* time */ second \
+ minute * SEC_PER_MIN \
+ hour * SEC_PER_HOUR \
+ /* year day (month + day) */ (_UNIX_TIMESTAMP_YDAY(year, month, day) - 1) * SEC_PER_DAY \
+ /* year */ (year - 1970UL) * SEC_PER_YEAR \
+ ((year - 1969UL) / 4UL) * SEC_PER_DAY \
- ((year - 1901UL) / 100UL) * SEC_PER_DAY \
+ ((year - 1601UL) / 400UL) * SEC_PER_DAY \
)

// the UNIX timestamp
#define UNIX_TIMESTAMP (_UNIX_TIMESTAMP(__TIME_YEARS__, __TIME_MONTH__, __TIME_DAYS__, __TIME_HOURS__, __TIME_MINUTES__, __TIME_SECONDS__))
//////////////////////////////////////////////
///
//////////////////////////////////////////////




//////////////////////////////////////////////
/// RANDOM MACROS
///   - depends on TIME MACROS
//////////////////////////////////////////////
#pragma once
#define UL unsigned long
#define znew  ((z=36969*(z&65535)+(z>>16))<<16)
#define wnew  ((w=18000*(w&65535)+(w>>16))&65535)
#define MWC   (znew+wnew)
#define SHR3  (jsr=(jsr=(jsr=jsr^(jsr<<17))^(jsr>>13))^(jsr<<5))
#define CONG  (jcong=69069*jcong+1234567)
#define KISS  ((MWC^CONG)+SHR3)


//static inline unsigned long z=362436069*(int)__TIME_SECONDS__, w=521288629*(int)__TIME_SECONDS__,
//jsr=123456789*(int)__TIME_SECONDS__, jcong=380116160*(int)__TIME_SECONDS__;
/*  Global static variables:
 (the seed changes on every minute) */







/*////////////////////////////////////////////////////////////////////////////////*\
 Simple implementation of a Linear Congruential Pseudo-Random Number Generator (PRNG)
 https://en.wikipedia.org/wiki/Linear_congruential_generator
 https://www.cplusplus.com/reference/random/minstd_rand/
 \*////////////////////////////////////////////////////////////////////////////////*/

// modulus (2^31 - 1) or 0x7FFFFFFF in hex
constexpr uint32_t m{ 2147483647 };
static_assert(m > 0, "modulus is not greater than 0!");

// multiplier
constexpr uint32_t a{ 48271 };
static_assert(0 < a && a < m, "multiplier is not between 0 and modulus!");

// constant / increment
constexpr uint32_t c{ 0 };
static_assert(0 <= c && c < m, "increment is not between 0 and modulus!");

// Defining the seed based on compile time in seconds since 00:00:00
constexpr uint32_t seed = ((__TIME__[7] - '0') * 1 + (__TIME__[6] - '0') * 10
                           + (__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600
                           + (__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000);
static_assert(0 <= seed && seed < m, "seed is not between 0 and modulus!");

// This ensures that RNG() is evaluated at compile time! (Keyword: Template Metaprogramming)
template <uint32_t Const>
struct MakeConst
{
      enum { Value = Const };
};




constexpr uint32_t RecursiveRNG(uint32_t num)
{
      return (c + a * ((num > 0) ? RecursiveRNG(num - 1) : seed)) & m;
}

// Outputs random number as constexpr
#define LCG_RANDOM() (MakeConst<RecursiveRNG(__COUNTER__ + 1)>::Value)
#define LCG_RANDOM2(a) (MakeConst<RecursiveRNG(__COUNTER__ + a)>::Value)
// Outputs a positive number in the given range
#define LCG_RANDOM_IN_RANGE(min, max) (min + (LCG_RANDOM() & m) % (max - min + 1))
// This acts as a bool. Could have use a range of 0 and 1, but this might have introduced more bias
#define LCG_BOOL (LCG_RANDOM_IN_RANGE(0, 100) % 2)

#define kk(min, max, size, seq) std::array<int, size>{(min + (LCG_RANDOM() & m) % (max - min + 1))...}

//template <size_t min, size_t max, size_t size, size_t... I>
//constexpr auto aa (std::index_sequence<I...>) {
//      return std::array<int, size>{LCG_RANDOM2(I)...};
//}

#define RANDOM_IN_RANGE(min, max, size) [](){std::array<int, size> mm; int i = 0;for(auto& i : mm)i = LCG_RANDOM2(i++);return mm;}();



/**
 Ordered collection of bits.
 */
template <bool... values>
using _bitset = std::integer_sequence<bool, values...>;

/**
 Ordered collection of indicies.
 */
template <size_t... values>
using indicies = std::integer_sequence<size_t, values...>;

/**
 Convert a `_bitset` to an integer type `T`.
 */
template <typename T, T value, typename set>
struct to_int;

template <typename T,  T value>
struct to_int<T, value, _bitset<>> :
std::integral_constant<T, value> { };

template <typename T, T value, bool x, bool... xs>
struct to_int<T, value, _bitset<x, xs...>> :
std::integral_constant<T,
to_int<T, static_cast<T>((value << 1) | x), _bitset<xs...>>::value> { };

/**
 _Get the head of an `integer_sequence`
 */
template <typename list>
struct car;

template <typename T, T x, T... xs>
struct car<std::integer_sequence<T, x, xs...>> : std::integral_constant<T, x> { };

/**
 _Get the rest of an `integer_sequence` excluding the head.
 */
template <typename list>
struct cdr;

template <typename T, T x, T... xs>
struct cdr<std::integer_sequence<T, x, xs...>> {
      using type = std::integer_sequence<T, xs...>;
};

template <typename list>
using cdr_t = typename cdr<list>::type;

/**
 Prepend a value onto an `integer_sequence`.
 */
template <typename rest, typename rest::value_type head>
struct cons;

template <typename T, T x, T... xs>
struct cons<std::integer_sequence<T, xs...>, x>
{
      using type = std::integer_sequence<T, x, xs...>;
};

template <typename rest, typename rest::value_type head>
using cons_t = typename cons<rest, head>::type;

/**
 Lookup a value in an `integer_sequence`.
 */
template <size_t N, typename T>
struct _get;

template <size_t N, typename T, T x, T... xs>
struct _get<N, std::integer_sequence<T, x, xs...>> :
std::integral_constant<T,
_get<N - 1, std::integer_sequence<T, xs...>>::value> { };

template <typename T, T x, T... xs>
struct _get<0, std::integer_sequence<T, x, xs...>> :
std::integral_constant<T, x> { };

/**
 Clamp an `integer_sequence` to length `N`.
 */
template <size_t N, typename T>
struct take;

template <typename T, T... xs>
struct take<0, std::integer_sequence<T, xs...>> {
      using type = std::integer_sequence<T>;
};

template <size_t N, typename T, T... xs>
struct take<N, std::integer_sequence<T, xs...>> {
      using type = cons_t<
      typename take<N - 1,
      cdr_t<std::integer_sequence<T, xs...>>>::type,
      car<std::integer_sequence<T, xs...>>::value>;
};

template <size_t N, typename T>
using take_t = typename take<N, T>::type;

/**
 _Get the most significant bit for the next iteration.
 */
template <typename state, typename taps>
struct _get_next;

template <typename T>
struct _get_next<T, indicies<>> :
std::integral_constant<bool, false> { };

template <typename T, size_t tap, size_t... taps>
struct _get_next<T, indicies<tap, taps...>> :
std::integral_constant<bool,
(_get<tap, T>::value) ^ (_get_next<T, indicies<taps...>>::value)> { };

/**
 Linear feedback shift register.
 */
template <typename state, typename taps>
struct Lfsr {
      /**
       Iterate once to get the next state.
       */
      using next =
      Lfsr<
      take_t<state::size(),
      cons_t<
      state,
      _get_next<state, taps>::value>>,
      taps>;
      
      /**
       Convert the current state to an integer.
       */
      template <typename T>
      using value = to_int<T, 0, state>;
};


/**
 Runs `N` iterations of a Lfsr, building results into a list of unsigned.
 */
template <size_t N, typename>
struct gen;

template <typename state, typename taps>
struct gen<0, Lfsr<state, taps>> {
      using type = std::integer_sequence<unsigned>;
};

template <size_t N, typename state, typename taps>
struct gen<N, Lfsr<state, taps>> {
      using lfsr = Lfsr<state, taps>;
      
      using type = cons_t<
      typename gen<N - 1, typename lfsr::next>::type,
      lfsr::template value<unsigned>::value>;
};

/**
 Prints a type to output.
 */
template <typename>
struct Printer;

template <typename T>
struct Printer<std::integer_sequence<T>>
{
      static void Print() { /* noop */ }
};

template <typename T, T x, T... xs>
struct Printer<std::integer_sequence<T, x, xs...>>
{
      static void Print()
      {
            std::cout << x << "\n";
            Printer<std::integer_sequence<T, xs...>>::Print();
      }
};
