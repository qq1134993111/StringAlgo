

#ifndef STRING_PREDICATE_FACADE_HPP
#define STRING_PREDICATE_FACADE_HPP


/*
 predicate_facade.hpp
 This file contains predicate_facade definition. This template class is used
 to identify classification predicates, so they can be combined using
 composition operators.
*/
namespace string_algo
{
	namespace algorithm
	{

		//  predicate facade ------------------------------------------------------//

		//! Predicate facade
		/*!
			This class allows to recognize classification
			predicates, so that they can be combined using
			composition operators.
			Every classification predicate must be derived from this class.
		*/
		template<typename Derived>
		struct predicate_facade {};

	} // namespace algorithm

}

#endif  // STRING_CLASSIFICATION_DETAIL_HPP
