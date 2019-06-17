#pragma once

#include "GameFramework/Pawn.h"
#include "PhysXPublic.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include <sstream>
#include <iostream>
#include <functional>
#include <vector>
#include "Framework/ModuleMotorVector.h"
#include "Behaviors/JointBehavior.h"
#include "CustomActors/ReferenceFrameActor.h"
#include "CustomActors/ManipulatorObjectActor.h"
#include "Framework/RangedMessage.h"
#include "Framework/ModuleDock.h"
#include "Framework/TreeMessage.h"
#include "Framework/ModuleState.h"
#include "Framework/ModuleModel.h"
#include "Framework/ModuleConnectionPair.h"
#include "SuperbotKinematics.h"
#include "Behaviors/THatDistributed.h"
#include "Behaviors/TwistBehavior.h"
#include "Behaviors/ModManipQBehavior.h"
#include "Behaviors/SnakeIKBehavior.h"
#include "Behaviors/CaterpillarBehavior.h"
#include "Behaviors/SuperBotDistKinematics.h"
#include "Behaviors/SuperBotDistKinematicsChain.h"
#include "Behaviors/StackToPlaneBehavior.h"
#include "Behaviors/ForwardKinematicsBehavior.h"
#include "Behaviors/GoToAnglesBehavior.h"
#include "Behaviors/TreeWalkingBehavior.h"
#include "Behaviors/DistributedIK.h"
#include "Framework/RobotModuleBehavior.h"
#include "Behaviors/GoToAnglesBehavior.h"
#include "Behaviors/FKIKBehavior.h"
#include "Behaviors/ReconfDemoQ.h"
#include "Behaviors/ReconfDemoQ2.h"
#include "Behaviors/ReconfIKBehavior.h"
#include "Behaviors/DistributedKinematicsBehavior.h"
#include "GameModes/ReBotsSimulatorGameMode.h"
#include "GameModes/ReBotsModuleGameMode.h"
#include "CustomActors/DockCollisionActor.h"
#include "CustomActors/BoundingSphere.h"
#include "Framework/ModularRobot.h"
#include "Framework/ModuleJoint.h"
#include "Framework/ModuleSensor.h"
#include "Framework/ModuleActuator.h"
#include "Framework/ModulePoseSensor.h"
#include "Framework/ModuleFlagSensor.h"
#include "Framework/ModuleFlagActuator.h"
#include "Framework/ModuleFloatActuator.h"
#include "Framework/ModuleFloatSensor.h"
#include "Framework/ModuleMessageSensor.h"
#include "Framework/ModuleMessageActuator.h"
#include "Runtime/Engine/Classes/Engine/CollisionProfile.h"
#include "SuperBotModule.generated.h"
using namespace physx;
/**
 * @enum BehaviorType
 * @brief behavior type for SuperBot
 */
UENUM()
enum BehaviorType {
	B_TWIST                UMETA(DisplayName = "Twist"),
	B_CATERPILLAR          UMETA(DisplayName = "Caterpillar"),
	B_FK                   UMETA(DisplayName = "Forward Kinematics"),
	B_FK_IK                UMETA(DisplayName = "Foward/Inverse Kinematics"),
	B_6DDOCK               UMETA(DisplayName = "6D Docking"),
	B_MODMANIPQ            UMETA(DisplayName = "ModManipQ"),
	B_RECONF               UMETA(DisplayName = "ReconfQ"),
	B_RECONF2              UMETA(DisplayName = "ReconfQ2"),
	B_SNAKEIK              UMETA(DisplayName = "SnakeIK"),
	B_RECONFIK             UMETA(DisplayName = "ReconfIK"),
	B_TREEWALK             UMETA(DisplayName = "TreeWalk"),
	B_STACKTOPLANE         UMETA(DisplayName = "StackToPlane"),
	B_DIK                  UMETA(DisplayName = "DistributedIK"),
	B_DIST_KINEMATICS      UMETA(DisplayName = "DistributedKinematics"),
	B_THAT				   UMETA(DisplayName = "Distributed That"),
    B_NONE                 UMETA(DisplayName = "None")
};

enum SuperBotColor {
	SUPERBOT_RED = 1,
	SUPERBOT_GREEN,
	SUPERBOT_BLUE,
	SUPERBOT_GOLD,
	SUPERBOT_WHITE
};
/**
* @enum SuperBotSensorActuator
* @brief sensor and actuator constants in an enum
*/
enum SuperBotSensorActuator {
	JOINT_0 = 0,
	JOINT_1,
	JOINT_2,
	POSITION_ORIENTATION,
	DOCKS_ENABLED,
	DOCKS_ENGAGED,
	DOCKS_ENGAGED_TO_GROUND,
	DOCKS_ENGAGED_TO_OBJECT,
	MESSAGE
};
/**
* @enum SuperBotLinks
* @brief super bot links
*/
enum SuperBotLinks {
	M_OUTER,
	M_INNER,
	S_INNER,
	S_OUTER
};
UCLASS()
/**
 * @class ASuperBotModule
 * @brief SuperBot module
 * @date 5-18-2015
 * @author Thomas Collins
 */
class REBOTS_API ASuperBotModule : public AModularRobot
{
    GENERATED_BODY()
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MasterInner; /**< master inner component of module */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MasterOuter; /**< master outer component of module */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* SlaveInner; /**< slave inner component of module */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* SlaveOuter; /**< slave outer component of module */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UPhysicsConstraintComponent* InnerJoint; /**< inner joint (between slave inner and master inner */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UPhysicsConstraintComponent* MasterJoint; /**< master joint between master outer and inner */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UPhysicsConstraintComponent* SlaveJoint; /**< slave joint between slave outer and inner */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *FrontDock; /**< front dock component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *BackDock; /**< front dock component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *LeftDock; /**< front dock component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *RightDock; /**< front dock component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *UpDock; /**< front dock component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *DownDock; /**< front dock component */
    UPROPERTY(EditAnywhere, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    FString BehaviorName = "Twist"; /**< name of behavior */
    UPROPERTY(EditAnywhere, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    bool RemoteControlMode = false; /**< are we in remote control mode? */
    UPROPERTY(EditAnywhere, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    bool RenderDockFrames = false; /**< render frame or not*/
    UPROPERTY(EditAnywhere, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    bool RenderModuleFrame = false; /**< render frame or not*/
    UPROPERTY(EditAnywhere, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    bool RenderKGFramesModules = false; /**< render kinematic graph frames for modules */
    UPROPERTY(EditAnywhere, Category = SuperBotBody, meta = (AllowPrivateAccess = "true"))
    bool RenderBoundingBoxes = false; /**< render kinematic graph frames for modules docks f and b  */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool BehaviorMode =  true; /**< in behavior mode or manual control mode */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool AutoDocking = true; /**< auto docking ? */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool RenderDockCollisions = false; /**< render docking boxes? */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool RenderTargetTransform = false; /**< render docking boxes? */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool RenderFinalFK = true; /**< render end effector? */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool RenderBaseFrame = true; /**< render end effector? */
    UPROPERTY(EditAnywhere, Category = SuperBotMind, meta = (AllowPrivateAccess = "true"))
    bool RenderGroundFrame = true; /**< render end effector? */
    /** The type of object the behavior is */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
    TEnumAsByte<BehaviorType> BehaviorType; /**< module behavior type */
    RobotModuleBehavior* ModuleBehavior = NULL; /**< module behavior */
    const float superbot_mass_inner = (0.718/2.0)*0.65; /**< inner superbot mass */
    const float superbot_mass_outer = (0.718/2.0)*0.35; /**< outer superbot mass */
    const float superbot_static_friction = 0.5; /**< superbot static friction */
    const float superbot_kinetic_friction = 0.5; /**< superbot kinematic friction */
    const float superbot_restitution = 0.0; /**< superbot restitution */
    const float superbot_total_mass = 0.718; /**< superbot total mass */
    int AngleWaitCounter = 0; /**< angle change wait counter */
    ModuleMotorVector curJoints; /**< current joint angles */
    ModuleMotorVector desJoints; /**< desired joint angles */
    std::string name; /**< name of module */
    int IDNumber; /**< ID number of module */
    static int numSuperBotMods; /**< number of superbot modules */
    UTextRenderComponent *NameText; /**< name text component */
    bool JointBehaviorMode = true; /**< in joint behavior mode ? */
    AReferenceFrameActor* rFrameModule = NULL; /**< middle of module frame */
    AReferenceFrameActor* rFrameFrontDock = NULL; /**< master joint frame */
    AReferenceFrameActor* rFrameBackDock = NULL; /**< slave joint frame */
    AReferenceFrameActor* rFrameLeftDock = NULL; /**< left dock frame */
    AReferenceFrameActor* rFrameRightDock = NULL; /**< right dock frame */
    AReferenceFrameActor* rFrameUpDock = NULL; /**< up dock frame */
    AReferenceFrameActor* rFrameDownDock = NULL; /**< down dock frame */
    AReferenceFrameActor* rFrameFromFrontDock = NULL; /**< from front dock */
    AReferenceFrameActor* rFrameFromBackDock = NULL; /**< from front dock */
    AReferenceFrameActor* rFrameFromLeftDock = NULL; /**< from left dock */
    AReferenceFrameActor* rFrameFromRightDock = NULL; /**< from right dock */
    AReferenceFrameActor* rFrameFromUpDock = NULL; /**< from right dock */
    AReferenceFrameActor* rFrameFromDownDock = NULL; /**< from right dock */
    AReferenceFrameActor* GroundFrame = NULL; /**< ground frame */
    ADockCollisionActor *DCBFront = NULL; /**< dock collision box front */
    ADockCollisionActor *DCBBack = NULL; /**< dock collision box back */
    ADockCollisionActor *DCBLeft = NULL; /**< dock collision box left */
    ADockCollisionActor *DCBRight = NULL; /**< dock collision box right */
    ADockCollisionActor *DCBUp = NULL; /**< dock collision box up */
    ADockCollisionActor *DCBDown = NULL; /**< dock collision box down */
    const int  joint0Int = 0; /**< joint 0 constant */
    const int  joint1Int = 1; /**< joint 1 constant */
    const int  joint2Int = 2; /**< joint 2 constant */
    const int  frontDockEnabledInt = 3; /**< constant for enabling front dock */
    const int  backDockEnabledInt = 4; /**< constant for enabling back dock */
    const int  leftDockEnabledInt = 5;/**< constant for enabling left dock */
    const int  rightDockEnabledInt = 6; /**< constant for enabling right dock */
    const int  upDockEnabledInt = 7; /**< constant for enabling up dock */
    const int  downDockEnabledInt = 8;/**< constant for enabling down dock */
    const int  posOrientInt = 9; /**< position/orientation constant */
    const int  frontDockEngagedInt = 10; /**< constant for engaged status front dock */
    const int  backDockEngagedInt = 11;/**< constant for engaged status back dock */
    const int  leftDockEngagedInt = 12; /**< constant for engaged status left dock */
    const int  rightDockEngagedInt = 13; /**< constant for engaged status right dock */
    const int  upDockEngagedInt = 14;/**< constant for engaged status up dock */
    const int  downDockEngagedInt = 15;/**< constant for engaged status down dock */
    const int  frontDockMessageInt = 16;/**< front dock message constant */
    const int  backDockMessageInt = 17; /**< back dock message constant */
    const int  leftDockMessageInt = 18; /**< left dock message constant */
    const int  rightDockMessageInt = 19; /**< right dock message constant */
    const int  upDockMessageInt = 20; /**< up dock message constant */
    const int  downDockMessageInt = 21; /**< down dock message constant */
    const int  rangedMessageInt = 30; /**< ranged (wireless) message constant */
    const int  frontEngagedToGroundInt = 34; /**< front dock engaged to ground constant */
    const int  backEngagedToGroundInt = 35; /**< back dock engaged to ground constant */
    const int  messageInt = 16; /**< dock message constant */
    const int  masterInnerInt = 0; /**< master inner link constant */
    const int  masterOuterInt = 1; /**< master outer link constant */
    const int  slaveInnerInt = 2; /**< slave inner link constant */
    const int  slaveOuterInt = 3; /**< slave outer link constant */
    std::vector<AReferenceFrameActor*> RefFramesKG; /**< kinematic graph reference frames */
    std::vector<AReferenceFrameActor*> RefFramesKGFBDocks; /**< kinematic graph reference frames */
    std::vector<AReferenceFrameActor*> RefFramesKGLRUDDocks; /**< kinematic graph reference frames */
    std::vector<ABoundingSphere*> BoundingSpheres; /**< bounding boxes associated with trees */
    AReferenceFrameActor* FinalFKActor = NULL; /**< end effector transform */
    AReferenceFrameActor* TargetTransformActor = NULL; /**< target transform actor */
    FTransform BaseTransform; /**< base transform */
    AReferenceFrameActor* BaseTransformActor = NULL; /**< base transform actor */
    vector<AReferenceFrameActor*> RandTargetTransformsActors; /**< target transform actors */
	SuperBotColor ModuleColor; /**< Color of the module */
	const int NumConnectors = 6;
public:
    constexpr static float SuperbotHalfWidth = 95.0; /**< half width of superbot module */
    constexpr static float SuperbotOuterJointToOuterDock = 32.0 + 8.0 + 12.0;
    constexpr static float SuperbotToOuterJoint = 95.0 - 12.0 - 8.0 - 32.0; /**< to outer joint */
    static FTransform SuperbotFix; /**< transform to put frame in middle of superbot from master inner */
    std::vector<ModuleDock> Docks; /**< module of docks */
    std::vector<UStaticMeshComponent*> Links; /**< module links */
    std::vector<UPhysicsConstraintComponent*> Joints; /**< module joints */
    std::vector<APhysicsConstraintActor*> GroundDockConstraints; /**< constraints with the ground */
	std::vector<APhysicsConstraintActor*> ObjectDockConstraints; /**< constraints on objects */
    UStaticMesh *CubeMesh; /**< cube mesh */
    ModuleState currentState; /**< current module state */
    ModuleState desiredState; /**< desired module state */
    ModuleModel model; /**< SuperBot module model of the world */
    UMaterial *BlueTransMaterial; /**< blue trans material */
	UMaterial* BlueMaterial = NULL; /**< blue material */
    UMaterialInterface* BlueMaterialInterface = NULL; /**< blue material interface */
	/**
	* @brief get number of connectors
	* @return number of connectors
	*/
	int GetNumConnectors();
	/**
	* @brief set module color
	* @param c color to set
	*/
	void SetModuleColor(SuperBotColor C);
    /**
     * @brief constructor
     */
    ASuperBotModule();
    /**
     * @brief set module program
     * @param P module program
     */
    void SetModuleBehavior(RobotModuleBehavior* P);
    /**
     * @brief set id number
     * @param Id number
     */
    void SetIDNumber(int ID);
    /**
     * @brief set transform
     * @param trans
     */
    void SetTransform(FTransform trans);
    /**
     * @brief engage dock to ground
	 * @param d dock face
	 * @param engage (true) or disengage (false)
     */
    void EngageDockToGround(ModuleDockFace d, bool engaged);
	/**
	* @brief engage dock to object
	* @param d dock face
	* @param engage (true) or disengage (false)
	*/
	void EngageDockToObject(ModuleDockFace d, bool engaged);
    /**
     * @brief engage dock to stackable object
     * @param d module dock face
     * @param engaged whether or not we are engaging or disengaging from object
     */
    void EngageDockToStackableObject(ModuleDockFace d, bool engaged);
	/**
	* @brief engage object to ground
	* @param engage (true) or disengage (false)
	*/
	void EngageObjectToGround(bool engaged);
    /**
     * @brief engage dock to object
     */
    void EngageStackableObjectToGround(bool engaged);
	/**
	* @brief get dock enabled to object status
	* @param dock face d
	* @return get dock enabled to object
	*/
	bool GetDockEnabledToObject(ModuleDockFace d);
	/**
	* @brief get dock engaged to object status
	* @param dock face d
	* @return get dock engaged to object
	*/
	bool GetDockEngagedToObject(ModuleDockFace d);
	/**
	* @brief set dock enabled to object status
	* @param dock face d
	* @param de dock enabled
	*/
	void SetDockEnabledToObject(ModuleDockFace d, bool de);
	/**
	* @brief set dock engaged to object status
	* @param dock face d
	* @param de dock engaged
	*/
	void SetDockEngagedToObject(ModuleDockFace d, bool de);
    /**
     * @brief get id number
     * @return Id number
     */
    int GetIDNumber();
    /**
     * @brief get module behavior
     * @return module behavior
     */
    RobotModuleBehavior* GetModuleBehavior();
    /**
     * @brief superbot dock setter
     * @param sd superbot dock
     */
    void SetDocks(std::vector<ModuleDock> sd);
    /**
     * @brief get superbot docks
     * @return superbot dock vector
     */
    std::vector<ModuleDock> GetDocks();
    /**
     * @brief superbot dock setter
     * @param sd superbot dock
     */
    void SetLinks(std::vector<UStaticMeshComponent*> sl);
    /**
     * @brief get superbot docks
     * @return superbot dock vector
     */
    std::vector<UStaticMeshComponent*> GetLinks();
    /**
     * @brief superbot dock setter
     * @param sd superbot dock
     */
    void SetJoints(std::vector<UPhysicsConstraintComponent*> sj);
    /**
     * @brief get superbot docks
     * @return superbot dock vector
     */
    std::vector<UPhysicsConstraintComponent*> GetJoints();
    /**
     * @brief return module name
     * @return name of module
     */
    std::string GetName();
    /**
     * @brief return module name
     * @return name of module
     */
    void SetName(std::string n);
    /**
     * @brief get dock for name
     * @param name string name
     * @return superbot dock
     */
    ModuleDockFace GetDockFaceForName(std::string dname);
    /**
     * @brief begin play (simulation)
     */
    virtual void BeginPlay() override;
    /**
     * @brief initialize module
     */
    virtual void InitModule();
    /**
     * @brief advance the simulation
     * @param DeltaSeconds fraction of a second by which to advance simulation
     */
    virtual void Tick( float DeltaSeconds ) override;
    /**
     * @brief set up the module
     */
    ModuleMotorVector GetJointAngles();
    /**
     * @brief wake up module
     */
    void WakeUpModule();
    /**
     * @brief set joint angles
     * @param ja joint angles
     */
    void SetJointAngles(ModuleMotorVector ja);
    /**
     * @brief are current joint angles close to desired ones
     * @param tol tolerance
     * @return true if desired and current angles "same", false otherwise.
     */
    bool AreCurrentJointAnglesDesired(float tol = 3.0);
    /**
     * @brief set dock engaged status
     * @param d dock face
     * @param e engaged status
     */
    void SetDockEngaged(ModuleDockFace d, bool e);
    /**
     * @brief set dock enabled status
     * @param d dock face
     * @param e enabled status
     */
    void SetDockEnabled(ModuleDockFace d, bool e);
    /**
     * @brief weld dock to component
     * @param d dock
     * @param sc scene component
     */
    void WeldDockToComponent(ModuleDockFace d, USceneComponent* sc);
    /**
     * @brief get dock enabled status
     * @param d dock face
     */
    bool GetDockEnabledStatus(ModuleDockFace d);
    /**
     * @brief attach dock to component
     * @param d dock face
     * @param sc scene component
     */
    void AttachDockToComponent(ModuleDockFace d, USceneComponent *sc);
    /**
     * @brief get dock component
     * @param d dock face
     */
    UStaticMeshComponent *GetDockComponent(ModuleDockFace d);
    /**
     * @brief perform current actions
     */
    void PerformActions();
    /**
     * @brief add impulse to module
     * @param vec
     */
    void AddImpulseToModule(FVector vec);
    /**
     * @brief add angular impulse to module
     * @param vec
     */
    void AddAngularImpulseToModule(FVector vec);
    /**
     * @brief get dock enabled status
     * @return dock faces
     */
    vector<bool> GetDockEnabledStatuses();
    /**
     * @brief get transform to master inner
     */
    FTransform GetRootToMasterInnerTransform();
    /**
     * @brief get dock engaged status
     * @return dock engaged status
     */
    bool GetDockEngagedStatus(ModuleDockFace d);
    /**
     * @brief get dock enabled status
     * @return dock faces
     */
    vector<bool> GetDockEngagedStatuses();
    /**
     * @brief get dock enabled to ground statuses
     */
    vector<bool> GetDockEnabledToGroundStatuses();
    /**
     * @brief get dock engaged to ground statuses
     */
    vector<bool> GetDockEngagedToGroundStatuses();
	/**
	* @brief get dock enabled to object statuses
	*/
	vector<bool> GetDockEnabledToObjectStatuses();
	/**
	* @brief get dock engaged to object statuses
	*/
	vector<bool> GetDockEngagedToObjectStatuses();
    /**
     * @brief get dock enabled to ground status
     * @param dock face d
     * @return get dock enabled to ground
     */
    bool GetDockEnabledToGround(ModuleDockFace d);
    /**
     * @brief get dock engaged to ground status
     * @param dock face d
     * @return get dock engaged to ground
     */
    bool GetDockEngagedToGround(ModuleDockFace d);
    /**
     * @brief set dock enabled to ground status
     * @param dock face d
     * @param de dock enabled
     */
    void SetDockEnabledToGround(ModuleDockFace d, bool de);
    /**
     * @brief set dock engaged to ground status
     * @param dock face d
     * @param de dock engaged
     */
    void SetDockEngagedToGround(ModuleDockFace d, bool de);
    /**
     * @brief send message on dock face
     * @param d dock face
     * @param m message
     */
    void SendMessageOnDockFace(ModuleDockFace d, std::string m);
    /**
     * @brief send kinematics message on dock face
     * @param d dock face
     * @param m kinematics messages
     */
    void SendKinematicsMessageOnDockFace(ModuleDockFace d, KinematicsMessage m);
    /**
     * @brief send tree message on dock face
     * @param d dock face
     * @param m tree messages
     */
    void SendTreeMessageOnDockFace(ModuleDockFace d, TreeMessage m);
    /**
     * @brief send ranged message
     * @param m message
     */
    void SendRangedMessage(std::string m);
    /**
     * @brief set material for all bodies
     */
    void SetMaterialForAllBodies(UMaterialInterface* material);
    /**
     * @brief get all messages
     */
    vector<Message> GetMessages();
    /**
     * @brief get all ranged messages
     */
    vector<RangedMessage> GetRangedMessages();
    /**
     * @brief get all kinematics messages
     */
    vector<KinematicsMessage> GetKinematicsMessages();
    /**
     * @brief get all tree messages
     */
    vector<TreeMessage> GetTreeMessages();
    /**
     * @brief initialize module behavior
     */
    void InitializeModuleBehavior();
    /**
     * @brief set up player input component
     * @param InputComponent
     */
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    /**
     * @brief get master inner component
     * @return master inner component
     */
    FORCEINLINE class UStaticMeshComponent* GetMasterInnerMesh() const { return MasterInner; }
    /**
     * @brief get slave inner component
     * @return slave inner component
     */
    FORCEINLINE class UStaticMeshComponent* GetSlaveInnerMesh() const { return SlaveInner; }
    /**
     * @brief get master outer component
     * @return master outer component
     */
    FORCEINLINE class UStaticMeshComponent* GetMasterOuterMesh() const { return MasterOuter; }
    /**
     * @brief get slave outer component
     * @return slave outer component
     */
    FORCEINLINE class UStaticMeshComponent* GetSlaveOuterMesh() const { return SlaveOuter; }
    /**
     * @brief get inner joint
     * @return inner joint component
     */
    FORCEINLINE class UPhysicsConstraintComponent* GetInnerConstraint() const { return InnerJoint; }
    /**
     * @brief get master joint
     * @return master joint component
     */
    FORCEINLINE class UPhysicsConstraintComponent* GetOuterConstraint1() const { return MasterJoint; }
    /**
     * @brief get slave joint
     * @return slave joint component
     */
    FORCEINLINE class UPhysicsConstraintComponent* GetOuterConstraint2() const { return SlaveJoint; }
	/**
	* @class Joint0Sensor
	* @brief joint 0 sensor
	*/
	class Joint0Sensor : public ModuleFloatSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual float GetFloatValue(ASuperBotModule *M);
	};
	/**
	* @class Joint1Sensor
	* @brief joint 1 sensor
	*/
	class Joint1Sensor : public ModuleFloatSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual float GetFloatValue(ASuperBotModule *M);
	};
	/**
	* @class Joint2Sensor
	* @brief joint 2 sensor
	*/
	class Joint2Sensor : public ModuleFloatSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual float GetFloatValue(ASuperBotModule *M);
	};
	/**
	* @class ModuleMessageSensor
	* @brief module message sensor
	*/
	class MessageSensor : public ModuleMessageSensor {
		/**
		* @brief get sensor value
		* @param M superbot module
		*/
		virtual std::vector<ModuleMessage> GetMessageValue(ASuperBotModule *M);
	};
	/**
	* @class PoseSensor
	* @brief superbot pose sensor
	*/
	class PoseSensor : public ModulePoseSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual FTransform GetTransformValue(ASuperBotModule *M);
	};
	/**
	* @class DockEnabledSensor
	* @brief dock enabled sensor
	*/
	class DockEnabledSensor : public ModuleFlagSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual std::vector<bool> GetFlagValue(ASuperBotModule *M);
	};
	/**
	* @class DockEnabledSensor
	* @brief dock enabled sensor
	*/
	class DockEngagedSensor : public ModuleFlagSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual std::vector<bool> GetFlagValue(ASuperBotModule *M);
	};
	/**
	* @class DockEnabledSensor
	* @brief dock enabled sensor
	*/
	class DockEngagedToGroundSensor : public ModuleFlagSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual std::vector<bool> GetFlagValue(ASuperBotModule *M);
	};
	/**
	* @class DockEnabledSensor
	* @brief dock enabled sensor
	*/
	class DockEngagedToObjectSensor : public ModuleFlagSensor {
		/**
		* @brief get sensor value
		* @param M superbot module instance
		* @return current sensor value
		*/
		virtual std::vector<bool> GetFlagValue(ASuperBotModule *M);
	};
	/**
	* @class MessageActuator
	* @brief message actuator
	*/
	class MessageActuator : public ModuleMessageActuator {
		/**
		* @brief set actuator value
		* @param M superbot module
		* @param Mes message
		*/
		virtual void SetMessageValue(ASuperBotModule* M, ModuleMessage Mes);
	};
	/**
	* @class Joint0Actuator
	* @brief joint 0 actuator
	* 
	*/
	class Joint0Actuator : public ModuleFloatActuator {
		/**
		* @brief set the value
		* @param M superbot module
		* @param  Val value to set
		*/
		virtual void SetFloatValue(ASuperBotModule* M, float Val);
	};
	/**
	* @class Joint1Actuator
	* @brief joint 1 actuator
	*
	*/
	class Joint1Actuator : public ModuleFloatActuator {
		/**
		* @brief set the value
		* @param M superbot module
		* @param  Val value to set
		*/
		virtual void SetFloatValue(ASuperBotModule* M, float Val);
	};
	/**
	* @class Joint2Actuator
	* @brief joint 2 actuator
	*
	*/
	class Joint2Actuator : public ModuleFloatActuator {
		/**
		* @brief set the value
		* @param M superbot module
		* @param  Val value to set
		*/
		virtual void SetFloatValue(ASuperBotModule* M, float Val);
	};
	/**
	* @class DocksEnabledActuator
	* @brief set docks enabled
	*/
	class DockEnabledActuator : public ModuleFlagActuator {
		/**
		* @brief set actuator value
		* @param M module
		* @param Val value to set for actuator
		*/
		virtual void SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val);
	};
	/**
	* @class DocksEnabledActuator
	* @brief set docks enabled
	*/
	class DockEngagedActuator : public ModuleFlagActuator {
		/**
		* @brief set actuator value
		* @param M module
		* @param Val value to set for actuator
		*/
		virtual void SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val);
	};
	/**
	* @class DocksEnabledActuator
	* @brief set docks enabled
	*/
	class DockEngagedToGroundActuator : public ModuleFlagActuator {
		/**
		* @brief set actuator value
		* @param M module
		* @param Val value to set for actuator
		*/
		virtual void SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val);
	};
	/**
	* @class DocksEnabledActuator
	* @brief set docks enabled
	*/
	class DockEngagedToObjectActuator : public ModuleFlagActuator {
		/**
		* @brief set actuator value
		* @param M module
		* @param Val value to set for actuator
		*/
		virtual void SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val);
	};
};
