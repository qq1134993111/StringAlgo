

#ifndef STRING_FIND_ITERATOR_DETAIL_HPP
#define STRING_FIND_ITERATOR_DETAIL_HPP

#include<span>
#include<functional>



namespace string_algo {
    namespace algorithm { 
        namespace detail {

//  find_iterator base -----------------------------------------------//

            // Find iterator base
            template<typename IteratorT>
            class find_iterator_base
            {
            protected:
                // typedefs
                typedef IteratorT input_iterator_type;
                typedef std::span<std::remove_pointer_t<typename IteratorT::pointer>> match_type;
                typedef std::function<match_type (input_iterator_type,input_iterator_type) > finder_type;
                
            protected:
            // Protected construction/destruction

                // Default constructor
                find_iterator_base() {}
                // Copy construction
                find_iterator_base( const find_iterator_base& Other ) :
                    m_Finder(Other.m_Finder) {}
                
                // Constructor
                template<typename FinderT>
                find_iterator_base( FinderT Finder, int ) :
                    m_Finder(Finder) {}

                // Destructor
                ~find_iterator_base() {}

                // Find operation
                match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    if (m_Finder)
                    {
                        return m_Finder(Begin,End);
                    }
                    else
                    {
                        return match_type(End,End);
                    }
                }

                // Check
                bool is_null() const
                {
                    return m_Finder==nullptr;
                }

            private:
                // Finder
                finder_type m_Finder;
            };

       } // namespace detail
    } // namespace algorithm
} // namespace string_algo


#endif  //STRING_FIND_ITERATOR_DETAIL_HPP
