#include "RipsawEngine/Core/Timer.hxx"

void Timer::start()
{
  mRunning = true;
  mPaused = false;
  mStartTime = SDL_GetTicksNS();
  mPauseTime = 0;
}

void Timer::stop()
{
  mRunning = false;
  mPaused = false;
  mStartTime = 0;
  mPauseTime = 0;
}

void Timer::pause()
{
  if (mRunning == true and mPaused == false)
  {
    mPaused = true;
    mPauseTime = SDL_GetTicksNS() - mStartTime;
    mStartTime = 0;
  }
}

void Timer::resume()
{
  if (mRunning == true and mPaused == true)
  {
    mPaused = false;
    mStartTime = SDL_GetTicksNS() - mPauseTime;
    mPauseTime = 0;
  }
}

Uint64 Timer::elapsedNS()
{
  Uint64 elapsed{};
  
  if (mRunning)
  {
    if (mPaused == true)
    {
      elapsed = mPauseTime;
    }
    else
    {
      elapsed = SDL_GetTicksNS() - mStartTime;
    }
  }

  return elapsed;
}

double Timer::elapsedSec()
{
  double sec{static_cast<double>(this->elapsedNS()) / mOneNS};
  return sec;
}

bool Timer::isRunning()
{
  return mRunning;
}

bool Timer::isPaused()
{
  return mPaused;
}

