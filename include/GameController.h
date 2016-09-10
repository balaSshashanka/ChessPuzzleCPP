#ifndef __GAMECONTROLLER_H__
  #define __GAMECONTROLLER_H__

#include "Building.h"
#include "ObstacleLocation.h"
#include "Move.h"
#include "UserBot.h"
class GameController
{
    private:
        UserBot user;
        Building BuildingMap;
        //returns ObstacleLocations from one of the Question Sets
        ObstacleLocation * LoadObstaclePosition();
        //Funtion to create board object and place obstacles
        void InitializeBuilding();
        void MarkPos(int Path[GameConfig::Rows][GameConfig::Columns],ObstacleLocation* Location);
        void MarkRow(int Path[GameConfig::Rows][GameConfig::Columns],int row);
        void MarkCol(int Path[GameConfig::Rows][GameConfig::Columns],int col);
        void MarkDiag(int Path[GameConfig::Rows][GameConfig::Columns],int row,int col);


    public:
        GameController();
        bool Simulate();
};
#endif // __GAMECONTROLLER_H__
