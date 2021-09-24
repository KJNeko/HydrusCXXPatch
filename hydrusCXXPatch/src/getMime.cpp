#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstring>

enum simpleFileType
{
    SIMPLE_IMAGE_JPEG = 1,
    SIMPLE_IMAGE_GIF = 3,
    SIMPLE_PNG = 2,
    SIMPLE_APNG = 23,
    SIMPLE_WEBP = 33,
    SIMPLE_IMAGE_TIFF = 34,
    SIMPLE_IMAGE_BMP = 4,
    SIMPLE_IMAGE_ICON = 7,
    SIMPLE_APPLICATION_FLASH = 5,
    SIMPLE_VIDEO_FLV = 9,
    SIMPLE_APPLICATION_PDR = 10,
    SIMPLE_APPLICATION_CLIP = 45,
    SIMPLE_APPLICATION_ZIP = 11,
    SIMPLE_APPLICATION_7Z = 32,
    SIMPLE_APPLICATION_RAR = 31,
    SIMPLE_APPLICATION_HYDRUS_ENCRYPTED_ZIP = 12,
    SIMPLE_VIDEO_MP4 = 14,
    SIMPLE_VIDEO_MOV = 26,
    SIMPLE_AUDIO_FLAC = 16,
    SIMPLE_AUDIO_WAVE = 46,
    SIMPLE_VIDEO_AVI = 27,
    SIMPLE_UNDETERMINED_WM = 19
};

#include <cstdint>
#include <vector>
#include <array>
#include <utility> // pair

enum SpecificFileType
{
    IMAGE_JPEG = 0, //0xffd8
    IMAGE_GIF_87a, //GIF87a
    IMAGE_GIF_89a, //GIF89a
    IMAGE_PNG, //\x89PNG
    IMAGE_WEBP, //WEBP
    IMAGE_TIFF_II, //II*\x00
    IMAGE_TIFF_MM, //MM\x00*
    IMAGE_BMP, //BM
    IMAGE_ICON_1, //\x00\x00\x01\x00
    IMAGE_ICON_2, //\x00\x00\x02\x00
    APPLICATION_FLASH_CWS, //I gave up here
    APPLICATION_FLASH_FWS,
    APPLICATION_FLASH_ZWS,
    VIDEO_FLV,
    APPLICATION_PDF,
    APPLICATION_PSD,
    APPLICATION_PSD_BIG,
    APPLICATION_CLIP,
    APPLICATIONZIP_1,
    APPLICATIONZIP_2,
    APPLICATIONZIP_3,
    APPLICATION_7Z,
    APPLICATION_RAR_1,
    APPLICATION_RAR_2,
    APPLICATION_HYDRUS_ENCRYPTED_ZIP,
    VIDEO_MP4_1,
    VIDEO_MP4_2,
    VIDEO_MP4_3,
    VIDEO_MP4_4,
    VIDEO_MP4_5,
    VIDEO_MP4_6,
    VIDEO_MP4_7,
    VIDEO_MOV,
    AUDIO_FLAC,
    AUDIO_WAVE,
    AUDIO_RIFF,
    VIDEO_AVI,
    UNDETERMINED_VM,

    MAX,
    IMAGE_APNG,
    INVALID
};


std::array<
	std::pair<uint8_t, std::vector<char>>,
	SpecificFileType::MAX
> FileTypeSignatures
{
	{
		{0, {'\xFF','\xD8'}},
		{0, {'G','I','F','8','7','a','\0'}},
		{0, {'G','I','F','8','9','a'}},
		{0, {'\x89','P','N','G'}},
		{8, {'W','E','B','P'}},
		{0, {'I','I','*','\x00'}},
		{0, {'M','M','\x00','*'}},
		{0, {'B','M'}},
		{0, {'\x00','\x00','\x01','\x00'}},
		{0, {'\x00','\x00','\x02','\x00'}},
		{0, {'C','W','S'}},
		{0, {'F','W','S'}},
		{0, {'Z','W','S'}},
		{0, {'F','L','V'}},
		{0, {'%','P','D','F'}},
		{0, {'8','B','P','S','\x00','\x01'}},
		{0, {'8','B','P','S','\x00','\x02'}},
		{0, {'C','S','F','C','H','U','N','K'}},
		{0, {'P','K','\x03','\x04'}},
		{0, {'P','K','\x05','\x06'}},
		{0, {'P','K','\x07','\x08'}},
		{0, {'7','z','\xBC','\xAF','\x27','\x1C'}},
		{0, {'\x52','\x61','\x72','\x21','\x1A','\x07','\x00'}},
		{0, {'\x52','\x61','\x72','\x21','\x1A','\x07','\x01','\x00'}},
		{0, {'h','y','d','r','u','s',' ','e','n','c','r','y','p','t','e','d',' ','z','i','p'}},
		{4, {'f','t','y','p','m','p','4'}},
		{4, {'f','t','y','p','i','s','o','m'}},
		{4, {'f','t','y','p','M','4','V'}},
		{4, {'f','t','y','p','M','S','N','V'}},
		{4, {'f','t','y','p','a','v','c','1'}},
		{4, {'f','t','y','p','F','A','C','E'}},
		{4, {'f','t','y','p','d','a','s','h'}},
		{4, {'f','t','y','p','q','t'}},
		{0, {'f','L','a','C'}},
		{0, {'R','I','F','F'}},
		{8, {'W','A','V','E'}},
		{8, {'A','V','I'}},
		{0, {'\x30','\x26','\xB2','\x75','\x8E','\x66','\xCF','\x11','\xA6','\xD9','\x00','\xAA','\x00','\x62','\xCE','\x6C'}},
	}
};

SpecificFileType fileTypeFromHeader( const std::array<char, 128>& fileData )
{
	std::size_t currentIndex { 0 };
    for (const auto& pair : FileTypeSignatures)
    {
        const auto& [offset, signature]{ pair };
        if (std::equal(
            fileData.cbegin() + offset, fileData.cbegin() + offset + signature.size(),
            signature.cbegin(), signature.cend()))
        {
            if(currentIndex == IMAGE_PNG)
            {
                //Search for acTL block

                int32_t IHDRoffset = 12;
                std::vector<char> sig = {'I','H','D','R'};

                if(std::equal(
                    fileData.cbegin() + IHDRoffset, fileData.cbegin() + IHDRoffset + sig.size(),
                    sig.cbegin(), sig.cend()))
                {
                    //We found the header
                    int32_t size { 0 };

                    std::array<char ,4> flipped;
                    for(int i = 0; i < 4; ++i)
                    {
                        flipped.at((flipped.size() - 1) - i) = fileData.at((IHDRoffset - 4) + i);
                    }

                    std::memcpy(&size, flipped.cbegin(), sizeof(int32_t));

                    IHDRoffset += size + 8 + 4; //+4 for offset to skip size of next header, +8 to get past the checksum and IHDR header itself

                    sig = {'a','c','T','L'};

                    if(std::equal(fileData.cbegin() + IHDRoffset, fileData.cbegin() + IHDRoffset + sig.size(), sig.cbegin(), sig.cend()))
                    {
                        //Is animated
                        return IMAGE_APNG;
                    }
                    else
                    {
                        return IMAGE_PNG;
                    }
                }
            }
            return static_cast<SpecificFileType>(currentIndex);
        }
        ++currentIndex;
    };
	return SpecificFileType::INVALID;
}

#include <bitset>

int parseType( std::string filename )
{
	std::array<char, 128> imgdata { 0 };

	if(std::ifstream ifs( filename, std::ios::binary ); ifs)
	{
		ifs.seekg( ifs.beg );
		ifs.read( imgdata.data(), imgdata.size() );
		return fileTypeFromHeader( imgdata );
	}
	return INVALID;
}

//getMime() return an int take in a string
extern "C"
int getMimeCXX(const char* cpath)
{
    std::string path {cpath};

    switch(parseType(path))
    {
        case IMAGE_JPEG: return SIMPLE_IMAGE_JPEG;
        case IMAGE_GIF_87a: [[fallthrough]];
        case IMAGE_GIF_89a: return SIMPLE_IMAGE_GIF;
        case IMAGE_PNG: return SIMPLE_PNG;
        case IMAGE_APNG: return SIMPLE_APNG;
        case IMAGE_WEBP: return SIMPLE_WEBP;
        case IMAGE_TIFF_II: [[fallthrough]];
        case IMAGE_TIFF_MM: return SIMPLE_IMAGE_TIFF;
        case IMAGE_ICON_1: [[fallthrough]];
        case IMAGE_ICON_2: return SIMPLE_IMAGE_ICON;
        case APPLICATION_FLASH_CWS: [[fallthrough]];
        case APPLICATION_FLASH_FWS: [[fallthrough]];
        case APPLICATION_FLASH_ZWS: return SIMPLE_APPLICATION_FLASH;
        case VIDEO_FLV: return SIMPLE_VIDEO_FLV;
        case APPLICATION_PDF: [[fallthrough]];
        case APPLICATION_PSD: [[fallthrough]];
        case APPLICATION_PSD_BIG: return SIMPLE_APPLICATION_PDR;
        case APPLICATION_CLIP: return SIMPLE_APPLICATION_CLIP;
        case APPLICATIONZIP_1: [[fallthrough]];
        case APPLICATIONZIP_2: [[fallthrough]];
        case APPLICATIONZIP_3: return SIMPLE_APPLICATION_ZIP;
        case APPLICATION_7Z: return SIMPLE_APPLICATION_7Z;
        case APPLICATION_RAR_1: [[fallthrough]];
        case APPLICATION_RAR_2: return SIMPLE_APPLICATION_RAR;
        case APPLICATION_HYDRUS_ENCRYPTED_ZIP: return SIMPLE_APPLICATION_HYDRUS_ENCRYPTED_ZIP;
        case VIDEO_MP4_1: [[fallthrough]];
        case VIDEO_MP4_2: [[fallthrough]];
        case VIDEO_MP4_3: [[fallthrough]];
        case VIDEO_MP4_4: [[fallthrough]];
        case VIDEO_MP4_5: [[fallthrough]];
        case VIDEO_MP4_6: [[fallthrough]];
        case VIDEO_MP4_7: return SIMPLE_VIDEO_MP4;
        case VIDEO_MOV: return SIMPLE_VIDEO_MOV;
        case AUDIO_FLAC: return SIMPLE_AUDIO_FLAC;
        case AUDIO_RIFF: [[fallthrough]];
        case AUDIO_WAVE: return SIMPLE_AUDIO_WAVE;
        case VIDEO_AVI: return SIMPLE_VIDEO_AVI;
        case UNDETERMINED_VM: return SIMPLE_UNDETERMINED_WM;
        case IMAGE_BMP: return SIMPLE_IMAGE_BMP;
        case MAX: return 101;
        case INVALID: return 101;
    };
    return -1;
}
