// Fill out your copyright notice in the Description page of Project Settings.
///TODO: Collision detector not properly working after first stacked object is moved
///TODO: Constraints not properly matched with stackable objects after first one is moved
 
#include "StackToPlaneBehavior.h"
/**
 * @brief constructor
 */
StackToPlaneBehavior::StackToPlaneBehavior() {
    Init();
    this->Name = "StackToPlane";
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
}
/**
 * @brief constructor
 * @param W world
 * @param NameOfModule name of module
 */
StackToPlaneBehavior::StackToPlaneBehavior(UWorld* W, std::string NameOfModule) {
    Init();
    this->Name = "StackToPlane";
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
    this->World = W;
    this->ModuleName = NameOfModule;
    TActorIterator< AStaticMeshActor > ActorIt = TActorIterator< AStaticMeshActor >(World);
    TActorIterator< AManipulatorObjectActor > MActorIt = TActorIterator< AManipulatorObjectActor >(World);
	
	


    while (ActorIt) {
        if (std::string(TCHAR_TO_UTF8(*(*ActorIt)->GetName())).compare("Floor") == 0) {
            Floor = *ActorIt;
            break;
        }
        ++ActorIt;
    }
	if (MActorIt) {
		ManipOb = *MActorIt;
	}
    TActorIterator< ASuperBotModule > SuperBotIt = TActorIterator< ASuperBotModule >(World);
    while (SuperBotIt) {
        if ((*SuperBotIt)->GetName().compare(ModuleName) == 0) {
            SModule = *SuperBotIt;
            break;
        }
        ++SuperBotIt;
    }
    TActorIterator<AStackableObjectActor> StackableIt = TActorIterator <AStackableObjectActor>(World);


    while (StackableIt) {
        StackableObs.push_back(*StackableIt);
        ++StackableIt;
    }
    std::cout<<StackableObs.size()<<" Stackable objects"<<std::endl;
    
    for (int i = 0; i < StackableObs.size(); ++i) {
            for (int j = 0; j < StackableObs.size() - i - 1; ++j)
            {
                if (StackableObs[j]->GetActorTransform().GetLocation().Z <
                    StackableObs[j + 1]->GetActorTransform().GetLocation().Z)
                {
                    AStackableObjectActor* temp = StackableObs[j];
                    StackableObs[j] = StackableObs[j + 1];
                    StackableObs[j + 1] = temp;
                }
            }
    }
    for (int i=0; i<StackableObs.size(); i++) {
        cout<<StackableObs[i]->GetActorTransform().GetLocation().Z<<endl;
    }
    
	TActorIterator<AStackableObjectTargetActor> StackableTargetIt = TActorIterator <AStackableObjectTargetActor>(World);
	while (StackableTargetIt) {
		StackableTargets.push_back(*StackableTargetIt);
		++StackableTargetIt;
	}  

	for (int i = 0; i < StackableTargets.size(); ++i) {
		for (int j = 0; j < StackableTargets.size() - i - 1; ++j)
		{
			if (StackableTargets[j]->GetTransform().GetLocation().Y <
				StackableTargets[j + 1]->GetTransform().GetLocation().Y)
			{
				AStackableObjectTargetActor* temp = StackableTargets[j];
				StackableTargets[j] = StackableTargets[j + 1];
				StackableTargets[j + 1] = temp;
			}
		}
	}
}
/**
 * @brief destructor
 */
StackToPlaneBehavior::~StackToPlaneBehavior() {}







///Stackable objects
/**
* @brief get stackable objects
* @return stackable objects
*/
std::vector<AStackableObjectActor*> StackToPlaneBehavior::GetStackableObs() {
	return this->StackableObs;
}
/**
* @brief get current stackable object index
* @return current stackable object index
*/
int StackToPlaneBehavior::GetCurrentStackableObjectIndex() {
	return this->CurrentStackableOb;
}
/**
* @brief get current pair of stackable objects
* @return stackable object pair
*/
std::pair<AActor*, AActor*> StackToPlaneBehavior::GetCurrentStackablePair() {
	AActor* a1 = StackableObs[CurrentStackableOb];
	AActor* a2 = NULL;
	if (CurrentStackableOb < StackableObs.size() - 1) {
		a2 = StackableObs[CurrentStackableOb + 1];
	}
	else if (CurrentStackableOb == StackableObs.size() - 1) {
		a2 = Floor;
	}
	return std::pair<AActor*, AActor*>(a1, a2);
}









///Special transforms relating module frames and world frame objects
/**
 * @brief get module base to ground transform
 * @return module base to ground transform
 */
FTransform StackToPlaneBehavior::GetModuleBaseToGroundTransform() {
    return ModuleBaseToGroundTransform;
}
/**
 * @brief get module base to object transform
 * @return module base to object transform
 */
FTransform StackToPlaneBehavior::GetModuleBaseToObjectTransform() {
    return ModuleBaseToObjectTransform;
}
/**
* @brief compute full transform to base
* @return full transform of base
*/
FTransform StackToPlaneBehavior::ComputeFullBaseTransform() {
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);
	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
	return FullBaseTransform;
}
/**
* @brief compute local transform to base
* @return local transform of base
*/
FTransform StackToPlaneBehavior::ComputeLocalBaseTransform() {
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);
	FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	return LocalBaseTransform;
}
/**
* @brief compute local transform to base
* @return local transform of base
*/
FTransform StackToPlaneBehavior::ComputeLocalBaseTransformWithAngles(ModuleMotorVector mv) {
	return SuperbotKinematics::computeTransformToDock(mv, GDock);
}
/**
* @brief compute module to ground with walk transform
* @return module to ground with walk transform
*/
FTransform StackToPlaneBehavior::ComputeModuleToGroundWithWalkTransform() {
	FTransform FullBaseTransform = ComputeFullBaseTransform();
	FTransform GroundTransform = Floor->GetTransform();
	GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
	FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
	BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
	FTransform LocalBaseTransform = ComputeLocalBaseTransform();
	FTransform MBTG = ComputeModuleToGroundTransform();
	FTransform TOG = ComputeTargetOnGroundTransform();
	FVector TarDist = (MBTG*LocalBaseTransform).GetLocation() - (TOG*LocalBaseTransform).GetLocation();

	FTransform BasePlusWalkToGround = GroundTransform*FullBaseTransform.Inverse();
	BasePlusWalkToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BasePlusWalkToGround;
	ModuleBaseToGroundWithWalkTransform = BasePlusWalkToGround;
	FTransform InvVWalk = FTransform(FVector(0, ModuleBaseToGroundWithWalkTransform.Inverse().GetLocation().Y,
		ModuleBaseToGroundWithWalkTransform.Inverse().GetLocation().Z));
	ModuleBaseToGroundWithWalkTransform = InvVWalk*BasePlusWalkToGround;
	FTransform DiffTrans = StackableTargets[CurrentStackableOb]->GetTransform()*
		(ModuleBaseToGroundWithWalkTransform*FullBaseTransform).Inverse();
	FVector TarVec = FVector(0, DiffTrans.GetLocation().Y, DiffTrans.GetLocation().Z);
	TarVec.Normalize();
	ModuleBaseToGroundWithWalkTransform = FTransform(370 * TarVec)*ModuleBaseToGroundWithWalkTransform;
	return ModuleBaseToGroundWithWalkTransform;
}

/**
* @brief update module to ground transform
* @return module base to ground transform
*/
FTransform StackToPlaneBehavior::ComputeModuleToGroundTransform() {
	FTransform FullBaseTransform = ComputeFullBaseTransform();
	FTransform GroundTransform = Floor->GetTransform();
	GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
	FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
	BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
	ModuleBaseToGroundTransform = BaseToGround;
	FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
		ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
	ModuleBaseToGroundTransform = InvV*BaseToGround;
	return ModuleBaseToGroundTransform;
}

/**
* @brief get transform on ground
* @return transform on ground representing target
*/
FTransform StackToPlaneBehavior::ComputeTargetOnGroundTransform() {
	FTransform FullBaseTransform = ComputeFullBaseTransform();
	FTransform GroundTransform = Floor->GetTransform();
	GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
	FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
	FTransform TTG = GroundTransform*StackableTargets[CurrentStackableOb]->GetTransform().Inverse();
	FTransform MBTG = ComputeModuleToGroundTransform();
	FTransform TDiff = StackableTargets[CurrentStackableOb]->GetTransform()*(MBTG*FullBaseTransform).Inverse();
	//FTransform Diff = [CurrentStackableOb]->GetTransform()*FullBaseTransform.Inverse();
	TargetOnGround = FTransform(TTG.GetRotation())*TDiff*MBTG;
	FTransform FDiff = GroundTransform*(TargetOnGround*FullBaseTransform).Inverse();
	TargetOnGround = FTransform(FVector(0, 0, FDiff.GetLocation().Z))*TargetOnGround;
	TargetOnGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*TargetOnGround;
	
return TargetOnGround;
}

/**
* @brief get transform on ground
* @return transform on ground representing target
*/
FTransform StackToPlaneBehavior::ComputeObjectTargetOnGroundTransform() {
	FTransform FullBaseTransform = ComputeFullBaseTransform();
	FTransform GroundTransform = Floor->GetTransform();
	GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
	FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
	FTransform TTG = GroundTransform*StackableObs[CurrentStackableOb]->GetActorTransform().Inverse();
	FTransform MBTG = ComputeModuleToGroundTransform();
	FTransform TDiff = StackableObs[CurrentStackableOb]->GetActorTransform()*(MBTG*FullBaseTransform).Inverse();
	//FTransform Diff = [CurrentStackableOb]->GetTransform()*FullBaseTransform.Inverse();
	ObjectOnGround = FTransform(TTG.GetRotation())*TDiff*MBTG;
	FTransform FDiff = GroundTransform*(ObjectOnGround*FullBaseTransform).Inverse();
	ObjectOnGround = FTransform(FVector(0, 0, FDiff.GetLocation().Z))*ObjectOnGround;
	ObjectOnGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ObjectOnGround;

	return ObjectOnGround;
}


/**
* @brief get target on ground transform
* @return target on ground transform
*/
FTransform StackToPlaneBehavior::GetTargetOnGroundTransform() {
	return TargetOnGround;
}
/**
* @brief get transform on ground
* @return transform on ground representing target
*/
FTransform StackToPlaneBehavior::GetObjectOnGroundTransform() {
	return ObjectOnGround;
}
/**
 * @brief Get master inner transform of module associated with this program
 * @return master inner transform
 */
FTransform StackToPlaneBehavior::GetMasterInnerTransformForBaseModule() {
    TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(World);
    while (SuperbotIt) {
        string str = (*SuperbotIt)->GetName();
        if (str.compare(this->ModuleName) == 0) {
            return (*SuperbotIt)->GetMasterInnerMesh()->GetComponentTransform();
        }
    }
    return FTransform(FVector(-1, -1, -1));
}










///Dynamic connections to objects
/**
 * @brief set joints distributed
 * @param JAngles joint angles
 */
void StackToPlaneBehavior::ConnectNewEffector() {
    GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Blue, FString("Switching Ground Module"));
    if (GDock == DOCK_1) {
        AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_GROUND, false));
    }
    else if (GDock == DOCK_0) {
        AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_GROUND, false));
    }
    cout << "Selected End Effector: " << SelectedEndEffector << endl;
    TreeMessage tcm("ConnectEffector", st.GetVertices().size(), st.GetVertices().size());
	tcm.OffsetAngle = AOffsetAngle1;
	tcm.ProgramMode = (STPProgramMode)M;
	tcm.CurrentOb = CurrentStackableOb;
    ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
    tcm.N = cNode;
    if (cNode->GetDockFacePath().size() > 2) {
        tcm.Command = "ConnectEffectorI";
        AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
    }
    else {
        tcm.Command = "ConnectEffector";
        AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
    }
}
/**
 * @brief connect object
 */
void StackToPlaneBehavior::ConnectObject() {
    cout << "Selected End Effector: " << SelectedEndEffector << endl;
    GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Blue, FString("Connecting"));
    TreeMessage tcm("ConnectObject", st.GetVertices().size(), st.GetVertices().size());
    ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
    tcm.N = cNode;
    if (cNode->GetDockFacePath().size() > 2) {
        tcm.Command = "ConnectObjectI";
        AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
    }
    else {
        tcm.Command = "ConnectObject";
        AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
    }
}
/**
 * @brief reconnect object to ground
 */
void StackToPlaneBehavior::ReconnectObjectToGround() {
    cout << "Selected End Effector: " << SelectedEndEffector << endl;
    GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Blue, FString("ReConnecting to ground"));
    TreeMessage tcm("ReConnectObject", st.GetVertices().size(), st.GetVertices().size());
    ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
    tcm.N = cNode;
    if (cNode->GetDockFacePath().size() > 2) {
        tcm.Command = "ReConnectObjectI";
        AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
    }
    else {
        tcm.Command = "ReConnectObject";
        AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
    }
}













///Collision detection
/**
 * @brief collision function
 * @param point point to check
 * @return collision (true) or not (false)
 */
bool StackToPlaneBehavior::CollisionFunction(std::vector<float> point) {
    return IsInCollisionWithGroundDetailed(point) || IsInSelfCollisionDetailed(point);
}
/**
 * @brief state valid
 * @param point point to check
 * @return true if state valid false otherwise
 */
bool StackToPlaneBehavior::StateValid(std::vector<float> point) {
    return !CollisionFunction(point);
}
/**
 * @brief detect ground collision
 * @param point point to check
 * @return is position in collision with ground
 */
bool StackToPlaneBehavior::IsInCollisionWithGroundDetailed(std::vector<float> point) {
    vector<ModuleNode*> Mods(st.GetVertices().size());
    ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                st.GetVertices()[GroundModule]->GetJointAngles()[2]);
    FTransform ActualBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
    for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);
	//ComputeObjectPose();
    vector<ModuleMotorVector> mvsFinals;
    ModuleMotorVector groundAngles;
    vector<ModuleDockFace> mvsDocks;
    groundAngles = ModuleMotorVector(point[0], point[1], point[2]);
    //FTransform LocalBaseTransform = SuperbotKinematics::computeTransformFromDock(groundAngles, GDock);
    FTransform BaseTransform = FTransform(FVector(0,0,0));
	//ModuleDockFace ObDock;
	for (int i = 0; i<st.GetVertices().size(); i++) {
        if (st.GetVertices()[i]->GetAmIEndEffector()) {
            mvsFinals.push_back(ModuleMotorVector(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]));
            ModuleDockFace D = (ModuleDockFace)st.GetVertices()[i]->GetDockFacePath()[st.GetVertices()[i]->GetDockFacePath().size() - 1].first;
            if (D == DOCK_0) {
                mvsDocks.push_back(DOCK_1);
            }
            else {
                mvsDocks.push_back(DOCK_0);
            }
        }
    }

    
    FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
    ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
    FTransform GroundTransform = Floor->GetTransform();
    GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
    FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
    BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
    FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(groundAngles, GDock);
    FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                         ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
    FTransform AGroundTransform = BaseToGround*LocalBaseTransform;
    
    

	bool isObjectConnected = false;
	int objectTs = -1;
	for (int i = 0; i < st.GetVertices().size(); i++) {
		if (st.GetVertices()[i]->GetAmIConnectedToObject()) {
			isObjectConnected = true;
			objectTs = i;
		}
	}
	FTransform obTrans;
	if (isObjectConnected) {
		ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[objectTs]->GetDockFacePath()[st.GetVertices()[objectTs]->GetDockFacePath().size() - 1].first;
		ModuleDockFace EEDockFace;
		if (LastDockFace == DOCK_0) {
			EEDockFace = DOCK_1;
		}
		else {
			EEDockFace = DOCK_0;
		}
		ModuleMotorVector currJoints(point[3 * objectTs + 0], point[3 * objectTs + 1], point[3 * objectTs + 2]);
		if (EEDockFace == DOCK_0) {
			obTrans = FTransform(FVector(ObjectExtents.Z / 1.8, 0, 0))*
				SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
				Ts[objectTs] * LocalBaseTransform;
		}
		else {
			obTrans = FTransform(FVector(-ObjectExtents.Z / 1.8, 0, 0))*
				SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
				Ts[objectTs] * LocalBaseTransform;
		}
	}

    physx::PxTransform transGround;
    physx::PxBoxGeometry groundGeometry;
    if (GDock == DOCK_0) {
        BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
    }
    else {
        BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
    }
    FTransform GroundFix = FTransform(FVector(-207,0,0));
    physx::PxTransform transBase = U2PTransform(GroundFix*AGroundTransform);
    groundGeometry = physx::PxBoxGeometry(200, 1000, 1000);
    vector<FTransform> obTranss(StackableObs.size());
    vector<physx::PxTransform> transObjects(obTranss.size());
    for (int i=0; i<StackableObs.size(); i++) {
        FTransform MBToOb = FTransform(FVector(0,0,50))*StackableObs[i]->GetActorTransform();
        MBToOb = FTransform(FVector(0, 0, 50))*StackableObs[i]->GetActorTransform();
        MBToOb.SetScale3D(FVector(1.,1.,1.));

		if (isObjectConnected && i == CurrentStackableOb) {
			obTranss[i] = obTrans;
			transObjects[i] = U2PTransform(obTranss[i]);
		}
		else {
			obTranss[i] = MBToOb*FullBaseTransform.Inverse();
			obTranss[i] = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*obTranss[i];
			transObjects[i] = U2PTransform(obTranss[i] * LocalBaseTransform);
		}
    }
    PxBoxGeometry objGeom(ObjectExtents.Z / 2, ObjectExtents.Y / 2, ObjectExtents.X / 2);
	PxBoxGeometry objGeom2(ObjectExtents.Z / 2.5, ObjectExtents.Y / 2.5, ObjectExtents.X / 2.5);
    for (int i = 0; i<Ts.size(); i++) {
        FTransform MInnerTrans = FTransform(FVector(30.0, 0.0, 0))*Ts[i]*LocalBaseTransform;
        FTransform SInnerTrans = FTransform(FVector(-30.0, 0.0, 0))*Ts[i]*LocalBaseTransform;
        SInnerTrans = FTransform(FQuat(FVector(1, 0, 0), (M_PI / 180.0)*point[3 * i + 1]))*SInnerTrans;
        ModuleMotorVector currJoints(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]);
        FTransform MOuterTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
        Ts[i]*LocalBaseTransform;
        FTransform SOuterTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
        Ts[i]*LocalBaseTransform;
        FTransform MOuterLeftTrans = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterTrans;
        FTransform MOuterRightTrans = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterTrans;
        FTransform SOuterLeftTrans = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterTrans;
        FTransform SOuterRightTrans = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterTrans;
        MOuterTrans = FTransform(FVector(-10, 0, 0))*MOuterTrans;
        SOuterTrans = FTransform(FVector(10, 0, 0))*SOuterTrans;
        physx::PxTransform trans1 = U2PTransform(MInnerTrans);
        physx::PxBoxGeometry geom1(30, 37.5, 37.5);
        physx::PxTransform trans2 = U2PTransform(SInnerTrans);
        physx::PxBoxGeometry geom2(30, 37.5, 37.5);
        physx::PxTransform trans3 = U2PTransform(MOuterTrans);
        physx::PxBoxGeometry geom3(5, 37.5, 37.5);
        physx::PxTransform trans4 = U2PTransform(SOuterTrans);
        physx::PxBoxGeometry geom4(5, 37.5, 37.5);
        physx::PxTransform trans5 = U2PTransform(MOuterLeftTrans);
        physx::PxBoxGeometry geom5(50, 37.5, 9);
        physx::PxTransform trans6 = U2PTransform(MOuterRightTrans);
        physx::PxBoxGeometry geom6(50, 37.5, 9);
        physx::PxTransform trans7 = U2PTransform(SOuterLeftTrans);
        physx::PxBoxGeometry geom7(50, 37.5, 9);
        physx::PxTransform trans8 = U2PTransform(SOuterRightTrans);
        physx::PxBoxGeometry geom8(50, 37.5, 9);
        if (physx::PxGeometryQuery::overlap(geom1, trans1, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom2, trans2, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom3, trans3, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom4, trans4, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom5, trans5, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom6, trans6, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom7, trans7, groundGeometry, transBase) ||
            physx::PxGeometryQuery::overlap(geom8, trans8, groundGeometry, transBase)) {
            return true;
        }
		if (i == objectTs && isObjectConnected) continue;
        for (int j=0; j<obTranss.size(); j++) {
				if (physx::PxGeometryQuery::overlap(geom1, trans1, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom2, trans2, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom3, trans3, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom4, trans4, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom5, trans5, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom6, trans6, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom7, trans7, objGeom, transObjects[j]) ||
					physx::PxGeometryQuery::overlap(geom8, trans8, objGeom, transObjects[j])) {
					///TODO: Causing an error with the second stackable object
					return true;
				}

        }
    }
    
    for (int i=0; i<obTranss.size(); i++) {
        if (physx::PxGeometryQuery::overlap(objGeom, transObjects[i], groundGeometry, transBase)) {
            return true;
        }
        for (int j=i +1; j<obTranss.size(); j++) {
            if (physx::PxGeometryQuery::overlap(objGeom, transObjects[i], objGeom, transObjects[j])) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief detect self collision
 * @param point point to check
 * @return is position in self collision
 */
bool StackToPlaneBehavior::IsInSelfCollisionDetailed(std::vector<float> point) {
    vector<ModuleNode*> Mods(st.GetVertices().size());
    ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                st.GetVertices()[GroundModule]->GetJointAngles()[2]);
    FTransform ActualBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
    for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);
    
    vector<ModuleMotorVector> mvsFinals;
    ModuleMotorVector groundAngles;
    vector<ModuleDockFace> mvsDocks;
    groundAngles = ModuleMotorVector(point[0], point[1], point[2]);
    //FTransform LocalBaseTransform = SuperbotKinematics::computeTransformFromDock(groundAngles, GDock);
    FTransform BaseTransform = FTransform(FVector(0, 0, 0));
    for (int i = 0; i<st.GetVertices().size(); i++) {
        if (st.GetVertices()[i]->GetAmIEndEffector()) {
            mvsFinals.push_back(ModuleMotorVector(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]));
            ModuleDockFace D = (ModuleDockFace)st.GetVertices()[i]->GetDockFacePath()[st.GetVertices()[i]->GetDockFacePath().size() - 1].first;
            if (D == DOCK_0) {
                mvsDocks.push_back(DOCK_1);
            }
            else {
                mvsDocks.push_back(DOCK_0);
            }
        }
    }
    
    
    FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
    ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
    FTransform GroundTransform = Floor->GetTransform();
    GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
    FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
    BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
    FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(groundAngles, GDock);
    FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                         ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
    FTransform AGroundTransform = BaseToGround*LocalBaseTransform;
    
    
    physx::PxTransform transGround;
    physx::PxBoxGeometry groundGeometry;
    if (GDock == DOCK_0) {
        BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
    }
    else {
        BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
    }
    FTransform GroundFix = FTransform(FVector(-225, 0, 0));
    if (GDock == DOCK_0) {
        //FTransform GroundFix = FTransform(FVector(-225, 0, 0));
    }
    physx::PxTransform transBase = U2PTransform(GroundFix*AGroundTransform);
    groundGeometry = physx::PxBoxGeometry(200, 1000, 1000);
    for (int i = 0; i<Ts.size(); i++) {
        for (int j = i + 1; j < Ts.size(); j++) {
            
            FTransform MInnerTrans1 = FTransform(FVector(30.0, 0.0, 0))*Ts[i] * LocalBaseTransform;
            FTransform SInnerTrans1 = FTransform(FVector(-30.0, 0.0, 0))*Ts[i] * LocalBaseTransform;
            SInnerTrans1 = FTransform(FQuat(FVector(1, 0, 0), (M_PI / 180.0)*point[3 * i + 1]))*SInnerTrans1;
            ModuleMotorVector currJoints1(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]);
            FTransform MOuterTrans1 = SuperbotKinematics::computeTransformToDock(currJoints1, DOCK_0)*
            Ts[i] * LocalBaseTransform;
            FTransform SOuterTrans1 = SuperbotKinematics::computeTransformToDock(currJoints1, DOCK_1)*
            Ts[i] * LocalBaseTransform;
            FTransform MOuterLeftTrans1 = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterTrans1;
            FTransform MOuterRightTrans1 = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterTrans1;
            FTransform SOuterLeftTrans1 = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterTrans1;
            FTransform SOuterRightTrans1 = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterTrans1;
            MOuterTrans1 = FTransform(FVector(-10, 0, 0))*MOuterTrans1;
            SOuterTrans1 = FTransform(FVector(10, 0, 0))*SOuterTrans1;
            
            FTransform MInnerTrans2 = FTransform(FVector(30.0, 0.0, 0))*Ts[j] * LocalBaseTransform;
            FTransform SInnerTrans2 = FTransform(FVector(-30.0, 0.0, 0))*Ts[j] * LocalBaseTransform;
            SInnerTrans2 = FTransform(FQuat(FVector(1, 0, 0), (M_PI / 180.0)*point[3 * j + 1]))*SInnerTrans2;
            ModuleMotorVector currJoints2(point[3 * j + 0], point[3 * j + 1], point[3 * j + 2]);
            FTransform MOuterTrans2 = SuperbotKinematics::computeTransformToDock(currJoints2, DOCK_0)*
            Ts[j] * LocalBaseTransform;
            FTransform SOuterTrans2 = SuperbotKinematics::computeTransformToDock(currJoints2, DOCK_1)*
            Ts[j] * LocalBaseTransform;
            FTransform MOuterLeftTrans2 = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterTrans2;
            FTransform MOuterRightTrans2 = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterTrans2;
            FTransform SOuterLeftTrans2 = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterTrans2;
            FTransform SOuterRightTrans2 = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterTrans2;
            MOuterTrans2 = FTransform(FVector(-10, 0, 0))*MOuterTrans2;
            SOuterTrans2 = FTransform(FVector(10, 0, 0))*SOuterTrans2;
            
            
            physx::PxTransform trans11 = U2PTransform(MInnerTrans1);
            physx::PxBoxGeometry geom11(30, 37.5, 37.5);
            physx::PxTransform trans21 = U2PTransform(SInnerTrans1);
            physx::PxBoxGeometry geom21(30, 37.5, 37.5);
            physx::PxTransform trans31 = U2PTransform(MOuterTrans1);
            physx::PxBoxGeometry geom31(5, 37.5, 37.5);
            physx::PxTransform trans41 = U2PTransform(SOuterTrans1);
            physx::PxBoxGeometry geom41(5, 37.5, 37.5);
            physx::PxTransform trans51 = U2PTransform(MOuterLeftTrans1);
            physx::PxBoxGeometry geom51(50, 37.5, 9);
            physx::PxTransform trans61 = U2PTransform(MOuterRightTrans1);
            physx::PxBoxGeometry geom61(50, 37.5, 9);
            physx::PxTransform trans71 = U2PTransform(SOuterLeftTrans1);
            physx::PxBoxGeometry geom71(50, 37.5, 9);
            physx::PxTransform trans81 = U2PTransform(SOuterRightTrans1);
            physx::PxBoxGeometry geom81(50, 37.5, 9);
            
            
            physx::PxTransform trans12 = U2PTransform(MInnerTrans2);
            physx::PxBoxGeometry geom12(30, 37.5, 37.5);
            physx::PxTransform trans22 = U2PTransform(SInnerTrans2);
            physx::PxBoxGeometry geom22(30, 37.5, 37.5);
            physx::PxTransform trans32 = U2PTransform(MOuterTrans2);
            physx::PxBoxGeometry geom32(5, 37.5, 37.5);
            physx::PxTransform trans42 = U2PTransform(SOuterTrans2);
            physx::PxBoxGeometry geom42(5, 37.5, 37.5);
            physx::PxTransform trans52 = U2PTransform(MOuterLeftTrans2);
            physx::PxBoxGeometry geom52(50, 37.5, 9);
            physx::PxTransform trans62 = U2PTransform(MOuterRightTrans2);
            physx::PxBoxGeometry geom62(50, 37.5, 9);
            physx::PxTransform trans72 = U2PTransform(SOuterLeftTrans2);
            physx::PxBoxGeometry geom72(50, 37.5, 9);
            physx::PxTransform trans82 = U2PTransform(SOuterRightTrans2);
            physx::PxBoxGeometry geom82(50, 37.5, 9);
            
            std::vector<physx::PxBoxGeometry> boxGeoms1{ geom11, geom21, geom31, geom41, geom51, geom61,geom71,geom81 };
            std::vector<physx::PxBoxGeometry> boxGeoms2{ geom12, geom22, geom32, geom42, geom52, geom62,geom72,geom82 };
            std::vector<physx::PxTransform> transs1{ trans11, trans21, trans31, trans41, trans51, trans61,trans71,trans81 };
            std::vector<physx::PxTransform> transs2{ trans12, trans22, trans32, trans42, trans52, trans62,trans72,trans82 };
            
            if (physx::PxGeometryQuery::overlap(geom11, trans11, geom12, trans12) ||
                physx::PxGeometryQuery::overlap(geom21, trans21, geom22, trans22) ||
                physx::PxGeometryQuery::overlap(geom31, trans31, geom32, trans32) ||
                physx::PxGeometryQuery::overlap(geom41, trans41, geom42, trans42) ||
                physx::PxGeometryQuery::overlap(geom51, trans51, geom52, trans52) ||
                physx::PxGeometryQuery::overlap(geom61, trans61, geom62, trans62) ||
                physx::PxGeometryQuery::overlap(geom71, trans71, geom72, trans72) ||
                physx::PxGeometryQuery::overlap(geom81, trans81, geom82, trans82)) {
               // return true;
            }
        }
    }
    for (int i = 0; i<Ts.size(); i++) {
        for (int j = i + 1; j<Ts.size(); j++) {
            FVector DiffVec = Ts[i].GetLocation() - Ts[j].GetLocation();
            if (DiffVec.Size() < 120.0) return true;
        }
    }
    return false;
}








//Foot placement planning
/**
* @brief state valid
* @param point point to check
* @return true if state valid false otherwise
*/
bool StackToPlaneBehavior::StateValidFoot(std::vector<float> point) {
	return !CollisionFunctionFoot(point);
}
/**
* @brief is in collision with ground for foot
* @param P point to check
* @return is in collision with ground (true) or not (false)
*/
bool StackToPlaneBehavior::IsInCollisionWithGroundFoot(std::vector<float> P) {
	
	vector<ModuleNode*> Mods(st.GetVertices().size());
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);

	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
	FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);

	vector<FTransform> obTranss(StackableObs.size());
	vector<physx::PxTransform> transObjects(obTranss.size());
	for (int i = 0; i<StackableObs.size(); i++) {
		FTransform MBToOb = StackableObs[i]->GetActorTransform();
		MBToOb = StackableObs[i]->GetActorTransform();
		MBToOb.SetScale3D(FVector(1., 1., 1.));
		obTranss[i] = MBToOb*FullBaseTransform.Inverse();
		obTranss[i] = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*obTranss[i];
		transObjects[i] = U2PTransform(obTranss[i] * LocalBaseTransform);
	}
	PxBoxGeometry objGeom(ObjectExtents.Z / 2.5, ObjectExtents.Y / 2, ObjectExtents.X / 2);
	PxBoxGeometry objGeom2(ObjectExtents.Z / 2.5, ObjectExtents.Y / 2.5, ObjectExtents.X / 2.5);
	physx::PxBoxGeometry geomFoot(5, 37.5, 37.5);
	FTransform FootT = FTransform(FVector(P[0],P[1],P[2]))*LocalBaseTransform;
	physx::PxTransform transFoot = U2PTransform(FootT);

	for (int j = 0; j<obTranss.size(); j++) {
		if (physx::PxGeometryQuery::overlap(geomFoot, transFoot, objGeom, transObjects[j])) return true;

	}

	return false;
}
/**
* @brief is in collision with ground for foot
* @param P point to check
* @return is in collision with ground (true) or not (false)
*/
bool StackToPlaneBehavior::CollisionFunctionFoot(std::vector<float> P) {
	return IsInCollisionWithGroundFoot(P);
}
/**
* @brief find target foot location
* @return true if process finished, false otherwise
*/
bool StackToPlaneBehavior::FindTargetFootLocation() {
	return true;
}
/**
* @brief plan foot path current foot to target foot
* @return true when process finished, false otherwise
*/
bool StackToPlaneBehavior::PlanFootPathCurrentFootToTargetFoot() {
	if (PPCounter == 0) {
		Path.clear();
		HaveInitiatedPP = false;
		HaveCompletedPP = false;
	}
	if (HaveInitiatedPP && !HaveCompletedPP) {
		GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Planning Path To Goal. Num Nodes: %d"), RRTWorker->GetGraphSize()));
		HaveCompletedPP = RRTWorker->IsFinished();
		if (HaveCompletedPP) {
			GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("Done Planning.")));
			Path.push_back(SolutionPos);
			RRTWorker->Stop();
			RRTWorker->Shutdown();
			PPCounter = 0;
			return true;
		}
	}
	else {
		FTransform MBTO  = ComputeObjectPose();
		FTransform MBTG = ComputeModuleToGroundTransform();
		FTransform TOG = ComputeTargetOnGroundTransform();


		HaveInitiatedPP = true;
		std::vector<std::pair<float, float> > run(3);
		std::vector<std::pair<float, float> > vel(3);
		std::vector<float> goal(3);
		std::vector<float> start(3);

		run[0] = std::pair<float,float>(TOG.GetLocation().X, TOG.GetLocation().X);
		run[1] = std::pair<float, float>(-100000, 100000);
		run[2] = std::pair<float, float>(-100000, 100000);

		goal[0] = TOG.GetLocation().X;
		goal[1] = TOG.GetLocation().Y;
		goal[2] = TOG.GetLocation().Z;

		start[0] = MBTG.GetLocation().X;
		start[1] = MBTG.GetLocation().Y;
		start[2] = MBTG.GetLocation().Z;

		CurrentPathElement = 0;
		float FitVal;
		vector<ModuleNode*> Mods(st.GetVertices().size());
		for (int i = 0; i < st.GetVertices().size(); i++) {
			Mods[i] = st.GetVertices()[i];
		}
		BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
		RRTWorker = FRRTWorker::RRTInit(5000, 3, 100, run, 20.0,
			std::bind(&StackToPlaneBehavior::StateValidFoot, this, std::placeholders::_1),
			std::bind(&StackToPlaneBehavior::Distance, this, std::placeholders::_1,
				std::placeholders::_2),
			start, goal, FootPath, &FitVal);
	}
	PPCounter++;
	return false;
}
/**
* @brief execute foot path
* @return true when process finished, false otherwise
*/
bool StackToPlaneBehavior::ExecuteFootPath() {
	return true;
}
/**
* @brief fitness function for IK
* @param P particle
* @param tar target
* @return fitness value
*/
float StackToPlaneBehavior::FitnessFoot(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);

	//Full base transform
	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();


	FTransform GroundTransform = Floor->GetTransform();
	GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
	FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
	BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
	FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	FTransform MBaseToGroundTransform = BaseToGround;
	FTransform InvV = FTransform(FVector(0, MBaseToGroundTransform.Inverse().GetLocation().Y,
		MBaseToGroundTransform.Inverse().GetLocation().Z));
	//Transform from module base to actual ground
	MBaseToGroundTransform = InvV*BaseToGround;
	MBaseToGroundTransform = FTransform(FVector(0,0,P.GetPosition()[1]))*FTransform(FQuat(FVector(1,0,0), P.GetPosition()[0]))*MBaseToGroundTransform;
	float SizeDiff = (StackableTargets[CurrentStackableOb]->GetTransform().GetLocation() - MBaseToGroundTransform.GetLocation()).Size();
	if (SizeDiff > 450) {
		return SizeDiff - 450;
	}
	else if (SizeDiff < 300) {
		return 10000;
	}
	return 0.0;
}





///Path planning functionality
/**
 * @brief plan path from current angles to 0 angles (default)
 * @return true if planning completed, false otherwise
 */
bool StackToPlaneBehavior::PlanPathCurrentAnglesTo0Angles() {
    if (PPCounter == 0) {
        Path.clear();
        HaveInitiatedPP = false;
        HaveCompletedPP = false;
    }
    if (HaveInitiatedPP && !HaveCompletedPP) {
        HaveCompletedPP = RRTWorker->IsFinished();
        GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("Planning Path To 0. Num Nodes: %d"), RRTWorker->GetGraphSize()));
        if (HaveCompletedPP) {
            vector<float> zeros(st.GetVertices().size() * 3);
            for (int i = 0; i < zeros.size(); i++) {
                zeros[i] = 0.0;
            }
            Path.push_back(zeros);
            GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Red,
                                             FString::Printf(TEXT("Done Planning.")));
            RRTWorker->Stop();
            RRTWorker->Shutdown();
            PPCounter = 0;
            return true;
        }
    }
    else {
        HaveInitiatedPP = true;
        std::vector<std::pair<float, float> > run(st.GetVertices().size() * 3);
        std::vector<std::pair<float, float> > vel(st.GetVertices().size() * 3);
        std::vector<float> goal(st.GetVertices().size() * 3);
        std::vector<float> start(st.GetVertices().size() * 3);
        for (int i = 0; i < vel.size(); i++) {
            run[i] = std::pair<float, float>(-90, 90);
            vel[i] = std::pair<float, float>(-90, 90);
            goal[i] = 0.0;
        }
        for (int i = 0; i<st.GetVertices().size(); i++) {
            start[3 * i + 0] = st.GetVertices()[i]->GetJointAngles()[0];
            start[3 * i + 1] = st.GetVertices()[i]->GetJointAngles()[1];
            start[3 * i + 2] = st.GetVertices()[i]->GetJointAngles()[2];
        }
        CurrentPathElement = 0;
        float FitVal;
        vector<ModuleNode*> Mods(st.GetVertices().size());
        for (int i = 0; i < st.GetVertices().size(); i++) {
            Mods[i] = st.GetVertices()[i];
        }
        //BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
        bool ssc = IsInSelfCollisionDetailed(start);
        bool sgc = IsInCollisionWithGroundDetailed(start);
        bool gsc = IsInSelfCollisionDetailed(goal);
        bool ggc = IsInCollisionWithGroundDetailed(goal);
        
        if (ssc) {
            cout<<"Start Configuration Failed Self Collision Test"<<endl;
        }
        if (sgc) {
            cout<<"Start Configuration Failed Ground Collision Test"<<endl;
        }
        if (gsc) {
            cout<<"Goal Configuration Failed Self Collision Test"<<endl;
        }
        if (ggc) {
            cout<<"Goal Configuration Failed Ground Collision Test"<<endl;
        }
        
        RRTWorker = FRRTWorker::RRTInit(5000, st.GetVertices().size() * 3, 100, run, 20.0,
                                        std::bind(&StackToPlaneBehavior::StateValid, this, std::placeholders::_1),
                                        std::bind(&StackToPlaneBehavior::Distance, this, std::placeholders::_1,
                                                  std::placeholders::_2),
                                        start, goal, Path, &FitVal);
    }
    PPCounter++;
    return false;
}
/**
 * @brief find optimal goals for IK procedure
 * @return true if process completed, false otherwise
 */
bool StackToPlaneBehavior::FindGoalAnglesWithIK() {
    if (IKCounter == 0) {
        HaveInitiatedIK = false;
        HaveCompletedIK = false;
    }
    


    if (HaveInitiatedIK && !HaveCompletedIK) {
        HaveCompletedIK = PSOWorker->IsFinished();
        float IKError = 1000.0;
        if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
            IKError = 1000.0;
        }
        else {
            IKError = PSOWorker->GetCurrentUpperBound();
        }
        GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("IK Current Error: %f"), IKError));
        GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
        if (HaveCompletedIK) {
            GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
                                             FString::Printf(TEXT("IK Finished")));
            PSOWorker->Stop();
            PSOWorker->Shutdown();
            IKCounter = 0;
            return true;
        }
    }
    else {
        std::vector<int> PossibleEndEffectors;
        for (int i = 1; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetAmIEndEffector() && !smn->GetAmIConnectedToObject()) {
                PossibleEndEffectors.push_back(i);
            }
        }
        if (CurrentDockEngagedToGroundStatus[0]) {
            GDock = DOCK_0;
        }
        else if (CurrentDockEngagedToGroundStatus[1]) {
            GDock = DOCK_1;
        }
        
        for (int i = 0; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetConnectedToGround()) {
                GroundModule = smn->GetName();
            }
        }
        ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[2]);
        if (PossibleEndEffectors.size() > 1) {
            std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
            int RandEffector = posRand(Generator);
            cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
            SelectedEndEffector = PossibleEndEffectors[RandEffector];
            ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
            if (LastDockFace == DOCK_0) {
                EEDock = DOCK_1;
            }
            else {
                EEDock = DOCK_0;
            }
        }
        else if (PossibleEndEffectors.size() == 1) {
            SelectedEndEffector = PossibleEndEffectors[0];
            ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
            if (LastDockFace == DOCK_0) {
                EEDock = DOCK_1;
            }
            else {
                EEDock = DOCK_0;
            }
        }
        else {
            SelectedEndEffector = -1;
        }
        FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
        ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
        CurrentX = FullBaseTransform.GetLocation().X;
        GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
        FTransform GroundTransform = Floor->GetTransform();
        GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
        FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
        BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
        FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
        ModuleBaseToGroundTransform = BaseToGround;
        FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                             ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
        ModuleBaseToGroundTransform = InvV*BaseToGround;
        ActualGroundTransform = BaseToGround*LocalBaseTransform;

		FVector TarDist = (ModuleBaseToGroundTransform*LocalBaseTransform).GetLocation() - (TargetOnGround*LocalBaseTransform).GetLocation();

		GEngine->AddOnScreenDebugMessage(TargetDistanceKey, 15., FColor::Red, FString::Printf(TEXT("Distance to T: %f"),TarDist.Size()));

		FVector Dir = (TargetTransform).GetLocation();
		Dir.Normalize(); 
		FVector NewLocation = 350 * FVector(0,Dir.Y,Dir.Z);
		WalkingTarget = FTransform(NewLocation);

		FTransform BasePlusWalkToGround = GroundTransform*FullBaseTransform.Inverse();
		BasePlusWalkToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BasePlusWalkToGround;
		ModuleBaseToGroundWithWalkTransform = BasePlusWalkToGround;
		FTransform InvVWalk = FTransform(FVector(0, ModuleBaseToGroundWithWalkTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundWithWalkTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundWithWalkTransform = InvVWalk*BasePlusWalkToGround;
		FTransform DiffTrans = StackableTargets[CurrentStackableOb]->GetTransform()*
			(ModuleBaseToGroundWithWalkTransform*FullBaseTransform).Inverse();
		FVector TarVec = FVector(0,DiffTrans.GetLocation().Y, DiffTrans.GetLocation().Z);
		TarVec.Normalize();
		ModuleBaseToGroundWithWalkTransform = FTransform(350*TarVec)*ModuleBaseToGroundWithWalkTransform;



		FTransform BasePlusObjectWalkToGround = GroundTransform*FullBaseTransform.Inverse();
		BasePlusObjectWalkToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BasePlusObjectWalkToGround;
		ModuleBaseToGroundWithObjectWalkTransform = BasePlusObjectWalkToGround;
		FTransform InvVObjectWalk = FTransform(FVector(0, ModuleBaseToGroundWithObjectWalkTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundWithObjectWalkTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundWithObjectWalkTransform = InvVObjectWalk*BasePlusObjectWalkToGround;
		FTransform DiffObjectTrans = StackableObs[CurrentStackableOb]->GetActorTransform()*
			(ModuleBaseToGroundWithObjectWalkTransform*FullBaseTransform).Inverse();
		FVector TarVecObject = FVector(0, DiffObjectTrans.GetLocation().Y, DiffObjectTrans.GetLocation().Z);
		TarVecObject.Normalize();
		ModuleBaseToGroundWithObjectWalkTransform = FTransform(350 * TarVecObject)*ModuleBaseToGroundWithObjectWalkTransform;



        if (SelectedEndEffector != -1) {
            std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
            std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
            for (int i = 0; i < st.GetVertices().size() * 3; i++)
            {
                posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
            }
            SolutionPos = vector<float>(st.GetVertices().size() * 3);
            PSOWorker = FBBPSOWorker::BBPSOInit(50, 50, st.GetVertices().size() * 3, posB, velB, 3.0,
                                                std::bind(&StackToPlaneBehavior::Fitness, this,
                                                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                                std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
                                                SolutionPos, &SolutionFitness);
            HaveInitiatedIK = true;
        }
        else {
            PS = NULL;
        }
    }
    IKCounter++;
    return false;
}
/**
* @brief compute transformation between target and current foot
* @param Target target transform
* @param Foot current foot transform
*/
FTransform StackToPlaneBehavior::ComputeTransformTargetToFoot() {
	if (CurrentDockEngagedToGroundStatus[0]) {
		GDock = DOCK_0;
	}
	else if (CurrentDockEngagedToGroundStatus[1]) {
		GDock = DOCK_1;
	}

	for (int i = 0; i < st.GetVertices().size(); i++) {
		ModuleNode *smn = st.GetVertices()[i];
		if (smn->GetConnectedToGround()) {
			GroundModule = smn->GetName();
		}
	}
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);
	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		TargetTransform = StackableTargets[CurrentStackableOb]->GetTransform()*FullBaseTransform.Inverse();
return	TargetTransform;
}
/**
 * @brief find optimal goal angles for picking up object
 * @return true if process completed, false otherwise
 */
bool StackToPlaneBehavior::FindGoalAnglesForObject() {
    if (ObjectIKCounter == 0) {
        HaveInitiatedIK = false;
        HaveCompletedIK = false;
    }
    
    if (HaveInitiatedIK && !HaveCompletedIK) {
        HaveCompletedIK = PSOWorker->IsFinished();
        float IKError = 1000.0;
        if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
            IKError = 1000.0;
        }
        else {
            IKError = PSOWorker->GetCurrentUpperBound();
        }
        GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("IK To Object Current Error: %f"), IKError));
        GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
        if (HaveCompletedIK) {
            GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
                                             FString::Printf(TEXT("IK Finished")));
            PSOWorker->Stop();
            PSOWorker->Shutdown();
            ObjectIKCounter = 0;
			//Compute offset
			vector<ModuleNode*> Mods(st.GetVertices().size());
			for (int i = 0; i < st.GetVertices().size(); i++) {
				Mods[i] = st.GetVertices()[i];
			}
			ModuleMotorVector mvsGround(SolutionPos[0], SolutionPos[1], SolutionPos[2]);
			FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
			//vector<ModuleNode*> Mods(st.GetVertices().size());
			BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
			FTransform FTargetTransform = ComputeObjectPose()*BaseTransform;
			if (EEDock == DOCK_0) {
				FTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FTargetTransform;
			}
			int EE = GetSelectedEndEffector();
			ModuleMotorVector mvsFinal = ModuleMotorVector(SolutionPos[3 * SelectedEndEffector + 0],
				SolutionPos[3 * SelectedEndEffector + 1],
				SolutionPos[3 * SelectedEndEffector + 2]);
			FTransform F = 
				SuperbotKinematics::computeTransformToDock(mvsFinal, EEDock)*BestTransformsFound[EE]*BaseTransform;
			AttachmentOffSet = F*FTargetTransform.Inverse();
			float RollAngle = AttachmentOffSet.GetRotation().Rotator().Roll;
			if (RollAngle > 0) {
				float Count = 90;
				while (Count < RollAngle) {
					Count = Count + 90;
				}
				RollAngle = Count - RollAngle;
			}
			else if (RollAngle < 0) {
				float Count = -90;
				while (Count > RollAngle) {
					Count = Count - 90;
				}
				RollAngle = Count - RollAngle;
			}
			GEngine->AddOnScreenDebugMessage(AttachmentKey, 15., FColor::Blue, FString::Printf(TEXT("Roll Offset: %f"), 
				RollAngle));
			AOffsetAngle1 = RollAngle;
            return true;
        }
    }
    else {
        std::vector<int> PossibleEndEffectors;
        for (int i = 1; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetAmIEndEffector()) {
                PossibleEndEffectors.push_back(i);
            }
        }
        if (CurrentDockEngagedToGroundStatus[0]) {
            GDock = DOCK_0;
        }
        else if (CurrentDockEngagedToGroundStatus[1]) {
            GDock = DOCK_1;
        }
        
        for (int i = 0; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetConnectedToGround()) {
                GroundModule = smn->GetName();
            }
        }
        ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[2]);
        if (PossibleEndEffectors.size() > 1) {
            std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
            int RandEffector = posRand(Generator);
            cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
            SelectedEndEffector = PossibleEndEffectors[RandEffector];
            ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
            if (LastDockFace == DOCK_0) {
                EEDock = DOCK_1;
            }
            else {
                EEDock = DOCK_0;
            }
        }
        else if (PossibleEndEffectors.size() == 1) {
            SelectedEndEffector = PossibleEndEffectors[0];
            ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
            if (LastDockFace == DOCK_0) {
                EEDock = DOCK_1;
            }
            else {
                EEDock = DOCK_0;
            }
        }
        else {
            SelectedEndEffector = -1;
        }
        FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
        ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
        CurrentX = FullBaseTransform.GetLocation().X;
        GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
        FTransform GroundTransform = Floor->GetTransform();
        GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
        FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
        BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
        FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
        ModuleBaseToGroundTransform = BaseToGround;
        FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                             ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
        ModuleBaseToGroundTransform = InvV*BaseToGround;
        ActualGroundTransform = BaseToGround*LocalBaseTransform;
        
        if (SelectedEndEffector != -1) {
            std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
            std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
            for (int i = 0; i < st.GetVertices().size() * 3; i++)
            {
                posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
            }
            SolutionPos = vector<float>(st.GetVertices().size() * 3);
            PSOWorker = FBBPSOWorker::BBPSOInit(50, 50, st.GetVertices().size() * 3, posB, velB, 6.0,
                                                std::bind(&StackToPlaneBehavior::FitnessObject, this,
                                                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                                std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
                                                SolutionPos, &SolutionFitness);
            HaveInitiatedIK = true;
        }
        else {
            PS = NULL;
        }
    }
    ObjectIKCounter++;
    return false;
}
/**
 * @brief find optimal goal angles for picking up object
 * @return true if process completed, false otherwise
 */
bool StackToPlaneBehavior::FindGoalAnglesForObjectSetDown() {
    if (ObjectIKCounter == 0) {
        HaveInitiatedIK = false;
        HaveCompletedIK = false;
    }
    
    if (HaveInitiatedIK && !HaveCompletedIK) {
        HaveCompletedIK = PSOWorker->IsFinished();
        float IKError = 1000.0;
        if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
            IKError = 1000.0;
        }
        else {
            IKError = PSOWorker->GetCurrentUpperBound();
        }
        GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("IK To Object Set Down Current Error: %f"), IKError));
        GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
        if (HaveCompletedIK) {
            GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
                                             FString::Printf(TEXT("IK Finished")));
            PSOWorker->Stop();
            PSOWorker->Shutdown();
            ObjectIKCounter = 0;
			//Compute offset
			vector<ModuleNode*> Mods(st.GetVertices().size());
			for (int i = 0; i < st.GetVertices().size(); i++) {
				Mods[i] = st.GetVertices()[i];
			}
			ModuleMotorVector mvsGround(SolutionPos[0], SolutionPos[1], SolutionPos[2]);
			FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
			//vector<ModuleNode*> Mods(st.GetVertices().size());
			BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
			FTransform FTargetTransform = TargetTransform*BaseTransform;
			if (EEDock == DOCK_0) {
				FTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FTargetTransform;
			}


			int EE = GetSelectedEndEffector();
			ModuleMotorVector mvsFinal = ModuleMotorVector(SolutionPos[3 * SelectedEndEffector + 0],
				SolutionPos[3 * SelectedEndEffector + 1],
				SolutionPos[3 * SelectedEndEffector + 2]);
			FTransform F =
				SuperbotKinematics::computeTransformToDock(mvsFinal, EEDock)*BestTransformsFound[EE] * BaseTransform;
			
			if (EEDock == DOCK_0) {
				//FullTargetTransform = FTransform(FVector(-ObjectExtents.X / 6.0, 0, 0))*FullTargetTransform;
				F = FTransform(FVector(ObjectExtents.Z / 2.0, 0, 0))*F;
			}
			else {
				//FullTargetTransform = FTransform(FVector(ObjectExtents.X / 6.0, 0, 0))*FullTargetTransform;
				F = FTransform(FVector(-ObjectExtents.Z / 2.0, 0, 0))*F;
			}

			AttachmentOffSetPutDown = F*FTargetTransform.Inverse();
			float RollAngle = AttachmentOffSetPutDown.GetRotation().Rotator().Roll;
			if (RollAngle > 0) {
				float Count = 90;
				while (Count < RollAngle) {
					Count = Count + 90;
				}
				RollAngle = Count - RollAngle;
			}
			else if (RollAngle < 0) {
				float Count = -90;
				while (Count > RollAngle) {
					Count = Count - 90;
				}
				RollAngle = Count - RollAngle;
			}
			AOffsetAngle2 = RollAngle;
			TotalOffsetAngle = AOffsetAngle1 + AOffsetAngle2;
			float RollAngleAdjust = TotalOffsetAngle;
			if (RollAngleAdjust > 0) {
				float Count = 90;
				while (Count < RollAngleAdjust) {
					Count = Count + 90;
				}
				RollAngleAdjust = Count - RollAngleAdjust;
			}
			else if (RollAngleAdjust < 0) {
				float Count = -90;
				while (Count > RollAngleAdjust) {
					Count = Count - 90;
				}
				RollAngleAdjust = Count - RollAngleAdjust;
			}
			TotalOffsetAngle = RollAngleAdjust;
			GEngine->AddOnScreenDebugMessage(AttachmentKey, 15., FColor::Yellow, FString::Printf(TEXT("Total Offset to Fix: %f"), TotalOffsetAngle));
            return true;
        }
    }
    else {
        std::vector<int> PossibleEndEffectors;
        for (int i = 1; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetAmIEndEffector() && smn->GetAmIConnectedToObject()) {
                PossibleEndEffectors.push_back(i);
            }
        }
        if (CurrentDockEngagedToGroundStatus[0]) {
            GDock = DOCK_0;
        }
        else if (CurrentDockEngagedToGroundStatus[1]) {
            GDock = DOCK_1;
        }
        
        for (int i = 0; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetConnectedToGround()) {
                GroundModule = smn->GetName();
            }
        }
        ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[2]);
        if (PossibleEndEffectors.size() > 1) {
            std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
            int RandEffector = posRand(Generator);
            cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
            SelectedEndEffector = PossibleEndEffectors[RandEffector];
            ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
            if (LastDockFace == DOCK_0) {
                EEDock = DOCK_1;
            }
            else {
                EEDock = DOCK_0;
            }
        }
        else if (PossibleEndEffectors.size() == 1) {
            SelectedEndEffector = PossibleEndEffectors[0];
            ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
            if (LastDockFace == DOCK_0) {
                EEDock = DOCK_1;
            }
            else {
                EEDock = DOCK_0;
            }
        }
        else {
            SelectedEndEffector = -1;
        }
        FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
        ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
        CurrentX = FullBaseTransform.GetLocation().X;
        GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
        FTransform GroundTransform = Floor->GetTransform();
        GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
        FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
        BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
        FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
        ModuleBaseToGroundTransform = BaseToGround;
        FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                             ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
        ModuleBaseToGroundTransform = InvV*BaseToGround;
        ActualGroundTransform = BaseToGround*LocalBaseTransform;
        
        if (SelectedEndEffector != -1) {
            std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
            std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
            for (int i = 0; i < st.GetVertices().size() * 3; i++)
            {
                posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
            }
            SolutionPos = vector<float>(st.GetVertices().size() * 3);
            PSOWorker = FBBPSOWorker::BBPSOInit(20, 50, st.GetVertices().size() * 3, posB, velB, 6.0,
                                                std::bind(&StackToPlaneBehavior::FitnessObjectSetDown, this,
                                                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                                std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
                                                SolutionPos, &SolutionFitness);
            HaveInitiatedIK = true;
        }
        else {
            PS = NULL;
        }
    }
    ObjectIKCounter++;
    return false;
}
/**
 * @brief plan path from current angles to goal angles
 * @return true if process completed, false otherwise
 */
bool StackToPlaneBehavior::PlanPathCurrentAnglesToGoalAngles() {
    if (PPCounter == 0) {
        Path.clear();
        HaveInitiatedPP = false;
        HaveCompletedPP = false;
    }
    if (HaveInitiatedPP && !HaveCompletedPP) {
        GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("Planning Path To Goal. Num Nodes: %d"), RRTWorker->GetGraphSize()));
        HaveCompletedPP = RRTWorker->IsFinished();
        if (HaveCompletedPP) {
            GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Green,
                                             FString::Printf(TEXT("Done Planning.")));
            Path.push_back(SolutionPos);
            RRTWorker->Stop();
            RRTWorker->Shutdown();
            PPCounter = 0;
            return true;
        }
    } else {
        HaveInitiatedPP = true;
        std::vector<std::pair<float, float> > run(st.GetVertices().size() * 3);
        std::vector<std::pair<float, float> > vel(st.GetVertices().size() * 3);
        std::vector<float> goal(st.GetVertices().size() * 3);
        std::vector<float> start(st.GetVertices().size() * 3);
        for (int i = 0; i < vel.size(); i++) {
            run[i] = std::pair<float, float>(-90, 90);
            vel[i] = std::pair<float, float>(-90, 90);
            goal[i] = SolutionPos[i];
        }
        for (int i = 0; i < st.GetVertices().size(); i++) {
            start[3 * i + 0] = st.GetVertices()[i]->GetJointAngles()[0];
            start[3 * i + 1] = st.GetVertices()[i]->GetJointAngles()[1];
            start[3 * i + 2] = st.GetVertices()[i]->GetJointAngles()[2];
        }
        CurrentPathElement = 0;
        float FitVal;
        vector<ModuleNode*> Mods(st.GetVertices().size());
        for (int i = 0; i < st.GetVertices().size(); i++) {
            Mods[i] = st.GetVertices()[i];
        }
        BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
        RRTWorker = FRRTWorker::RRTInit(5000, st.GetVertices().size() * 3, 100, run, 20.0,
                                        std::bind(&StackToPlaneBehavior::StateValid, this, std::placeholders::_1),
                                        std::bind(&StackToPlaneBehavior::Distance, this, std::placeholders::_1,
                                                  std::placeholders::_2),
                                        start, goal, Path, &FitVal);
    }
    PPCounter++;
    return false;
}
/**
 * @brief execute a wait for a certain number of time steps
 * @param Counter number of time steps to wait
 * @return true if process completed false otherwise
 */
bool StackToPlaneBehavior::ExecuteWait(int Counter) {
    if (EWCounter == 0) {
        WaitCounter = Counter;
    }
    if (WaitCounter <= 0) {
        GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
                                         FString::Printf(TEXT("Done Waiting")));
        EWCounter = 0;
        return true;
    }
    else {
        GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red,
                                         FString::Printf(TEXT("Waiting")));
        WaitCounter--;
    }
    EWCounter++;
    return false;
}
/**
 * @brief execute planned path
 * @return true if process completed, false otherwise
 */
bool StackToPlaneBehavior::ExecutePath() {
    if (PECounter == 0) {
        CurrentPathElement = 0;
        WaitCounter = 0;
        HaveSetJointAngles = false;
    }
    if (!HaveSetJointAngles && WaitCounter <=0) {
        SetJointAnglesDistributed(Path[CurrentPathElement]);
        WaitCounter = 20;
        GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Blue,
                                         FString::Printf(TEXT("Remaining Path Size: %d"), Path.size() - CurrentPathElement));
		CurrentPathElement++;
		
        if (CurrentPathElement >= Path.size()) {
            GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Green,
                                             FString::Printf(TEXT("Execution Finished")));
            HaveSetJointAngles = true;
            PECounter = 0;
            WaitCounter = 20;
            return true;
        }
    }
    else {
        WaitCounter--;
    }
    PECounter++;
    return false;
}
/**
 * @brief compute distance between point1 and point2
 * @param point1 point number 1
 * @param point2 point number 2
 * @return euclidean distance between point1 and point2
 */
float StackToPlaneBehavior::Distance(std::vector<float> point1, std::vector<float> point2) {
    float distance = 0.0;
    for (int i = 0; i<point1.size(); i++) {
        distance += (point1[i] - point2[i])*(point1[i] - point2[i]);
    }
    return sqrtf(distance);
}
/**
 * @brief fitness for PASO
 * @param P PSO particle
 * @param st start vector
 * @param tar target vector
 */
float StackToPlaneBehavior::FitnessPSO(PSOParticle P, std::vector<float> start, std::vector<float> target) {
    float DistanceError = Distance(P.getPosition(), target);
    int CollisionVal = CollisionFunction(P.getPosition());
    return DistanceError + 1/(1 + GetDistanceToGroundScore(P.getPosition())) + 1000 * CollisionVal;
}
/**
 * @brief get distance to ground score
 * @param p point
 * @return score of distance to ground
 */
float StackToPlaneBehavior::GetDistanceToGroundScore(std::vector<float> point) {
    vector<ModuleNode*> Mods(st.GetVertices().size());
    ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                st.GetVertices()[GroundModule]->GetJointAngles()[2]);
    FTransform ActualBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
    for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);
    
    vector<ModuleMotorVector> mvsFinals;
    ModuleMotorVector groundAngles;
    vector<ModuleDockFace> mvsDocks;
    groundAngles = ModuleMotorVector(point[0], point[1], point[2]);
    //FTransform LocalBaseTransform = SuperbotKinematics::computeTransformFromDock(groundAngles, GDock);
    FTransform BaseTransform = FTransform(FVector(0, 0, 0));
    for (int i = 0; i<st.GetVertices().size(); i++) {
        if (st.GetVertices()[i]->GetAmIEndEffector()) {
            mvsFinals.push_back(ModuleMotorVector(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]));
            ModuleDockFace D = (ModuleDockFace)st.GetVertices()[i]->GetDockFacePath()[st.GetVertices()[i]->GetDockFacePath().size() - 1].first;
            if (D == DOCK_0) {
                mvsDocks.push_back(DOCK_1);
            }
            else {
                mvsDocks.push_back(DOCK_0);
            }
        }
    }
    
    
    FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
    ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
    FTransform GroundTransform = Floor->GetTransform();
    GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
    FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
    BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
    FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(groundAngles, GDock);
    FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                         ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
    FTransform AGroundTransform = BaseToGround*LocalBaseTransform;
    
    
    physx::PxTransform transGround;
    physx::PxBoxGeometry groundGeometry;
    if (GDock == DOCK_0) {
        BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
    }
    else {
        BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
    }
    FTransform GroundFix = FTransform(FVector(-225, 0, 0));
    if (GDock == DOCK_0) {
        //FTransform GroundFix = FTransform(FVector(-225, 0, 0));
    }
    physx::PxTransform transBase = U2PTransform(GroundFix*AGroundTransform);
    groundGeometry = physx::PxBoxGeometry(200, 1000, 1000);
    bool isObjectConnected = false;
    int objectTs = -1;
    for (int i = 0; i < st.GetVertices().size(); i++) {
        if (st.GetVertices()[i]->GetAmIConnectedToObject()) {
            isObjectConnected = true;
            objectTs = i;
        }
    }
    float GroundScore = 0.0;
    for (int i = 0; i < Ts.size(); i++) {
        FTransform TTrans = Ts[i] * LocalBaseTransform;
        GroundScore += (TTrans.GetLocation() - AGroundTransform.GetLocation()).Size();
    }
    return GroundScore;
}






///Inverse kinematics functionality
/**
 * @brief get best transforms found by IK process
 * @return best transforms
 */
std::vector<FTransform> StackToPlaneBehavior::GetBestTransforms() {
    return BestTransformsFound;
}
/**
 * @brief get best (solution) position
 * @return best (solution) position
 */
std::vector<float> StackToPlaneBehavior::GetSolutionPos() {
    return SolutionPos;
}
/**
 * @brief get the transforms of modules for joint angles
 * @param Mods modules
 * @param JAngles joint angles
 * @return transform of modules in tree
 */
vector<FTransform> StackToPlaneBehavior::GetTransformsOfModulesForJointAngles(std::vector<ModuleNode*> Mods,
                                                                           std::vector<float> JAngles) {
    vector<FTransform> Transforms(Mods.size());
    vector<ModuleMotorVector> MVS(Mods.size());
    std::queue<ModuleNode*> SearchQueue;
    SearchQueue.push(Mods[0]);
    vector<bool> Discovered(Mods.size());
    for (int i = 0; i<Mods.size(); i++) {
        Discovered[i] = false;
        Transforms[i] = FTransform(FVector(0, 0, 0));
    }
    for (int i = 0; i<Mods.size(); i++) { MVS[i] = ModuleMotorVector(JAngles[3 * i + 0], JAngles[3 * i + 1], JAngles[3 * i + 2]); }
    
    int CurrentDock = 0;
    bool AmIEngagedToGroundFront = CurrentDockEngagedToGroundStatus[DOCK_0];
    bool AmIEngagedToGroundBack = CurrentDockEngagedToGroundStatus[DOCK_1];
    if (AmIEngagedToGroundFront) {
        Transforms[0] = SuperbotKinematics::computeTransformFromDock(MVS[0], DOCK_0);
    }
    else if (AmIEngagedToGroundBack) {
        Transforms[0] = SuperbotKinematics::computeTransformFromDock(MVS[0], DOCK_1);
    }
    for (int i = 1; i<st.GetVertices().size(); i++) {
        FTransform CurrentTransform = Transforms[0];
        std::vector<int> P = GetPathToRootFromNode(st.GetVertices()[i]);
        std::vector<std::pair<ModuleDockFace, int> > DP = st.GetVertices()[i]->GetDockFacePath();
        for (int j = 1; j<P.size(); j++) {
            ModuleDockFace d1 = DP[2 * j - 2].first;
            ModuleDockFace d2 = DP[2 * j - 1].first;
            FTransform trans1 = SuperbotKinematics::computeTransformToDock(MVS[P[j - 1]], d1);
            FTransform trans2 = SuperbotKinematics::computeTransformFromDock(MVS[P[j]], d2);
            CurrentTransform = trans2*GetCorrectiveDockingTransform(d1, d2)*trans1*CurrentTransform;
            Transforms[i] = CurrentTransform;
        }
    }
    return Transforms;
}
/**
 * @brief fitness function for IK
 * @param P particle
 * @param tar target
 * @return fitness value
 */
float StackToPlaneBehavior::Fitness(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
    ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
    FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
    vector<ModuleNode*> Mods(st.GetVertices().size());
    for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
    ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3 * SelectedEndEffector + 0],
                                                   P.GetPosition()[3 * SelectedEndEffector + 1],
                                                   P.GetPosition()[3 * SelectedEndEffector + 2]);




    FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
    Ts[SelectedEndEffector] * BaseTransform;
    
	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();

    FTransform FullTargetTransform;
	if (M == SETTING_DOWN_OBJECT) {
		FullTargetTransform = ModuleBaseToGroundWithWalkTransform*BaseTransform;
	}
	else {
		FullTargetTransform = ModuleBaseToGroundWithObjectWalkTransform*BaseTransform;
	}
	FTransform	TargetNoWalk = ModuleBaseToGroundTransform*BaseTransform;

	if (GDock == DOCK_1 || GDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI))*FullTargetTransform;
		TargetNoWalk = FTransform(FQuat(FVector(0, 1, 0), M_PI))*TargetNoWalk;
	}
    if (GDock == DOCK_1 || GDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI))*FullTargetTransform;
		TargetNoWalk = FTransform(FQuat(FVector(0, 1, 0), -M_PI))*TargetNoWalk;
    }
    if (EEDock == DOCK_0) {
        FullTargetTransform = FTransform(FVector(-10, 0, 0))*FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FullTargetTransform;
		TargetNoWalk = FTransform(FVector(-10, 0, 0))*FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*TargetNoWalk;
    }
    else {
        FullTargetTransform = FTransform(FVector(10, 0, 0))*FullTargetTransform;
		TargetNoWalk = FTransform(FVector(10, 0, 0))*TargetNoWalk;
	}
	float ZDiff = (TargetNoWalk.GetLocation().X - FullTargetTransform.GetLocation().X);
	//FTransform FT = FullTargetTransform;
	//FullTargetTransform = FTransform(FVector(ZDiff, 0,0))*FullTargetTransform;
	//FullTargetTransform.SetLocation(FVector(TargetNoWalk.GetLocation().X, FT.GetLocation().Y, FT.GetLocation().Z));
	     FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
    FVector OrientVec = FVector(/*DiffRot.Roll*/0, DiffRot.Pitch, DiffRot.Yaw);
    FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
    FVector DiffVec2D(0, DiffPos.Y, DiffPos.Z);
    return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
    100 * IsInCollisionWithGroundDetailed(P.GetPosition());
    
}
FTransform StackToPlaneBehavior::GetWalkingTarget() {
	return WalkingTarget;
}
/**
 * @brief fitness function for IK
 * @param P particle
 * @param tar target
 * @return fitness value
 */
float StackToPlaneBehavior::FitnessObject(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
    ModuleMotorVector mvsGround(P.GetPosition()[0],P.GetPosition()[1],P.GetPosition()[2]);
    FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
    vector<ModuleNode*> Mods(st.GetVertices().size());
    for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
    ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3 * SelectedEndEffector + 0],
                                                   P.GetPosition()[3 * SelectedEndEffector + 1],
                                                   P.GetPosition()[3 * SelectedEndEffector + 2]);
    FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
    Ts[SelectedEndEffector] * BaseTransform;
    
    FTransform FullTargetTransform;
    FullTargetTransform = ComputeObjectPose()*BaseTransform;
    if (EEDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FullTargetTransform;
    }
    FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
    FVector OrientVec = FVector(DiffRot.Roll*0, DiffRot.Pitch, DiffRot.Yaw);
    FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
    FVector DiffVec2D(0, DiffPos.Y, DiffPos.Z);
    return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
    100 * IsInCollisionWithGroundDetailed(P.GetPosition()) + 1 / (1 + GetDistanceToGroundScore(P.GetPosition()));
    
}
/**
 * @brief fitness function for IK to object set down
 * @param P particle
 * @param tar target
 * @return fitness value
 */
float StackToPlaneBehavior::FitnessObjectSetDown(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
    ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
    FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
    vector<ModuleNode*> Mods(st.GetVertices().size());
    for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
    ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3 * SelectedEndEffector + 0],
                                                   P.GetPosition()[3 * SelectedEndEffector + 1],
                                                   P.GetPosition()[3 * SelectedEndEffector + 2]);
    FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
    Ts[SelectedEndEffector] * BaseTransform;
    
    FTransform FullTargetTransform;
    FullTargetTransform = ModuleBaseToGroundTransform*BaseTransform;
    if (GDock == DOCK_1 || GDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI))*FullTargetTransform;
    }
    FullTargetTransform = TargetTransform*BaseTransform;
    if (GDock == DOCK_1 || GDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI))*FullTargetTransform;
    }
    if (EEDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FullTargetTransform;
    }
    
    if (EEDock == DOCK_0) {
        //FullTargetTransform = FTransform(FVector(-ObjectExtents.X / 6.0, 0, 0))*FullTargetTransform;
        FinalFKActorTrans = FTransform(FVector(ObjectExtents.Z/2.0,0,0))*FinalFKActorTrans;
    }
    else {
        //FullTargetTransform = FTransform(FVector(ObjectExtents.X / 6.0, 0, 0))*FullTargetTransform;
        FinalFKActorTrans = FTransform(FVector(-ObjectExtents.Z/2.0, 0, 0))*FinalFKActorTrans;
    }
	FullTargetTransform = FTransform(FQuat(FVector(1, 0, 0),  (M_PI / 180.0)*AOffsetAngle1))*FullTargetTransform;
    FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
    FVector OrientVec = FVector(DiffRot.Roll*0, DiffRot.Pitch, DiffRot.Yaw);
    FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
    FVector DiffVec2D(0, DiffPos.Y, DiffPos.Z);
    return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
    100 * IsInCollisionWithGroundDetailed(P.GetPosition()) + 1 / (1 + GetDistanceToGroundScore(P.GetPosition()));
    
}
/**
 * @brief get target transform
 * @return target transform
 */
FTransform StackToPlaneBehavior::GetTargetTransform() {
    return this->TargetTransform;
}




///Kinematic discovery
/**
 * @brief set joints distributed
 * @param JAngles joint angles
 */
void StackToPlaneBehavior::SetJointAnglesDistributed(std::vector<float> JAngles) {
    TreeMessage tcm("SetJoints", st.GetVertices().size(), st.GetVertices().size());
    for (int i = 0; i<st.GetVertices().size(); i++) {
        double a0 = JAngles[3 * i + 0];
        double a1 = JAngles[3 * i + 1];
        double a2 = JAngles[3 * i + 2];
        if (i == 0) {
            AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_0, a0));
            AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_1, a1));
            AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_2, a2));
        }
        else {
            ModuleNode* cNode = st.GetVertices()[i];
            tcm.N = cNode;
            vector<float> cAngles(3);
            cAngles[0] = a0;
            cAngles[1] = a1;
            cAngles[2] = a2;
            tcm.CommandAngles = cAngles;
            if (cNode->GetDockFacePath().size() > 2) {
                tcm.Command = "SetJointsI";
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
            }
            else {
                tcm.Command = "SetJoints";
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
            }
        }
    }
}
/**
 * @brief initialize kinematic tree
 * @param aEE am i end effector?
 * @param cTG connected to ground?
 */
void StackToPlaneBehavior::InitializeKinematicTree() {
    ModuleNode *rootNode = new ModuleNode(CurrentAngles, 0, FTransform(FVector(0, 0, 0)));
    rootNode->SetDiscoveredLevel(0);
    rootNode->SetDiscoveredDock(-1);
    rootNode->SetDiscoveringNode(NULL);
    rootNode->SetAmIEndEffector(false);
    rootNode->SetConnectedToGround(this->AmIEngagedToGround);
    if (CurrentDockEngagedToGroundStatus[DOCK_0]) {
        rootNode->SetDockFaceConnectedToGround(DOCK_0);
    }
    else if (CurrentDockEngagedToGroundStatus[DOCK_1]) {
        rootNode->SetDockFaceConnectedToGround(DOCK_1);
    }
    ModuleMotorVector RAngles(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
    rootNode->SetTransform(SuperbotKinematics::computeTransformFromDock(RAngles, rootNode->GetDockFaceConnectedToGround()));
    ModNodes[rootNode->GetName()] = rootNode;
    st.InitializeTree(rootNode);
    st.AddNodeToBFSQueue(rootNode);
    HasBeenInitialized = true;
    this->CanSendMessage = true;
}
/**
 * @brief discover kinematic structure
 */
void StackToPlaneBehavior::DiscoverKinematicStructure() {
    ModuleNode *cNode = st.GetQueueFront();
    TreeMessage tm = TreeMessage("StateProbe", st.GetVertices().size(), st.GetVertices().size());
    if (CurrentModel.GetCurrentState().GetIDNumber() == 0 && ShouldPrintDiscovery) {
        cout << "Module Num: 0" << endl;
        cout << cNode->GetName() << endl;
        cout << cNode->GetCurrentDock();
        cout << endl << endl;
    }
    if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() < 6) {
        tm.N = cNode;
        if (cNode->GetDockFacePath().size() > 0) {
            tm.Command = "StateProbeI";
            tm.CurrentPathElement = 0;
            tm.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)cNode->GetDockFacePath()[tm.CurrentPathElement].first, 0));
            if (cNode->GetDiscoveredLevel() < 15) {
                CanSendMessage = false;
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>
                                     (GetTreeActionForDock(cNode->GetDockFacePath()[tm.CurrentPathElement].first), tm));
            }
            else {
                if (cNode) cNode->IncrementCurrentDock();
            }
        }
        else {
            if (CurrentDockEngagedStatus[cNode->GetCurrentDock()]) {
                this->CanSendMessage = false;
                cNode->SetDiscoveredDock(cNode->GetCurrentDock());
                tm.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)cNode->GetCurrentDock(), 0));
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>
                                     (GetTreeActionForDock((ModuleDockFace)cNode->GetCurrentDock()), tm));
            }
            else {
                CanSendMessage = true;
                if (cNode) cNode->IncrementCurrentDock();
            }
        }
    }
    
    if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() >= 6) {
        this->CanSendMessage = true;
        FVector p = cNode->GetTransform().GetLocation();
        st.AddCenterOfMassTotal(p);
        st.SetCenterOfMass(st.GetCenterOfMassTotal() / st.GetVertices().size());
        st.PopBFSQueue();
    }
}
/**
 * @brief process message
 * @param aEE am i end effector?
 * @param cTG connected to ground?
 * @param messages messages vector
 */
void StackToPlaneBehavior::ProcessMessages(vector<TreeMessage> messages) {
    for (int i = 0; i<messages.size(); i++) {
        TreeMessage mes = messages[i];
        if (mes.Command.compare("ReConnectObject") == 0) {
            AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_STACKABLE_OBJECT_TO_GROUND, true));
            cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
            if (CurrentDockEngagedStatus[DOCK_1]) {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_STACKABLE, false));
            }
            else {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_STACKABLE, false));
            }
        }
        else if (mes.Command.compare("ReConnectObjectI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "ReConnectObjectI";
            }
            else {
                mes.Command = "ReConnectObject";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
            }
        }
        else if (mes.Command.compare("ConnectObjectS") == 0) {
            cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
            if (CurrentDockEngagedStatus[DOCK_1]) {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_STACKABLE, true));
            }
            else {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_STACKABLE, true));
            }
        }
        else if (mes.Command.compare("ConnectObjectSI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "ConnectObjectSI";
            }
            else {
                mes.Command = "ConnectObjectS";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
            }
        }
        else if (mes.Command.compare("DisconnectObject") == 0) {
            cout << "Will Disconnect Effector at Module: " << mes.N->GetName() << endl;
            if (CurrentDockEngagedStatus[DOCK_1]) {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_STACKABLE, false));
            }
            else {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_STACKABLE, false));
            }
        }
        else if (mes.Command.compare("DisconnectObjectI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "DisconnectObjectI";
            }
            else {
                mes.Command = "DisconnectObject";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
            }
        }
        else if (mes.Command.compare("ConnectObject") == 0) {
            AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_STACKABLE_OBJECT_TO_GROUND, false));
            cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
            if (CurrentDockEngagedStatus[DOCK_1]) {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_STACKABLE, true));
            }
            else {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_STACKABLE, true));
            }
        }
        else if (mes.Command.compare("ConnectObjectI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "ConnectObjectI";
            }
            else {
                mes.Command = "ConnectObject";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
            }
        }
        else if (mes.Command.compare("ConnectEffector") == 0) {
            cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
            if (CurrentDockEngagedStatus[DOCK_1]) {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_GROUND, true));
            }
            else {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_GROUND, true));
            }
			AOffsetAngle1 = mes.OffsetAngle;
			M = (STPProgramMode)mes.ProgramMode;
			CurrentStackableOb = mes.CurrentOb;
			WalkCounter = 0;
			PickCounter = 0;
			SetCounter = 0;
            
        }
        else if (mes.Command.compare("ConnectEffectorI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "ConnectEffectorI";
            }
            else {
                mes.Command = "ConnectEffector";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
            }
        }
        else if (mes.Command.compare("StateProbe") == 0) {
            mes.MV.push_back(ModuleMotorVector(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]));
            mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
            mes.CurrentPathElement = mes.DockFacePath.size() - 1;
            mes.DockConnectedStatuses = CurrentDockEngagedStatus;
            mes.Command = "ReturnState";
            mes.AmIEndEffector = this->AmIEndEffector;
            mes.ConnectedToGround = this->AmIEngagedToGround;
            mes.ConnectedToObject = this->AmIConnectedToObject;
            if (mes.N->GetDockFacePath().size() > 0) { mes.Command = "ReturnStateI"; }
            AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()), mes));
        }
        else if (mes.Command.compare("StateProbeI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size()) {
                mes.Command = "StateProbeI";
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
            }
            else {
                mes.Command = "StateProbe";
                d = (ModuleDockFace)mes.N->GetCurrentDock();
            }
            
            if (CurrentDockEngagedStatus[d] && d != mes.GetReceivingDock().GetDockFace()) {
                mes.MV.push_back(ModuleMotorVector(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]));
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)d, 0));
                if (mes.Command.compare("StateProbe") == 0) {
                    mes.N->SetDiscoveredDock(mes.N->GetCurrentDock());
                }
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
            }
            else {
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
                mes.CurrentPathElement = mes.DockFacePath.size() - 1;
                if (mes.CurrentPathElement > 1) {
                    mes.Command = "ReturnStateFI";
                }
                else {
                    mes.Command = "ReturnStateF";
                }
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()), mes));
            }
        }
        else if (mes.Command.compare("ReturnStateI") == 0) {
            mes.CurrentPathElement -= 2;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "ReturnState";
            }
            else {
                mes.Command = "ReturnStateI";
            }
            AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(mes.N->GetDockFacePath()[mes.CurrentPathElement].first), mes));
        }
        else if (mes.Command.compare("ReturnState") == 0) {
            this->CanSendMessage = true;
            std::vector<float> angles = std::vector<float>(3);
            angles[0] = CurrentAngles[0]; angles[1] = CurrentAngles[1]; angles[2] = CurrentAngles[2];
            FTransform CurrentTransform = FTransform(FVector(0, 0, 0));
            ModuleMotorVector mv = ModuleMotorVector(angles[0], angles[1], angles[2]);
            int dockCounter = 0;
            CurrentTransform = st.GetVertices()[0]->GetTransform();
            for (int j = 0; j<mes.MV.size(); j++) {
                ModuleDockFace d1 = mes.DockFacePath[dockCounter++].first;
                ModuleDockFace d2 = mes.DockFacePath[dockCounter++].first;
                FTransform trans1 = SuperbotKinematics::computeTransformToDock(mv, d1);
                angles[0] = mes.MV[j].Motor0Angle; angles[1] = mes.MV[j].Motor1Angle; angles[2] = mes.MV[j].Motor2Angle;
                mv = ModuleMotorVector(angles[0], angles[1], angles[2]);
                FTransform trans2 = SuperbotKinematics::computeTransformFromDock(mv, d2);
                CurrentTransform = trans2*GetCorrectiveDockingTransform(d1, d2)*trans1*CurrentTransform;
                if (!CurrentTransform.IsValid()) {
                    cout << "Problem" << endl;
                }
            }
            mes.N->IncrementCurrentDock();
            ModuleNode *n = new ModuleNode(angles, mes.GetNeighborNumID(), CurrentTransform);
            n->SetDiscoveredLevel(mes.DockFacePath.size() / 2);
            n->SetDockFacePath(mes.DockFacePath);
            n->SetDiscoveredDock(mes.N->GetDiscoveredDock());
            n->SetDiscoveringNode(mes.N);
            n->SetDockEngagedStatuses(mes.DockConnectedStatuses);
            n->SetJointAngles(angles);
            n->SetAmIEndEffector(mes.AmIEndEffector);
            n->SetConnectedToGround(mes.ConnectedToGround);
            n->SetAmIConnectedToObject(mes.ConnectedToObject);
            st.AddEdge(mes.N->GetName(), n->GetName(), mes.DockFacePath[mes.DockFacePath.size() - 2].first, mes.DockFacePath[mes.DockFacePath.size() - 1].first);
            st.AddNodeToBFSQueue(n);
            st.AddVertex(n);
            ModNodes[mes.GetNeighborNumID()] = n;
        }
        else if (mes.Command.compare("ReturnStateF") == 0) {
            this->CanSendMessage = true;
            mes.N->IncrementCurrentDock();
        }
        else if (mes.Command.compare("ReturnStateFI") == 0) {
            mes.CurrentPathElement -= 2;
            ModuleDockFace d = (ModuleDockFace)mes.DockFacePath[mes.CurrentPathElement].first;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "ReturnStateF";
            }
            else {
                mes.Command = "ReturnStateFI";
            }
            AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
        }
        else if (mes.Command.compare("Reset") == 0) {
            this->ShouldSetTreeDirty = true;
            //cout<<"Received Reset"<<endl;
            TreeMessage tm = TreeMessage("Reset", st.GetVertices().size(), 0);
            for (int j = 0; j<6; j++) {
                if (CurrentDockEngagedStatus[j] && j != mes.GetReceivingDock().GetDockFace()) {
                    AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)j), tm));
                }
            }
        }
        else if (mes.Command.compare("SetJoints") == 0) {
            AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_0, mes.CommandAngles[0]));
            AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_1, mes.CommandAngles[1]));
            AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_2, mes.CommandAngles[2]));
        }
        else if (mes.Command.compare("SetJointsI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
			if (mes.N) {
				if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
					mes.Command = "SetJointsI";
				}
				else {
					mes.Command = "SetJoints";
				}
				if (mes.N->GetDockFacePath().size() > 0) {
					d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
					AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
				}
			}
        }
    }
}
/**
 * @brief update the current joint angles
 */
void StackToPlaneBehavior::UpdateCurrentAngles() {
    float motor0Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor0Angle;
    float motor1Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor1Angle;
    float motor2Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor2Angle;
    if (this->ProgramCounter == 0) {
        CurrentAngles[0] = motor0Angle;
        CurrentAngles[1] = motor1Angle;
        CurrentAngles[2] = motor2Angle;
        CAngleDiffs[0] = 0;
        CAngleDiffs[1] = 0;
        CAngleDiffs[2] = 0;
    }
    else {
        CAngleDiffs[0] += motor0Angle - CurrentAngles[0];
        CAngleDiffs[1] += motor1Angle - CurrentAngles[1];
        CAngleDiffs[2] += motor2Angle - CurrentAngles[2];
        CurrentAngles[0] = motor0Angle;
        CurrentAngles[1] = motor1Angle;
        CurrentAngles[2] = motor2Angle;
    }
}
/**
 * @brief update dock engaged status
 */
void StackToPlaneBehavior::UpdateDockEngagedStatus() {
    bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_0];
    bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_1];
    bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_2];
    bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_3];
    bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_4];
    bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_5];
    
    if (this->ProgramCounter == 0) {
        CDockDiffs[DOCK_0] = 0;
        CDockDiffs[DOCK_1] = 0;
        CDockDiffs[DOCK_2] = 0;
        CDockDiffs[DOCK_3] = 0;
        CDockDiffs[DOCK_4] = 0;
        CDockDiffs[DOCK_5] = 0;
        this->CurrentDockEngagedStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedStatus[DOCK_5] = currentDock5;
    }
    else {
        CDockDiffs[DOCK_0] = CurrentDockEngagedStatus[DOCK_0] - currentDock0;
        CDockDiffs[DOCK_1] = CurrentDockEngagedStatus[DOCK_1] - currentDock1;
        CDockDiffs[DOCK_2] = CurrentDockEngagedStatus[DOCK_2] - currentDock2;
        CDockDiffs[DOCK_3] = CurrentDockEngagedStatus[DOCK_3] - currentDock3;
        CDockDiffs[DOCK_4] = CurrentDockEngagedStatus[DOCK_4] - currentDock4;
        CDockDiffs[DOCK_5] = CurrentDockEngagedStatus[DOCK_5] - currentDock5;
        this->CurrentDockEngagedStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedStatus[DOCK_5] = currentDock5;
    }
}
/**
 * @brief update dock engaged status
 */
void StackToPlaneBehavior::UpdateDockEngagedToGroundStatus() {
    bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_0];
    bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_1];
    bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_2];
    bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_3];
    bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_4];
    bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_5];
    if (this->ProgramCounter == 0) {
        CDockToGroundDiffs[DOCK_0] = 0;
        CDockToGroundDiffs[DOCK_1] = 0;
        CDockToGroundDiffs[DOCK_2] = 0;
        CDockToGroundDiffs[DOCK_3] = 0;
        CDockToGroundDiffs[DOCK_4] = 0;
        CDockToGroundDiffs[DOCK_5] = 0;
        this->CurrentDockEngagedToGroundStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedToGroundStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedToGroundStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedToGroundStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedToGroundStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedToGroundStatus[DOCK_5] = currentDock5;
    }
    else {
        CDockToGroundDiffs[DOCK_0] = CurrentDockEngagedToGroundStatus[DOCK_0] - currentDock0;
        CDockToGroundDiffs[DOCK_1] = CurrentDockEngagedToGroundStatus[DOCK_1] - currentDock1;
        CDockToGroundDiffs[DOCK_2] = CurrentDockEngagedToGroundStatus[DOCK_2] - currentDock2;
        CDockToGroundDiffs[DOCK_3] = CurrentDockEngagedToGroundStatus[DOCK_3] - currentDock3;
        CDockToGroundDiffs[DOCK_4] = CurrentDockEngagedToGroundStatus[DOCK_4] - currentDock4;
        CDockToGroundDiffs[DOCK_5] = CurrentDockEngagedToGroundStatus[DOCK_5] - currentDock5;
        this->CurrentDockEngagedToGroundStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedToGroundStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedToGroundStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedToGroundStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedToGroundStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedToGroundStatus[DOCK_5] = currentDock5;
    }
}
/**
 * @brief update dock engaged to object status
 */
void StackToPlaneBehavior::UpdateDockEngagedToObjectStatus() {
    bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_0];
    bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_1];
    bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_2];
    bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_3];
    bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_4];
    bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_5];
    if (this->ProgramCounter == 0) {
        CDockToObjectDiffs[DOCK_0] = 0;
        CDockToObjectDiffs[DOCK_1] = 0;
        CDockToObjectDiffs[DOCK_2] = 0;
        CDockToObjectDiffs[DOCK_3] = 0;
        CDockToObjectDiffs[DOCK_4] = 0;
        CDockToObjectDiffs[DOCK_5] = 0;
        this->CurrentDockEngagedToObjectStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedToObjectStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedToObjectStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedToObjectStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedToObjectStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedToObjectStatus[DOCK_5] = currentDock5;
    }
    else {
        CDockToObjectDiffs[DOCK_0] = CurrentDockEngagedToObjectStatus[DOCK_0] - currentDock0;
        CDockToObjectDiffs[DOCK_1] = CurrentDockEngagedToObjectStatus[DOCK_1] - currentDock1;
        CDockToObjectDiffs[DOCK_2] = CurrentDockEngagedToObjectStatus[DOCK_2] - currentDock2;
        CDockToObjectDiffs[DOCK_3] = CurrentDockEngagedToObjectStatus[DOCK_3] - currentDock3;
        CDockToObjectDiffs[DOCK_4] = CurrentDockEngagedToObjectStatus[DOCK_4] - currentDock4;
        CDockToObjectDiffs[DOCK_5] = CurrentDockEngagedToObjectStatus[DOCK_5] - currentDock5;
        this->CurrentDockEngagedToObjectStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedToObjectStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedToObjectStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedToObjectStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedToObjectStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedToObjectStatus[DOCK_5] = currentDock5;
    }
}
/**
 * @brief update dock diffs
 */
void StackToPlaneBehavior::UpdateDockDiffs() {
    int diffTotalDocks = 0;
    for (int i = 0; i<6; i++) {
        diffTotalDocks += abs(CDockDiffs[i]);
    }
    int diffTotalDocksToGround = 0;
    for (int i = 0; i<6; i++) {
        diffTotalDocksToGround += abs(CDockToGroundDiffs[i]);
    }
    int diffTotalDocksToObject = 0;
    for (int i=0; i<6; i++) {
        diffTotalDocksToObject += abs(CDockToObjectDiffs[i]);
    }
    
    if (diffTotalDocksToGround > 0) {
        cout<<"Change of Base: "<<this->CurrentModel.GetCurrentState().GetIDNumber()<<endl;
        GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Blue, FString::Printf(TEXT("Base Changed: %d"),
                                                                                       this->CurrentModel.GetCurrentState().GetIDNumber()));
    }
    if (diffTotalDocksToObject > 0) {
        //GEngine->AddOnScreenDebugMessage(ObjectChangeKey, 5.0, FColor::Green, FString("Object picked up"));
    }
    
    if ((fabs(CAngleDiffs[0]) > 1.0 || fabs(CAngleDiffs[1]) > 1.0 || fabs(CAngleDiffs[2]) > 1.0 || abs(diffTotalDocks) > 0) ||
        abs(diffTotalDocksToGround) > 0 || abs(diffTotalDocksToObject) > 0) {
        CAngleDiffs[0] = 0.0;
        CAngleDiffs[1] = 0.0;
        CAngleDiffs[2] = 0.0;
        CDockDiffs[0] = 0;
        CDockDiffs[1] = 0;
        CDockDiffs[2] = 0;
        CDockDiffs[3] = 0;
        CDockDiffs[4] = 0;
        CDockDiffs[5] = 0;
        CDockToGroundDiffs[0] = 0;
        CDockToGroundDiffs[1] = 0;
        CDockToGroundDiffs[2] = 0;
        CDockToGroundDiffs[3] = 0;
        CDockToGroundDiffs[4] = 0;
        CDockToGroundDiffs[5] = 0;
        CDockToObjectDiffs[0] = 0;
        CDockToObjectDiffs[1] = 0;
        CDockToObjectDiffs[2] = 0;
        CDockToObjectDiffs[3] = 0;
        CDockToObjectDiffs[4] = 0;
        CDockToObjectDiffs[5] = 0;
        if (diffTotalDocksToGround > 0 || diffTotalDocksToObject > 0) {
            this->ProgramCounter = 1;
        }
        TreeMessage tm = TreeMessage("Reset", st.GetVertices().size(), 0);
        for (int j = 0; j<6; j++) {
            if (CurrentDockEngagedStatus[j]) {
                AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)j), tm));
            }
        }
        this->ShouldSetTreeDirty = true;
        
    }
}
/**
 * @brief update engaged to ground
 */
void StackToPlaneBehavior::UpdateEngagedToGround() {
    AmIEngagedToGround = (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1]);
    if (AmIEngagedToGround) {
        if (CurrentDockEngagedToGroundStatus[0]) {
            GDock = DOCK_0;
        }
        else if (CurrentDockEngagedToGroundStatus[1]) {
            GDock = DOCK_1;
        }
        
        for (int i = 0; i < st.GetVertices().size(); i++) {
            ModuleNode *smn = st.GetVertices()[i];
            if (smn->GetConnectedToGround()) {
                GroundModule = smn->GetName();
            }
        }
        /*if (SModule) {
         ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
         st.GetVertices()[GroundModule]->GetJointAngles()[1],
         st.GetVertices()[GroundModule]->GetJointAngles()[2]);
         FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
         ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
         CurrentX = FullBaseTransform.GetLocation().X;
         GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
         }*/
    }
}
/**
 * @brief update whether or not I am end effector
 */
void StackToPlaneBehavior::UpdateEndEffectorStatus() {
    int numDocksConnected = 0;
    for (int i = 0; i<6; i++) {
        numDocksConnected += CurrentDockEngagedStatus[i];
    }
    if (numDocksConnected == 1) {
        AmIEndEffector = true;
    }
    else {
        AmIEndEffector = false;
    }
}
/**
 * @brief update connected to object
 */
void StackToPlaneBehavior::UpdateConnectedToObject() {
    AmIConnectedToObject = (CurrentDockEngagedToObjectStatus[0] || CurrentDockEngagedToObjectStatus[1]);
}
/**
 * @brief update object pose
 */
FTransform StackToPlaneBehavior::ComputeObjectPose() {
    if (GroundModule != -1 && SModule) {
        ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                    st.GetVertices()[GroundModule]->GetJointAngles()[2]);
        FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
        ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
        CurrentX = FullBaseTransform.GetLocation().X;
        //GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
        FTransform ManipulatorObjectTransform;
        if (CurrentStackableOb < StackableObs.size() && StackableObs[CurrentStackableOb]) {
            ManipulatorObjectTransform = StackableObs[CurrentStackableOb]->GetActorTransform();
            //ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
            ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
            ModuleBaseToObjectTransform = FTransform(FVector(0, 0, 100))*ModuleBaseToObjectTransform;
            ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform.SetScale3D(FVector(1, 1, 1));
        }
    }
	return ModuleBaseToObjectTransform;
}
/**
 * @brief get kinematics action for dock face
 * @param d dock face
 * @return Superbot action
 */
ModuleAction StackToPlaneBehavior::GetKinematicsActionForDock(ModuleDockFace d) {
    if (d == DOCK_0) {
        return SEND_KINEMATICS_MESSAGE_FRONT_DOCK;
    }
    else if (d == DOCK_1) {
        return SEND_KINEMATICS_MESSAGE_BACK_DOCK;
    }
    else if (d == DOCK_2) {
        return SEND_KINEMATICS_MESSAGE_LEFT_DOCK;
    }
    else if (d == DOCK_3) {
        return SEND_KINEMATICS_MESSAGE_RIGHT_DOCK;
    }
    else if (d == DOCK_4) {
        return SEND_KINEMATICS_MESSAGE_UP_DOCK;
    }
    else if (d == DOCK_5) {
        return SEND_KINEMATICS_MESSAGE_DOWN_DOCK;
    }
    return SEND_KINEMATICS_MESSAGE_FRONT_DOCK;
}
/**
 * @brief get kinematics action for dock face
 * @param d dock face
 * @return Superbot action
 */
ModuleAction StackToPlaneBehavior::GetTreeActionForDock(ModuleDockFace d) {
    if (d == DOCK_0) {
        return SEND_TREE_MESSAGE_FRONT_DOCK;
    }
    else if (d == DOCK_1) {
        return SEND_TREE_MESSAGE_BACK_DOCK;
    }
    else if (d == DOCK_2) {
        return SEND_TREE_MESSAGE_LEFT_DOCK;
    }
    else if (d == DOCK_3) {
        return SEND_TREE_MESSAGE_RIGHT_DOCK;
    }
    else if (d == DOCK_4) {
        return SEND_TREE_MESSAGE_UP_DOCK;
    }
    else if (d == DOCK_5) {
        return SEND_TREE_MESSAGE_DOWN_DOCK;
    }
    return SEND_TREE_MESSAGE_FRONT_DOCK;
}
/**
 * @brief get path to root from node
 * @param n superbot module node
 * @return path
 */
std::vector<int> StackToPlaneBehavior::GetPathToRootFromNode(ModuleNode* n) {
    std::vector<int> path;
    ModuleNode* CNode = n;
    path.push_back(n->GetName());
    while (CNode->GetDiscoveringNode()) {
        CNode = CNode->GetDiscoveringNode();
        path.push_back(CNode->GetName());
    }
    std::reverse(path.begin(), path.end());
    return path;
}
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform StackToPlaneBehavior::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
    if (d1 == DOCK_0 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI));
    }
    else if (d1 == DOCK_1 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI));
    }
    else if (d1 == DOCK_0 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_2 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    else if (d1 == DOCK_3 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_0 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    else if (d1 == DOCK_1 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_2 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_3 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    else if (d1 == DOCK_1 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_0 && d2 == DOCK_4) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    else if (d1 == DOCK_4 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_1 && d2 == DOCK_4) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_4 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    else if (d1 == DOCK_0 && d2 == DOCK_5) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_5 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    else if (d1 == DOCK_1 && d2 == DOCK_5) {
        return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
    }
    else if (d1 == DOCK_5 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
    }
    return FTransform(FVector(0, 0, 0));
}
/**
 * @brief get superbot module tree
 */
ModuleTree StackToPlaneBehavior::GetSuperBotTree() {
    return this->st;
}
/**
 * @brief get the selected end effector
 */
ModuleDockFace StackToPlaneBehavior::GetEndEffectorDockFace() {
    return EEDock;
}
/**
 * @brief get the selected end effector
 */
int StackToPlaneBehavior::GetSelectedEndEffector() {
    return SelectedEndEffector;
}
/**
 * @brief get the selected end effector
 */
int StackToPlaneBehavior::GetGroundModule() {
    return this->GroundModule;
}
/**
 * @brief get the selected end effector
 */
ModuleDockFace StackToPlaneBehavior::GetGroundDockFace() {
    return this->GDock;
}
/**
 * @brief get am i end effector
 * @return am I an end effector
 */
bool StackToPlaneBehavior::GetAmIEndEffector() {
    return this->AmIEndEffector;
}
/**
 * @brief get am i connected to ground
 * @return am I connected to ground
 */
bool StackToPlaneBehavior::GetAmIConnectedToGround() {
    return this->AmIEngagedToGround;
}
/**
 * @brief should reinitialize program ?
 * @return whether or not we need to re init program
 */
bool StackToPlaneBehavior::ShouldReInit() {
    return false;
}




/**
 * @brief init program
 */
void StackToPlaneBehavior::Init() {
    ObjectExtents = FVector(200.0, 200.0, 20.0);
    this->NeighborAngles = std::vector<std::vector<float> >(6);
    for (int i = 0; i<6; i++) {
        this->NeighborAngles[i] = std::vector<float>(3);
    }
    for (int i = 0; i<6; i++) {
        for (int j = 0; j<3; j++) {
            this->NeighborAngles[i][j] = -1000;
        }
    }
    HasReturned[0] = true;
    HasReturned[1] = true;
    HasReturned[2] = true;
    HasReturned[3] = true;
    HasReturned[4] = true;
    HasReturned[5] = true;
    
    this->CurrentAngles = std::vector<float>(3);
    this->CurrentDockEngagedStatus = std::vector<bool>(6);
    this->CurrentDockEngagedToGroundStatus = std::vector<bool>(6);
    this->CurrentDockEngagedToObjectStatus = std::vector<bool>(6);
    for (int i = 0; i<6; i++) {
        this->CurrentDockEngagedStatus[i] = false;
        this->CurrentDockEngagedToGroundStatus[i] = false;
        this->CurrentDockEngagedToObjectStatus[i] = false;
    }
    this->CAngleDiffs = std::vector<float>(3);
    this->CDockDiffs = std::vector<int>(6);
    this->CDockToGroundDiffs = std::vector<int>(6);
    this->CDockToObjectDiffs = std::vector<int>(6);
    for (int i = 0; i<6; i++) {
        this->CDockDiffs[i] = 0;
        this->CDockToGroundDiffs[i] = 0;
        this->CDockToObjectDiffs[i] = 0;
    }
    this->CAngleDiffs[0] = 0.0;
    this->CAngleDiffs[1] = 0.0;
    this->CAngleDiffs[2] = 0.0;
}

/**
* @brief walk toward target
* @return true if completed, false otherwise
*/
bool StackToPlaneBehavior::WalkTowardTarget() {
	if (WalkCounter == 0) {
		HaveInitiatedStep = false;
		HaveFinishedStep = false;
		HaveWaited = false;
		HaveWaitedGround3 = false;
		HaveFoundAnglesToGround = false;
		HavePlannedIKToGround = false;
		HaveExecutedIKToGround = false;
		HaveWaitedGround4 = false;
		HaveWaitedGround1 = false;
		HaveConnectedToGround = false;
	}
	if (WalkCounter > 0) {
		if (!HaveWaited) HaveWaited = ExecuteWait(200);
		else if (!HaveWaitedGround3) HaveWaitedGround3 = ExecuteWait(200);
		else if (!HaveFoundAnglesToGround) HaveFoundAnglesToGround = FindGoalAnglesWithIK();
		else if (!HavePlannedIKToGround) HavePlannedIKToGround = PlanPathCurrentAnglesToGoalAngles();
		else if (!HaveExecutedIKToGround) HaveExecutedIKToGround = ExecutePath();
		else if (!HaveWaitedGround4) HaveWaitedGround4 = ExecuteWait(200);
		else if (!HaveWaitedGround1 || !HaveWaitedGround2) {
			if (!HaveWaitedGround1) HaveWaitedGround1 = ExecuteWait(200);
			else if (HaveWaitedGround1 && !HaveConnectedToGround) {
				ConnectNewEffector();
				HaveConnectedToGround = true;
				WalkCounter = 0;
				return true;
			}
		}
	}

	WalkCounter++;
	return false;
}

/**
* @brief walk toward target
* @return true if completed, false otherwise
*/
bool StackToPlaneBehavior::PickUpObject() {
	if (PickCounter == 0) {
		HaveFoundObjectAngles = false;
		HavePlannedObjectPath = false;
		HaveExecutedObjectPath = false;
		HaveExecutedWait1 = false;
		HaveExecutedWait2 = false;
		HaveConnectedObjectToEffector = false;
	}
	if (PickCounter > 0) {
		if (!HaveFoundObjectAngles) {
			HaveFoundObjectAngles = FindGoalAnglesForObject();
		}
		else if (!HavePlannedObjectPath) { HavePlannedObjectPath = PlanPathCurrentAnglesToGoalAngles(); }
		else if (!HaveExecutedObjectPath) { HaveExecutedObjectPath = ExecutePath(); }
		else if (!HaveExecutedWait1 || !HaveExecutedWait2) {
			if (!HaveExecutedWait1) HaveExecutedWait1 = ExecuteWait(500);
			else if (HaveExecutedWait1 && !HaveConnectedObjectToEffector) {
				ConnectObject();
				HaveConnectedObjectToEffector = true;
			}
			else if (!HaveExecutedWait2 && HaveConnectedObjectToEffector) {
				HaveExecutedWait2 = ExecuteWait(500);
				PickCounter = 0;
				return true;
			}
		}
	}

	PickCounter++;
	return false;
}


/**
* @brief walk toward target
* @return true if completed, false otherwise
*/
bool StackToPlaneBehavior::SetDownObject() {
	if (SetCounter == 0) {
		HavePostWalkPostSwitchFindAngles = false;
		HavePostWalkPostSwitchPlannedToSetDown = false;
		HavePostWalkPostSwitchExecutedSetDown = false;
		HaveWaitedReconnect1 = false;
		HaveWaitedReconnect2 = false;
		HaveReconnected = false;
	}
	if (SetCounter > 0) {
		if (!HavePostWalkPostSwitchFindAngles) HavePostWalkPostSwitchFindAngles = FindGoalAnglesForObjectSetDown();
		else if (!HavePostWalkPostSwitchPlannedToSetDown)HavePostWalkPostSwitchPlannedToSetDown = PlanPathCurrentAnglesToGoalAngles();
		else if (!HavePostWalkPostSwitchExecutedSetDown) HavePostWalkPostSwitchExecutedSetDown = ExecutePath();
		else if (!HaveWaitedReconnect1 || !HaveWaitedReconnect2) {
			if (!HaveWaitedReconnect1) HaveWaitedReconnect1 = ExecuteWait(500);
			else if (HaveWaitedReconnect1 && !HaveReconnected) {
				ReconnectObjectToGround();
				HaveReconnected = true;
			}
			else if (!HaveWaitedReconnect2 && HaveReconnected) {
				HaveWaitedReconnect2 = ExecuteWait(500);
				SetCounter = 0;
				return true;
			}
		}
	}

	SetCounter++;
	return false;
}


/**
 * @brief step function of behavior
 * @param jointVals superbot sensor values
 * @param desiredVals desired sensor values
 * @return action values
 */
void StackToPlaneBehavior::Tick(ModuleModel model) {
    ClearAllActions(); /** clear all the actions from the queue*/
    this->CurrentModel = model;
    UpdateCurrentAngles(); /** update current joint angles of this module */
    UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
    UpdateDockEngagedToGroundStatus(); /** update dock engaged statuses for each dock of this module */
    UpdateDockEngagedToObjectStatus(); /** update dock engaged statuses for object */
    UpdateEngagedToGround(); /** update engaged to ground */
    UpdateEndEffectorStatus(); /** update end effector status */
    UpdateConnectedToObject(); /** update connected to object */
    ComputeObjectPose(); /**< update object pose */
    std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages(); /** Get ranged messages */
    std::vector<Message> ms = model.GetCurrentState().GetMessages(); /** Get messages */
    std::vector<KinematicsMessage> kms = model.GetCurrentState().GetKinematicsMessages(); /** Get kinematics messages */
    std::vector<TreeMessage> tms = model.GetCurrentState().GetTreeMessages(); /** Get tree messages */
    UpdateDockDiffs(); /** Update dock differences */
    
    //Initiate kinematic tree if we are attached  to the ground and have not initiatlized it already
    if (!HasBeenInitialized && (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1])) {
        InitializeKinematicTree();
    }
    
    ProcessMessages(tms); /** Process any messages this module has received */
    
    if (CanSendMessage && (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1])) {
        if (st.GetQueueSize() > 0) {
            //Discover the kinematic structure of the tree
            DiscoverKinematicStructure();
        }
        else if (ShouldSetTreeDirty) {
            //Tree must be rebuilt and re-initialized
            st.ResetCenterOfMassTotal();
            this->ShouldSetTreeDirty = false;
            this->CanSendMessage = true;
            for (int i = 0; i < st.GetVertices().size(); i++) {
                ModuleNode *smn = st.GetVertices()[i];
                if (smn) delete smn;
            }
            InitializeKinematicTree();
        }
        else {
            bool CToOb = false;
            for (int i = 0; i < st.GetVertices().size(); i++) {
                if (st.GetVertices()[i]->GetAmIConnectedToObject()) {
                    CToOb = true;
                }
            }

			if (CToOb) {
				GEngine->AddOnScreenDebugMessage(ObjectChangeKey, 10.0, FColor::Green, FString("Object connected"));
			}

			if (M == PICKING_UP_OBJECT) {
				FTransform LocalB = ComputeLocalBaseTransform();
				FTransform ObjectP = ComputeObjectTargetOnGroundTransform()*LocalB;
				FTransform MB = ComputeModuleToGroundTransform()*LocalB;
				FVector DiffVec = (ObjectP.GetLocation() - MB.GetLocation());
				float DiffSize = DiffVec.Size();
				if (DiffSize <= 500) {
					CloseEnoughToObject = true;
				}
				else {
					CloseEnoughToObject = false;
				}			 
				GEngine->AddOnScreenDebugMessage(ProgramModeKey, 10., FColor::Blue, FString::Printf(TEXT("Program Mode: PICKING, %f, %d"), DiffSize, CurrentStackableOb));
			}
			else if (M == SETTING_DOWN_OBJECT) {
				FTransform LocalB = ComputeLocalBaseTransform();
				FTransform ObjectP = ComputeTargetOnGroundTransform()*LocalB;
				FTransform MB = ComputeModuleToGroundTransform()*LocalB;
				FVector DiffVec = (ObjectP.GetLocation() - MB.GetLocation());
				float DiffSize = DiffVec.Size();
				if (DiffSize <= 500) {
					CloseEnoughToTarget = true;
				}
				else {
					CloseEnoughToTarget = false;
				}
				GEngine->AddOnScreenDebugMessage(ProgramModeKey, 10., FColor::Blue, FString::Printf(TEXT("Program Mode: SETTING, %f, %d"), DiffSize, CurrentStackableOb));
			}
			else if (M == NOTHING) {
				GEngine->AddOnScreenDebugMessage(ProgramModeKey, 10.0, FColor::Blue, FString("Program Mode: NOTHING"));
			}



			if (M == PICKING_UP_OBJECT) {
				if (!CloseEnoughToObject) {
					WalkTowardTarget();
				}
				else {
					if (PickUpObject())
					{
						M = SETTING_DOWN_OBJECT;
					}
				}
			}
			else if (M == SETTING_DOWN_OBJECT) {
				if (!CloseEnoughToTarget) {
					ComputeTargetOnGroundTransform();
					ComputeTransformTargetToFoot();
					WalkTowardTarget();
				}
				else {
					ComputeTargetOnGroundTransform();
					ComputeTransformTargetToFoot();
					//Set down object
					if (SetDownObject()) {
						StackableTargets[CurrentStackableOb]->SetActorHiddenInGame(true);
						CurrentStackableOb++;
						if (CurrentStackableOb <= StackableObs.size() - 1) {
							M = PICKING_UP_OBJECT;
						}
						else {
							M = NOTHING;
						}
					}
				}
			}
        }
    }
    this->ProgramCounter++;
    
}
