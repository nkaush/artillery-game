//
// Created by Neil Kaushikkar on 4/24/21.
//

#include "core/json_manager.h"

namespace artillery {

using std::string;

// These constants are used in deserializing ColorA8u objects from json
const string JsonManager::kJsonRedColorKey = "red";
const string JsonManager::kJsonGreenColorKey = "green";
const string JsonManager::kJsonBlueColorKey = "blue";
const string JsonManager::kJsonAlphaChannelKey = "alpha";

// These constants are used in deserializing json objects describing terrain
const string JsonManager::kJsonRidgeExtremaKey = "ridge_extrema";
const string JsonManager::kJsonStartingHeightsKey = "starting_pixel_heights";
const string JsonManager::kJsonBackgroundColorKey = "background_color";
const string JsonManager::kJsonVisibleTerrainColorKey = "visible_terrain_color";
const string JsonManager::kJsonRemovedTerrainColorKey = "removed_terrain_color";

// These constants are used in deserializing player json objects
const string JsonManager::kJsonBulletColorKey = "bullet_color";
const string JsonManager::kJsonLaserColorKey = "laser_color";
const string JsonManager::kJsonTankColorKey = "chassis_color";
const string JsonManager::kJsonStartingXKey = "starting_x";

// These constants are used in deserializing the game settings json
const string JsonManager::kJsonTerrainKey = "terrain";
const string JsonManager::kJsonMaxBlastRadiusKey = "blast_radius_max";
const string JsonManager::kJsonMinBlastRadiusKey = "blast_radius_min";
const string JsonManager::kJsonBlastRadiusScalarKey = "blast_radius_scalar";
const string JsonManager::kJsonTankConfigurationKey = "tank_configuration";
const string JsonManager::kJsonBulletVelocityDampingKey =
    "bullet_velocity_damping";

} // namespace artillery

namespace nlohmann {

using artillery::JsonManager;
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
