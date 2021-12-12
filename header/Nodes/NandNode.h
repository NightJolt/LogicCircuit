#pragma once

#include "DefaultNode.h"

class NandNode final : public DefaultNode {
public:

    NandNode();
    ~NandNode() noexcept final;

    void Run() final;

    std::string GetNodeName() const final;
    int GetInPinCount() const final;
    int GetOutPinCount() const final;

private:
};