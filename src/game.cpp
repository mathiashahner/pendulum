#include <game.h>

#define NUM_PENDULUMS 1

Game::Game()
{
  isRunning = false;
}

void Game::init()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("Pendulum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);

  // info = new Info(renderer);

  pendulums = new Pendulum *[NUM_PENDULUMS];
  pendulums2 = new Pendulum2 *[NUM_PENDULUMS];

  for (int i = 0; i < NUM_PENDULUMS; i++)
  {
    double period = 60.0 / (i + 50.0);
    double length = pow((period / 2.0 / M_PI), 2.0) * GRAVITY;

    pendulums[i] = new Pendulum(renderer, length * 750, 10, 0xFFFFFFFF);
    pendulums2[i] = new Pendulum2(renderer, length * 750, 10, 0xFF00FFFF);
  }

  isRunning = true;
}

void Game::render()
{
  SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
  SDL_RenderClear(renderer);

  // info->render();

  for (int i = 0; i < NUM_PENDULUMS; i++)
  {
    pendulums[i]->render();
    pendulums2[i]->render();
  }

  SDL_RenderPresent(renderer);
}

void Game::update()
{
  // info->update();

  for (int i = 0; i < NUM_PENDULUMS; i++)
  {
    pendulums[i]->update();
    pendulums2[i]->update();
  }
}

void Game::clean()
{
  SDL_WaitThread(thread, NULL);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::handleEvents()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
  case SDL_QUIT:
    isRunning = false;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case SDLK_e:
      isRunning = false;
      break;
    }
    break;
  }
}

bool Game::running()
{
  return isRunning;
}

void Game::setFrameStart()
{
  frameStart = SDL_GetTicks();
}

void Game::delay()
{
  int frameTime = SDL_GetTicks() - frameStart;

  if (frameDelay > frameTime)
  {
    SDL_Delay(frameDelay - frameTime);
  }
}
