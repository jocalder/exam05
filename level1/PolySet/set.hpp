#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set
{
    private:
        searchable_bag&     bag;
        set();
        set(const set& other);
        set&    operator=(const set& other);
    public:
        set(searchable_bag& s_bag);
        ~set();

        const searchable_bag&   get_bag();

        bool    has(int) const;
        void    insert(int);
        void    insert(int *, int);
        void    print() const;
        void    clear();
};

#endif