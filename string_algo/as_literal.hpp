
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
		struct  CHAR_PTR_TYPE {};
		struct  CONTAINER_TYPE {};
		struct  SPAN_TYPE {};

		template<typename T>
		struct RANG_TRAITS
		{
			using type = CONTAINER_TYPE;
		};

		template<>
		struct RANG_TRAITS<char>
		{
			using  type = CHAR_PTR_TYPE;
		};

		template<>
		struct RANG_TRAITS<const char>
		{
			using  type = CHAR_PTR_TYPE;
		};

#ifndef NO_CXX11_CHAR16_T
		template<>
		struct RANG_TRAITS<char16_t>
		{
			using  type = CHAR_PTR_TYPE;
		};

		template<>
		struct RANG_TRAITS<const char16_t>
		{
			using  type = CHAR_PTR_TYPE;
		};
#endif

#ifndef NO_CXX11_CHAR32_T
		template<>
		struct RANG_TRAITS<char32_t>
		{
			using  type = CHAR_PTR_TYPE;
		};

		template<>
		struct RANG_TRAITS<const char32_t>
		{
			using  type = CHAR_PTR_TYPE;
		};
#endif

#ifndef NO_CWCHAR
		template<>
		struct RANG_TRAITS<wchar_t>
		{
			using  type = CHAR_PTR_TYPE;
		};

		template<>
		struct RANG_TRAITS<const wchar_t>
		{
			using  type = CHAR_PTR_TYPE;
		};
#endif

		template<typename T>
		struct RANG_TRAITS<std::span<T>>
		{
			using  type = SPAN_TYPE;
		};

		template<typename T>
		struct RANG_TRAITS<const std::span<T>>
		{
			using  type = SPAN_TYPE;
		};


		inline std::size_t length(const char* s)
		{
			return strlen(s);
		}

#ifndef NO_CXX11_CHAR16_T
		inline std::size_t length(const char16_t* s)
		{
			return std::char_traits<char16_t>::length(s);
		}
#endif

#ifndef NO_CXX11_CHAR32_T
		inline std::size_t length(const char32_t* s)
		{
			return std::char_traits<char32_t>::length(s);
		}
#endif

#ifndef NO_CWCHAR
		inline std::size_t length(const wchar_t* s)
		{
			return wcslen(s);
		}
#endif


		template< class T >
		inline std::span<T>
			make_range(T* const r, CHAR_PTR_TYPE)
		{
			return std::span<T>(r, r + length(r));
		}

		template< class T >
		inline auto make_range(T& r, CONTAINER_TYPE)
		{
			if constexpr (std::is_const_v<T>)
			{
				return	std::span<std::add_const_t<typename T::value_type>>(r);
			}
			else
			{
				return	std::span<typename T::value_type>(r);
			}

		}


		template< class T >
		inline auto make_range(T& r, SPAN_TYPE)
		{
			return r;
		}
	}

	template< class Range >
	inline auto as_literal(Range& r)
	{
		return range_detail::make_range(r, typename range_detail::RANG_TRAITS<Range>::type());
	}

	template< class Range >
	inline  std::span<std::add_const_t<typename Range::value_type>>
		as_literal(const Range& r)
	{
		return range_detail::make_range<const Range>(r, typename range_detail::RANG_TRAITS<Range>::type());
	}

	template< class Char, std::size_t sz >
	inline std::span<Char> as_literal(Char(&arr)[sz])
	{
		return range_detail::make_range(arr, typename range_detail::RANG_TRAITS<std::decay_t<Char>>::type());
	}

	template< class Char, std::size_t sz >
	inline std::span<const Char> as_literal(const Char(&arr)[sz])
	{
		return range_detail::make_range(arr, typename range_detail::RANG_TRAITS<std::decay_t<Char>>::type());
	}
}

#endif
