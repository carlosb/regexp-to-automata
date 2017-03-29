//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/24/17 Carlos Brito
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.*
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/22/17.
 *
 * Description:
 *
 * This is a class implementing a hashtable à la STL.
 *
 * This header file has been compiled for C++11.
 *
 * We have to note that the default value for the Hasher is to utilize
 * std::hash which overloads  operator() and has a result of type size_t
 *
 * For insertion of an hash_entry of type T, we expect that the object class
 * for T has an appropiate and well behaved copy constructor.
 *
 * TODO:
 *
 * Implement operator=
 * Implement operator[]
 *
 *
 * (?) Overload iterator operator() on iterator so we can typedef something like this
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_HASHTABLE_H
#define MYREGEX_HASHTABLE_H

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <functional>
#include <memory>
#include <vector>
#include <list>

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //
template <
        class Key,
        class T,
        class Hasher = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
>
class hashtable {


    // TYPEDEFS STRUCTURES
    typedef typename std::pair<Key, T> hash_entry_type;
    typedef typename std::list<hash_entry_type> bucket_type;
    typedef typename std::vector<bucket_type> index_table;

public:
    // TYPEDEFS ITERATORS
    typedef typename index_table::iterator index_iterator;
    typedef typename bucket_type::iterator bucket_iterator;


    // ITERATOR CLASS
public:
    class iterator {
    public:
        typedef iterator self_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        typedef hash_entry_type& reference;
        typedef hash_entry_type value_type;
        typedef hash_entry_type* pointer;


        iterator(hashtable const& table, size_t index, bucket_iterator const& entry)
                : t_(table),
                  index_(index),
                  entry_(entry)
        {}

        iterator(hashtable const& table, size_t index)
                : t_(table),
                  index_(index),
                  entry_(table.bucket(index).begin())
        {}

        iterator(hashtable const& table)
                : t_(table),
                  index_(0),
                  entry_(table.bucket(0).begin()) // start of first bucket
        {}

        self_type operator++() { // prefix
            std:: cout << "++: " << index_ << std::endl;
            if ( ++index_ == t_.bucket_count()-1 )
                return t_.end();

            while ( t_.bucket(index_).empty() )// current bucket is empty
            {
                if ( ++index_ == t_.bucket_count() - 1 ) // we reached the last bucket and still no bucket found
                    return t_.end();

            }
            entry_ = t_.bucket(index_).begin(); // return beginning of first non-empty bucket
            return *this;
        }

        self_type operator++(int dummy) { // postfix
            self_type it = *this; ++(*this); return it;
        }

        reference operator*() { return *entry_; }
        pointer operator->() { return &*entry_; }

        bool operator==(const self_type& rhs) { return entry_ == rhs.entry_; }
        bool operator!=(const self_type& rhs) { return !(*this == rhs); }

    private:
        hashtable t_;
        size_t index_;
        bucket_iterator entry_;
    };


    // VARIABLES
private:
    KeyEqual equal_to_ = KeyEqual();
    index_table table_;
    Hasher h_;
    const size_t bucket_count_;

    // METHODS
public:
    hashtable(const size_t buckets)
            : bucket_count_(buckets),
              h_(Hasher()),
              equal_to_(KeyEqual())
    {
        table_ = std::vector<bucket_type>(buckets);
    }

    virtual ~hashtable() {
    }

    virtual size_t size() const {
        return bucket_count_;
    }

    virtual iterator insert(Key const& key, T const& obj) {

        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];

        // Verify that we're not adding a duplicate hash_entry
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if ( equal_to_( it->first, key ) )
                return this->end();

        b->push_back( hash_entry_type(key, obj) ); // push to back of bucket

        return iterator( *this, index, --(b->end()) );
    }

    virtual iterator find(Key const& key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            // iterate over bucket
            if ( equal_to_( key, it->first ) )
                // if we find key return iterator to it
                return iterator( *this, index, it );

        return this->end();
    }

    virtual void remove(Key key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to_(key, it->first))
                b->erase(it); // erase entry
    }

    virtual bool containsKey(Key key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to_(key, it->first))
                return true;

        return false;
    }

    size_t bucket_count() const {
        return bucket_count_;
    }

    iterator begin()  {
        size_t index = 0;

        while ( bucket(index).size() == 0 )// current bucket is empty
        {
            std::cout << index << std::endl;

            if ( ++index == bucket_count() - 1 )
                return iterator(*this, index, bucket(index).end() ); // return end of last bucket
        }
        return iterator(*this, index, bucket(index).begin()); // return beginning of first non-empty bucket
    }

    iterator end()  {
        size_t index = bucket_count();

        while ( bucket(index).size() == 0 ) // current bucket is empty
        {
            if ( --index == 0 )
                return iterator( *this, index, bucket(index).begin() ); // return start of first bucket

        }
        return iterator( *this, index, bucket(index).end() ); // return end of first non-empty bucket
    }

     bucket_type& bucket(size_t index) {
         return table_[index];
    }


};

#endif //MYREGEX_HASHTABLE_H
