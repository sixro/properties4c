#include "properties4c.h"

#include <string.h>

#include "assertions.h"

void test_not_found() {
	const char *filename = "not_existant.properties";
	Properties *p;

	p = props_create(filename);
	assert_null(p);
}

void test_open() {
	const char *filename = "test.properties";
	Properties *p;

	p = props_create(filename);
	assert_not_null(p);
}

void test_get() {
	const char *filename = "test.properties";
	const char *server_port;
	Properties *p;

	p = props_create(filename);
	server_port = props_get(p, "server.port");
	printf("Server port: %s\n", server_port);

	assert_eq_str("8080", server_port);
}

void test_free() {
	const char *filename = "test.properties";
	Properties *p;

	p = props_create(filename);
	props_free(p);
}

int main(void) {
	test_not_found();
	test_open();
	test_get();
	test_free();
	return 0;
}
