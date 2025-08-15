#ifndef ASSERTIONS_H
#define ASSERTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define assert_eq(a, b) \
	if (a != b) { \
		fprintf(stderr, "%s:%d expected: %s but was: %s\n", __FILE__, __LINE__, #a, #b); \
		abort(); \
	}

#define assert_eqs(a, b) \
	if (strcmp(a, b) != 0) { \
		fprintf(stderr, "%s:%d expected: \"%s\" but was: \"%s\"\n", __FILE__, __LINE__, a, b); \
		abort(); \
	}

#endif /* ASSERTIONS_H */
