#pragma once

#include "Node.h"

class BulbNode final : public Node {
public:

    BulbNode();
    ~BulbNode() noexcept final;

    void Draw(fun::wndmgr::Window*) const final;

    void Run() final;

    void UpdateShape(const sf::Vector2f&) final;

    bool Interactable_Interaction(const sf::Vector2f&) final;

    [[nodiscard]] std::string GetNodeName() const final;
    [[nodiscard]] int GetInPinCount() const final;
    [[nodiscard]] int GetOutPinCount() const final;

    const sf::Vector2f& GetPosition() const final;

private:
    static const sf::Color UNLIT_COLOR;
    static const sf::Color LIT_COLOR;

    sf::CircleShape shape;
};