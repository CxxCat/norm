#include "norm.h"
#include <stdint.h>

std::string normalize(const std::string& path) {
    std::string result;
    result.reserve(path.length());
    size_t skips = 0;
    auto it = path.rbegin();
    while (it != path.rend()) {
        if (*it == '/') { // save last slash
            if (it == path.rbegin()) {
                result += *it;
            }
            ++it;
        }
        if (*it == '.') {
            ++it;
            if (it == path.rend() || *it == '/') { // is "./"
                ++skips;
            }
            else {
                if (*it == '.') {
                    ++it;
                    if (it == path.rend() || *it == '/') { // is "../"
                        skips += 2;
                    }
                    else if (skips == 0) {
                        result += "..";
                    }
                }
                else if (skips == 0) {
                    result += '.';
                }
            }
        }
        while (it != path.rend() && *it != '/') { // copy symbols until '/'
            if (skips == 0) {
                result += *it;
            }
            ++it;
        }
        if (it != path.rend())
        {
            if (skips == 0) { // new path item
                result += '/';
            }
            else {
                --skips;
            }
            ++it;
        }
    }
    if (result.empty() || result.back() != '/') {
        result += '/';
    }
    std::reverse(result.begin(), result.end());
    return result;
}
