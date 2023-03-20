#include "ServerGameLoop.h"

ServerGameLoop::~ServerGameLoop()
{

}
bool ServerGameLoop::Init(string args)
{
    cout<<"Init..."<<endl;
    m_StateMachine.Add(ServerState::Idle, std::bind(&ServerGameLoop::EnterIdleState, this),
     std::bind(&ServerGameLoop::UpdateIdleState, this), 
    std::bind(&ServerGameLoop::LeaveIdleState, this));
    m_StateMachine.Add(ServerState::Loading,std::bind(&ServerGameLoop::EnterLoadingState, 
    this), std::bind(&ServerGameLoop::UpdateLoadingState, this), 
    std::bind(&ServerGameLoop::LeaveLoadingState, this));
    m_StateMachine.Add(ServerState::Active,std::bind(&ServerGameLoop::EnterActiveState, 
    this), std::bind(&ServerGameLoop::UpdateActiveState, this), 
    std::bind(&ServerGameLoop::LeaveActiveState, this));
    m_StateMachine.SwitchTo(ServerState::Idle);
    m_StateMachine.Update();
    return true;
}

void ServerGameLoop::Shutdown()
{
	m_StateMachine.Shutdown();
}

void ServerGameLoop::Update(double accFrameTime)
{
    if(accFrameTime > 5 * 1000)
    {
        if((ServerState)m_StateMachine.CurrentState() == ServerState::Loading)
            return;
        m_StateMachine.SwitchTo(ServerState::Loading);
        m_StateMachine.Update();
    }
}

void ServerGameLoop::FixedUpdate()
{

}

void ServerGameLoop::LateUpdate()
{

}

void ServerGameLoop::EnterIdleState()
{
    cout<<"EnterIdle..."<<endl;
}

void ServerGameLoop::UpdateIdleState()
{
    cout<<"UpdateIdle..."<<endl;
}

void ServerGameLoop::LeaveIdleState()
{
    cout<<"LeaveIdle..."<<endl;
}

void ServerGameLoop::EnterLoadingState()
{
    cout<<"EnterLoading..."<<endl;
}

void ServerGameLoop::UpdateLoadingState()
{
    cout<<"UpdateLoading..."<<endl;
}

void ServerGameLoop::LeaveLoadingState()
{
    cout<<"LeaveLoading..."<<endl;
}

void ServerGameLoop::EnterActiveState()
{
    cout<<"EnterActive..."<<endl;
}

void ServerGameLoop::UpdateActiveState()
{
    cout<<"UpdateActive..."<<endl;
}

void ServerGameLoop::LeaveActiveState()
{
    cout<<"LeaveActive..."<<endl;
}
