#include "Nodes/AndNode.h"

AndNode::AndNode() : DefaultNode(GetNodeName(), GetInPinCount(), GetOutPinCount()) {}

AndNode::~AndNode() noexcept = default;

void AndNode::Run() {
    Node::Run();

    out_pins[0].value = GetPinValue(0) and GetPinValue(1);
}

std::string AndNode::GetNodeName() const {
    return "AND";
}

int AndNode::GetInPinCount() const {
    return 2;
}

int AndNode::GetOutPinCount() const {
    return 1;
}