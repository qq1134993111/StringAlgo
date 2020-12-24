

#ifndef STRING_FIND_ITERATOR_HPP
#define STRING_FIND_ITERATOR_HPP

#include "as_literal.hpp"

#include "detail/find_iterator.hpp"

/*! \file
    Defines find iterator classes. Find iterator repeatedly applies a Finder
    to the specified input string to search for matches. Dereferencing
    the iterator yields the current match or a range between the last and the current
    match depending on the iterator used.
*/

namespace string_algo {
    namespace algorithm { 

//  find_iterator -----------------------------------------------//

        //! find_iterator
        /*!    
            Find iterator encapsulates a Finder and allows
            for incremental searching in a string.
            Each increment moves the iterator to the next match.

            Find iterator is a readable forward traversal iterator.

            Dereferencing the iterator yields an iterator_range delimiting
            the current match.
        */
        template<typename IteratorT>
        class find_iterator : 
            private detail::find_iterator_base<IteratorT>
        {
        private:
        private:
        // typedefs

            typedef detail::find_iterator_base<IteratorT> base_type;
            typedef typename  
                base_type::input_iterator_type input_iterator_type;
            typedef typename  
                base_type::match_type match_type;

        public:
            //! Default constructor
            /*!
                Construct null iterator. All null iterators are equal.

                \post eof()==true
            */
            find_iterator() {}

            //! Copy constructor
            /*!
                Construct a copy of the find_iterator
            */
            find_iterator( const find_iterator& Other ) :
                base_type(Other),
                m_Match(Other.m_Match),
                m_End(Other.m_End) {}

            //! Constructor
            /*!
                Construct new find_iterator for a given finder
                and a range.
            */
            template<typename FinderT>
            find_iterator(
                    IteratorT Begin,
                    IteratorT End,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_Match(Begin,Begin),
                m_End(End)
            {
                increment();
            }

            //! Constructor
            /*!
                Construct new find_iterator for a given finder
                and a range.
            */
            template<typename FinderT, typename RangeT>
            find_iterator(
                    RangeT& Col,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0)
            {
                auto lit_col=string_algo::as_literal(Col);
            	
                m_Match=std::span(::std::begin(lit_col), ::std::begin(lit_col));
                m_End=::std::end(lit_col);

                increment();
            }

        private:
        // iterator operations

            // dereference
            const match_type& dereference() const
            {
                return m_Match;
            }

            // increment
            void increment()
            {
                m_Match=this->do_find(m_Match.end(),m_End);
            }

            // comparison
            bool equal( const find_iterator& Other ) const
            {
                bool bEof=eof();
                bool bOtherEof=Other.eof();

                return bEof || bOtherEof ? bEof==bOtherEof :
                    (
                        m_Match==Other.m_Match &&
                        m_End==Other.m_End 
                    );
            }

        public:
        // operations

            //! Eof check
            /*!
                Check the eof condition. Eof condition means that
                there is nothing more to be searched i.e. find_iterator
                is after the last match.
            */
            bool eof() const
            {
                return 
                    this->is_null() || 
                    ( 
                        m_Match.begin() == m_End &&
                        m_Match.end() == m_End
                    );
            }

        private:
        // Attributes
            match_type m_Match;
            input_iterator_type m_End;
        };

        //! find iterator construction helper
        /*!
         *    Construct a find iterator to iterate through the specified string
         */
        template<typename RangeT, typename FinderT>
        inline find_iterator< 
           std::remove_pointer_t<typename RangeT::pointer> >
        make_find_iterator(
            RangeT& Collection,
            FinderT Finder)
        {
            return find_iterator<std::remove_pointer_t<typename RangeT::pointer> >(
                Collection, Finder);
        }

//  split iterator -----------------------------------------------//

        //! split_iterator
        /*!    
            Split iterator encapsulates a Finder and allows
            for incremental searching in a string.
            Unlike the find iterator, split iterator iterates
            through gaps between matches.

            Find iterator is a readable forward traversal iterator.

            Dereferencing the iterator yields an iterator_range delimiting
            the current match.
        */
        template<typename IteratorT>
        class split_iterator : 
            private detail::find_iterator_base<IteratorT>
        {
        private:
         
        private:
        // typedefs

            typedef detail::find_iterator_base<IteratorT> base_type;
            typedef typename  
                base_type::input_iterator_type input_iterator_type;
            typedef typename  
                base_type::match_type match_type;

        public:
            //! Default constructor
            /*!
                Construct null iterator. All null iterators are equal.
    
                \post eof()==true
            */
            split_iterator() :
                m_Next(),
                m_End(),
                m_bEof(true)
            {}

            //! Copy constructor
            /*!
                Construct a copy of the split_iterator
            */
            split_iterator( const split_iterator& Other ) :
                base_type(Other),
                m_Match(Other.m_Match),
                m_Next(Other.m_Next),
                m_End(Other.m_End),
                m_bEof(Other.m_bEof)
            {}

            //! Constructor
            /*!
                Construct new split_iterator for a given finder
                and a range.
            */
            template<typename FinderT>
            split_iterator(
                    IteratorT Begin,
                    IteratorT End,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_Match(Begin,Begin),
                m_Next(Begin),
                m_End(End),
                m_bEof(false)
            {
                // force the correct behavior for empty sequences and yield at least one token
                if(Begin!=End)
                {
                    increment();
                }
            }
            //! Constructor
            /*!
                Construct new split_iterator for a given finder
                and a collection.
            */
            template<typename FinderT, typename RangeT>
            split_iterator(
                    RangeT& Col,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_bEof(false)
            {
                auto lit_col = string_algo::as_literal(Col);
            	
                m_Match=std::span(::std::begin(lit_col), ::std::begin(lit_col));
                m_Next=::std::begin(lit_col);
                m_End=::std::end(lit_col);

                // force the correct behavior for empty sequences and yield at least one token
                if(m_Next!=m_End)
                {
                    increment();
                }
            }


        public:
        // iterator operations

            // dereference
            const match_type& dereference() const
            {
                return m_Match;
            }

            // increment
            void increment()
            {
                match_type FindMatch=this->do_find( m_Next, m_End );

                if(FindMatch.begin()==m_End && FindMatch.end()==m_End)
                {
                    if(m_Match.end()==m_End)
                    {
                        // Mark iterator as eof
                        m_bEof=true;
                    }
                }

                m_Match=match_type( m_Next, FindMatch.begin() );
                m_Next=FindMatch.end();
            }

        private:
            // comparison
            bool equal( const split_iterator& Other ) const
            {
                bool bEof=eof();
                bool bOtherEof=Other.eof();

                return bEof || bOtherEof ? bEof==bOtherEof :
                    (
                        m_Match==Other.m_Match &&
                        m_Next==Other.m_Next &&
                        m_End==Other.m_End
                    );
            }

        public:
        // operations

            //! Eof check
            /*!
                Check the eof condition. Eof condition means that
                there is nothing more to be searched i.e. find_iterator
                is after the last match.
            */
            bool eof() const
            {
                return this->is_null() || m_bEof;
            }

        private:
        // Attributes
            match_type m_Match;
            input_iterator_type m_Next;
            input_iterator_type m_End;
            bool m_bEof;
        };

        //! split iterator construction helper
        /*!
         *    Construct a split iterator to iterate through the specified collection
         */
        template<typename RangeT, typename FinderT>
        inline split_iterator< 
            std::remove_pointer_t<typename RangeT::pointer> >
        make_split_iterator(
            RangeT& Collection,
            FinderT Finder)
        {
            return split_iterator< std::remove_pointer_t<typename RangeT::pointer> >(
                Collection, Finder);
        }


    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_iterator;
    using algorithm::make_find_iterator;
    using algorithm::split_iterator;
    using algorithm::make_split_iterator;

} // namespace string_algo


#endif  //STRING_FIND_ITERATOR_HPP
