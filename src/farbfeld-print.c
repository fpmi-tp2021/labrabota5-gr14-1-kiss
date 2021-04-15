#include "farbfeld-print.h"
#include "farbfeld.h"

#include <chafa.h>
#include <stdio.h>
#include <arpa/inet.h>

void
farbfeld_print(const void *farbfeld_data)
{
	uint32_t width = 0, height = 0;
	uint16_t *pixels = farbfeld_read(farbfeld_data, &width, &height);
	if (pixels == NULL) {
		fprintf(stderr, "error reading image");
	}
	float ratio = (float)(width * K_RATIO_ADJUST) / height;
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

	int canvas_width = IMG_WIDTH;
	int canvas_height = IMG_WIDTH/ratio;
	printf("canvas width: %d, canvas height: %d\n", canvas_width, canvas_height);

	/* Set up a configuration with the symbols and the canvas size in characters */
	config = chafa_canvas_config_new ();
	chafa_canvas_config_set_geometry (config, canvas_width, canvas_height);
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
