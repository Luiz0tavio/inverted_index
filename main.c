#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define FILE_BEFORE_SORT ".fbs"

void sortString(){

}


int main(int argc, char * argv[]){

	FILE *input = NULL, *output = NULL;
	char *line;
	char *word, *next_word;

	char eof;

	long int memory_size = strtol(argv[2], &word, 10);
	
	char *dir_name = malloc(256);
	strcpy(dir_name, argv[4]);
	strcat(dir_name, FILE_BEFORE_SORT);
	//output = fopen(dir_name, "w+");

	line = malloc( (size_t) (memory_size+1) );
	int files_counter, files_tmp_counter = 0;

	char file_name_counter_string[10]; // MAX number of inputs with 10 digits
	for (files_counter = 1; files_counter <= (strtol(argv[1], &word, 10)); files_counter++) {

		strcpy(dir_name, argv[3]);
		sprintf(file_name_counter_string, "%d", files_counter);
		strcat(dir_name, file_name_counter_string);
		input = fopen(dir_name, "r");

		if(input != NULL) {
			while( fread(line, 1, (size_t) memory_size, input) ) {
				eof = (char) (strlen(line) == ((size_t)memory_size) ? '0' : '1');
				word = strtok (line, " \n"); //  no memory is allocated, we're good at this point
				files_tmp_counter++;
				strcpy(dir_name, "./tmp/");
				sprintf(file_name_counter_string, "%d", files_tmp_counter);
				strcat(dir_name, file_name_counter_string);
				output = fopen(dir_name, "w+");
				while (word != NULL && word != "" ) {
					next_word = strtok (NULL, " \n");
					if(next_word == NULL && eof == '0'){
						// verify if the next word is null, then back it
						fseek(input, -strlen(word)-1, SEEK_CUR);
					} else {
						fwrite(word, strlen(word), 1, output);
						fwrite("\n", 1, 1, output);
					}
					word = next_word;
				}

				fclose(output);
				memset(line, '\0', (size_t)(memory_size+1)); // clear memory
			}
		}
		memset(file_name_counter_string, '\0', (size_t)(strlen(file_name_counter_string)+1)); // clear memory to avoid errors
	}
	memset(line, '\0', (size_t)(memory_size+1)); // clear memory to avoid errors
	memset(file_name_counter_string, '\0', (size_t)(strlen(file_name_counter_string)+1)); // clear memory to avoid errors


	if(input != NULL) fclose(input);

	free(line);
	free(dir_name);
	return 0;
}