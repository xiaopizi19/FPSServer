#ifndef IGameLoop_H
#define IGameLoop_H
#include <string>

using namespace std;
class IGameLoop
{
public:
	virtual bool Init(string args)=0;
	virtual void Shutdown() = 0;
	virtual void Update(double accFrameTime) = 0;
	virtual void FixedUpdate() = 0;
	virtual void LateUpdate() = 0;
	virtual ~IGameLoop(){}
};
#endif
