#include <map>
#include <functional>
#include <cassert>

template <typename T>
class StateMachine
{
public:
    using StateFunc = std::function<void()>;

    void Add(T id, StateFunc enter, StateFunc update, StateFunc leave)
    {
        m_States[id] = {id, enter, update, leave};
    }

    T CurrentState() const
    {
        return m_CurrentState.Id;
    }

    void Update()
    {
        m_CurrentState.Update();
    }

    void Shutdown()
    {
        if (m_CurrentState.Leave != nullptr)
            m_CurrentState.Leave();
        m_CurrentState = {};
    }

    void SwitchTo(T state)
    {
        assert(m_States.count(state) > 0 && "Trying to switch to unknown state");
        assert(m_CurrentState.Id != state && "Trying to switch to state that is already current");

        const auto& newState = m_States[state];
        if (m_CurrentState.Leave != nullptr)
            m_CurrentState.Leave();
        if (newState.Enter != nullptr)
            newState.Enter();
        m_CurrentState = newState;
    }

private:
    struct State
    {
        T Id;
        StateFunc Enter;
        StateFunc Update;
        StateFunc Leave;
    };

    std::map<T, State> m_States;
    State m_CurrentState;
};
