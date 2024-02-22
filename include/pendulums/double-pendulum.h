#ifndef DOUBLE_PENDULUM_H
#define DOUBLE_PENDULUM_H

#include <math.h>
#include <line.h>
#include <circle.h>
#include <vector>

#define GRAVITY 9.81
#define TIME_STEP 0.1
#define MAX_AMPLITUDE 90 * M_PI / 180.0

#define TH1 0
#define TH1P 1
#define TH2 2
#define TH2P 3
#define TH1PP 4
#define TH2PP 5
#define KE 6
#define PE 7
#define TE 8
#define TIME 9

class DoublePendulum
{
public:
  DoublePendulum(SDL_Renderer *renderer, double firstLength, double secondLength, double radius, Uint32 color);
  ~DoublePendulum();

  void update();
  void render();
  void step();
  void move();
  void modify();
  void getEnergyInfo();
  void evaluate(std::vector<double> &vars, std::vector<double> &change);

private:
  double radius;
  double firstLength;
  double secondLength;

  double theta1, theta2;
  double x1, y1;
  double x2, y2;

  std::vector<double> inp_;
  std::vector<double> k1_;
  std::vector<double> k2_;
  std::vector<double> k3_;
  std::vector<double> k4_;
  std::vector<double> vars;

  Line *firstLine;
  Line *secondLine;
  Circle *firstCircle;
  Circle *secondCircle;
  SDL_Renderer *renderer;
};

#endif
