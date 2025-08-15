#include "properties4c.h"

struct Properties {
	unsigned short count;
	char **keys;
	char **values;
};

Properties *props_create(FILE *file) {
	return NULL;
}

const char *props_get(const Properties *properties, const char *key) {
	return NULL;
}

void props_free(Properties *properties) {
}
