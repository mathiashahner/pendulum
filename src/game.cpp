#include <game.h>

#define NUM_PENDULUMS 100

Game::Game()
{
  isRunning = false;
}

static int interpolateColor(int c1, int c2, float t)
{
  int r1 = (c1 >> 16) & 0xFF;
  int g1 = (c1 >> 8) & 0xFF;
  int b1 = c1 & 0xFF;

  int r2 = (c2 >> 16) & 0xFF;
  int g2 = (c2 >> 8) & 0xFF;
  int b2 = c2 & 0xFF;

  int r = r1 + (int)((r2 - r1) * t);
  int g = g1 + (int)((g2 - g1) * t);
  int b = b1 + (int)((b2 - b1) * t);

  return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

void Game::init()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("Pendulum", 0, 0, 720, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);

  // info = new Info(renderer);

  // pendulums = new Pendulum *[NUM_PENDULUMS];
  doublePendulums = new DoublePendulum *[NUM_PENDULUMS];

  for (int i = 0; i < NUM_PENDULUMS; i++)
  {
    float t = (float)i / (NUM_PENDULUMS - 1);
    int interpolated_color = interpolateColor(0x000000, 0xFFFFFF, t);

    printf("#%06X\n", interpolated_color);

    double period = 60.0 / (i + 50.0);
    double length = pow((period / 2.0 / M_PI), 2.0) * GRAVITY;

    // pendulums[i] = new Pendulum(renderer, i + 100, 2, 0xFFFFFFFF);
    doublePendulums[i] = new DoublePendulum(renderer, i + 100, i + 100, 2, interpolated_color);
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
    // pendulums[i]->render();
    doublePendulums[i]->render();
  }

  SDL_RenderPresent(renderer);
}

void Game::update()
{
  // info->update();

  for (int i = 0; i < NUM_PENDULUMS; i++)
  {
    // pendulums[i]->update();
    doublePendulums[i]->update();
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
