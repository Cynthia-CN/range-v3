// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_UNIQUE_HPP
#define RANGES_V3_VIEW_UNIQUE_HPP

#include <utility>
#include <range/v3/range_fwd.hpp>
#include <range/v3/view/adjacent_filter.hpp>
#include <range/v3/view/view.hpp>

namespace ranges
{
    inline namespace v3
    {
        /// \cond
        namespace detail
        {
            struct not_equal_to
            {
                template<typename T>
                bool operator()(T && t, T && u) const
                {
                    return !(std::forward<T>(t) == std::forward<T>(u));
                }
            };
        }
        /// \endcond

        /// \addtogroup group-views
        /// @{
        namespace view
        {
            struct unique_fn
            {
                template<typename Rng>
                using Concept = meta::and_<
                    ForwardIterable<Rng>,
                    EqualityComparable<range_value_t<Rng>>>;

                template<typename Rng, CONCEPT_REQUIRES_(Concept<Rng>())>
                unique_view<Rng> operator()(Rng && rng) const
                {
                    return {std::forward<Rng>(rng), detail::not_equal_to{}};
                }
            #ifndef RANGES_DOXYGEN_INVOKED
                template<typename Rng,
                    CONCEPT_REQUIRES_(!Concept<Rng>())>
                void operator()(Rng &&) const
                {
                    CONCEPT_ASSERT_MSG(ForwardIterable<Rng>(),
                        "The object on which view::unique operates must be a model the "
                        "ForwardIterable concept.");
                    CONCEPT_ASSERT_MSG(EqualityComparable<range_value_t<Rng>>(),
                        "The value type of the range passed to view::unique must be "
                        "EqualityComparable.");
                }
            #endif
            };

            /// \sa `unique_fn`
            /// \ingroup group-views
            constexpr view<unique_fn> unique{};
        }
        /// @}
    }
}

#endif
