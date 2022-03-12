/*
 ================================================================================================================
 Name        : main.c
 Author      : Esther Osammor
 Description : A program that allows a user input a file, search that file for a pokemon property and store the
	       results found in a separate file. 
 ================================================================================================================
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "pfile.h"

/*function prototypes */
void *displayMenu(void *);

int main() {
	char *inputFile = NULL;
	FILE *pokemonFile;
	pthread_t menu;
	char userSelection;
	PokemonLine *pokemonLineArr = NULL;
	char *userSearch = NULL;
	int arrCount = 0;
	int successQueries = 0;
	char **createdFilesArr;
	int files = 0;

	/*Promt User to enter file*/
	printf("Enter the name of the file containing Pokemon descriptions \n");
	scanf("%ms", &inputFile);
	pokemonFile = fopen(inputFile, "r");

	/*Reprompt if file is not found*/
	while (!pokemonFile){
		printf("Pokemon file is not found. Please enter the name of the file again or type 3 to exit: \n");
		scanf("%ms", &inputFile);

		/*user enters '3' to exit*/
		if (strcmp(inputFile, "3") == 0)
			exit(0);
	
		pokemonFile = fopen(inputFile, "r");
	}

	while(1) {
		/*create thread to display menu */
		pthread_create(&menu, NULL, displayMenu, &userSelection);
		pthread_join(menu, NULL);

		/*search*/
		if (userSelection == 'a') {
			int temp = 0;
			printf("What type of pokemon would you like to search for? \n");
			scanf("%ms", &userSearch);
			temp = searchFile(pokemonFile, &pokemonLineArr, userSearch, &arrCount);	
			/*if userSearch was found, increment the successQuery var*/
			if (temp)
				successQueries++; 
			continue;		/*back to start of loop*/
		}

		/*save*/
		if (userSelection == 'b') {
			/*call save to file and store the name of file in saveName var*/
			const char *saveName = saveToFile(pokemonLineArr, arrCount);
			files++;  

			if (files == 1)
				createdFilesArr = calloc(1, sizeof(char*));
			else
				createdFilesArr = realloc(createdFilesArr, (files+1)*sizeof(char*));

			/*add the saveFile name to array of filenames*/
			createdFilesArr[files-1] = (char *)saveName;
			continue;

		}

		if (userSelection == 'c') {
			printf("Number of Sucessful Queries: %d\n", successQueries);
			printf("Names of the new files created during the session: \n");
			for(int i =0; i<files; i++){
				printf("%s\n", createdFilesArr[i]);
				free(createdFilesArr[i]);
			}
			if (files>0)
				free(createdFilesArr);
			break;
		}
		else
			continue;


	}

	/*free memory and close file*/
	free(inputFile);
	free(userSearch);
	free(pokemonLineArr);

	fclose(pokemonFile);

	return EXIT_SUCCESS;
}

/************************************************************************************************/
/* Purpose : Displays a menu and prompts the user the selection an option from the menu
 * Input   : arg - an argument pointer that will store the user selection
 * Output  : Instructions for the user to follow
 * Return  : None
 */
void *displayMenu(void *arg){
	char userSelection = *((char *)arg);

	printf("Select one of the following options: \na. Type search \nb. Save results \nc. Exit the program \n");
	scanf("%s", &userSelection);

	*((char *)arg) = userSelection;
	return(0);
}


