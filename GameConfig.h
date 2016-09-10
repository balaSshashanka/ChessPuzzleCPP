#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__


class GameConfig{
    public :
        static const int Rows    = 10;
        static const int Columns = 10;
        static const int MovesLength = 50;
        enum ObstacleTypes {NONE,HEROBOT,RADAR,MISSILE,TANK,ENEMY_COMMANDER};
        /*
            here,
            HEROBOT is knight
            RADAR is queen
            MISSILE is bishop
            TANK is rook
            ENEMY_COMMANDER is king
            NONE is empty cell
        */

};
#endif // __GAMECONFIG_H__
