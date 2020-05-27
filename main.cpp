#include <behaviortree_cpp_v3/blackboard.h>
#include <behaviortree_cpp_v3/bt_factory.h>

#include <functional>
#include <iostream>

#include "geralt.h"
#include "world.h"

namespace WW = Witcher::World;
namespace WG = Witcher::Geralt;

int main() {
  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<WW::SpawnEnemy>("SpawnEnemy");
  factory.registerNodeType<WG::Geralt>("Geralt");

  auto tree = factory.createTreeFromFile("./witcher_bt.xml");

  while (tree.tickRoot() != (BT::NodeStatus::SUCCESS)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  // for (int i = 0; i != 100; i++)
  //   std::cout << ww::distribution(ww::generator) << std::endl;

  return 0;
}