#pragma once
#include <SFML\System.hpp>
#include "json.hpp"

using nlohmann::json;

typedef sf::Vector2i ScreenPixelCoor;
typedef sf::Vector2f MapPixelCoor;
typedef sf::Vector2i MapSpaceCoor;
typedef sf::Vector2i ObjectSpaceCoor;
typedef sf::Vector2f ObjectPixelCoor;
typedef sf::Vector2f OverlayPixelCoor;
typedef sf::Vector2f OverlayLocalCoor;


namespace nlohmann {
	template <typename T>
	struct adl_serializer<sf::Vector2<T>> {
		static void to_json(json& j, const sf::Vector2<T>& opt) {
			j = json{ opt.x, opt.y };
		}

		static void from_json(const json& j, sf::Vector2<T>& opt) {
			j.at(0).get_to(opt.x);
			j.at(1).get_to(opt.y);
		}
	};
}