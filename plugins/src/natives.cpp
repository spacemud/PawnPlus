#include "natives.h"
#include "amxinfo.h"

cell impl::handle_error(AMX *amx, cell *params, const char *native, const errors::native_error &error)
{
	int handler;
	if(amx_FindPublic(amx, "pp_on_error", &handler) == AMX_ERR_NONE)
	{
		cell amx_addr, *addr;
		cell reset_hea, *ret_addr;
		amx_Allot(amx, 1, &reset_hea, &ret_addr);
		*ret_addr = 0;
		amx_Push(amx, reset_hea);
		amx_Push(amx, error.level);
		amx_PushString(amx, &amx_addr, &addr, error.message.c_str(), false, false);
		amx_PushString(amx, &amx_addr, &addr, native, false, false);
		cell ret;
		amx_Exec(amx, &ret, handler);
		cell retval = *ret_addr;
		amx_Release(amx, reset_hea);

		if(ret)
		{
			return retval;
		}
	}

	logprintf("[PawnPlus] %s: %s", native, error.message.c_str());
	if(error.level >= amx::load_lock(amx)->get_extra<native_error_level>().level)
	{
		amx_RaiseError(amx, AMX_ERR_NATIVE);
	}
	return 0;
}
