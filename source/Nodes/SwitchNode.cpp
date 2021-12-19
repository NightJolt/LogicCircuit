#include "Nodes/SwitchNode.h"

const sf::Color SwitchNode::DISABLED_COLOR = { 255, 50, 50 };
const sf::Color SwitchNode::ENABLED_COLOR = { 50, 255, 50 };

SwitchNode::SwitchNode() : Node(GetInPinCount(), GetOutPinCount()) {
    shape.SetSize({ 120.f, 120.f });
    shape.SetFillColor(DISABLED_COLOR);

    UpdateShape({ 0, 0 });
}

SwitchNode::~SwitchNode() noexcept = default;

void SwitchNode::Run() {}

std::string SwitchNode::GetNodeName() const {
    return "Switch";
}

int SwitchNode::GetInPinCount() const {
    return 0;
}

int SwitchNode::GetOutPinCount() const {
    return 1;
}

void SwitchNode::Draw(fun::wndmgr::Window* window) const {
    Node::Draw(window);

    window->AddWorld(shape, Drawable_GetDrawingLayer());
}

void SwitchNode::Update() {
    Node::Update();

    if (Interactable_RightPressed()) {
        out_pins[0].value ^= 1;

        shape.SetFillColor(out_pins[0].value ? ENABLED_COLOR : DISABLED_COLOR);
    }
}

void SwitchNode::UpdateShape(const sf::Vector2f& p) {
    shape.SetPosition(p);

    out_pins[0].SetPosition(shape.GetPosition() + shape.GetSize() * sf::Vector2f { .5f, 0 });
}

bool SwitchNode::Interactable_Interaction(const sf::Vector2f& mouse_position) {
    return fun::math::abs(mouse_position - shape.GetPosition()) < shape.GetSize() * .5f;
}

const sf::Vector2f& SwitchNode::GetPosition() const {
    return shape.GetPosition();
}