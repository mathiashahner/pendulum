#ifndef GAME_H
#define GAME_H

#define SDL_MAIN_HANDLED

#include <info.h>

class Game
{
public:
  Game();

  void init();
  void render();
  void update();
  void clean();
  void handleEvents();

  bool running();

private:
  const int fps = 60;
  const int frameDelay = 1000 / fps;

  Info *info;

  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Thread *thread;
};

#endif
