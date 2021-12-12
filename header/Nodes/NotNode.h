#pragma once

#include "DefaultNode.h"

class NotNode final : public DefaultNode {
public:

    NotNode();
    ~NotNode() noexcept final;

    void Run() final;

    std::string GetNodeName() const final;
    int GetInPinCount() const final;
    int GetOutPinCount() const final;

private:
};