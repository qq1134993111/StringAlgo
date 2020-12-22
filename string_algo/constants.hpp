
#ifndef STRING_CONSTANTS_HPP
#define STRING_CONSTANTS_HPP

namespace string_algo {
	namespace algorithm {

		//! Token compression mode 
		/*!
			Specifies token compression mode for the token_finder.
		*/
		enum token_compress_mode_type
		{
			token_compress_on,    //!< Compress adjacent tokens
			token_compress_off  //!< Do not compress adjacent tokens
		};

	} // namespace algorithm

	// pull the names to the boost namespace
	using algorithm::token_compress_on;
	using algorithm::token_compress_off;

} // namespace string_algo 

#endif  // STRING_CONSTANTS_HPP

