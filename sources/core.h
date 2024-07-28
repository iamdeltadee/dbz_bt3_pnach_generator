#pragma once

#include <string>

#include "character.h"
#include "characters.h"


class Core
{
public:
    Core();
    ~Core();

    void Init();

private:
    Character mCharacters[NUM_CHARACTERS];

    void InitializeCharacters();
    void CreatePnachFile();
};


namespace miscUtils
{
    std::string GetHexString(int value);
} // namespace miscUtils


namespace healthBarTools
{
    constexpr int mHPAddressStart = 0x20562D80;
    constexpr int mHPAddressOffset = 0x10;
    constexpr int healthPerBar = 10000;

    std::string GetHealthBarString(const Character& character);
} // namespace healthBarTools


namespace potaraTools
{
    constexpr int mPotaraAdressesStart = 0x406B9988;
    constexpr int mCharacterOffset = 56;
    constexpr int mCustomNumberOffset = 0x10;

    std::string GetPotaraString(const Character& character, int potaraLine, const char* potaraOne, const char* potaraTwo);
} // namespace healthBarTools
