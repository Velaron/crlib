//
// YaPB - Counter-Strike Bot based on PODBot by Markus Klinge.
// Copyright © 2004-2022 YaPB Project <yapb@jeefo.net>.
//
// SPDX-License-Identifier: MIT
//

#pragma once

// our global namaespace
#define CR_NAMESPACE_BEGIN namespace cr {
#define CR_NAMESPACE_END }

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <stddef.h>
#include <limits.h>

CR_NAMESPACE_BEGIN

//
// global helper stuff
//
template <typename T, size_t N> constexpr size_t bufsize (const T (&)[N]) {
   return N - 1;
}

template <typename T>  constexpr T abs (const T &a) {
   return a > 0 ? a : -a;
}

template <typename T>  constexpr T bit (const T &a) {
   return static_cast <T> (1ULL << a);
}

template <typename T>  constexpr T min (const T &a, const T &b) {
   return a < b ? a : b;
}

template <typename T>  constexpr T max (const T &a, const T &b) {
   return a > b ? a : b;
}

template <typename T> constexpr T square (const T &value) {
   return value * value;
}

template <typename T>  constexpr T clamp (const T &x, const T &a, const T &b) {
   return min (max (x, a), b);
}

template <typename T> const T &fix (const T &type) {
   return type;
}

//
// base classes
//

// simple non-copying base class
class DenyCopying {
protected:
   explicit DenyCopying () = default;
   ~DenyCopying () = default;

public:
   DenyCopying (const DenyCopying &) = delete;
   DenyCopying &operator = (const DenyCopying &) = delete;
};

// singleton for objects
template <typename T> class Singleton : public DenyCopying {
protected:
   Singleton () = default;
   ~Singleton () = default;

public:
   static  T &instance () {
      static T __instance;
      return __instance;
   }
};

// simple scoped enum, instaed of enum class
#define CR_DECLARE_SCOPED_ENUM_TYPE(enumName, enumType, ...) \
   CR_NAMESPACE_BEGIN                                        \
   namespace enums {                                         \
      struct _##enumName : protected DenyCopying {           \
         enum Type : enumType {                              \
            __VA_ARGS__                                      \
         };                                                  \
      };                                                     \
   }                                                         \
   CR_NAMESPACE_END                                          \
   using enumName = ::cr::enums::_##enumName::Type;          \

// same as above, but with int32_t type
#define CR_DECLARE_SCOPED_ENUM(enumName, ...)                  \
   CR_DECLARE_SCOPED_ENUM_TYPE(enumName, int32_t, __VA_ARGS__)   \

// exposes global variable from class singleton
#define CR_EXPOSE_GLOBAL_SINGLETON(className, variable)  \
   static auto &variable { className::instance () }      \

CR_NAMESPACE_END

// platform-dependant-stuff
#include <crlib/platform.h>
