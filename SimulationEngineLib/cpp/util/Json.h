#pragma once
#include <string>

// Just enough JSON to wrap the engine's CSV documents in one response. Not
// a general encoder: it escapes a string and joins named string fields,
// which is all the simulation endpoint returns.
namespace Json {
    // Escapes value and wraps it in quotes. CSV is mostly digits and
    // commas, but it is full of newlines, and a raw newline inside a JSON
    // string is invalid — a parser rejects the whole response rather than
    // just the line it appeared on.
    std::string quote(const std::string& value);

    // {"<name>":"<value>", ...} from pairs already quoted by quote().
    std::string object(const std::string& fields);
}
