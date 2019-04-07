#include "textview.h"

#include <iostream>

#include "../physics/particle.h"
#include "../accelerator/element.h"
#include "../accelerator/accelerator.h"

void TextView::draw(const Segment &to_draw){ to_draw.print(stream); }

void TextView::draw(const Particle &to_draw){ to_draw.print(stream); }

void TextView::draw(const Beam &to_draw){ to_draw.print(stream); }

void TextView::draw(const StraightSection &to_draw){ to_draw.print(stream); }

void TextView::draw(const MagneticElement &to_draw){ to_draw.print(stream); }

void TextView::draw(const ElectricElement &to_draw){ to_draw.print(stream); }

void TextView::draw(const Accelerator &to_draw){ to_draw.print(stream, false); }
