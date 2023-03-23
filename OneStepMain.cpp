#include <iostream>
#include <chrono>
#include <string.h>
#include <thread>
#include "ServerGameLoop.h"
using namespace std;

int main()
{
	cout<<"GameServerBegin..."<<endl;
	int loop_count = 0;
	int loop_accSeconds = 0;
	auto total_duration = 0;
	auto loop_start = chrono::high_resolution_clock::now();
	auto loop_end = chrono::high_resolution_clock::now();
	auto total_start = chrono::high_resolution_clock::now();
	bool isAbort = false;
	string ip = "127.0.0.1";
	ServerGameLoop *server = new ServerGameLoop();
	server->Init(ip); 
	while(!isAbort)
	{
		loop_end = chrono::high_resolution_clock::now();
		auto loop_duration = chrono::duration_cast<chrono::milliseconds>(loop_end 
		- loop_start).count();
		if(loop_duration > 16)
		{
			cout<<"Loop:"<<loop_count<< "loop_duation:"<<loop_duration<<"ms"<<endl;
			if(server)
				server->Update(total_duration);
			loop_start = chrono::high_resolution_clock::now();
		}
		
		auto total_end = chrono::high_resolution_clock::now();
		total_duration = chrono::duration_cast<chrono::milliseconds>(total_end 
		- total_start).count();
		if(total_duration > 10 * 1000)
		{
			server->Shutdown();
			break;
		}
		loop_count++;
	}
	auto total_end = chrono::high_resolution_clock::now();
	total_duration = chrono::duration_cast<chrono::seconds>(total_end-total_start).count();
	cout<<"Total duration::"<<total_duration<<"s"<<endl;
	cout<<"GameServerEnd..."<<endl;
	return 0;
}
