//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_JSON_MANAGER_H
#define ARTILLERY_JSON_MANAGER_H

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

class JsonManager {
 public:
  static constexpr uint8_t kDefaultAlphaChannel = 255;

  // These constants are used in deserializing ColorA8u objects from json
  static const std::string kJsonRedColorKey;
  static const std::string kJsonGreenColorKey;
  static const std::string kJsonBlueColorKey;
  static const std::string kJsonAlphaChannelKey;

  // These constants are used in deserializing json objects describing terrain
  static const std::string kJsonRidgeExtremaKey;
  static const std::string kJsonStartingHeightsKey;
  static const std::string kJsonBackgroundColorKey;
  static const std::string kJsonVisibleTerrainColorKey;
  static const std::string kJsonRemovedTerrainColorKey;

  // These constants are used in deserializing player json objects
  static const std::string kJsonBulletColorKey;
  static const std::string kJsonLaserColorKey;
  static const std::string kJsonTankColorKey;
  static const std::string kJsonStartingXKey;

  // These constants are used in deserializing the game settings json
  static const std::string kJsonTerrainKey;
  static const std::string kJsonMaxBlastRadiusKey;
  static const std::string kJsonMinBlastRadiusKey;
  static const std::string kJsonBlastRadiusScalarKey;
  static const std::string kJsonTankConfigurationKey;
  static const std::string kJsonBulletVelocityDampingKey;
};

} // namespace artillery

namespace nlohmann {

template <> struct adl_serializer<glm::vec2> {
  static void to_json(json& json_array, const glm::vec2& vec);

  static void from_json(const json& json_array, glm::vec2& vec);
};

template <> struct adl_serializer<ci::ColorA8u> {
  static void to_json(json& json_object, const ci::ColorA8u& color);

  static void from_json(const json& json_object, ci::ColorA8u& color);
};

} // namespace nlohmann

#endif  // ARTILLERY_JSON_MANAGER_H
