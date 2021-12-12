#pragma once

#include "../FunEngine2D/core/include/globals.h"
#include "../FunEngine2D/core/include/_Time.h"
#include "../FunEngine2D/core/include/render/WindowManager.h"
#include "../FunEngine2D/experimental/include/object_system/Level.h"

#include "Node.h"

class Graph {
public:

    Graph() = default;
    ~Graph() = default;

    void AddNode(Node*);
    void Update();
    void SetClockSpeed(float);
    void Draw(fun::WindowManager::WindowData*) const;
    void Dispose();
    void ShowSettings();

private:

    void VisitNode(Node*);

    std::vector <Node*> nodes;

    float clock_speed = .1f;
    float delta_time_sum = 0;
};