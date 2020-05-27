#pragma once
#include <behaviortree_cpp_v3/action_node.h>

#include "world.h"

namespace Witcher {
namespace Geralt {

enum class SwordType { Steel, Silver };

class Geralt : public BT::SyncActionNode {
 public:
  Geralt(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config) {}

  static BT::PortsList providedPorts() {
    return {BT::InputPort<World::EnemyType>("enemy")};
  }

  BT::NodeStatus tick() override {
    BT::Optional<World::EnemyType> enemy = getInput<World::EnemyType>("enemy");
    SwordType sword;
    if (enemy == World::EnemyType::Human) {
      std::cout << name() << ": Drawing sword of type steel..." << std::endl;
      sword = SwordType::Steel;
    } else if (enemy == World::EnemyType::Monster) {
      std::cout << name() << ": Drawing sword of type silver..." << std::endl;
      sword = SwordType::Silver;
    } else {
      throw BT::RuntimeError("invalid EnemyType, the categories are mutually exclusive: ");
      return BT::NodeStatus::FAILURE;
    }
    return BT::NodeStatus::SUCCESS;
  }
};
}  // namespace Geralt
}  // namespace Witcher