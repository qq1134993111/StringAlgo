

#ifndef STRING_TRIM_HPP
#define STRING_TRIM_HPP

#include <locale>
#include "as_literal.hpp"
#include "detail/trim.hpp"
#include "classification.hpp"


/*! \file
	Defines trim algorithms.
	Trim algorithms are used to remove trailing and leading spaces from a
	sequence (string). Space is recognized using given locales.

	Parametric (\c _if) variants use a predicate (functor) to select which characters
	are to be trimmed..
	Functions take a selection predicate as a parameter, which is used to determine
	whether a character is a space. Common predicates are provided in classification.hpp header.

*/
namespace string_algo
{
	namespace algorithm
	{

		//  left trim  -----------------------------------------------//


		//! Left trim - parametric
		/*!
			Remove all leading spaces from the input.
			The supplied predicate is used to determine which characters are considered spaces.
			The result is a trimmed copy of the input. It is returned as a sequence
			or copied to the output iterator

			\param Output An output iterator to which the result will be copied
			\param Input An input range
			\param IsSpace A unary predicate identifying spaces
			\return
				An output iterator pointing just after the last inserted character or
				a copy of the input

			   \note The second variant of this function provides the strong exception-safety guarantee
		*/
		template<typename OutputIteratorT, typename RangeT, typename PredicateT>
		inline OutputIteratorT trim_left_copy_if(
			OutputIteratorT Output,
			const RangeT& Input,
			PredicateT IsSpace)
		{
			auto lit_range(string_algo::as_literal(Input));

			std::copy(
				::string_algo::algorithm::detail::trim_begin(
					::std::begin(lit_range),
					::std::end(lit_range),
					IsSpace),
				::std::end(lit_range),
				Output);

			return Output;
		}

		//! Left trim - parametric
		/*!
			\overload
		*/
		template<typename SequenceT, typename PredicateT>
		inline SequenceT trim_left_copy_if(const SequenceT& Input, PredicateT IsSpace)
		{
			return SequenceT(
				algorithm::detail::trim_begin(
					begin(Input),
					end(Input),
					IsSpace),
				end(Input));
		}

		//! Left trim - parametric
		/*!
			Remove all leading spaces from the input.
			The result is a trimmed copy of the input.

			\param Input An input sequence
			\param Loc a locale used for 'space' classification
			\return A trimmed copy of the input

			\note This function provides the strong exception-safety guarantee
		*/
		template<typename SequenceT>
		inline SequenceT trim_left_copy(const SequenceT& Input, const std::locale& Loc = std::locale())
		{
			return
				algorithm::trim_left_copy_if(
					Input,
					is_space(Loc));
		}

		//! Left trim
		/*!
			Remove all leading spaces from the input. The supplied predicate is
			used to determine which characters are considered spaces.
			The input sequence is modified in-place.

			\param Input An input sequence
			\param IsSpace A unary predicate identifying spaces
		*/
		template<typename SequenceT, typename PredicateT>
		inline void trim_left_if(SequenceT& Input, PredicateT IsSpace)
		{
			Input.erase(
				begin(Input),
				algorithm::detail::trim_begin(
					begin(Input),
					end(Input),
					IsSpace));
		}

		//! Left trim
		/*!
			Remove all leading spaces from the input.
			The Input sequence is modified in-place.

			\param Input An input sequence
			\param Loc A locale used for 'space' classification
		*/
		template<typename SequenceT>
		inline void trim_left(SequenceT& Input, const std::locale& Loc = std::locale())
		{
			algorithm::trim_left_if(
				Input,
				is_space(Loc));
		}

		//  right trim  -----------------------------------------------//

		//! Right trim - parametric
		/*!
			Remove all trailing spaces from the input.
			The supplied predicate is used to determine which characters are considered spaces.
			The result is a trimmed copy of the input. It is returned as a sequence
			or copied to the output iterator

			\param Output An output iterator to which the result will be copied
			\param Input An input range
			\param IsSpace A unary predicate identifying spaces
			\return
				An output iterator pointing just after the last inserted character or
				a copy of the input

			 \note The second variant of this function provides the strong exception-safety guarantee
		*/
		template<typename OutputIteratorT, typename RangeT, typename PredicateT>
		inline OutputIteratorT trim_right_copy_if(
			OutputIteratorT Output,
			const RangeT& Input,
			PredicateT IsSpace)
		{
			auto lit_range(::string_algo::as_literal(Input));

			std::copy(
				::std::begin(lit_range),
				::string_algo::algorithm::detail::trim_end(
					::std::begin(lit_range),
					::std::end(lit_range),
					IsSpace),
				Output);

			return Output;
		}

		//! Right trim - parametric
		/*!
			\overload
		 */
		template<typename SequenceT, typename PredicateT>
		inline SequenceT trim_right_copy_if(const SequenceT& Input, PredicateT IsSpace)
		{
			return SequenceT(
				std::begin(Input),
				algorithm::detail::trim_end(
					std::begin(Input),
					std::end(Input),
					IsSpace)
			);
		}

		//! Right trim
		/*!
			Remove all trailing spaces from the input.
			The result is a trimmed copy of the input

			\param Input An input sequence
			\param Loc A locale used for 'space' classification
			\return A trimmed copy of the input

			\note This function provides the strong exception-safety guarantee
		*/
		template<typename SequenceT>
		inline SequenceT trim_right_copy(const SequenceT& Input, const std::locale& Loc = std::locale())
		{
			return
				algorithm::trim_right_copy_if(
					Input,
					is_space(Loc));
		}


		//! Right trim - parametric
		/*!
			Remove all trailing spaces from the input.
			The supplied predicate is used to determine which characters are considered spaces.
			The input sequence is modified in-place.

			\param Input An input sequence
			\param IsSpace A unary predicate identifying spaces
		*/
		template<typename SequenceT, typename PredicateT>
		inline void trim_right_if(SequenceT& Input, PredicateT IsSpace)
		{
			Input.erase(
				algorithm::detail::trim_end(
					std::begin(Input),
					std::end(Input),
					IsSpace),
				std::end(Input)
			);
		}


		//! Right trim
		/*!
			Remove all trailing spaces from the input.
			The input sequence is modified in-place.

			\param Input An input sequence
			\param Loc A locale used for 'space' classification
		*/
		template<typename SequenceT>
		inline void trim_right(SequenceT& Input, const std::locale& Loc = std::locale())
		{
			algorithm::trim_right_if(
				Input,
				is_space(Loc));
		}

		//  both side trim  -----------------------------------------------//

		//! Trim - parametric
		/*!
			Remove all trailing and leading spaces from the input.
			The supplied predicate is used to determine which characters are considered spaces.
			The result is a trimmed copy of the input. It is returned as a sequence
			or copied to the output iterator

			\param Output An output iterator to which the result will be copied
			\param Input An input range
			\param IsSpace A unary predicate identifying spaces
			\return
				An output iterator pointing just after the last inserted character or
				a copy of the input

			 \note The second variant of this function provides the strong exception-safety guarantee
		*/
		template<typename OutputIteratorT, typename RangeT, typename PredicateT>
		inline OutputIteratorT trim_copy_if(
			OutputIteratorT Output,
			const RangeT& Input,
			PredicateT IsSpace)
		{
			auto lit_range(::string_algo::as_literal(Input));

			auto TrimEnd =
				::string_algo::algorithm::detail::trim_end(
					::std::begin(lit_range),
					::std::end(lit_range),
					IsSpace);

			std::copy(
				detail::trim_begin(
					::std::begin(lit_range), TrimEnd, IsSpace),
				TrimEnd,
				Output
			);

			return Output;
		}

		//! Trim - parametric
		/*!
			\overload
		 */
		template<typename SequenceT, typename PredicateT>
		inline SequenceT trim_copy_if(const SequenceT& Input, PredicateT IsSpace)
		{
			auto TrimEnd =
				algorithm::detail::trim_end(
					std::begin(Input),
					std::end(Input),
					IsSpace);

			return SequenceT(
				detail::trim_begin(
					std::begin(Input),
					TrimEnd,
					IsSpace),
				TrimEnd
			);
		}

		//! Trim
		/*!
			Remove all leading and trailing spaces from the input.
			The result is a trimmed copy of the input

			\param Input An input sequence
			\param Loc A locale used for 'space' classification
			\return A trimmed copy of the input

			\note This function provides the strong exception-safety guarantee
		*/
		template<typename SequenceT>
		inline SequenceT trim_copy(const SequenceT& Input, const std::locale& Loc = std::locale())
		{
			return
				algorithm::trim_copy_if(
					Input,
					is_space(Loc));
		}

		//! Trim
		/*!
			Remove all leading and trailing spaces from the input.
			The supplied predicate is used to determine which characters are considered spaces.
			The input sequence is modified in-place.

			\param Input An input sequence
			\param IsSpace A unary predicate identifying spaces
		*/
		template<typename SequenceT, typename PredicateT>
		inline void trim_if(SequenceT& Input, PredicateT IsSpace)
		{
			algorithm::trim_right_if(Input, IsSpace);
			algorithm::trim_left_if(Input, IsSpace);
		}

		//! Trim
		/*!
			Remove all leading and trailing spaces from the input.
			The input sequence is modified in-place.

			\param Input An input sequence
			\param Loc A locale used for 'space' classification
		*/
		template<typename SequenceT>
		inline void trim(SequenceT& Input, const std::locale& Loc = std::locale())
		{
			algorithm::trim_if(
				Input,
				is_space(Loc));
		}

	} // namespace algorithm 


	using algorithm::trim_left;
	using algorithm::trim_left_if;
	using algorithm::trim_left_copy;
	using algorithm::trim_left_copy_if;
	using algorithm::trim_right;
	using algorithm::trim_right_if;
	using algorithm::trim_right_copy;
	using algorithm::trim_right_copy_if;
	using algorithm::trim;
	using algorithm::trim_if;
	using algorithm::trim_copy;
	using algorithm::trim_copy_if;

}
#endif  // STRING_TRIM_HPP
