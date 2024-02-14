#pragma once

#include <vector>
#include <string>

namespace intra {
std::string
to_string(std::vector<float>& vec, const size_t max_len = 0,
        const std::string& delimiter = " ");
}
