/*
 ================================================================================================================
 Name        : pfile.h
 Author      : Esther Osammor
================================================================================================================
 */

#include <stdio.h>
/***************************************************************************************************************/
//DEFINES

#define MAX_LINE_LEN 90


/***************************************************************************************************************/
// Structures

typedef struct PokemonLineType {
	char description[MAX_LINE_LEN + 1];
}PokemonLine;

/****************************************************************************************************************/
//Function Prototypes

int searchFile(FILE *file, PokemonLine **arr, char *input, int *);
void saveToArr(char *line, PokemonLine *pokemon);
const char *saveToFile(PokemonLine *pokemonLine, int count);


