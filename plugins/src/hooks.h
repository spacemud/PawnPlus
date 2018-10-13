#ifndef HOOKS_H_INCLUDED
#define HOOKS_H_INCLUDED

#include "sdk/amx/amx.h"

int AMXAPI amx_InitOrig(AMX *amx, void *program);
int AMXAPI amx_ExecOrig(AMX *amx, cell *retval, int index);

namespace Hooks
{
	void Register();
	void Unregister();
	void ToggleStrLen(bool toggle);
	void ToggleRefArgs(bool toggle);
}

#endif
