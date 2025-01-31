#ifndef DUSK_SCRIPTING_SCRIPTING_SYSTEM_HPP
#define DUSK_SCRIPTING_SCRIPTING_SYSTEM_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Types.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Collections/ArrayList.hpp>

#include <lua.hpp>

namespace dusk
{

class ScriptHost;

class Scripting
{
public:
    Scripting() = delete;
    Scripting(const Scripting&) = delete;
    Scripting& operator=(const Scripting&) = delete;
    ~Scripting() = delete;

    static void AddScriptHost(ScriptHost* pHost);

    static ScriptHost* GetScriptHost(lua_State* L);

    static void RemoveScriptHost(ScriptHost* pHost);

    static bool RegisterFunction(const string& funcName, LuaCallback callback);

private:
    static Map<string, LuaCallback> s_Functions;

    static ArrayList<ScriptHost*> s_ScriptHosts;

}; // class ScriptingSystem

} // namespace dusk

#endif // DUSK_SCRIPTING_SCRIPTING_SYSTEM_HPP
