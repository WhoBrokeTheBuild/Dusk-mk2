#ifndef DUSK_SCRIPTING_SCRIPT_HOST_HPP
#define DUSK_SCRIPTING_SCRIPT_HOST_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Types.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>

#include <lua.hpp>

namespace dusk
{

class ScriptHost : public TrackedObject
{
public:
    DUSK_CLASSNAME("ScriptHost")

    ScriptHost();
    ScriptHost(const ScriptHost&) = delete;
    ScriptHost& operator=(const ScriptHost&) = delete;
    virtual ~ScriptHost();

    bool RunFile(const string& filename);
    bool RunString(const string& code);
    bool RegisterFunction(const string& funcName, LuaCallback callback);

    inline lua_State* GetState() { return mp_LuaState; }

private:
    lua_State* mp_LuaState;

}; // class ScriptHost

} // namespace dusk

#endif // DUSK_SCRIPTING_SCRIPT_HOST_HPP
