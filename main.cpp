#include "FunEngine2D/core/include/globals.h"

#include "FunEngine2D/core/include/tools/Command.h"
#include "FunEngine2D/core/include/render/RenderQueue.h"
#include "FunEngine2D/core/include/render/WindowManager.h"
#include "FunEngine2D/core/include/Resources.h"
#include "FunEngine2D/core/include/Input.h"
#include "FunEngine2D/core/include/_Time.h"
#include "FunEngine2D/experimental/include/interactable/Interaction.h"
#include "FunEngine2D/experimental/include/object_system/Level.h"
#include "FunEngine2D/experimental/include/drawable/RoundedRect.h"

#include "Nodes/AndNode.h"
#include "Nodes/OrNode.h"
#include "Nodes/NotNode.h"
#include "Nodes/NandNode.h"
#include "Nodes/ButtonNode.h"
#include "Nodes/SwitchNode.h"
#include "Nodes/BulbNode.h"

#include "Graph.h"

int main () {
    fun::glob_init();

    fun::resources::load_font("lato_light", "lato_light.ttf");

    fun::WindowManager::Init("LogicCircuit");

    fun::WindowManager::WindowData* window_data = fun::WindowManager::main_window;
    window_data->window.resetGLStates();
    //window_data->window.setFramerateLimit(60);
    window_data->window.setVerticalSyncEnabled(false);

    ImGui::SFML::Init(window_data->window);

    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.FontGlobalScale = 2.f;

    fun::Level level;
    Graph graph;

    graph.SetClockSpeed(.01f);

    graph.AddNode(level.CreateLiveObject <AndNode> ());
    graph.AddNode(level.CreateLiveObject <AndNode> ());
    graph.AddNode(level.CreateLiveObject <NotNode> ());
    graph.AddNode(level.CreateLiveObject <NandNode> ());
    graph.AddNode(level.CreateLiveObject <NandNode> ());
    graph.AddNode(level.CreateLiveObject <BulbNode> ());
    graph.AddNode(level.CreateLiveObject <ButtonNode> ());
    graph.AddNode(level.CreateLiveObject <ButtonNode> ());
    graph.AddNode(level.CreateLiveObject <SwitchNode> ());
    graph.AddNode(level.CreateLiveObject <SwitchNode> ());

    // level.Init();

    while (window_data->window.isOpen()) {
        fun::input::listen();
        fun::time::recalculate();
        fun::Interaction::Update();
        ImGui::SFML::Update(window_data->window, fun::time::delta_time_object());

        window_data->PollEvents();
        window_data->world_view.move(fun::input::keyboard_2d() * sf::Vector2f(1, -1) * window_data->zoom * .5f);

        graph.Update();
        graph.Draw(window_data);

        //ImGui::ShowDemoWindow();
        level.ShowHierarchy();
        graph.ShowSettings();
        window_data->Display(sf::Color::Black);

        graph.Dispose();
        level.Dispose();
    }

    level.Unload();

    ImGui::SFML::Shutdown();

    return 0;
}