#include <vector>
#include <string>

#include "util/util.hpp"


namespace intra {

std::string
to_string(std::vector<float>& vec, const size_t len, const std::string& delimiter)
{
    std::string out = "";
    size_t max_idx = vec.size();
    
    if (len > 0 && len < max_idx)
        max_idx = len;

    for (size_t i = 0; i < max_idx; i++) {
        auto e = vec.at(i);
        out.append(std::to_string(e));
        if (!delimiter.empty() && i < max_idx - 1)
            out.append(delimiter);
    }
    
    return out;
}

}
