
// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2006-2007 Benoit Jacob <jacob@math.jussieu.fr>
//
// Eigen is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 or (at your option) any later version.
//
// Eigen is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along
// with Eigen; if not, write to the Free Software Foundation, Inc., 51
// Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
//
// As a special exception, if other files instantiate templates or use macros
// or functions from this file, or you compile this file and link it
// with other works to produce a work based on this file, this file does not
// by itself cause the resulting work to be covered by the GNU General Public
// License. This exception does not invalidate any other reasons why a work
// based on this file might be covered by the GNU General Public License.

#ifndef EI_NUMERIC_H
#define EI_NUMERIC_H

template<typename T> struct NumTraits;

template<> struct NumTraits<int>
{
  typedef int Real;
  typedef double FloatingPoint;
  typedef double RealFloatingPoint;
  
  static const bool IsComplex = false;
  static const bool HasFloatingPoint = false;
  
  static int epsilon() { return 0; }
  static int epsilon2() { return 0; }
  static int real(const int& x) { return x; }
  static int imag(const int& x) { EI_UNUSED(x); return 0; }
  static int conj(const int& x) { return x; }
  static double sqrt(const int& x) { return std::sqrt(static_cast<double>(x)); }
  static int abs(const int& x) { return std::abs(x); }
  static int abs2(const int& x) { return x*x; }
  static int rand()
  {
    // "rand() % n" is bad, they say, because the low-order bits are not random enough.
    // However here, 21 is odd, so rand() % 21 uses the high-order bits
    // as well, so there's no problem.
    return (std::rand() % 21) - 10;
  }
  static bool negligible(const int& a, const int& b)
  {
    EI_UNUSED(b);
    return(a == 0);
  }
  static bool approx(const int& a, const int& b)
  {
    return(a == b);
  }
  static bool lessThanOrApprox(const int& a, const int& b)
  {
    return(a <= b);
  }
};

template<> struct NumTraits<float>
{
  typedef float Real;
  typedef float FloatingPoint;
  typedef float RealFloatingPoint;
  
  static const bool IsComplex = false;
  static const bool HasFloatingPoint = true;
  
  static float epsilon() { return 1e-5f; }
  static float epsilon2() { return epsilon() * epsilon(); }
  static float real(const float& x) { return x; }
  static float imag(const float& x) { EI_UNUSED(x); return 0; }
  static float conj(const float& x) { return x; }
  static float sqrt(const float& x) { return std::sqrt(x); }
  static float abs(const float& x) { return std::abs(x); }
  static float abs2(const float& x) { return x*x; }
  static float rand()
  {
    return std::rand() / (RAND_MAX/20.0f) - 10.0f;
  }
  static bool negligible(const float& a, const float& b)
  {
    return(abs(a) <= abs(b) * epsilon());
  }
  static bool approx(const float& a, const float& b)
  {
    return(abs(a - b) <= std::min(abs(a), abs(b)) * epsilon());
  }
  static bool lessThanOrApprox(const float& a, const float& b)
  {
    return(a <= b || approx(a, b));
  }
};

template<> struct NumTraits<double>
{
  typedef double Real;
  typedef double FloatingPoint;
  typedef double RealFloatingPoint;
  
  static const bool IsComplex = false;
  static const bool HasFloatingPoint = true;
  
  static double epsilon() { return 1e-11; }
  static double epsilon2() { return epsilon() * epsilon(); }
  static double real(const double& x) { return x; }
  static double imag(const double& x) { EI_UNUSED(x); return 0; }
  static double conj(const double& x) { return x; }
  static double sqrt(const double& x) { return std::sqrt(x); }
  static double abs(const double& x) { return std::abs(x); }
  static double abs2(const double& x) { return x*x; }
  static double rand()
  {
    return std::rand() / (RAND_MAX/20.0) - 10.0;
  }
  static bool negligible(const double& a, const double& b)
  {
    return(abs(a) <= abs(b) * epsilon());
  }
  static bool approx(const double& a, const double& b)
  {
    return(abs(a - b) <= std::min(abs(a), abs(b)) * epsilon());
  }
  static bool lessThanOrApprox(const double& a, const double& b)
  {
    return(a <= b || approx(a, b));
  }
};

template<typename _Real> struct NumTraits<std::complex<_Real> >
{
  typedef _Real Real;
  typedef std::complex<Real> Complex;
  typedef std::complex<double> FloatingPoint;
  typedef typename NumTraits<Real>::FloatingPoint RealFloatingPoint;
  
  static const bool IsComplex = true;
  static const bool HasFloatingPoint = NumTraits<Real>::HasFloatingPoint;
  
  static Real epsilon() { return NumTraits<Real>::epsilon(); }
  static Real epsilon2() { return epsilon() * epsilon(); }
  static Real real(const Complex& x) { return std::real(x); }
  static Real imag(const Complex& x) { return std::imag(x); }
  static Complex conj(const Complex& x) { return std::conj(x); }
  static FloatingPoint sqrt(const Complex& x)
  { return std::sqrt(static_cast<FloatingPoint>(x)); }
  static RealFloatingPoint abs(const Complex& x)
  { return std::abs(static_cast<FloatingPoint>(x)); }
  static Real abs2(const Complex& x)
  { return std::real(x) * std::real(x) + std::imag(x) * std::imag(x); }
  static Complex rand()
  {
    return Complex(NumTraits<Real>::rand(), NumTraits<Real>::rand());
  }
  static bool negligible(const Complex& a, const Complex& b)
  {
    return(abs2(a) <= abs2(b) * epsilon2());
  }
  static bool approx(const Complex& a, const Complex& b)
  {
    return(NumTraits<Real>::approx(std::real(a), std::real(b))
        && NumTraits<Real>::approx(std::imag(a), std::imag(b)));
  }
  // lessThanOrApprox wouldn't make sense for complex numbers
};

#endif // EI_NUMERIC_H
