//
// Created by Neil Kaushikkar on 4/20/21.
//

#include <catch2/catch.hpp>

#include <core/bullet.h>
#include <core/tank.h>

using artillery::Bullet;
using artillery::Tank;
using glm::vec2;

TEST_CASE("Test Pointing Barrel") {
  Tank tank = Tank(vec2(50, 400), Tank::kDefaultTurretOffset,
                   40, 15, 10, 30, 3, 106, 113, 82);

  //  pivot position: (52, 392.5)

  SECTION("Point barrel directly horizontal to the left") {
    tank.PointBarrel(vec2(150, 392.5));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == 0);
  }

  SECTION("Point barrel directly horizontal to the right") {
    tank.PointBarrel(vec2(0, 392.5));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == M_PI);
  }

  SECTION("Point barrel directly vertical upward") {
    tank.PointBarrel(vec2(52, 500));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == M_PI / 2);
  }

  SECTION("Point barrel directly vertical downward") {
    tank.PointBarrel(vec2(52, 0));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == -M_PI / 2);
  }

  SECTION("Point barrel diagonally up and right") {
    tank.PointBarrel(vec2(102, 442.5));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == M_PI / 4);
  }

  SECTION("Point barrel diagonally up and left") {
    tank.PointBarrel(vec2(2, 442.5));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == 3 * M_PI / 4);
  }

  SECTION("Point barrel diagonally down and left") {
    tank.PointBarrel(vec2(2, 342.5));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == -3 * M_PI / 4);
  }

  SECTION("Point barrel diagonally down and right") {
    tank.PointBarrel(vec2(102, 342.5));
    REQUIRE(Approx( tank.GetBarrelRotation() ).epsilon(0.01) == -M_PI / 4);
  }
}

TEST_CASE("Test Shooting Bullet Parallel to Axes") {
  Tank tank = Tank(vec2(50, 400), Tank::kDefaultTurretOffset,
                   40, 15, 10, 30, 3, 106, 113, 82);

  SECTION("Shoot bullet horizontally") {
    tank.PointBarrel(vec2(152, 392.5));
    Bullet bullet = tank.ShootBullet();

    REQUIRE(Approx( bullet.GetVelocity().x ).epsilon(0.01) == 5);
    REQUIRE(Approx( bullet.GetVelocity().y ).epsilon(0.01) == 0);
    REQUIRE(Approx( bullet.GetPosition().x ).epsilon(0.01) == 89);
    REQUIRE(Approx( bullet.GetPosition().y ).epsilon(0.01) == 392.5);
  }

  SECTION("Shoot bullet horizontally with scaled velocity") {
    tank.PointBarrel(vec2(452, 392.5));
    Bullet bullet = tank.ShootBullet();

    REQUIRE(Approx( bullet.GetVelocity().x ).epsilon(0.01) == 20);
    REQUIRE(Approx( bullet.GetVelocity().y ).epsilon(0.01) == 0);
    REQUIRE(Approx( bullet.GetPosition().x ).epsilon(0.01) == 89);
    REQUIRE(Approx( bullet.GetPosition().y ).epsilon(0.01) == 392.5);
  }

  SECTION("Shoot bullet vertically") {
    tank.PointBarrel(vec2(52, 592.5));
    Bullet bullet = tank.ShootBullet();

    REQUIRE(Approx( bullet.GetVelocity().x ).epsilon(0.01) == 0);
    REQUIRE(Approx( bullet.GetVelocity().y ).epsilon(0.01) == 10);
    REQUIRE(Approx( bullet.GetPosition().x ).epsilon(0.01) == 52);
    REQUIRE(Approx( bullet.GetPosition().y ).epsilon(0.01) == 429.5);
  }

  SECTION("Shoot bullet vertically with scaled velocity") {
    tank.PointBarrel(vec2(52, 792.5));
    Bullet bullet = tank.ShootBullet();

    REQUIRE(Approx( bullet.GetVelocity().x ).epsilon(0.01) == 0);
    REQUIRE(Approx( bullet.GetVelocity().y ).epsilon(0.01) == 20);
    REQUIRE(Approx( bullet.GetPosition().x ).epsilon(0.01) == 52);
    REQUIRE(Approx( bullet.GetPosition().y ).epsilon(0.01) == 429.5);
  }

  SECTION("Shoot bullet diagonally") {
    tank.PointBarrel(vec2(252, 592.5));
    Bullet bullet = tank.ShootBullet();

    REQUIRE(Approx( bullet.GetVelocity().x ).epsilon(0.01) == 10);
    REQUIRE(Approx( bullet.GetVelocity().y ).epsilon(0.01) == 10);
    REQUIRE(Approx( bullet.GetPosition().x ).epsilon(0.01) == 78);
    REQUIRE(Approx( bullet.GetPosition().y ).epsilon(0.01) == 418);
  }

  SECTION("Shoot bullet diagonally with scaled velocity") {
    tank.PointBarrel(vec2(852, 1192.5));
    Bullet bullet = tank.ShootBullet();

    REQUIRE(Approx( bullet.GetVelocity().x ).epsilon(0.01) == 40);
    REQUIRE(Approx( bullet.GetVelocity().y ).epsilon(0.01) == 40);
    REQUIRE(Approx( bullet.GetPosition().x ).epsilon(0.01) == 78);
    REQUIRE(Approx( bullet.GetPosition().y ).epsilon(0.01) == 418);
  }
}
