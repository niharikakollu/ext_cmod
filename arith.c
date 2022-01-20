#include "esp_log.h"
#include "lauxlib.h"
#include "lnodeaux.h"
#include "module.h"
#include<string.h>
static const char* ARITHMETIC_METATABLE = NODEMCU_MODULE_METATABLE();
// addition module
static int arithmetic_add(lua_State* L)
{
  int n= lua_gettop(L);
  int num1 = lua_tonumber( L, 1);
  int num2 = lua_tonumber( L, 2);
  int add_test=num1+num2;
  printf("number of arguments, %d:\nnum1 %d ,num2 %d\n", n,num1,num2);
    lua_pushinteger( L, (lua_Integer )add_test );
    return 1;
}

// substraction module
static int arithmetic_sub(lua_State* L)
{
  int n= lua_gettop(L);
  int num1 = lua_tonumber( L, 1);
  int num2 = lua_tonumber( L, 2);
  int sub_test=num1-num2;
  printf("number of arguments, %d:\nnum1 %d ,num2 %d\n", n,num1,num2);
    lua_pushinteger( L, (lua_Integer )sub_test );
    return 1;
}
// multiplication module
static int arithmetic_mul(lua_State* L){
  int n= lua_gettop(L);
  int num1 = lua_tonumber( L, 1);
  int num2 = lua_tonumber( L, 2);
  int mul_test=num1*num2;
  printf("number of arguments, %d:\nnum1 %d ,num2 %d\n", n,num1,num2);
    lua_pushinteger( L, (lua_Integer )mul_test );
    return 1;
}
// division module
 static int arithmetic_div(lua_State* L)
{
  char div_res[20];
  int n= lua_gettop(L);
  float num1 = lua_tonumber( L, 1);
  float num2 = lua_tonumber( L, 2);
  float div_test=num1/num2;
  sprintf(div_res, "%f",div_test);
  printf("number of arguments, %d:\nnum1 %f ,num2 %f\n", n,num1,num2);
    lua_pushnumber( L, div_test );
    return 1;
}
// string concatination module
static int string_concat(lua_State* L)
{
    size_t datalen,datalen2;
    datalen = lua_objlen( L, 1 );
    datalen2 = lua_objlen( L, 2);
   const char *sdata1=luaL_checkstring(L,1, &datalen), *sdata2=luaL_checkstring(L,1,&datalen2);
     printf("two strings  %s:\n %s",sdata1,sdata2);
    //strcat(sdata1,sdata2);
    lua_pushfstring(L,sdata1,sdata2);
    return 1;
}
 static int load_arr(lua_State* L){
  int data;
  size_t datalen, i;
   lua_newtable( L ); 
     if( lua_istable( L,1)){
     datalen = lua_objlen( L,1 );
      for( i = 0; i < datalen; i ++ ){
       lua_rawgeti( L, 1, i + 1 );
       data= ( int )luaL_checkinteger( L, -1 );
       lua_pop( L, 1 );
       if( data< 0 || data> 255 )
       return luaL_error( L, "table value does not fit in 1 byte" );
       printf("table data %d\n", data);  
	 lua_pushinteger(L, (lua_Integer )data);
         lua_rawseti( L,-2, i + 1 );	
      }
     } 
   return 1;
 }
LROT_BEGIN(arith_metatable)
LROT_END(arith_metatable, NULL, 0)

LROT_BEGIN(module)
LROT_FUNCENTRY(add, arithmetic_add)
LROT_FUNCENTRY(sub, arithmetic_sub)
LROT_FUNCENTRY(mul, arithmetic_mul)
LROT_FUNCENTRY(div, arithmetic_div)
LROT_FUNCENTRY(larr,load_arr)
LROT_FUNCENTRY(sconcat,string_concat)
LROT_END(module, NULL, 0)

// module_init is invoked on device startup
static int module_init(lua_State* L) {
    luaL_rometatable(L, ARITHMETIC_METATABLE, (void*)arith_metatable_map);  // create metatable for arithmetic
    return 0;
}

NODEMCU_MODULE_STD();  // define Lua entries
