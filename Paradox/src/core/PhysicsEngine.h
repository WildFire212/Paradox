#pragma once
#include<vector>
#include"../Components/PhysicsObject.h"
using namespace Paradox::component; 
namespace Paradox {
	namespace core{

class PhysicsEngine
{
private: 
	std::vector<PhysicsObject*> m_PhysicsObjects; 
public : 
	//static instance cause we dont want to create an object of the class
	static PhysicsEngine& Instance();
	
	//add object
	void addPhysicsObject( PhysicsObject* physicsObject);
	//update all physics objects 
	void update(float deltaTime); 

	//getters 
	inline const int getNumObjects() const {
		return m_PhysicsObjects.size();
	}
	inline const PhysicsObject& getObject(int index) {
		return *m_PhysicsObjects[index];
	}

private:
	PhysicsEngine();
	void simulate(float deltaTime); 
	void handleCollisions(); 

};

} }
