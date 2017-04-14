/* Mackenna Judge 
   ECE 2220
   Program #5
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Function Purpose: To check to see if a file exists and open it if it does to be used in the program. */
int file_open(char *file_name) {
	FILE * file;
	file = fopen(file_name, "r");
	if (file){
		// the file exists and can be opened
   		return 1;
	}
	else{
   		//file doesn't exists or cannot be opened (es. you don't have access permission )
		return 0;
	}
	fclose(file);
}

int main(int argc, char *argv[]) {

	// Variables
	FILE *OpenFile;
	char file_name[100];
	int file_count = 1;
	long int word_count = 0;
	long int letter_count = 0;
	long int alphabet_count[26] = { 0 }; // A is at 0, B is at 1 and so on until Z at 25
	int word_per_length[50] = { 0 };
	int more = 1;
	int exists;
	char current_char;
	int previous_space = 0;
	int previous_char = 0;
	int letter_location;
	int i = 0, j = 0;
	float letter_percent[26];
	char **All_words;
	char current_word[50];
	int word_length;
	long int file_word_count = 0;
	int maxFileNumber;
	char temp_word[50];
	int loop2_word_counter = 0;
	int smallest_string = 50;
	int largest_string = 0;
	char **Dictionary;
	int Dictionary_word_count = 1;
	int letter_count_word = 0;


	// Name of the file set to a specific variable
	while (more == 1) {
		// Name of the first file
		sprintf(file_name, "%s_%d.txt", argv[1], file_count);
		printf("File Name = %s\n", file_name);

		// Check if the file exists
		exists = file_open(file_name);
		if (exists == 1) {
			// The file can be opened
			OpenFile = fopen(file_name, "r");

			// Count the number of letters in this file
			while (!feof(OpenFile)) {
				fscanf(OpenFile, " %c", &current_char);
				//fscanf(OpenFile, " %s", current_word);
				//word_length = strlen(current_word);
				//current_word = (char *)malloc(sizeof(char)*word_length);
				//printf("Curret_word = %s\n", current_word);
				//if( strcmp(current_word,"\n") )
					//printf("NEW LINE");
				//printf(current_word);
				//for (i=0; i<word_length; ++i) {  // If it is a letter
				//	current_char = current_word[i];
					if (isalpha(current_char)) {
						letter_count = letter_count + 1;
					}
			}
			letter_count = letter_count - 1;

			// Back to the begining of the file
			rewind(OpenFile);

			// Count the number of words in the file
			while (letter_count_word < letter_count) {
				fscanf(OpenFile, "%s", current_word);
				word_length = strlen(current_word);
				printf("current_word = %s\n", current_word);
				for (i=0; i<word_length; ++i) {
					if(isalpha(current_word[i]) != 0) {
						letter_count_word = letter_count_word + 1;
					}
				}
				word_count = word_count + 1;
			}
			
			// Back to the begining of the file
			rewind(OpenFile);

			// count number of each letter
			letter_count_word = 0;
			while (letter_count_word < letter_count) {
				fscanf(OpenFile, "%c", &current_char);
				if (current_char >= 65 && current_char <= 90) {  // For capital letters
					letter_location = current_char - 65;
					alphabet_count[letter_location] = alphabet_count[letter_location] + 1;
					letter_count_word = letter_count_word + 1;
				}
				else if (current_char >= 97 && current_char <= 122) {  // For lower case letters
					letter_location = current_char - 97;
					alphabet_count[letter_location] = alphabet_count[letter_location] + 1;
					letter_count_word = letter_count_word + 1;
				}
				// Do nothing for non-letters
			}

			// Find the letter percentage 
			for (i=0; i<26; ++i) {
				letter_percent[i] =((float)alphabet_count[i]) / letter_count;
			}
			
			
		}
		else {
			// There are no more files to open
			maxFileNumber = file_count - 1;
			more = 0;
		}
		file_count = file_count + 1;
		// fclose(OpenFile);	
	}
	
	// Crete an array for all of the words
/*	for (i=1; i<=maxFileNumber; ++i) {
		// Open the file
		sprintf(file_name, "%s_%d.txt", argv[1], i);
		OpenFile = fopen(file_name, "r");
		// Malloc the large array
		All_words = (char**)malloc(sizeof(char*) * word_count);
		// Clear out current_word
		//memset(current_word, 0, sizeof(current_word));
		j = 0;
		previous_space = 0;
		while(!feof(OpenFile)) {
			fgets(&current_char, 1, OpenFile);
			// Put word into current_word (stil has punctuation on the end)
			if ((current_char >=65 && current_char <= 90) || (current_char >= 97 && current_char <= 122)) {
				current_word[j] = current_char;
				previous_char = 1;
				previous_space = 0;
				j = j + 1;
			}
			else if (previous_char == 1 && ispunct(current_char) != 0) {
				current_word[j] = current_char;
				previous_char = 0;
				previous_space = 0;
				j = j + 1;
			}
			else if (previous_space == 0 && isspace(current_char) != 0) {
				previous_space = 1;
				previous_char = 0;
				// Take punctution off the end of the word
				//memset(temp_word, 0, sizeof(temp_word));
				word_length = strlen(current_word);
				if (ispunct(current_word[word_length-1]) != 0) {
					strncpy(temp_word, current_word, word_length-1);
					//memset(current_word, 0, sizeof(current_word));
					strcpy(current_word, temp_word);
				}
				// Malloc the strings in the array
				All_words[loop2_word_counter] = (char*)malloc(sizeof(char)*word_length);
				strcpy(All_words[loop2_word_counter], current_word);
				loop2_word_counter = loop2_word_counter + 1;
				j = 0;
				//memset(current_word, 0, sizeof(current_word));
			}
		}
	}
	
	// Count the number of words for each length
	for (i=0; i<word_count; ++i) {
		word_length = strlen(All_words[i]);
		word_per_length[word_length] = word_per_length[word_length] + 1;
		// Check for lowest Value
		if(word_length < smallest_string) {
			smallest_string = word_length;
		}
		// Check for highest Value
		if(word_length > largest_string) {
			largest_string = word_length;
		}
	}
	
	// Create an Array of Strings for the Dictionary
	// Open the file
	OpenFile = fopen("dictionary.txt", "r");
	// Count the number of words in dictionary file
	while (!feof(OpenFile)) { 
		fscanf(OpenFile, "%c", &current_char);
		// If it is a letter
		if ((current_char >= 65 && current_char <=90) || (current_char >= 97 && current_char <=122)) {
			previous_space = 0; // The previous letter was not a space (used for the next loop)
		}
		else if (current_char == 32) {   // If it is a space
			if (previous_space == 0) {
				Dictionary_word_count = Dictionary_word_count + 1;
				previous_space = 1;    // The previous letter is a space (used for the next loop)
			}
		} 
		else {      // Not a letter or a space 
			previous_space = 0;   // the previous letter is not a space
		}
	}
	// Bring file back to top
	rewind(OpenFile);
	// Allocate memory for each word
	Dictionary = (char**)malloc(sizeof(char*) * Dictionary_word_count);
	//memset(current_word, 0, sizeof(current_word));
	j = 0;
	loop2_word_counter = 0;
	previous_space = 0;
	previous_char = 0;
	while(!feof(OpenFile)) {
		fscanf(OpenFile, "%c", &current_char);
		// Put word into current_word (stil has punctuation on the end)
		if ((current_char >=65 && current_char <= 90) || (current_char >= 97 && current_char <= 122)) {
			current_word[j] = current_char;
			previous_char = 1;
			previous_space = 0;
			j = j + 1;
		}
		else if (previous_char == 1 && ispunct(current_char) != 0) {
			current_word[j] = current_char;
			previous_char = 0;
			previous_space = 0;
			j = j + 1;
		}
		else if (previous_space == 0 && isspace(current_char) != 0) {
			previous_space = 1;
			previous_char = 0;
			// Take punctution off the end of the word
			//memset(temp_word, 0, sizeof(temp_word));
			word_length = strlen(current_word);
			if (ispunct(current_word[word_length-1]) != 0) {
				strncpy(temp_word, current_word, word_length-1);
				//memset(current_word, 0, sizeof(current_word));
				strcpy(current_word, temp_word);
			}
			// Malloc the strings in the array
			Dictionary[loop2_word_counter] = (char*)malloc(sizeof(char)*word_length);
			strcpy(Dictionary[loop2_word_counter], current_word);
			loop2_word_counter = loop2_word_counter + 1;
			j = 0;
			//memset(current_word, 0, sizeof(current_word));
		}		
	}

		
*/			






//----------------------------------------------------------------------//
// TAKE THIS OUT BEFORE SUBMISSION !!!!!!!!!!
printf("word_count = %ld\n", word_count);
printf("letter_count = %ld\n", letter_count);
for (i=0; i<26; ++i) {
	printf("Alphabet count = %ld\n", alphabet_count[i]);
} 
for (i=0; i<26; ++i) {
	printf("Letter Percent = %f\n", letter_percent[i]);
} 
/*for (i=0; i<50; ++i) {
	printf("Length Count = %d\n", word_per_length[i]);
}
printf("all_words[0] = %s\n", All_words[0]);
printf("Dictionary[0] = %s\n", Dictionary[0]);*/
//---------------------------------------------------------------------//


	return 0;
}	
