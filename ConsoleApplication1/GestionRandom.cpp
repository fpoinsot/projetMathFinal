#pragma once
#include "stdafx.h"
#include "GestionRandom.h"
#include <random>
#include <iostream>
#include <string>
#include <chrono>

std::default_random_engine generator;

void initialiserRand()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator.seed(seed);
}

int tirerUnIntEntre(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
}