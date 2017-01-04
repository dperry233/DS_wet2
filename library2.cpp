/*
 * library2.cpp
 *
 *  Created on: Jan 4, 2017
 *      Author: user
 */

#include "library2.h"
#include "TrollManager2.h"
#include <iostream>
#include <exception>

void* Init(int n) {
	if(n<2){
		return NULL;
	}
	TrollManager* manager;
	try {
		manager = new TrollManager(n);
	} catch (std::exception& e) {
		return NULL;
	}
	return manager;
}

StatusType AddTroll(void* DS, int trollID, int strength) {
	if (NULL == DS || trollID < 0 || strength < 0) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->addTroll(trollID, strength);
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

StatusType AssignTroll(void* DS, int trollID, int team) {
	if (NULL == DS || trollID < 0 || team < 0) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (team >= manager->teamAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->assignTroll(trollID, team);
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

StatusType JoinGroups(void* DS, int team1, int team2) {
	if (NULL == DS || team1 < 0 || team2 < 0) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (team1 >= manager->teamAmount || team2 >= manager->teamAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->joinGroups(team1, team2);
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

StatusType GetGroup(void* DS, int trollID, int* group) {
	if (NULL == DS || trollID < 0 || !(group)) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->getGroup(trollID, group);
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

StatusType TeamUpgrade(void* DS, int teamID, int factor) {
	if (NULL == DS || teamID < 0 || factor < 1) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (teamID >= manager->teamAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->teamUpgrade(teamID, factor);
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

StatusType GetStrongestTroll(void* DS, int groupID, int* troll) {
	if (NULL == DS || groupID < 0 || !(troll)) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	if (groupID >= manager->teamAmount) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->getStrongestTroll(groupID, troll);
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

StatusType GetNumOfTrollsInRange(void* DS, int min, int max, int* num) {
	if (NULL == DS || min < 0 || min >= max || !(num)) {
		return INVALID_INPUT;
	}
	TrollManager* manager;
	try {
		manager = (TrollManager*) DS;
	} catch (std::exception& e) {
		return INVALID_INPUT;
	}
	ManagerResult result = manager->GetNumOfTrollsInRange(min, max, num);
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
	TrollManager* manager;
	try {
		manager = (TrollManager*) *DS;
	} catch (std::exception& e) {
		return ;
	}
	delete manager;
	*DS=NULL;
}



