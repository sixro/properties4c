#include "properties4c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Properties {
	unsigned short count;
	char **keys;
	char **values;
	char *buffer;
};

#define OUT      0
#define IN_KEY   1
#define IN_VALUE 2

void props_print(Properties *p);

/*
 * TODO manage errors on fopen, malloc, etc...
 */
Properties *props_create(const char *filepath) {
	long filesize;
	char c;
	char *buffer;
	int i, allocated, state, idx;
	Properties *p;
	FILE *file = fopen(filepath, "r");
	if (file == NULL) {
		printf("Unable to open specified file \"%s\"\n", filepath);
		return NULL;
	}
	
	/* Retrieve the filesize to allocate the right amount of memory */
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	/* Read the whole file in memory */
	buffer = (char *) malloc(filesize + 1);
	fread(buffer, 1, filesize, file);
	buffer[filesize] = '\0';

	p = (Properties *)malloc(sizeof(Properties));
	p->buffer = buffer;
	p->count = 0;
	allocated = 10;
	p->keys = (char**) malloc(allocated * sizeof(char *));
	p->values = (char**) malloc(allocated * sizeof(char *));

	i = idx = 0;
	state = OUT;
	while (i < filesize) {
		c = buffer[i];
		if (c == '=') {
			if (state == IN_KEY) {
				state = IN_VALUE;
				buffer[i] = '\0';
				p->values[idx] = buffer + i + 1;
			}
		} else if (c == '\n') {
			if (state == IN_VALUE) {
				state = OUT;
				buffer[i] = '\0';

				p->count++;
				idx++;
			} else {
				/* TODO write an error */
			}
		} else {
			if (state == OUT) {
				state = IN_KEY;
				p->keys[idx] = buffer + i;
			}
		}

		i++;
		if (idx == allocated) {
			allocated += 10;
			p->keys = (char **) realloc(p->keys, allocated * sizeof(char *));
			p->values = (char **) realloc(p->values, allocated * sizeof(char *));
		}
	}
	
	fclose(file);

	props_print(p);
	return p;
}

const char *props_get(const Properties *properties, const char *key) {
	unsigned int i;
	for (i = 0; i < properties->count; i++) {
		if (strcmp(properties->keys[i], key) == 0) {
			return properties->values[i];
		}
	}
	return NULL;
}

void props_free(Properties *properties) {
	printf("Free...\n");
	free(properties->buffer);
	free(properties->keys);
	free(properties->values);
	free(properties);
	printf("Free done...\n");
}

void props_print(Properties *p) {
	int i;
	printf("Properties count: %d\n", p->count);
	for (i = 0; i < p->count; i++) {
		printf("%d: %s => %s\n", i, p->keys[i], p->values[i]);
	}
}
