#pragma once

#include "DefaultNode.h"

class AndNode final : public DefaultNode {
public:

    AndNode();
    ~AndNode() noexcept final;

    void Run() final;

    std::string GetNodeName() const final;
    int GetInPinCount() const final;
    int GetOutPinCount() const final;

private:
};