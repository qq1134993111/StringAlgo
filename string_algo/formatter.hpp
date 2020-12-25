
#ifndef STRING_FORMATTER_HPP
#define STRING_FORMATTER_HPP

#include "as_literal.hpp"
#include "detail/formatter.hpp"

/*! \file
    Defines Formatter generators. Formatter is a functor which formats
    a string according to given parameters. A Formatter works
    in conjunction with a Finder. A Finder can provide additional information
    for a specific Formatter. An example of such a cooperation is regex_finder
    and regex_formatter.

    Formatters are used as pluggable components for replace facilities. 
    This header contains generator functions for the Formatters provided in this library.
*/

namespace string_algo {
    namespace algorithm {

// generic formatters  ---------------------------------------------------------------//

        //! Constant formatter
        /*!
            Constructs a \c const_formatter. Const formatter always returns
            the same value, regardless of the parameter.

            \param Format A predefined value used as a result for formatting
            \return An instance of the \c const_formatter object.
        */
        template<typename RangeT>
        inline  auto
        const_formatter(const RangeT& Format)
        {
            return detail::const_formatF<
                std::span<
                   std::remove_pointer_t<typename decltype(std::begin(Format))::pointer > > >(::string_algo::as_literal(Format));
        }

        //! Identity formatter
        /*!
            Constructs an \c identity_formatter. Identity formatter always returns
            the parameter.

            \return An instance of the \c identity_formatter object.
        */
        template<typename RangeT>
        inline detail::identity_formatF<
            std::span<
            typename RangeT::const_iterator> >
        identity_formatter()
        {
            return detail::identity_formatF<
                std::span<
                    typename RangeT::const_iterator> >();
        }

        //! Empty formatter
        /*!
            Constructs an \c empty_formatter. Empty formatter always returns an empty
            sequence. 

            \param Input container used to select a correct value_type for the
                         resulting empty_container<>.
            \return An instance of the \c empty_formatter object.
        */
        template<typename RangeT>
        inline detail::empty_formatF< 
            typename RangeT::value_type>
        empty_formatter(const RangeT&)
        {
            return detail::empty_formatF<
                typename RangeT::value_type>();
        }

        //! Empty formatter
        /*!
            Constructs a \c dissect_formatter. Dissect formatter uses a specified finder
            to extract a portion of the formatted sequence. The first finder's match is returned 
            as a result

            \param Finder a finder used to select a portion of the formatted sequence
            \return An instance of the \c dissect_formatter object.
        */
        template<typename FinderT>
        inline detail::dissect_formatF< FinderT >
        dissect_formatter(const FinderT& Finder)
        {
            return detail::dissect_formatF<FinderT>(Finder);
        }


    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::const_formatter;
    using algorithm::identity_formatter;
    using algorithm::empty_formatter;
    using algorithm::dissect_formatter;

} // namespace string_algo


#endif  // FORMATTER_HPP
