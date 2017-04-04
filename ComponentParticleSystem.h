#ifndef COMPONENT_PARTICLE_SYSTEM_H
#define COMPONENT_PARTICLE_SYSTEM_H

#include "Component.h"
#include "Billboard.h"
#include "AssimpIncludes.h"

struct Particle {
	Particle(aiVector3D position, aiVector3D velocity, unsigned lifetime, Billboard billboard)
		: position(position), velocity(velocity), lifetime(lifetime), billboard(billboard) {}
	aiVector3D position;
	aiVector3D velocity;
	unsigned lifetime;
	std::vector<float3> quad;
	Billboard billboard;
};

class ComponentParticleSystem :
	public Component
{
private:
	typedef std::vector<Particle> ParticlePool;
	typedef std::vector<unsigned> ParticleList;

public:
	ComponentParticleSystem(GameObject* container, std::string id);
	~ComponentParticleSystem();

	void Init(unsigned maxParticles, const aiVector2D& emitArea, unsigned fallingTime, float fallingHeight,
		const char* textureFile, const float2 particleSize);
	void Clear();
	void Update(const float3 cameraPosition);
	void Draw();
	bool DrawGUI();

private:
	ParticlePool particles;
	ParticleList alive;
	ParticleList dead;

	unsigned maxParticles = 10;
	aiVector2D emitArea = { 1,1 };
	unsigned fallingTime = 0;
	float fallingHeight = 0.0f;
	unsigned texture = 0;
	float2 particleSize = { 1,1 };
	//unsigned accumElapsed = 0;

	aiVector3D* vertices = nullptr;
	aiVector2D* textureCoords = nullptr;
	aiColor4D* colors = nullptr;
	unsigned* indices = nullptr;
};

#endif // !COMPONENT_PARTICLE_SYSTEM_H