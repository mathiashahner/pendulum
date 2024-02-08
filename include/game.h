#ifndef GAME_H
#define GAME_H

#include <info.h>
#include <pendulum.h>

class Game
{
public:
  Game();

  void init();
  void render();
  void update();
  void clean();
  void delay();
  void handleEvents();
  void setFrameStart();

  bool running();

private:
  const int fps = 60;
  const int frameDelay = 1000 / fps;

  Info *info;
  Pendulum **pendulums;

  bool isRunning;
  Uint32 frameStart;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Thread *thread;
};

#endif
