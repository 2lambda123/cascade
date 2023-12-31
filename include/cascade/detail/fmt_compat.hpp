// Copyright 2022 Francesco Biscani (bluescarni@gmail.com), Dario Izzo (dario.izzo@gmail.com)
//
// This file is part of the cascade library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CASCADE_DETAIL_FMT_COMPAT_HPP
#define CASCADE_DETAIL_FMT_COMPAT_HPP

#include <stdexcept>

#include <fmt/core.h>

#if FMT_VERSION >= 90000L

#include <fmt/ostream.h>

#else

#include <sstream>

#include <fmt/format.h>

#endif

namespace cascade::detail
{

#if FMT_VERSION >= 90000L

using ostream_formatter = fmt::ostream_formatter;

#else

struct ostream_formatter {
    template <typename ParseContext>
    constexpr auto parse(ParseContext &ctx)
    {
        if (ctx.begin() != ctx.end()) {
            // LCOV_EXCL_START
            throw std::invalid_argument("The ostream formatter does not accept any format string");
            // LCOV_EXCL_STOP
        }

        return ctx.begin();
    }

    template <typename T, typename FormatContext>
    auto format(const T &x, FormatContext &ctx)
    {
        std::ostringstream oss;
        oss << x;

        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};

#endif

} // namespace cascade::detail

#endif
