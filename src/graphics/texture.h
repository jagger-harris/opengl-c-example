#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct texture {
  int height;
  int width;
  int nr_channels;
  unsigned int texture;
} texture;

texture texture_create(const char *texture_path, unsigned int color_mode);
void texture_use(texture *texture, unsigned int texture_level);

#endif /* TEXTURE_H */
