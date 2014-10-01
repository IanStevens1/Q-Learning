/**
	This class is only there as a place holder you can modify this to work with you EA controller any way you want
*/
#pragma once
#include "cneuralnet.h"
#include "CContMinesweeper.h"
#include <vector>
#include <assert.h>
#include <algorithm>
typedef struct {
	CNeuralNet * parent_genome;
	double fitness;
} ParentAndFitness;

class CBasicEA
{
private:
	static void crossover(const CNeuralNet & genotypeA,const CNeuralNet & genotypeB, CNeuralNet & out);
	static void mutate(const CNeuralNet & genotypeA, CNeuralNet & out);
public:
	static void computeFitness(const std::vector<CContMinesweeper *> & parent_sweepers,
							   const std::vector<CNeuralNet *> & parent_genomes,
							   std::vector<ParentAndFitness> & fitness_out);
	static void selection_crossover_mutate(std::vector<ParentAndFitness> & parents);
};

