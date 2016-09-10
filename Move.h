#ifndef __MOVE_H__
#define __MOVE_H__


class Move{

    private:
            unsigned int room;
            unsigned int floor;

    public:
            Move();
            Move(unsigned int room,unsigned int floor);
            void SetRow(unsigned int floor);
            void SetColumn(unsigned int room);
            unsigned int GetRow();
            unsigned int GetColumn();

};
#endif // __MOVE_H__
