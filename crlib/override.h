//
// YaPB - Counter-Strike Bot based on PODBot by Markus Klinge.
// Copyright © 2004-2022 YaPB Project <yapb@jeefo.net>.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <crlib/memory.h>
#include <crlib/platform.h>

using crmem = cr::Memory;

// override all the operators to get rid of linking to stdc++
void *operator new (size_t size) {
   return crmem::get <void *> (size);
}

void *operator new [] (size_t size) {
   return crmem::get <void *> (size);
}

void operator delete (void *ptr) noexcept {
   crmem::release (ptr);
}

void operator delete [] (void *ptr) noexcept {
   crmem::release (ptr);
}

void operator delete (void *ptr, size_t) noexcept {
   crmem::release (ptr);
}

void operator delete [] (void *ptr, size_t) noexcept {
   crmem::release (ptr);
}

CR_LINKAGE_C void __cxa_pure_virtual () {
   cr::plat.abort ("pure virtual function call");
}
