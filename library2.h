/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet  2                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library2.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET2_
#define _234218_WET2_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3

} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initializes the system with n creatures.
 * Input:         n - number of creatures.
 *                levels - pointer to an array that holds the risk level of each creature.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void* Init(int n,int* levels);


/* Description:   Add a magizoologist to the data structure.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The ID of the magizoologist.
 *                magiLevel - Witchcraft level of the magizoologist.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or magiID<=0 or magiLevel<=0.
 *                FAILURE - If a magizoologist with magiID already in the system, or in the case of any other problem.
 *                SUCCESS - Otherwise.
 */
StatusType AddMagizoologist(void *DS, int magiID, int magiLevel);


/* Description:   Remove a magizoologist from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The ID of the magizoologis
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or magiID<=0.
 *                FAILURE - If a magizoologist with this ID does not exist in the system, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType RemoveMagizoologist(void *DS, int magiID);


/* Description:   Remove the barrier between the area of two creatures.
 * Input:         DS - A pointer to the data structure.
 *                creature1 - The identifier of the 1st creature.
 *                creature2 - The identifier of the 2nd creature.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or either creature1 or creature2 are illegal creatures numbers.
 *                FAILURE - If both creatures belong to the same area, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType RemoveBarrier(void *DS, int creature1, int creature2);


/* Description:   Assign a magizoologist to attend the creature with the ID creature.
 *                The function will assign the magizoologist with the minimal seniority from those who
 *                have witchcraft level greater then the risk level of the area.
 * Input:         DS - A pointer to the data structure.
 *                creatureID - The identifier of the creature to be attended.
 * Output:        group - The identifier of the group.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or creatureID is an illegal creature numbers.
 *                FAILURE - If there is no free magizoologist with witchcraft level
 *                          greater then the risk level of the area.
 *                SUCCESS - Otherwise.
 */
StatusType AssignMagizoologistToCreature(void *DS, int creatureID);


/* Description:   Release the magizoologist with the ID magiID from attending his creature.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The magi to release.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 * 				  INVALID_INPUT - If DS==NULL or magiID<=0.
 * 				  FAILURE - If there is no magizoologist with ID magiID or in case that this
 * 				            magizoologist have no creature to attend.
 *                SUCCESS - Otherwise.
 */
StatusType ReleaseMagizoologist(void *DS, int magiID);


/* Description:   Return the ID of the creature that the magizoologist with the ID magiID is responsible of.
 * Input:         DS - A pointer to the data structure.
 *                magiID - The identifier of the magizoologist.
 * Output:        creatureID - the creature that the magizoologist is responsible of.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, magiID<=0 or creatureID==NULL.
 * 				  FAILURE - If there is no magizoologist with ID magiID or in case that this
 * 				            magizoologist have no creature to attend.
 *                SUCCESS - Otherwise.
 */
StatusType GetCreatureOfMagi(void *DS, int magiID, int* creatureID);


/* Description:   Check whether creature1 and creature2 are in the same area.
 * Input:         DS - A pointer to the data structure.
 *                creature1 - The first creature to check.
 *                creature2 - The second creature to check.
 * Output:        sameArea - The result of the comparison between creature1 area to creature2 area.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, either creature1 or creature2 are illegal creatures numbers
 *                                or sameArea == NULL.
 * 				  FAILURE - In case of any problem.
 *                SUCCESS - Otherwise.
 */
StatusType AreCreaturesInSameArea(void *DS, int creature1, int creature2,  bool* sameArea);


/* Description:   Return the number of creatures in the area of the creature with the ID creatureID.
 * Input:         DS - A pointer to the data structure.
 *                creatureID - The creature to check.
 * Output:        sizeOfArea - The number of animals in the area of the creature with the ID creatureID.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, creatureID is an illegal creature numbers or sameArea == NULL.
 * 				  FAILURE - In case of any problem.
 *                SUCCESS - Otherwise.
 */
StatusType GetSizeOfArea(void *DS, int creatureID, int* sizeOfArea);

/* Description:   Quits and deletes the database.
 *                The variable pointed by DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);





#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET2_ */