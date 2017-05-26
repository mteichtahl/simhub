// MPark.Variant
//
// Copyright Michael Park, 2015-2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <mpark/variant.hpp>

#include <string>

#include <gtest/gtest.h>

TEST(Cnstr_Default, Variant) {
  mpark::variant<int, std::string> v;
  EXPECT_EQ(0, mpark::get<0>(v));

  /* constexpr */ {
    constexpr mpark::variant<int> cv;
    static_assert(0 == mpark::get<0>(cv), "");
  }
}
