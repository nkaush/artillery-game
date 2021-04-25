//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_JSON_HELPER_H
#define ARTILLERY_JSON_HELPER_H

#include "nlohmann/json.hpp"
#include "cinder/gl/gl.h"

#include <string>

namespace artillery {

class JsonHelper {
 public:
  static const std::string kJsonRedColorKey;
  static const std::string kJsonGreenColorKey;
  static const std::string kJsonBlueColorKey;
  static const std::string kJsonAlphaChannelKey;

  static constexpr uint8_t kDefaultAlphaChannel = 255;
};

} // namespace artillery

namespace nlohmann {

template <>
struct adl_serializer<glm::vec2> {
  static void to_json(json& json_array, const glm::vec2& vec);

  static void from_json(const json& json_array, glm::vec2& vec);
};

template <>
struct adl_serializer<ci::ColorA8u> {
  static void to_json(json& json_object, const ci::ColorA8u& color);

  static void from_json(const json& json_object, ci::ColorA8u& color);
};

} // namespace nlohmann

#endif  // ARTILLERY_JSON_HELPER_H
