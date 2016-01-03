/**
 * File: chain-reaction-types.h
 * ------------------
 */

#ifndef __chain_reaction_types__
#define __chain_reaction_types__

#include "cmpfn.h"

/**
 * Manages the notion of a location.
 */

struct location {
	double x;
	double y;
};

/**
 * Imposes an ordering on locations so they can be compared
 * and stored in a Set.
 *
 * @param location one the first of two locations.
 * @param location two the second of two locations.
 * @return int 0 if the two locations are identical, negative
 *         if one can be said to be less than two, and positive
 *         otherwise.
 */

inline int LocationCompare(location one, location two) {
	if (one.x != two.x) return OperatorCmp(one.x, two.x);
	return OperatorCmp(one.y, two.y);
}

/**
 * The amount of time it takes for the detonation of one mine
 * to prompt the detonation of another one.
 */

static const double kDetonationDelay = 1.0;

/**
 * Defines the various distances that are relevant both to the
 * main program and the graphics package.  All values are in inches.
 *
 *   kLandMineReach: When a single mine is detonated, it prompts
 *                   all undetonated mines within this distance to
 *                   detonate kDetonationDelay seconds later.
 *   kLandMineMinSeparation: The closest two mines can be placed to one another.
 *   kLandMineRadius: The actual radius of a land mine.
 */

static const double kLandMineReach = 0.45;
static const double kLandMineMinSeparation = 0.15;
static const double kLandMineRadius = kLandMineMinSeparation / 3;

#endif
