#pragma once

#include "Node.h"

#include "../FunEngine2D/experimental/include/drawable/RoundedRect.h"

class DefaultNode : public Node {
public:

    explicit DefaultNode(const std::string&, int, int);
    ~DefaultNode() noexcept override = 0;

    void Draw(fun::wndmgr::WindowData*) const final;

    void UpdateShape(const sf::Vector2f&) final;

    bool Interactable_Interaction(const sf::Vector2f&) final;

    const sf::Vector2f& GetPosition() const final;

protected:
    static const sf::Color LABEL_COLOR;
    static const sf::Vector2f INIT_SHAPE_SIZE;

    fun::RoundedRect shape;
    sf::Text label;
};