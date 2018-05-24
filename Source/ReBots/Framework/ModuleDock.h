#include "GameFramework/Pawn.h"
#include "PhysXPublic.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "Framework/ModuleDockFace.h"
#include <sstream>
#include <iostream>
#include <functional>
#pragma once
class AModularRobot;
/**
 * @enum ModuleDockFace
 * @brief superbot dock face
 */
/*enum ModuleDockFace {
    DOCK_0 = 0,
    DOCK_1 = 1,
    DOCK_2 = 2,
    DOCK_3 = 3,
    DOCK_4 = 4,
    DOCK_5 = 5,
    DOCK_6 = 6
};*/
/**
 * @enum ModuleMotor
 * @brief superbot motor constants
 */
enum ModuleMotor {
    MOTOR_0 = 0,
    MOTOR_1 = 1,
    MOTOR_2 = 2,
    MOTOR_3 = 3,
    MOTOR_4 = 4,
    MOTOR_5 = 5,
    MOTOR_6 = 6
};
/**
 * @class ModuleDock
 * @brief SuperBot dock
 * @date 5-18-2015
 * @author Thomas Collins
 */
class REBOTS_API ModuleDock
{
private:
    ModuleDockFace Face; /**< dock face */
    UStaticMeshComponent* DockComponent; /**< dock component */
    AModularRobot* Module; /**< superbot module */
    bool DockEngaged = false; /**< dock engaged ? */
    bool DockEnabled = true; /**< dock enabled ? */
    bool DockEngagedToGround = false; /**< is dock engaged to ground ?*/
    bool DockEnabledToGround = true; /**< is dock enabled to  ground */
	bool DockEngagedToObject = false; /**< is dock enagaged to object */
	bool DockEnabledToObject = true; /**< is dock enabled to object */
public:
    /**
     * @brief set dock face
     * @param df dock face
     */
    void SetFace(ModuleDockFace df);
    /**
     * @brief set dock component
     * @param dc dock component
     */
    void SetDockComponent(UStaticMeshComponent* mc);
    /**
     * @brief set dock module
     * @param m dock module
     */
    void SetModule(AModularRobot* m);
    /**
     * @brief set dock engaged
     * @param dengaged dock engaged
     */
    void SetDockEngaged(bool dengaged);
    /**
     * @brief set dock enabled
     * @param denabled dock enabled
     */
    void SetDockEnabled(bool denabled);
    /**
     * @brief set dock enabled to ground
     * @param etg enabled to ground
     */
    void SetDockEnabledToGround(bool etg);
    /**
     * @brief set dock engaged to ground
     * @param etg engaged to ground
     */
    void SetDockEngagedToGround(bool etg);
	    /**
     * @brief set dock enabled to object
     * @param etg enabled to object
     */
    void SetDockEnabledToObject(bool eto);
    /**
     * @brief set dock engaged to object
     * @param etg engaged to object
     */
    void SetDockEngagedToObject(bool eto);
    /**
     * @brief get dock face
     * @return dock face
     */
    ModuleDockFace GetDockFace();
    /**
     * @brief get dock component
     * @return dock component
     */
    UStaticMeshComponent* GetDockComponent();
    /**
     * @brief get dock module
     * @return dock module
     */
    AModularRobot* GetModule();
    /**
     * @brief get dock engaged
     * @return dock engaged
     */
    bool GetDockEngaged();
    /**
     * @brief get dock enabled
     * @return dock enabled
     */
    bool GetDockEnabled();
    /**
     * @brief get dock enabled to ground
     * @return dock enabled to ground
     */
    bool GetDockEnabledToGround();
    /**
     * @brief get dock engaged to ground
     * @return dock engaged to ground
     */
    bool GetDockEngagedToGround();
	/**
	* @brief get dock enabled to object
	* @return dock enabled to object
	*/
	bool GetDockEnabledToObject();
	/**
	* @brief get dock engaged to object
	* @return dock engaged to object
	*/
	bool GetDockEngagedToObject();
    /**
     * @brief constructor
     * @param df Dock face
     * @param dc dock component
     * @param m module
     */
	ModuleDock(ModuleDockFace df, UStaticMeshComponent* dc, AModularRobot* m);
    /**
     * @brief constructor
     */
    ModuleDock();
    /**
     * @brief destructor
     */
	~ModuleDock();
};
