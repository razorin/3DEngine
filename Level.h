#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Globals.h"
#include <vector>
#include "assimp\vector3.h"
#include "assimp/scene.h"
#include "Mesh.h"
#include "MemLeaks.h"
#include "MathGeoLib\include\MathGeoLib.h"


struct Node {
	std::string name;
	float3 position = float3::zero;
	Quat rotation = Quat::identity;
	float3 scale = float3::one;
	float4x4 localTransform = float4x4::identity;
	float4x4 globalTransform = float4x4::identity;
	std::vector<unsigned> meshes;
	Node* parent = nullptr;
	std::vector<Node*> childs;

	Node() {};
	~Node();
};

struct Material {
	aiColor4D ambient = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	aiColor4D diffuse = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	aiColor4D specular = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	unsigned num_vertices = 0;
	unsigned* indices;
	unsigned num_indices = 0;
};

class Level
{
public:
	Level();
	~Level();

	void Load(const char* path, const char* file);
	void RecursiveNodeRead(Node* node, aiNode& aiNode, Node* parentNode);
	void RecursiveCalcTransforms(Node* node);
	const void PrintNodeInfo(Node& node);
	void Draw(Node* node);
	void RecursiveNodeRelease(Node* node);
	void Clear();

	unsigned GetNumMeshes() const { return meshes.size(); }
	unsigned GetNumMaterials() const { return materials.size(); }

	Mesh& GetMesh(unsigned index) { return *meshes[index]; }
	//const Mesh& GetMesh(unsigned index) { return meshes[index]; }

	Node* GetRootNode() { return root; }
	//const Node* GetRootNode() { return root; }

	Node* FindNode(const char* name);
	Node* RecursiveSearchNode(const char* name, Node* node);
	bool LinkNode(Node* node, Node* parent);

	void DrawHierarchy(Node * node);
	void TransformHierarchy();

public:
	Node* root = nullptr;
	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;

	uint* imageNames;

	int frame = 0;
	int maxFrames;

	bool print = false;
};

#endif /* _LEVEL_H_ */