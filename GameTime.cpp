#include "GameTime.h"

GameTime::GameTime(int tickRate)
{
	this->tickRate = tickRate;
	this->tickInterval = 1.0f / tickRate;
	this->tick = 1;
	this->tickDuration = 0;
}

float GameTime::getTickDurationAsFraction() const 
{
	return tickDuration / tickInterval;
}

void GameTime::setTime(int tick, float tickDuration)
{
	this->tick = tick;
	this->tickDuration = tickDuration;
}

float GameTime::durationSinceTick(int tick) const
{
	return (this->tick - tick) * tickInterval + tickDuration;
}

void GameTime::addDuration(float duration)
{
	tickDuration += duration;
	int deltaTicks = floor(tickDuration * (float)tickRate);
	tick += deltaTicks;
	tickDuration = fmod(tickDuration, tickInterval);
}

float GameTime::getDuration(const GameTime& start, const GameTime& end)
{
	if(start.tickRate != end.tickRate)
	{
		std::cerr << "Trying to compare time with different tick rates("<< start.tickRate<<")"<<end.tickRate<<std::endl;
		return 0;
	}
	float result = (end.tick - start.tick) * start.tickInterval + end.tickDuration - start.tickDuration;
	return result;
}
