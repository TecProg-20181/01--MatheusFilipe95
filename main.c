#include <stdio.h>

typedef struct pixel {
  unsigned short int red, green, blue;
} Pixel;

typedef struct image {
  Pixel pixel[512][512];   // [width][height][rgb] / 0 -> r / 1 -> g / 2 -> b
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
      int media = (img.pixel[i][j].red + img.pixel[i][j].green + img.pixel[i][j].blue)/3;

      img.pixel[i][j].red = media;
      img.pixel[i][j].green = media;
      img.pixel[i][j].blue = media;
    }
  }

  return img;
}

Image blur(Image img) {
  int size = 0;
  scanf("%d", &size);

  for (unsigned int i = 0; i < img.height; ++i) {
    for (unsigned int j = 0; j < img.width; ++j) {
      Pixel media = {0, 0, 0};

      int menor_height = min(img.height - 1, i + size/2);
      int min_width = min(img.width - 1, j + size/2);
      for(int x = max(0, i - size/2); x <= menor_height; ++x) {
        for(int y = max(0, j - size/2); y <= min_width; ++y) {
          media.red += img.pixel[x][y].red;
          media.green += img.pixel[x][y].green;
          media.blue += img.pixel[x][y].blue;
        }
      }
      media.red /= size * size;
      media.green /= size * size;
      media.blue /= size * size;

      img.pixel[i][j].red = media.red;
      img.pixel[i][j].green = media.green;
      img.pixel[i][j].blue = media.blue;
    }
  }
  return img;
}

Image rotate90right(Image img) {
  Image rotacionada;

  rotacionada.width = img.height;
  rotacionada.height = img.width;

  for (int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
    for (int j = rotacionada.width - 1, x = 0; j >= 0; --j, ++x) {
      rotacionada.pixel[i][j].red = img.pixel[x][y].red;
      rotacionada.pixel[i][j].green = img.pixel[x][y].green;
      rotacionada.pixel[i][j].blue = img.pixel[x][y].blue;
    }
  }
  return rotacionada;
}

Image invert_colors(Image img) {
    for (unsigned int i = 0; i < img.height; ++i) {
      for (unsigned int j = 0; j < img.width; ++j) {
        img.pixel[i][j].red = 255 - img.pixel[i][j].red;
        img.pixel[i][j].green = 255 - img.pixel[i][j].green;
        img.pixel[i][j].blue = 255 - img.pixel[i][j].blue;
      }
    }
    return img;
  }

  Image sepiascale(Image img){
    for (unsigned int x = 0; x < img.height; ++x) {
      for (unsigned int j = 0; j < img.width; ++j) {
        Pixel pixel;
        pixel.red = img.pixel[x][j].red;
        pixel.green = img.pixel[x][j].green;
        pixel.blue = img.pixel[x][j].blue;

        int p =  pixel.red * .393 + pixel.green * .769 + pixel.blue * .189;
        int menor_r = min(255, p);
        img.pixel[x][j].red = menor_r;

        p =  pixel.red * .349 + pixel.green * .686 + pixel.blue * .168;
        menor_r = min(255, p);
        img.pixel[x][j].green = menor_r;

        p =  pixel.red * .272 + pixel.green * .534 + pixel.blue * .131;
        menor_r = min(255, p);
        img.pixel[x][j].blue = menor_r;
      }
    }
    return img;
  }

  Image mirror_image(Image img){
    int w = img.width, h = img.height;

    int horizontal = 0;
    scanf("%d", &horizontal);

    if (horizontal == 1){
      w /= 2;
    }
    else{
      h /= 2;
    }
    for (int i2 = 0; i2 < h; ++i2) {
      for (int j = 0; j < w; ++j) {
        int x = i2, y = j;

        if (horizontal == 1)
          y = img.width - 1 - j;
        else
          x = img.height - 1 - i2;

        Pixel aux1;
        aux1.red = img.pixel[i2][j].red;
        aux1.green = img.pixel[i2][j].green;
        aux1.blue = img.pixel[i2][j].blue;

        img.pixel[i2][j].red = img.pixel[x][y].red;
        img.pixel[i2][j].green = img.pixel[x][y].green;
        img.pixel[i2][j].blue = img.pixel[x][y].blue;

        img.pixel[x][y].red = aux1.red;
        img.pixel[x][y].green = aux1.green;
        img.pixel[x][y].blue = aux1.blue;
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
        cortada.pixel[i][j].red = img.pixel[i + y][j + x].red;
        cortada.pixel[i][j].green = img.pixel[i + y][j + x].green;
        cortada.pixel[i][j].blue = img.pixel[i + y][j + x].blue;
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
        scanf("%hu %hu %hu", &img.pixel[i][j].red,
        &img.pixel[i][j].green,
        &img.pixel[i][j].blue);
      }
    }
    return img;
  }

  void imagePrint(Image img){
    printf("P3\n");
    printf("%u %u\n255\n", img.width, img.height);

    for (unsigned int i = 0; i < img.height; ++i) {
      for (unsigned int j = 0; j < img.width; ++j) {
        printf("%hu %hu %hu ", img.pixel[i][j].red,
        img.pixel[i][j].green,
        img.pixel[i][j].blue);
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
          img = blur(img);
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
          img = invert_colors(img);
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
