#include "Pin.h"

const sf::Color Pin::HOVERED_COLOR = { 255, 100, 100 };
const sf::Color Pin::DEFAULT_COLOR = { 100, 100, 100 };

Pin::Pin(void* node) : shape(sf::CircleShape(RADIUS, VERTEX_COUNT)), wire(nullptr), owner(node), fun::Interactable() {
    shape.setOrigin(sf::Vector2f(1, 1) * RADIUS);
    shape.setFillColor(DEFAULT_COLOR);
}

Pin::~Pin() noexcept {
    delete wire;
}

void Pin::Update() {
    if (Interactable_HoverEnter()) {
        shape.setFillColor(HOVERED_COLOR);
    }

    if (Interactable_HoverExit()) {
        shape.setFillColor(DEFAULT_COLOR);
    }

    if (Interactable_LeftPressed()) {
        if (!wire) {
            wire = new fun::CurvedLine;

            wire->SetColor({ 100, 100, 100 });
        }
    }

    if (Interactable_LeftHold()) {
        wire->SetPoints(shape.getPosition() + sf::Vector2f { is_type_of(OutPin, this) ? RADIUS : -RADIUS, 0 }, fun::wndmgr::main_window->GetMouseWorldPosition());
    }
}

void Pin::SetPosition(const sf::Vector2f& p) {
    shape.setPosition(p);
}

void Pin::Draw(fun::wndmgr::WindowData* window_data) const {
    window_data->AddWorld(shape, Drawable_GetDrawingLayer());

    if (wire) window_data->AddWorld(*wire, 1000000);
}

bool Pin::Interactable_Interaction(const sf::Vector2f& mouse_position) {
    return fun::math::magnitude(mouse_position - shape.getPosition()) <= RADIUS;
}

OutPin::OutPin(void* node) : Pin(node) {}

void OutPin::Update() {
    Pin::Update();

    if (Interactable_LeftReleased()) {
        auto* target = fun::Interaction::ObjectAtPos(fun::wndmgr::main_window->GetMouseWorldPosition());
        auto* other = dynamic_cast <InPin*> (target);

        if (target && other) {
            other->other = this;
            other->wire = wire;
        } else {
            delete wire;
        }

        wire = nullptr;
    }
}

InPin::InPin(void* node) : Pin(node) {}

void InPin::Update() {
    Pin::Update();

    if (Interactable_LeftPressed()) {
        other = nullptr;
    }

    if (Interactable_LeftReleased()) {
        auto* target = fun::Interaction::ObjectAtPos(fun::wndmgr::main_window->GetMouseWorldPosition());

        other = dynamic_cast <OutPin*> (target);

        if (!(target && other)) {
            delete wire;

            wire = nullptr;
        }
    }
}

void InPin::Draw(fun::wndmgr::WindowData* window_data) const {
    if (other) {
        wire->SetPoints(shape.getPosition() - sf::Vector2f { RADIUS, 0 }, other->shape.getPosition() + sf::Vector2f { RADIUS, 0 });
    }

    Pin::Draw(window_data);
}
