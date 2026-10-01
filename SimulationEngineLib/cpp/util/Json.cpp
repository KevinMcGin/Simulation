#include "cpp/util/Json.h"

#include <iomanip>
#include <sstream>

std::string Json::quote(const std::string& value) {
    std::string out = "\"";
    for (const char c : value) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            case '\b': out += "\\b";  break;
            case '\f': out += "\\f";  break;
            default:
                // Anything else below 0x20 has to go out as \u00xx; JSON
                // forbids a bare control character inside a string.
                if (static_cast<unsigned char>(c) < 0x20) {
                    std::ostringstream escaped;
                    escaped << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                            << static_cast<int>(static_cast<unsigned char>(c));
                    out += escaped.str();
                } else {
                    out += c;
                }
        }
    }
    out += "\"";
    return out;
}

std::string Json::object(const std::string& fields) {
    return "{" + fields + "}";
}
