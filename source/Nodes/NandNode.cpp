#include "Nodes/NandNode.h"

NandNode::NandNode() : DefaultNode(GetNodeName(), GetInPinCount(), GetOutPinCount()) {}

NandNode::~NandNode() noexcept = default;

void NandNode::Run() {
    Node::Run();

    out_pins[0].value = (not GetPinValue(0)) and (not GetPinValue(1));
}

std::string NandNode::GetNodeName() const {
    return "NAND";
}

int NandNode::GetInPinCount() const {
    return 2;
}

int NandNode::GetOutPinCount() const {
    return 1;
}