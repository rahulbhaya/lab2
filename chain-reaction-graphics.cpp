/**
 * File: chain-reaction-graphics.cpp
 * ---------------------------------
 * Created by Jerry on 4/10/10.
 */

#include "genlib.h"
#include "extgraph.h"
#include "strutils.h"
#include "chain-reaction-graphics.h"

/**
 * Lots of graphics code I don't want to document.  It's all fairly brute
 * force and self-explanatory.
 */

static const string kNoMinePresentColor = "White";
static const string kLandMineColor = "Black";
static const string kSoonToDetonateLandMineColor = "Red";
static const string kAlreadyDetonatedMineColor = "Light Gray";

static void DrawCenteredCircle(double radius, double cx, double cy, string color = "Black", bool isSolid = true) {
	string oldColor = GetPenColor();
	SetPenColor(color);
	MovePen(cx + radius, cy);
	if (isSolid) StartFilledRegion(1.0);
	DrawArc(radius, 0, 360);
	if (isSolid) EndFilledRegion();
	SetPenColor(oldColor);
}

static void DrawCenteredText(string text, double cx, double cy, string color) {
	double x = cx - TextStringWidth(text)/2;
	double y = cy - GetFontAscent()/2;
	MovePen(x, y);
	string oldColor = GetPenColor();
	SetPenColor(color);
	DrawTextString(text);
	SetPenColor(oldColor);
}

void InitChainReactionGraphics() {
	SetWindowTitle("Chain Reaction");
	InitGraphics();
	SetFont("Palatino");
	SetPointSize(10);
	SetStyle(Bold);
}

void DrawLandMine(location landMine) {
	DrawCenteredCircle(kLandMineRadius, landMine.x, landMine.y, kLandMineColor);
}

void DrawSoonToDenotateLandMine(location landMine) {
	DrawCenteredCircle(kLandMineRadius, landMine.x, landMine.y, kSoonToDetonateLandMineColor);
}

void DrawDetonatedLandMine(location landMine, int value) {
	DrawCenteredCircle(kLandMineRadius, landMine.x, landMine.y, kNoMinePresentColor);
	DrawCenteredCircle(kLandMineReach - kLandMineRadius, landMine.x, landMine.y, kAlreadyDetonatedMineColor, false);
	DrawCenteredText(IntegerToString(value), landMine.x, landMine.y, "Gray");
}

double GetChainReactionWindowWidth() { return GetWindowWidth(); }
double GetChainReactionWindowHeight() { return GetWindowHeight(); }
void UpdateChainReactionDisplay() { UpdateDisplay(); }
