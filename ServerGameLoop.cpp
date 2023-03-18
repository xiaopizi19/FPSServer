#include "ServerGameLoop.h"


ServerGameLoop::~ServerGameLoop()
{

}
bool ServerGameLoop::Init(string args)
{
    cout<<"Init..."<<endl;
    return true;
}

void ServerGameLoop::Shutdown()
{
	
}

void ServerGameLoop::Update()
{

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
