#include "course_manager.h"
#include "ex3.h"

#define MAX_WORDS_IN_LINE 7

#define ERROR_AND_EXIT(error){ \
	ex3PrintErrorMessage(error_channel,error); \
	return 0; \
}

static void closeFiles(FILE **input, FILE **output){
    if(*input != NULL && *input != stdin){
        fclose(*input);
    }
    if(*output != NULL && *output != stdout){
        fclose(*output);
    }
}

static bool loadFile(FILE **input_channel, FILE **output_channel, char* flag,
		char* file_name,EX3ErrorCode* error_code){
	if(strcmp(flag,"-i")==0){
		*input_channel = fopen(file_name,"r");
		if(!*input_channel){
			*error_code = EX3_CANNOT_OPEN_FILE;
			return false;
		}
	}else if(strcmp(flag,"-o")==0){
		*output_channel = fopen(file_name,"w+");
		if(!*output_channel){
			*error_code = EX3_CANNOT_OPEN_FILE;
			return false;
		}
	}else{
		*error_code = EX3_INVALID_COMMAND_LINE_PARAMETERS;
		return false;
	}
	return true;
}

static bool convertError(CMResult cm_result, FILE *error_channel){
	if(cm_result == CM_OUT_OF_MEMORY) ERROR_AND_EXIT(EX3_OUT_OF_MEMORY);
	EX3ErrorCode error;
	switch(cm_result){
	case CM_INVALID_PARAMETERS: error = EX3_INVALID_PARAMETERS;
	break;
	case CM_NOT_LOGGED_IN: error = EX3_NOT_LOGGED_IN;
	break;
	case CM_ALREADY_LOGGED_IN: error = EX3_ALREADY_LOGGED_IN;
	break;
	case CM_STUDENT_DOES_NOT_EXIST: error = EX3_STUDENT_DOES_NOT_EXIST;
	break;
	case CM_STUDENT_ALREADY_EXISTS: error = EX3_STUDENT_ALREADY_EXISTS;
	break;
	case CM_NOT_FRIEND: error = EX3_NOT_FRIEND;
	break;
	case CM_ALREADY_FRIEND: error = EX3_ALREADY_FRIEND;
	break;
	case CM_NOT_REQUESTED: error = EX3_NOT_REQUESTED;
	break;
	case CM_ALREADY_REQUESTED: error = EX3_ALREADY_REQUESTED;
	break;
	case CM_COURSE_DOES_NOT_EXIST: error = EX3_COURSE_DOES_NOT_EXIST;
	break;
	default: break;
	}
	if(cm_result != CM_SUCCESS){
		ex3PrintErrorMessage(error_channel, error);
	}
	return true;
}

static char** makeStringsArray(int size){
	char **array = (char **)malloc(sizeof(*array)*size);
	if(!array) return NULL;
	for(int i=0; i<size; i++){
		array[i] = (char*)malloc(sizeof(char)*(MAX_LEN+1));
		if(!array[i]){
			for(int j=0; j<i; j++){
				free(array[j]);
			}
			free(array);
			return NULL;
		}
		strcpy(array[i],"");
	}
	return array;
}
static void freeStringArray(char** array, int size){
	if(!array) return;
	for(int i=0; i<size; i++){
		free(array[i]);
	}
	free(array);
}

static CMResult subCommandGradeSheet(CourseManager system, char** command){
	CMResult result = CM_SUCCESS;
	if(strcmp(command[1],"add")==0){
		result = gradeSheetAdd(system,atoi(command[2]),atoi(command[3]),
				command[4],atoi(command[5]));
	}
	if(strcmp(command[1],"remove")==0){
		result = gradeSheetRemove(system,atoi(command[2]),atoi(command[3]));
	}
	if(strcmp(command[1],"update")==0){
		result = gradeSheetUpdate(system,atoi(command[2]),atoi(command[3]));
	}
	return result;
}

static CMResult subCommandReport(CourseManager system,char** command,
		FILE* output_channel){
	CMResult result = CM_SUCCESS;
	if(strcmp(command[1],"faculty_request")==0){
		result = reportFacultyRequest(system,getID(getLogin(system)),
				atoi(command[2]),command[3],output_channel);
	}
	if(strcmp(command[1],"reference")==0){
		result = reportReference(system,getID(getLogin(system)),
				atoi(command[2]),atoi(command[3]),output_channel);
	}
	if(strcmp(command[1],"full")==0){
		result =  printFullGradeSheet(system,output_channel);
	}
	if(strcmp(command[1],"clean")==0){
		result =  printCleanGradeSheet(system,output_channel);
	}
	if(strcmp(command[1],"best")==0){
		result =  PrintHighestGrades(system,atoi(command[2]),output_channel);
	}
	if(strcmp(command[1],"worst")==0){
		result =  PrintLowestGrades(system,atoi(command[2]),output_channel);
	}
	return result;
}

static CMResult subCommandStudent(CourseManager system, char** command){
	CMResult result = CM_SUCCESS;
	if(strcmp(command[1],"add")==0){
		result = studentAdd(system,atoi(command[2]),command[3],command[4]);
	}
	if(strcmp(command[1],"remove")==0){
		result = studentRemove(system,atoi(command[2]));
	}
	if(strcmp(command[1],"login")==0){
		result = studentLogin(system,atoi(command[2]));
	}
	if(strcmp(command[1],"logout")==0){
		result = studentLogout(system);
	}
	if(strcmp(command[1],"friend_request")==0){
		result = studentSendFriendRequest(system,getID(getLogin(system)),
				atoi(command[2]));
	}
	if(strcmp(command[1],"handle_request")==0){
		result = studentHandleRequest(system,getID(getLogin(system)),
				atoi(command[2]),command[3]);
	}
	if(strcmp(command[1],"unfriend")==0){
		result = studentUnfriend(system,getID(getLogin(system)),
				atoi(command[2]));
	}
	return result;
}

static bool arrangeInputOutput(FILE **input_channel, FILE **output_channel,
		int argc, char** argv,EX3ErrorCode* error_code){

	for(int i=1; i<argc; i+=2){
		if (i+1 >= argc){
			*error_code = EX3_INVALID_COMMAND_LINE_PARAMETERS;
			return false;
		}
		bool file = loadFile(input_channel,output_channel,
				argv[i],argv[i+1], error_code);
		if(!file){
			closeFiles(input_channel,output_channel);
			return false;
		}
	}
	return true;
}

static bool readLine(CourseManager system,char* line, FILE* output_channel,
		FILE* error_channel){
	char **command = makeStringsArray(MAX_WORDS_IN_LINE);
	if(!command) return convertError(CM_OUT_OF_MEMORY,error_channel);
	char *token;
	char delim[] = "\r\n\t ";
	token = strtok(line, delim);
	for(int i=0; (i<MAX_WORDS_IN_LINE)&&(token); i++, token=strtok(NULL,delim)){
		if((i==0)&&(token[0]=='#')){
			freeStringArray(command,MAX_WORDS_IN_LINE);
			return true;
		}
		strcpy(command[i],token);
	}
	CMResult result = CM_SUCCESS;
	if(strcmp(command[0],"student")==0){
		result = subCommandStudent(system,command);
	}else if(strcmp(command[0],"report")==0){
			result = subCommandReport(system,command,output_channel);
	}else if(strcmp(command[0],"grade_sheet")==0){
			result = subCommandGradeSheet(system,command);
	}
	freeStringArray(command,MAX_WORDS_IN_LINE);
	return convertError(result,error_channel);
}

static void getInput(CourseManager system, FILE* input_channel,
		FILE* output_channel, FILE* error_channel){
	bool keep_looping = true;
	char line[MAX_LEN+1];
	while((keep_looping) && (fgets(line,MAX_LEN+1,input_channel))){
		   keep_looping = readLine(system,line,output_channel,error_channel);
	}
}

int main(int argc, char **argv){
	FILE *input_channel = stdin;
	FILE *output_channel = stdout;
	FILE *error_channel = stderr;

	if(argc!=1 && argc!=3 && argc!=5){
		ERROR_AND_EXIT(EX3_INVALID_COMMAND_LINE_PARAMETERS);
	}
	if(argc>1){
		EX3ErrorCode error_code;
		if(!arrangeInputOutput(&input_channel,&output_channel,argc,argv,
				&error_code)){
			ERROR_AND_EXIT(error_code);
		}
	}
	CourseManager system = createCourseManager();
	if(!system){
		closeFiles(&input_channel, &output_channel);
		ERROR_AND_EXIT(EX3_OUT_OF_MEMORY);
	}

	getInput(system,input_channel,output_channel,error_channel);

	destroyCourseManager(system);
	closeFiles(&input_channel, &output_channel);
	return 0;
}
