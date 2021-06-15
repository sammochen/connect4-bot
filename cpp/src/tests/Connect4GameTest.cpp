#define BOOST_TEST_MODULE connect4_test
#include "../CustomOStreams.h"
#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

// BOOST_AUTO_TEST_CASE(makeSmallGame, *boost::unit_test::timeout(1)) {
//   const auto g = std::make_unique<Game>("1247");
//   std::vector<std::vector<int>> expected = {
//       {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
//       {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {1, 2, 0, 1, 0, 0, 2}};
//   BOOST_CHECK_EQUAL(g->getBoard(), expected);
// }

// BOOST_AUTO_TEST_CASE(makeBigGame, *boost::unit_test::timeout(1)) {
//   const auto g =
//       std::make_unique<Game>("3575316255751336464276636772271112");
//   std::vector<std::vector<int>> expected = {
//       {0, 0, 0, 0, 0, 1, 2}, {1, 2, 2, 0, 2, 1, 1}, {2, 1, 1, 0, 2, 2, 2},
//       {1, 2, 2, 0, 1, 2, 1}, {1, 2, 1, 1, 2, 2, 1}, {2, 2, 1, 1, 2, 1, 1}};

//   BOOST_CHECK_EQUAL(g->getBoard(), expected);
// }
