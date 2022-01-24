#include <stdio.h>
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
static const char* TESTCPLUS_METATABLE = NODEMCU_MODULE_METATABLE();
static int average_sum(lua_State *L)
{
	int n = lua_gettop(L);
	double sum = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
          sum += lua_tonumber(L, i);
	}
	lua_pushnumber(L, sum / n);
	lua_pushnumber(L, sum);
	return 2;
}
LROT_BEGIN(testcplus_metatable)
LROT_END(testcplus_metatable, NULL, 0)
LROT_BEGIN(module)
LROT_FUNCENTRY(avg, average_sum)
LROT_END(module, NULL, 0)

// module_init is invoked on device startup
static int module_init(lua_State* L) {
    luaL_rometatable(L, TESTCPLUS_METATABLE, (void*)testcplus_metatable_map);  // create metatable for arithmetic
    return 0;
}

NODEMCU_MODULE_STD();  
