#ifndef IGameLoop_H
#define IGameLoop_H
#include <string>
class IGameLoop
{
public:
	virtual bool Init(std::string args[])=0;
	virtual void Shutdown() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void LateUpdate() = 0;
	virtual ~IGameLoop(){}
};
#endif
