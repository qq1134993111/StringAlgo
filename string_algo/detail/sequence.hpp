

#ifndef STRING_DETAIL_SEQUENCE_HPP
#define STRING_DETAIL_SEQUENCE_HPP

#include "../sequence_traits.hpp"

namespace string_algo {
	namespace algorithm {
		namespace detail {

			//  insert helpers  -------------------------------------------------//

			template< typename InputT, typename ForwardIteratorT >
			inline void insert(
				InputT& Input,
				typename InputT::iterator At,
				ForwardIteratorT Begin,
				ForwardIteratorT End)
			{
				Input.insert(At, Begin, End);
			}

			template< typename InputT, typename InsertT >
			inline void insert(
				InputT& Input,
				typename InputT::iterator At,
				const InsertT& Insert)
			{
				::string_algo::algorithm::detail::insert(Input, At, ::std::begin(Insert), ::std::end(Insert));
			}

			//  erase helper  ---------------------------------------------------//

						// Erase a range in the sequence
						/*
							Returns the iterator pointing just after the erase subrange
						*/
			template< typename InputT >
			inline typename InputT::iterator erase(
				InputT& Input,
				typename InputT::iterator From,
				typename InputT::iterator To)
			{
				return Input.erase(From, To);
			}

			//  replace helper implementation  ----------------------------------//

						// Optimized version of replace for generic sequence containers
						// Assumption: insert and erase are expensive
			template< bool HasConstTimeOperations >
			struct replace_const_time_helper
			{
				template< typename InputT, typename ForwardIteratorT >
				void operator()(
					InputT& Input,
					typename InputT::iterator From,
					typename InputT::iterator To,
					ForwardIteratorT Begin,
					ForwardIteratorT End)
				{
					// Copy data to the container ( as much as possible )
					ForwardIteratorT InsertIt = Begin;
					typename InputT::iterator InputIt = From;
					for (; InsertIt != End && InputIt != To; InsertIt++, InputIt++)
					{
						*InputIt = *InsertIt;
					}

					if (InsertIt != End)
					{
						// Replace sequence is longer, insert it
						Input.insert(InputIt, InsertIt, End);
					}
					else
					{
						if (InputIt != To)
						{
							// Replace sequence is shorter, erase the rest
							Input.erase(InputIt, To);
						}
					}
				}
			};

			template<>
			struct replace_const_time_helper< true >
			{
				// Const-time erase and insert methods -> use them
				template< typename InputT, typename ForwardIteratorT >
				void operator()(
					InputT& Input,
					typename InputT::iterator From,
					typename InputT::iterator To,
					ForwardIteratorT Begin,
					ForwardIteratorT End)
				{
					typename InputT::iterator At = Input.erase(From, To);
					if (Begin != End)
					{
						if (!Input.empty())
						{
							Input.insert(At, Begin, End);
						}
						else
						{
							Input.insert(Input.begin(), Begin, End);
						}
					}
				}
			};

			// No native replace method
			template< bool HasNative >
			struct replace_native_helper
			{
				template< typename InputT, typename ForwardIteratorT >
				void operator()(
					InputT& Input,
					typename InputT::iterator From,
					typename InputT::iterator To,
					ForwardIteratorT Begin,
					ForwardIteratorT End)
				{
					replace_const_time_helper<
						std::conjunction<
						has_const_time_insert<InputT>,
						has_const_time_erase<InputT> >::value >()(
							Input, From, To, Begin, End);
				}
			};

			// Container has native replace method
			template<>
			struct replace_native_helper< true >
			{
				template< typename InputT, typename ForwardIteratorT >
				void operator()(
					InputT& Input,
					typename InputT::iterator From,
					typename InputT::iterator To,
					ForwardIteratorT Begin,
					ForwardIteratorT End)
				{
					Input.replace(From, To, Begin, End);
				}
			};

			//  replace helper  -------------------------------------------------//

			template< typename InputT, typename ForwardIteratorT >
			inline void replace(
				InputT& Input,
				typename InputT::iterator From,
				typename InputT::iterator To,
				ForwardIteratorT Begin,
				ForwardIteratorT End)
			{
				replace_native_helper< has_native_replace<InputT>::value >()(
					Input, From, To, Begin, End);
			}

			template< typename InputT, typename InsertT >
			inline void replace(
				InputT& Input,
				typename InputT::iterator From,
				typename InputT::iterator To,
				const InsertT& Insert)
			{
				if (From != To)
				{
					::string_algo::algorithm::detail::replace(Input, From, To, ::std::begin(Insert), ::std::end(Insert));
				}
				else
				{
					::string_algo::algorithm::detail::insert(Input, From, ::std::begin(Insert), ::std::end(Insert));
				}
			}

		} // namespace detail
	} // namespace algorithm
} // namespace string_algo


#endif  // STRING_DETAIL_SEQUENCE_HPP
