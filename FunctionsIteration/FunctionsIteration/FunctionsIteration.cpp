#include <functional>
#include <iostream>
#include <utility>
#include <variant>
#include <vector>

class Module
{
public:
    void
    foo()
    {
        std::cout << "In foo\n";
    }

    Module();
};

class Function_Manager
{
private:
    using ModuleCallback = std::function<void(Module*)>;
    using VoidCallback   = std::function<void(void)>;

    std::vector<VoidCallback> m_callbacks;



public:
    void
    Add_Callback(const VoidCallback& callbackFunc)
    {
        m_callbacks.emplace_back(callbackFunc);
    }
    void
    Add_Callback(const ModuleCallback& callbackFunc, Module* caller)
    {
        auto function = std::bind(callbackFunc, caller);
        m_callbacks.emplace_back(function);
    }

    void
    CallEverything()
    {
        for(const VoidCallback& callbackFunc : m_callbacks)
        {
            callbackFunc();
        }
    }
};

Function_Manager fm{};

Module::Module()
{
    fm.Add_Callback(&Module::foo, this);
}

void AnotherFoo()
{
    std::cout << "In another foo\n";
}

int
main()
{
    Module m{};
    fm.Add_Callback(&AnotherFoo);

    fm.CallEverything();
    std::cout << "Hello World!\n";
}
