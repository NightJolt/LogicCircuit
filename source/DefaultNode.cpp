#include "DefaultNode.h"

const sf::Color DefaultNode::LABEL_COLOR = { 54, 54, 54 };
const sf::Vector2f DefaultNode::INIT_SHAPE_SIZE = { 80, 40 };

DefaultNode::DefaultNode(const std::string& name, int in_pin_count, int out_pin_count) : Node(in_pin_count, out_pin_count) {
    label.setFillColor(LABEL_COLOR);
    label.setFont(fun::resources::get_font("lato_light"));

    label.setString(name);
    const sf::Vector2f label_size = sf::Vector2f(label.getGlobalBounds().width, label.getGlobalBounds().height);
    label.setOrigin(label_size * sf::Vector2f(.5f, 1.f));

    sf::Vector2f shape_size = INIT_SHAPE_SIZE;
    shape_size.x += label_size.x;
    shape_size.y *= (float)(std::max(in_pin_count, out_pin_count) + 1);

    shape.SetFillColor(DEFAULT_COLOR);
    shape.SetSize(shape_size);

    UpdateShape({ 0, 0 });
}

DefaultNode::~DefaultNode() noexcept = default;

void DefaultNode::Draw(fun::wndmgr::WindowData* window_data) const {
    Node::Draw(window_data);

    window_data->AddWorld(shape, Drawable_GetDrawingLayer());
    window_data->AddWorld(label, Drawable_GetDrawingLayer() + 2);
}

void DefaultNode::UpdateShape(const sf::Vector2f& p) {
    shape.SetPosition(p);
    label.setPosition(p);

    const sf::Vector2f& half_shape_size = shape.GetSize() * .5f;

    const sf::Vector2f in_start_pnt = shape.GetPosition() - half_shape_size;
    const sf::Vector2f out_start_pnt = shape.GetPosition() + half_shape_size * sf::Vector2f(1, -1);

    const float in_step = shape.GetSize().y / (float)(in_pins.size() + 1);
    const float out_step = shape.GetSize().y / (float)(out_pins.size() + 1);

    auto pos = in_start_pnt;

    for (auto& in_pin : in_pins) {
        pos.y += in_step;

        in_pin.SetPosition(pos);
    }

    pos = out_start_pnt;

    for (auto& out_pin : out_pins) {
        pos.y += out_step;

        out_pin.SetPosition(pos);
    }
}

bool DefaultNode::Interactable_Interaction(const sf::Vector2f& mouse_position) {
    return fun::math::abs(mouse_position - shape.GetPosition()) < shape.GetSize() * .5f;
}

const sf::Vector2f& DefaultNode::GetPosition() const {
    return shape.GetPosition();
}