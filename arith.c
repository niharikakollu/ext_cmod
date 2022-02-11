#include "esp_log.h"
#include "lauxlib.h"
#include "lnodeaux.h"
#include "module.h"
#include<string.h>
#define ADD_TABLE_ITEM(L, key, val) \
  lua_pushstring (L, val);      \
  lua_setfield (L, -2, key);
 struct task_table{
  const char *name;
  const char *task;
  const char *status;
};
static const char* ARITHMETIC_METATABLE = NODEMCU_MODULE_METATABLE();
void inline structure_ToTable(lua_State *L, struct task_table *test )
{ 
  lua_createtable (L, 0, 3);
  ADD_TABLE_ITEM (L, "name", test->name );
  ADD_TABLE_ITEM (L, "task", test->task);
  ADD_TABLE_ITEM (L, "status", test->status);
}
static int teal_scheduler_table(lua_State *L){
 int *zon,*sw,*dur,i=0;
size_t datalen
struct localstruct SPprog_tab;
 if( lua_istable( L,1)){
 lua_getfield(L,1,"zone_id");
 if (lua_type(L, -1)==LUA_TTABLE){
    printf("failed");
    datalen = lua_objlen(L,1);
    SPprog_tab.zone_id=(int*)calloc(datalen, sizeof(int));
	for( i = 0; i < datalen; i ++ ){
		lua_rawgeti( L, 1, i + 1 );
     SPprog_tab.zone_id[i]=lua_tointeger (L, -1);
     printf("%d\t",SPprog_tab.zone_id[i]);
      lua_pop (L, 2);
    }
 }
 else
	 luaL_error (L, "Not an array");
 lua_getfield(L,1,"duration_mins");
 if (lua_type(L, -1) == LUA_TTABLE){
     datalen = lua_objlen(L,1);
    printf("failed1\n");
    SPprog_tab.duration_mins=(int*)calloc(datalen, sizeof(int));
    for( i = 0; i < datalen; i ++ ){
		lua_rawgeti( L, 1, i + 1 );
     SPprog_tab.duration_mins[i]=lua_tointeger (L, -1);
     printf("%d\t",SPprog_tab.duration_mins[i]);
      lua_pop (L, 2);
    }
 }
 else
   luaL_error (L, "Not an array");
 lua_getfield(L,1,"seq_num");
 if (lua_type(L, -1) == LUA_TTABLE){
   datalen = lua_objlen( L,1 );
   printf("failed2\n");
   SPprog_tab.seq_num=(int*)calloc(datalen, sizeof(int));
   int i=0;
  for( i = 0; i < datalen; i ++ ){
		lua_rawgeti( L, 1, i + 1 );
     SPprog_tab.seq_num[i]=lua_tointeger (L, -1);
     printf("%d\t",SPprog_tab.seq_num[i]);
      lua_pop (L, 2);
  }
 }
 else
   luaL_error (L, "Not an array"); zon=(int*)calloc(datalen,sizeof(int));
 sw=(int*)calloc(datalen,sizeof(int));
 dur=(int*)calloc(datalen,sizeof(int));
 int k=0,cur_seq=0,crt_ix=0;
 while(crt_ix<=datalen){
  cur_seq=repeated_seq(SPprog_tab.seq_num,crt_ix,SPprog_tab.seq_num[crt_ix],datalen);
  if (cur_seq==1){
   sw[k]=1;
   zon[k]=SPprog_tab.zone_id[crt_ix];
   dur[k]=0;
   k=k+1;
   sw[k]=0;
   zon[k]=SPprog_tab.zone_id[crt_ix];
   dur[k]=SPprog_tab.duration_mins[crt_ix];
   k=k+1;
  }
  else{
    int buff[cur_seq],low_val=0,tp=k;
    for(int i=0;i<cur_seq;i++){
     buff[i]=SPprog_tab.duration_mins[crt_ix+i-1];
     sw[tp]=1;
     dur[tp]=0;
     tp++;
    }
    quick(buff,0,cur_seq-1);
    int s[cur_seq],l=k,m=0;
    for(int i=0;i<cur_seq;i++){
      for(int j=0; j<cur_seq; j++){
        if(buff[i]==SPprog_tab.duration_mins[crt_ix+i-1]){
          if(find_val_match(s,cur_seq,buff[i])==0){
            sw[k]=0;
            zon[l]=SPprog_tab.zone_id[crt_ix+i-1];
            zon[k]=SPprog_tab.zone_id[crt_ix+i-1];
            dur[k]=buff[i]-low_val;
            s[m]=i;
            k++;
            l++;
            m++;
            low_val=buff[i];
            break;
          }
        }
      }
    }
  }
  crt_ix+=cur_seq;
 }
 //lua_createtable(L,3,0);
 printf("failed3\n");
 lua_newtable(L);
 lua_pushliteral(L,"switch");
 lua_newtable(L);
 size_t len=(sizeof(sw)/sizeof(sw[0]));
 int len1=len,len2=len;
 for(int i=0;i<(sizeof(sw)/sizeof(sw[0]));i++){
   len1=len1+1-i;
   len2=len2-i;
   lua_pushnumber( L, (lua_Number)sw[i]);
   lua_rawseti( L,-(len1), len2);
  }
 lua_pushliteral(L,"time");
 lua_newtable(L);
 len1=len;len2=len;
 for(int i=0;i<(sizeof(sw)/sizeof(sw[0]));i++){
   len1=len1+1-i;
   len2=len2-i;
   lua_pushnumber( L, (lua_Number)dur[i]);
   lua_rawseti( L,-(len1), len2);
  }
 lua_pushliteral(L,"zone");
 lua_newtable(L);
 len1=len;len2=len;
 for(int i=0;i<(sizeof(sw)/sizeof(sw[0]));i++){
   len1=len1+1-i;
   len2=len2-i;
   lua_pushnumber( L, (lua_Number)zon[i]);
   lua_rawseti( L,-(len1), len2);
  }
lua_settable(L,-(len+1));
lua_settable(L,-(len+1));
lua_settable(L,-(len+1));
 free(zon);
 free(sw);
 free(dur);
 return 1;
}
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
   const char *sdata1=luaL_checkstring(L,1), *sdata2=luaL_checkstring(L,2);
     printf("two strings:%s\t%s\n",sdata1,sdata2);
    lua_concat(L,2);
    return 1;
}

// decimal to binary module
static int decimal_binary(lua_State* L){  
  int dec_num=luaL_checknumber(L,1);
  long long bin_num=0;
  int rem, i = 1;
    while (dec_num!=0) {
    rem = dec_num % 2;
    dec_num /= 2;
    bin_num+= rem * i;
    i *= 10;
  }
  lua_pushnumber(L, (lua_Number)bin_num);
    return 1;
}
//  lopading table with key values.
static int table_key(lua_State* L){  
  struct task_table test;
  luaL_checkanytable (L, 1);
  lua_getfield (L, 1, "name");
  test.name = luaL_optstring(L, -1, "nill");
  lua_getfield (L, 1, "task");
  test.task =  luaL_optstring(L, -1, "nill");
  lua_getfield (L, 1, "status");
  test.status =  luaL_optstring(L, -1, "nill");
  printf("table elemnts are:%s\t%s\t%s\n",test.name,test.task,test.status);
  structure_ToTable(L,&test);
    return 1;
}
 static int load_arr(lua_State* L){
  size_t datalen, i;
   lua_newtable( L ); 
     if( lua_istable( L,1)){
     datalen = lua_objlen( L,1 );
      for( i = 0; i < datalen; i ++ ){
      lua_rawgeti( L, 1, i + 1 );
    if(lua_type(L,-1)== LUA_TNUMBER){ 
    lua_pushnumber(L, (lua_Number)luaL_checknumber(L,-1));
     lua_pop( L, 1 );
     lua_rawseti( L,-2, i + 1 );
    }
    else if(lua_type(L,-1)== LUA_TSTRING){
     lua_pushstring(L,luaL_checkstring(L,-1));
     lua_pop( L, 1 );
     lua_rawseti( L,-2, i + 1 );
    }
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
LROT_FUNCENTRY(tkey,table_key)
LROT_FUNCENTRY(sconcat,string_concat)
LROT_FUNCENTRY(dectobin,decimal_binary)
  LROT_FUNCENTRY(schedule_table,teal_scheduler_table)
LROT_END(module, NULL, 0)

// module_init is invoked on device startup
static int module_init(lua_State* L) {
    luaL_rometatable(L, ARITHMETIC_METATABLE, (void*)arith_metatable_map);  // create metatable for arithmetic
    return 0;
}

NODEMCU_MODULE_STD();  // define Lua entries
