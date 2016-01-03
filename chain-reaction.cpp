/**
 * File: chain-reaction.cpp
 * ------------------------
 * Implements our version of the game of Chain Reaction.
 */

#include "genlib.h"
#include "set.h"
#include "random.h"
#include "chain-reaction-types.h"
#include "chain-reaction-graphics.h"
#include <cmath>
#include <iostream>

/**
 * Introduces the game.  Self-explanatory.
 *
 * @return void
 */

void Introduce() {
	cout << "Welcome to the game of Chain Reaction!" << endl;
	cout << "Select the land mine that should be deliberately detonated, and then watch the other mines go boom..." << endl;
	cout << endl;
}

/**
 * Returns true if and only if the two provided locations are 
 * within the specified threshold distance of one another, and returns
 * false otherwise.
 *
 * @param location one the first of two locations.
 * @param location two the second of two locations.
 * @param double distance the threshold distance that defines what in-range
 *        and out-of-range means.
 * @return bool true if and only if the two locations are within the specified
 *         distance of each other.
 */

bool IsInRange(location one, location two, double distance) {
	double deltax = one.x - two.x;
	double deltay = one.y - two.y;
	return sqrt(deltax * deltax + deltay * deltay) < distance;
}

/**
 * Returns true if and only if the potentialLandMine is within a threshold
 * distance of one or more of the already placed land mines.
 *
 * @param Set<location>& landMines the already placed land mines.
 * @param location& potentialLandMine the location we're considering for a land mine.
 * @param double distance how far the new land mine needs to be from all previously placed
 *        ones.
 * @return bool true if and only if the location we're considering for a new land mine
 *         if within the threshold distance of one or more existing land mines, and false
 *         otherwise.
 */

bool IsInRange(Set<location>& landMines, location& potentialLandMine, double threshold) {
	foreach (location landMine in landMines) {
		if (IsInRange(landMine, potentialLandMine, threshold)) {
			return true;
		}
	}

	return false;
}

/**
 * Accepts the empty land mine set, and populates it with between 150
 * and 200 randomly positioned land mines such that no two are all that
 * close together.
 *
 * @param Set<location>& landMines the set where the collection of land mines
 *        should be added.  Assumed to be initially empty, but cleared out
 *        for safety.
 * @return void
 */

void GenerateLandMines(Set<location>& landMines) {
	landMines.clear();
	int numLandMinesNeeded = RandomInteger(150, 200);
	while (landMines.size() < numLandMinesNeeded) {
		location proposedLocation = { 
			RandomReal(kLandMineMinSeparation, GetChainReactionWindowWidth() - kLandMineMinSeparation), 
			RandomReal(kLandMineMinSeparation, GetChainReactionWindowHeight() - kLandMineMinSeparation) };
		if (!IsInRange(landMines, proposedLocation, kLandMineMinSeparation)) {
			landMines.add(proposedLocation);
			DrawLandMine(proposedLocation);
		}
	}
	
	UpdateChainReactionDisplay();
}

/**
 * Wait for the user to click the mouse on one of the land mines.
 * Repeatedly prompts and reprompts the user until s/he clicks on
 * an actual land mine (as opposed to some empty location.)
 *
 * @param Set<location>& landMines the set of all land mines.
 * @return location the location of the land mine the user ultimately
 *         selects.
 */

location GetUserSelection(Set<location>& landMines) {
	while (true) {
		WaitForMouseUp();
		WaitForMouseDown();
		location selection = { GetMouseX(), GetMouseY() };
		UpdateChainReactionDisplay();
		foreach (location landMine in landMines) {
			if (IsInRange(landMine, selection, kLandMineRadius)) {
				return landMine;
			}
		}
		cout << "Sorry, but you didn't click on a mine.  Please try again." << endl;
	}
}

/**
 * Manages the animation of the chain reaction of explosions that
 * result from the initial detonation of the land mine at the init 
 * location.
 *
 * @param location init the location of the manually detonated land
 *        mine.
 * @param Set<location>& landMines the set of all land mines.
 * @return int the total score achieved from the accumulation of
 *         all explosions.
 */

int FollowChainReaction(location init, Set<location>& landMines) {
	DrawSoonToDenotateLandMine(init);
	return 0;
}

/**
 * Fairly crufty function that jams commas into the presentation of
 * a large number.  Uses recursion.  Neat.
 *
 * @param int the number being printed.
 * @return string the string form of the incoming number, with commas
 *         inserted for easier reading.
 */

string IntegerToPrettyString(int number) {
	if (number < 1000) return IntegerToString(number);
	string large = IntegerToPrettyString(number / 1000);
	string small = IntegerToString(number % 1000);
	while (small.size() < 3) small = "0" + small;
	return large + "," + small;
}

/**
 * Implements the game loop for the Chain Reaction Game.  Fairly
 * self-explanatory.
 *
 * @return int 0 in theory, but never returns in practice.  User must
 *         explicitly quit the application to stop playing.
 */

int main() {
	Randomize();
	Introduce();
	while (true) {
		InitChainReactionGraphics();
		Set<location> landMines(LocationCompare);
		GenerateLandMines(landMines);
		location selection = GetUserSelection(landMines);
		int score = FollowChainReaction(selection, landMines);
		cout << "Total Score: " << IntegerToPrettyString(score) << endl;
		cout << "Click anywhere to play again." << endl;
		UpdateChainReactionDisplay();
		WaitForMouseUp();
		WaitForMouseDown();
	}
	
	return 0;
}
