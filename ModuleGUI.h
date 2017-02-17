#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "Module.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "IMGUI\imgui.h"
#include<list>

struct ImGuiTextBuffer;

struct AppConsole {
	ImGuiTextBuffer consoleBuffer;
	bool ScrollToBottom;

	void Clear() { consoleBuffer.clear(); }
	
	void AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
	{
		va_list args;
		va_start(args, fmt);
		consoleBuffer.appendv(fmt, args);
		consoleBuffer.append("\n");
		va_end(args);
		ScrollToBottom = true;
	}

	bool Draw()
	{
		bool open = true;
		ImGui::SetNextWindowSize(ImVec2((float)(App->window->screen_width * App->window->screen_size), (float)(App->window->screen_height * App->window->screen_size / 4)), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, (float)(App->window->screen_height * App->window->screen_size * 3 / 4)), ImGuiSetCond_Once);
		ImGui::Begin("Console", &open);
		if (ImGui::Button("Clear")) Clear();
		ImGui::Separator();
		ImGui::BeginChild("Scrolling");
		ImGui::TextUnformatted(consoleBuffer.begin());
		if (ScrollToBottom)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();
		ImGui::End();
		return open;
	}
};

class ModuleGUI :
	public Module
{
public:
	ModuleGUI(const JSON_Object *json = nullptr);
	~ModuleGUI();
	
	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void AddLog(const char* fmt, ...);
	bool DrawMainMenuBar();
	bool DrawPreferencesMenu();
	void AddFpsLog(float fps, float ms);
	

public:
	AppConsole console;

	int numFps = 0;
	std::list<float> fpsLog;
	int numMs = 0;
	std::list<float> msLog;

private:
	bool fullscreen = false;
	bool resizable = false;
	bool showPreferences = false;
	bool showConsole = true;
};

#endif // __MODULEGUI_H__