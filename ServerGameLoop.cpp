#include "ServerGameLoop.h"


ServerGameLoop::~ServerGameLoop()
{

}
bool ServerGameLoop::Init(string args)
{
    cout<<"Init..."<<endl;
    m_sm.Add(ServerState::Idle, &EnterIdleState, &UpdateIdleState,&LeaveIdleState);
    m_sm.Add(ServerState::Loading,&EnterLoadingState,&UpdateLoadingState,&LeaveLoadingState);
    m_sm.Add(ServerState::Active,&EnterActiveState,&UpdateActiveState,&LeaveActiveState);
    return true;
}

void ServerGameLoop::Shutdown()
{
	
}

void ServerGameLoop::Update(double accFrameTime)
{
    if(accFrameTime > 10 * 1000)
    {
        m_sm.SwitchTo(ServerState::Idle);
        m_sm.Update();
    }else if(accFrameTime > 20 * 1000)
    {
        m_sm.SwitchTo(ServerState::Loading);
        m_sm.Update();
    }else if(accFrameTime > 30 * 1000)
    {
        m_sm.SwitchTo(ServerState::Active);
        m_sm.Update();
        m_sm.ShutDown();
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
