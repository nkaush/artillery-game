//
// Created by Neil Kaushikkar on 4/24/21.
//

#include "utilities/json_manager.h"

#include <vector>

namespace artillery {

using std::string;

// These constants are used in deserializing ColorA8u objects from json
const string JsonManager::kJsonRedColorKey = "red";
const string JsonManager::kJsonGreenColorKey = "green";
const string JsonManager::kJsonBlueColorKey = "blue";
const string JsonManager::kJsonAlphaChannelKey = "alpha";

// These constants are used in deserializing json objects describing terrain
const string JsonManager::kJsonRidgeExtremaKey = "ridge_extrema";
const string JsonManager::kJsonBackgroundColorKey = "background_color";
const string JsonManager::kJsonVisibleTerrainColorKey = "visible_terrain_color";
const string JsonManager::kJsonRemovedTerrainColorKey = "removed_terrain_color";

} // namespace artillery

namespace nlohmann {

using artillery::JsonManager;
using ci::ColorA8u;
using std::vector;
using glm::vec2;

void adl_serializer<vec2>::to_json(json& json_array, const vec2& vec) {
  json_array = {vec.x, vec.y};
}

void adl_serializer<vec2>::from_json(const json& json_array, vec2& vec) {
  vector<float> values;

  // Only deserialize the json if it contains an array or a numeric value
  if (json_array.is_array()) {
    values = json_array.get<vector<float>>();
  } else if (json_array.is_number()) {
    values.push_back(json_array.get<float>());
  } else {
    return;
  }

  // If the 1st value is missing, set it to 0, otherwise, fill with 1st value
  if (values.empty()) {
    vec.x = 0;
  } else {
    vec.x = values.at(0);
  }

  // If the 2nd value is missing, set it to 0, otherwise, fill with 2nd value
  if (values.size() < JsonManager::kVec2Length) {
    vec.y = 0;
  } else {
    vec.y = values.at(1);
  }
}

void adl_serializer<ColorA8u>::to_json(json& json_object,
                                       const ColorA8u& color) {
  json_object = json {
      {JsonManager::kJsonRedColorKey, color.r},
      {JsonManager::kJsonGreenColorKey, color.g},
      {JsonManager::kJsonBlueColorKey, color.b},
      {JsonManager::kJsonAlphaChannelKey, color.a}
  };
}

void adl_serializer<ColorA8u>::from_json(const json& json_object,
                                         ColorA8u& color) {
  json_object.at(JsonManager::kJsonRedColorKey).get_to(color.r);
  json_object.at(JsonManager::kJsonGreenColorKey).get_to(color.g);
  json_object.at(JsonManager::kJsonBlueColorKey).get_to(color.b);

  try { // if 'alpha' is missing, set it to the default 255
    json_object.at(JsonManager::kJsonAlphaChannelKey).get_to(color.a);
  } catch (json::exception& e) {
    color.a = JsonManager::kDefaultAlphaChannel;
  }
}

} // namespace nlohmann
