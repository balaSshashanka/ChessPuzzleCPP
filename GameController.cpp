#include "GameController.h"
#include <iostream>
#include <fstream>
#include "Output.h"
using namespace std;

GameController::GameController()
{
     InitializeBuilding();
}

void GameController::InitializeBuilding()
{
     ObstacleLocation *locations = LoadObstaclePosition();
     BuildingMap = Building(locations);
}

ObstacleLocation *GameController::LoadObstaclePosition( )
{
     return new ObstacleLocation[5]
                 {{2,2,GameConfig::ENEMY_COMMANDER},
                  {0,8,GameConfig::TANK},
                  {5,3,GameConfig::MISSILE},
                  {7,9,GameConfig::HEROBOT},
                  {8,1,GameConfig::RADAR},
                 };


}
bool GameController::Simulate()
{
      Move *moves=new Move[GameConfig::MovesLength];
      int Path[GameConfig::Rows][GameConfig::Columns]={0};
      ObstacleLocation *orig;
      ObstacleLocation *dest;
      ObstacleLocation *location;

      user.MakeMoves(BuildingMap,moves,GameConfig::MovesLength);

      for(int i=0;i<GameConfig::Rows;i++)
      {
          for(int j=0;j<GameConfig::Columns;j++)
          {

                if(BuildingMap.GetObstacleType(i,j)==GameConfig::HEROBOT)
                {
                    location = new ObstacleLocation(i,j,GameConfig::HEROBOT);
                    orig = location;

                }
                else if(BuildingMap.GetObstacleType(i,j)==GameConfig::MISSILE)
                {
                    location = new ObstacleLocation(i,j,GameConfig::MISSILE);
                    MarkPos(Path,location);
                }
                else if(BuildingMap.GetObstacleType(i,j)==GameConfig::RADAR)
                {
                    location = new ObstacleLocation(i,j,GameConfig::RADAR);
                    MarkPos(Path,location);
                }
                else if(BuildingMap.GetObstacleType(i,j)==GameConfig::TANK)
                {
                    location = new ObstacleLocation(i,j,GameConfig::TANK);
                    MarkPos(Path,location);
                }
                else if(BuildingMap.GetObstacleType(i,j)==GameConfig::ENEMY_COMMANDER)
                {
                    location = new ObstacleLocation(i,j,GameConfig::ENEMY_COMMANDER);
                    dest = location;
                }


          }
      }

      Move *PrevMove = new Move(orig->GetFloor(),orig->GetRoom());
      Output* out;
      out = Output::getInstance();
      out->jsonMsg.append("{\"moves\":[\n\n");
      int i;

      for( i=0;i<GameConfig::MovesLength;i++)
      {

          if(!((moves[i].GetRow()==dest->GetFloor())&&moves[i].GetColumn()==dest->GetRoom()))
          {
               if( BuildingMap.IsValidMove(*PrevMove,moves[i])&&(moves[i].GetRow()!=-1&&moves[i].GetColumn()!=-1))
               {
                    out->jsonMsg.append(" \t{\"row\":\""+to_string(moves[i].GetRow())+"\",");
                    out->jsonMsg.append(" \"column\":\""+to_string(moves[i].GetColumn())+"\"},\n\n");
                    *PrevMove = moves[i];
                    continue;
               }
               else
               {
                    if( !BuildingMap.IsValidMove(*PrevMove,moves[i]))
                    {
                            out->jsonMsg.append("\n]}\n\n}");
                            out->jsonMsg.insert(2,"\n\"IsGameValid\":\"False\",\n\n" );
                    }
                     else if((moves[i].GetRow()!=-1&&moves[i].GetColumn()!=-1))
                     {
                            out->jsonMsg.insert(2,"\n\"IsGameValid\":\"True\",\n\n" );
                            out->jsonMsg.append("\"GameStatus\":\"Lose\"}") ;
                     }
                   return false;
               }
          }
          if(BuildingMap.IsValidMove(*PrevMove,moves[i]))
          {
              out->jsonMsg.append(" \t{\"row\":\""+to_string(moves[i].GetRow())+"\",");
              out->jsonMsg.append(" \"column\":\""+to_string(moves[i].GetColumn())+"\"}\n\n]},\n\n");
              out->jsonMsg.insert(2,"\n\n\"IsGameValid\":\"True\"," );
              out->jsonMsg.append("\"GameStatus\":\"Win\"" );
              out->jsonMsg.append("\n\n}");
              return true;
          }
          else
          {
               out->jsonMsg.append("\n\n]}\n\n}");
               out->jsonMsg.insert(2,"\n\"IsGameValid\":\"False\",\n\n" );
               return false;
          }
      }

      if(!((moves[i].GetRow()==dest->GetFloor())&&moves[i].GetColumn()==dest->GetRoom()))
      {
              out->jsonMsg.append("\n\n]}\n\n}");
              out->jsonMsg.insert(2,"\n\"IsGameValid\":\"False\",\n\n" );

      }
}


void GameController::MarkPos(int Path[GameConfig::Rows][GameConfig::Columns],ObstacleLocation* Location)
{
       switch(Location->GetObstacle())
       {
         case GameConfig::RADAR:
               {
                    MarkRow(Path,Location->GetFloor());
                    MarkCol(Path,Location->GetRoom());
                    MarkDiag(Path,Location->GetFloor(),Location->GetRoom());
               }
               break;
         case GameConfig::MISSILE:
               {
                     MarkDiag(Path,Location->GetFloor(),Location->GetRoom());
               }
               break;
         case GameConfig::TANK:
               {

                    MarkRow(Path,Location->GetFloor());
                    MarkCol(Path,Location->GetRoom());
               }
       }

}
void GameController::MarkRow(int Path[GameConfig::Rows][GameConfig::Columns],int row)
{

    for(int j=0;j<GameConfig::Columns;j++)
        Path[row][j]=-1;
}
void GameController::MarkCol(int Path[GameConfig::Rows][GameConfig::Columns],int col)
{

    for(int i=0;i<GameConfig::Columns;i++)
        Path[i][col]=-1;
}
void GameController::MarkDiag(int Path[GameConfig::Rows][GameConfig::Columns],int row,int col)
{
    int colInc=col+1;
    int rowInc=row;


    for(int i=row-1;i>=0  && colInc<GameConfig::Columns;i--){
        Path[i][colInc++]=-1;
    }

    colInc=col-1;
    for(int i=row-1;i>=0 && colInc>=0;i--)
        Path[i][colInc--]=-1;

    colInc=col+1;
    for(int i=row+1;i<GameConfig::Rows && colInc<GameConfig::Columns;i++)
        Path[i][colInc++]=-1;

    colInc=col-1;
    for(int i=row+1;i<GameConfig::Rows && colInc>=0;i++)
        Path[i][colInc--]=-1;

}
