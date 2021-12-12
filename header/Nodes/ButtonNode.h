#pragma once

#include "Node.h"

class ButtonNode final : public Node {
public:

    ButtonNode();
    ~ButtonNode() noexcept final;

    void Draw(fun::WindowManager::WindowData*) const final;

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

    sf::CircleShape shape;
};