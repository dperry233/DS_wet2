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
	animalUF* teamsAndGroups;
	magiHash<Magi>* trollById;
	AVLTree<Magi, Magi>* availableMagiTree;
	RAVLTree<Magi, Magi>* workingMagiTree;


	int animalAmount;
	MagicManager(int n){

		this->teamsAndGroups = new unionFind(n);
		this->trollTree =  new RAVLTree<troll, troll>;

		this->trollById = new magiHash<Magi>(n);
		this->animalAmount=n;

	}






	~TrollManager(){
		delete trollById;
		delete teamsAndGroups;
		delete trollTree;

	}

	ManagerResult addTroll(int id ,int strength){
		troll tmpTroll(id,strength);
		if (trollById->doesKeyExists(id)){
			return MANAGER_FAILURE;
		}
		troll newTroll =  troll(id,strength);
		trollById->insertNode(id,newTroll);
		trollTree->insertData(newTroll,newTroll);
		return MANAGER_SUCCESS;
	}

	ManagerResult assignTroll(int ID, int team){
		if (!trollById->doesKeyExists(ID)){
			return MANAGER_FAILURE;
		}
		troll t = trollById->getValue(ID);
		if (t.team == team){
			return MANAGER_SUCCESS;
		}
		if (t.team != NO_TEAM){
			return MANAGER_FAILURE;
		}
		t.team=team;
		trollById->getValue(ID).team=team;
		trollTree->getValue(t)->team=team;
		rTree* group =teamsAndGroups->find(team);
		if(group->getStrongest()<=t.strength){
			if(group->getStrongest()<t.strength || group->getWhoIsstrongest()>t.trollId) {
				group->updateStrongest(t.strength);
				group->updateWhoIsStrongest(t.trollId);
			}
		}
		return MANAGER_SUCCESS;

	}


	ManagerResult joinGroups(int teamId1, int teamId2){

		if( teamId1 >=teamAmount || teamId1<0 || teamId2 >=teamAmount || teamId2<0 ) {
			return MANAGER_INVALID_INPUT;
		}

		if (teamsAndGroups->find(teamId1)==teamsAndGroups->find(teamId2)){
			return MANAGER_FAILURE;
		}

		teamsAndGroups->unionTeams(teamId1,teamId2);
		return MANAGER_SUCCESS;

	}

	ManagerResult getGroup(int trollID, int* group){
		if (group == NULL){
			return MANAGER_INVALID_INPUT;
		}
		if (!trollById->doesKeyExists(trollID)){
			return MANAGER_FAILURE;
		}
		troll t = trollById->getValue(trollID);
		if (t.team == NO_TEAM){
			return MANAGER_FAILURE;
		}
		int team= t.team;
		rTree* root = teamsAndGroups->find(team);
		*group=(root->getGroup());
		return MANAGER_SUCCESS;
	}


	void updateArray(troll* array,int i ,int factor){

		while(i>=0){

			array->strength*=(factor);
			array++;
			i--;

		}

	}

	void mergeArrays(troll* updated,troll* notUpdated,troll* newArray ,int size){
		troll* ptr1=updated;
		troll* ptr2=notUpdated;
		for (int i=0; i<size ; i++){
			if ((ptr1)->trollId== NO_TROLL){
				newArray[i]=*ptr2;
				ptr2++;
				continue;
			}else if((ptr2)->trollId==NO_TROLL){
				newArray[i]=*ptr1;
				ptr1++;
				continue;
			}
			if (*ptr1>*ptr2){
				newArray[i]=*ptr2;
				ptr2++;
			}
			else{
				newArray[i]=*ptr1;
				ptr1++;
			}
		}
	}


	void redoTree(RAVLNode<troll,troll>* node,troll* array1, int* i, int size) {

		if (!node) {
			return;
		}

		redoTree(node->leftSon,array1, i,size);

		node->getData().strength=(array1[*i].strength);
		node->getData().team=(array1[*i].team);
		node->getData().trollId=(array1[*i].trollId);
		node->key=node->value;
		(*i)++;
		redoTree(node->rightSon,array1,i ,size);
	}


	void redoHash(Hash<troll>* trolls, troll* array,int size){

		int i=0;
		while(i<size){
			if (array[i].trollId == NO_TROLL){
				i++;
				continue;
			}
			(trolls->getValue(array[i].trollId)).strength=(array[i].strength);
			i++;
		}

	}


	ManagerResult teamUpgrade(int teamID ,int factor){



		int size=this->trollTree->size;
		int i=0,j=0;
		troll array1[size];
		troll array2[size];
		troll array3[size];
		inorderToArrayIf(trollTree->rootNode,array1,array2,&i,&j,teamID);
		if(i==0){
			return MANAGER_SUCCESS;
		}
		int strongID=NO_TROLL;
		int strongStrength=NO_TROLL;
		if(i>0){
			if((array1+i-1)!=NULL){
				if(array1[i-1].trollId!=NO_TROLL){
					strongID= array1[i-1].trollId;
					strongStrength= array1[i-1].strength;
				}
			}
		}
		updateArray(array1,i,factor);


		mergeArrays(array1,array2,array3,size);
		i=0;
		redoTree(this->trollTree->rootNode,array3,&i,size);
		redoHash(this->trollById,array1,size);

		rTree* root = teamsAndGroups->find(teamID);
		strongStrength = strongStrength*factor;
		if(strongID!=NO_TROLL){
			if( strongStrength >= root->getStrongest() ){
				if (strongStrength > root->getStrongest() || strongID < root->getWhoIsstrongest() ){
					root->updateStrongest(strongStrength);
					root->updateWhoIsStrongest(strongID);
				}
			}
		}

		return MANAGER_SUCCESS;
	}



	void inorderToArrayIf(RAVLNode<troll,troll>* node,troll* array1,troll* array2
			, int* i,int* j,int team) {

		if (!node) {
			return;
		}

		inorderToArrayIf(node->leftSon,array1,array2,i,j,team);

		if(node->getData().team==team){
			array1[*i]=node->getData();
			(*i)++;
		}else{
			array2[*j]=node->getData();
			(*j)++;
		}
		inorderToArrayIf(node->rightSon,array1,array2,i,j,team);
	}



	ManagerResult getStrongestTroll(int group, int* troll){
		if (troll==NULL){
			return MANAGER_INVALID_INPUT;
		}
		rTree* t = teamsAndGroups->getGroupRoot(group);
		if(t==NULL){
			return MANAGER_FAILURE;
		}
		if(t->getStrongest()<0){
			return MANAGER_FAILURE;
		}
		*troll=(t->getWhoIsstrongest());
		return MANAGER_SUCCESS;


	}

	ManagerResult GetNumOfTrollsInRange( int min, int max, int* num){
		if (min<0 || min>=max || !num){
			return MANAGER_INVALID_INPUT;
		}
		RAVLNode<troll,troll>* trollMin=this->trollTree->getBiggestSmallerThan(trollTree->rootNode, min);
		RAVLNode<troll,troll>* trollMax=this->trollTree->getSmallestBiggerThan(trollTree->rootNode, max);
		if (!trollMin || !trollMax){
			*num=0;
			return MANAGER_SUCCESS;
		}
		int minIndex= trollTree->calcNodeIndex(trollMin);
		if (trollMin->key.strength>min){
			minIndex=minIndex-1;
		}
		int maxIndex= trollTree->calcNodeIndex(trollMax);
		if (trollMax->key.strength<=max){
			maxIndex=maxIndex+1;
		}
		*num=maxIndex-minIndex-1;
		return MANAGER_SUCCESS;
	}
};


#endif /* MAGICMANAGER_H_ */
