//
// Created by Neil Kaushikkar on 4/25/21.
//

#include <catch2/catch.hpp>

#include <core/quadratic_solver.h>
#include "cinder/gl/gl.h"

using artillery::QuadraticSolver;
using glm::vec3;
using glm::vec2;

TEST_CASE("Test Quadratic Solver") {
  SECTION("Test quadratic centered at origin") {
    QuadraticSolver quad = QuadraticSolver(vec2(), vec2(1, 1), vec2(-1, 1));

    REQUIRE(quad.GetQuadraticConstants() == vec3(0, 0, 1));
  }

  SECTION("Test quadratic centered below origin") {
    QuadraticSolver quad = QuadraticSolver(vec2(-5, -33), vec2(0, -8), vec2(-10.745, 0));

    vec3 constants = quad.GetQuadraticConstants();
    vec3 expected = vec3(-8, 10, 1);

    REQUIRE(Approx(constants.x).epsilon(0.0001) == expected.x);
    REQUIRE(Approx(constants.y).epsilon(0.0001) == expected.y);
    REQUIRE(Approx(constants.z).epsilon(0.0001) == expected.z);
  }
}
