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

#ifndef __RIGHTWAY_DUMP_WIN_BASIC_DUMP_IMPL_HPP__
#define __RIGHTWAY_DUMP_WIN_BASIC_DUMP_IMPL_HPP__

#include <rightway/dump/error.hpp>
#include "basic_dump.hpp"

#include <rightway/system/noncopyable.hpp>

#include <string>

#include <windows.h>
#include <dbghelp.h>

#pragma comment(lib, "dbghelp.lib")

namespace rightway { namespace system {

BOOL CALLBACK minidump_callback(PVOID param, const PMINIDUMP_CALLBACK_INPUT input, PMINIDUMP_CALLBACK_OUTPUT output);

template<>
class pimpl<rightway::dump::detail::basic_dump>::implementation
    : private rightway::system::noncopyable
{
public:
    implementation()
    {
    }

    ~implementation()
    {
    }

public:
    void save(const std::string & filename, rightway::system::error_code & ec)
    {
        HANDLE hFile = ::CreateFileA(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 
            0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE)) 
        {
            MINIDUMP_CALLBACK_INFORMATION mci; 

            mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)minidump_callback; 
            mci.CallbackParam   = 0; 

            MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory); 

            if (!::MiniDumpWriteDump( ::GetCurrentProcess(), ::GetCurrentProcessId(), 
                hFile, mdt, 0, 0, 0 ))
            {
                ec = rightway::dump::error::no_dump;
            }

            ::CloseHandle(hFile);
        }

        switch (::GetLastError())
        {
        case ERROR_SUCCESS:
            ec = rightway::system::error_code();
            break;
        case ERROR_ACCESS_DENIED:
            ec = rightway::dump::error::access_denied;
            break;
            
        }
    }
};

BOOL CALLBACK minidump_callback(
    PVOID param, 
    const PMINIDUMP_CALLBACK_INPUT   input, 
    PMINIDUMP_CALLBACK_OUTPUT        output 
) 
{
    BOOL result = FALSE; 

    // Check parameters
    if( input == 0 ) 
        return FALSE; 

    if( output == 0 ) 
        return FALSE; 


    // Process the callbacks 
    switch (input->CallbackType)
    {
        case IncludeModuleCallback: 
        {
            // Include the module into the dump 
            result = TRUE; 
        }
        break; 

        case IncludeThreadCallback: 
        {
            // Include the thread into the dump 
            result = TRUE; 
        }
        break; 

        case ModuleCallback: 
        {
            // Does the module have ModuleReferencedByMemory flag set ?
            if( !(output->ModuleWriteFlags & ModuleReferencedByMemory) ) 
            {
                // No, it does not - exclude it 
                output->ModuleWriteFlags &= (~ModuleWriteModule); 
            }

            result = TRUE; 
        }
        break; 

        case ThreadCallback: 
        {
            // Include all thread information into the minidump 
            result = TRUE;  
        }
        break; 

        case ThreadExCallback: 
        {
            // Include this information 
            result = TRUE;  
        }
        break; 

        case MemoryCallback: 
        {
            // We do not include any information here -> return FALSE 
            result = FALSE; 
        }
        break; 

        case CancelCallback: 
            break; 
    }

    return result; 

}

template<>
template<>
pimpl<rightway::dump::detail::basic_dump>::pointer_semantics::~pointer_semantics()
{
    // Always empty
}

}   // namespace system
}   // rightway

#endif
