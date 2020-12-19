//  Boost string_algo library predicate.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef STRING_PREDICATE_DETAIL_HPP
#define STRING_PREDICATE_DETAIL_HPP
#include <span>
#include <iterator>
#include "find.hpp"

namespace string_algo {
	namespace algorithm {
		namespace detail {

			//  ends_with predicate implementation ----------------------------------//

			template<
				typename ForwardIterator1T,
				typename ForwardIterator2T,
				typename PredicateT>
				inline bool ends_with_iter_select(
					ForwardIterator1T Begin,
					ForwardIterator1T End,
					ForwardIterator2T SubBegin,
					ForwardIterator2T SubEnd,
					PredicateT Comp,
					std::bidirectional_iterator_tag)
			{
				ForwardIterator1T it = End;
				ForwardIterator2T pit = SubEnd;
				for (; it != Begin && pit != SubBegin;)
				{
					if (!(Comp(*(--it), *(--pit))))
						return false;
				}

				return pit == SubBegin;
			}

			template<
				typename ForwardIterator1T,
				typename ForwardIterator2T,
				typename PredicateT>
				inline bool ends_with_iter_select(
					ForwardIterator1T Begin,
					ForwardIterator1T End,
					ForwardIterator2T SubBegin,
					ForwardIterator2T SubEnd,
					PredicateT Comp,
					std::forward_iterator_tag)
			{
				if (SubBegin == SubEnd)
				{
					// empty subsequence check
					return true;
				}

				auto Result
					= last_finder(
						std::span(SubBegin, SubEnd),
						Comp)(Begin, End);

				return !Result.empty() && Result.end() == End;
			}

		} // namespace detail
	} // namespace algorithm
} // namespace string_algo 


#endif  // STRING_PREDICATE_DETAIL_HPP
