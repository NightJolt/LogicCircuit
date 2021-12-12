#include "Nodes/OrNode.h"

OrNode::OrNode() : DefaultNode(GetNodeName(), GetInPinCount(), GetOutPinCount()) {}

OrNode::~OrNode() noexcept = default;

void OrNode::Run() {
    Node::Run();

    out_pins[0].value = GetPinValue(0) or GetPinValue(1);
}

std::string OrNode::GetNodeName() const {
    return "OR";
}

int OrNode::GetInPinCount() const {
    return 2;
}

int OrNode::GetOutPinCount() const {
    return 1;
}