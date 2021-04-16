//
//  compare.cpp
//  CF.STL_Compare
//
//  Created by Alan Sampson on 3/3/21.
//
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/header/compare
//  @see: https://en.cppreference.com/w/cpp/language/default_comparisons
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <utility>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <compare>
#include <type_traits>

using namespace std::literals::string_literals;

int X_compare_three_way_result(int argc, char const * argv[]);
int X_compare_three_way(int argc, char const * argv[]);
int X_compare_weak_order_fallback(int argc, char const * argv[]);
int X_isXXX(int argc, char const * argv[]);
int X_default_comparison(int argc, char const * argv[]);

namespace konst {

auto const dlm = std::string(80, '-');

} /* namespace konst */

/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  std::cout << "CF.STL_Compare" << std::endl;
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  X_compare_three_way_result(argc, argv);

  std::cout << '\n' << konst::dlm << std::endl;
  X_compare_three_way(argc, argv);

  std::cout << '\n' << konst::dlm << std::endl;
  X_compare_weak_order_fallback(argc, argv);

  std::cout << '\n' << konst::dlm << std::endl;
  X_isXXX(argc, argv);

  std::cout << '\n' << konst::dlm << std::endl;
  X_default_comparison(argc, argv);

  return 0;
}

//  MARK: - X_compare_three_way_result
//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
//  ================================================================================
//  MARK: namespace ctwr
namespace ctwr {

template <class Ord>
void print_cmp_type() {
  if constexpr (std::is_same_v<Ord, std::strong_ordering>) {
    std::cout << "strong ordering\n"s;
  }
  else if constexpr (std::is_same_v<Ord, std::weak_ordering>) {
    std::cout << "weak ordering\n"s;
  }
  else if constexpr (std::is_same_v<Ord, std::partial_ordering>) {
    std::cout << "partial ordering\n"s;
  }
  else {
    std::cout << "illegal comparison result type\n"s;
  }
}

} /* namespace ctw */

//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
/*
 *  MARK: X_compare_three_way_result()
 */
int X_compare_three_way_result(int argc, char const * argv[]) {
  std::cout << "In "s << __func__ << std::endl;

#if (__cplusplus >= 201709L)
  ctwr::print_cmp_type<std::compare_three_way_result_t<int>>();
  ctwr::print_cmp_type<std::compare_three_way_result_t<double>>();
#else
  std::cout << "std::compare_three_way_result_t not implemented in C++ "s
            << __cplusplus << '\n';
#endif
  
  return 0;
}

//  MARK: - X_compare_three_way
//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
//  ================================================================================
//  MARK: namespace ctw

namespace ctw {

struct Rational_2 {
  int num;
  int den; // > 0
};

constexpr std::weak_ordering operator<=>(Rational_2 lhs, Rational_2 rhs) {
  return lhs.num * rhs.den <=> rhs.num * lhs.den;
}

void print(std::weak_ordering value) {
  if (value == 0) {
    std::cout << "equal\n"s;
  }
  else if (value < 0) {
    std::cout << "less\n"s;
  }
  else {
    std::cout << "greater\n"s;
  }
}

} /* namespace ctw */

//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
/*
 *  MARK: X_compare_three_way()
 */
int X_compare_three_way(int argc, char const * argv[]) {
  std::cout << "In "s << __func__ << std::endl;

  ctw::Rational_2 c_r { 6, 5 };
  ctw::Rational_2 d_r { 8, 7 };
  std::cout << c_r.num << '/' << c_r.den
            << " <=> "s
            << d_r.num << '/' << d_r.den
            << " ? "s;
  ctw::print(c_r <=> d_r);

#if (__cplusplus >= 201709L)
  ctw::print(std::compare_three_way{}(c_r, d_r));
#else
  std::cout << "std::compare_three_way not implemented in C++ "s
            << __cplusplus << '\n';
#endif

  return 0;
}

//  MARK: - X_compare_weak_order_fallback
//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
//  ================================================================================
//  MARK: namespace cwof

namespace cwof {

// does not support <=>
struct Rational_1 {
  int num;
  int den; // > 0
};

inline constexpr bool operator<(Rational_1 lhs, Rational_1 rhs) {
  return lhs.num * rhs.den < rhs.num * lhs.den;
}

inline constexpr bool operator==(Rational_1 lhs, Rational_1 rhs) {
  return lhs.num * rhs.den == rhs.num * lhs.den;
}

// supports <=>
struct Rational_2 {
  int num;
  int den; // > 0
};

inline constexpr std::weak_ordering operator<=>(Rational_2 lhs, Rational_2 rhs) {
  return lhs.num * rhs.den <=> rhs.num * lhs.den;
}

void print(std::weak_ordering value) {
  if (value == 0) {
    std::cout << "\nequal\n"s;
  }
  else if (value < 0) {
    std::cout << "\nless\n"s;
  }
  else {
    std::cout << "\ngreater\n"s;
  }
}

} /* namespace cwof */

//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
/*
 *  MARK: X_compare_weak_order_fallback()
 */
int X_compare_weak_order_fallback(int argc, char const * argv[]) {
  std::cout << "In "s << __func__ << std::endl;

  cwof::Rational_1 a1 {1, 2};
  cwof::Rational_1 b1 {3, 4};
  auto lt = a1 <  b1;
  auto eq = a1 == b1;
  auto gt = !lt && !eq;
  std::cout << "a1: "s << a1.num << '/' << a1.den << '\n';
  std::cout << "b1: "s << b1.num << '/' << b1.den << '\n';
  std::cout << "  a1 <  b1 ? "s << std::boolalpha << lt
            << ", a1 == b1 ? "s << std::boolalpha << eq
            << ", a1 gt b1 ? "s << std::boolalpha << gt
            << '\n';
//  cwof::print(a <=> b);                // doesn't work
#if (__cplusplus >= 201709L)
  cwof::print(std::compare_weak_order_fallback(a, b)); // works, defaults to < and ==
#else
#endif

  cwof::Rational_2 c2 {6, 5};
  cwof::Rational_2 d2 {8, 7};
  cwof::print(c2 <=> d2);                // works
  lt = c2 <  d2;
  gt = c2 >  d2;
  eq = !gt && !lt;
  std::cout << "21: "s << c2.num << '/' << c2.den << '\n';
  std::cout << "d2: "s << d2.num << '/' << d2.den << '\n';
  std::cout << "  c2 <  d2 ? "s << std::boolalpha << lt
            << ", c2 == d2 ? "s << std::boolalpha << eq
            << ", c2 gt d2 ? "s << std::boolalpha << gt
            << '\n';
#if (__cplusplus >= 201709L)
  cwof::print(std::compare_weak_order_fallback(c, d)); // works
#else
#endif

  return 0;
}

//  MARK: - X_isXXX
//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
//  ================================================================================

//  MARK: namespace xxx
namespace xxx {

struct Rational {
public:
  explicit
  constexpr
  Rational(int n_ = 0, int d_ = 1) : num(n_), den(d_) {
    if (d_ == 0) {
      den = 1;
    }
  }

  int numerator(void) const noexcept {
    return num;
  }

  int denominator(void) const noexcept {
    return den;
  }

  std::string toString(void) const noexcept {
    std::ostringstream tos;
    auto lcm = std::lcm(num, den);
    auto gcd = std::gcd(num, den);
    auto real = static_cast<double>(num) / den;
    tos << std::setw(4) << num << '/' << std::setw(4) << den
        << " - "s
        << std::setw(4) << num / gcd << '/' << std::setw(4) << den / gcd
        << " - "s
        << std::setw(8) << num * lcm << '/' << std::setw(8) << den * lcm
        << " [gcd="s  << std::setw(4) << gcd
        << ", lcm="s  << std::setw(4) << lcm
        << ", real="s << std::fixed   << real
        << "]"s;
    return tos.str();
  }

  friend std::ostream & operator<<(std::ostream & os, Rational const & that) {
    os << that.toString();
    return os;
  }

  auto operator<=>(Rational const & that) const {
    return num * that.den <=> that.num * den;
  }

  auto operator==(Rational const & that) const {
    return (*this <=> that) == 0;
  }

  auto operator!=(Rational const & that) const {
    return (*this <=> that) != 0;
  }

private:
  int num;
  int den;
};

//inline
//auto operator<=>(Rational lhs, Rational rhs) {
//  return lhs.numerator() * rhs.denominator() <=> rhs.numerator() * lhs.denominator();
//}

} /* namespace xxx */

//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
/*
 *  MARK: X_isXXX()
 */
int X_isXXX(int argc, char const * argv[]) {
  std::cout << "In "s << __func__ << std::endl;

  auto rv = std::vector<xxx::Rational> {
    xxx::Rational(  1,     2), xxx::Rational( 3,  4), xxx::Rational( 5,   8),
    xxx::Rational(  4,     3), xxx::Rational( 8,  5), xxx::Rational( 4,   8),
    xxx::Rational(  8,     4), xxx::Rational(12,  6), xxx::Rational( 6,  12),
    xxx::Rational(  9,    12), xxx::Rational(15, 24), xxx::Rational(15,  24),
    xxx::Rational(125, 1'000), xxx::Rational( 5, 10), xxx::Rational(33, 100),
  };

  for (auto rg : rv) {
    std::cout << rg << '\n';
  }
  std::cout << std::endl;

  auto it = rv.cbegin();
  auto il = it;
  std::advance(it, 1);

  static
  auto const dot = std::string(80, '.');
  while (it != rv.cend()) {
    std::cout << dot << '\n';
    std::cout << *it << '\n';
    std::cout << *il << '\n';

    auto eq   = std::is_eq(*il <=> *it);
    auto neq  = std::is_neq(*il <=> *it);
    auto lt   = std::is_lt(*il <=> *it);
    auto gt   = std::is_gt(*il <=> *it);
    auto lteq = std::is_lteq(*il <=> *it);
    auto gteq = std::is_gteq(*il <=> *it);

    std::cout << std::boolalpha
              << "eq   : "s << eq   << '\n'
              << "neq  : "s << neq  << '\n'
              << "lt   : "s << lt   << '\n'
              << "gt   : "s << gt   << '\n'
              << "lteq : "s << lteq << '\n'
              << "gteq : " << gteq << '\n'
              << std::endl;

    auto frac = [](auto const num, auto const den) -> std::string {
      std::ostringstream frac;
      auto gcd(std::gcd(num, den));
      auto nnum(num / gcd);
      auto nden(den / gcd);
      frac << std::setw(4) << nnum << '/' << std::setw(4) << nden;
      return frac.str();
    };

    auto il_frac = frac((*il).numerator(), il->denominator());  //  TODO: because I can!
    auto it_frac = frac(it->numerator(), (*it).denominator());

    if (*il <=> *it == 0) {
      std::cout << il_frac << " eq "s << it_frac << '\n';
    }
    else if (*il <=> *it >  0) {
      std::cout << il_frac << " gt "s << it_frac << '\n';
    }
    else if (*il <=> *it <  0) {
      std::cout << il_frac << " lt "s << it_frac << '\n';
    }
    std::cout << std::endl;

    //  Compiler-Generated:
    if (*il < *it) {
      std::cout << il_frac << " lt "s << it_frac << '\n';
    }
    if (*il > *it) {
      std::cout << il_frac << " gt "s << it_frac << '\n';
    }
    if (*il == *it) {
      std::cout << il_frac << " eq "s << it_frac << '\n';
    }
//    if ((*il >= *it) && (*il <= *it)) {
//      std::cout << il_frac << " eq "s << it_frac << '\n';
//    }
    if (*il != *it) {
      std::cout << il_frac << " ne "s << it_frac << '\n';
    }
//    if ((*il > *it) || (*il < *it)) {
//      std::cout << il_frac << " ne "s << it_frac << '\n';
//    }
    if (*il <= *it) {
      std::cout << il_frac << " le "s << it_frac << '\n';
    }
    if (*il >= *it) {
      std::cout << il_frac << " ge "s << it_frac << '\n';
    }
    std::cout << std::endl;

    //  bump loop comtrol iterators
    ++it;
    ++il;
  }

  return 0;
}

//  MARK: - X_default_comparison
//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
//  ================================================================================

//  MARK: namespace xdc
namespace xdc {

struct Point1 {
  int x_m;
  int y_m;
  auto operator<=>(Point1 const & that) const = default;
};

struct Point2 {
  int x_m;
  int y_m;

public:
  auto operator<=>(Point2 const & that) const {
    if (auto cmp = (x_m <=> that.x_m); cmp != 0) {
      return cmp;
    }
    auto cmp = y_m <=> that.y_m;
    return cmp;
  }

  auto operator==(Point2 const & that) const {
    auto cmp = (x_m == that.x_m && y_m == that.y_m);
    return cmp;
  }
};

struct Foo {
    int n_m;
};

bool operator==(Foo const & lhs, Foo const & rhs) {
  return lhs.n_m == rhs.n_m;
}

bool operator<(Foo const & lhs, Foo const & rhs) {
  return lhs.n_m < rhs.n_m;
}

struct Base {
#if (__cplusplus > 201707L)
  std::string zip;
#else
  char zip;
#endif

  auto operator<=>(Base const & other) const = default;
};

struct TotallyOrdered : Base {
#if (__cplusplus > 201707L)
  std::string tax_id;
  std::string first_name;
  std::string last_name;
#else
  char tax_id;
  char first_name;
  char last_name;
#endif

public:
  // custom operator<=> because we want to compare last names first:
  std::strong_ordering operator<=>(TotallyOrdered const & that) const {
//    if (auto cmp = (Base &)(*this) <=> (Base &)that; cmp != 0) {
//      return cmp;
//    }
//    if (auto cmp = last_name <=> that.last_name; cmp != 0) {
//      return cmp;
//    }
//    if (auto cmp = first_name <=> that.first_name; cmp != 0) {
//      return cmp;
//    }
//    return tax_id <=> that.tax_id;
    auto cmp = static_cast<Base const &>(*this) <=> static_cast<Base const &>(that);
    if (std::is_eq(cmp)) {
      cmp = last_name <=> that.last_name;
      if (std::is_eq(cmp)) {
        cmp = first_name <=> that.first_name;
        if (std::is_eq(cmp)) {
          cmp = tax_id <=> that.tax_id;
        }
      }
    }

    return cmp;
  }
 // ... non-comparison functions ...
};
// compiler generates all four relational operators

} /* namespace xdc */

//  ....+....|....+....|....+....|....+....|....+....|....+....|....+....|....+....|
/*
 *  MARK: X_default_comparison()
 *  @see: https://en.cppreference.com/w/cpp/language/default_comparisons
 */
int X_default_comparison(int argc, char const * argv[]) {
  std::cout << "In "s << __func__ << std::endl;

  static
  auto const dot = std::string(80, '.');
  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';

  {
    xdc::Point1 pt1 { 1, 1, }, pt2 { 1, 2, };
    std::set<xdc::Point1> poinsettia;  // ok
    poinsettia.insert(pt1);           // ok
    std::cout << std::boolalpha
              << (pt1 == pt2) << ' '  // false; operator== is implicitly defaulted.
              << (pt1 != pt2) << ' '  // true
              << (pt1 <  pt2) << ' '  // true
              << (pt1 <= pt2) << ' '  // true
              << (pt1 >  pt2) << ' '  // false
              << (pt1 >= pt2) << ' '; // false
    std::cout << std::noboolalpha;
    std::cout << std::endl;
  }

  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
    xdc::Point1 pt1 { 3, 5, }, pt2 { 2, 5, };
    std::cout << std::boolalpha
              << (pt1 != pt2) << '\n'  // true
              << (pt1 == pt1) << '\n'; // true
    std::cout << std::noboolalpha;
    struct [[maybe_unused]] { int x{}, y{}; } p_val, q_val;
    // if (p_val == q_val) { } // Error: 'operator==' is not defined
  }

  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
    xdc::Point2 pt1 { 1, 1, }, pt2 { 1, 2, };
    std::set<xdc::Point2> poinsettia;  // ok
    poinsettia.insert(pt1);           // ok
    std::cout << std::boolalpha
              << (pt1 == pt2) << ' '  // false; operator== is implicitly defaulted.
              << (pt1 != pt2) << ' '  // true
              << (pt1 <  pt2) << ' '  // true
              << (pt1 <= pt2) << ' '  // true
              << (pt1 >  pt2) << ' '  // false
              << (pt1 >= pt2) << ' '; // false
    std::cout << std::noboolalpha;
    std::cout << std::endl;
  }

  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
    xdc::Point2 pt1 { 3, 5, }, pt2 { 2, 5, };
    std::cout << std::boolalpha
              << (pt1 != pt2) << '\n'  // true
              << (pt1 == pt1) << '\n'; // true
    std::cout << std::noboolalpha;
    struct [[maybe_unused]] { int x_val {}, y_val {}; } p_v, q_v;
    // if (p_v == q_v) { } // Error: 'operator==' is not defined
  }

  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
    static_assert( sizeof(int) == 4 ); // precondition
    std::cout << "static_assert( sizeof(int) == 4 ) passed\n"s;

    // Quite surprisingly
    static_assert( -1 > 1U );
    std::cout << "static_assert( -1 > 1U ) passed\n"s;
    // because after implicit conversion of -1 to the RHS type (`unsigned int`)
    // the expression is equivalent to:
    static_assert( 0xFFFFFFFFU > 1U );
    std::cout << "static_assert( 0xFFFFFFFFU > 1U ) passed\n"s;
    static_assert( 0xFFFFFFFFU == static_cast<unsigned>(-1) );
    std::cout << "static_assert( 0xFFFFFFFFU == static_cast<unsigned>(-1) ) passed\n"s;

#if (__cplusplus > 201707L)
    // In contrast, the cmp_* family compares integers as most expected -
    // negative signed integers always compare less than unsigned integers:
    static_assert( std::cmp_less( -1, 1U ) );
    static_assert( std::cmp_less_equal( -1, 1U ) );
    static_assert( ! std::cmp_greater( -1, 1U ) );
    static_assert( ! std::cmp_greater_equal( -1, 1U ) );
#endif
  }

#if (__cplusplus > 201707L)
  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
    std::cout << std::boolalpha;

    std::cout << std::in_range<std::size_t>(-1) << '\n';
    std::cout << std::in_range<std::size_t>(42) << '\n';

    std::cout << std::endl;
  }
#endif

  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
    xdc::Foo f1 = { 1 };
    xdc::Foo f2 = { 2 };
    using namespace std::rel_ops;

    std::cout << std::boolalpha;
    std::cout << "not equal?     : " << (f1 != f2) << '\n';
    std::cout << "greater?       : " << (f1 >  f2) << '\n';
    std::cout << "less equal?    : " << (f1 <= f2) << '\n';
    std::cout << "greater equal? : " << (f1 >= f2) << '\n';
    std::cout << std::noboolalpha;

    std::cout << std::endl;
  }

  // ....+....|....+....|....+....|....+....|....+....|....+....|
  std::cout << dot << '\n';
  {
#if (__cplusplus > 201707L)
    xdc::TotallyOrdered to1{ "a", "b", "c", "d" }, to2{ "a", "b", "d", "c" };
    std::set<xdc::TotallyOrdered> toast; // ok
    toast.insert(to1); // ok
    assert(to2 <= to1); // ok, single call to <=>
    std::cout << "success!\n";
#else
    xdc::TotallyOrdered to1{ 'a', 'b', 'c', 'd' }, to2{ 'a', 'b', 'd', 'c' };
    std::set<xdc::TotallyOrdered> toast; // ok
    toast.insert(to1); // ok

    assert(to2 <= to1); // ok, single call to <=>
    std::cout << "success!\n";

    xdc::TotallyOrdered to3{ 'c', 'b', 'c', 'd' };

    for (auto tlc : { to2, to3, }) {
      std::cout << "lhs: "
                << to1.zip       << ' ' << to1.tax_id << ' '
                << to1.last_name << ' ' << to1.first_name
                << '\n';
      std::cout << "rhs: "
                << tlc.zip       << ' ' << tlc.tax_id << ' '
                << tlc.last_name << ' ' << tlc.first_name
                << '\n';
      std::cout << std::boolalpha
                << "lhs == rhs: "
                << (to1 == tlc) << '\n' // operator== is implicitly defaulted.
                << "lhs != rhs: "
                << (to1 != tlc) << '\n' // ditto
                << "lhs <  rhs: "
                << (to1 <  tlc) << '\n'
                << "lhs <= rhs: "
                << (to1 <= tlc) << '\n'
                << "lhs >  rhs: "
                << (to1 >  tlc) << '\n'
                << "lhs >= rhs: "
                << (to1 >= tlc) << '\n';
      std::cout << std::noboolalpha;
    }
#endif

    std::cout << std::endl;
  }

  return 0;
}
