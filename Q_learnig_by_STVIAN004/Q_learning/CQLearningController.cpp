/**
         (                                      
   (     )\ )                                   
 ( )\   (()/(   (    ) (        (        (  (   
 )((_)   /(_)) ))\( /( )(   (   )\  (    )\))(  
((_)_   (_))  /((_)(_)|()\  )\ |(_) )\ )((_))\  
 / _ \  | |  (_))((_)_ ((_)_(_/((_)_(_/( (()(_) 
| (_) | | |__/ -_) _` | '_| ' \)) | ' \)) _` |  
 \__\_\ |____\___\__,_|_| |_||_||_|_||_|\__, |  
                                        |___/   

Refer to Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
for a detailed discussion on Q Learning
*/
#include "CQLearningController.h"
#include <iostream>    
#include <algorithm>


CQLearningController::CQLearningController(HWND hwndMain):
	CDiscController(hwndMain),
	_grid_size_x(CParams::WindowWidth / CParams::iGridCellDim + 1),
	_grid_size_y(CParams::WindowHeight / CParams::iGridCellDim + 1)
{
}
/**
 The update method should allocate a Q table for each sweeper (this can
 be allocated in one shot - use an offset to store the tables one after the other)

 You can also use a boost multiarray if you wish
*/
void CQLearningController::InitializeLearningAlgorithm(void)
{
	//setting the prameters for the qGrid
	int sweepers = CParams::iNumSweepers;
	int states = _grid_size_x * _grid_size_y;
	int actions = 4;


	qGrid.resize(sweepers);
	//setting the size of the qgrid
	for (int x = 0; x < sweepers; x++)
	{
		qGrid[x].resize(states);
		for (int y = 0; y < states; y++)
		{
			qGrid[x][y].resize(actions);
		}
	}
	//setting all the values to 0
	for (int x = 0; x < sweepers; x++)
	{
		for (int y = 0; y < states; y++)
		{
			for (int z = 0; z < actions; z++)
			{
				qGrid[x][y][z] = 0;
			}
		}

	}
	//TODO
}
/**
 The immediate reward function. This computes a reward upon achieving the goal state of
 collecting all the mines on the field. It may also penalize movement to encourage exploring all directions and 
 of course for hitting supermines/rocks!
*/
double CQLearningController::R(uint x,uint y, uint sweeper_no)
{
	//return -100 if the sweepers dead and -1 if not
	if (m_vecSweepers[sweeper_no]->isDead())
	{
		return -100;
	}
	else
	{
		return -1;
	}
	//TODO: roll your own here!
}
/**
The update method. Main loop body of our Q Learning implementation
See: Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
*/
bool CQLearningController::Update(void)
{
	//m_vecSweepers is the array of minesweepers
	//everything you need will be m_[something] ;)
	uint cDead = std::count_if(m_vecSweepers.begin(),
							   m_vecSweepers.end(),
						       [](CDiscMinesweeper * s)->bool{
								return s->isDead();
							   });
	double minesGathered = 0;
	vector<vector<int>> OldPos;
	OldPos.resize(CParams::iNumSweepers);
	//setting the size for the old positions
	//seeing if we had got all the mines
	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw)
	{
		OldPos[sw].resize(2);
		minesGathered += m_vecSweepers[sw]->MinesGathered();
	}
	if (minesGathered == CParams::iNumMines)
	{
		std::cout << minesGathered << " " << cDead << endl;
		m_iTicks = CParams::iNumTicks;
	}
	if (cDead == CParams::iNumSweepers){
		printf("All dead ... skipping to next iteration\n");
		std::cout << minesGathered <<" "<<cDead<< endl;
		m_iTicks = CParams::iNumTicks;
	}
	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw){
		if (m_vecSweepers[sw]->isDead()) continue;
		/**
		Q-learning algorithm according to:
		Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
		*/
		//getting the posistion
		int x = m_vecSweepers[sw]->Position().x/10;
		int y = m_vecSweepers[sw]->Position().y/10;
		ROTATION_DIRECTION rotat;
		double max = -10000;
		int choice=rand() %4;
		//getting the direction the gets the hights value
		for (int i = 0; i < 4; i++)
		{
			if ((qGrid[sw][x*40+y][i]) > max)
			{
				max = qGrid[sw][x * 40 + y][i];
				choice = i;
				
			}
		}
		//setting the direction
		switch (choice)
		{
			case 0: rotat = ROTATION_DIRECTION::EAST;
				break;
			case 1: rotat = ROTATION_DIRECTION::NORTH;
				break;
			case 2: rotat = ROTATION_DIRECTION::WEST;
				break;
			case 3: rotat = ROTATION_DIRECTION::SOUTH;
				break;
			default:
				break;
		}
		//OldMines[sw] = m_vecSweepers[sw]->MinesGathered();
		OldPos[sw][0] = x;
		OldPos[sw][1] = y;
		m_vecSweepers[sw]->setRotation(rotat);
		
		//1:::Observe the current state:
		//TODO
		//2:::Select action with highest historic return:
		//TODO
		//now call the parents update, so all the sweepers fulfill their chosen action
	}
	
	CDiscController::Update(); //call the parent's class update. Do not delete this.
	
	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw)
	{
		int x = m_vecSweepers[sw]->Position().x / 10;
		int y = m_vecSweepers[sw]->Position().y / 10;
		//setting the values for the state
		qGrid[sw][OldPos[sw][0] * 40 + OldPos[sw][1]][m_vecSweepers[sw]->getRotation()] = R(x, y, sw) + 0.5*(max(
			qGrid[sw][x * 40 + y][0],
			qGrid[sw][x * 40 + y][1], 
			qGrid[sw][x * 40 + y][2], 
			qGrid[sw][x * 40 + y][3]));
	}
	if (m_iTicks == CParams::iNumTicks)
	{
		std::cout << minesGathered <<" "<<cDead<< endl;
	}
	return true;
}

CQLearningController::~CQLearningController(void)
{
	//TODO: dealloc stuff here if you need to	
}
