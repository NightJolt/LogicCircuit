#include "FunEngine2D/core/include/globals.h"

#include "FunEngine2D/core/include/tools/Command.h"
#include "FunEngine2D/core/include/render/RenderQueue.h"
#include "FunEngine2D/core/include/render/WindowManager.h"
#include "FunEngine2D/core/include/Resources.h"
#include "FunEngine2D/core/include/Input.h"
#include "FunEngine2D/core/include/_Time.h"
#include "FunEngine2D/core/include/tools/Debugger.h"
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

    fun::wndmgr::init(fun::wndmgr::WindowData("LogicCircuit"));

    fun::wndmgr::Window* window = fun::wndmgr::main_window;
    window->render_window.resetGLStates();
    //window->window.setFramerateLimit(60);
    window->render_window.setVerticalSyncEnabled(false);

    ImGui::SFML::Init(window->render_window);

    // ImGuiIO& imgui_io = ImGui::GetIO();
    // imgui_io.FontGlobalScale = 2.f;

    fun::Level level("logic circuit");
    Graph graph;

    graph.SetClockSpeed(.01f);

    graph.AddNode(level.CreateLiveObject <AndNode> ("AND"));
    graph.AddNode(level.CreateLiveObject <AndNode> ("AND"));
    graph.AddNode(level.CreateLiveObject <NotNode> ("NOT"));
    graph.AddNode(level.CreateLiveObject <NandNode> ("NAND"));
    graph.AddNode(level.CreateLiveObject <NandNode> ("NAND"));
    graph.AddNode(level.CreateLiveObject <BulbNode> ("BULB"));
    graph.AddNode(level.CreateLiveObject <ButtonNode> ("BUTTON"));
    graph.AddNode(level.CreateLiveObject <ButtonNode> ("BUTTON"));
    graph.AddNode(level.CreateLiveObject <SwitchNode> ("SWITCH"));
    graph.AddNode(level.CreateLiveObject <SwitchNode> ("SWITCH"));

    // level.Init();

    while (window->render_window.isOpen()) {
        fun::input::listen();
        fun::time::recalculate();
        fun::Interaction::Update();
        ImGui::SFML::Update(window->render_window, fun::time::delta_time_object());

        window->PollEvents();
        window->world_view.move(fun::input::keyboard_2d() * sf::Vector2f(1, -1) * window->zoom * .5f);

        graph.Update();
        graph.Draw(window);

        ImGui::ShowDemoWindow();
        level.ShowHierarchy();
        graph.ShowSettings();

        fun::debugger::display();
        window->Display(sf::Color::Black);

        graph.Dispose();
        level.Dispose();
    }

    level.Unload();

    ImGui::SFML::Shutdown();

    return 0;
}