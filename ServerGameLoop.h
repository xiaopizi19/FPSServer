#ifndef ServerGameLoop_H
#define ServerGameLoop_H

#include <iostream>
#include "IGameLoop.h"
#include "StateMachine.h"
using namespace std;

class ServerGameLoop : public IGameLoop
{
public:
	bool Init(string args);
	void Shutdown();
	void Update(double accFrameTime);
	void FixedUpdate();
	void LateUpdate();
	~ServerGameLoop();
private:
	void EnterIdleState();
	void UpdateIdleState();
	void LeaveIdleState();
	
	void EnterLoadingState();
	void UpdateLoadingState();
	void LeaveLoadingState();

	void EnterActiveState();
	void UpdateActiveState();
	void LeaveActiveState();	
private:
	StateMachine<ServerState> m_sm;
};
#endif
