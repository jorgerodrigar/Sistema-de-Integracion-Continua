#pragma once
#include "checkML.h"
#include <string>
#include <vector>
using namespace std;

const double ANIM_RATE = 100;
struct animData {
	string label_; // nombre/etiqueta de la animacion
	vector<int> framesAnim_; // frames que forman la animacion
	bool loop_; // si es loopeada o no (por defecto true)
	double rate_; // velocidad de frames (por defecto ANIM_RATE)
	int onEnded_;

	// constructora de animData
	animData() { label_ = "Default"; loop_ = false; rate_ = 100; onEnded_ = -1; };
	animData(string label, vector<int> framesAnim, bool loop = true, int onEnded = -1, double rate = ANIM_RATE) :
		label_(label), framesAnim_(framesAnim), loop_(loop), rate_(rate), onEnded_(onEnded) {};
};