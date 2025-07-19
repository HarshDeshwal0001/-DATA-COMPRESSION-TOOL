#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to compress file
void compressFile(const char *input, const char *output) {
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");

    if (!in || !out) {
        printf("File error!\n");
        return;
    }

    char ch, prev;
    int count = 1;

    prev = fgetc(in);
    while ((ch = fgetc(in)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            fprintf(out, "%d%c", count, prev);
            count = 1;
            prev = ch;
        }
    }
    // Write the last set
    fprintf(out, "%d%c", count, prev);

    fclose(in);
    fclose(out);

    printf("Compression complete.\n");
}

// Function to decompress file
void decompressFile(const char *input, const char *output) {
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");

    if (!in || !out) {
        printf("File error!\n");
        return;
    }

    int count;
    char ch;

    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);

    printf("Decompression complete.\n");
}

// Main menu
int main() {
    int choice;
    char inFile[100], outFile[100];

    printf("Run-Length Encoding (RLE) Tool\n");
    printf("1. Compress\n");
    printf("2. Decompress\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter input file name: ");
    scanf("%s", inFile);
    printf("Enter output file name: ");
    scanf("%s", outFile);

    if (choice == 1)
        compressFile(inFile, outFile);
    else if (choice == 2)
        decompressFile(inFile, outFile);
    else
        printf("Invalid choice!\n");

    return 0;
}
