#include "properties4c.h"

#include <string.h>

#include "assertions.h"

void test_not_found() {
	FILE *file;
	const char *filename = "test.properties";
	Properties *p;

	file = fopen(filename, "r");
	if (file == NULL) {
		perror(strcat("Unable to open file ", filename));
		abort();
	}

	p = props_create(file);
	assert_not_null(p);

	fclose(file);
}

int main(void) {
	test_not_found();
	return 0;
}
