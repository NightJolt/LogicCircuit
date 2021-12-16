#pragma once

#include "../FunEngine2D/core/include/globals.h"

#include "../FunEngine2D/core/include/Resources.h"
#include "../FunEngine2D/experimental/include/object_system/LiveObject.h"
#include "../FunEngine2D/experimental/include/interactable/Interactable.h"
#include "../FunEngine2D/experimental/include/interactable/Interaction.h"

#include "Pin.h"

class Node : public fun::Drawable, public fun::LiveObject, public fun::Interactable {
public:

    Node(int, int);
    ~Node() noexcept override = 0;

    void Update() override;

    virtual void UpdateShape(const sf::Vector2f&) = 0;
    virtual void Run();

    bool GetPinValue(int);

    [[nodiscard]] virtual std::string GetNodeName() const = 0;
    [[nodiscard]] virtual int GetInPinCount() const = 0;
    [[nodiscard]] virtual int GetOutPinCount() const = 0;

    void SetLayer(i32);
    i32 GetLayer() const;

    virtual const sf::Vector2f& GetPosition() const = 0;

    void Draw(fun::wndmgr::WindowData*) const override;

    std::vector <InPin> in_pins;
    std::vector <OutPin> out_pins;

    bool was_visited; // used by Graph.h

protected:

    static const sf::Color DEFAULT_COLOR;

    sf::Vector2f drag_offset;
    sf::Vector2f drag_distance;
};