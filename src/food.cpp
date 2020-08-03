#include "food.h"
#include<SDL.h>
#include<vector>
#include<iostream>

Food* Food::createFood(int x, int y, food_type type=food_type::brown) {
    Food *food_object = new Food(x,y, type);
    return food_object; 
}

int Food::getScore(food_type type) {
    switch(type) {
        case 2:
            return 5;
            break;
        case 1:
            return 10;
            break;
        case 0:
            return 20;
            break;
        default:
            return -1;
            break;
    }
}
std::vector<int> Food::getColor(food_type type) {
    std::vector<int> color;
    switch(type) {
        case 2:
            color = {92,52,15,255};
            break;
        case 1:
            color = {227,194,30,255};
            break;
        case 0:
            color = {0,255,0,255};
            break;
    }
    return color;
}
std::vector<int> Food::getLocation() {
    return {this->loc_x, this->loc_y};
}
food_type Food::getType() {
    return this->type;
}