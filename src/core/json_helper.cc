//
// Created by Neil Kaushikkar on 4/24/21.
//

#include "core/json_helper.h"

namespace artillery {

using std::string;
using glm::vec2;

const string JsonHelper::kJsonRedColorKey = "red";
const string JsonHelper::kJsonGreenColorKey = "green";
const string JsonHelper::kJsonBlueColorKey = "blue";
const string JsonHelper::kJsonAlphaChannelKey = "alpha";

} // namespace artillery

namespace nlohmann {

using artillery::JsonHelper;
using ci::ColorA8u;
using glm::vec2;

void adl_serializer<vec2>::to_json(json& json_array, const vec2& vec) {
  json_array = {vec.x, vec.y};
}

void adl_serializer<vec2>::from_json(const json& json_array, vec2& vec) {
  auto values = json_array.get<std::vector<float>>();
  vec.x = values.at(0);
  vec.y = values.at(1);
}

void adl_serializer<ColorA8u>::to_json(json& json_object,
                                       const ColorA8u& color) {
  json_object = json {
      {JsonHelper::kJsonRedColorKey, color.r},
      {JsonHelper::kJsonGreenColorKey, color.g},
      {JsonHelper::kJsonBlueColorKey, color.b},
      {JsonHelper::kJsonAlphaChannelKey, color.a}
  };
}

void adl_serializer<ColorA8u>::from_json(const json& json_object,
                                         ColorA8u& color) {
  json_object.at(JsonHelper::kJsonRedColorKey).get_to(color.r);
  json_object.at(JsonHelper::kJsonGreenColorKey).get_to(color.g);
  json_object.at(JsonHelper::kJsonBlueColorKey).get_to(color.b);

  try { // if 'alpha' is missing, set it to the default 255
    json_object.at(JsonHelper::kJsonAlphaChannelKey).get_to(color.a);
  } catch (json::exception& e) {
    color.a = JsonHelper::kDefaultAlphaChannel;
  }
}

} // namespace nlohmann
