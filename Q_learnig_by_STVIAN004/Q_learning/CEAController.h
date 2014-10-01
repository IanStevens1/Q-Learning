#pragma once
#include "ccontcontroller.h"
#include <vector>
#include "CNeuralNet.h"
#include "CParams.h"
#include "CBasicEA.h"

class CEAController :
	public CContController
{
protected:

public:
	CEAController(HWND hwndMain);
	virtual void InitializeLearningAlgorithm(void);
	virtual bool Update(void);
	virtual ~CEAController(void);
};

