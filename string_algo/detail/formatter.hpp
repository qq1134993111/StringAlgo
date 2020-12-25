

#ifndef STRING_FORMATTER_DETAIL_HPP
#define STRING_FORMATTER_DETAIL_HPP


#include "./util.hpp"

//  generic replace functors -----------------------------------------------//

namespace string_algo {
    namespace algorithm {
        namespace detail {

//  const format functor ----------------------------------------------------//

            // constant format functor
            template<typename RangeT>
            struct const_formatF
            {
            private:
                typedef typename RangeT::iterator format_iterator;
                typedef std::span<std::remove_pointer_t<typename format_iterator::pointer>> result_type;
            
            public:
                // Construction
                const_formatF(const RangeT& Format) :
                    m_Format(::std::begin(Format), ::std::end(Format)) {}

                // Operation
//#if WORKAROUND(BORLANDC, TESTED_AT(0x564))
//                template<typename Range2T>
//                result_type& operator()(const Range2T&)
//                {
//                    return m_Format;
//                }
//#endif

                template<typename Range2T>
                const result_type& operator()(const Range2T&) const
                {
                    return m_Format;
                }

            private:
                result_type m_Format;
            };

//  identity format functor ----------------------------------------------------//

            // identity format functor
            template<typename RangeT>
            struct identity_formatF
            {
                // Operation
                template< typename Range2T >
                const RangeT& operator()(const Range2T& Replace) const
                {
                    return RangeT(::std::begin(Replace), ::std::end(Replace));
                }
            };

//  empty format functor ( used by erase ) ------------------------------------//
        
            // empty format functor
            template< typename CharT >
            struct empty_formatF
            {
                template< typename ReplaceT >
                empty_container<CharT> operator()(const ReplaceT&) const
                {
                    return empty_container<CharT>();
                }
            };

//  dissect format functor ----------------------------------------------------//

            // dissect format functor
            template<typename FinderT>
            struct dissect_formatF
            {
            public:
                // Construction
                dissect_formatF(FinderT Finder) :
                  m_Finder(Finder) {}

                  // Operation
                  template<typename RangeT>
                  inline std::span< 
                      typename RangeT::const_iterator>
                  operator()(const RangeT& Replace) const
                  {
                      return m_Finder(::std::begin(Replace), ::std::end(Replace));
                  }

            private:
                FinderT m_Finder;
            };


        } // namespace detail
    } // namespace algorithm
} // namespace string_algo

#endif  // STRING_FORMATTER_DETAIL_HPP
