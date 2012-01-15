#pragma once

namespace Resource
{
  enum type {
    P1 = 0,
    P2,
    P3,
    P4,
    SINGLE_MONSTER,
	BOMB_MONSTER,
	SINUSOIDAL_MONSTER,
	METROID_MONSTER,
	BOSS_METROID,
	RANDOM_MONSTER,
	FISH_MONSTER,
	TRON_MONSTER,
	DEFAULT_SHOT,
	SHOT
  };

  extern const char *monsters[];
}
