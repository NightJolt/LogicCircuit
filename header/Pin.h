#pragma once

#include "../FunEngine2D/core/include/_Math.h"
#include "../FunEngine2D/core/include/globals.h"
#include "../FunEngine2D/core/include/render/WindowManager.h"
#include "../FunEngine2D/core/include/render/Drawable.h"
#include "../FunEngine2D/experimental/include/drawable/CurvedLine.h"
#include "../FunEngine2D/experimental/include/interactable/Interactable.h"
#include "../FunEngine2D/experimental/include/interactable/Interaction.h"

class Pin : public fun::Drawable, public fun::Interactable {
public:

    explicit Pin(void*);
    ~Pin() noexcept override = 0;

    virtual void Update();

    void SetPosition(const sf::Vector2f&);

    bool Interactable_Interaction(const sf::Vector2f&) final;

    void Draw(fun::wndmgr::Window*) const override;

    static constexpr float RADIUS = 10;
    static constexpr int VERTEX_COUNT = 12;

    static const sf::Color HOVERED_COLOR;
    static const sf::Color DEFAULT_COLOR;

    sf::CircleShape shape;
    fun::CurvedLine* wire;

    void* owner;
};

class OutPin final : public Pin {
public:

    explicit OutPin(void*);
    ~OutPin() final = default;

    void Update() final;

    bool value = false;
};

class InPin final : public Pin {
public:

    explicit InPin(void*);
    ~InPin() final = default;

    void Update() final;

    void Draw(fun::wndmgr::Window*) const override;

    OutPin* other = nullptr;
};