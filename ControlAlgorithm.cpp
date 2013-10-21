enum HeatingZoneEnum {  Z1_HZ, Z2_HZ, Z3_HZ, SIDEWALK_HZ, UNDERDRIVEWAY_HZ,
                        SOLAR_HZ, COMPOST_HZ, LOTANK_HZ, HITANK_HZ,
                        SHOP_HZ, GEO_HZ, DHW_HZ,
                        BOILER_HZ,
                        CREEK_HZ };

#define HeatingZoneLast (CREEK_HZ)
#define HeatingZoneSize (HeatingZoneLast+1)

static int Priority [HeatingZoneSize] [HeatingZoneSize] = {
  { //1 2 3 sw U  S C  L  H  Sh G  D  B  C
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // Z1
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // Z2
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // Z3
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // SIDEWALK
    { 1,1,1,1, 0, 0,0,11,11, 0, 6.6?, 0, 0, 0 },   // UNDERDRIVEWAY
    { 2,2,2,2,13, 0,0,12,12, 5, 7, 9, 0,14 },   // SOLAR
    { 2,2,2,2,13, 0,0,12,12, 5, 7, 9, 0,14 },   // COMPOST
    { 3,3,3,3,13, 0,0, 0, 0, 6, 8,10, 0,14 },   // LOTANK
    { 3,3,3,3,13, 0,0, 0, 0, 6, 8,10, 0,14 },   // HITANK
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // SHOP
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // GEO
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 },   // DHW
    { 4,4,4,4, 0, 0,0, 0, 0, 6.5?, 0, 0, 0, 0 },   // BOILER
    { 0,0,0,0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 } }; // CREEK

static int MaxPriority = 14;

enum LoopEnum { DISTRIBUTION_LOOP,
                  HOUSE_INJ, SNOWMELT_INJ, STORAGE_INJ,
                SNOWMELT_LOOP  // = (BOILER | UNDER) & !(Z1 | Z2 | Z3 | Z4)
                STORAGE_LOOP
                DHW_LOOP,
                GEO_LOOP };

#define LoopLast (STORAGE_LOOP)
#define LoopSize (LoopLast+1)

static bool DependentPumps[ MaxPriority ] =
  {
    {},
    {},                                                                     //  1: UNDER       -> Z1..Z4
    { DISTRIBUTION_LOOP, SNOWMELT_INJ, STORAGE_INJ, STORAGE_LOOP },         //  2: SOLAR/CMPST -> Z1..Z4
    { DISTRIBUTION_LOOP, SNOWMELT_INJ, STORAGE_INJ, STORAGE_LOOP },         //  3: TANKS       -> Z1..Z4
    {},                                                                     //  4: BOILER      -> Z1..Z4
    { DISTRIBUTION_LOOP, HOUSE_LOOP, HOUSE_INJ, STORAGE_INJ, STORAGE_LOOP },//  5: SOLAR/CMPST -> SHOP
    { DISTRIBUTION_LOOP, HOUSE_LOOP, HOUSE_INJ, STORAGE_INJ, STORAGE_LOOP },//  6: TANKS       -> SHOP
    { DISTRIBUTION_LOOP, SNOWMELT_INJ, SNOWMELT_LOOP, HOUSE_LOOP },         //  6.5: BOILER -> SHOP
    { DISTRIBUTION_LOOP, SNOWMELT_INJ, SNOWMELT_LOOP, HOUSE_LOOP },         //  6.6: UNDER  -> GEO
    { DISTRIBUTION_LOOP, HOUSE_LOOP, STORAGE_LOOP, GEO_LOOP }, //  7
    { DISTRIBUTION_LOOP, HOUSE_LOOP, STORAGE_LOOP, GEO_LOOP }, //  8
    { DISTRIBUTION_LOOP, HOUSE_LOOP, STORAGE_LOOP, DHW_LOOP }, //  9
    { DISTRIBUTION_LOOP, HOUSE_LOOP, STORAGE_LOOP, DHW_LOOP }, // 10
    { DISTRIBUTION_LOOP, SNOWMELT_LOOP, STORAGE_LOOP },        // 11
    { STORAGE_LOOP },                                          // 12
    { DISTRIBUTION_LOOP, SNOWMELT_LOOP, STORAGE_LOOP },        // 13
