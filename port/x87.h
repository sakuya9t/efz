// The original's arithmetic where a 64-bit build's would differ.
//
// efz.exe ran its floating point on the x87 with the precision control at 53 bits (the
// CRT's default), and Visual C++ .NET 2003 without optimisation keeps each expression on
// the x87 stack. That gives SSE2's double results, except in two places this header
// handles:
// - floats: loaded onto the stack, they are computed with at double precision and only
//   rounded to float when stored (Float32, src/efz.h's F32);
// - sin, cos and atan2: the CRT's run fsin, fcos and fpatan, which leave a result with a
//   64-bit significand on the stack, and the next operation rounds what it makes of that
//   to 53 bits. cos(a) * speed is round53(cos_64(a) * speed), not the product of two
//   doubles (X87Value).
#ifndef EFZ_X87_H
#define EFZ_X87_H

#include <stdint.h>
#include <type_traits>

namespace efz {

// A float as the original's code used one: stored in 4 bytes, but loaded onto the x87
// stack, which held double precision, so that arithmetic on it is done in double and
// rounded to float only when the result is stored. src/efz.h's F32.
struct Float32 {
    float v;

    operator double() const { return v; }
    Float32& operator=(double d)
    {
        v = (float)d;
        return *this;
    }
    Float32& operator+=(double d) { return *this = (double)v + d; }
    Float32& operator-=(double d) { return *this = (double)v - d; }
    Float32& operator*=(double d) { return *this = (double)v * d; }
    Float32& operator/=(double d) { return *this = (double)v / d; }
};

// A value in an x87 register at full precision: (-1)^neg * mant * 2^exp, mant with its
// top bit set unless the value is zero.
struct X87Value {
    uint64_t mant;
    int exp;
    bool neg;

    // Rounded to 53 bits, as storing it as a double or passing it to a function does.
    operator double() const;
    // Truncated toward zero, as _ftol2 does with the register.
    explicit operator int() const;
    X87Value operator-() const
    {
        X87Value r = *this;
        r.neg = !r.neg;
        return r;
    }
};

// fsin, fcos and fpatan (atan2(y, x)), correctly rounded to 64 bits. The x87 rounds
// them about as well (on the CPUs measured, to within a few units in the 64th bit),
// so that what follows rounds the same to 53 bits nearly always; docs/native.md.
X87Value Sin(double x);
X87Value Cos(double x);
X87Value Atan2(double y, double x);

// One x87 operation with a register operand at full precision, rounded to 53 bits.
double Mul(X87Value a, double b);
double Add(X87Value a, double b);
double Div(X87Value a, double b);
double DivR(double a, X87Value b); // a / b
// -1, 0 or 1 as a is below, equal to or above b.
int Compare(X87Value a, double b);

template <class T>
using Arith = typename std::enable_if<std::is_arithmetic<T>::value, double>::type;
template <class T>
using ArithBool = typename std::enable_if<std::is_arithmetic<T>::value, bool>::type;

template <class T> Arith<T> operator*(X87Value a, T b) { return Mul(a, (double)b); }
template <class T> Arith<T> operator*(T a, X87Value b) { return Mul(b, (double)a); }
template <class T> Arith<T> operator+(X87Value a, T b) { return Add(a, (double)b); }
template <class T> Arith<T> operator+(T a, X87Value b) { return Add(b, (double)a); }
template <class T> Arith<T> operator-(X87Value a, T b) { return Add(a, -(double)b); }
template <class T> Arith<T> operator-(T a, X87Value b) { return Add(-b, (double)a); }
template <class T> Arith<T> operator/(X87Value a, T b) { return Div(a, (double)b); }
template <class T> Arith<T> operator/(T a, X87Value b) { return DivR((double)a, b); }
template <class T> ArithBool<T> operator<(X87Value a, T b) { return Compare(a, (double)b) < 0; }
template <class T> ArithBool<T> operator>(X87Value a, T b) { return Compare(a, (double)b) > 0; }
template <class T> ArithBool<T> operator<=(X87Value a, T b) { return Compare(a, (double)b) <= 0; }
template <class T> ArithBool<T> operator>=(X87Value a, T b) { return Compare(a, (double)b) >= 0; }
template <class T> ArithBool<T> operator<(T a, X87Value b) { return Compare(b, (double)a) > 0; }
template <class T> ArithBool<T> operator>(T a, X87Value b) { return Compare(b, (double)a) < 0; }
template <class T> ArithBool<T> operator<=(T a, X87Value b) { return Compare(b, (double)a) >= 0; }
template <class T> ArithBool<T> operator>=(T a, X87Value b) { return Compare(b, (double)a) <= 0; }
inline double operator*(X87Value a, Float32 b) { return Mul(a, b); }
inline double operator*(Float32 a, X87Value b) { return Mul(b, a); }

// The static CRT's rand and srand (Visual C++ .NET 2003), whose sequence the game's
// effects follow.
int Rand();
void Srand(unsigned seed);

} // namespace efz

#define F32 ::efz::Float32
#define F32CAST(x) ((double)(x))
// fabs(float): the argument is passed as a float, rounded once from double.
#define FABSF(x) fabs((double)(float)(double)(x))
#define sin(x) ::efz::Sin(x)
#define cos(x) ::efz::Cos(x)
#define atan2(y, x) ::efz::Atan2(y, x)
#define rand() ::efz::Rand()
#define srand(seed) ::efz::Srand(seed)

#endif
