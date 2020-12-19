

#ifndef STRING_PREDICATE_HPP
#define STRING_PREDICATE_HPP

#include <iterator>
#include "as_literal.hpp"
#include "compare.hpp"
#include "find.hpp"
#include "detail/predicate.hpp"

/*! \file boost/algorithm/string/predicate.hpp
    Defines string-related predicates. 
    The predicates determine whether a substring is contained in the input string 
    under various conditions: a string starts with the substring, ends with the 
    substring, simply contains the substring or if both strings are equal.
    Additionaly the algorithm \c all() checks all elements of a container to satisfy a 
    condition.

    All predicates provide the strong exception guarantee.
*/

namespace string_algo {
    namespace algorithm {

//  starts_with predicate  -----------------------------------------------//

        //! 'Starts with' predicate
        /*!
            This predicate holds when the test string is a prefix of the Input.
            In other words, if the input starts with the test.
            When the optional predicate is specified, it is used for character-wise
            comparison.

            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

              \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
            inline bool starts_with( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            auto lit_input(::string_algo::as_literal(Input));
            auto lit_test(::string_algo::as_literal(Test));

           

            auto InputEnd=::std::end(lit_input);
            auto TestEnd=::std::end(lit_test);

            auto it=::std::begin(lit_input);
            auto pit=::std::begin(lit_test);
            for(;
                it!=InputEnd && pit!=TestEnd;
                ++it,++pit)
            {
                if( !(Comp(*it,*pit)) )
                    return false;
            }

            return pit==TestEnd;
        }

        //! 'Starts with' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool starts_with( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::string_algo::algorithm::starts_with(Input, Test, is_equal());
        }

        //! 'Starts with' predicate ( case insensitive )
        /*!
            This predicate holds when the test string is a prefix of the Input.
            In other words, if the input starts with the test.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool istarts_with( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::string_algo::algorithm::starts_with(Input, Test, is_iequal(Loc));
        }


//  ends_with predicate  -----------------------------------------------//

        //! 'Ends with' predicate
        /*!
            This predicate holds when the test string is a suffix of the Input.
            In other words, if the input ends with the test.
            When the optional predicate is specified, it is used for character-wise
            comparison.


            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

              \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool ends_with( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            auto lit_input(::string_algo::as_literal(Input));
            auto lit_test(::string_algo::as_literal(Test));

           
            typedef typename
                std::iterator_traits<typename decltype(lit_input)::iterator>::iterator_category category;

            return detail::
                ends_with_iter_select( 
                    ::std::begin(lit_input), 
                    ::std::end(lit_input), 
                    ::std::begin(lit_test), 
                    ::std::end(lit_test), 
                    Comp,
                    category());
        }


        //! 'Ends with' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool ends_with( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::string_algo::algorithm::ends_with(Input, Test, is_equal());
        }

        //! 'Ends with' predicate ( case insensitive )
        /*!
            This predicate holds when the test container is a suffix of the Input.
            In other words, if the input ends with the test.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool iends_with( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::string_algo::algorithm::ends_with(Input, Test, is_iequal(Loc));
        }

//  contains predicate  -----------------------------------------------//

        //! 'Contains' predicate
        /*!
            This predicate holds when the test container is contained in the Input.
            When the optional predicate is specified, it is used for character-wise
            comparison.

            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

               \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool contains( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            auto lit_input(::string_algo::as_literal(Input));
            auto lit_test(::string_algo::as_literal(Test));

            if (lit_test.empty())
            {
                // Empty range is contained always
                return true;
            }
            
            // Use the temporary variable to make VACPP happy
            auto span = ::string_algo::algorithm::first_finder(lit_test, Comp)(::std::begin(lit_input), ::std::end(lit_input));
            bool bResult=(!span.empty());
            return bResult;
        }

        //! 'Contains' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool contains( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::string_algo::algorithm::contains(Input, Test, is_equal());
        }

        //! 'Contains' predicate ( case insensitive )
        /*!
            This predicate holds when the test container is contained in the Input.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool icontains( 
            const Range1T& Input, 
            const Range2T& Test, 
            const std::locale& Loc=std::locale())
        {
            return ::string_algo::algorithm::contains(Input, Test, is_iequal(Loc));
        }

//  equals predicate  -----------------------------------------------//

        //! 'Equals' predicate
        /*!
            This predicate holds when the test container is equal to the
            input container i.e. all elements in both containers are same.
            When the optional predicate is specified, it is used for character-wise
            comparison.

            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

            \note This is a two-way version of \c std::equal algorithm

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool equals( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            auto lit_input(::string_algo::as_literal(Input));
            auto lit_test(::string_algo::as_literal(Test));

            
                
            auto InputEnd=::std::end(lit_input);
            auto TestEnd=::std::end(lit_test);

            auto it=::std::begin(lit_input);
            auto pit=::std::begin(lit_test);
            for(;
                it!=InputEnd && pit!=TestEnd;
                ++it,++pit)
            {
                if( !(Comp(*it,*pit)) )
                    return false;
            }

            return  (pit==TestEnd) && (it==InputEnd);
        }

        //! 'Equals' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool equals( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::string_algo::algorithm::equals(Input, Test, is_equal());
        }

        //! 'Equals' predicate ( case insensitive )
        /*!
            This predicate holds when the test container is equal to the
            input container i.e. all elements in both containers are same.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This is a two-way version of \c std::equal algorithm

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool iequals( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::string_algo::algorithm::equals(Input, Test, is_iequal(Loc));
        }

// lexicographical_compare predicate -----------------------------//

        //! Lexicographical compare predicate
        /*!
             This predicate is an overload of std::lexicographical_compare
             for range arguments

             It check whether the first argument is lexicographically less
             then the second one.

             If the optional predicate is specified, it is used for character-wise
             comparison

             \param Arg1 First argument 
             \param Arg2 Second argument
             \param Pred Comparison predicate
             \return The result of the test

             \note This function provides the strong exception-safety guarantee
         */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool lexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2,
            PredicateT Pred)
        {
            auto lit_arg1(::string_algo::as_literal(Arg1));
            auto lit_arg2(::string_algo::as_literal(Arg2));

            return std::lexicographical_compare(
                ::std::begin(lit_arg1),
                ::std::end(lit_arg1),
                ::std::begin(lit_arg2),
                ::std::end(lit_arg2),
                Pred);
        }

        //! Lexicographical compare predicate
        /*!
            \overload
         */
        template<typename Range1T, typename Range2T>
            inline bool lexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2)
        {
            return ::string_algo::algorithm::lexicographical_compare(Arg1, Arg2, is_less());
        }

        //! Lexicographical compare predicate (case-insensitive)
        /*!
            This predicate is an overload of std::lexicographical_compare
            for range arguments.
            It check whether the first argument is lexicographically less
            then the second one.
            Elements are compared case insensitively


             \param Arg1 First argument 
             \param Arg2 Second argument
             \param Loc A locale used for case insensitive comparison
             \return The result of the test

             \note This function provides the strong exception-safety guarantee
         */
        template<typename Range1T, typename Range2T>
        inline bool ilexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2,
            const std::locale& Loc=std::locale())
        {
            return ::string_algo::algorithm::lexicographical_compare(Arg1, Arg2, is_iless(Loc));
        }
        

//  all predicate  -----------------------------------------------//

        //! 'All' predicate
        /*!
            This predicate holds it all its elements satisfy a given 
            condition, represented by the predicate.
            
            \param Input An input sequence
            \param Pred A predicate
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename RangeT, typename PredicateT>
        inline bool all( 
            const RangeT& Input, 
            PredicateT Pred)
        {
            auto lit_input(::string_algo::as_literal(Input));

            typedef typename 
                decltype(lit_input)::iterator Iterator1T;

            Iterator1T InputEnd=::std::end(lit_input);
            for( Iterator1T It=::std::begin(lit_input); It!=InputEnd; ++It)
            {
                if (!Pred(*It))
                    return false;
            }
            
            return true;
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::starts_with;
    using algorithm::istarts_with;
    using algorithm::ends_with;
    using algorithm::iends_with;
    using algorithm::contains;
    using algorithm::icontains;
    using algorithm::equals;
    using algorithm::iequals;
    using algorithm::all;
    using algorithm::lexicographical_compare;
    using algorithm::ilexicographical_compare;

} // namespace string_algo 


#endif  // STRING_PREDICATE_HPP
