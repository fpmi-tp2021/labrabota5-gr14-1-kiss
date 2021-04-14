#include "farbfeld.h"

uint16_t *
farbfeld_read(void *farbfeld_data, uint32_t *ret_width, uint32_t *ret_height)
{
	uint32_t hdr[4];
	memcpy(hdr, farbfeld_data, sizeof(hdr));
	if (memcmp("farbfeld", hdr, sizeof("farbfeld") - 1) != 0) {
		fprintf(stderr, "not a farbfeld image\n");
		exit(1);
	}
	*(ret_width) = ntohl(hdr[2]);
	*(ret_height) = ntohl(hdr[3]);

	/* read data */
	const uint32_t pixels = *ret_width * *ret_height;
	uint16_t *image = malloc(sizeof(uint16_t) * 4 * *ret_width * *ret_height);
	memcpy(image, farbfeld_data + sizeof(hdr), sizeof(uint16_t) * 4 * pixels);

	return image;
	readerr:
	errno = 1;
	return NULL;
}
