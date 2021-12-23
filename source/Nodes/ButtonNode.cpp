#include "Nodes/ButtonNode.h"

const sf::Color ButtonNode::DISABLED_COLOR = { 255, 50, 50 };
const sf::Color ButtonNode::ENABLED_COLOR = { 50, 255, 50 };

ButtonNode::ButtonNode() : Node(GetInPinCount(), GetOutPinCount()) {
    shape.setOrigin(60.f, 60.f);
    shape.setRadius(60);
    shape.setOutlineThickness(0);
    shape.setFillColor(DISABLED_COLOR);

    UpdateShape({ 0, 0 });
}

ButtonNode::~ButtonNode() noexcept = default;

void ButtonNode::Run() {}

std::string ButtonNode::GetNodeName() const {
    return "Button";
}

int ButtonNode::GetInPinCount() const {
    return 0;
}

int ButtonNode::GetOutPinCount() const {
    return 1;
}

void ButtonNode::Draw(fun::wndmgr::Window* window) const {
    Node::Draw(window);

    window->DrawWorld(shape, Drawable_GetDrawingLayer());
}

void ButtonNode::Update() {
    Node::Update();

    out_pins[0].value = Interactable_RightHold();

    shape.setFillColor(out_pins[0].value ? ENABLED_COLOR : DISABLED_COLOR);
}

void ButtonNode::UpdateShape(const sf::Vector2f& p) {
    shape.setPosition(p);

    out_pins[0].SetPosition(shape.getPosition() + shape.getRadius() * sf::Vector2f { 1.f, 0 });
}

bool ButtonNode::Interactable_Interaction(const sf::Vector2f& mouse_position) {
    return fun::math::magnitude(mouse_position - shape.getPosition()) < shape.getRadius();
}

const sf::Vector2f& ButtonNode::GetPosition() const {
    return shape.getPosition();
}
