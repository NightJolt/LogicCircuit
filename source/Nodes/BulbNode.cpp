#include "Nodes/BulbNode.h"

const sf::Color BulbNode::UNLIT_COLOR = { 60, 60, 60 };
const sf::Color BulbNode::LIT_COLOR = { 255, 220, 100 };

BulbNode::BulbNode() : Node(GetInPinCount(), GetOutPinCount()) {
    shape.setOrigin(60.f, 60.f);
    shape.setRadius(60);
    shape.setOutlineThickness(0);
    shape.setFillColor(UNLIT_COLOR);

    UpdateShape({ 0, 0 });
}

BulbNode::~BulbNode() noexcept = default;

void BulbNode::Run() {
    Node::Run();

    shape.setFillColor(GetPinValue(0) ? LIT_COLOR : UNLIT_COLOR);
}

std::string BulbNode::GetNodeName() const {
    return "Bulb";
}

int BulbNode::GetInPinCount() const {
    return 1;
}

int BulbNode::GetOutPinCount() const {
    return 0;
}

void BulbNode::Draw(fun::wndmgr::Window* window) const {
    Node::Draw(window);

    window->DrawWorld(shape, Drawable_GetDrawingLayer());
}

void BulbNode::UpdateShape(const sf::Vector2f& p) {
    shape.setPosition(p);

    in_pins[0].SetPosition(shape.getPosition() - shape.getRadius() * sf::Vector2f { 1.f, 0 });
}

bool BulbNode::Interactable_Interaction(const sf::Vector2f& mouse_position) {
    return fun::math::magnitude(mouse_position - shape.getPosition()) < shape.getRadius();
}

const sf::Vector2f& BulbNode::GetPosition() const {
    return shape.getPosition();
}