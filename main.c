#include <stdio.h>

typedef struct pixel {
  unsigned short int red, green, blue;
} Pixel;

typedef struct image {
  unsigned short int pixel[512][512][3];   // [width][height][rgb] / 0 -> r / 1 -> g / 2 -> b
  unsigned int width, height;
} Image;

int max(int a, int b){
  if (a > b)
  return a;
  return b;
}

int min(int a, int b){
  if (a > b)
  return b;
  return a;
}

Image grayscale(Image img) {

  for (int i = 0; i < img.height; ++i) {
    for (int j = 0; j < img.width; ++j) {
      int media = (img.pixel[i][j][0] + img.pixel[i][j][1] + img.pixel[i][j][2])/3;

      img.pixel[i][j][0] = media;
      img.pixel[i][j][1] = media;
      img.pixel[i][j][2] = media;
    }
  }

  return img;
}

void blur(unsigned int height, unsigned short int pixel[512][512][3], unsigned int width) {
  int size = 0;
  scanf("%d", &size);

  for (unsigned int i = 0; i < height; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
      Pixel media = {0, 0, 0};

      int menor_height = min(height - 1, i + size/2);
      int min_width = min(width - 1, j + size/2);
      for(int x = max(0, i - size/2); x <= menor_height; ++x) {
        for(int y = max(0, j - size/2); y <= min_width; ++y) {
          media.red += pixel[x][y][0];
          media.green += pixel[x][y][1];
          media.blue += pixel[x][y][2];
        }
      }
      media.red /= size * size;
      media.green /= size * size;
      media.blue /= size * size;

      pixel[i][j][0] = media.red;
      pixel[i][j][1] = media.green;
      pixel[i][j][2] = media.blue;
    }
  }
}

Image rotate90right(Image img) {
  Image rotacionada;

  rotacionada.width = img.height;
  rotacionada.height = img.width;

  for (int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
    for (int j = rotacionada.width - 1, x = 0; j >= 0; --j, ++x) {
      rotacionada.pixel[i][j][0] = img.pixel[x][y][0];
      rotacionada.pixel[i][j][1] = img.pixel[x][y][1];
      rotacionada.pixel[i][j][2] = img.pixel[x][y][2];
    }
  }
  return rotacionada;
}

void invert_colors(unsigned short int pixel[512][512][3],
  unsigned int width, unsigned int height) {
    for (unsigned int i = 0; i < height; ++i) {
      for (unsigned int j = 0; j < width; ++j) {
        pixel[i][j][0] = 255 - pixel[i][j][0];
        pixel[i][j][1] = 255 - pixel[i][j][1];
        pixel[i][j][2] = 255 - pixel[i][j][2];
      }
    }
  }

  Image sepiascale(Image img){
    for (unsigned int x = 0; x < img.height; ++x) {
      for (unsigned int j = 0; j < img.width; ++j) {
        unsigned short int pixel[3];
        pixel[0] = img.pixel[x][j][0];
        pixel[1] = img.pixel[x][j][1];
        pixel[2] = img.pixel[x][j][2];

        int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
        int menor_r = min(255, p);
        img.pixel[x][j][0] = menor_r;

        p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
        menor_r = min(255, p);
        img.pixel[x][j][1] = menor_r;

        p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
        menor_r = min(255, p);
        img.pixel[x][j][2] = menor_r;
      }
    }
    return img;
  }

  Image mirror_image(Image img){
    int w = img.width, h = img.height;

    int horizontal = 0;
    scanf("%d", &horizontal);

    if (horizontal == 1)
    w /= 2;
    else
    h /= 2;
    for (int i2 = 0; i2 < h; ++i2) {
      for (int j = 0; j < w; ++j) {
        int x = i2, y = j;

        if (horizontal == 1)
        y = img.width - 1 - j;
        else
        x = img.height - 1 - i2;

        Pixel aux1;
        aux1.red = img.pixel[i2][j][0];
        aux1.green = img.pixel[i2][j][1];
        aux1.blue = img.pixel[i2][j][2];

        img.pixel[i2][j][0] = img.pixel[x][y][0];
        img.pixel[i2][j][1] = img.pixel[x][y][1];
        img.pixel[i2][j][2] = img.pixel[x][y][2];

        img.pixel[x][y][0] = aux1.red;
        img.pixel[x][y][1] = aux1.green;
        img.pixel[x][y][2] = aux1.blue;
      }
    }
    return img;
  }

  Image imageCut(Image img) {
    int x, y, width, height;
    scanf("%d %d", &x, &y);
    scanf("%d %d", &width, &height);

    Image cortada;

    cortada.width = width;
    cortada.height = height;

    for(int i = 0; i < height; ++i) {
      for(int j = 0; j < width; ++j) {
        cortada.pixel[i][j][0] = img.pixel[i + y][j + x][0];
        cortada.pixel[i][j][1] = img.pixel[i + y][j + x][1];
        cortada.pixel[i][j][2] = img.pixel[i + y][j + x][2];
      }
    }
    return cortada;
  }

  Image rotation90(Image img){
    int quantas_vezes = 0;
    scanf("%d", &quantas_vezes);
    quantas_vezes %= 4;
    for(int j = 0; j < quantas_vezes; ++j){
      img = rotate90right(img);
    }
    return img;
  }

  Image imageRead(Image img){

    char imagetype[4];
    scanf("%s", imagetype);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &img.width, &img.height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < img.height; ++i) {
      for (unsigned int j = 0; j < img.width; ++j) {
        scanf("%hu %hu %hu", &img.pixel[i][j][0],
        &img.pixel[i][j][1],
        &img.pixel[i][j][2]);
      }
    }
    return img;
  }

  void imagePrint(Image img){
    printf("P3\n");
    printf("%u %u\n255\n", img.width, img.height);

    for (unsigned int i = 0; i < img.height; ++i) {
      for (unsigned int j = 0; j < img.width; ++j) {
        printf("%hu %hu %hu ", img.pixel[i][j][0],
        img.pixel[i][j][1],
        img.pixel[i][j][2]);
      }
      printf("\n");
    }
  }


  int main() {
    Image img;

    img = imageRead(img);

    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) {
      int opcao;
      scanf("%d", &opcao);

      switch(opcao) {
        case 1: {
          img = grayscale(img);
          break;
        }
        case 2: {
          img = sepiascale(img);
          break;
        }
        case 3: {
          blur(img.height, img.pixel, img.width);
          break;
        }
        case 4: {
          img = rotation90(img);
          break;
        }
        case 5: {
          img = mirror_image(img);
          break;
        }
        case 6: {
          invert_colors(img.pixel, img.width, img.height);
          break;
        }
        case 7: {
          img = imageCut(img);
          break;
        }
      }
    }

    imagePrint(img);

    return 0;
  }
