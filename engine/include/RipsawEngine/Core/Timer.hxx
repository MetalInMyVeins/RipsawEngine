#pragma once

#include <SDL3/SDL.h>

class Timer
{
public:
  /// Constructs time.
  /// @details This is high resolution timer class that works on nanosecond level using SDL3.
  Timer() = default;
  /// Starts the timer.
  void start();
  /// Stops the timer.
  void stop();
  /// Pauses the timer.
  void pause();
  /// Resumes the timer.
  void resume();
  /// Returns elapsed time in nanoseconds.
  Uint64 elapsedNS();
  /// Returns elapsed time in seconds.
  double elapsedSec();
  /// Returns true if timer is running.
  bool isRunning();
  /// Returns true if timer is paused.
  bool isPaused();

private:
  /// Initial system time.
  Uint64 mStartTime{};
  /// Time point when timer is paused.
  Uint64 mPauseTime{};
  /// Timer running state.
  bool mRunning{false};
  /// Timer pause state.
  bool mPaused{false};
  /// Portion of 1 second that is 1 nanosecond.
  Uint64 mOneNS{1000000000};
};

