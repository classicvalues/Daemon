/*
===========================================================================

Daemon GPL Source Code
Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company.

This file is part of the Daemon GPL Source Code (Daemon Source Code).

Daemon Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Daemon Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Daemon Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Daemon Source Code is also subject to certain additional terms.
You should have received a copy of these additional terms immediately following the
terms and conditions of the GNU General Public License which accompanied the Daemon
Source Code.  If not, please request a copy in writing from id Software at the address
below.

If you have questions concerning this license or the applicable additional terms, you
may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville,
Maryland 20850 USA.

===========================================================================
*/

#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_

#ifndef QVM_COMPAT

#include "../../libs/nacl/nacl.h"
#include "../../common/RPC.h"

namespace VM {

enum Type {
  TYPE_NACL,
  TYPE_NATIVE
};

// Base class for a virtual machine instance
class VMBase {
public:
  // Create the VM for the named module. Returns the ABI version reported
  // by the module.
  int Create(const char* name, Type type);

  // Free the VM
  void Free()
  {
    module.Close();
  }

  // Check if the VM is active
  bool IsActive() const
  {
    return bool(module);
  }

protected:
  // Perform an RPC call with the given inputs, returns results in output
  RPC::Reader DoRPC(RPC::Writer& input, bool ignoreErrors = false);

  // System call handler
  virtual void Syscall(int index, RPC::Reader& input, RPC::Writer& output) = 0;

private:
  NaCl::Module module;
};

} // namespace VM

#endif // QVM_COMPAT

#endif // VIRTUALMACHINE_H_