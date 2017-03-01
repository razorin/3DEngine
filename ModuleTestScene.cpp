#include "Globals.h"
#include "Application.h"
#include "ModuleTestScene.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Animation.h"
#include "Model.h"
#include "SCube.h"
#include "MemLeaks.h"


ModuleTestScene::ModuleTestScene(const JSON_Value *json, bool active) : Module(json, active) 
{
}

ModuleTestScene::ModuleTestScene(const bool active) : Module(active) 
{
}

ModuleTestScene::~ModuleTestScene()
{
}

bool ModuleTestScene::Start() {

	primitives.push_back(cube = new SCube());

	importedLevel = new Level();
	importedLevel->Load("Models/street/", "Street.obj");
	//Test FindNode function
	Node* node = importedLevel->FindNode("g City_building_004");
	if (node == nullptr) {
		DLOG("Node not found");
	}
	else
	{
		DLOG("The name of the node is: %s", node->name.c_str());
	}
	//model = new Model();
	//model->Load("models/batman/","batman.obj");
	//model2->Load("Models/Magnetto/", "magnetto2.fbx");
	//model2 = new Model();


	return true;
}

update_status ModuleTestScene::PreUpdate() 
{
	return UPDATE_CONTINUE;
}

update_status ModuleTestScene::Update(float dt) 
{
	return UPDATE_CONTINUE;
}

update_status ModuleTestScene::PostUpdate() 
{
	return UPDATE_CONTINUE;
}

void ModuleTestScene::Draw()
{
	for (std::list<SPrimitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
	{
		(*it)->Draw();
	}

	if (model != nullptr)
		model->Draw();

	if (model2 != nullptr)
		model2->Draw();

	if (importedLevel != nullptr)
	{
		importedLevel->Draw();
	}
}

bool ModuleTestScene::CleanUp() {

	for (std::list<SPrimitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
	{
		RELEASE(*it);
	}

	if (model != nullptr)
	{
		model->Clear();
		RELEASE(model);
	}

	if (model2 != nullptr)
	{
		model2->Clear();
		RELEASE(model2);
	}

	if (importedLevel != nullptr)
	{
		importedLevel->Clear();
		RELEASE(importedLevel);
	}

	return true;
}