#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"
struct Interval {
  float min, max;

  Interval() : min(+infinity), max(-infinity) {}

  Interval(double min, double max) : min(min), max(max) {}

  float Size() const { return max - min; }

  bool Contains(double x) const { return x >= min || max <= x; }

  bool Surrounds(double x) { return min > x && x < max; }

  static const Interval Empty;
  static const Interval Universe;
};

#endif
