#define BOOST_TEST_MODULE performance_test
#include "../Game.cpp"
#include "../NegamaxBot.cpp"
#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

const std::string testDirectory = "test-data/performance/";
const std::vector<std::string> testnames = {
    "Test_L1_R1", "Test_L1_R2", "Test_L1_R3", "Test_L2_R1", "Test_L2_R2", "Test_L3_R1",
};
const std::string beginEasy = testnames[0];
const std::string beginMedium = testnames[1];
const std::string beginHard = testnames[2];
const std::string middleEasy = testnames[3];
const std::string middleMedium = testnames[4];
const std::string endEasy = testnames[5];

std::vector<std::pair<std::string, int>> samples(std::string name) {
  std::ifstream ifs;
  ifs.open(name);
  if (!ifs)
    throw name + " does not exist";

  std::vector<std::pair<std::string, int>> res;
  for (std::pair<std::string, int> sample; ifs >> sample.first >> sample.second;) {
    res.push_back(sample);
  }

  ifs.close();
  return res;
}

BOOST_AUTO_TEST_CASE(endEasyTest, *boost::unit_test::timeout(10)) {
  const std::string name = endEasy;
  const auto bot = std::make_unique<NegamaxBot>();

  for (const auto &sample : samples(testDirectory + name)) {
    Game game(sample.first);

    int actualScore = bot->solve(game);
    int expectedScore = sample.second;

    BOOST_REQUIRE_EQUAL(actualScore, expectedScore);
  }
}

BOOST_AUTO_TEST_CASE(middleEasyTest, *boost::unit_test::timeout(10)) {
  const std::string name = middleEasy;
  const auto bot = std::make_unique<NegamaxBot>();

  for (const auto &sample : samples(testDirectory + name)) {
    Game game(sample.first);

    int actualScore = bot->solve(game);
    int expectedScore = sample.second;

    BOOST_REQUIRE_EQUAL(actualScore, expectedScore);
  }
}

BOOST_AUTO_TEST_CASE(beginEasyTest, *boost::unit_test::timeout(10)) {
  const std::string name = beginEasy;
  const auto bot = std::make_unique<NegamaxBot>();

  for (const auto &sample : samples(testDirectory + name)) {
    Game game(sample.first);

    int actualScore = bot->solve(game);
    int expectedScore = sample.second;

    BOOST_REQUIRE_EQUAL(actualScore, expectedScore);
  }
}

// BOOST_AUTO_TEST_CASE(middleMediumTest, *boost::unit_test::timeout(10)) {
//   const std::string name = middleMedium;
//   const auto bot = std::make_unique<NegamaxBot>();

//   for (const auto &sample : samples(testDirectory + name)) {
//     Game game(sample.first);

//     int actualScore = bot->solve(game);
//     int expectedScore = sample.second;

//     BOOST_REQUIRE_EQUAL(actualScore, expectedScore);
//   }
// }

// BOOST_AUTO_TEST_CASE(beginMediumTest, *boost::unit_test::timeout(10)) {
//   const std::string name = beginMedium;
//   const auto bot = std::make_unique<NegamaxBot>();

//   for (const auto &sample : samples(testDirectory + name)) {
//     Game game(sample.first);

//     int actualScore = bot->solve(game);
//     int expectedScore = sample.second;

//     BOOST_REQUIRE_EQUAL(actualScore, expectedScore);
//   }
// }

BOOST_AUTO_TEST_CASE(beginHardTest, *boost::unit_test::timeout(60)) {
  const std::string name = beginHard;
  const auto bot = std::make_unique<NegamaxBot>();

  int count = 0;
  for (const auto &sample : samples(testDirectory + name)) {
    Game game(sample.first);

    int actualScore = bot->solve(game);
    int expectedScore = sample.second;

    BOOST_REQUIRE_EQUAL(actualScore, expectedScore);
    count++;
    std::cout << "beginHard: " << count << std::endl;
  }
}