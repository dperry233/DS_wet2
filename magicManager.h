/*
 * magicManager.h
 *
 *  Created on: Jan 4, 2017
 *      Author: user
 */

#ifndef MAGICMANAGER_H_
#define MAGICMANAGER_H_

#include "RAVLTree.h"
#include "MagiHash.h"
#include "avlTree.h"
#include "animalUnionFind.h"

#include <iostream>

typedef enum {
	MANAGER_SUCCESS, MANAGER_ALLOCATION_ERROR, MANAGER_FAILURE,MANAGER_INVALID_INPUT
} ManagerResult;
class MagicManager {
private:



public:
	animalUF* animalZoneUF;
	magiHash* magiIdHash;
	AVLTree<int, Magi>* allMagiTree;
	RAVLTree<Magi, Magi>* availableMagiTree;
	//int* levelsArray; //comment

	int animalAmount;
	MagicManager(int n,int* levels){

		this->animalZoneUF = new animalUF(n,levels);
		this->availableMagiTree =  new RAVLTree<Magi, Magi>;
		this->allMagiTree =  new AVLTree<int, Magi>;

		this->magiIdHash = new magiHash;
		this->animalAmount=n;
		//this->levelsArray= levels;
	}






	~MagicManager(){
		delete magiIdHash;
		delete animalZoneUF;
		delete allMagiTree;
		delete availableMagiTree;
	}

	ManagerResult addMagi(int id ,int MagiLevel){
		if(id<=0 || MagiLevel<=0){
			return MANAGER_INVALID_INPUT;
		}

			if (allMagiTree->findIfValueExists(id))
			{
				return MANAGER_FAILURE;
			}
		Magi newMagi =  Magi(id,MagiLevel);
		allMagiTree->insertData(id,newMagi);
		//magiIdHash->insert(allMagiTree->getValue(id));
		availableMagiTree->insertData(newMagi,newMagi);
		//consider allocation success checks
		return MANAGER_SUCCESS;
	}


	ManagerResult removeMagi(int id ){

		if (!allMagiTree->findIfValueExists(id)){
			return MANAGER_FAILURE;
		}
		this->releaseMagi(id);

		this->availableMagiTree->removeValue(*allMagiTree->getValue(id));


		magiIdHash->eraseMagi(id);
		allMagiTree->removeValue(id);

		return MANAGER_SUCCESS;
	}


	ManagerResult assignMagi(int creatureId){
		if( creatureId >=animalAmount || creatureId<0  ) {
			return MANAGER_INVALID_INPUT;
		}
		int levelOfArea=0;
		animalZoneUF->getLevelofArea(creatureId,&levelOfArea);

		Magi* youngest= availableMagiTree->findYoungestBiggerThan(levelOfArea);
		if(youngest){
			int youngestId=youngest->getId();
			availableMagiTree->removeValue(*youngest);
			(allMagiTree->getValue(youngestId))->setBeast(creatureId);
			magiIdHash->insert(allMagiTree->getValue(youngestId));
		}else{
			return MANAGER_FAILURE;
		}


		return MANAGER_SUCCESS;

	}


	ManagerResult removeBarrier(int creature1, int creature2){



		if( creature1 >=animalAmount || creature1<0 || creature2 >=animalAmount || creature2<0 ) {
			return MANAGER_INVALID_INPUT;
		}
		bool isSameArea=false;
		animalZoneUF->sameArea(creature1,creature2,&isSameArea);
		if (isSameArea){
			return MANAGER_FAILURE;
		}
		animalZoneUF->removeBarrier(creature1,creature2);

		return MANAGER_SUCCESS;

	}

	ManagerResult releaseMagi(int magiId){
		if(magiId<=0){
			return MANAGER_INVALID_INPUT;
		}
		if (!allMagiTree->findIfValueExists(magiId)){
			return MANAGER_FAILURE;
		}
		Magi* currentMagi=allMagiTree->getValue(magiId);
		if(availableMagiTree->findIfValueExists(*currentMagi)){
			return MANAGER_FAILURE;
		}
		availableMagiTree->insertData(*currentMagi,*currentMagi);
		//allMagiTree->getValue(magiId)->setBeast(-1);
		magiIdHash->eraseMagi(magiId);


		return MANAGER_SUCCESS;

	}








	ManagerResult getCreatureOfMagi(int MagiID, int* creatureId){
		if (creatureId == NULL ||MagiID<=0){
			return MANAGER_INVALID_INPUT;
		}
		if(magiIdHash->findMagi(MagiID)==-1){
			return MANAGER_FAILURE;
		}
		int tmpId=-2;
		magiIdHash->getCreature(MagiID,&tmpId);
		if(tmpId==-1){
			return MANAGER_FAILURE;
		}
		*creatureId=tmpId;


		return MANAGER_SUCCESS;
	}


	ManagerResult areCreaturesSameArea(int creature1, int creature2,bool* SameArea){



			if( creature1 >=animalAmount || creature1<0 || creature2 >=animalAmount || creature2<0 ) {
				return MANAGER_INVALID_INPUT;
			}
			if(!SameArea){
				return MANAGER_INVALID_INPUT;
			}
			bool isSameArea=false;
			animalZoneUF->sameArea(creature1,creature2,&isSameArea);

			*SameArea=isSameArea;

			return MANAGER_SUCCESS;

		}

	ManagerResult getSizeOfArea(int creature1,int* SizeOfArea){



			if( creature1 >=animalAmount || creature1<0 ) {
				return MANAGER_INVALID_INPUT;
			}
			if(!SizeOfArea){
				return MANAGER_INVALID_INPUT;
			}
			int size;
			 animalZoneUF->getSizeofArea(creature1,&size);
			 *SizeOfArea=size;



			return MANAGER_SUCCESS;

		}



};


#endif /* MAGICMANAGER_H_ */
