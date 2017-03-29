//
// Created by root on 3/29/17.
//

#ifndef COMS327_DUNGEON_H
#define COMS327_DUNGEON_H

#define d_MIN_HEIGHT 105
#define d_MIN_WIDTH 160

#define r_MIN_W 7
#define r_MIN_H 5

#define NUM_ROOMS 15
#define NUM_STAIRS 2
#define MAX_TRIES 2000

#define IMPASS 256
#define ROCK ' '
#define CORRIDOR '#'
#define rm_FLOOR '.'
#define STAIR_UP '<'
#define STAIR_DOWN '>'

#include <cstdio>

class Dungeon {
private:
    int height;
    int width;
    Cell* cells;
    Room* rooms;

protected:
    void placeStairs();
    void applyProperties();
    bool checkRoom(Room *room);
    void placeRooms();
    void setBoundaries();
    int compareDistance(Room *ref, Room *room1, Room *room2);
    int compareDistanceCtrd(Room *ref, Room room1, Room room2);


public:
    Dungeon(int height, int width, int num_rooms);
    ~Dungeon();
    int writeDungeon(FILE *file);
    int writeRooms(FILE *file);
    void drawCorridors();
    void applyRoom(Room *room);
};

class Room{
private:
    int y;
    int x;
    int width;
    int height;
public:
    void getCentroid(int *y, int *x){
        //may be off by 1 due to integer division, but good enough for this purpose
        *y = this->y + height/2;
        *x = this->x+ width/2;
    }
    Room* getClosestRoom(Room *rooms);
    int getY() const {
        return y;
    }

    void setY(int y) {
        Room::y = y;
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        Room::x = x;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        Room::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        Room::height = height;
    }
};

class Cell{
private:
    int type;
    int x;
    int y;
    int hardness;
public:
    int getType() const {
        return type;
    }

    void setType(int type) {
        Cell::type = type;
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        Cell::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Cell::y = y;
    }

    int getHardness() const {
        return hardness;
    }

    void setHardness(int hardness) {
        Cell::hardness = hardness;
    }
};


#endif //COMS327_DUNGEON_H
