#ifndef CONSTANTS_H
#define CONSTANTS_H

// stala SCALE jest uzywana do przeskalowania wspolrzednych logicznych we wspolrzedne fizyczne
#define SCALE 50.0

#define DEFAULT_WOOD_THICKNESS 2.5 // rozmiar w centymetrach

#define INITIAL_PLANK_LENGTH 100.0 // rozmiar w centymetrach
#define INITIAL_PLANK_WIDTH 28.0 // rozmiar w centymetrach
#define INITIAL_PLANK_HEIGHT 2.5 // rozmiar w centymetrach

#define INITIAL_EUROPLANK_LENGTH 145.0 // rozmiar w centymetrach
#define INITIAL_EUROPLANK_WIDTH 20.0 // rozmiar w centymetrach
#define INITIAL_EUROPLANK_HEIGHT 1.0 // rozmiar w centymetrach

#define INITIAL_BEVEL_LENGTH 100.0 // rozmiar w centymetrach
#define INITIAL_BEVEL_WIDTH 23.0 // rozmiar w centymetrach
#define INITIAL_BEVEL_HEIGHT 23.0 // rozmiar w centymetrach

#define INITIAL_CHANNEL_LENGTH 100.0 // rozmiar w centymetrach
#define INITIAL_CHANNEL_WIDTH 23.0 // rozmiar w centymetrach
#define INITIAL_CHANNEL_HEIGHT 23.0 // rozmiar w centymetrach

#define INITIAL_EMPTY_PROFILE_LENGTH 100.0 // rozmiar w centymetrach
#define INITIAL_EMPTY_PROFILE_WIDTH 23.0 // rozmiar w centymetrach
#define INITIAL_EMPTY_PROFILE_HEIGHT 23.0 // rozmiar w centymetrach

#define PRICE_FOR_PLANK_QUADRATIC_METER 223 // cena w zl
#define PRICE_FOR_BEVEL_QUADRATIC_METER 264 // cena w zl
#define PRICE_FOR_CHANNEL_QUADRATIC_METER 164.5 // cena w zl
#define PRICE_FOR_EMPTY_PROFILE_QUADRATIC_METER 164.5 // cena w zl

#define PRICE_FOR_SHORT_RETRO_EUROPLANK_QUADRATIC_METER 172.23 // cena w zl
#define PRICE_FOR_LONG_RETRO_EUROPLANK_QUADRATIC_METER 94.19 // cena w zl
#define PRICE_FOR_SHORT_MODERN_EUROPLANK_QUADRATIC_METER 164.74 // cena w zl
#define PRICE_FOR_LONG_MODERN_EUROPLANK_QUADRATIC_METER 90.09 // cena w zl

#define PRICE_FOR_DECORATED_EDGES_PER_METER 6 // cena w zl

enum Object3D
{
    Plank, // deska
    Channel, // ceownik
    FullProfile, // profil pelny
    EmptyProfile, // profil przelotowy
    Bevel // katownik
};

enum WoodType
{
    Karbon,
    Retro,
    Modern
};

extern Object3D currentObject3D;
extern WoodType currentWoodType;
extern bool euroPlank;

#endif // CONSTANTS_H
