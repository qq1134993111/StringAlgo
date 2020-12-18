

#ifndef STRING_CASE_CONV_DETAIL_HPP
#define STRING_CASE_CONV_DETAIL_HPP

#include <locale>
#include <functional>
#include <type_traits>

namespace string_algo
{
	namespace algorithm
	{
		namespace detail
		{

			//  case conversion functors -----------------------------------------------//


	//#pragma warning(push)
	//#pragma warning(disable:4512) //assignment operator could not be generated


			// a tolower functor
			template<typename CharT>
			struct to_lowerF
			{
				typedef CharT argument_type;
				typedef CharT result_type;
				// Constructor
				to_lowerF(const std::locale& Loc) : m_Loc(&Loc) {}

				// Operation
				CharT operator ()(CharT Ch) const
				{
#if defined(BORLANDC) && (BORLANDC >= 0x560) && (BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
					return std::tolower(static_cast<typename boost::make_unsigned <CharT>::type> (Ch));
#else
					return std::tolower<CharT>(Ch, *m_Loc);
#endif
				}
			private:
				const std::locale* m_Loc;
			};

			// a toupper functor
			template<typename CharT>
			struct to_upperF
			{
				typedef CharT argument_type;
				typedef CharT result_type;
				// Constructor
				to_upperF(const std::locale& Loc) : m_Loc(&Loc) {}

				// Operation
				CharT operator ()(CharT Ch) const
				{
#if defined(BORLANDC) && (BORLANDC >= 0x560) && (BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
					return std::toupper(static_cast<typename boost::make_unsigned <CharT>::type> (Ch));
#else
					return std::toupper<CharT>(Ch, *m_Loc);
#endif
				}
			private:
				const std::locale* m_Loc;
			};


			//#pragma warning(pop)


			// algorithm implementation -------------------------------------------------------------------------

			// Transform a range
			template<typename OutputIteratorT, typename RangeT, typename FunctorT>
			OutputIteratorT transform_range_copy(
				OutputIteratorT Output,
				const RangeT& Input,
				FunctorT Functor)
			{
				return std::transform(
					std::begin(Input),
					std::end(Input),
					Output,
					Functor);
			}

			// Transform a range (in-place)
			template<typename RangeT, typename FunctorT>
			void transform_range(
				const RangeT& Input,
				FunctorT Functor)
			{
				std::transform(
					std::begin(Input),
					std::end(Input),
					std::begin(const_cast<RangeT&>(Input)),
					Functor);
			}

			template<typename SequenceT, typename RangeT, typename FunctorT>
			inline SequenceT transform_range_copy(
				const RangeT& Input,
				FunctorT Functor)
			{
				/*	return SequenceT(
						::boost::make_transform_iterator(
							::boost::begin(Input),
							Functor),
						::boost::make_transform_iterator(
							::boost::end(Input),
							Functor));*/

				SequenceT s;
				transform_range_copy(std::back_inserter(s), Input, Functor);
				return s;
			}

		} // namespace detail
	} // namespace algorithm

}

#endif  // STRING_CASE_CONV_DETAIL_HPP
