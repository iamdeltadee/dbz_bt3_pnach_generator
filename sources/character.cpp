#include "character.h"


int charUtils::CalculateLevel(long long power)
{
    long long number = power;
    int count = 0;
    while (number !=0) {   
        count++;  
        number/=10;
    } 
    return count > 0 ? count : 1;
};


int charUtils::CalculateBars(int level)
{
    const int bars = level / 2;
    return bars > 0 ? bars : 1;
};


Character::Character(const CharacterData& data) : mData(data)
{
    mLevel = charUtils::CalculateLevel(data.mPower);
    mHealthBars = charUtils::CalculateBars(mLevel);
}


CharacterId Character::GetId() const
{
    return mData.mId;
}


BaseCharacterId Character::GetBaseId() const
{
    return mData.mBaseId;
}


int Character::GetIndex() const
{
    return static_cast<int>(mData.mId);
}


int Character::GetBaseIndex() const
{
    return static_cast<int>(mData.mBaseId);
}


const char* Character::GetName() const
{
    return mData.mName;
}


long long Character::GetPower() const
{
    return mData.mPower;
}


int Character::GetLevel() const
{
    return mLevel;
}


int Character::GetHelthBars() const
{
   return mHealthBars;
}
