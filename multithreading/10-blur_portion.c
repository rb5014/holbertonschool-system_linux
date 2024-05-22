#include "multithreading.h"

/**
 * blur_pixel - blurs a pixel of a portion of an image
 * @portion: points to a data structure blur_portion_t
 * @x: X position of pixel
 * @y: Y position of pixel
*/
void blur_pixel(blur_portion_t const *portion, size_t x, size_t y)
{
	size_t k_x, k_y; /* Kernel indexes */
	size_t p_index = y * portion->img->w + x; /* Pixel to blur */
	size_t current_p_index; /* Current surrounding pixel */
	ssize_t i, j /* Position of current surrounding pixel being processed */;
	float tot_r = 0, tot_g = 0, tot_b = 0; /* Total of rgb colors */
	float divider = 0; /* Sum of kernel values to use to normalize */
	size_t half_k = portion->kernel->size / 2; /* Middle (X and Y) of kernel */
	pixel_t *pixels = portion->img->pixels; /* Array of pixels of source image */

	/* Iterate over surroundings pixels in the range of the kernel size */
	for (j = y - half_k, k_y = 0; j <= (ssize_t) (y + half_k); j++, k_y++)
	{
		/* Bound checking vertically */
		if ((j < 0) || (j >= (ssize_t) portion->img->h))
			continue;
		for (i = x - half_k, k_x = 0; i <= (ssize_t) (x + half_k); i++, k_x++)
		{
			/* Bound checking horizontally */
			if ((i < 0) || (i >= (ssize_t) portion->img->w))
				continue;
			divider += portion->kernel->matrix[k_x][k_y];
			current_p_index = j * portion->img->w + i;
			tot_r += pixels[current_p_index].r * portion->kernel->matrix[k_x][k_y];
			tot_g += pixels[current_p_index].g * portion->kernel->matrix[k_x][k_y];
			tot_b += pixels[current_p_index].b * portion->kernel->matrix[k_x][k_y];
		}
	}
	/* Normalize values */
	portion->img_blur->pixels[p_index].r = tot_r / divider;
	portion->img_blur->pixels[p_index].g = tot_g / divider;
	portion->img_blur->pixels[p_index].b = tot_b / divider;
}

/**
 * blur_portion - blurs a portion of an image using a Gaussian Blur
 * @portion: points to a data structure blur_portion_t
*/
void blur_portion(blur_portion_t const *portion)
{
	size_t x, y;

	/* Check if the structures are valid */
	if (!portion || !portion->img || !portion->img_blur || !portion->kernel)
	{
		fprintf(stderr, "Error: At least one of the structures is null.\n");
		return;
	}

	/* Check if the slice dimensions are valid */
	if (((portion->x + portion->w) > portion->img->w) ||
		((portion->y + portion->h) > portion->img->h))
	{
		fprintf(stderr, "Error: Invalid portion dimensions.\n");
		return;
	}

	/* Iterate over portion pixels */
	for (y = portion->y; y < portion->y + portion->h; y++)
	{
		for (x = portion->x; x < portion->x + portion->w; x++)
			blur_pixel(portion, x, y);
	}
}
