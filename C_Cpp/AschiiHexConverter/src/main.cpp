#include "windows.h"
#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>

static void copyResultToFile(const char *binaryData, int size);
static void copyResultToStd(const char *binaryData, int size);
static void copyResultToClipboard(const char *binaryData, int size);

int main() {
    while (true) {
        std::string hexString;
        std::cout << "Paste your hex string:" << std::endl;
        std::getline(std::cin, hexString);

        const char digitOffset = 48;
        const char bigLetterOffset = 55;
        const char smallLetterOffset = 87;
        std::unordered_map<char, char> offsetMap{
            {'0', digitOffset},
            {'1', digitOffset},
            {'2', digitOffset},
            {'3', digitOffset},
            {'4', digitOffset},
            {'5', digitOffset},
            {'6', digitOffset},
            {'7', digitOffset},
            {'8', digitOffset},
            {'9', digitOffset},
            {'A', bigLetterOffset},
            {'B', bigLetterOffset},
            {'C', bigLetterOffset},
            {'D', bigLetterOffset},
            {'E', bigLetterOffset},
            {'F', bigLetterOffset},
            {'a', smallLetterOffset},
            {'b', smallLetterOffset},
            {'c', smallLetterOffset},
            {'d', smallLetterOffset},
            {'e', smallLetterOffset},
            {'f', smallLetterOffset},
        };

        auto test = offsetMap['S'];

        std::deque<char> convertedHexBytes;
        char currentByte = 0;
        int nibblesRead = 0;

        for (auto hexChar : hexString) {
            auto offset = offsetMap[hexChar];

            if (offset != 0) {
                char nibble = hexChar - offset;
                auto isNibbleHighInByte = nibblesRead % 2 == 0;
                if (isNibbleHighInByte) {
                    currentByte |= (nibble << 4);
                } else {
                    currentByte |= nibble;
                    convertedHexBytes.push_back(currentByte);
                    currentByte = 0;
                }
                nibblesRead++;
            }
        }

        const int size = convertedHexBytes.size();
        auto hexBytesArray = std::make_unique<char[]>(size);
        std::copy(convertedHexBytes.cbegin(), convertedHexBytes.cend(), hexBytesArray.get());
        copyResultToFile(hexBytesArray.get(), size);
        copyResultToStd(hexBytesArray.get(), size);
        copyResultToClipboard(hexBytesArray.get(), size);

        std::cout << std::endl;
    }

    return 0;
}

static void copyResultToFile(const char *binaryData, int size) {
    std::ofstream output("conversion_result", std::ios::binary);
    std::copy(binaryData, binaryData + size, std::ostreambuf_iterator<char>(output));
    output.close();
}

static void copyResultToStd(const char *binaryData, int size) {
    std::copy(binaryData, binaryData + size, std::ostream_iterator<char>(std::cout));
}


static void copyResultToClipboard(const char *binaryData, int size) {
    size += 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, size);
    memcpy(GlobalLock(hMem), binaryData, size);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    // will trim the data before first null character, so you will not be able to insert binary data containg null
    // more info here https://superuser.com/questions/946533/is-there-any-way-to-copy-null-bytes-ascii-0x00-to-the-clipboard-on-windows
    SetClipboardData(CF_OEMTEXT, hMem);
    CloseClipboard();
}