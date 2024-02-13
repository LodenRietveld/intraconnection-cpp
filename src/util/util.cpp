#include <vector>
#include <string>

#include "util/util.hpp"


namespace intra {

std::string
to_string(std::vector<float>& vec, const std::string& delimiter)
{
    std::string out = "";
    for (size_t i = 0; i < vec.size(); i++) {
        auto e = vec.at(i);
        out.append(std::to_string(e));
        if (!delimiter.empty() && i < (vec.size() - 1))
            out.append(delimiter);
    }
    
    return out;
}

}
