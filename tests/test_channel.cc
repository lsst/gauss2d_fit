#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "channel.h"

namespace g2f = gauss2d::fit;

TEST_CASE("Channels")
{
    CHECK(g2f::Channel::get_channels().size() == 1);
    CHECK_THROWS_AS(g2f::Channel::make_const("None"), std::invalid_argument);
    auto x = g2f::Channel::make("x");
    CHECK(x->get_channels().size() == 2);
    CHECK_THROWS_AS(g2f::Channel::erase("None"), std::invalid_argument);
    CHECK_THROWS_AS(g2f::Channel::erase("x"), std::runtime_error);
    CHECK_THROWS_AS(g2f::Channel::make("x"), std::invalid_argument);
    x.reset();
    g2f::Channel::erase("x");
    CHECK(g2f::Channel::get_channels().size() == 1);
    CHECK(g2f::Channel::make("x")->get_channels().size() == 2);
    CHECK(g2f::Channel::find_channel("y") == nullptr);
    CHECK(g2f::Channel::get_channel("x")->get_channels().size() == 2);
    CHECK(g2f::Channel::get_channel("y")->get_channels().size() == 3);
}
