
#ifndef RANGE_AS_LITERAL_HPP
#define RANGE_AS_LITERAL_HPP
#include <span>
#include <cstring>
#include <type_traits>

#if !defined(NO_CXX11_CHAR16_T) || !defined(NO_CXX11_CHAR32_T)
#include <string>  // for std::char_traits
#endif

#ifndef NO_CWCHAR
#include <cwchar>
#endif

namespace string_algo
{
    namespace range_detail
    {
        inline std::size_t length( const char* s )
        {
            return strlen( s );
        }

#ifndef NO_CXX11_CHAR16_T
        inline std::size_t length( const char16_t* s )
        {
            return std::char_traits<char16_t>::length( s );
        }
#endif

#ifndef NO_CXX11_CHAR32_T
        inline std::size_t length( const char32_t* s )
        {
            return std::char_traits<char32_t>::length( s );
        }
#endif

#ifndef NO_CWCHAR
        inline std::size_t length( const wchar_t* s )
        {
            return wcslen( s );
        }
#endif

        //
        // Remark: the compiler cannot choose between T* and T[sz]
        // overloads, so we must put the T* internal to the
        // unconstrained version.
        //

        inline bool is_char_ptr( char* )
        {
            return true;
        }

        inline bool is_char_ptr( const char* )
        {
            return true;
        }

#ifndef NO_CXX11_CHAR16_T
        inline bool is_char_ptr( char16_t* )
        {
            return true;
        }

        inline bool is_char_ptr( const char16_t* )
        {
            return true;
        }
#endif

#ifndef NO_CXX11_CHAR32_T
        inline bool is_char_ptr( char32_t* )
        {
            return true;
        }

        inline bool is_char_ptr( const char32_t* )
        {
            return true;
        }
#endif

#ifndef NO_CWCHAR
        inline bool is_char_ptr( wchar_t* )
        {
            return true;
        }

        inline bool is_char_ptr( const wchar_t* )
        {
            return true;
        }
#endif

        template< class T >
        inline long is_char_ptr( const T& /* r */ )
        {
            return 0L;
        }

        template< class T >
        inline std::span<T>
        make_range( T* const r, bool )
        {
            return std::span<T>( r, r + length(r) );
        }

        template< class T >
        inline std::span<typename T::value_type>
        make_range( T& r, long )
        {
            return std::span<typename  T::value_type>( r );
        }

    }

    template< class Range >
    inline std::span<typename Range::value_type>
    as_literal( Range& r )
    {
        return range_detail::make_range( r, range_detail::is_char_ptr(r) );
    }

    template< class Range >
    inline  std::span<typename std::add_const_t<Range>::value_type>
    as_literal( const Range& r )
    {
        return range_detail::make_range( r, range_detail::is_char_ptr(r) );
    }

    template< class Char, std::size_t sz >
    inline std::span<Char> as_literal( Char (&arr)[sz] )
    {
        return range_detail::make_range( arr, range_detail::is_char_ptr(arr) );
    }

    template< class Char, std::size_t sz >
    inline std::span<const Char> as_literal( const Char (&arr)[sz] )
    {
        return range_detail::make_range( arr, range_detail::is_char_ptr(arr) );
    }
}

#endif
