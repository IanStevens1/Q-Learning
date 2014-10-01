#pragma once
#include "cdisccontroller.h"
#include "CParams.h"
#include "CDiscCollisionObject.h"
#include <cmath>

typedef unsigned int uint;
class CQLearningController :
	public CDiscController
{
private:
	uint _grid_size_x;
	uint _grid_size_y;
public:
	CQLearningController(HWND hwndMain);
	virtual void InitializeLearningAlgorithm(void);
	vector<vector<vector<double>>> qGrid;
	double R(uint x, uint y, uint sweeper_no);
	virtual bool Update(void);
	virtual ~CQLearningController(void);
};

