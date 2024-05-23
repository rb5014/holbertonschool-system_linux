#include "multithreading.h"

#define NB_PORTIONS 16
#define NB_THREADS 16

/**
 * thread_entry - entry point to a new thread.
 * @portion: pointer to the adress of a blur_portion_t
 * Return: NULL
 */
void *thread_entry(void *portion)
{
	blur_portion((blur_portion_t *)portion);
	pthread_exit(NULL);
}
/**
 * blur_image - blurs the entirety of an image using a Gaussian Blur.
 * @img_blur: holds the address at which the blured image is stored
 * @img: points to the source image,
 * @kernel: points to the convolution kernel to use
 */
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	size_t portion_height, bonus;
	blur_portion_t portion[NB_PORTIONS];
	int i, count;
	pthread_t threads[NB_THREADS];

	if (!img || !img_blur || !kernel || !img->w || !img->h)
		return;

	portion_height = img->h / NB_PORTIONS;
	bonus = img->h - portion_height * NB_PORTIONS;

	portion[0].y = 0;
	for (count = 0; count < NB_THREADS; count++)
	{
		if (count > 0)
		{
			if (portion[count - 1].h > img->h / NB_PORTIONS)
				portion[count].y++;
			portion[count].y = portion[count - 1].y + portion[count - 1].h;
		}
		portion[count].img = img;
		portion[count].img_blur = img_blur;
		portion[count].kernel = kernel;
		portion[count].w = img->w;
		portion[count].h = portion_height;
		portion[count].x = 0;
		/* Increase height by one if bonus rows */
		if (bonus)
		{
			portion[count].h++;
			bonus--;
		}
		if (pthread_create(&threads[count], NULL, &thread_entry,
						   &(portion[count])) != 0)
		{
			fprintf(stderr, "error: Cannot create thread # %d\n", count);
			break;
		}
	}
	for (i = 0; i < count; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			fprintf(stderr, "error: Cannot join thread # %d\n", i);
		}
	}
}
