#include "Nodes/NotNode.h"

NotNode::NotNode() : DefaultNode(GetNodeName(), GetInPinCount(), GetOutPinCount()) {}

NotNode::~NotNode() noexcept = default;

void NotNode::Run() {
    Node::Run();

    out_pins[0].value = not GetPinValue(0);
}

std::string NotNode::GetNodeName() const {
    return "NOT";
}

int NotNode::GetInPinCount() const {
    return 1;
}

int NotNode::GetOutPinCount() const {
    return 1;
}