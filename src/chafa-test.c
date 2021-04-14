#include <chafa.h>
#include <stdio.h>
#include <arpa/inet.h>

#define N_CHANNELS 4 
#define IMG_HEIGHT 24 

#define HEADER_LENGTH 4

gint16 *farbfeld_read(char *input_file_name, gint32 *hdr, gint32 *width, gint32 *height) {
    FILE *input_file = fopen(input_file_name, "r");

    /* read header */
    if (input_file == NULL || fread(hdr, sizeof(*hdr), HEADER_LENGTH, input_file) != HEADER_LENGTH) {
        goto readerr;
    }
    if (memcmp("farbfeld", hdr, sizeof("farbfeld") - 1) != 0) {
        fprintf(stderr, "invalid magic value\n");
        exit(1);
    }
    *(width) = ntohl(hdr[2]);
    *(height) = ntohl(hdr[3]);

    /* read data */
    const gint32 pixels = *width * *height;
    gint16 *image = malloc(sizeof(gint16) * 4 * *width * *height);
    if (fread(image, sizeof(gint16) * 4, pixels,
              input_file) != pixels) {
        goto readerr;
    }

    if (fclose(input_file)) {
        fprintf(stderr, "fclose: %s\n",
                strerror(errno));
        exit(1);
    }

    return image;
    readerr:
    errno = 1;
    return NULL;
}

int
main (int argc, char *argv [])
{
	gint32 width = 0, height = 0;
	gint32 hdr[4];
	gint16 *pixels = farbfeld_read(argv[1], hdr, &width, &height);
	if (pixels == NULL) {
		fprintf(stderr, "error reading image: %s\n", argv[1]);
	}
	float ratio = (float)width / height;
	printf("width: %d, height: %d, ratio: %f\n", width, height, ratio);

	uint8_t *pixels_8bit = malloc(width * height * 4 * sizeof(uint8_t));
	for (int i = 0; i < width * height * 4; ++i) {
		pixels_8bit[i] = (uint8_t)pixels[i];
	}

	ChafaSymbolMap *symbol_map; ChafaCanvasConfig *config;
	ChafaCanvas *canvas;
	GString *gs;

	/* Specify the symbols we want */
	symbol_map = chafa_symbol_map_new ();
	chafa_symbol_map_add_by_tags (symbol_map, CHAFA_SYMBOL_TAG_ALL);

	/* Set up a configuration with the symbols and the canvas size in characters */
	config = chafa_canvas_config_new ();
	chafa_canvas_config_set_geometry (config, IMG_HEIGHT*ratio*ratio, IMG_HEIGHT);
	chafa_canvas_config_set_symbol_map (config, symbol_map);

	/* Create canvas */
	canvas = chafa_canvas_new (config);

	/* Draw pixels and build ANSI string */
	chafa_canvas_draw_all_pixels (canvas,
								  CHAFA_PIXEL_RGBA8_UNASSOCIATED,
								  pixels_8bit,
								  width,
								  height,
								  width * N_CHANNELS);
	gs = chafa_canvas_build_ansi (canvas);

	/* Print the string */
	fwrite (gs->str, sizeof (char), gs->len, stdout);
	fputc ('\n', stdout);

	/* Free resources */
	g_string_free (gs, TRUE);
	chafa_canvas_unref (canvas);
	chafa_canvas_config_unref (config);
	chafa_symbol_map_unref (symbol_map);

	free(pixels_8bit);
	free(pixels);

	return 0;
}
