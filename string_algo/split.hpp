
#ifndef STRING_SPLIT_HPP
#define STRING_SPLIT_HPP


#include "iter_find.hpp"
#include "finder.hpp"
#include "compare.hpp"

/*! \file
    Defines basic split algorithms. 
    Split algorithms can be used to divide a string
    into several parts according to given criteria.
    
    Each part is copied and added as a new element to the
    output container.
    Thus the result container must be able to hold copies
    of the matches (in a compatible structure like std::string) or
    a reference to it (e.g. using the iterator range class).
    Examples of such a container are \c std::vector<std::string>
    or \c std::list<boost::iterator_range<std::string::iterator>>
*/

namespace string_algo {
    namespace algorithm {

//  find_all  ------------------------------------------------------------//

        //! Find all algorithm
        /*!
            This algorithm finds all occurrences of the search string
            in the input.
            
            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& find_all(
            SequenceSequenceT& Result,
            Range1T&& Input,
            const Range2T& Search)
        {
            return ::string_algo::algorithm::iter_find(
                Result,
                string_algo::as_literal(Input),
                ::string_algo::algorithm::first_finder(string_algo::as_literal(Search)) );        
        }

        //! Find all algorithm ( case insensitive ) 
        /*!
            This algorithm finds all occurrences of the search string
            in the input. 
            Each part is copied and added as a new element to the
            output container. Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            Searching is case insensitive.

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& ifind_all(
            SequenceSequenceT& Result,
            Range1T&& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::string_algo::algorithm::iter_find(
                Result,
                string_algo::as_literal(Input),
                ::string_algo::algorithm::first_finder(string_algo::as_literal(Search), is_iequal(Loc) ) );        
        }


//  tokenize  -------------------------------------------------------------//

        //! Split algorithm
        /*! 
            Tokenize expression. This function is equivalent to C strtok. Input
            sequence is split into tokens, separated by separators. Separators 
            are given by means of the predicate.

            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>
    
            \param Result A container that can hold copies of references to the substrings          
            \param Input A container which will be searched.
            \param Pred A predicate to identify separators. This predicate is 
                supposed to return true if a given element is a separator.
            \param eCompress If eCompress argument is set to token_compress_on, adjacent 
                separators are merged together. Otherwise, every two separators
                delimit a token.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename RangeT, typename PredicateT >
        inline SequenceSequenceT& split(
            SequenceSequenceT& Result,
            RangeT&& Input,
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off )
        {
            return ::string_algo::algorithm::iter_split(
                Result,
                as_literal(Input),
                ::string_algo::algorithm::token_finder( Pred, eCompress ) );         
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_all;
    using algorithm::ifind_all;
    using algorithm::split;    

} // namespace string_algo


#endif  //STRING_SPLIT_HPP

