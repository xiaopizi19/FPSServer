#include <iostream>
#include <chrono>
#include <string.h>
#include <thread>
#include "StateMachine.h"
using namespace std;

int main()
{
	cout<<"GameServerBegin..."<<endl;
	int loop_count = 0;
	auto total_duration = 0;
	auto current_time = chrono::high_resolution_clock::now();
	auto last_time = chrono::high_resolution_clock::now();
	auto total_start = chrono::high_resolution_clock::now();
	bool isAbort = false;

	while(!isAbort)
	{
		current_time = chrono::high_resolution_clock::now();
		auto loop_duration = chrono::duration_cast<chrono::milliseconds>(current_time - last_time).count();
		//cout<<"Loop:"<<loop_count<< "loop_duation:"<<loop_duration<<"ms"<<endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		auto total_end = chrono::high_resolution_clock::now();
		total_duration = chrono::duration_cast<chrono::seconds>(total_end - total_start).count();
		if(total_duration > 10)
			break;
		loop_count++;
		last_time = current_time;
	}
	auto total_end = chrono::high_resolution_clock::now();
	total_duration = chrono::duration_cast<chrono::seconds>(total_end-total_start).count();
	cout<<"Total duration::"<<total_duration<<"s"<<endl;
	

	cout<<"GameServerEnd..."<<endl;
	return 0;
}
