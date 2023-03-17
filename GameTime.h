#ifndef GameTime_H
#define GameTime_H

#include <cmath>
#include <iostream>

class GameTime
{
public:
	GameTime(int tickRate);
	float getTickDurationAsFraction() const;
	void setTime(int tick, float tickDuration);
	float durationSinceTick(int tick) const;
	void addDuration(float duration);
	static float getDuration(const GameTime& start, const GameTime& end);
private:
	int tickRate;        //Number of ticks per second.
	float tickInterval;  //Length of each world tick at current tickrate, e.g. 0.0166 if ticking at 60fps.
	int tick;            //Current tick
	float tickDuration;  // Duration of current tick
};
#endif
