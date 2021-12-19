#include "Graph.h"

void Graph::AddNode(Node* node) {
    nodes.emplace_back(node);
}

void Graph::Update() {
    for (auto node : nodes) {
        node->Update();
    }

    delta_time_sum += fun::time::delta_time();

    while (delta_time_sum > clock_speed) {
        delta_time_sum -= clock_speed;

        for (auto node : nodes) {
            node->was_visited = false;
        }

        for (auto node : nodes) {
            if (node->GetOutPinCount() == 0) {
                VisitNode(node);
            }
        }
    }
}

void Graph::VisitNode(Node* node) {
    node->was_visited = true;

    for (auto& pin : node->in_pins) {
        if (pin.other) {
            auto other = reinterpret_cast <Node*> (pin.other->owner);

            if (other->was_visited) continue;

            VisitNode(other);
        }
    }

    node->Run();
}

void Graph::SetClockSpeed(float c_s) {
    clock_speed = c_s;
}

void Graph::Draw(fun::wndmgr::Window* window) const {
    for (auto node : nodes) {
        node->Draw(window);
    }
}

void Graph::Dispose() {
    for (auto rit = nodes.rbegin(); rit != nodes.rend(); rit++) {
        if ((*rit)->should_be_disposed) {
            for (auto node : nodes) {
                if (node == *rit) continue;

                for (auto& pin : node->in_pins) {
                    if (pin.other && pin.other->owner == *rit) {
                        pin.other = nullptr;
                        pin.wire = nullptr;
                    }
                }
            }

            nodes.erase((rit + 1).base());
        }
    }
}

void Graph::ShowSettings() {
    ImGui::Begin("Graph");

        ImGui::SliderFloat(" clock speed", &clock_speed, .001f, 1.f);

    ImGui::End();
}
