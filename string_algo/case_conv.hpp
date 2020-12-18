

#ifndef STRING_CASE_CONV_HPP
#define STRING_CASE_CONV_HPP

#include <algorithm>
#include <locale>

#include "detail/case_conv.hpp"

/*! \file
	Defines sequence case-conversion algorithms.
	Algorithms convert each element in the input sequence to the
	desired case using provided locales.
*/
namespace string_algo
{
	namespace algorithm
	{

		//  to_lower  -----------------------------------------------//

		//! Convert to lower case
		/*!
			Each element of the input sequence is converted to lower
			case. The result is a copy of the input converted to lower case.
			It is returned as a sequence or copied to the output iterator.

			\param Output An output iterator to which the result will be copied
			\param Input An input range
			\param Loc A locale used for conversion
			\return
				An output iterator pointing just after the last inserted character or
				a copy of the input

			\note The second variant of this function provides the strong exception-safety guarantee

		*/
		template<typename OutputIteratorT, typename RangeT>
		inline OutputIteratorT
			to_lower_copy(
				OutputIteratorT Output,
				const RangeT& Input,
				const std::locale& Loc = std::locale())
		{
			return algorithm::detail::transform_range_copy(
				Output,
				Input,
				algorithm::detail::to_lowerF<RangeT>(Loc));
		}

		//! Convert to lower case
		/*!
			\overload
		*/
		template<typename SequenceT>
		inline SequenceT to_lower_copy(
			const SequenceT& Input,
			const std::locale& Loc = std::locale())
		{
			return  algorithm::detail::transform_range_copy<SequenceT>(
				Input,
				algorithm::detail::to_lowerF<typename SequenceT::value_type>(Loc));
		}

		//! Convert to lower case
		/*!
			Each element of the input sequence is converted to lower
			case. The input sequence is modified in-place.

			\param Input A range
			\param Loc a locale used for conversion
		*/
		template<typename WritableRangeT>
		inline void to_lower(
			WritableRangeT& Input,
			const std::locale& Loc = std::locale())
		{
			algorithm::detail::transform_range(
				Input,
				algorithm::detail::to_lowerF<typename WritableRangeT::value_type>(Loc));
		}

		//  to_upper  -----------------------------------------------//

		//! Convert to upper case
		/*!
			Each element of the input sequence is converted to upper
			case. The result is a copy of the input converted to upper case.
			It is returned as a sequence or copied to the output iterator

			\param Output An output iterator to which the result will be copied
			\param Input An input range
			\param Loc A locale used for conversion
			\return
				An output iterator pointing just after the last inserted character or
				a copy of the input

			\note The second variant of this function provides the strong exception-safety guarantee
		*/
		template<typename OutputIteratorT, typename RangeT>
		inline OutputIteratorT
			to_upper_copy(
				OutputIteratorT Output,
				const RangeT& Input,
				const std::locale& Loc = std::locale())
		{
			return  algorithm::detail::transform_range_copy(
				Output,
				Input,
				algorithm::detail::to_upperF<typename RangeT::value_type>(Loc));
		}

		//! Convert to upper case
		/*!
			\overload
		*/
		template<typename SequenceT>
		inline SequenceT to_upper_copy(
			const SequenceT& Input,
			const std::locale& Loc = std::locale())
		{
			return algorithm::detail::transform_range_copy<SequenceT>(
				Input,
				algorithm::detail::to_upperF<typename SequenceT::value_type>(Loc));
		}

		//! Convert to upper case
		/*!
			Each element of the input sequence is converted to upper
			case. The input sequence is modified in-place.

			\param Input An input range
			\param Loc a locale used for conversion
		*/
		template<typename WritableRangeT>
		inline void to_upper(
			WritableRangeT& Input,
			const std::locale& Loc = std::locale())
		{
			::algorithm::detail::transform_range(
				Input,
				algorithm::detail::to_upperF<typename WritableRangeT::value_type>(Loc));
		}

	} // namespace algorithm


	using algorithm::to_lower;
	using algorithm::to_lower_copy;
	using algorithm::to_upper;
	using algorithm::to_upper_copy;

}

#endif  // STRING_CASE_CONV_HPP
