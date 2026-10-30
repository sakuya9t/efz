// The original's arithmetic where a 64-bit build's would differ (x87.h).
//
// sin, cos and atan2 are computed in double-double arithmetic (about 100 bits) and
// rounded to the x87's 64-bit significand; an operation between such a value and a
// double is done exactly on integers and rounded once to 53 bits, as the x87 rounds
// with its precision control at 53 bits. Everything here is integer arithmetic and
// basic IEEE double operations without fused multiply-add, so it gives the same bits
// on every machine.
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "x87.h"

namespace efz {

namespace {

// --- 128-bit integers.

struct U128 {
    uint64_t hi, lo;
};

U128 Mul64(uint64_t a, uint64_t b)
{
    uint64_t a0 = (uint32_t)a, a1 = a >> 32, b0 = (uint32_t)b, b1 = b >> 32;
    uint64_t p00 = a0 * b0, p01 = a0 * b1, p10 = a1 * b0, p11 = a1 * b1;
    uint64_t mid = (p00 >> 32) + (uint32_t)p01 + (uint32_t)p10;
    U128 r;
    r.lo = (mid << 32) | (uint32_t)p00;
    r.hi = p11 + (p01 >> 32) + (p10 >> 32) + (mid >> 32);
    return r;
}

U128 Shl(U128 v, int s)
{
    if (s == 0)
        return v;
    if (s >= 64)
        return U128{v.lo << (s - 64), 0};
    return U128{(v.hi << s) | (v.lo >> (64 - s)), v.lo << s};
}

U128 Shr(U128 v, int s)
{
    if (s == 0)
        return v;
    if (s >= 128)
        return U128{0, 0};
    if (s >= 64)
        return U128{0, v.hi >> (s - 64)};
    return U128{v.hi >> s, (v.lo >> s) | (v.hi << (64 - s))};
}

U128 Add128(U128 a, U128 b)
{
    U128 r{a.hi + b.hi, a.lo + b.lo};
    r.hi += r.lo < a.lo;
    return r;
}

U128 Sub128(U128 a, U128 b)
{
    U128 r{a.hi - b.hi, a.lo - b.lo};
    r.hi -= a.lo < b.lo;
    return r;
}

bool Less(U128 a, U128 b)
{
    return a.hi < b.hi || (a.hi == b.hi && a.lo < b.lo);
}

bool IsZero(U128 a)
{
    return !a.hi && !a.lo;
}

int Bits(U128 v)
{
    int n = 0;
    uint64_t w = v.hi ? v.hi : v.lo;
    while (w) {
        n++;
        w >>= 1;
    }
    return v.hi ? n + 64 : n;
}

// Bits [0, s) of v are not all zero.
bool LowBits(U128 v, int s)
{
    if (s <= 0)
        return false;
    if (s >= 128)
        return !IsZero(v);
    U128 kept = Shl(Shr(v, s), s);
    return kept.hi != v.hi || kept.lo != v.lo;
}

// (-1)^neg * (m + a sticky fraction below it if `sticky`) * 2^exp, rounded to nearest
// even with `bits` significant bits: the significand and the exponent of its last bit.
void Round(U128 m, int exp, bool sticky, int bits, uint64_t& out, int& outExp)
{
    int n = Bits(m);
    if (n <= bits) {
        out = m.lo;
        outExp = exp;
        return;
    }
    int s = n - bits;
    uint64_t q = Shr(m, s).lo;
    bool guard = Shr(m, s - 1).lo & 1;
    bool rest = sticky || LowBits(m, s - 1);
    if (guard && (rest || (q & 1)))
        q++;
    if (q >> bits) {
        q >>= 1;
        s++;
    }
    out = q;
    outExp = exp + s;
}

double ToDouble(bool neg, U128 m, int exp, bool sticky)
{
    uint64_t q;
    int e;
    if (IsZero(m))
        return neg ? -0.0 : 0.0;
    Round(m, exp, sticky, 53, q, e);
    double d = ldexp((double)q, e);
    return neg ? -d : d;
}

// A finite nonzero double as m * 2^e, m an integer of 53 bits with the top one set.
void Decompose(double d, uint64_t& m, int& e)
{
    int k;
    double f = frexp(fabs(d), &k);
    m = (uint64_t)ldexp(f, 53);
    e = k - 53;
}

// --- Double-double arithmetic, about 104 bits.

struct DD {
    double hi, lo;
};

DD TwoSum(double a, double b)
{
    double s = a + b;
    double bb = s - a;
    return DD{s, (a - (s - bb)) + (b - bb)};
}

DD QuickTwoSum(double a, double b)
{
    double s = a + b;
    return DD{s, b - (s - a)};
}

void Split(double a, double& hi, double& lo)
{
    double t = 134217729.0 * a;
    hi = t - (t - a);
    lo = a - hi;
}

DD TwoProd(double a, double b)
{
    double p = a * b, ah, al, bh, bl;
    Split(a, ah, al);
    Split(b, bh, bl);
    return DD{p, ((ah * bh - p) + ah * bl + al * bh) + al * bl};
}

DD operator+(DD a, DD b)
{
    DD s = TwoSum(a.hi, b.hi);
    DD t = TwoSum(a.lo, b.lo);
    s.lo += t.hi;
    s = QuickTwoSum(s.hi, s.lo);
    s.lo += t.lo;
    return QuickTwoSum(s.hi, s.lo);
}

DD operator-(DD a)
{
    return DD{-a.hi, -a.lo};
}

DD operator-(DD a, DD b)
{
    return a + -b;
}

DD operator*(DD a, DD b)
{
    DD p = TwoProd(a.hi, b.hi);
    p.lo += a.hi * b.lo + a.lo * b.hi;
    return QuickTwoSum(p.hi, p.lo);
}

DD operator/(DD a, DD b)
{
    double q1 = a.hi / b.hi;
    DD r = a - b * DD{q1, 0};
    double q2 = r.hi / b.hi;
    r = r - b * DD{q2, 0};
    double q3 = r.hi / b.hi;
    return QuickTwoSum(q1, q2) + DD{q3, 0};
}

DD Sqrt(DD a)
{
    double q = sqrt(a.hi);
    DD r = a - TwoProd(q, q);
    return QuickTwoSum(q, r.hi / (2 * q));
}

const DD kPi = {0x1.921fb54442d18p+1, 0x1.1a62633145c07p-53};
const DD kPiO2 = {0x1.921fb54442d18p+0, 0x1.1a62633145c07p-54};
// pi/2 in pieces of 30 bits, so that k times each is exact for |k| < 2^23.
const double kPiO2Parts[] = {0x1.921fb54000000p+0, 0x1.10b4611800000p-30, 0x1.313198a000000p-61,
                             0x1.701b839800000p-92, 0x1.129024e000000p-123,
                             0x1.114cf98800000p-156, 0x1.a0105df000000p-186};

// 1/n! for n = 0 to 35.
const DD kInvFact[] = {
    {1.0, 0.0}, {1.0, 0.0},
    {0x1.0000000000000p-1, 0x0.0p+0}, {0x1.5555555555555p-3, 0x1.5555555555555p-57},
    {0x1.5555555555555p-5, 0x1.5555555555555p-59}, {0x1.1111111111111p-7, 0x1.1111111111111p-63},
    {0x1.6c16c16c16c17p-10, -0x1.f49f49f49f49fp-65}, {0x1.a01a01a01a01ap-13, 0x1.a01a01a01a01ap-73},
    {0x1.a01a01a01a01ap-16, 0x1.a01a01a01a01ap-76}, {0x1.71de3a556c734p-19, -0x1.c154f8ddc6c00p-73},
    {0x1.27e4fb7789f5cp-22, 0x1.cbbc05b4fa99ap-76}, {0x1.ae64567f544e4p-26, -0x1.c062e06d1f209p-80},
    {0x1.1eed8eff8d898p-29, -0x1.2aec959e14c06p-83}, {0x1.6124613a86d09p-33, 0x1.f28e0cc748ebep-87},
    {0x1.93974a8c07c9dp-37, 0x1.05d6f8a2efd1fp-92}, {0x1.ae7f3e733b81fp-41, 0x1.1d8656b0ee8cbp-97},
    {0x1.ae7f3e733b81fp-45, 0x1.1d8656b0ee8cbp-101}, {0x1.952c77030ad4ap-49, 0x1.ac981465ddc6cp-103},
    {0x1.6827863b97d97p-53, 0x1.eec01221a8b0bp-107}, {0x1.2f49b46814157p-57, 0x1.2650f61dbdcb4p-112},
    {0x1.e542ba4020225p-62, 0x1.ea72b4afe3c2fp-120}, {0x1.71b8ef6dcf572p-66, -0x1.d043ae40c4647p-120},
    {0x1.0ce396db7f853p-70, -0x1.aebcdbd20331cp-124}, {0x1.761b41316381ap-75, -0x1.3423c7d91404fp-130},
    {0x1.f2cf01972f578p-80, -0x1.9ada5fcc1ab14p-135}, {0x1.3f3ccdd165fa9p-84, -0x1.58ddadf344487p-139},
    {0x1.88e85fc6a4e5ap-89, -0x1.71c37ebd16540p-143}, {0x1.d1ab1c2dccea3p-94, 0x1.054d0c78aea14p-149},
    {0x1.0a18a2635085dp-98, 0x1.b9e2e28e1aa54p-153}, {0x1.259f98b4358adp-103, 0x1.eaf8c39dd9bc5p-157},
    {0x1.3932c5047d60ep-108, 0x1.832b7b530a627p-162}, {0x1.434d2e783f5bcp-113, 0x1.0b87b91be9affp-167},
    {0x1.434d2e783f5bcp-118, 0x1.0b87b91be9affp-172}, {0x1.3981254dd0d52p-123, -0x1.2b1f4c8015a2fp-177},
    {0x1.2710231c0fd7ap-128, 0x1.3f8a2b4af9d6bp-184}, {0x1.0dc59c716d91fp-133, 0x1.419e3fad3f031p-188},
};

// 1/(2n + 1) for n = 0 to 34.
const DD kInvOdd[] = {
    {1.0, 0.0},
    {0x1.5555555555555p-2, 0x1.5555555555555p-56}, {0x1.999999999999ap-3, -0x1.999999999999ap-57},
    {0x1.2492492492492p-3, 0x1.2492492492492p-57}, {0x1.c71c71c71c71cp-4, 0x1.c71c71c71c71cp-58},
    {0x1.745d1745d1746p-4, -0x1.745d1745d1746p-59}, {0x1.3b13b13b13b14p-4, -0x1.3b13b13b13b14p-58},
    {0x1.1111111111111p-4, 0x1.1111111111111p-60}, {0x1.e1e1e1e1e1e1ep-5, 0x1.e1e1e1e1e1e1ep-61},
    {0x1.af286bca1af28p-5, 0x1.af286bca1af28p-59}, {0x1.8618618618618p-5, 0x1.8618618618618p-59},
    {0x1.642c8590b2164p-5, 0x1.642c8590b2164p-60}, {0x1.47ae147ae147bp-5, -0x1.eb851eb851eb8p-61},
    {0x1.2f684bda12f68p-5, 0x1.2f684bda12f68p-59}, {0x1.1a7b9611a7b96p-5, 0x1.1a7b9611a7b96p-61},
    {0x1.0842108421084p-5, 0x1.0842108421084p-60}, {0x1.f07c1f07c1f08p-6, -0x1.f07c1f07c1f08p-61},
    {0x1.d41d41d41d41dp-6, 0x1.0750750750750p-60}, {0x1.bacf914c1bad0p-6, -0x1.bacf914c1bad0p-60},
    {0x1.a41a41a41a41ap-6, 0x1.0690690690690p-60}, {0x1.8f9c18f9c18fap-6, -0x1.f3831f3831f38p-61},
    {0x1.7d05f417d05f4p-6, 0x1.7d05f417d05f4p-62}, {0x1.6c16c16c16c17p-6, -0x1.f49f49f49f49fp-61},
    {0x1.5c9882b931057p-6, 0x1.310572620ae4cp-61}, {0x1.4e5e0a72f0539p-6, 0x1.e0a72f0539783p-60},
    {0x1.4141414141414p-6, 0x1.4141414141414p-62}, {0x1.3521cfb2b78c1p-6, 0x1.a90e7d95bc60ap-61},
    {0x1.29e4129e4129ep-6, 0x1.04a7904a7904ap-60}, {0x1.1f7047dc11f70p-6, 0x1.1f7047dc11f70p-60},
    {0x1.15b1e5f75270dp-6, 0x1.15b1e5f75270dp-64}, {0x1.0c9714fbcda3bp-6, -0x1.f79b47582192ep-61},
    {0x1.0410410410410p-6, 0x1.0410410410410p-60}, {0x1.f81f81f81f820p-7, -0x1.f81f81f81f820p-61},
    {0x1.e9131abf0b767p-7, 0x1.503d226357e17p-62}, {0x1.dae6076b981dbp-7, -0x1.9f89467e251a0p-63},
};

// The double-double hi + lo rounded to a 64-bit significand.
X87Value ToX87(DD v)
{
    X87Value r;
    v = QuickTwoSum(v.hi, v.lo);
    r.neg = v.hi < 0 || (v.hi == 0 && signbit(v.hi));
    if (v.hi == 0) {
        r.mant = 0;
        r.exp = 0;
        return r;
    }
    if (r.neg)
        v = -v;
    uint64_t mh;
    int eh;
    Decompose(v.hi, mh, eh);
    // hi + lo = (mh * 2^s + lo / 2^(eh - s)) * 2^(eh - s): 11 more bits make 64, 12 if
    // lo takes the sum below hi's power of two.
    for (int s = 11; s <= 12; s++) {
        double l = ldexp(v.lo, s - eh);
        double li = floor(l);
        double lf = l - li;
        uint64_t n = (mh << s) + (uint64_t)(int64_t)li;
        if (!(n >> 63) && s == 11)
            continue;
        if (lf > 0.5 || (lf == 0.5 && (n & 1)))
            n++;
        int exp = eh - s;
        if (!n) {
            n = (uint64_t)1 << 63;
            exp++;
        }
        r.mant = n;
        r.exp = exp;
        return r;
    }
    r.mant = mh << 11;
    r.exp = eh - 11;
    return r;
}

DD SinSeries(DD r)
{
    DD r2 = r * r;
    DD p = kInvFact[33];
    for (int k = 15; k >= 0; k--) {
        DD c = kInvFact[2 * k + 1];
        p = p * r2 + (k & 1 ? -c : c);
    }
    return r * p;
}

DD CosSeries(DD r)
{
    DD r2 = r * r;
    DD p = -kInvFact[34];
    for (int k = 16; k >= 0; k--) {
        DD c = kInvFact[2 * k];
        p = p * r2 + (k & 1 ? -c : c);
    }
    return p;
}

// x - k pi/2 for the k that leaves it within pi/4; k mod 4 in q.
DD Reduce(double x, int& q)
{
    double k = nearbyint(x * 0x1.45f306dc9c883p-1);
    DD r = {x, 0.0};
    for (double part : kPiO2Parts)
        r = r - TwoProd(k, part);
    q = (int)(((int64_t)fmod(k, 4.0) + 4) % 4);
    return r;
}

// atan(t) for 0 <= t <= 1.
DD AtanDD(DD t)
{
    // atan(t) = 2 atan(t / (1 + sqrt(1 + t^2))), twice: t below tan(pi/16).
    for (int i = 0; i < 2; i++)
        t = t / (DD{1.0, 0.0} + Sqrt(DD{1.0, 0.0} + t * t));
    DD u = t * t;
    DD p = kInvOdd[34];
    for (int n = 33; n >= 0; n--)
        p = p * u + (n & 1 ? -kInvOdd[n] : kInvOdd[n]);
    DD a = t * p;
    return a + a + a + a;
}

uint32_t g_holdrand = 1;

#if defined(EFZ_HOST_X87) && defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#define EFZ_USE_HOST_X87 1
// The register an x87 instruction left, as an X87Value.
X87Value FromRegister(const unsigned char* bytes)
{
    X87Value r;
    uint16_t se;
    memcpy(&r.mant, bytes, 8);
    memcpy(&se, bytes + 8, 2);
    r.neg = se >> 15;
    r.exp = r.mant ? (se & 0x7fff) - 16383 - 63 : 0;
    return r;
}
#endif

} // namespace

#ifdef EFZ_USE_HOST_X87
// EFZ_HOST_X87: this CPU's own fsin, fcos and fpatan, as the original used them. The
// results then match the original's on the same machine exactly, and differ between
// CPUs as the original's do.
X87Value Sin(double x)
{
    unsigned char r[10];
    __asm__ volatile("fldl %1\n\tfsin\n\tfstpt %0" : "=m"(r) : "m"(x));
    return FromRegister(r);
}

X87Value Cos(double x)
{
    unsigned char r[10];
    __asm__ volatile("fldl %1\n\tfcos\n\tfstpt %0" : "=m"(r) : "m"(x));
    return FromRegister(r);
}

X87Value Atan2(double y, double x)
{
    unsigned char r[10];
    __asm__ volatile("fldl %1\n\tfldl %2\n\tfpatan\n\tfstpt %0" : "=m"(r) : "m"(y), "m"(x));
    return FromRegister(r);
}
#else
X87Value Sin(double x)
{
    if (x == 0 || !isfinite(x))
        return ToX87(DD{x == 0 ? x : NAN, 0.0});
    int q;
    DD r = Reduce(x, q);
    DD v = q == 0 ? SinSeries(r) : q == 1 ? CosSeries(r) : q == 2 ? -SinSeries(r) : -CosSeries(r);
    return ToX87(v);
}

X87Value Cos(double x)
{
    if (!isfinite(x))
        return ToX87(DD{NAN, 0.0});
    int q;
    DD r = Reduce(x, q);
    DD v = q == 0 ? CosSeries(r) : q == 1 ? -SinSeries(r) : q == 2 ? -CosSeries(r) : SinSeries(r);
    return ToX87(v);
}

X87Value Atan2(double y, double x)
{
    DD a;
    double ay = fabs(y), ax = fabs(x);
    if (ay == 0 && ax == 0)
        a = DD{0.0, 0.0};
    else if (ay <= ax)
        a = AtanDD(DD{ay, 0.0} / DD{ax, 0.0});
    else
        a = kPiO2 - AtanDD(DD{ax, 0.0} / DD{ay, 0.0});
    if (signbit(x))
        a = kPi - a;
    if (signbit(y))
        a = -a;
    return ToX87(a);
}
#endif

X87Value::operator double() const
{
    return ToDouble(neg, U128{0, mant}, exp, false);
}

X87Value::operator int() const
{
    uint64_t m = mant;
    if (exp >= 0)
        m = exp >= 64 ? 0 : m << exp;
    else
        m = -exp >= 64 ? 0 : m >> -exp;
    return neg ? -(int)(int64_t)m : (int)(int64_t)m;
}

double Mul(X87Value a, double b)
{
    bool neg = a.neg != (signbit(b) != 0);
    if (!a.mant || b == 0)
        return neg ? -0.0 : 0.0;
    uint64_t mb;
    int eb;
    Decompose(b, mb, eb);
    return ToDouble(neg, Mul64(a.mant, mb), a.exp + eb, false);
}

double Add(X87Value a, double b)
{
    if (b == 0)
        return (double)a;
    if (!a.mant)
        return b;
    uint64_t mb;
    int eb;
    Decompose(b, mb, eb);
    bool nb = b < 0;
    // Both on a common exponent; an operand more than 63 bits below the other only
    // counts as a sticky bit at the bottom.
    U128 ua{0, a.mant}, ub{0, mb};
    int exp;
    if (a.exp >= eb) {
        int d = a.exp - eb;
        if (d > 63) {
            ua = Shl(ua, 63);
            ub = U128{0, 1};
            exp = a.exp - 63;
        } else {
            ua = Shl(ua, d);
            exp = eb;
        }
    } else {
        int d = eb - a.exp;
        if (d > 63) {
            ub = Shl(ub, 63);
            ua = U128{0, 1};
            exp = eb - 63;
        } else {
            ub = Shl(ub, d);
            exp = a.exp;
        }
    }
    if (a.neg == nb)
        return ToDouble(nb, Add128(ua, ub), exp, false);
    if (Less(ua, ub))
        return ToDouble(nb, Sub128(ub, ua), exp, false);
    if (Less(ub, ua))
        return ToDouble(a.neg, Sub128(ua, ub), exp, false);
    return 0.0;
}

// (a << 64) / b and whether there is a remainder; a, b with their top bits set.
static U128 Divide(uint64_t a, uint64_t b, bool& remainder)
{
    U128 q{0, 0};
    U128 r{0, 0};
    U128 n{a, 0};
    for (int i = 127; i >= 0; i--) {
        r = Shl(r, 1);
        r.lo |= Shr(n, i).lo & 1;
        q = Shl(q, 1);
        if (!Less(r, U128{0, b})) {
            r = Sub128(r, U128{0, b});
            q.lo |= 1;
        }
    }
    remainder = !IsZero(r);
    return q;
}

double Div(X87Value a, double b)
{
    bool neg = a.neg != (signbit(b) != 0);
    if (!a.mant)
        return neg ? -0.0 : 0.0;
    uint64_t mb;
    int eb;
    Decompose(b, mb, eb);
    bool rem;
    U128 q = Divide(a.mant, mb << 11, rem);
    return ToDouble(neg, q, a.exp - (eb - 11) - 64, rem);
}

double DivR(double a, X87Value b)
{
    bool neg = b.neg != (signbit(a) != 0);
    if (a == 0)
        return neg ? -0.0 : 0.0;
    uint64_t ma;
    int ea;
    Decompose(a, ma, ea);
    bool rem;
    U128 q = Divide(ma << 11, b.mant, rem);
    return ToDouble(neg, q, ea - 11 - b.exp - 64, rem);
}

int Compare(X87Value a, double b)
{
    bool nb = signbit(b) != 0;
    if (!a.mant && b == 0)
        return 0;
    if (!a.mant)
        return nb ? 1 : -1;
    if (b == 0 || a.neg != nb)
        return a.neg ? -1 : 1;
    uint64_t mb;
    int eb;
    Decompose(b, mb, eb);
    mb <<= 11;
    eb -= 11;
    int mag = a.exp != eb ? (a.exp > eb ? 1 : -1) : a.mant != mb ? (a.mant > mb ? 1 : -1) : 0;
    return a.neg ? -mag : mag;
}

int Rand()
{
    g_holdrand = g_holdrand * 214013u + 2531011u;
    return (g_holdrand >> 16) & 0x7fff;
}

void Srand(unsigned seed)
{
    g_holdrand = seed;
}

} // namespace efz
