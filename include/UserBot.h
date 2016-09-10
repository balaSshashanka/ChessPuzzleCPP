#ifndef __USERBOT_H__
   #define __USERBOT_H__

#include "Building.h"
#include "Move.h"

class UserBot
{
public:
    void MakeMoves(Building BuildingPlan,Move moves[],int size);
};


#endif // __USERBOT_H__
