

#ifndef STRING_TRIM_DETAIL_HPP
#define STRING_TRIM_DETAIL_HPP

#include <iterator>
namespace string_algo
{
	namespace algorithm
	{
		namespace detail
		{

			//  trim iterator helper -----------------------------------------------//
			template< typename ForwardIteratorT, typename PredicateT >
			inline ForwardIteratorT trim_end_iter_select(
				ForwardIteratorT InBegin,
				ForwardIteratorT InEnd,
				PredicateT IsSpace,
				std::forward_iterator_tag)
			{
				ForwardIteratorT TrimIt = InBegin;

				for (ForwardIteratorT It = InBegin; It != InEnd; ++It)
				{
					if (!IsSpace(*It))
					{
						TrimIt = It;
						++TrimIt;
					}
				}

				return TrimIt;
			}

			template< typename ForwardIteratorT, typename PredicateT >
			inline ForwardIteratorT trim_end_iter_select(
				ForwardIteratorT InBegin,
				ForwardIteratorT InEnd,
				PredicateT IsSpace,
				std::bidirectional_iterator_tag)
			{
				for (ForwardIteratorT It = InEnd; It != InBegin; )
				{
					if (!IsSpace(*(--It)))
						return ++It;
				}

				return InBegin;
			}
			// Search for first non matching character from the beginning of the sequence
			template< typename ForwardIteratorT, typename PredicateT >
			inline ForwardIteratorT trim_begin(
				ForwardIteratorT InBegin,
				ForwardIteratorT InEnd,
				PredicateT IsSpace)
			{
				ForwardIteratorT It = InBegin;
				for (; It != InEnd; ++It)
				{
					if (!IsSpace(*It))
						return It;
				}

				return It;
			}

			// Search for first non matching character from the end of the sequence
			template< typename ForwardIteratorT, typename PredicateT >
			inline ForwardIteratorT trim_end(
				ForwardIteratorT InBegin,
				ForwardIteratorT InEnd,
				PredicateT IsSpace)
			{
				typedef typename std::iterator_traits<ForwardIteratorT>::iterator_category category;

				return algorithm::detail::trim_end_iter_select(InBegin, InEnd, IsSpace, category());
			}

		} // namespace detail
	} // namespace algorithm

}

#endif  // STRING_TRIM_DETAIL_HPP
