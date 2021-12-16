#pragma once

#include "Node.h"

#include "../FunEngine2D/experimental/include/drawable/RoundedRect.h"

class SwitchNode final : public Node {
public:

    SwitchNode();
    ~SwitchNode() noexcept final;

    void Draw(fun::wndmgr::WindowData*) const final;

    void Run() final;

    void Update() final;
    void UpdateShape(const sf::Vector2f&) final;

    bool Interactable_Interaction(const sf::Vector2f&) final;

    [[nodiscard]] std::string GetNodeName() const final;
    [[nodiscard]] int GetInPinCount() const final;
    [[nodiscard]] int GetOutPinCount() const final;

    const sf::Vector2f& GetPosition() const final;

private:
    static const sf::Color DISABLED_COLOR;
    static const sf::Color ENABLED_COLOR;

    fun::RoundedRect shape;
};