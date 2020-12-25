

#ifndef STRING_FIND_FORMAT_ALL_DETAIL_HPP
#define STRING_FIND_FORMAT_ALL_DETAIL_HPP

#include "./find_format_store.hpp"
#include "./replace_storage.hpp"

namespace string_algo {
    namespace algorithm {
        namespace detail {

// find_format_all_copy (iterator variant) implementation ---------------------------//

           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_all_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef typename InputT::const_iterator input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::std::begin(Input);

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    Output = std::copy( LastMatch, M.begin(), Output );
                    // Copy formatted result
                    Output = std::copy( ::std::begin(M.format_result()), ::std::end(M.format_result()), Output );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::std::end(Input) );
                }

                // Copy the rest of the sequence
                Output = std::copy( LastMatch, ::std::end(Input), Output );

                return Output;
            }

            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_all_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::string_algo::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::string_algo::algorithm::detail::find_format_all_copy_impl2( 
                        Output,
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::std::begin(Input), ::std::end(Input), Output );
                }
            }

 // find_format_all_copy implementation ----------------------------------------------//

           template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_all_copy_impl2(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef typename InputT::const_iterator input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::std::begin(Input);

                // Output temporary
                InputT Output;

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    string_algo::algorithm::detail::insert( Output, ::std::end(Output), LastMatch, M.begin() );
                    // Copy formatted result
                    string_algo::algorithm::detail::insert( Output, ::std::end(Output), M.format_result() );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::std::end(Input) );
                }

                // Copy the rest of the sequence
                ::string_algo::algorithm::detail::insert( Output, ::std::end(Output), LastMatch, ::std::end(Input) );

                return Output;
            }

            template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_all_copy_impl(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::string_algo::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::string_algo::algorithm::detail::find_format_all_copy_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

 // find_format_all implementation ------------------------------------------------//
        
            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_all_impl2( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult,
                FormatResultT FormatResult)
            {
                typedef  typename std::span<std::remove_pointer_t<typename InputT::pointer>>::iterator input_iterator_type; 
                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );
          
                // Instantiate replacement storage
                std::deque<std::remove_pointer_t<typename InputT::pointer>> Storage;

                auto lit_input = as_literal(Input);
                // Initialize replacement iterators
                input_iterator_type InsertIt=::std::begin(lit_input);
                input_iterator_type SearchIt=::std::begin(lit_input);
                
                while( !M.empty() )
                {
                    // process the segment
                    InsertIt= ::string_algo::algorithm::detail::process_segment(
                        Storage,
                        Input,
                        InsertIt,
                        SearchIt,
                        M.begin());
                    
                    // Adjust search iterator
                    SearchIt=M.end();

                    // Copy formatted replace to the storage
                    ::string_algo::algorithm::detail::copy_to_storage( Storage, M.format_result() );

                    // Find range for a next match
                    M=Finder( SearchIt, ::std::end(as_literal(Input)) );
                }

                // process the last segment
                InsertIt=::string_algo::algorithm::detail::process_segment( 
                    Storage,
                    Input,
                    InsertIt,
                    SearchIt,
                    ::std::end(as_literal(Input)) );
                
                if ( Storage.empty() )
                {
                    // Truncate input
                    auto n= std::distance(std::begin(as_literal(Input)), InsertIt);
                    auto b = Input.begin();
                    std::advance(b, n);
                    ::string_algo::algorithm::detail::erase( Input, b, ::std::end(Input) );
                
                }
                else
                {
                    // Copy remaining data to the end of input
                    ::string_algo::algorithm::detail::insert( Input, ::std::end(Input), Storage.begin(), Storage.end() );
                 
                }
            }

            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_all_impl( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult)
            {
               
                if( ::string_algo::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::string_algo::algorithm::detail::find_format_all_impl2(
                     Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace string_algo

#endif  // STRING_FIND_FORMAT_ALL_DETAIL_HPP
