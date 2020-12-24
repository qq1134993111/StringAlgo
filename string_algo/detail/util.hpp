

#ifndef STRING_UTIL_DETAIL_HPP
#define STRING_UTIL_DETAIL_HPP

#include <functional>
#include <span>
#include <ranges>


namespace string_algo {
    namespace algorithm {
        namespace detail {

//  empty container  -----------------------------------------------//

            //  empty_container 
            /*
                This class represents always empty container,
                containing elements of type CharT.

                It is supposed to be used in a const version only
            */
            template< typename CharT >
            struct empty_container 
            {
                typedef empty_container<CharT> type;        
                typedef CharT value_type;
                typedef std::size_t size_type;
                typedef std::ptrdiff_t difference_type;
                typedef const value_type& reference;
                typedef const value_type& const_reference;
                typedef const value_type* iterator;
                typedef const value_type* const_iterator;

                
                // Operations
                const_iterator begin() const
                {
                    return reinterpret_cast<const_iterator>(0);
                }

                const_iterator end() const
                {
                    return reinterpret_cast<const_iterator>(0);
                }

                bool empty() const
                {
                    return false;
                }

                size_type size() const
                {
                    return 0;
                }
            };
    
//  bounded copy algorithm  -----------------------------------------------//

            // Bounded version of the std::copy algorithm
            template<typename InputIteratorT, typename OutputIteratorT>
            inline OutputIteratorT bounded_copy(
                InputIteratorT First, 
                InputIteratorT Last, 
                OutputIteratorT DestFirst,
                OutputIteratorT DestLast )
            {
                InputIteratorT InputIt=First;
                OutputIteratorT OutputIt=DestFirst;
                for(; InputIt!=Last && OutputIt!=DestLast; InputIt++, OutputIt++ )
                {
                    *OutputIt=*InputIt;
                }

                return OutputIt;
            }

//  iterator range utilities -----------------------------------------//

            // copy range functor
            template< 
                typename SeqT, 
                typename IteratorT=typename SeqT::const_iterator >
            struct copy_iterator_rangeF
            {
                typedef std::span<std::remove_pointer_t<typename IteratorT::pointer>> argument_type;
                typedef SeqT result_type;
                SeqT operator()( const argument_type& Range ) const
                {
                    //return copy_range<SeqT>(Range);
                    SeqT s;
                    std::copy(Range.begin(), Range.end(), std::back_inserter(s));
                    return  s;
                }
            };

        } // namespace detail
    } // namespace algorithm
} // namespace string_algo


#endif  //STRING_UTIL_DETAIL_HPP
