#ifndef __MODULEANIMATION_H__
#define __MODULEANIMATION_H__

#include "Globals.h"
#include "Module.h"
#include <map>
#include <vector>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp\anim.h"
#include "MathGeoLib\include\MathGeoLib.h"



class ModuleAnimation : public Module
{

private:
	struct NodeAnim
	{
		aiString name;
		float3* positions = nullptr;
		Quat* rotations = nullptr;
		float3* scales = nullptr;
		uint numPositions = 0;
		uint numRotations = 0;
		uint numScales = 0;
		uint numKeyframes = 0;
	};

	struct Anim
	{
		aiString name;
		uint duration = 0;
		uint numChannels = 0;
		NodeAnim* channels = nullptr;
	};

	struct AnimInstance
	{
		Anim* animation;
		uint id = 0;
		uint time = 0;
		bool loop = true;
		AnimInstance* next = nullptr;
		uint blendDuration = 0;
		uint blendTime = 0;
	};

	typedef std::map<std::string, Anim*> AnimationMap;
	typedef std::vector<AnimInstance*> InstanceList;
	typedef std::vector<uint> HoleList;

	AnimationMap animations;
	InstanceList instances;
	HoleList holes;

public:
	ModuleAnimation();
	~ModuleAnimation();

	bool Init();
	bool Start();
	void Load(const char* path, const char* file);
	bool CleanUp();
	update_status Update(float dt = 0);

	uint Play(const char* animName);
	void Stop(uint instanceId);
	void BlendTo(uint instanceId, const char* newAnim, uint blendTime);
	bool GetTransform(uint instanceId, const char* channelName, float3& position, Quat& rotation, float3& scale);
	float3 InterpVector3D(const float3& first, const float3& second, float lambda) const;
	Quat InterpQuaternion(const Quat& first, const Quat& second, float lambda) const;

};

#endif