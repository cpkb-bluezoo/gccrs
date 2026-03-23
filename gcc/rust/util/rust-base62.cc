// Copyright (C) 2020-2026 Free Software Foundation, Inc.

// This file is part of GCC.

// GCC is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3, or (at your option) any later
// version.

// GCC is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.

// You should have received a copy of the GNU General Public License
// along with GCC; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include "rust-base62.h"

namespace Rust {

std::string
base62_integer (uint64_t value)
{
  const static std::string base_64
    = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@$";
  std::string buffer (128, '\0');
  size_t idx = 0;
  size_t base = 62;

  do
    {
      buffer[idx] = base_64[(value % base)];
      idx++;
      value = value / base;
    }
  while (value != 0);

  std::reverse (buffer.begin (), buffer.begin () + idx);
  return buffer.substr (0, idx);
}

} // namespace Rust

#if CHECKING_P

#include "selftest.h"

namespace selftest {

void
rust_base62_integer_test ()
{
  ASSERT_EQ (Rust::base62_integer (0), "0");
  ASSERT_EQ (Rust::base62_integer (1), "1");
  ASSERT_EQ (Rust::base62_integer (10), "a");
  ASSERT_EQ (Rust::base62_integer (61), "Z");
  ASSERT_EQ (Rust::base62_integer (62), "10");
  ASSERT_EQ (Rust::base62_integer (62 * 62), "100");
  ASSERT_EQ (Rust::base62_integer (61 * 62 + 61), "ZZ");
  ASSERT_EQ (Rust::base62_integer (UINT64_C (18446744073709551615)),
	     "lYGhA16ahyf");
}

} // namespace selftest

#endif // CHECKING_P
