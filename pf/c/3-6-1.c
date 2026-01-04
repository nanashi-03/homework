#include <stdio.h>
#include <stdlib.h>

#define KEY 0xAC

void encodeFile(void) {
  char filename[FILENAME_MAX];
  printf("Enter filename:");
  scanf("%s", filename);
  FILE *in = fopen(filename, "rb");
  FILE *out = fopen("encoded.bin", "wb");

  if (!in || !out) {
    printf("File error during encoding.\n");
    return;
  }

  unsigned char ch;
  while (fread(&ch, 1, 1, in)) {
    ch = ch ^ KEY;
    fwrite(&ch, 1, 1, out);
  }

  fclose(in);
  fclose(out);

  printf("Encoding completed successfully.\n");
}

void decodeFile(void) {
  FILE *in = fopen("encoded.bin", "rb");
  FILE *out = fopen("decoded.c", "wb");

  if (!in || !out) {
    printf("File error during decoding.\n");
    return;
  }

  unsigned char ch;
  while (fread(&ch, 1, 1, in)) {
    ch = ch ^ KEY;
    fwrite(&ch, 1, 1, out);
  }

  fclose(in);
  fclose(out);

  printf("Decoding completed successfully.\n");
}

void compareFiles(void) {
  char filename[FILENAME_MAX];
  printf("Enter filename:");
  scanf("%s", filename);
  FILE *f1 = fopen(filename, "rb");
  FILE *f2 = fopen("decoded.c", "rb");

  if (!f1 || !f2) {
    printf("File error during comparison.\n");
    return;
  }

  int diff = 0;
  unsigned char c1, c2;

  while (1) {
    int r1 = fread(&c1, 1, 1, f1);
    int r2 = fread(&c2, 1, 1, f2);

    if (r1 != r2 || c1 != c2) {
      diff = 1;
      break;
    }

    if (r1 == 0)
      break;
  }

  fclose(f1);
  fclose(f2);

  if (diff)
    printf("Files are NOT identical.\n");
  else
    printf("Files are IDENTICAL.\n");
}

void exitProgram(void) {
  printf("Exiting program.\n");
  exit(0);
}

int main() {
  int choice;

  void (*menu[])() = {
    encodeFile,
    decodeFile,
    compareFiles,
    exitProgram
  };

  while (1) {
    printf("\nMenu:\n");
    printf("1. Encode Source-Code File\n");
    printf("2. Decode Encoded File\n");
    printf("3. Compare Original and Regenerated Code\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 4) {
      printf("Invalid option.\n");
      continue;
    }

    menu[choice - 1]();
  }

  return 0;
}
