// Fill out your copyright notice in the Description page of Project Settings.

 
#include "PASO.h"
/**
 * @brief destructor
 */
PASO::~PASO() {}
/**
 * @brief constructor
 */
PASO::PASO() {}
/**
 * @brief constructor
 * @param tcLimit try counter limit
 * @param baseCase step size
 * @param PBounds position bounds
 * @param VBouns velocity bounds
 * @param Fit fitness function
 * @param StateV state valid
 * @param Dist distance function
 */
PASO::PASO(int cdim, int wdim, int tcLimit, float baseCase, std::vector<std::pair<float, float> > PBounds,
           std::vector<std::pair<float, float> > VBounds, std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fit,
           std::function<bool(std::vector<float>)> StateV,std::function<float(std::vector<float>,std::vector<float>)> Dist) {
    this->CDim = cdim;
    this->WDim = wdim;
    this->TryCounterLimit =tcLimit;
    this->BaseCaseError = baseCase;
    this->FitnessFunction = Fit;
    this->Distance = Dist;
    this->TryCounter = 0;
    this->StateValid = StateV;
    this->PosBounds = PBounds;
    this->VelBounds = VBounds;
}
/**
 * @brief get path
 * @return path planned by algorithm
 */
std::vector<std::vector<float> > PASO::GetPath() {return this->Path;}
/**
 * @brief getter for didConverge
 * @return value of didConverge
 */
bool PASO::DidPASOConverge() {
	for (int i = 0; i < Path.size(); i++) {
        if (!StateValid(Path[i])) {
            return false;
        }
    }
    for (int i=1; i<Path.size(); i++) {
        if (Distance(Path[i], Path[i-1]) > BaseCaseError) {
            return false;
        }
    }
    return true;
}
/**
 * @brief getter for pasoRuntime
 * @return value of pasoRuntime
 */
float PASO::GetPASORuntime() {return this->PasoRuntime;}
/**
* @brief Check motion validity from one state to another (long distance)
* @details Returns a boolean indicating whether or not a direct motion from
* one state to another is valid.
*
* @param from The start state
* @param to The destination state
*
* @return A boolean indicating validity
*/
bool PASO::LongTransitionValid(const std::vector<float>& from, const std::vector<float>& to, float range) {
	if (StateValid(from) && StateValid(to) && Distance(from, to) <= range) {
		return true;
	}
	else if (StateValid(from) && StateValid(to)) {
		std::vector<float> mid(from.size());
		for (int i = 0; i < mid.size(); i++) {
			mid[i] = (from[i] + to[i]) / 2.0;
		}
		return LongTransitionValid(from, mid, range) && LongTransitionValid(mid, to, range);
	}
	else {
		return false;
	}
}
/**
* @brief get number of tries performed
* @return try counter value
*/
int PASO::GetTryCounter() {
	return this->TryCounter;
}
/**
 * @brief compute bounds
 * @param point point around which bounds should be made
 * @param range range around which to create bounds around
 */
std::vector<std::pair<float,float> > PASO::ComputePosBounds(std::vector<float> point, float range) {
    std::vector<std::pair<float,float> > pbounds(point.size());
    for (int i=0; i<point.size(); i++) {
        pbounds[i] = std::pair<float,float>(fmax(point[i] - range/2.0, PosBounds[i].first),fmin(point[i] + range/2.0, PosBounds[i].second));
    }
    return pbounds;
}
/**
 * @brief compute bounds
 * @param bs position bounds
 * @return velocity bounds
 */
std::vector<std::pair<float,float> > PASO::ComputeVelBounds(std::vector<std::pair<float,float> > bs) {
    std::vector<std::pair<float,float> > velB(bs.size());
    for (int i=0; i<bs.size(); i++) {
        float maxVal = fabs(fmax(bs[i].first,bs[i].second));
        velB[i] = std::pair<float,float>(-maxVal, maxVal);
    }
    return velB;
}
/**
 * @brief plan path function (PASO V5)
 * @param start starting point in c space
 * @param goal goal point in c space
 * @param run initialization bounds
 * @param vel run bounds
 * @param tryLimit number of tries to allow before failure
 * @param baseCase resolution of path (distance metric)
 * @param forward is direction forward (true) or reverse (false)
 * @return planned path
 */
bool PASO::PlanPathOptimize(std::vector<float> start,
                            std::vector<float> goal) {
    bool forward = true;
    std::vector<std::vector<float> > currentPathForward;
    std::vector<std::vector<float> > currentPathReverse;
    std::vector<float> originalGoal(goal.size());
    for (int i=0; i<goal.size(); i++) {
        originalGoal[i] = goal[i];
    }
    std::vector<float> currentStart;
    std::vector<float> currentTarget;
    cout<<start.size()<<endl;
    cout<<goal.size()<<endl;
    while (Distance(start,goal) > BaseCaseError && TryCounter < TryCounterLimit) {
        if (forward) {
            currentStart = start;
            currentTarget = goal;
        } else {
            currentStart = goal;
            currentTarget = start;
        }
        PSOParticleSwarm Swarm = PSOParticleSwarm(100, 100, currentStart.size());
        std::vector<std::pair<float,float> > pBounds = ComputePosBounds(currentStart, BaseCaseError);
        std::vector<std::pair<float,float> > vBounds = ComputeVelBounds(pBounds);
        
        Swarm.initializeSwarm(pBounds, vBounds, pBounds, vBounds, 0.001, MODE_CONSTRICTION,
                              FitnessFunction, currentStart, currentTarget);
        PSOParticle newPart = Swarm.optimize();
        //If progress made, new particle is added to path
        if (this->Distance(newPart.getPosition(), currentTarget) < this->Distance(currentTarget, currentStart) &&
			StateValid(newPart.getPosition()) && LongTransitionValid(currentStart, newPart.getPosition(), BaseCaseError)) {
            if (forward) {
                start = newPart.getPosition();
                currentPathForward.push_back(start);
            } else {
                goal = newPart.getPosition();
                currentPathReverse.push_back(goal);
                
            }
        }
        cout<<"Try Number: "<<TryCounter<<endl;
        cout<<"Current distance: "<<Distance(start,goal)<<endl;
        TryCounter++;
        forward = !forward;
    }
    
    for (int i=0; i<currentPathForward.size(); i++) {
        Path.push_back(currentPathForward[i]);
    }
    for (int i=currentPathReverse.size() - 1; i>=0; i--) {
        Path.push_back(currentPathReverse[i]);
    }
    
    Path.push_back(originalGoal);
    
    if (Distance(start,goal) < BaseCaseError || LongTransitionValid(start,goal,BaseCaseError)) {
        return true;
    } else {
		Path.clear();
        return false;
    }
    
    
    
}
