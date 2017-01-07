/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2016                                          */
/*                                                                         */
/* Homework : Wet 2                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <string>
#include "library2.h"
#include <cstring>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INIT_CMD = 0,
    ADDMAGI_CMD = 1,
    REMOVEMAGI_CMD = 2,
    REMOVEBARRIER_CMD = 3,
    ASSIGNMAGI_CMD = 4,
    RELEASEMAGI_CMD = 5,
    GETCREATURE_CMD = 6,
    SAMEAREA_CMD = 7,
    SIZEOFAREA_CMD = 8,
    QUIT_CMD = 9
} commandType;

static const int numActions = 10;
static const char *commandStr[] = { "Init", "AddMagi", "RemoveMagi",
                                    "RemoveBarrier", "AssignMagi", "ReleaseMagi",
                                    "GetCreature", "SameArea", "SizeOfArea", "Quit" };

static const char* ReturnValToStr(int val) {
    switch (val) {
        case (SUCCESS):
            return "Success";
        case (FAILURE):
            return "Failure";
        case (ALLOCATION_ERROR):
            return "Allocation_error";
        case (INVALID_INPUT):
            return "Invalid_input";
        default:
            return "";
    }
}

static const char* BoolToStr(bool val) {
    return val ? "True" : "False";
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
//#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
    error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
    char buffer[MAX_STRING_INPUT_SIZE];
    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}


/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
                                const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            printf("%s", command);
        return (COMMENT_CMD);
    };
    for (int index = 0; index < numActions; index++) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType) index);
        };
    };
    return (NONE_CMD);
}


/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddMagi(void* DS, const char* const command);
static errorType OnRemoveMagi(void* DS, const char* const command);
static errorType OnRemoveBarrier(void* DS, const char* const command);
static errorType OnAssignMagi(void* DS, const char* const command);
static errorType OnReleaseMagi(void* DS, const char* const command);
static errorType OnGetCreature(void* DS, const char* const command);
static errorType OnSameArea(void* DS, const char* const command);
static errorType OnSizeOfArea(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);


/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    commandType command_val = CheckCommand(command, &command_args);

    switch (command_val) {
        case (INIT_CMD):
            rtn_val = OnInit(&DS, command_args);
            break;
        case (ADDMAGI_CMD):
            rtn_val = OnAddMagi(DS, command_args);
            break;
        case (REMOVEMAGI_CMD):
            rtn_val = OnRemoveMagi(DS, command_args);
            break;
        case (REMOVEBARRIER_CMD):
            rtn_val = OnRemoveBarrier(DS, command_args);
            break;
        case (ASSIGNMAGI_CMD):
            rtn_val = OnAssignMagi(DS, command_args);
            break;
        case (RELEASEMAGI_CMD):
            rtn_val = OnReleaseMagi(DS, command_args);
            break;
        case (GETCREATURE_CMD):
            rtn_val = OnGetCreature(DS, command_args);
            break;
        case (SAMEAREA_CMD):
            rtn_val = OnSameArea(DS, command_args);
            break;
        case (SIZEOFAREA_CMD):
            rtn_val = OnSizeOfArea(DS, command_args);
            break;
        case (QUIT_CMD):
            rtn_val = OnQuit(&DS, command_args);
            break;
        case (COMMENT_CMD):
            rtn_val = error_free;
            break;
        case (NONE_CMD):
            rtn_val = error;
            break;
        default:
            assert(false);
    };
    return (rtn_val);
}


int INIT_n;

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS,const char* const command) {
    if (isInit) {
        printf("Init was already called.\n");
        return (error_free);
    };
    isInit = true;

    ValidateRead( sscanf(command, "%d",&INIT_n), 1, "Init failed.\n");
    int* levels = new int[INIT_n];
    char c[MAX_STRING_INPUT_SIZE];
    strcpy(c,command);
    char* l = strtok(c ," ");
    for (int i = 0; i < INIT_n; ++i) {
        l = strtok(NULL ," ");
        ValidateRead( sscanf(l, " %d",levels+i), 1, "Init failed.\n");
    }



    *DS = Init(INIT_n,levels);
    if (*DS == NULL) {
        printf("Init failed.\n");
        return (error);
    };
    printf("Init done.\n");
    delete [] levels;
    return error_free;
}

/***************************************************************************/
/* OnAddMagi                                                          */
/***************************************************************************/
static errorType OnAddMagi(void* DS, const char* const command) {
    int magiID;
    int level;
    ValidateRead( sscanf(command, "%d %d",&magiID,&level), 2,
                  "AddMagi failed.\n");
    StatusType res = AddMagizoologist(DS, magiID, level);

    printf("AddMagi: %s\n", ReturnValToStr(res));

    return error_free;
}

/***************************************************************************/
/* OnRemoveMagi                                                       */
/***************************************************************************/
static errorType OnRemoveMagi(void* DS, const char* const command) {
    int magiID;
    ValidateRead( sscanf(command, "%d",&magiID), 1,
                  "RemoveMagi failed.\n");
    StatusType res = RemoveMagizoologist(DS, magiID);

    printf("RemoveMagi: %s\n", ReturnValToStr(res));

    return error_free;
}

/***************************************************************************/
/* OnRemoveBarrier                                                       */
/***************************************************************************/
static errorType OnRemoveBarrier(void* DS, const char* const command) {
    int creature1;
    int creature2;
    ValidateRead( sscanf(command, "%d %d",&creature1,&creature2), 2,
                  "RemoveBarrier failed.\n");
    StatusType res = RemoveBarrier(DS, creature1, creature2);

    printf("RemoveBarrier: %s\n", ReturnValToStr(res));

    return error_free;
}

/***************************************************************************/
/* OnAssignMagi                                                         */
/***************************************************************************/
static errorType OnAssignMagi(void* DS, const char* const command) {
    int creatureId;
    ValidateRead( sscanf(command, "%d",&creatureId), 1,
                  "AssignMagi failed.\n");
    StatusType res = AssignMagizoologistToCreature(DS, creatureId);

    printf("AssignMagi: %s\n", ReturnValToStr(res));

    return error_free;
}

/***************************************************************************/
/* OnReleaseMagi                                                         */
/***************************************************************************/
static errorType OnReleaseMagi(void* DS, const char* const command) {
    int magiID;
    ValidateRead( sscanf(command, "%d",&magiID), 1,
                  "ReleaseMagi failed.\n");
    StatusType res = ReleaseMagizoologist(DS, magiID);

    printf("ReleaseMagi: %s\n", ReturnValToStr(res));

    return error_free;
}

/***************************************************************************/
/* OnGetCreature                                                 */
/***************************************************************************/
static errorType OnGetCreature(void* DS, const char* const command) {
    int magiID;
    ValidateRead( sscanf(command, "%d",&magiID), 1,
                  "GetCreature failed.\n");
    int creature;
    StatusType res = GetCreatureOfMagi(DS, magiID, &creature);

    if (res != SUCCESS) {
        printf("GetCreature: %s\n", ReturnValToStr(res));
    } else {
        printf("GetCreature: %s %d\n", ReturnValToStr(res),
               creature);
    }

    return error_free;
}

/***************************************************************************/
/* OnSameArea                                                 */
/***************************************************************************/
static errorType OnSameArea(void* DS, const char* const command) {
    int creature1;
    int creature2;
    ValidateRead( sscanf(command, "%d %d",&creature1, &creature2), 2,
                  "SameArea failed.\n");
    bool sameArea;
    StatusType res = AreCreaturesInSameArea(DS, creature1, creature2, &sameArea);

    if (res != SUCCESS) {
        printf("SameArea: %s\n", ReturnValToStr(res));
    } else {
        printf("SameArea: %s %s\n", ReturnValToStr(res),
               BoolToStr(sameArea));
    }

    return error_free;
}

/***************************************************************************/
/* OnSizeOfArea                                                 */
/***************************************************************************/
static errorType OnSizeOfArea(void* DS, const char* const command) {
    int creatureID;
    ValidateRead( sscanf(command, "%d",&creatureID), 1,
                  "SizeOfArea failed.\n");
    int size;
    StatusType res = GetSizeOfArea(DS, creatureID, &size);

    if (res != SUCCESS) {
        printf("SizeOfArea : %s\n", ReturnValToStr(res));
    } else {
        printf("SizeOfArea : %s %d\n", ReturnValToStr(res),
               size);
    }

    return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if (*DS != NULL) {
        printf("Quit failed.\n");
        return (error);
    };
    isInit = false;
    printf("Quit done.\n");

    return error_free;
}

#ifdef __cplusplus
}
#endif