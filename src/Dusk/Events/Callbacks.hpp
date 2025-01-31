#ifndef DUSK_CALLBACKS_HPP
#define DUSK_CALLBACKS_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/Event.hpp>

namespace dusk
{

class ScriptHost;

template <typename ReturnType, typename Param = void>
class ICallback : public TrackedObject
{
public:
    virtual inline ~ICallback() {}

    virtual inline string GetClassName() const { return "Callback"; }

    friend bool operator==(
        const ICallback<ReturnType, Param>& lhs, const ICallback<ReturnType, Param>& rhs)
    {
        return lhs.IsEqualTo(rhs);
    }

    friend bool operator!=(
        const ICallback<ReturnType, Param>& lhs, const ICallback<ReturnType, Param>& rhs)
    {
        return !lhs.IsEqualTo(rhs);
    }

    virtual ReturnType Invoke(Param param) = 0;
    virtual ICallback* Clone() = 0;
    virtual bool IsMethodOf(void* pObject) = 0;

protected:
    inline virtual bool IsEqualTo(const ICallback<ReturnType, Param>& rhs) const { return false; };

private:
}; // class Callback

template <typename ReturnType, typename Param = void>
class FunctionCallback : public ICallback<ReturnType, Param>
{
public:
    DUSK_CLASSNAME("Function Callback")

    FunctionCallback(ReturnType (*pFunction)(Param))
        : mp_Function(pFunction)
    {
    }

    inline virtual ReturnType Invoke(Param param) override { return (*mp_Function)(param); }

    inline virtual FunctionCallback* Clone() override { return New FunctionCallback(mp_Function); }

    inline virtual bool IsMethodOf(void* pObject) override { return false; }

protected:
    virtual bool IsEqualTo(const ICallback<ReturnType, Param>& rhs) const override
    {
        if (const FunctionCallback<ReturnType, Param>* pConvert
            = dynamic_cast<const FunctionCallback<ReturnType, Param>*>(&rhs))
        {
            return (mp_Function == pConvert->mp_Function);
        }
        return false;
    }

private:
    ReturnType (*mp_Function)(Param);

}; // class FunctionCallback

template <typename ReturnType, typename Param = void, typename ObjectType = void,
    typename Method = void>
class MethodCallback : public ICallback<ReturnType, Param>
{
public:
    DUSK_CLASSNAME("Method Callback")

    MethodCallback(void* pObject, Method method)
        : m_Method(method)
        , mp_Object(pObject)
    {
    }

    inline virtual ReturnType Invoke(Param param) override
    {
        return (static_cast<ObjectType*>(mp_Object)->*m_Method)(param);
    }

    inline virtual MethodCallback* Clone() override { return New MethodCallback(mp_Object, m_Method); }

    inline virtual bool IsMethodOf(void* pObject) override { return mp_Object == pObject; }

protected:
    virtual bool IsEqualTo(const ICallback<ReturnType, Param>& rhs) const override
    {
        if (const MethodCallback<ReturnType, Param, ObjectType, Method>* pConvert
            = dynamic_cast<const MethodCallback<ReturnType, Param, ObjectType, Method>*>(&rhs))
        {
            return (m_Method == pConvert->m_Method && mp_Object == pConvert->mp_Object);
        }
        return false;
    }

private:
    Method m_Method;
    void* mp_Object;

}; // class MethodCallback

class LuaFucntionCallback : public ICallback<void, const Event&>
{
public:
    DUSK_CLASSNAME("Lua Function Callback")

    LuaFucntionCallback(ScriptHost* pScriptHost, const string& callback);

    virtual void Invoke(const Event& event) override;

    inline virtual LuaFucntionCallback* Clone() override
    {
        return New LuaFucntionCallback(mp_ScriptHost, m_Callback);
    }

    inline virtual bool IsMethodOf(void* pObject) override { return false; }

protected:
    virtual bool IsEqualTo(const ICallback<void, const Event&>& rhs) const override;

private:
    ScriptHost* mp_ScriptHost;
    string m_Callback;

}; // class LuaFucntionCallback

} // namespace dusk

#endif // DUSK_CALLBACKS_HPP
