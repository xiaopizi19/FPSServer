#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "StateMachine.h"
using namespace std;
#define MY_TIMEV struct timeval
MY_TIMEV clockGetTime(clockid_t _tclock_id)
{
	struct timespec stTime;
	clock_gettime(_tclock_id, &stTime);
	MY_TIMEV stRet;
	stRet.tv_sec = stTime.tv_sec;
	stRet.tv_usec = stTime.tv_nsec/1000;
	return stRet;
}
int main()
{
	cout<<"Begin..."<<endl;
	MY_TIMEV tmp = {0};
	int timeOffset = 0;
	int timeOffset1 = 0;
	tmp = clockGetTime(CLOCK_MONOTONIC);
	timeOffset = tmp.tv_sec*1000+tmp.tv_usec/1000;
	memset(&tmp,0,sizeof(tmp));
	tmp = clockGetTime(CLOCK_MONOTONIC);
	timeOffset1 = tmp.tv_sec*1000+tmp.tv_usec/1000;
	cout<<timeOffset1 - timeOffset<<endl;
        
	StateMachine<ServerState> sm;
	sm.Add(ServerState::Idle,[](){cout<<"Enter idle\n";},
	[](){cout<<"Update Idle\n";},[](){cout<<"Leave Idle\n";});
		
	sm.Add(ServerState::Loading,[](){cout<<"Enter Loading\n";},
	[](){cout<<"Update Loading\n";},[](){cout<<"Leave Loading\n";});
	sm.SwitchTo(ServerState::Idle);
	sm.Update();
	sm.SwitchTo(ServerState::Loading);
	sm.Update();
	sm.ShutDown();
	cout<<"End..."<<endl;
	return 0;
}
