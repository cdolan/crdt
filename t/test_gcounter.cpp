#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <string>
#include "../crdt.h"

void signed_gcounter() {
  crdt::GCounter<std::string, int>("counter");
}

TEST_CASE("GCounter") {
  auto a = crdt::GCounter<std::string, unsigned int>("b");
  auto b = crdt::GCounter<std::string, unsigned int>("b", 42);

  REQUIRE(a.value() == 0);
  REQUIRE(b.value() == 42);
  REQUIRE_THROWS_MESSAGE(signed_gcounter(), "type T must be unsigned type");

  SUBCASE("id()") {
    auto a = crdt::GCounter<std::string, unsigned int>("a");
    auto b = crdt::GCounter<std::string, unsigned int>("b");

    CHECK(a.id() == "a");
    CHECK(b.id() == "b");
  }

  SUBCASE("value()") {
    auto counter = crdt::GCounter<std::string, unsigned int>("counter", 42);

    CHECK(counter.value() == 42);
  }

  SUBCASE("increment()") {
    SUBCASE("without argument increases the value by one") {
      auto counter = crdt::GCounter<std::string, unsigned int>("counter");

      counter.increment();

      CHECK(counter.value() == 1);
    }

    SUBCASE("with argument increases the value by delta") {
      auto counter = crdt::GCounter<std::string, unsigned int>("counter");

      counter.increment(3);

      CHECK(counter.value() == 3);
    }
  }

  SUBCASE("merge()") {
    SUBCASE("creates a new G-Counter from others") {
      auto a = crdt::GCounter<std::string, unsigned int>("a", 2);
      auto b = crdt::GCounter<std::string, unsigned int>("b", 3);

      auto c = a.merge("c", b);

      CHECK(c.value() == 5);
    }

    SUBCASE("uses the max() of each G-Counter") {
      auto foo1 = crdt::GCounter<std::string, unsigned int>("foo", 5);
      auto foo2 = crdt::GCounter<std::string, unsigned int>("foo", 7);

      auto foo3 = foo1.merge("foo", foo2);

      CHECK(foo3.value() == 7);
    }
  }
}
