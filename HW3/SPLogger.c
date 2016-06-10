#include "SPLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//File open mode
#define SP_LOGGER_OPEN_MODE "w"



// Global variable holding the logger
SPLogger logger = NULL;

struct sp_logger_t {
	FILE* outputChannel; //The logger file
	bool isStdOut; //Indicates if the logger is stdout
	SP_LOGGER_LEVEL level; //Indicates the level
};

SP_LOGGER_MSG spLoggerCreate(const char* filename, SP_LOGGER_LEVEL level) {
	if (logger != NULL) { //Already defined
		return SP_LOGGER_DEFINED;
	}
	logger = (SPLogger) malloc(sizeof(*logger));
	if (logger == NULL) { //Allocation failure
		return SP_LOGGER_OUT_OF_MEMORY;
	}
	logger->level = level; //Set the level of the logger
	if (filename == NULL) { //In case the filename is not set use stdout
		logger->outputChannel = stdout;
		logger->isStdOut = true;
	} else { //Otherwise open the file in write mode
		logger->outputChannel = fopen(filename, SP_LOGGER_OPEN_MODE);
		if (logger->outputChannel == NULL) { //Open failed
			free(logger);
			logger = NULL;
			return SP_LOGGER_CANNOT_OPEN_FILE;
		}
		logger->isStdOut = false;
	}
	return SP_LOGGER_SUCCESS;
}


void spLoggerDestroy() {
	if (!logger) {
		return;
	}
	if (!logger->isStdOut) {//Close file only if not stdout
		fclose(logger->outputChannel);
	}
	free(logger);//free allocation
	logger = NULL;
}


SP_LOGGER_MSG spLoggerPrintError(const char* msg, const char* file,
		const char* function, const int line){

	// Check valid arguments and logger defined

	if(!msg || !function || line < 0){
		return SP_LOGGER_INVAlID_ARGUMENT;
	}
	if(logger == NULL){
		return SP_LOGGER_UNDIFINED;
	}

	// Write to file
	if (logger->outputChannel == NULL) { //Open failed
	 	return SP_LOGGER_WRITE_FAIL;
	}
	else {
			 fprintf(logger->outputChannel, "---ERROR---\n");
			 fprintf(logger->outputChannel, "- file: %s\n",file);
			 fprintf(logger->outputChannel, "- function: %s\n",function);
			 fprintf(logger->outputChannel, "- line: %i\n",line);
			 fprintf(logger->outputChannel, "- message: %s\n",msg);
			 //fprintf(logger->outputChannel, "\n");

	}
	return SP_LOGGER_SUCCESS;

}


SP_LOGGER_MSG spLoggerPrintWarning(const char* msg, const char* file,
		const char* function, const int line){



	// Check valid arguments and logger defined
	if(!msg || !function || line < 0){
	 return SP_LOGGER_INVAlID_ARGUMENT;
	}
	if(logger == NULL){
		return SP_LOGGER_UNDIFINED;
	}

	// Check valid level
		if(logger->level == SP_LOGGER_ERROR_LEVEL){
			return SP_LOGGER_SUCCESS;
		}

		else {

			// Write to file
			if (logger->outputChannel == NULL) { //Open failed
				return SP_LOGGER_WRITE_FAIL;
			}
			else {
					 fprintf(logger->outputChannel, "---WARNING---\n");
					 fprintf(logger->outputChannel, "- file: %s\n",file);
					 fprintf(logger->outputChannel, "- function: %s\n",function);
					 fprintf(logger->outputChannel, "- line: %i\n",line);
					 fprintf(logger->outputChannel, "- message: %s\n",msg);
					 //fprintf(logger->outputChannel, "\n");

			}
		}
	return SP_LOGGER_SUCCESS;
}

SP_LOGGER_MSG spLoggerPrintDebug(const char* msg, const char* file,
		const char* function, const int line){

	// Check valid arguments and logger defined
	if(!msg || !function || line < 0){
	 return SP_LOGGER_INVAlID_ARGUMENT;
	}
	if(logger == NULL){
		return SP_LOGGER_UNDIFINED;
	}

	// Check valid level
	if(logger->level == SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL){

		// Write to file
			if (logger->outputChannel == NULL) { //Open failed
			 	return SP_LOGGER_WRITE_FAIL;
			}
			else {
					 fprintf(logger->outputChannel, "---DEBUG---\n");
					 fprintf(logger->outputChannel, "- file: %s\n",file);
					 fprintf(logger->outputChannel, "- function: %s\n",function);
					 fprintf(logger->outputChannel, "- line: %i\n",line);
					 fprintf(logger->outputChannel, "- message: %s\n",msg);
					 //fprintf(logger->outputChannel, "\n");

			}
	}
	return SP_LOGGER_SUCCESS;
}

SP_LOGGER_MSG spLoggerPrintInfo(const char* msg){
	// Check valid arguments and logger defined
		if(!msg){
		 return SP_LOGGER_INVAlID_ARGUMENT;
		}
		if(logger == NULL){
			return SP_LOGGER_UNDIFINED;
		}

		// Check valid level
		if(logger->level == SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL ||
				logger->level == SP_LOGGER_INFO_WARNING_ERROR_LEVEL){

			// Write to file
				if (logger->outputChannel == NULL) { //Open failed
				 	return SP_LOGGER_WRITE_FAIL;
				}
				else {
						 fprintf(logger->outputChannel, "---INFO---\n");
						 fprintf(logger->outputChannel, "- message: %s\n",msg);
						 //fprintf(logger->outputChannel, "\n");

				}
		}
		return SP_LOGGER_SUCCESS;
}

SP_LOGGER_MSG spLoggerPrintMsg(const char* msg){
	// Check valid arguments and logger defined
			if(!msg){
			 return SP_LOGGER_INVAlID_ARGUMENT;
			}
			if(logger == NULL){
				return SP_LOGGER_UNDIFINED;
			}

			if (logger->outputChannel == NULL) { //Open failed
				return SP_LOGGER_WRITE_FAIL;
			}
			else {
				fprintf(logger->outputChannel, "- message: %s\n",msg);
				//fprintf(logger->outputChannel, "\n");

			}
			return SP_LOGGER_SUCCESS;
}
