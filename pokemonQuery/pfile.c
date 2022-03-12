/*
 ================================================================================================================
 Name        : pfile.c
 Author      : Esther Osammor
 ================================================================================================================
 */


/****************************************************************************************************************/
//INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "pfile.h"

//DEFINES
#define MAX_LINE_LEN 90

/****************************************************************************************************************/
/* Purpose : Search a csv for the input given, if found, store that line in an array
 * Input   : file - pointer to the file that is read
 * 	     arr - pointer to the struct of pokemon lines that the input is found in
 * 	     input - the word the user is searching the file for
 * 	     arrCount - pointer to an int that represents the #of structues in arr
 * Output  : None
 * Return  : 1 if given input was found in file
 * 	     0 if given input was not found in file
 */
int searchFile(FILE *file, PokemonLine **arr, char *input, int *arrCount) {
	int numLines = 0;
	int successFlag = 0;
	char line[MAX_LINE_LEN];

	while (fgets(line, MAX_LINE_LEN, file)) {
		char type1[10];
	
		if (numLines > 0) {                                /*ignore the first line */
			/*create a temp var to avoid modifying the original line*/
			/*gets the 'type1' from the curr line */
			char *tempLine = malloc(MAX_LINE_LEN +1);
			strcpy(tempLine, line);			
			strtok(tempLine, ",");
			strtok(NULL, ",");
			strcpy(type1, strtok(NULL, ","));

			if (strcmp(input, type1) == 0) {            /*if user input is found...*/
				successFlag = 1;
				++*arrCount;
				if (*arrCount == 1) 
					*arr = calloc(1, sizeof(PokemonLine));
				else if (*arrCount > 1)
					*arr = realloc(*arr, (*arrCount)*sizeof(PokemonLine));

				saveToArr(line, &(*arr)[*arrCount-1]);
			}
			free(tempLine);
		}
		numLines++;
	}
	rewind(file);  /*when all lines of the file have been read, reset pointer back to the start of file*/
	return successFlag;
}


/****************************************************************************************************************/
/* Purpose : converts csv line to Pokemon data structure
 * Input   : line - the line that will be converted to Pokemon
 * 	     foundPokemon - new Pokemon to be filled with the line
 * Output  : None
 * Return  : None
 */
void saveToArr(char *line, PokemonLine *foundPokemon) {
	strcpy(foundPokemon->description, line);
}


/****************************************************************************************************************/
/* Purpose : Save all pokemon descriptions from Pokemon array to a given file
 * Input   : pokemon - array of Poken descriptions to be stored in the file
 *           count - number of elements in the pokemon array
 * Output  : Instructions for user to follow
 * Return  : The name of the file in which descriptions were stored in
 */
const char *saveToFile(PokemonLine *pokemon, int count) {
	char *outputFile = NULL;
	FILE *saveFile = NULL;

	printf("Enter the name of the file you want to save the search results to: \n");
	scanf("%ms", &outputFile);
	saveFile = fopen(outputFile, "w");
	while(!saveFile) {
		printf("Unable to create new file. Please enter the name of the file again\n");
		scanf("%ms", &outputFile);
		saveFile = fopen(outputFile, "w");
	}
	
	for(int i = 0; i < count; i++){
		char line[MAX_LINE_LEN] = "";
		strcat(line, pokemon[i].description);
		fprintf(saveFile, "%s\n", line);
	}
	fclose(saveFile);
	return outputFile;
}

