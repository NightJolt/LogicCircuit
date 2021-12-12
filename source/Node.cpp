#include "Node.h"

using namespace std;

const sf::Color Node::DEFAULT_COLOR = { 200, 200, 200 };

Node::Node(int in_pin_count, int out_pin_count) : fun::Drawable(), fun::LiveObject(), fun::Interactable() {
    in_pins.reserve(in_pin_count);
    out_pins.reserve(out_pin_count);

    for (int i = 0; i < in_pin_count; i++) {
        in_pins.emplace_back(this);
    }

    for (int i = 0; i < out_pin_count; i++) {
        out_pins.emplace_back(this);
    }

    SetLayer(0);
}

Node::~Node() noexcept = default;

void Node::Run() {
    // Can be optimised so this part only runs when wire value changes

    for (auto& pin : in_pins) {
        if (pin.other) {
            pin.wire->SetColor(pin.other->value ? sf::Color { 100, 255, 100 } : sf::Color { 255, 100, 100 });
        }
    }
}

void Node::Update() {
    for (auto& in_pin : in_pins) {
        in_pin.Update();
    }

    for (auto& out_pin : out_pins) {
        out_pin.Update();
    }

    if (Interactable_LeftPressed()) {
        drag_distance = { 0, 0 };

        drag_offset = fun::WindowManager::main_window->GetMouseWorldPosition() - GetPosition();

        SetLayer(GetLayer() + 100);
    }

    if (Interactable_LeftHold()) {
        const sf::Vector2f prev_pos = GetPosition();

        UpdateShape(fun::WindowManager::main_window->GetMouseWorldPosition() - drag_offset);

        drag_distance += GetPosition() - prev_pos;
    }
}

bool Node::GetPinValue(int index) {
    return in_pins[index].other && in_pins[index].other->value;
}

void Node::SetLayer(i32 new_layer) {
    Drawable_SetDrawingLayer(new_layer);
    Interactable_SetInteractionLayer(new_layer);

    i32 pin_layer = new_layer + 1;

    for (auto& in_pin : in_pins) {
        in_pin.Drawable_SetDrawingLayer(pin_layer);
        in_pin.Interactable_SetInteractionLayer(pin_layer);
    }

    for (auto& out_pin : out_pins) {
        out_pin.Drawable_SetDrawingLayer(pin_layer);
        out_pin.Interactable_SetInteractionLayer(pin_layer);
    }
}

i32 Node::GetLayer() const {
    return Drawable_GetDrawingLayer();
}

void Node::Draw(fun::WindowManager::WindowData* window_data) const {
    for (auto& in_pin : in_pins) {
        in_pin.Draw(window_data);
    }

    for (auto& out_pin : out_pins) {
        out_pin.Draw(window_data);
    }
}
