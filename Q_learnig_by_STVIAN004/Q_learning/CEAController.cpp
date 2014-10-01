/**
    )                                                         
 ( /(                                (         )              
 )\())  (   (  (         (    )      )\  (  ( /((             
((_)\  ))\ ))\ )(   (    )\  /((  ( ((_)))\ )\())\  (   (     
 _((_)/((_)((_|()\  )\  ((_)(_))\ )\ _ /((_|_))((_) )\  )\ )  
| \| (_))(_))( ((_)((_) | __|)((_|(_) (_))(| |_ (_)((_)_(_/(  
| .` / -_) || | '_/ _ \ | _|\ V / _ \ | || |  _|| / _ \ ' \)) 
|_|\_\___|\_,_|_| \___/ |___|\_/\___/_|\_,_|\__||_\___/_||_|  
                                              
	   (                )        (  (           
	   )\            ( /((       )\ )\  (  (    
	 (((_)  (   (    )\())(   ( ((_|(_)))\ )(   
	 )\___  )\  )\ )(_))(()\  )\ _  _ /((_|()\  
	((/ __|((_)_(_/(| |_ ((_)((_) || (_))  ((_) 
	 | (__/ _ \ ' \))  _| '_/ _ \ || / -_)| '_| 
	  \___\___/_||_| \__|_| \___/_||_\___||_|   
                                            
*/
#include "CEAController.h"


CEAController::CEAController(HWND hwndMain):
	CContController(hwndMain)
{
	
}

void CEAController::InitializeLearningAlgorithm(void)
{
	//TODO: set up any data structures you need to store the genomes here
}

/**
Returns the dot product between the sweeper's look vector and the vector from the sweeper to the object
*/
inline double dot_between_vlook_and_vObject(const CContMinesweeper &s,const CContCollisionObject &o){
	SVector2D<double> vLook = s.getLookAt();
	SVector2D<double> pt = o.getPosition();
		//get the vector to the point from the sweepers current position:
		SVector2D<double> vObj(SVector2D<double>(pt.x,pt.y) - s.Position());
		Vec2DNormalize<double>(vObj);
		//remember (MAM1000 / CSC3020) the dot product between two normalized vectors returns
		//1 if the two vectors point in the same direction
		//0 if the two vectors are perpendicular
		//-1 if the two vectors are pointing in opposite directions
		return Vec2DDot<double>(vLook,vObj);
}

bool CEAController::Update(void)
{
	uint cDead = std::count_if(m_vecSweepers.begin(),
							   m_vecSweepers.end(),
						       [](CContMinesweeper * s)->bool{
								return s->isDead();
							   });
	if (cDead == CParams::iNumSweepers){
		printf("All dead ... skipping to next iteration\n");
		m_iTicks = CParams::iNumTicks;
	}

	if (m_iTicks+1 >= CParams::iNumTicks){
		//TODO: when the round is over select, cross over and mutate here
	}
	CContController::Update(); //call the parent's class update. Do not delete this.
	for (uint i = 0; i < CParams::iNumSweepers; ++i){
		CContMinesweeper * s = m_vecSweepers[i]; 
		//TODO: set up your sensory inputs and motor outputs here
		/*
		//This turns the sweeper towards a point
		SPoint pt(m_vecObjects[(s)->getClosestMine()]->getPosition().x,
			m_vecObjects[(s)->getClosestMine()]->getPosition().y);
		(s)->turn(pt, 1);
		//This turns the sweeper away from a point
		SPoint pt(m_vecObjects[(s)->getClosestRock()]->getPosition().x,
					  m_vecObjects[(s)->getClosestRock()]->getPosition().y); 
					(s)->turn(pt,1,false);
					break;
		*/
	}

	return true; //method returns true if successful. Do not delete this.
}

CEAController::~CEAController(void)
{
	//TODO:: release any allocations here
}
