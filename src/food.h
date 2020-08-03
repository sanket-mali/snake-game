#ifndef FOOD_H
#define FOOD_H

#include<SDL.h>
#include<vector>
#include<iostream>

enum food_type {green = 20, yellow=10, brown=5};
class Food {
    public:
    Food(int x, int y,food_type type=food_type::brown) {
        // std::cout<<"#########################"<<type<<std::endl;
        this->loc_x = x;
        this->loc_y = y;
        this->type = type;
    }
    Food *createFood(int x, int y, food_type type);
    Food getFood(int x, int y);
    int getScore(food_type type);
    std::vector<int>getLocation();
    std::vector<int> getColor(food_type type);
    food_type getType();
    private:
    int loc_x;
    int loc_y;
    food_type type;
};

#endif