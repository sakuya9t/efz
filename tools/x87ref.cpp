// The compatibility test's reference (make trace, docs/compat.md) takes sin, cos and
// atan2 from here: port/x87.cpp's, correctly rounded to the x87's 64-bit significand.
// MinGW compiles this for 32-bit Windows (the original's compiler can't build
// port/x87.cpp), and src/trace.cpp puts it in place of the CRT's sin, cos and atan2.
//
// The original's came from the CPU's fsin, fcos and fpatan, whose last bits differ from
// one CPU to another (docs/native.md); with these the reference plays the same on every
// machine, as the native game does.
#include "../port/x87.cpp"

// The original's C library (Visual C++ .NET 2003's) has no nearbyint: rounded to the
// nearest integer, halves to even, as the default rounding mode does.
extern "C" double nearbyint(double x)
{
    const double big = 4503599627370496.0; // 2^52: above it every double is an integer
    double r;

    if (!(fabs(x) < big))
        return x;
    r = fabs(x) + big - big;
    return x < 0 || (x == 0 && signbit(x)) ? -r : r;
}

// op 0 sin(a), 1 cos(a), 2 atan2(a, b), as an x87 register's 10 bytes: the significand,
// then the sign and the biased exponent.
extern "C" void EfzReferenceTrig(int op, double a, double b, unsigned char* out)
{
    efz::X87Value v = op == 0 ? efz::Sin(a) : op == 1 ? efz::Cos(a) : efz::Atan2(a, b);
    uint16_t se = 0;

    if (v.mant)
        se = (uint16_t)(v.exp + 63 + 16383);
    if (v.neg)
        se |= 0x8000;
    memcpy(out, &v.mant, 8);
    memcpy(out + 8, &se, 2);
}
