#include "game.h"
#include <iostream>
#include<vector>
#include "SDL.h"
#include<cstdlib>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(1, static_cast<int>(grid_width-1)),
      random_h(1, static_cast<int>(grid_height-1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  // std::srand(time(0));
  int food_count = std::rand() % 2;
  std::cout<<"###############################################>> "<<food_count<<std::endl;
  int num = 0;
  while (num <= food_count) {
    x = random_w(engine);
    y = random_h(engine);
    // std::srand(time(0));
    int type = std::rand() % 3;
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      // SDL_Point tmp;
      Food *tmp = new Food(x,y, food_type(type));
      // tmp.x = x;
      // tmp.y = y;
      this->food.push_back(*tmp);
      // return;
    }
    num ++;
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  int index = 0;
  std::vector<Food> tmp = food;
  for(auto i:tmp){
    std::vector<int>point = i.getLocation();
    // std::cout<<"==================  "<<point[0]<<std::endl;
    // std::cout<< new_x<<"==================  "<<new_y<<std::endl;
    // Check if there's food over here
    if (point[0] == new_x && point[1] == new_y) {
      int scr = i.getScore(i.getType());
      // std::cout<<"================================== "<<scr<<std::endl;
      score += scr;
      // std::cout<< i.getType()<<"==================  "<<i.getLocation()[0]<<std::endl;
      food.erase(food.begin()+index);
      PlaceFood();
      // Grow snake and increase speed.
      snake.GrowBody();
    //   if(i.getType() == 0)
    //     snake.speed += 0.02;
    //   else if(i.getType() == 1)
    //     snake.speed += 0.01;
    //   else
    //     snake.speed += 0.005;
      break;
    }
    index++;
  }
  std::cout<<"================================== "<<index<<std::endl;
  // food.erase(food.begin()+(index-1));
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }