
#ifndef STRING_FIND_FORMAT_STORE_DETAIL_HPP
#define STRING_FIND_FORMAT_STORE_DETAIL_HPP
#include<span>
#include<type_traits>


namespace string_algo {
    namespace algorithm {
        namespace detail {

//  temporary format and find result storage --------------------------------//


            template< 
                typename ForwardIteratorT,
                typename FormatterT,
                typename FormatResultT >
            class find_format_store : 
                public std::span<std::remove_pointer_t<typename  ForwardIteratorT::pointer>>
            {
            public:
                // typedefs
                typedef std::span<std::remove_pointer_t<typename  ForwardIteratorT::pointer>> base_type;
                typedef FormatterT  formatter_type;
                typedef FormatResultT format_result_type;
                
            public:
                // Construction
                find_format_store( 
                        const base_type& FindResult,
                        const format_result_type& FormatResult,
                        const formatter_type& Formatter ) :
                    base_type(FindResult),
                    m_FormatResult(FormatResult),
                    m_Formatter(Formatter) {}

                // Assignment
                template< typename FindResultT >
                find_format_store& operator=( FindResultT FindResult )
                {
                    std::span<std::remove_pointer_t<typename  ForwardIteratorT::pointer>>::operator=(FindResult);
                    if( !this->empty() ) {
                        m_FormatResult=m_Formatter(FindResult);
                    }
                    
                    return *this;
                }

                // Retrieve format result
                const format_result_type& format_result()
                {   
                    return m_FormatResult;
                }

            private:
                format_result_type m_FormatResult;
                const formatter_type& m_Formatter;
            };

            template<typename InputT, typename FindResultT>
            bool check_find_result(InputT&, FindResultT& FindResult)
            {
                typedef typename InputT::iterator input_iterator_type;
                std::span<std::remove_pointer_t<typename  input_iterator_type::pointer>> ResultRange(FindResult);
                return !ResultRange.empty();
            }

        } // namespace detail
    } // namespace algorithm
} // namespace string_algo

#endif  // STRING_FIND_FORMAT_STORE_DETAIL_HPP
