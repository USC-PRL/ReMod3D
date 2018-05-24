// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ReBotsSimulatorGameMode.h"
#include "PhysXPublic.h"

/**
* @brief get manipulator object
* @return manipulator object
*/
AManipulatorObjectActor* AReBotsSimulatorGameMode::GetManipObject() {
	return ManipObject;
}
/**
* @brief get constraint between floor and object
* @return constraint between floor and object
*/
APhysicsConstraintActor* AReBotsSimulatorGameMode::GetManipConstraint() {
	return ManipConstraintToGround;
}
//#pragma mark -
//#pragma Superbot Docking
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform AReBotsSimulatorGameMode::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
	if (d1 == DOCK_0 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI));
	}
	else if (d1 == DOCK_0 && d2 == DOCK_2) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_2 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_3 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_0 && d2 == DOCK_3) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_2) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_2 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_3 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_3) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
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
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_5 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	return FTransform(FVector(0, 0, 0));
}
/**
 * @brief dock two modules together
 * @param sm1 superbot module 1
 * @param sm2 superbot module 2
 * @param d1 dock face of module 1
 * @param d2 dock face of module 2
 */
void AReBotsSimulatorGameMode::DockModuleToGround(ASuperBotModule* sm1, ModuleDockFace d1) {
	FName d1S = "BackDock";
	if (d1 == DOCK_0) d1S = "FrontDock";
	else if (d1 == DOCK_1) d1S = "BackDock";
	else if (d1 == DOCK_2) d1S = "LeftDock";
	else if (d1 == DOCK_3) d1S = "RightDock";
	else if (d1 == DOCK_4) d1S = "UpDock";
	else if (d1 == DOCK_5) d1S = "DownDock";
	UStaticMeshComponent* stMesh1;

	if (d1 == DOCK_0 || d1 == DOCK_3 || d1 == DOCK_2) {
		stMesh1 = sm1->GetMasterOuterMesh();
	}
	else {
		stMesh1 = sm1->GetSlaveOuterMesh();
	}
	APhysicsConstraintActor *a = GetWorld()->SpawnActor<APhysicsConstraintActor>();
	a->GetConstraintComp()->SetConstrainedComponents(stMesh1, d1S, Floor->GetStaticMeshComponent(), "");
	a->GetConstraintComp()->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	sm1->SetDockEngagedToGround(d1, true);
	sm1->GroundDockConstraints[d1] = a;
}
/**
* @brief dock object to ground
* @param a manipulator object actor
*/
void AReBotsSimulatorGameMode::DockObjectToGround(AManipulatorObjectActor* a) {
	APhysicsConstraintActor *apc = GetWorld()->SpawnActor<APhysicsConstraintActor>();
	apc->GetConstraintComp()->SetConstrainedComponents(a->GetBox(), "Box", Floor->GetStaticMeshComponent(), "");
	apc->GetConstraintComp()->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	apc->GetConstraintComp()->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	apc->GetConstraintComp()->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	apc->GetConstraintComp()->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	apc->GetConstraintComp()->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	apc->GetConstraintComp()->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
}
/**
* @brief dock two modules together
* @param sm1 superbot module 1
* @param d1 superbot module 1 dock face
* @param actor static mesh actor to which to connect
*/
void AReBotsSimulatorGameMode::DockModuleToObject(ASuperBotModule* sm1, ModuleDockFace d1,
												  AManipulatorObjectActor* actor) {
	FName d1S = "BackDock";
	if (d1 == DOCK_0) d1S = "FrontDock";
	else if (d1 == DOCK_1) d1S = "BackDock";
	else if (d1 == DOCK_2) d1S = "LeftDock";
	else if (d1 == DOCK_3) d1S = "RightDock";
	else if (d1 == DOCK_4) d1S = "UpDock";
	else if (d1 == DOCK_5) d1S = "DownDock";
	UStaticMeshComponent* stMesh1;

	if (d1 == DOCK_0 || d1 == DOCK_3 || d1 == DOCK_2) {
		stMesh1 = sm1->GetMasterOuterMesh();
	}
	else {
		stMesh1 = sm1->GetSlaveOuterMesh();
	}
	APhysicsConstraintActor *a = GetWorld()->SpawnActor<APhysicsConstraintActor>();
	a->GetConstraintComp()->SetConstrainedComponents(stMesh1, d1S, actor->GetBox(), "Box");
	a->GetConstraintComp()->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	sm1->SetDockEngagedToObject(d1, true);
	sm1->ObjectDockConstraints[d1] = a;
}
/**
 * @brief dock two modules together
 * @param sm1 superbot module 1
 * @param sm2 superbot module 2
 * @param d1 dock face of module 1
 * @param d2 dock face of module 2
 */
void AReBotsSimulatorGameMode::DockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2) {

	//TODO: use root hierarchy somehow?
	connections[sm1->GetIDNumber()][d1] = sm2->GetDocks()[d2];
	connections[sm2->GetIDNumber()][d2] = sm1->GetDocks()[d1];
	std::pair<ASuperBotModule*, ModuleDockFace> modPair(sm1, d1);
	std::pair<ASuperBotModule*, ModuleDockFace> modPair2(sm2, d2);
	sm1->SetDockEngaged(d1, true);
	sm2->SetDockEngaged(d2, true);
	ModuleMotorVector mv1 = sm1->GetJointAngles();
	ModuleMotorVector mv2 = sm2->GetJointAngles();
    sm1->GetRootComponent()->AttachTo(sm2->GetRootComponent(),"",EAttachLocation::SnapToTarget, true);
	sm1->GetRootComponent()->SetRelativeTransform(sm1->GetRootToMasterInnerTransform().Inverse()*
		SuperbotKinematics::computeTransformFromDock(mv1, d1)*
		GetCorrectiveDockingTransform(d1, d2)*
		SuperbotKinematics::computeTransformToDock(mv2, d2)*
		sm2->GetRootToMasterInnerTransform());

	sm1->WeldDockToComponent(d1, sm2->GetDockComponent(d2));
	FName d1S = "BackDock";
	FName d2S = "FrontDock";
	if (d1 == DOCK_0) d1S = "FrontDock";
	else if (d1 == DOCK_1) d1S = "BackDock";
	else if (d1 == DOCK_2) d1S = "LeftDock";
	else if (d1 == DOCK_3) d1S = "RightDock";
	else if (d1 == DOCK_4) d1S = "UpDock";
	else if (d1 == DOCK_5) d1S = "DownDock";
	if (d2 == DOCK_0) d1S = "FrontDock";
	else if (d2 == DOCK_1) d2S = "BackDock";
	else if (d2 == DOCK_2) d2S = "LeftDock";
	else if (d2 == DOCK_3) d2S = "RightDock";
	else if (d2 == DOCK_4) d2S = "UpDock";
	else if (d2 == DOCK_5) d2S = "DownDock";
	UStaticMeshComponent* stMesh1;
	UStaticMeshComponent* stMesh2;

	if (d1 == DOCK_0 || d1 == DOCK_3 || d1 == DOCK_2) {
		stMesh1 = sm1->GetMasterOuterMesh();
	}
	else {
		stMesh1 = sm1->GetSlaveOuterMesh();
	}

	if (d2 == DOCK_0 || d2 == DOCK_3 || d2 == DOCK_2) {
		stMesh2 = sm2->GetMasterOuterMesh();
	}
	else {
		stMesh2 = sm2->GetSlaveOuterMesh();
	}
	APhysicsConstraintActor *a = GetWorld()->SpawnActor<APhysicsConstraintActor>();
	a->GetConstraintComp()->SetConstrainedComponents(stMesh1, d1S, stMesh2, d2S);
	a->GetConstraintComp()->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	a->GetConstraintComp()->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	a->GetConstraintComp()->SetDisableCollision(true);
	InterModuleConstraints[modPair] = a;
	InterModuleConstraints[modPair2] = a;
}
/**
* @brief undock two modules
* @param sm1 superbot module 1
* @param sm2 superbot module 2
* @param d1 dock face of module 1
* @param d2 dock face of module 2
*/
void AReBotsSimulatorGameMode::UnDockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2) {
	typedef std::map<std::pair<ASuperBotModule*, ModuleDockFace>, APhysicsConstraintActor*>::iterator monitorIt;
	for (monitorIt iterator = InterModuleConstraints.begin(); iterator != InterModuleConstraints.end(); iterator++) {
		std::pair<ASuperBotModule*, ModuleDockFace> modPair = iterator->first;
		APhysicsConstraintActor* a = iterator->second;
		if ((modPair.first == sm1 && modPair.second == d1)) {
			if (a) {
				a->GetConstraintComp()->BreakConstraint();
				a->Destroy(); 
				sm1->SetDockEngaged(d1, false);
				sm2->SetDockEngaged(d2, false);
				InterModuleConstraints[modPair] = NULL; 
				break; 
			}
		}
	}
}
/**
 * @brief game mode constructor
 * @param ObjectInitializer initializer
 */
AReBotsSimulatorGameMode::AReBotsSimulatorGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	//DefaultPawnClass = ASuperBotModule::StaticClass();
}
/**
 * @brief advance the simulation
 * @param DeltaSeconds fraction of a second by which to advance simulation
 */
void AReBotsSimulatorGameMode::Tick(float DeltaSeconds) {

	if (FirstTick) {
		TActorIterator< APhysicsConstraintActor > ConstraintIt = TActorIterator< APhysicsConstraintActor >(GetWorld());
		TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(GetWorld());
		TActorIterator< AManipulatorObjectActor > ManipObjectIt = TActorIterator< AManipulatorObjectActor >(GetWorld());
		while (SuperbotIt) {
			string str = (*SuperbotIt)->GetName();
			size_t last_index = str.find_last_not_of("0123456789");
			string result = str.substr(last_index + 1);
			stringstream  ss(result);
			int resultInt;
			ss >> resultInt;
			(*SuperbotIt)->SetIDNumber(resultInt);
			modsToIDs[*SuperbotIt] = resultInt;
			modulesMap[resultInt] = *SuperbotIt;
			++SuperbotIt;
		}
		if (*ManipObjectIt) cout << TCHAR_TO_UTF8(*(*ManipObjectIt)->GetName()) << endl;
		ManipObject = *ManipObjectIt;
		int numConstraints = 0;
		while (ConstraintIt) {
			numConstraints++;
			APhysicsConstraintActor *c = *ConstraintIt;
			if (c->GetConstraintComp()->ConstraintActor1->GetClass() == ASuperBotModule::StaticClass() &&
				c->GetConstraintComp()->ConstraintActor2->GetClass() == ASuperBotModule::StaticClass()) {
				ASuperBotModule* sm1 = Cast<ASuperBotModule>(c->GetConstraintComp()->ConstraintActor1);
				ASuperBotModule* sm2 = Cast<ASuperBotModule>(c->GetConstraintComp()->ConstraintActor2);
				FConstrainComponentPropName n1 = c->GetConstraintComp()->ComponentName1;
				FConstrainComponentPropName n2 = c->GetConstraintComp()->ComponentName2;
				FString name1 = n1.ComponentName.ToString();
				FString name2 = n2.ComponentName.ToString();
				FString bone1 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone1.ToString();
				FString bone2 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone2.ToString();
				ModuleDockFace dock1 = sm1->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone1)));
				ModuleDockFace dock2 = sm2->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone2)));
				//sm1->AttachRootComponentTo(sm2->GetRootComponent(), "", EAttachLocation::KeepRelativeOffset, false);
				if (sm1 && sm2) {
					if (DockDebug) {
						cout << "Constraint Found: " << sm1->GetName() << "-" << std::string(TCHAR_TO_UTF8(*bone1)) <<
							"(" << dock1 << ")" << "," << sm2->GetName() << "-" << std::string(TCHAR_TO_UTF8(*bone2)) << "(" << dock2 << ")" << endl;
					}
					CMonitor.AddConstraint(sm1->GetName(), sm2->GetName(), (ModuleDockFace)dock1, (ModuleDockFace)dock2);
					connections[sm1->GetIDNumber()][dock1] = sm2->GetDocks()[dock2];
					connections[sm2->GetIDNumber()][dock2] = sm1->GetDocks()[dock1];
					InterModuleConstraints[std::pair<ASuperBotModule*, ModuleDockFace>(sm1, dock1)] = c;
					InterModuleConstraints[std::pair<ASuperBotModule*, ModuleDockFace>(sm2, dock2)] = c;
					sm1->WeldDockToComponent(dock1, sm2->GetDocks()[dock2].GetDockComponent());

					sm1->SetDockEngaged(dock1, true);
					sm2->SetDockEngaged(dock2, true);
					if (DockDebug) {
						cout << sm1->GetName() << " Dock Status: ";
						for (int i = 0; i < 6; i++) {
							cout << sm1->GetDocks()[i].GetDockEngaged() << " ";
						}
						cout << endl;
						cout << sm2->GetName() << " Dock Status: ";
						for (int i = 0; i < 6; i++) {
							cout << sm2->GetDocks()[i].GetDockEngaged() << " ";
						}
						cout << endl;
					}
				}
			}
			else if (c->GetConstraintComp()->ConstraintActor1->GetClass() == ASuperBotModule::StaticClass() &&
				c->GetConstraintComp()->ConstraintActor2->GetClass() == AStaticMeshActor::StaticClass()) {
				ASuperBotModule *m = (ASuperBotModule*)c->GetConstraintComp()->ConstraintActor1;
				AStaticMeshActor *sma = (AStaticMeshActor*)c->GetConstraintComp()->ConstraintActor2;
				if (std::string(TCHAR_TO_UTF8(*sma->GetName())).compare("Floor") == 0) {
					FString bone1 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone1.ToString();
					ModuleDockFace dock1 = m->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone1)));
					m->SetDockEngagedToGround(dock1, true);
					m->GroundDockConstraints[dock1] = c;
					cout << m->GetName() << " Connected to floor statuses: " << endl;
					if (DockDebug) {
						for (int i = 0; i < 6; i++) {
							cout << m->GetDocks()[i].GetDockEngagedToGround() << " ";
						}
						cout << endl;
					}
				}
			}
			else if (c->GetConstraintComp()->ConstraintActor1->GetClass() == AStaticMeshActor::StaticClass() &&
				c->GetConstraintComp()->ConstraintActor2->GetClass() == ASuperBotModule::StaticClass()) {
				ASuperBotModule *m = (ASuperBotModule*)c->GetConstraintComp()->ConstraintActor2;
				AStaticMeshActor *sma = (AStaticMeshActor*)c->GetConstraintComp()->ConstraintActor1;
				if (std::string(TCHAR_TO_UTF8(*sma->GetName())).compare("Floor") == 0) {
					FString bone2 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone2.ToString();
					ModuleDockFace dock2 = m->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone2)));
					m->SetDockEngagedToGround(dock2, true);
					m->GroundDockConstraints[dock2] = c;
					cout << m->GetName() << " Connected to floor statuses ";
					if (DockDebug) {
						for (int i = 0; i < 6; i++) {
							cout << m->GetDocks()[i].GetDockEngagedToGround() << " ";
						}
						cout << endl;
					}
				}
			}
			else if (c->GetConstraintComp()->ConstraintActor1->GetClass() == AManipulatorObjectActor::StaticClass() ||
				c->GetConstraintComp()->ConstraintActor2->GetClass() == AManipulatorObjectActor::StaticClass()) {
				ManipConstraintToGround = c;
			}
			++ConstraintIt;
		}
		TActorIterator< AStaticMeshActor > StaticMeshActorsIt = TActorIterator< AStaticMeshActor >(GetWorld());
		while (StaticMeshActorsIt) {
			if (std::string(TCHAR_TO_UTF8(*(*StaticMeshActorsIt)->GetName())).compare("Floor") == 0) {
				AStaticMeshActor* MeshActor = (*StaticMeshActorsIt);
				Floor = MeshActor;
				//AFloorCollisionActor* FloorCollision = GetWorld()->SpawnActor<AFloorCollisionActor>(MeshActor->GetActorLocation(),
				//                                                              MeshActor->GetActorRotation());

				break;
			}
			++StaticMeshActorsIt;
		}
		FirstTick = false;
	}
	else {
		TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(GetWorld());
		while (SuperbotIt) {
			bool EngagedToGround = false;
			ModuleDockFace D = DOCK_1;
			if ((*(SuperbotIt))->GetDocks()[DOCK_0].GetDockEngagedToGround() ||
				(*(SuperbotIt))->GetDocks()[DOCK_1].GetDockEngagedToGround()) {
				EngagedToGround = true;
			}
			if ((*(SuperbotIt))->GetDocks()[DOCK_0].GetDockEngagedToGround()) {
				D = DOCK_0;
			}
			else if ((*(SuperbotIt))->GetDocks()[DOCK_0].GetDockEngagedToGround()) {
				D = DOCK_1;
			}
			RenderBehaviorData(*SuperbotIt, EngagedToGround, D);
			++SuperbotIt;
		}
	}
}




//#pragma mark -
//#pragma mark Messaging Functionality
/**
 *	@brief	Sends a message from module to the module connected to dock
 *	@param 	module 	sending module
 *	@param 	dock 	dock out which message is sent
 *	@param 	message 	message contents
 */
void AReBotsSimulatorGameMode::sendMessageToDock(ASuperBotModule *module, ModuleDock dock, std::string message) {
	if (connections[modsToIDs[module]][dock.GetDockFace()].GetDockFace() == DOCK_6) {
		cout << "Message unroutable: module " << modsToIDs[module] << " dock " << dock.GetDockFace() << endl; \
			cout << "No dock connected" << endl;
		return;
	}
	Message m = Message(message, dock, connections[modsToIDs[module]][dock.GetDockFace()]);
	messageRoom[modsToIDs[(ASuperBotModule*)connections[modsToIDs[module]][dock.GetDockFace()].GetModule()]].push_back(m);
}
/**
* @brief send module message to dock face
* @param sendingModule sending module
* @param Face module dock face
* @param Mes message
*/
void AReBotsSimulatorGameMode::sendModuleMessageToDock(ASuperBotModule *sendingModule, ModuleDockFace Face, std::string Mes) {
	
}
/**
 *	@brief	Sends a kinematics message out on dock
 *	@param 	sendingModule 	module sending the message
 * @param dock dock send ing message
 *	@param 	mes 	message contents
 */
void AReBotsSimulatorGameMode::sendKinematicsMessageToDock(ASuperBotModule *module, ModuleDock dock, KinematicsMessage mes) {
	if (connections[modsToIDs[module]][dock.GetDockFace()].GetDockFace() == DOCK_6) {
		cout << "Message unroutable: module " << modsToIDs[module] << " dock " << dock.GetDockFace() << endl;
		cout << "No dock connected" << endl;
		return;
	}
	mes.SetSendingDock(dock);
	mes.SetReceivingDock(connections[modsToIDs[module]][dock.GetDockFace()]);
	messageRoomKinematics[modsToIDs[(ASuperBotModule*)connections[modsToIDs[module]][dock.GetDockFace()].GetModule()]].push_back(mes);
}
/**
 *	@brief	Sends a kinematics message out on dock
 *	@param 	sendingModule 	module sending the message
 * @param dock dock send ing message
 *	@param 	mes 	message contents
 */
void AReBotsSimulatorGameMode::sendTreeMessageToDock(ASuperBotModule *module, ModuleDock dock, TreeMessage mes) {
	if (connections[modsToIDs[module]][dock.GetDockFace()].GetDockFace() == DOCK_6) {
		cout << "Message unroutable: module " << modsToIDs[module] << " dock " << dock.GetDockFace() << endl;
		cout << "No dock connected" << endl;
		return;
	}
	mes.SetSendingDock(dock);
	mes.SetReceivingDock(connections[modsToIDs[module]][dock.GetDockFace()]);
	messageRoomSuperBotTree[modsToIDs[(ASuperBotModule*)connections[modsToIDs[module]][dock.GetDockFace()].GetModule()]].push_back(mes);
}
/**
 *	@brief	Sends a wireless message out from sendingModule's center of mass. The range of the message is a sphere
 *          centered at sendingModule's center of mass with a radius of range.
 *	@param 	sendingModule 	module sending the message
 *	@param 	range 	range of the message
 *	@param 	message 	message contents
 */
void AReBotsSimulatorGameMode::sendRangedMessage(ASuperBotModule *sendingModule, float range, string message) {

	RangedMessage m = RangedMessage(message, range);
	for (int i = 0; i < (int)modulesMap.size(); i++) {
		if (modsToIDs[modulesMap[i]] != modsToIDs[sendingModule]) {
			FTransform pose1 = ASuperBotModule::SuperbotFix*modulesMap[i]->GetMasterInnerMesh()->GetComponentTransform();
			FTransform pose2 = ASuperBotModule::SuperbotFix*sendingModule->GetMasterInnerMesh()->GetComponentTransform();
			float dist = FVector::Dist(pose1.GetLocation(), pose2.GetLocation());
			if (dist <= range) {
				messageRoomRanged[modsToIDs[modulesMap[i]]].push_back(m);
			}
		}
	}
}
/**
 *	@brief	retrieves the last message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent message in module's queue of messages
 */
Message AReBotsSimulatorGameMode::getLastMessage(int module) {
	Message m = messageRoom[module].back();
	messageRoom[module].pop_back();
	return m;
}
/**
*	@brief	retrieves the last message sent to the module with the given name
*	@param 	module 	name of module
*	@return	most recent message in module's queue of messages
*/
ModuleMessage AReBotsSimulatorGameMode::getLastModuleMessage(int module) {
	ModuleMessage m = moduleMessageRoom[module].back();
	moduleMessageRoom[module].pop_back();
	return m;
}
/**
 *	@brief	retrieves the last ranged message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent ranged message in module's queue of ranged messages
 */
RangedMessage AReBotsSimulatorGameMode::getLastRangedMessage(int module) {
	RangedMessage m = messageRoomRanged[module].back();
	messageRoomRanged[module].pop_back();
	return m;
}
/**
 *	@brief	retrieves the ranged messages for a given module
 *	@param 	module 	name of module
 *	@return	messages from modules ranged message queue
 */
vector<RangedMessage> AReBotsSimulatorGameMode::getRangedMessages(int module) {
	vector<RangedMessage> messagesR;
	for (int i = messageRoomRanged[module].size() - 1; i >= 0; i--) {
		messagesR.push_back(messageRoomRanged[module][i]);
	}
	messageRoomRanged[module].clear();
	return messagesR;
}
/**
 *	@brief	retrieves messages for a given module
 *	@param 	module 	name of module
 *	@return	messages fromm module's message queue
 */
vector<Message> AReBotsSimulatorGameMode::getMessages(int module) {
	vector<Message> messages;
	for (int i = messageRoom[module].size() - 1; i >= 0; i--) {
		messages.push_back(messageRoom[module][i]);
	}
	messageRoom[module].clear();
	return messages;
}
/**
* @brief get module messages
* @param module module name
* @return module messages
*/
vector<ModuleMessage> AReBotsSimulatorGameMode::getModuleMessages(int module) {
	vector<ModuleMessage> messages;
	for (int i = moduleMessageRoom[module].size() - 1; i >= 0; i--) {
		messages.push_back(moduleMessageRoom[module][i]);
	}
	moduleMessageRoom.clear();
	return messages;
}
/**
 *	@brief	Clears (deletes) the messages of a module with the given name
 *	@param 	module 	name of the module
 */
void AReBotsSimulatorGameMode::clearMessages(int module) {
	messageRoom[module].clear();
}

/**
 *	@brief	retrieves the last message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent message in module's queue of messages
 */
KinematicsMessage AReBotsSimulatorGameMode::getLastKinematicsMessage(int module) {
	KinematicsMessage m = messageRoomKinematics[module].back();
	messageRoomKinematics[module].pop_back();
	return m;
}

/**
 *	@brief	retrieves messages for a given module
 *	@param 	module 	name of module
 *	@return	messages fromm module's message queue
 */
vector<KinematicsMessage> AReBotsSimulatorGameMode::getKinematicsMessages(int module) {
	vector<KinematicsMessage> messages;
	for (int i = messageRoomKinematics[module].size() - 1; i >= 0; i--) {
		messages.push_back(messageRoomKinematics[module][i]);
	}
	messageRoomKinematics[module].clear();
	return messages;
}
/**
 *	@brief	retrieves the last message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent message in module's queue of messages
 */
TreeMessage AReBotsSimulatorGameMode::getLastTreeMessage(int module) {
	TreeMessage m = messageRoomSuperBotTree[module].back();
	messageRoomSuperBotTree[module].pop_back();
	return m;
}

/**
 *	@brief	retrieves messages for a given module
 *	@param 	module 	name of module
 *	@return	messages fromm module's message queue
 */
vector<TreeMessage> AReBotsSimulatorGameMode::getTreeMessages(int module) {
	vector<TreeMessage> messages;
	for (int i = messageRoomSuperBotTree[module].size() - 1; i >= 0; i--) {
		messages.push_back(messageRoomSuperBotTree[module][i]);
	}
	messageRoomSuperBotTree[module].clear();
	return messages;
}

/**
* @brief render behavior-specific stuff
* @param Mod superbot module
* @param EngagedToGround is module engaged to ground?
* @param D dock face attached to ground
*/
void AReBotsSimulatorGameMode::RenderBehaviorData(ASuperBotModule *Mod, bool EngagedToGround, ModuleDockFace D) {
	ModManipQBehavior* MMQB = NULL;
	ReconfDemoQ2Behavior* RDQ2B = NULL;
	ReconfDemoQBehavior* RDQB = NULL;
	SnakeIKBehavior* SIKB = NULL;
	TreeWalkingBehavior* TWB = NULL;
	if ((Mod)->GetModuleBehavior()->GetName().compare("ModManipQ") == 0) {
		MMQB = (ModManipQBehavior*)(Mod)->GetModuleBehavior();
	}
	if ((Mod)->GetModuleBehavior()->GetName().compare("ReconfQ") == 0) {
		RDQB = (ReconfDemoQBehavior*)(Mod)->GetModuleBehavior();
	}
	if ((Mod)->GetModuleBehavior()->GetName().compare("ReconfQ2") == 0) {
		RDQ2B = (ReconfDemoQ2Behavior*)(Mod)->GetModuleBehavior();
	}
	if ((Mod)->GetModuleBehavior()->GetName().compare("SnakeIK") == 0) {
		SIKB = (SnakeIKBehavior*)(Mod)->GetModuleBehavior();
	}
	if ((Mod)->GetModuleBehavior()->GetName().compare("TreeWalk") == 0) {
		TWB = (TreeWalkingBehavior*)(Mod)->GetModuleBehavior();
	}
	if (SIKB && EngagedToGround) {
		std::vector<std::pair<int, ModuleDockFace> > TargetEs = SIKB->GetTargetEffectors();
		std::vector<FTransform> TargetTs = SIKB->GetTargetTransforms();
		std::vector<float> TAngles = SIKB->GetTargetAngles();
		int gm = SIKB->GetGroundModule();
		bool shouldRender = true;
		if (TargetEs.size() > 0) {
			for (int i = 0; i < TargetEs.size(); i++) {
				if (SIKB->GetSuperBotTree().GetVertices().size() - 1 < TargetEs[i].first) {
					shouldRender = false;
				}
			}
		}
		if (TAngles.size() > 0 && SIKB->GetSuperBotTree().GetVertices().size() > 0 && gm != -1 &&
			SIKB->GetSuperBotTree().GetVertices().size() - 1 >= gm && shouldRender) {
			ModuleMotorVector mvs(SIKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
				SIKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
				SIKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
			FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
				SIKB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
			if (TargetTs.size() > 0 && TargetEs.size() > 0) {
				for (int i = 0; i < TargetTransformActors.size(); i++) {
					if (TargetTransformActors[i]) TargetTransformActors[i]->Destroy();
					TargetTransformActors[i] = NULL;
				}
				TargetTransformActors.clear();
				for (int i = 0; i < TargetEs.size(); i++) {
					if (TargetEs[i].first == SIKB->GetSelectedEndEffector()) {
						ModuleDockFace fDockFace = TargetEs[i].second;
						ModuleMotorVector mvsF(TAngles[3 * TargetEs[i].first + 0], TAngles[3 * TargetEs[i].first + 1],
							TAngles[3 * TargetEs[i].first + 2]);
						FTransform EEPose = SuperbotKinematics::computeTransformToDock(mvsF, fDockFace)*TargetTs[TargetEs[i].first] * GroundActorTrans;
						TargetTransformActors.push_back(GetWorld()->SpawnActor<AReferenceFrameActor>(EEPose.GetLocation(),
							FRotator(EEPose.GetRotation())));
					}
				}
			}
			if (SIKB->GetSuperBotTree().GetVertices().size() > 0 && gm!=-1 &&
				SIKB->GetSuperBotTree().GetVertices().size() - 1 >= gm &&
				shouldRender) {
				ModuleMotorVector mvss(SIKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					SIKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					SIKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				std::vector<std::pair<int, ModuleDockFace> > TargetEss = SIKB->GetTargetEffectors();
				for (int i = 0; i < EEActors.size(); i++) {
					if (EEActors[i]) EEActors[i]->Destroy();
					EEActors[i] = NULL;
				}
				EEActors.clear();
				FTransform GroundActorTransN = SuperbotKinematics::computeTransformToDock(mvss, SIKB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				for (int i = 0; i < TargetEss.size(); i++) {
						FTransform FTrans = SIKB->GetSuperBotTree().GetVertices()[TargetEss[i].first]->GetTransform();
						ModuleMotorVector mvsFinal(SIKB->GetSuperBotTree().GetVertices()[TargetEss[i].first]->GetJointAngles()[0],
							SIKB->GetSuperBotTree().GetVertices()[TargetEss[i].first]->GetJointAngles()[1],
							SIKB->GetSuperBotTree().GetVertices()[TargetEss[i].first]->GetJointAngles()[2]);
						FTransform FinalFKTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, TargetEss[i].second)*FTrans*GroundActorTransN;
						EEActors.push_back(GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKTrans.GetLocation(), FRotator(FinalFKTrans.GetRotation())));
				}
			}
		}
	}
	if (TWB && EngagedToGround) {
		if (TWB->GetSuperBotTree().GetVertices().size() > 0) {
			int see = TWB->GetSelectedEndEffector();
			if (see != -1 && TWB->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				FTransform FinalFKActorTrans = TWB->GetSuperBotTree().GetVertices()[see]->GetTransform()*
					SuperbotKinematics::computeTransformToDock((Mod)->GetJointAngles(), D)*
					ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				ModuleMotorVector mvs(TWB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					TWB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					TWB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
					TWB->GetEndEffectorDockFace())*FinalFKActorTrans;
				if (TWB->GetSuperBotTree().GetVertices()[see]->GetAmIConnectedToObject()) {
					if (TWB->GetEndEffectorDockFace() == DOCK_0) {
						FinalFKActorTrans = FTransform(FVector(50, 0, 0))*FinalFKActorTrans;
					}
					else {
						FinalFKActorTrans = FTransform(FVector(-50, 0, 0))*FinalFKActorTrans;
					}
				}
				if (!FinalFKActor) {
					FinalFKActor = GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKActorTrans.GetLocation(), FRotator(FinalFKActorTrans.GetRotation()));
				}
				else {
					FinalFKActor->SetActorTransform(FinalFKActorTrans);
				}
			}
		}
		if (TWB->GetBestTransforms().size() > 0) {
			int gm = TWB->GetGroundModule();
			std::vector<float> sol = TWB->GetSolutionPos();
			int see = TWB->GetSelectedEndEffector();
			if (gm != -1 && TWB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(sol[3 * see + 0], sol[3 * see + 1], sol[3 * see + 2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, TWB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform EndModuleTrans =
					SuperbotKinematics::computeTransformToDock(end, TWB->GetEndEffectorDockFace())*
					TWB->GetBestTransforms()[see] * GroundActorTrans;
				if (!TargetFootActor) {
					TargetFootActor = GetWorld()->SpawnActor<AReferenceFrameActor>((EndModuleTrans).GetLocation(), FRotator(EndModuleTrans.GetRotation()));
				}
				else {
					TargetFootActor->SetActorTransform(EndModuleTrans);
				}

			}
		}
		if (TWB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = TWB->GetGroundModule();
			if (gm != -1 && TWB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, TWB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform TargTrans = TWB->GetTargetTransform()*GroundActorTrans;
				if (TWB->GetEndEffectorDockFace() != TWB->GetGroundDockFace()) {
					TargTrans = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*TargTrans;
				}
				if (!TargetTransformActor) {
					//TargetTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(TargTrans.GetLocation(), FRotator(TargTrans.GetRotation()));
				}
				else {
					//TargetTransformActor->SetActorTransform(TargTrans);
				}
			}
		}
		if (TWB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = TWB->GetGroundModule();
			if (gm != -1 && TWB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					TWB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, TWB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform ObjectTrans = TWB->GetModuleBaseToObjectTransform()*GroundActorTrans;
				FTransform ActualGTrans = TWB->GetModuleBaseToGroundTransform()*GroundActorTrans;
				ObjectTrans = FTransform(FVector(-50.0 / 2.0, 0, 0))*ObjectTrans;
				if (!ManipObjectTransformActor) {
					//ManipObjectTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(ObjectTrans.GetLocation(),
					//	FRotator(ObjectTrans.GetRotation()));
				}
				else {
					//ManipObjectTransformActor->SetActorTransform(ObjectTrans);
				}

			}
		}
	}
	if (RDQB && EngagedToGround) {
		if (RDQB->GetSuperBotTree().GetVertices().size() > 0) {
			int see = RDQB->GetSelectedEndEffector();
			if (see != -1 && RDQB->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				FTransform FinalFKActorTrans = RDQB->GetSuperBotTree().GetVertices()[see]->GetTransform()*
					SuperbotKinematics::computeTransformToDock((Mod)->GetJointAngles(), D)*
					ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				ModuleMotorVector mvs(RDQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					RDQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					RDQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
					RDQB->GetEndEffectorDockFace())*FinalFKActorTrans;
				if (RDQB->GetSuperBotTree().GetVertices()[see]->GetAmIConnectedToObject()) {
					if (RDQB->GetEndEffectorDockFace() == DOCK_0) {
						FinalFKActorTrans = FTransform(FVector(50, 0, 0))*FinalFKActorTrans;
					}
					else {
						FinalFKActorTrans = FTransform(FVector(-50, 0, 0))*FinalFKActorTrans;
					}
				}
				if (!FinalFKActor) {
					FinalFKActor = GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKActorTrans.GetLocation(), FRotator(FinalFKActorTrans.GetRotation()));
				}
				else {
					FinalFKActor->SetActorTransform(FinalFKActorTrans);
				}
			}
		}
		if (RDQB->GetBestTransforms().size() > 0) {
			int gm = RDQB->GetGroundModule();
			std::vector<float> sol = RDQB->GetSolutionPos();
			int see = RDQB->GetSelectedEndEffector();
			if (gm != -1 && RDQB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(sol[3 * see + 0], sol[3 * see + 1], sol[3 * see + 2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform EndModuleTrans =
					SuperbotKinematics::computeTransformToDock(end, RDQB->GetEndEffectorDockFace())*
					RDQB->GetBestTransforms()[see] * GroundActorTrans;
				if (!TargetFootActor) {
					TargetFootActor = GetWorld()->SpawnActor<AReferenceFrameActor>((EndModuleTrans).GetLocation(), FRotator(EndModuleTrans.GetRotation()));
				}
				else {
					TargetFootActor->SetActorTransform(EndModuleTrans);
				}

			}
		}
		if (RDQB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = RDQB->GetGroundModule();
			if (gm != -1 && RDQB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform TargTrans = RDQB->GetTargetTransform()*GroundActorTrans;
				if (RDQB->GetEndEffectorDockFace() != RDQB->GetGroundDockFace()) {
					TargTrans = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*TargTrans;
				}
				if (!TargetTransformActor) {
					//TargetTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(TargTrans.GetLocation(), FRotator(TargTrans.GetRotation()));
				}
				else {
					//TargetTransformActor->SetActorTransform(TargTrans);
				}
			}
		}
		if (RDQB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = RDQB->GetGroundModule();
			if (gm != -1 && RDQB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform ObjectTrans = RDQB->GetModuleBaseToObjectTransform()*GroundActorTrans;
				FTransform ActualGTrans = RDQB->GetModuleBaseToGroundTransform()*GroundActorTrans;
				ObjectTrans = FTransform(FVector(-50.0 / 2.0, 0, 0))*ObjectTrans;
				if (!ManipObjectTransformActor) {
					//ManipObjectTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(ObjectTrans.GetLocation(),
					//	FRotator(ObjectTrans.GetRotation()));
				}
				else {
					//ManipObjectTransformActor->SetActorTransform(ObjectTrans);
				}

			}
		}
	}
	if (RDQ2B && EngagedToGround) {
		if (RDQ2B->GetSuperBotTree().GetVertices().size() > 0) {
			int see = RDQ2B->GetSelectedEndEffector();
			if (see != -1 && RDQ2B->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				FTransform FinalFKActorTrans = RDQ2B->GetSuperBotTree().GetVertices()[see]->GetTransform()*
					SuperbotKinematics::computeTransformToDock((Mod)->GetJointAngles(), D)*
					ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				ModuleMotorVector mvs(RDQ2B->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					RDQ2B->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					RDQ2B->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
					RDQ2B->GetEndEffectorDockFace())*FinalFKActorTrans;
				if (RDQ2B->GetSuperBotTree().GetVertices()[see]->GetAmIConnectedToObject()) {
					if (RDQ2B->GetEndEffectorDockFace() == DOCK_0) {
						FinalFKActorTrans = FTransform(FVector(50, 0, 0))*FinalFKActorTrans;
					}
					else {
						FinalFKActorTrans = FTransform(FVector(-50, 0, 0))*FinalFKActorTrans;
					}
				}
				if (!FinalFKActor) {
					FinalFKActor = GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKActorTrans.GetLocation(), FRotator(FinalFKActorTrans.GetRotation()));
				}
				else {
					FinalFKActor->SetActorTransform(FinalFKActorTrans);
				}
			}
		}
		if (RDQ2B->GetBestTransforms().size() > 0) {
			int gm = RDQ2B->GetGroundModule();
			std::vector<float> sol = RDQ2B->GetSolutionPos();
			int see = RDQ2B->GetSelectedEndEffector();
			if (gm != -1 && RDQ2B->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(sol[3 * see + 0], sol[3 * see + 1], sol[3 * see + 2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQ2B->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform EndModuleTrans =
					SuperbotKinematics::computeTransformToDock(end, RDQ2B->GetEndEffectorDockFace())*
					RDQ2B->GetBestTransforms()[see] * GroundActorTrans;
				FTransform EndModuleTrans2 =
					FTransform(FQuat(FVector(0, 1, 0), M_PI))*
					FTransform(FQuat(FVector(0, 1, 0), M_PI_2))*
					SuperbotKinematics::computeTransformToDock(end, DOCK_3)*
					RDQ2B->GetBestTransforms()[2] * GroundActorTrans;
				if (!TargetFootActor2) {
					//TargetFootActor2 = GetWorld()->SpawnActor<AReferenceFrameActor>((EndModuleTrans2).GetLocation(), FRotator(EndModuleTrans2.GetRotation()));
				}
				else {
					//TargetFootActor2->SetActorTransform(EndModuleTrans2);
				}
				if (!TargetFootActor) {
					TargetFootActor = GetWorld()->SpawnActor<AReferenceFrameActor>((EndModuleTrans).GetLocation(), FRotator(EndModuleTrans.GetRotation()));
				}
				else {
					TargetFootActor->SetActorTransform(EndModuleTrans);
				}

			}
		}
		if (RDQ2B->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = RDQ2B->GetGroundModule();
			if (gm != -1 && RDQ2B->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQ2B->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform TargTrans = RDQ2B->GetTargetTransform()*GroundActorTrans;
				if (RDQ2B->GetEndEffectorDockFace() != RDQ2B->GetGroundDockFace()) {
					TargTrans = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*TargTrans;
				}
				if (!TargetTransformActor) {
					//TargetTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(TargTrans.GetLocation(), FRotator(TargTrans.GetRotation()));
				}
				else {
					//TargetTransformActor->SetActorTransform(TargTrans);
				}
			}
		}
		if (RDQ2B->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = RDQ2B->GetGroundModule();
			if (gm != -1 && RDQ2B->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQ2B->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform ObjectTrans = RDQ2B->GetModuleBaseToObjectTransform()*GroundActorTrans;
				FTransform ActualGTrans = RDQ2B->GetModuleBaseToGroundTransform()*GroundActorTrans;
				ObjectTrans = FTransform(FVector(-50.0 / 2.0, 0, 0))*ObjectTrans;
				if (!ManipObjectTransformActor) {
					//ManipObjectTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(ObjectTrans.GetLocation(),
					//	FRotator(ObjectTrans.GetRotation()));
				}
				else {
					//ManipObjectTransformActor->SetActorTransform(ObjectTrans);
				}

			}
		}
		/*if (RDQ2B->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = RDQ2B->GetGroundModule();
			std::vector<float> sol = RDQ2B->GetSolutionPos();
			int see = RDQ2B->GetSelectedEndEffector();
			if (gm != -1 && RDQ2B->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				for (int i = 0; i < BoundingBoxes.size(); i++) {
					if (BoundingBoxes[i])BoundingBoxes[i]->Destroy();
					BoundingBoxes[i] = NULL;
				}
				BoundingBoxes.clear();
				ModuleMotorVector mvs(RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					RDQ2B->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(RDQ2B->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					RDQ2B->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					RDQ2B->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, RDQ2B->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				for (int i = 0; i < RDQ2B->GetSuperBotTree().GetVertices().size(); i++) {
					FTransform EndModuleTrans = RDQ2B->GetSuperBotTree().GetVertices()[i]->GetTransform()*GroundActorTrans;
					FTransform MInnerEndModuleTrans = FTransform(FVector(30.0, 0.0, 0))*EndModuleTrans;
					FTransform SInnerEndModuleTrans = FTransform(FVector(-30.0, 0.0, 0))*EndModuleTrans;
					SInnerEndModuleTrans = FTransform(FQuat(FVector(1, 0, 0),
						(M_PI / 180.0)*RDQ2B->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[1]))*SInnerEndModuleTrans;
					ABoundingBoxActor* B1 = GetWorld()->SpawnActor<ABoundingBoxActor>((MInnerEndModuleTrans).GetLocation(), FRotator(MInnerEndModuleTrans.GetRotation()));
					B1->SetScale(FVector(0.5, 0.6, 0.6));
					ABoundingBoxActor* B2 = GetWorld()->SpawnActor<ABoundingBoxActor>((SInnerEndModuleTrans).GetLocation(), FRotator(SInnerEndModuleTrans.GetRotation()));
					B2->SetScale(FVector(0.5, 0.6, 0.6));
					BoundingBoxes.push_back(B1);
					BoundingBoxes.push_back(B2);
					ModuleMotorVector currJoints(RDQ2B->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[0],
						RDQ2B->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[1],
						RDQ2B->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[2]);
					FTransform MOuterEndModuleTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
						EndModuleTrans;
					FTransform SOuterEndModuleTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
						EndModuleTrans;
					MOuterEndModuleTrans = FTransform(FVector(-8, 0, 0))*MOuterEndModuleTrans;
					SOuterEndModuleTrans = FTransform(FVector(8, 0, 0))*SOuterEndModuleTrans;
					ABoundingBoxActor* B3 = GetWorld()->SpawnActor<ABoundingBoxActor>((MOuterEndModuleTrans).GetLocation(), FRotator(MOuterEndModuleTrans.GetRotation()));
					B3->SetScale(FVector(0.06, 0.6, 0.6));
					ABoundingBoxActor* B4 = GetWorld()->SpawnActor<ABoundingBoxActor>((SOuterEndModuleTrans).GetLocation(), FRotator(SOuterEndModuleTrans.GetRotation()));
					B4->SetScale(FVector(0.06, 0.6, 0.6));
					BoundingBoxes.push_back(B3);
					BoundingBoxes.push_back(B4);
					if (RDQ2B->GetSuperBotTree().GetVertices()[i]->GetAmIEndEffector()) {
						B1->SetColor(YellowBoundingBoxColor);
					}
					FTransform MOuterLeftTrans = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterEndModuleTrans;
					FTransform MOuterRightTrans = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterEndModuleTrans;
					FTransform SOuterLeftTrans = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterEndModuleTrans;
					FTransform SOuterRightTrans = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterEndModuleTrans;
					ABoundingBoxActor* B5 = GetWorld()->SpawnActor<ABoundingBoxActor>((MOuterLeftTrans).GetLocation(), FRotator(MOuterLeftTrans.GetRotation()));
					ABoundingBoxActor* B6 = GetWorld()->SpawnActor<ABoundingBoxActor>((MOuterRightTrans).GetLocation(), FRotator(MOuterRightTrans.GetRotation()));
					ABoundingBoxActor* B7 = GetWorld()->SpawnActor<ABoundingBoxActor>((SOuterLeftTrans).GetLocation(), FRotator(SOuterLeftTrans.GetRotation()));
					ABoundingBoxActor* B8 = GetWorld()->SpawnActor<ABoundingBoxActor>((SOuterRightTrans).GetLocation(), FRotator(SOuterRightTrans.GetRotation()));
					B5->SetScale(FVector(0.5, 0.6, 0.12));
					B6->SetScale(FVector(0.5, 0.6, 0.12));
					B7->SetScale(FVector(0.5, 0.6, 0.12));
					B8->SetScale(FVector(0.5, 0.6, 0.12));
					BoundingBoxes.push_back(B5);
					BoundingBoxes.push_back(B6);
					BoundingBoxes.push_back(B7);
					BoundingBoxes.push_back(B8);

				}
			}
		}*/
	}
	if (MMQB && EngagedToGround) {
		if (MMQB->GetSuperBotTree().GetVertices().size() > 0) {
			int see = MMQB->GetSelectedEndEffector();
			if (see != -1 && MMQB->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				FTransform FinalFKActorTrans = MMQB->GetSuperBotTree().GetVertices()[see]->GetTransform()*
					SuperbotKinematics::computeTransformToDock((Mod)->GetJointAngles(), D)*
					ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				ModuleMotorVector mvs(MMQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					MMQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					MMQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
					MMQB->GetEndEffectorDockFace())*FinalFKActorTrans;
				if (MMQB->GetSuperBotTree().GetVertices()[see]->GetAmIConnectedToObject()) {
					if (MMQB->GetEndEffectorDockFace() == DOCK_0) {
						FinalFKActorTrans = FTransform(FVector(50,0,0))*FinalFKActorTrans;
					}
					else {
						FinalFKActorTrans = FTransform(FVector(-50, 0, 0))*FinalFKActorTrans;
					}
				}
				if (!FinalFKActor) {
					FinalFKActor = GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKActorTrans.GetLocation(), FRotator(FinalFKActorTrans.GetRotation()));
				}
				else {
					FinalFKActor->SetActorTransform(FinalFKActorTrans);
				}
			}
		}
		if (MMQB->GetBestTransforms().size() > 0) {
			int gm = MMQB->GetGroundModule();
			std::vector<float> sol = MMQB->GetSolutionPos();
			int see = MMQB->GetSelectedEndEffector();
			if (gm != -1 && MMQB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(sol[3 * see + 0], sol[3 * see + 1], sol[3 * see + 2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, MMQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform EndModuleTrans =
					SuperbotKinematics::computeTransformToDock(end, MMQB->GetEndEffectorDockFace())*
					MMQB->GetBestTransforms()[see] * GroundActorTrans;
				if (!TargetFootActor) {
					TargetFootActor = GetWorld()->SpawnActor<AReferenceFrameActor>((EndModuleTrans).GetLocation(), FRotator(EndModuleTrans.GetRotation()));
				}
				else {
					TargetFootActor->SetActorTransform(EndModuleTrans);
				}

			}
		}
		if (MMQB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = MMQB->GetGroundModule();
			if (gm != -1 && MMQB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, MMQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform TargTrans = MMQB->GetTargetTransform()*GroundActorTrans;
				if (MMQB->GetEndEffectorDockFace() != MMQB->GetGroundDockFace()) {
					TargTrans = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*TargTrans;
				}
				if (!TargetTransformActor) {
					//TargetTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(TargTrans.GetLocation(), FRotator(TargTrans.GetRotation()));
				}
				else {
					//TargetTransformActor->SetActorTransform(TargTrans);
				}
			}
		}
		if (MMQB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = MMQB->GetGroundModule();
			if (gm != -1 && MMQB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, MMQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform ObjectTrans = MMQB->GetModuleBaseToObjectTransform()*GroundActorTrans;
				FTransform ActualGTrans = MMQB->GetModuleBaseToGroundTransform()*GroundActorTrans;
				ObjectTrans = FTransform(FVector(-50.0 / 2.0, 0, 0))*ObjectTrans;
				if (!ManipObjectTransformActor) {
					//ManipObjectTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(ObjectTrans.GetLocation(),
					//	FRotator(ObjectTrans.GetRotation()));
				}
				else {
					//ManipObjectTransformActor->SetActorTransform(ObjectTrans);
				}

			}
		}
		/*if (MMQB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = MMQB->GetGroundModule();
			std::vector<float> sol = MMQB->GetSolutionPos();
			int see = MMQB->GetSelectedEndEffector();
			if (gm != -1 && MMQB->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				for (int i = 0; i < BoundingBoxes.size(); i++) {
					if (BoundingBoxes[i])BoundingBoxes[i]->Destroy();
					BoundingBoxes[i] = NULL;
				}
				BoundingBoxes.clear();
				ModuleMotorVector mvs(MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					MMQB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(MMQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					MMQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					MMQB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, MMQB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				for (int i = 0; i < MMQB->GetSuperBotTree().GetVertices().size(); i++) {
					FTransform EndModuleTrans = MMQB->GetSuperBotTree().GetVertices()[i]->GetTransform()*GroundActorTrans;
					FTransform MInnerEndModuleTrans = FTransform(FVector(30.0, 0.0, 0))*EndModuleTrans;
					FTransform SInnerEndModuleTrans = FTransform(FVector(-30.0, 0.0, 0))*EndModuleTrans;
					SInnerEndModuleTrans = FTransform(FQuat(FVector(1, 0, 0),
						(M_PI / 180.0)*MMQB->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[1]))*SInnerEndModuleTrans;
					ABoundingBoxActor* B1 = GetWorld()->SpawnActor<ABoundingBoxActor>((MInnerEndModuleTrans).GetLocation(), FRotator(MInnerEndModuleTrans.GetRotation()));
					B1->SetScale(FVector(0.6, 0.75, 0.75));
					ABoundingBoxActor* B2 = GetWorld()->SpawnActor<ABoundingBoxActor>((SInnerEndModuleTrans).GetLocation(), FRotator(SInnerEndModuleTrans.GetRotation()));
					B2->SetScale(FVector(0.6, 0.75, 0.75));
					BoundingBoxes.push_back(B1);
					BoundingBoxes.push_back(B2);
					ModuleMotorVector currJoints(MMQB->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[0],
						MMQB->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[1],
						MMQB->GetSuperBotTree().GetVertices()[i]->GetJointAngles()[2]);
					FTransform MOuterEndModuleTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
						EndModuleTrans;
					FTransform SOuterEndModuleTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
						EndModuleTrans;
					MOuterEndModuleTrans = FTransform(FVector(-8, 0, 0))*MOuterEndModuleTrans;
					SOuterEndModuleTrans = FTransform(FVector(8, 0, 0))*SOuterEndModuleTrans;
					ABoundingBoxActor* B3 = GetWorld()->SpawnActor<ABoundingBoxActor>((MOuterEndModuleTrans).GetLocation(), FRotator(MOuterEndModuleTrans.GetRotation()));
					B3->SetScale(FVector(0.1, 0.75, 0.75));
					ABoundingBoxActor* B4 = GetWorld()->SpawnActor<ABoundingBoxActor>((SOuterEndModuleTrans).GetLocation(), FRotator(SOuterEndModuleTrans.GetRotation()));
					B4->SetScale(FVector(0.1, 0.75, 0.75));
					BoundingBoxes.push_back(B3);
					BoundingBoxes.push_back(B4);
					FTransform MOuterLeftTrans = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterEndModuleTrans;
					FTransform MOuterRightTrans = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterEndModuleTrans;
					FTransform SOuterLeftTrans = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterEndModuleTrans;
					FTransform SOuterRightTrans = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterEndModuleTrans;
					ABoundingBoxActor* B5 = GetWorld()->SpawnActor<ABoundingBoxActor>((MOuterLeftTrans).GetLocation(), FRotator(MOuterLeftTrans.GetRotation()));
					ABoundingBoxActor* B6 = GetWorld()->SpawnActor<ABoundingBoxActor>((MOuterRightTrans).GetLocation(), FRotator(MOuterRightTrans.GetRotation()));
					ABoundingBoxActor* B7 = GetWorld()->SpawnActor<ABoundingBoxActor>((SOuterLeftTrans).GetLocation(), FRotator(SOuterLeftTrans.GetRotation()));
					ABoundingBoxActor* B8 = GetWorld()->SpawnActor<ABoundingBoxActor>((SOuterRightTrans).GetLocation(), FRotator(SOuterRightTrans.GetRotation()));
					B5->SetScale(FVector(1, 0.75, 0.18));
					B6->SetScale(FVector(1, 0.75, 0.18));
					B7->SetScale(FVector(1, 0.75, 0.18));
					B8->SetScale(FVector(1, 0.75, 0.18));
					BoundingBoxes.push_back(B5);
					BoundingBoxes.push_back(B6);
					BoundingBoxes.push_back(B7);
					BoundingBoxes.push_back(B8);

				}
			}
		}*/

	}


	FKIKBehavior *FKB = NULL;
	if ((Mod)->GetModuleBehavior()->GetName().compare("FKIK") == 0) {
		FKB = (FKIKBehavior*)(Mod)->GetModuleBehavior();
	}
	if (FKB && EngagedToGround) {
		if (FKB->GetSuperBotTree().GetVertices().size() > 0) {
			int see = FKB->GetSelectedEndEffector();
			if (see != -1 && FKB->GetSuperBotTree().GetVertices().size() - 1 >= see) {
				FTransform FinalFKActorTrans = FKB->GetSuperBotTree().GetVertices()[see]->GetTransform()*
					SuperbotKinematics::computeTransformToDock((Mod)->GetJointAngles(), D)*
					ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				ModuleMotorVector mvs(FKB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
					FKB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
					FKB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
				FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
					FKB->GetEndEffectorDockFace())*FinalFKActorTrans;
				if (!FinalFKActor) {
					FinalFKActor = GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKActorTrans.GetLocation(), FRotator(FinalFKActorTrans.GetRotation()));
				}
				else {
					FinalFKActor->SetActorTransform(FinalFKActorTrans);
				}
			}
		}
		if (FKB->GetBestTransforms().size() > 0) {
			int gm = FKB->GetGroundModule();
			std::vector<float> sol = FKB->GetSolutionPos();
			int see = FKB->GetSelectedEndEffector();
			if (gm != -1 && FKB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				ModuleMotorVector end(sol[3 * see + 0], sol[3 * see + 1], sol[3 * see + 2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, FKB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform EndModuleTrans =
					SuperbotKinematics::computeTransformToDock(end, FKB->GetEndEffectorDockFace())*
					FKB->GetBestTransforms()[see] * GroundActorTrans;
				if (!TargetFootActor) {
					TargetFootActor = GetWorld()->SpawnActor<AReferenceFrameActor>((EndModuleTrans).GetLocation(), FRotator(EndModuleTrans.GetRotation()));
				}
				else {
					TargetFootActor->SetActorTransform(EndModuleTrans);
				}

			}
		}
		if (FKB->GetSuperBotTree().GetVertices().size() > 0) {
			int gm = FKB->GetGroundModule();
			if (gm != -1 && FKB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
				ModuleMotorVector mvs(FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
					FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
					FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
				FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs, FKB->GetGroundDockFace())*ASuperBotModule::SuperbotFix*(Mod)->GetMasterInnerMesh()->GetComponentTransform();
				FTransform TargTrans = FKB->GetTargetTransform()*GroundActorTrans;
				if (FKB->GetEndEffectorDockFace() != FKB->GetGroundDockFace()) {
					TargTrans = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*TargTrans;
				}
				if (!TargetTransformActor) {
					TargetTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(TargTrans.GetLocation(), FRotator(TargTrans.GetRotation()));
				}
				else {
					TargetTransformActor->SetActorTransform(TargTrans);
				}
			}
		}
	}
}


