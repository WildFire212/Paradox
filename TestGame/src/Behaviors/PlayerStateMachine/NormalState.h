#pragma once
#include"PlayerState.h"
class NormalState : public PlayerState {
public:
	enum NormalStates {
		Running , 
		Walking 
	};

	~NormalState();
	virtual void entry(PlayerBehavior* playerBehavior) override;
	virtual void execute(PlayerBehavior* playerBehavior, float deltaTime);
	virtual void exit(PlayerBehavior* playerBehavior) override;
	static NormalState* Instance();

private: 
	NormalStates m_NormalState; 
	
	NormalState();
	void run(PlayerBehavior* playerBehavior,float deltaTime);
	void walk(PlayerBehavior* playerBehavior,float deltaTime);

};