#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

BYTE block[BLOCK_SIZE];
char filename[8];

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("ERROR: Must include a memory card image to scan.\n");
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("ERROR: File cannot be opened.\n");
    return 2;
  }

  int fnum = 0;
  FILE *img = NULL;
  while (fread(block, sizeof(BYTE), BLOCK_SIZE, input) == 512) {
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
    {
      if (fnum == 0) {
        sprintf(filename, "%03i.jpg", fnum);
        img = fopen(filename, "w");
        fwrite(block, sizeof(BYTE), BLOCK_SIZE, img);
        fnum++;
      }
      else {
        fclose(img);
        sprintf(filename, "%03i.jpg", fnum);
        img = fopen(filename, "w");
        fwrite(block, sizeof(BYTE), BLOCK_SIZE, img);
        fnum++;
      }
    }
    else if (fnum > 0) {
      fwrite(block, sizeof(BYTE), BLOCK_SIZE, img);
    }
  }
  fclose(img);
  fclose(input);
  return 0;
}