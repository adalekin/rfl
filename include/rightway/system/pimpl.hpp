/*
 * Rightway Feedback Libraries.
 * Copyright (C) 2009  Alexey Dalekin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __RIGHTWAY_SYSTEM_PIMPL_HPP__
#define __RIGHTWAY_SYSTEM_PIMPL_HPP__

#include <memory>

namespace rightway { namespace system {

template<class T>
struct pimpl
{
    class implementation;

    template<template<class> class PointerPolicy>
    class detail;

    typedef detail<std::auto_ptr> pointer_semantics;
};

template<class T>
template<template<class> class PointerPolicy>
class pimpl<T>::detail
{
public:
    typedef typename pimpl<T>::implementation implementation;

protected:
    detail()
    {
    }

    detail(implementation * p)
        : impl_(p)
    {
    }
    
    virtual ~detail() = 0;

    detail(const detail&);
    detail& operator=(const detail&); 

public:
    implementation const* operator->() const { return  impl_.get(); }
    implementation const& operator *() const { return *impl_.get(); }
    implementation*       operator->()       { return  impl_.get(); }
    implementation&       operator *()       { return *impl_.get(); }

private:
    PointerPolicy<implementation> impl_;
};

}   // namespace system
}   // namespace rightway

#endif
