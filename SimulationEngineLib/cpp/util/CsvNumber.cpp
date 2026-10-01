#include "cpp/util/CsvNumber.h"

#include <sstream>

namespace {
    // Enough digits to describe a particle without inventing precision the
    // simulation doesn't have.
    const int precision = 12;

    // std::fixed pads every value out to the full precision, so a radius of
    // 1 comes out as "1.000000000000". Those tail zeros carry no value and,
    // at one row per particle per frame, they are a large share of the
    // response — so drop them, along with a decimal point left with nothing
    // after it. Trimming only ever removes digits that don't affect the
    // value, so what the reader parses back is unchanged.
    std::string trimTrailingZeros(std::string value) {
        if (value.find('.') == std::string::npos) {
            return value;
        }
        value.erase(value.find_last_not_of('0') + 1);
        if (value.back() == '.') {
            value.pop_back();
        }
        return value;
    }
}

std::string CsvNumber::format(double value) {
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << value;
    return trimTrailingZeros(std::move(out).str());
}
