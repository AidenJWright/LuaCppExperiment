#include <iostream>
#include <string>

extern "C"
{
#include "Lua536/include/lua.h"
#include "Lua536/include/lauxlib.h"
#include "Lua536/include/lualib.h"
}

#ifdef _WIN64
#pragma comment(lib, "Lua536/liblua53.a")
#endif // x64


bool CheckLua(lua_State* L, int r)
{
  if (r != LUA_OK)
  {
    std::string errormsg = lua_tostring(L, -1);
    std::cout << errormsg << std::endl;
    return false;
  }
  return true;
}

int main()
{
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  if(CheckLua(L, luaL_dofile(L, "ExampleScript.lua")))
  {
    lua_getglobal(L, "a");
    if (lua_isnumber(L, -1))
    {
      float a_in_cpp = (float)lua_tonumber(L, -1);
      std::cout << "a_in_cpp = " << a_in_cpp << std::endl;
    }
  }

  lua_close(L);
  return 0;
}