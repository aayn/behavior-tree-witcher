#pragma once
#include <behaviortree_cpp_v3/action_node.h>

#include <boost/algorithm/string.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

namespace Witcher {
namespace World {

enum class EnemyType { Human, Monster };
}  // namespace World
}  // namespace Witcher

namespace BT {
using namespace Witcher::World;
template <>
EnemyType convertFromString<EnemyType>(StringView str) {
  std::cout << "Converting from string to EnemyType..." << std::endl;
  std::string s = convertFromString<std::string>(str);
  // Remove preceding and trailing whitespaces
  boost::trim(s);
  if (s == "0")
    return EnemyType::Human;
  else if (s == "1")
    return EnemyType::Monster;
  throw RuntimeError("invalid EnemyType: ", s);
}

template<>
std::string toStr<EnemyType>(EnemyType e) {
  if (e == EnemyType::Human)
    return std::string("Human");
  return std::string("Monster");
}

}  // namespace BT

namespace Witcher {
namespace World {  // namespace World

std::default_random_engine generator;
std::bernoulli_distribution distribution(0.5);

class SpawnEnemy : public BT::AsyncActionNode {
 public:
  SpawnEnemy(const std::string& name, const BT::NodeConfiguration& config)
      : BT::AsyncActionNode(name, config) {}

  static BT::PortsList providedPorts() {
    return {BT::OutputPort<EnemyType>("enemy")};
  }

  BT::NodeStatus tick() override {
    EnemyType enemy;
    _halt_requested.store(false);
    if (name().compare("Second") == 0) return BT::NodeStatus::FAILURE;

    std::cout << name() << ": ";
    if (distribution(generator)) {
      std::cout << "Spawning a human..." << std::endl;
      enemy = EnemyType::Human;
    } else {
      std::cout << "Spawning a monster..." << std::endl;
      enemy = EnemyType::Monster;
    }

    // Spawning an enemy takes 250 ms
    int count = 25;
    while (!_halt_requested && count--)
      std::this_thread::sleep_for(std::chrono::milliseconds(10));

    setOutput<EnemyType>("enemy", enemy);
    return _halt_requested ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;
  }

  virtual void halt() override { _halt_requested.store(true); }

 private:
  std::atomic<bool> _halt_requested;
};

}  // namespace World
}  // namespace Witcher