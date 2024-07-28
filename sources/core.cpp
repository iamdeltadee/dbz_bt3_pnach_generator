#include <iostream>
#include <sstream>
#include <fstream>  

#include "core.h"
#include "logger.h"


Core::Core()
{
}


Core::~Core()
{
}


void Core::Init()
{
    InitializeCharacters();
    LOG(INFO, "Core initialized");

    CreatePnachFile();
    LOG(INFO, "Pnach file created");
}


void Core::InitializeCharacters()
{
    for (int i = 0; i < NUM_CHARACTERS; i++)
    {
        mCharacters[i] = Character(characterDefs::charactersData[i]);
#ifdef LOGGER_ENABLED
        LOG(INFO, "CHARACTER %i DATA - NAME: %s \n -- LEVEL: %i, HP BARS: %i, POWER: %lli", i, mCharacters[i].GetName(), mCharacters[i].GetLevel(), mCharacters[i].GetHelthBars(), mCharacters[i].GetPower());
#endif
    }
}


void Core::CreatePnachFile()
{
    std::ofstream outfile ("A422BB13.pnach");

    outfile << "// ULTIMATE BUDOKAI TENKAICHI 3 MOD\n// by Delta De\n" << std::endl;

    outfile << "// CHARACTER HEALTH\n" << std::endl;

    for (int i = 0; i < NUM_CHARACTERS; ++i)
    {
        outfile << "// " << mCharacters[i].GetName() << " HP"<< std::endl;
        outfile << healthBarTools::GetHealthBarString(mCharacters[i]) << std::endl;
        outfile << std::endl;
    }

    outfile << "// CHARACTER POTARAS\n" << std::endl;

    for (int i = 0; i < NUM_CHARACTERS; ++i)
    {
        Character& character = mCharacters[i];
        if(character.GetBaseId() != BaseCharacterId::Unset)
        {
            outfile << "// " << mCharacters[i].GetName() << " HP"<< std::endl;
            outfile << healthBarTools::GetHealthBarString(mCharacters[i]) << std::endl;
            outfile << std::endl;
        }
    }

    outfile.close();
}


std::string miscUtils::GetHexString(int value)
{
    std::stringstream stream;

    stream << std::setfill ('0') << std::setw(8) << std::hex << value;

    std::string out( stream.str() );

    return out;
}


std::string healthBarTools::GetHealthBarString(const Character& character)
{
    const int healthValue = character.GetHelthBars() * healthPerBar;

    const std::string address = miscUtils::GetHexString(healthBarTools::mHPAddressStart + healthBarTools::mHPAddressOffset * character.GetIndex());
    const std::string health = miscUtils::GetHexString(healthValue);

    std::ostringstream oss;
    oss << "patch=1,EE," << address << ",extended," << health;
    const std::string out = oss.str();

    return out;
}


std::string potaraTools::GetPotaraString(const Character& character, int potaraLine, const char* potaraOne, const char* potaraTwo)
{
    const std::string address = miscUtils::GetHexString(potaraTools::mPotaraAdressesStart + potaraTools::mCharacterOffset * character.GetBaseIndex());

    std::ostringstream oss;
    oss << "patch=1,EE," << address << ",extended," << potaraOne << potaraTwo;
    const std::string out = oss.str();

    return out;
}


// if add2v=="0081 Medical Machine" then potara1v=0x81; potara2v=0x00 end
// if add2v=="0089 Launch's Support" then potara1v=0x89; potara2v=0x00 end
// end
// function PotaraEditorWindow.OnAdd2Clicked()
//     PotaraEditorWindow.bAdd2Enabled = not PotaraEditorWindow.bAdd2Enabled;
//     if( PotaraEditorWindow.bAdd2Enabled == true ) then
//      if GameCode=="SLES_549.45" then --when eu version
//         SkillTypeF()
//         DetectPotaraModeF()
//         if add2v~="SKILL TYPE" then                                               potara   0000
//         if add2v~="STRATEGY TYPE" then                                            potara   0000
//         406B99A8
//            writeBytes(0x206B9988+((56*character)+(16*customnumber)+(2*potaraslot)), potara1v,potara2v)


//NORMAL POTARA LIST

//ABILITY TYPE
//0001 Attack Up 1
//0002 Attack Up 2
//0003 Attack Up 3
//0004 Defense Up 1
//0005 Defense Up 2
//0006 Defense Up 3
//0007 Ki Power Up 1
//0008 Ki Power Up 2
//0009 Ki Power Up 3
//000A Super Up 1
//000B Super Up 2
//000C Super Up 3
//000D Attack Up 2 & Defense Down 1
//000E Defense Up 2 & Attack Down 1
//000F Ki Power Up 2 & Super Down 1
//0010 Super Up 2 & Power Down 1
//0011 Attack Up 3 & Super Down 1
//0012 Defense Up 3 & Attack Down 2
//0013 Ki Power Up 3 & Defense Down 1
//0014 Super Up 3 & Power Down 2
//0015 Attack Up 3 & Defense Down 2
//0016 Defense Up 3 & Power Down 1
//0017 Power Up 3 & Super Down 2
//0018 Super Up 3 & Attack Down 1

//SKILL TYPE
//0023 Flight
//0024 Unleash Latent Power 1
//0025 Unleash Latent Power 2
//0026 Unleash Latent Power 3
//0027 Ki Control
//0028 Dragon Dash Mastery
//0029 High Spot
//002A Essence of Sight
//002B Warrior Lineage
//002C Halo
//002D Demon Seal
//002E Satisfying Blow
//002F Active Heart
//0030 Indomitable Fighting Spirit
//0031 Mind Breaker
//0032 Gigantic Power
//0033 Rising Fighting Spirit
//0034 Secret Measures
//0035 Proof of Friendship
//0036 Dende's Healing Ability
//0037 Eternal Life
//0038 Tension Up
//0039 High Tension
//003A Water Blessing
//003B Spiritual Control
//003C Lover of Justice
//003D Evil Ambitions
//003E Dragon Heart
//003F Dragon Beat
//0040 Dragon Spirit
//0041 Confidence
//0042 Battle Control
//0043 Kibito's Secret Art
//0044 Persistent Threat
//0045 Miracle Master
//0046 Exquisite Skill
//0047 Quick Return
//0048 High Pressure
//0049 Unleash Ki
//004A Power of Rage
//004B Dragon Power
//004C Latent Energy!
//004D Fighting Spirit!
//004E Indignation!
//004F Serious!
//0050 Hatred of Saiyans
//0051 Rush Blast 1
//0052 Rush Blast 2
//0053 Rush Blast 3
//0054 Guard Master
//0055 Mirage
//0056 Warrior's Will
//0057 Evil Pride
//0058 Perfect Guard
//0059 Sparking Plus
//005A Style of the Strong
//005B Emperor's Aura
//005C Miracle Sparking
//005D Savior
//005E Light Body
//005F Power Body
//0060 Ultimate Body
//0061 Draconic Aura
//0062 Master Strike
//0063 Master Blast
//0064 Master Throw
//0065 Charged Attack
//0066 Quick Fast Attack
//0067 Dragon Break
//0068 Dragon Crush
//0069 Vanishing Break
//006A Vanishing Rush
//006B Combo Master
//006C Quick Charge
//006D Super Senses
//006E Broly's Ring
//006F Namek Power
//0070 Earth Power
//0071 Universal Power
//0072 Aura Charge Blue
//0073 Aura Charge Purple
//0074 Aura Charge Yellow
//0075 Aura Charge Red
//0076 Aura Charge Green
//0077 Aura Charge White
//0078 Aura Charge Pink
//0079 Aura Charge Violet
//007A Aura Charge Ultimate
//007B Aura Charge Ultimate 3
//007C Aura Charge Ultimate 4
//007D Master Roshi's Training
//007E King Kai's Training
//007F #18's Kiss
//0080 #17's Scarf
//0081 Medical Machine
//0089 Launch's Support

//STRATEGY TYPE
//008A Goku Type
//008B Vegeta Type
//008C Gohan Type
//008D Trunks Type
//008E Piccolo Type
//008F Krillin Type
//0090 Tien Type
//0091 Chiaotzu Type
//0092 Yajirobe Type
//0093 Frieza Type
//0094 Cell Type
//0095 Majin Buu Type
//0096 Broly Type
//0097 Ginyu Type
//0098 Recoome Type

//RED POTARA LIST
//00A3 Ultimate Warrior  1
//00A4 Ultimate Warrior  2
//00A5 Ultimate Warrior  3
//00A6 Ultimate Warrior  4
//00A7 Ultimate Warrior  5
//00A8 Ultimate Warrior  6
//00A9 Ultimate Warrior  7
//00AA Ultimate Warrior  8
//00AB Attack -25 
//00AC Attack -24 
//00AD Attack -23 
//00AE Attack -22 
//00AF Attack -21 
//00B0 Attack -20 
//00B1 Attack -19 
//00B2 Attack -18 
//00B3 Attack -17 
//00B4 Attack -16 
//00B5 Attack -15 
//00B6 Attack -14 
//00B7 Attack -13 
//00B8 Attack -12 
//00B9 Attack -11 
//00BA Attack -10 
//00BB Attack -9 
//00BC Attack -8 
//00BD Attack -7 
//00BE Attack -6 
//00BF Attack -5 
//00C0 Attack -4 
//00C1 Attack -3 
//00C2 Attack -2 
//00C3 Attack -1 
//00C4 Attack 0 
//00C5 Attack 1 
//00C6 Attack 2 
//00C7 Attack 3 
//00C8 Attack 4 
//00C9 Attack 5 
//00CA Attack 6 
//00CB Attack 7 
//00CC Attack 8 
//00CD Attack 9 
//00CE Attack 10 
//00CF Attack 11 
//00D0 Attack 12 
//00D1 Attack 13 
//00D2 Attack 14 
//00D3 Attack 15 
//00D4 Attack 16 
//00D5 Attack 17 
//00D6 Attack 18 
//00D7 Attack 19 
//00D8 Attack 20 
//00D9 Attack 21 
//00DA Attack 22 
//00DB Attack 23 
//00DC Attack 24 
//00DD Attack 25 
//00DE Attack 26 
//00DF Attack 27 
//00E0 Attack 28 
//00E1 Attack 29 
//00E2 Attack 30 
//00E3 Attack 31 
//00E4 Attack 32 
//00E5 Attack 33 
//00E6 Attack 34 
//00E7 Attack 35 
//00E8 Attack 36 
//00E9 Attack 37 
//00EA Attack 38 
//00EB Attack 39 
//00EC Attack 40 
//00ED Attack 41 
//00EE Attack 42 
//00EF Attack 43 
//00F0 Attack 44 
//00F1 Attack 45 
//00F2 Attack 46 
//00F3 Attack 47 
//00F4 Attack 48 
//00F5 Attack 49 
//00F6 Attack 50 
//00F7 Defense -25 
//00F8 Defense -24 
//00F9 Defense -23 
//00FA Defense -22 
//00FB Defense -21 
//00FC Defense -20 
//00FD Defense -19 
//00FE Defense -18 
//00FF Defense -17 
//0100 Defense -16 
//0101 Defense -15 
//0102 Defense -14 
//0103 Defense -13 
//0104 Defense -12 
//0105 Defense -11 
//0106 Defense -10 
//0107 Defense -9 
//0108 Defense -8 
//0109 Defense -7 
//010A Defense -6 
//010B Defense -5 
//010C Defense -4 
//010D Defense -3 
//010E Defense -2 
//010F Defense -1 
//0110 Defense 0 
//0111 Defense 1 
//0112 Defense 2 
//0113 Defense 3 
//0114 Defense 4 
//0115 Defense 5 
//0116 Defense 6 
//0117 Defense 7 
//0118 Defense 8 
//0119 Defense 9 
//011A Defense 10 
//011B Defense 11 
//011C Defense 12 
//011D Defense 13 
//011E Defense 14 
//011F Defense 15 
//0120 Defense 16 
//0121 Defense 17 
//0122 Defense 18 
//0123 Defense 19 
//0124 Defense 20 
//0125 Defense 21 
//0126 Defense 22 
//0127 Defense 23 
//0128 Defense 24 
//0129 Defense 25 
//012A Defense 26 
//012B Defense 27 
//012C Defense 28 
//012D Defense 29 
//012E Defense 30 
//012F Defense 31 
//0130 Defense 32 
//0131 Defense 33 
//0132 Defense 34 
//0133 Defense 35 
//0134 Defense 36 
//0135 Defense 37 
//0136 Defense 38 
//0137 Defense 39 
//0138 Defense 40 
//0139 Defense 41 
//013A Defense 42 
//013B Defense 43 
//013C Defense 44 
//013D Defense 45 
//013E Defense 46 
//013F Defense 47 
//0140 Defense 48 
//0141 Defense 49 
//0142 Defense 50 
//0143 Strength Enhancement +30k HP
//0144 Strength Reduction -30k HP
//0145 Blast Clash Weakened (Small)
//0146 Blast Clash Weakened (Medium)
//0147 Blast Clash Weakened (Large)
//0148 Absolutely Invincible Body
//0149 Go To Hell
//014A Super Mode
//014B Extreme Hand to Hand
//014C Extreme Energy Blast
//014D Extreme Blast
//014E Extreme Defense
//014F Resistor
//0150 Super Regeneration Cells
//0151 Complete Ki Control
//0152 God of Battle
//0153 Fierce God
//0154 Strength Reduction -10k HP
//0155 Strength Reduction -20k HP
//0156 Limitbreaker
//0157 Inherited Power