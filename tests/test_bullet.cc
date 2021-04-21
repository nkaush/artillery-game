//
// Created by Neil Kaushikkar on 4/18/21.
//

#include <catch2/catch.hpp>

#include <core/bullet.h>
#include <vector>

using artillery::Bullet;
using std::vector;
using glm::vec2;

TEST_CASE("Test Bullet Follows Parabolic Path") {
  SECTION("Test bullet fired vertically") {
    Bullet bullet = Bullet(vec2(), vec2(0, 5), 2);

    vector<vec2> expected_velocities = {
        vec2(0, 5.2), vec2(0, 5.4), vec2(0, 5.6), vec2(0, 5.8), vec2(0, 6.0),
        vec2(0, 6.2), vec2(0, 6.4), vec2(0, 6.6), vec2(0, 6.8), vec2(0, 7.0)
    };

    vector<vec2> expected_positions = {
        vec2(0, 5), vec2(0, 10.2), vec2(0, 15.6), vec2(0, 21.2), vec2(0, 27),
        vec2(0, 33), vec2(0, 39.2), vec2(0, 45.6), vec2(0, 52.2), vec2(0, 59)
    };

    for (size_t i = 0; i < expected_positions.size(); i++) {
      bullet.UpdatePosition();

      REQUIRE(Approx( expected_positions.at(i).x ).epsilon(0.01)
              == bullet.GetPosition().x);
      REQUIRE(Approx( expected_positions.at(i).y ).epsilon(0.01)
              == bullet.GetPosition().y);

      REQUIRE(Approx( expected_velocities.at(i).x ).epsilon(0.01)
              == bullet.GetVelocity().x);
      REQUIRE(Approx( expected_velocities.at(i).y ).epsilon(0.01)
              == bullet.GetVelocity().y);
    }
  }

  SECTION("Test bullet fired horizontally") {
    Bullet bullet = Bullet(vec2(), vec2(5, 0), 2);

    vector<vec2> expected_velocities = {
        vec2(5, 0.2), vec2(5, 0.4), vec2(5, 0.6), vec2(5, 0.8), vec2(5, 1),
        vec2(5, 1.2), vec2(5, 1.4), vec2(5, 1.6), vec2(5, 1.8), vec2(5, 2)
    };

    vector<vec2> expected_positions = {
        vec2(5, 0), vec2(10, 0.2), vec2(15, 0.6), vec2(20, 1.2), vec2(25, 2),
        vec2(30, 3), vec2(35, 4.2), vec2(40, 5.6), vec2(45, 7.2), vec2(50, 9)
    };

    for (size_t i = 0; i < expected_positions.size(); i++) {
      bullet.UpdatePosition();

      REQUIRE(Approx( expected_positions.at(i).x ).epsilon(0.01)
              == bullet.GetPosition().x);
      REQUIRE(Approx( expected_positions.at(i).y ).epsilon(0.01)
              == bullet.GetPosition().y);

      REQUIRE(Approx( expected_velocities.at(i).x ).epsilon(0.01)
              == bullet.GetVelocity().x);
      REQUIRE(Approx( expected_velocities.at(i).y ).epsilon(0.01)
              == bullet.GetVelocity().y);
    }
  }

  SECTION("Test bullet fired Diagonally") {
    Bullet bullet = Bullet(vec2(), vec2(5, 5), 2);

    vector<vec2> expected_velocities = {
        vec2(5, 5.2), vec2(5, 5.4), vec2(5, 5.6), vec2(5, 5.8), vec2(5, 6.0),
        vec2(5, 6.2), vec2(5, 6.4), vec2(5, 6.6), vec2(5, 6.8), vec2(5, 7.0)
    };

    vector<vec2> expected_positions = {
        vec2(5, 5), vec2(10, 10.2), vec2(15, 15.6), vec2(20, 21.2), vec2(25, 27),
        vec2(30, 33), vec2(35, 39.2), vec2(40, 45.6), vec2(45, 52.2), vec2(50, 59)
    };

    for (size_t i = 0; i < expected_positions.size(); i++) {
      bullet.UpdatePosition();

      REQUIRE(Approx( expected_positions.at(i).x ).epsilon(0.01)
              == bullet.GetPosition().x);
      REQUIRE(Approx( expected_positions.at(i).y ).epsilon(0.01)
              == bullet.GetPosition().y);

      REQUIRE(Approx( expected_velocities.at(i).x ).epsilon(0.01)
              == bullet.GetVelocity().x);
      REQUIRE(Approx( expected_velocities.at(i).y ).epsilon(0.01)
              == bullet.GetVelocity().y);
    }
  }
}
