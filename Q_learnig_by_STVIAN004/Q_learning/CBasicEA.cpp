/**
    )                                                         
 ( /(                                (         )              
 )\())  (   (  (         (    )      )\  (  ( /((             
((_)\  ))\ ))\ )(   (    )\  /((  ( ((_)))\ )\())\  (   (     
 _((_)/((_)((_|()\  )\  ((_)(_))\ )\ _ /((_|_))((_) )\  )\ )  
| \| (_))(_))( ((_)((_) | __|)((_|(_) (_))(| |_ (_)((_)_(_/(  
| .` / -_) || | '_/ _ \ | _|\ V / _ \ | || |  _|| / _ \ ' \)) 
|_|\_\___|\_,_|_| \___/ |___|\_/\___/_|\_,_|\__||_\___/_||_|  

Further details can be found in:
X. Yao, Evolving artificial neural networks, Proceedings of the IEEE,
87(9):1423-1447, September 1999                                                              

This class only serves to give you some direction as where to go. You
can modify the headers, etc. if you want
*/

#include "CBasicEA.h"
/**
This function should compute the fitness of a particular sweeper and bundle its genome and fitness together
*/
void CBasicEA::computeFitness(const std::vector<CContMinesweeper *> & parent_sweepers,
							  const std::vector<CNeuralNet *> & parent_genomes,
							  std::vector<ParentAndFitness> & fitness_out)
{
	//TODO:: roll your own
}
/**
Selects the fittest of the population and use selection operators on them to spawn replacements for the rest
*/
void CBasicEA::selection_crossover_mutate(std::vector<ParentAndFitness> & parents)
{
	//TODO:: roll your own
}
/**
Crossover (exploration) of some sort
*/
void CBasicEA::crossover(const CNeuralNet & genotypeA,const CNeuralNet & genotypeB, CNeuralNet & out)
{
	//TODO:: roll your own
}
/**
Mutation (exploitation) of some sort
*/ 
void CBasicEA::mutate(const CNeuralNet & genotypeA, CNeuralNet & out)
{
	//TODO:: roll your own
}

