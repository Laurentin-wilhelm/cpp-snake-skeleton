#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <thread>
#include "sys/ioctl.h"
#include "termios.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"


///////////////////////////////////////////////////////////////////////////////
/////// 🧑‍💻 FROM HERE you must complete 🧑‍💻 ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void add_snake(const std::vector<std::pair<int, int>> &snake, std::vector<int> &bg, int nx, int ny)
{
  
  for(auto &xy :snake)
  {int x = xy.first;
  int y = xy.second;
  bg[y*nx+x] = 3;


  }

}

void remove_snake(const std::vector<std::pair<int, int>> &snake, std::vector<int> &bg, int nx, int ny)
{
 for(auto &xy :snake)
  {int x = xy.first;
  int y = xy.second;
  bg[y*nx+x] = 0;
  }
}

std::array<int, 2> snake_movement(char key)
{ 
  std::array<int, 2> u;
  if(key =='z')
  {
    u[0]=0;
    u[1]=-1;
  }
    if(key =='q')
  {
    u[0]=-1;
    u[1]=0;
  }
    if(key =='s')
  {
    u[0]=0;
    u[1]=1;
  }
    if(key =='d')
  {
    u[0]=1;
    u[1]=0;
  }
  return u;
}

bool verifyBorder(const std::vector<std::pair<int, int>> &snake, int nx, int ny)
{
  
  std::pair<int, int> head = snake[0];
  int snake_len = snake.size();
  
    int x = head.first;
    int y = head.second;

    
    if (x == 0 || y == 0 || x == nx - 1 || y == ny - 1) return false;

    
    for (size_t i = 1; i < snake_len-1; i++) {
        if (head == snake[i]) return false;
    }

    
    return true;
}

std::vector<std::pair<int, int>> setupSnake(int snake_len)
{
  std::vector<std::pair<int, int>> snake(snake_len);
  int i;
  for (i = 0; i < snake_len; i++)
  {
    snake[i].first = 10 + i;
    snake[i].second = 10;
  }
  return snake;
}

void update_snake_coordinates(std::vector<std::pair<int, int>> &snake, bool eat, std::array<int, 2> dxdy)
{ int i;
  int snake_len = snake.size();
  
  

    // If snake eats, append a new segment
    if (eat) {
        snake.push_back(snake.back());
    }

    // Shift body segments from back to front
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Update head position
    std::pair<int, int> new_head(snake[0].first + dxdy[0], snake[0].second + dxdy[1]);
    snake[0] = new_head;
 
  
}
float lap = 200;
void startGame( float &lap, const int &nx, const int &ny, std::vector<std::pair<int, int>> &snake, std::vector<int> &bg)
{
  char key;
  std::array<int, 2> dxdy = {1, 0};
  std::array<int, 2> food = {0, 0};
  internal::createFood(bg, food, nx, ny);
  while (true)
  {
    internal::frameSleep(lap);
    if (internal::keyEvent())
    {
      std::cin >> key;
      dxdy = snake_movement(key);
    }
    internal::backgroundClear();
    add_snake(snake, bg, nx, ny);
    internal::printFrame(nx, ny, bg);
    remove_snake(snake, bg, nx, ny);
    bool out = verifyBorder(snake, nx, ny);
    if (out == false)
    {
      std::cerr << "Perdu💀💀" << std::endl;
      exit(1);
    }
    bool eat = internal::eatFood(food, snake);
    if (eat)
    {
      internal::createFood(bg, food, nx, ny);
    }
    update_snake_coordinates(snake, eat, dxdy);
    lap = lap * 0.99;
  }
}

int main()
{
  const int nx = 50;
  const int ny = 25;
  
  int snake_len = 3;

  std::vector<int> background = backgroundSetup(nx, ny);
  internal::printFrame(nx, ny, background);

  std::vector<std::pair<int, int>> snake = setupSnake(snake_len);

  startGame(lap, nx, ny, snake, background);
  return 0;
}