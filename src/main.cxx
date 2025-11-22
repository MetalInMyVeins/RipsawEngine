#include "Engine.hxx"

int main(int argv, char** argc)
{
  Engine engine;
  if (engine.init() == false)
  {
    return -1;
  }
  engine.run();
  engine.shutdown();
  return 0;
}

