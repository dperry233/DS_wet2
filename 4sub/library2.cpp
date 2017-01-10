/*
 * library2.cpp
 *
 *  Created on: Jan 4, 2017
 *      Author: user
 */

#include "library2.h"
#include "magicManager.h"
#include <iostream>
#include <exception>

void* Init(int n,int* levels) {
	if(n<2){
		return NULL;
	}
	MagicManager* manager;
	try {
		manager = new MagicManager(n,levels);
	} catch (std::exception& e) {
		return NULL;
	}
	return manager;
}

StatusType AddMagizoologist(void *DS, int magiID, int magiLevel) {
	if (NULL == DS || magiID <= 0 || magiLevel <= 0) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->addMagi(magiID,magiLevel);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}


StatusType RemoveMagizoologist(void *DS, int magiID){
	if (NULL == DS || magiID <= 0 ) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->removeMagi(magiID);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}



StatusType AssignMagizoologistToCreature(void *DS, int creatureID) {
	if (NULL == DS || creatureID < 0 ) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (creatureID >= manager->animalAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->assignMagi(creatureID);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}

StatusType RemoveBarrier(void *DS, int creature1, int creature2) {
	if (NULL == DS || creature1 < 0 || creature2 < 0) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (creature1 >= manager->animalAmount || creature2 >= manager->animalAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->removeBarrier(creature1,creature2);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}


StatusType ReleaseMagizoologist(void *DS, int magiID) {
	if (NULL == DS || magiID <= 0) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}

	ManagerResult result = manager->releaseMagi(magiID);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}


StatusType GetCreatureOfMagi(void *DS, int magiID, int* creatureID) {
	if (NULL == DS || magiID <= 0 || !(creatureID)) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->getCreatureOfMagi(magiID,creatureID);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}

StatusType AreCreaturesInSameArea(void *DS, int creature1, int creature2,  bool* sameArea) {
	if (NULL == DS || creature1 < 0 || creature2 < 0 || !(sameArea) ) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (creature1 >= manager->animalAmount || creature2 >= manager->animalAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->areCreaturesSameArea(creature1,creature2,sameArea);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}

StatusType GetSizeOfArea(void *DS, int creatureID, int* sizeOfArea) {
	if (NULL == DS || creatureID < 0  || !(sizeOfArea) ) {
		return INVALID_INPUT;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (creatureID >= manager->animalAmount ) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->getSizeOfArea(creatureID,sizeOfArea);
	if (result == MANAGER_ALLOCATION_ERROR) {
		return ALLOCATION_ERROR;
	}
	if (result == MANAGER_FAILURE) {
		return FAILURE;
	}
	if (result == MANAGER_INVALID_INPUT) {
		return INVALID_INPUT;
	}
	if (result == MANAGER_SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}


void Quit(void** DS) {
	if (NULL == DS) {
		return ;
	}
	MagicManager* manager;
	try {
		manager = (MagicManager*) *DS;
	} catch (std::exception& e) {
		return ;
	}
	delete manager;
	*DS=NULL;
}



