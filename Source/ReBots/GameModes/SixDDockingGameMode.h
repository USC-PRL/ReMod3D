#pragma once

#include "GameFramework/GameMode.h"
#include "Framework/Message.h"
#include "Framework/RangedMessage.h"
#include "SuperBot/SuperBotModule.h"
#include "Framework/ModuleDock.h"
#include "Framework/ConstraintMonitor.h"
#include "CustomActors/FloorCollisionActor.h"
#include "Framework/KinematicsMessage.h"
#include "PSO/PSOParticleSwarm.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Framework/TreeMessage.h"
#include <map>
#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include "CustomActors/BoundingSphere.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysXPublic.h"
#include "PhysXIncludes.h"
#include "BBPSO/BranchBoundPSO.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "BBPSO/FBBPSOWorker.h"
#include "SixDDockingGameMode.generated.h"
/**
 * @class ASixDDockingGameMode
 * @brief six d docking game mode
 */
UCLASS()
class REBOTS_API ASixDDockingGameMode : public AReBotsSimulatorGameMode
{
	GENERATED_BODY()
private:
    vector<ModuleDock> docksToMonitor; /**< docks for the experiment to moonitor */
    float errorPositionDock = 0.05; /**< position error for docking */
    float errorOrientationDock = 0.05; /**< orientation error for docking */
    vector<pair<int, ModuleDockFace> > deleteQueue; /**< queue of docks to delete from monitor */
    vector<ModuleDock> addQueue; /**< docks to add to the monitor */
    map<int, map<ModuleDockFace, ModuleDock> > connections; /**< connections between modules */
    map<int, vector<KinematicsMessage> > messageRoomKinematics; /**< kinematic message room */
    map<int, vector<Message> > messageRoom; /**< message boxes for modules (by name) */
    map<int, vector<RangedMessage> > messageRoomRanged; /**< message boxes for ranged messages for modules (by name) */
    map<int, vector<TreeMessage> > messageRoomSuperBotTree; /**< message boxes for super bot tree messages */
    vector<ASuperBotModule*> modules; /**< vector of modules in simulation */
    map<int, ASuperBotModule*> modulesMap; /**< in order map of modules to integers */
    map<ASuperBotModule*,int> modsToIDs; /**< modules to ids */
    bool FirstTick = true; /**< is this the first tick of the game mode */
    ConstraintMonitor CMonitor; /**< constraint monitor */
    bool DockDebug = true; /**< dock debug output */
    bool FirstMove = true; /**< first move? */
    int waitCounter = 30; /**< wait counter */
    AReferenceFrameActor* EndEffectorFrame; /**< end effector reference frame */
    FTransform CurrentEndEffector; /**< current end effector transform */
    FTransform GoalEndEffector; /**< goal end effector transform */
    AStaticMeshActor* Floor; /**< floor actor */
    AReferenceFrameActor* GoalEndEffectorFrame; /**< goal end effector reference frame */
    FTransform ToGroundTransform; /**< to ground transform */
    AReferenceFrameActor* ToGroundFrame; /**< to ground frame */
    unsigned Seed; /**< seed value */
    std::mt19937 Generator; /**< generator for random nums */
    bool HaveInitiatedIK = false; /**< have initiated inverse kinematics */
    bool HaveCompletedIK = false; /**< have we completed IK computation */
    PSOParticleSwarm *PS; /**< particle swarm */
    vector<ABoundingSphere*> BoundingSpheresGoal; /**< goal bounding spheres */
    vector<ABoundingSphere*> BoundingSpheresCurrent; /**< current bounding spheres */
    UPROPERTY(EditAnywhere, Category = GameModeKinematics, meta = (AllowPrivateAccess = "true"))
    bool ToMasterKinematics = true; /**< render kinematic graph frames for modules docks f and b  */
    FBBPSOWorker* PSOWorker = NULL; /**< pso worker */
    vector<float> SolutionPos; /**< solution position */
    bool HaveAddedOnScreenMessage = false; /**< have added on screen message */
    float SolutionFitness; /**< solution fitness value */
    //BranchBoundPSO BBPSO; /**< branch bound pso */
    //TArray<uint32> PrimeNumbers;
public:
    /**
     * @brief get bounding spheres for joint angles
     * @param ToGround to ground transform
     * @param JAngles motor vectors
     * @param ToMaster to master direction
     * @return bounding spheres
     */
    vector<ABoundingSphere*> GetBoundingSpheresForJointAngles(FTransform ToGround, std::vector<ModuleMotorVector> JAngles);
    /**
     * @brief game mode constructor
     * @param ObjectInitializer initializer
     */
    ASixDDockingGameMode(const FObjectInitializer& ObjectInitializer);
    /**
     * @brief advance the simulation
     * @param DeltaSeconds fraction of a second by which to advance simulation
     */
    virtual void Tick( float DeltaSeconds ) override;
    /**
     * @brief get transform of end effector for joint angles
     * @param JAngles joint angles
     * @return transform of End effector
     */
    FTransform GetTransformOfEndEffector(std::vector<ModuleMotorVector> JAngles);
    /**
     * @brief fitness function
     * @param P particle
     * @return particle fitness
     */
    float Fitness(PSOParticle P);
    /**
     * @brief fitness function
     * @param P particle
     * @param tar target vector
     * @return particle fitness
     */
    float BBPSOFitness(BranchBoundParticle P, std::vector<float> st, std::vector<float> tar);
    /**
     * @brief detect self collision
     * @param ToGround to ground transform
     * @param JAngles joint angles
     * @param Thresh threshold
     * @param ToMaster run kinematics toward master side
     */
    bool IsInSelfCollision(FTransform ToGround, std::vector<ModuleMotorVector> JAngles);
    /**
     * @brief detect collision with ground
     * @param ToGround to ground transform
     * @param JAngles joint angles
     * @param GroundZVal ground z value (vertical)
     * @param Thresh threshold
     * @param ToMaster run kinematics toward master side
     */
    bool IsInCollisionWithGround(FTransform ToGround, std::vector<ModuleMotorVector> JAngles, float GroundZVal, float Thresh);
    /**
     * @brief dock two modules together
     * @param sm1 superbot module 1
     * @param sm2 superbot module 2
     * @param d1 dock face of module 1
     * @param d2 dock face of module 2
     */
    void DockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief get corrective docking transform
     * @param d1 dock 1
     * @param d2 dock 2
     */
    FTransform GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2);
    
    
};
