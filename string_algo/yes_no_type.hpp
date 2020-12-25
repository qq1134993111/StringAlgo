
#ifndef STRING_YES_NO_TYPE_DETAIL_HPP
#define STRING_YES_NO_TYPE_DETAIL_HPP

namespace string_algo {
	namespace algorithm {

		// taken from boost mailing-list
		// when yes_no_type will become officially
		// a part of boost distribution, this header
		// will be deprecated
		template<int I> struct size_descriptor
		{
			typedef char(&type)[I];
		};

		typedef size_descriptor<1>::type yes_type;
		typedef size_descriptor<2>::type no_type;

	} // namespace algorithm
} // namespace string_algo


#endif  // STRING_YES_NO_TYPE_DETAIL_HPP
