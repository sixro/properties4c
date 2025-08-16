#ifndef PROPERTIES4C_H
#define PROPERTIES4C_H

typedef struct Properties Properties;

/*
 * Create a properties using the specified file.
 *
 * Returns NULL if the memory cannot be allocated correctly.
 * Call props_free to free the memory allocated.
 */
Properties * props_create(const char *filepath);

/*
 * Returns the value of the specified key found in the specified properties.
 */
const char * props_get(const Properties *properties, const char *key);

/*
 * Free up the memory allocated for the specified properties (allocated with props_create).
 */
void props_free(Properties *properties);

#endif /* PROPERTIES4C_H */
