#include "speedoman.h"


int levelLoad(void *handle, const char *level) {
	SPEEDOMAN *s = handle;
	FILE *fp;
	char fname[256];

	if ((fp = fopen(level, "r")) == NULL) {
		fprintf(stderr, "Unable to load level %s\n", level);
		return -1;
	}

	return 0;
}
