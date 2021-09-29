
#include <iostream>
#include <filesystem>
#include <fstream>

#include "MrMime/src/mister_mime.hpp"

namespace fs = std::filesystem;

using std::cout, std::endl;

using
	MrMime::FileType,
	MrMime::header_data_buffer_t,
	MrMime::compareSignaturesTo,
	MrMime::hydrus_compatible_filetype;

//getMime() return an int take in a string
extern "C"
int getMimeCXX(const char* const cpath)
{
	header_data_buffer_t buffer{};
	char* const buffer_ptr{ reinterpret_cast<char*>(buffer.data()) };

    fs::path path {cpath};

    auto ifs{ std::ifstream(path, std::ios::binary) };

    // could use exceptions instead:
    //ifs.exceptions(ifs.badbit | ifs.failbit | ifs.eofbit);

    if (!ifs.is_open()) [[unlikely]]
    {
        //std::cerr << "failed to open file: " << path << endl;
        return MrMime::FileType::APPLICATION_UNKNOWN;
    }

    if (!ifs.seekg(ifs.beg)) [[unlikely]]
    {
        //std::cerr << "failed to seekg file: " << path << endl;
        return MrMime::FileType::APPLICATION_UNKNOWN;
    }

    if (!ifs.read(buffer_ptr, buffer.size())) [[unlikely]]
    {
        //std::cerr << "failed to read file: " << path << endl;
        return MrMime::FileType::APPLICATION_UNKNOWN;
    }

    return hydrus_compatible_filetype( compareSignaturesTo(buffer) );
}
