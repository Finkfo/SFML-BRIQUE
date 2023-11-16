#include "Math.h"

float Scalaire(sf::Vector2f v1, sf::Vector2f v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y;

	return result;
 }

float Module(sf::Vector2f v) {
	float result;
	result = sqrt((v.x * v.x) + (v.y * v.y));

	return result;
}