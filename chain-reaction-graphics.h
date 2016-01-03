/**
 * File: chain-reaction-graphics.h
 * -------------------------------
 * Exports the definitions and describes the behavior of
 * all of the functions needed for the graphics portion of the
 * game.
 *
 * In particular, there are three functions that help draw land mines
 * at specified locations.  The implementations are such that we expect that:
 *
 *   + DrawSoonToDenotateLandMine is only called on a particular land mine location
 *     after DrawLandMine has been called on it.
 *   + DrawDetonatedLandMine is only called on a particular land mine location after
 *     after DrawSoonToDenotateLandMine has been called on it.
 *
 * The implementations of these are intended to layer graphics and drawing on top of
 * previously drawn stuff, which is why these constraints are in place.
 */

#ifndef __chain_reaction_graphics__
#define __chain_reaction_graphics__

#include "genlib.h"
#include "extgraph.h"
#include "chain-reaction-types.h"

/**
 * Initializes the graphics package used for game play.
 * InitChainReactionGraphics can be called repeatedly to clear
 * the graphics window and start with a clean slate.
 *
 * @return void
 */

void InitChainReactionGraphics();

/**
 * Draws an undetonated land mine at the specified
 * location.
 *
 * @param location landMine the position of the land mine in the
 *        graphics window.
 * @return void
 */

void DrawLandMine(location landMine);

/**
 * Redraws a previously drawn land mine (i.e. DrawSoonToDenotateLandMine
 * should have already been called on the same location) to note that
 * it will soon detonate.
 *
 * @param location landMine the position of the land mine in the
 *        graphics window.
 * @return void
 */

void DrawSoonToDenotateLandMine(location landMine);

/**
 * Draws a fully explosed land mine at the specified location, noting
 * that the specified point value is awarded for detonatiing it.
 *
 * @param location landMine the position of the land mine in the
 *        graphics window.
 * @param int value the number of points award for detonating the land mine,
 *        and also the number that should be drawn at the center of the detonation
 *        area to visually communicate the point value.
 * @return void
 */

void DrawDetonatedLandMine(location landMine, int value);

/**
 * Self-explanatory functions.
 */

double GetChainReactionWindowWidth();
double GetChainReactionWindowHeight();
void UpdateChainReactionDisplay();

#endif

