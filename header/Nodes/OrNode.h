#pragma once

#include "DefaultNode.h"

class OrNode final : public DefaultNode {
public:

    OrNode();
    ~OrNode() noexcept final;

    void Run() final;

    std::string GetNodeName() const final;
    int GetInPinCount() const final;
    int GetOutPinCount() const final;

private:
};