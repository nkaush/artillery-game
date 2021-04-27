//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_JSON_MANAGER_H
#define ARTILLERY_JSON_MANAGER_H

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

/**
 * This class contains string keys used to deserialize the game settings json.
 */
class JsonManager {
 public:
  // The default alpha (opacity) to use when not specified by json color objects
  static constexpr uint8_t kDefaultAlphaChannel = 255;

  static constexpr size_t kVec2Length = 2;

  // These constants are used in deserializing ColorA8u objects from json
  static const std::string kJsonRedColorKey;
  static const std::string kJsonGreenColorKey;
  static const std::string kJsonBlueColorKey;
  static const std::string kJsonAlphaChannelKey;

  // These constants are used in deserializing json objects describing terrain
  static const std::string kJsonRidgeExtremaKey;
  static const std::string kJsonBackgroundColorKey;
  static const std::string kJsonVisibleTerrainColorKey;
  static const std::string kJsonRemovedTerrainColorKey;
};

} // namespace artillery

/**
 * Need to add to the nlohmann namespace in order to (de)serialize objects
 * from outside the project namespace from json. Read more here:
 * https://github.com/nlohmann/json#how-do-i-convert-third-party-types
 */
namespace nlohmann {

/**
 * Argument dependent lookup struct to (de)serialize glm::vec2.
 */
template<> struct adl_serializer<glm::vec2> {
  /**
   * Serialize a glm::vec2.
   * @param json_array - the json array to populate
   * @param vec - the glm::vec2 to serialize
   */
  static void to_json(json& json_array, const glm::vec2& vec);

  /**
   * Deserialize a glm::vec2. If the passed json array contains more than 2
   * values, the vec2 is populated with the first 2. If the array contains
   * fewer than 2 values, the missing values are set to 0.
   * @param json_array - the json array to deserialize from
   * @param vec - the glm::vec2 to populate
   */
  static void from_json(const json& json_array, glm::vec2& vec);
};

/**
 * Argument dependent lookup struct to (de)serialize ci::ColorA8u.
 */
template<> struct adl_serializer<ci::ColorA8u> {
  /**
   * Serialize a ci::ColorA8u.
   * @param json_array - the json object to populate
   * @param color - the ci::ColorA8u to serialize
   */
  static void to_json(json& json_object, const ci::ColorA8u& color);

  /**
   * Deserialize a ci::ColorA8u. If the passed json object does not
   * define an alpha (opacity), sets the alpha to the default 255.
   * @param json_array - the json object to deserialize from
   * @param vec - the ci::ColorA8u to populate
   */
  static void from_json(const json& json_object, ci::ColorA8u& color);
};

} // namespace nlohmann

#endif  // ARTILLERY_JSON_MANAGER_H
