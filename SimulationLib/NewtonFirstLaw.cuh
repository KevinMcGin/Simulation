#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonFirstLaw: public Law {
public:
	virtual void run(vector<Particle*>& particles);
	virtual void runParallel(vector<Particle*>& particles);
		
};