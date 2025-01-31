#include "ScriptHost.hpp"

#include <Dusk/Benchmark.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

ScriptHost::ScriptHost()
{
    mp_LuaState = luaL_newstate();

    if (!mp_LuaState)
    {
        DuskLog("error", "Failed to create Lua State");
        lua_close(mp_LuaState);
        return;
    }

    luaL_openlibs(mp_LuaState);

    Scripting::AddScriptHost(this);
}

ScriptHost::~ScriptHost()
{
    Scripting::RemoveScriptHost(this);

    lua_close(mp_LuaState);
}

bool
ScriptHost::RegisterFunction(const string& funcName, LuaCallback callback)
{
    if (funcName.empty())
    {
        DuskLog("error", "Cannot register a function with no name");
        return false;
    }

    if (callback == nullptr)
    {
        DuskLog("error", "Cannot register a fucntion with no callback");
    }

    lua_register(mp_LuaState, funcName.c_str(), callback);
    return true;
}

bool
ScriptHost::RunFile(const string& filename)
{
    int status = luaL_loadfile(mp_LuaState, filename.c_str());

    if (status)
        goto error;

    // Set the error callback to 0, this means errors will be pushed onto the stack
    status = lua_pcall(mp_LuaState, 0, LUA_MULTRET, 0);

    if (status)
        goto error;

    return true;

error:

    DuskExtLog("error", "%s", lua_tostring(mp_LuaState, -1)); // get error message from stack
    lua_pop(mp_LuaState, 1);                                  // remove error message
    return false;
}

bool
ScriptHost::RunString(const string& code)
{
    int status = luaL_dostring(mp_LuaState, code.c_str());

    if (status)
        goto error;

    status = lua_pcall(mp_LuaState, 0, LUA_MULTRET, 0);

    return true;

error:

    DuskExtLog("error", "%s", lua_tostring(mp_LuaState, -1)); // get error message from stack
    lua_pop(mp_LuaState, 1);                                  // remove error message
    return false;
}

} // namespace dusk
