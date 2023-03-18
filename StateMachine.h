#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
#include <memory>
#include "ServerGameLoop.h"

using namespace std;
typedef void (ServerGameLoop::*StateFunction)();

enum class ServerState {Idle, Loading, Active};

template <typename T>
class StateMachine
{
public:
	using StateFunc = function<void()>;
	void Add(T id, StateFunction  enter, StateFunction  update, StateFunction  leave)
	{
		m_States.emplace(id,State{id, enter, update, leave});
	}
	T CurrentState() const
	{
		return m_CurrentState ? m_CurrentState->Id : T();
	}
	void Update() const 
	{
		if(m_CurrentState)
			m_CurrentState->Update();
		else	
			cout<<"nullPtr"<<endl;
	}
	void ShutDown()
	{
		if(m_CurrentState && m_CurrentState->Leave)
			m_CurrentState->Leave();
		m_CurrentState = nullptr;
	}
	void SwitchTo(T state)
	{
		if(m_States.find(state) == m_States.end())
		{
			return;
		}
		if(m_CurrentState && m_CurrentState->Id == state)
		{
			return;
		}
		auto newState = &m_States[state];
		if(m_CurrentState&& m_CurrentState->Leave)
			m_CurrentState->Leave();
		if(newState->Enter)
			newState->Enter();
		m_CurrentState = newState;
	}
private:
	struct State
	{
		T Id;
		StateFunction  Enter;
		StateFunction  Update;
		StateFunction  Leave;
	};
	State* m_CurrentState = nullptr;
	std::unordered_map<T, State> m_States;
};
