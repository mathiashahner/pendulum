#include <double-pendulum.h>

DoublePendulum::DoublePendulum(SDL_Renderer *renderer, double firstLength, double secondLength, double radius, Uint32 color)
{
  this->radius = radius;
  this->renderer = renderer;
  this->firstLength = firstLength;
  this->secondLength = secondLength;

  this->vars = std::vector<double>(10);
  this->vars[TH1] = MAX_AMPLITUDE;

  this->firstLine = new Line(renderer, 0, 0, 0, 0, color);
  this->secondLine = new Line(renderer, 0, 0, 0, 0, color);

  this->firstCircle = new Circle(renderer, 0, 0, radius, color);
  this->secondCircle = new Circle(renderer, 0, 0, radius, color);
}

DoublePendulum::~DoublePendulum()
{
}

void DoublePendulum::update()
{
  int width, height, screenCenterX, screenCenterY;

  SDL_GetRendererOutputSize(renderer, &width, &height);
  screenCenterX = width / 2;
  screenCenterY = height / 3;

  step();
  modify();

  y1 *= -1;
  y2 *= -1;

  x1 += screenCenterX;
  y1 += screenCenterY;
  x2 += screenCenterX;
  y2 += screenCenterY;

  this->firstLine->update(screenCenterX, screenCenterY, x1, y1);
  this->secondLine->update(x1, y1, x2, y2);

  this->firstCircle->update(x1, y1, this->radius);
  this->secondCircle->update(x2, y2, this->radius);
}

static void zeroArray(std::vector<double> arr)
{
  int n = arr.size();

  for (int i = 0; i < n; i++)
    arr[i] = 0;
};

void DoublePendulum::step()
{
  int N = vars.size();

  if (this->inp_.size() < N)
  {
    this->inp_ = std::vector<double>(N);
    this->k1_ = std::vector<double>(N);
    this->k2_ = std::vector<double>(N);
    this->k3_ = std::vector<double>(N);
    this->k4_ = std::vector<double>(N);
  }

  auto inp = this->inp_;
  auto k1 = this->k1_;
  auto k2 = this->k2_;
  auto k3 = this->k3_;
  auto k4 = this->k4_;

  for (int i = 0; i < N; i++)
    inp[i] = vars[i];

  zeroArray(k1);
  evaluate(inp, k1);

  for (int i = 0; i < N; i++)
    inp[i] = vars[i] + k1[i] * TIME_STEP / 2;

  zeroArray(k2);
  evaluate(inp, k2);

  for (int i = 0; i < N; i++)
    inp[i] = vars[i] + k2[i] * TIME_STEP / 2;

  zeroArray(k3);
  evaluate(inp, k3);
  for (int i = 0; i < N; i++)
    inp[i] = vars[i] + k3[i] * TIME_STEP;

  zeroArray(k4);
  evaluate(inp, k4);
  for (int i = 0; i < N; i++)
    vars[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) * TIME_STEP / 6;
}

static double limitAngle(double angle)
{
  if (angle > M_PI)
  {
    double n = floor((angle - -M_PI) / (2 * M_PI));
    return angle - 2 * M_PI * n;
  }
  else if (angle < -M_PI)
  {
    double n = floor(-(angle - M_PI) / (2 * M_PI));
    return angle + 2 * M_PI * n;
  }

  return angle;
};

void DoublePendulum::modify()
{
  double theta1 = limitAngle(vars[TH1]);

  if (theta1 != vars[TH1])
  {
    this->theta1 = theta1;
    vars[TH1] = theta1;
  }

  double theta2 = limitAngle(vars[TH2]);

  if (theta2 != vars[TH2])
  {
    this->theta2 = theta2;
    vars[TH2] = theta2;
  }

  move();

  auto rate = std::vector<double>(vars.size());

  evaluate(vars, rate);

  vars[TH1PP] = rate[TH1P];
  vars[TH2PP] = rate[TH2P];

  getEnergyInfo();
}

void DoublePendulum::move()
{
  double theta1 = vars[TH1];
  double sinTheta1 = sin(theta1);
  double cosTheta1 = cos(theta1);
  double theta2 = vars[TH2];
  double sinTheta2 = sin(theta2);
  double cosTheta2 = cos(theta2);
  double L1 = this->firstLength;
  double L2 = this->secondLength;

  this->x1 = L1 * sinTheta1;
  this->y1 = -L1 * cosTheta1;
  this->x2 = x1 + L2 * sinTheta2;
  this->y2 = y1 - L2 * cosTheta2;

  double v1x = vars[TH1P] * L1 * cosTheta1;
  double v1y = vars[TH1P] * L1 * sinTheta1;
  double v2x = v1x + vars[TH2P] * L2 * cosTheta2;
  double v2y = v1y + vars[TH2P] * L2 * sinTheta2;

  this->firstCircle->velocityX = v1x;
  this->firstCircle->velocityY = v1y;
  this->secondCircle->velocityX = v2x;
  this->secondCircle->velocityY = v2y;
}

void DoublePendulum::evaluate(std::vector<double> &vars, std::vector<double> &change)
{
  zeroArray(change);
  change[TIME] = 1.0;

  double th1 = vars[TH1];
  double dth1 = vars[TH1P];
  double th2 = vars[TH2];
  double dth2 = vars[TH2P];
  double m1 = this->firstCircle->mass;
  double m2 = this->secondCircle->mass;
  double L1 = this->firstLength;
  double L2 = this->secondLength;

  change[TH1] = dth1;

  double num = -GRAVITY * (2 * m1 + m2) * sin(th1);
  num = num - GRAVITY * m2 * sin(th1 - 2 * th2);
  num = num - 2 * m2 * dth2 * dth2 * L2 * sin(th1 - th2);
  num = num - m2 * dth1 * dth1 * L1 * sin(2 * (th1 - th2));
  num = num / (L1 * (2 * m1 + m2 - m2 * cos(2 * (th1 - th2))));
  change[TH1P] = num;

  change[TH2] = dth2;

  num = (m1 + m2) * dth1 * dth1 * L1;
  num = num + GRAVITY * (m1 + m2) * cos(th1);
  num = num + m2 * dth2 * dth2 * L2 * cos(th1 - th2);
  num = num * 2 * sin(th1 - th2);
  num = num / (L2 * (2 * m1 + m2 - m2 * cos(2 * (th1 - th2))));
  change[TH2P] = num;
}

void DoublePendulum::getEnergyInfo()
{
  double ke = this->firstCircle->getKineticEnergy() + this->secondCircle->getKineticEnergy();

  double pe = GRAVITY * this->firstCircle->mass * (this->y1 - -this->firstLength) +
              GRAVITY * this->secondCircle->mass * (this->y2 - (-this->firstLength - this->secondLength));

  vars[KE] = ke;
  vars[PE] = pe;
  vars[TE] = ke + pe;
}

void DoublePendulum::render()
{
  firstLine->render();
  secondLine->render();

  firstCircle->render();
  secondCircle->render();
}
