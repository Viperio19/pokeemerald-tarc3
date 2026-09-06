#include "global.h"
#include "constants/trainers.h"

static enum TrainerPicID GetEmeraldTrainerPic(enum Gender gender)
{
    return gender == MALE ? TRAINER_PIC_BRENDAN : TRAINER_PIC_MAY;
}
static enum TrainerPicID GetRSTrainerPic(enum Gender gender)
{
    return gender == MALE ? TRAINER_PIC_RS_BRENDAN : TRAINER_PIC_RS_MAY;
}

static enum TrainerPicID GetKantoTrainerPic(enum Gender gender)
{
    return gender == MALE ? TRAINER_PIC_RED : TRAINER_PIC_LEAF;
}

enum TrainerPicID GetPlayerTrainerPic(enum Gender gender, enum GameVersion version)
{
    if (IS_PLAYER_ONE)
        return gender == MALE ? TRAINER_PIC_PLAYER_M : TRAINER_PIC_PLAYER_F;

    return gender == MALE ? TRAINER_PIC_PLAYER_2_M : TRAINER_PIC_PLAYER_2_F;

    switch (version)
    {
        case VERSION_SAPPHIRE:
        case VERSION_RUBY:
            return GetRSTrainerPic(gender);
        case VERSION_LEAF_GREEN:
        case VERSION_FIRE_RED:
            return GetKantoTrainerPic(gender);
        case VERSION_EMERALD:
        default:
            return GetEmeraldTrainerPic(gender);
    }
}

enum TrainerPicID GetPlayer2TrainerPic(enum Gender gender, enum GameVersion version)
{
    if (!IS_PLAYER_ONE)
        return gender == MALE ? TRAINER_PIC_PLAYER_M : TRAINER_PIC_PLAYER_F;

    return gender == MALE ? TRAINER_PIC_PLAYER_2_M : TRAINER_PIC_PLAYER_2_F;
}
