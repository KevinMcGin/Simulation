#include "cpp/law/LawConfig.h"

#include <cmath>
#include <sstream>
#include <stdexcept>

namespace {
	const std::string COLLISION_COALESCE = "collisionCoalesce";
	const std::string NEWTON_GRAVITY = "newtonGravity";
	const std::string NEWTON_FIRST_LAW = "newtonFirstLaw";

	const std::string NEWTON = "newton";
	const std::string EINSTEIN = "einstein";

	std::string trim(const std::string& value) {
		const auto first = value.find_first_not_of(" \t\r\n");
		if (first == std::string::npos) {
			return "";
		}
		const auto last = value.find_last_not_of(" \t\r\n");
		return value.substr(first, last - first + 1);
	}

	// Quoted and comma-separated, so the message can list what the caller
	// should have sent instead of just saying the value was wrong.
	std::string quotedList(const std::vector<std::string>& values) {
		std::string list;
		for (const auto& value : values) {
			if (!list.empty()) {
				list += ", ";
			}
			list += "\"" + value + "\"";
		}
		return list;
	}
}

const std::vector<std::string>& LawConfig::lawNames() {
	static const std::vector<std::string> names = { COLLISION_COALESCE, NEWTON_GRAVITY, NEWTON_FIRST_LAW };
	return names;
}

const std::vector<std::string>& LawConfig::momentumNames() {
	static const std::vector<std::string> names = { NEWTON, EINSTEIN };
	return names;
}

std::string LawConfig::setLaws(const std::string& laws) {
	bool collisionCoalesce = false;
	bool newtonGravity = false;
	bool newtonFirstLaw = false;

	std::istringstream stream(laws);
	std::string name;
	while (std::getline(stream, name, ',')) {
		name = trim(name);
		if (name.empty()) {
			continue;
		}
		if (name == COLLISION_COALESCE) {
			collisionCoalesce = true;
		} else if (name == NEWTON_GRAVITY) {
			newtonGravity = true;
		} else if (name == NEWTON_FIRST_LAW) {
			newtonFirstLaw = true;
		} else {
			return "unknown law \"" + name + "\": laws must be a comma-separated list of " + quotedList(lawNames());
		}
	}

	isCollisionCoalesceEnabled = collisionCoalesce;
	isNewtonGravityEnabled = newtonGravity;
	isNewtonFirstLawEnabled = newtonFirstLaw;
	return "";
}

std::string LawConfig::setMomentum(const std::string& momentumName) {
	const auto name = trim(momentumName);
	if (name == NEWTON) {
		momentum = MOMENTUM_NEWTON;
		return "";
	}
	if (name == EINSTEIN) {
		momentum = MOMENTUM_EINSTEIN;
		return "";
	}
	return "unknown momentum \"" + name + "\": momentum must be one of " + quotedList(momentumNames());
}

std::string LawConfig::setGravitationalConstant(const std::string& value) {
	// Parsed with std::stof rather than atof: atof answers 0 for text it
	// cannot read at all, which is indistinguishable from a caller genuinely
	// sending 0 and would be reported as the wrong problem.
	float parsed = 0;
	try {
		size_t consumed = 0;
		parsed = std::stof(trim(value), &consumed);
		if (consumed != trim(value).size()) {
			throw std::invalid_argument("trailing characters");
		}
	} catch (const std::exception&) {
		return "gravitationalConstant must be a number";
	}

	// Written as a negated greater-than so a NaN, which compares false
	// against everything, is rejected here rather than reaching the force
	// calculation and poisoning every particle it touches.
	if (!(parsed > 0)) {
		return "gravitationalConstant must be greater than 0";
	}
	gravitationalConstant = parsed;
	return "";
}
