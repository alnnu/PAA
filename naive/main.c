#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#define d 256


int naive(char* pat, char* txt)
{
    int count = 0;
    int M = strlen(pat);
    int N = strlen(txt);

    for (int i = 0; i <= N - M; i++) {
        int j;

        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if(j==M)
            count ++;
    }

    return count;
}


int main()
{

    FILE *dataFile = fopen("ifg", "r");

    // Seek to the end of the file to get its size
    fseek(dataFile, 0, SEEK_END);
    long file_size = ftell(dataFile);
    rewind(dataFile);  // Reset file pointer to the beginning

    // Allocate memory to store the entire file content
    char *buffer = (char *)malloc(file_size + 1); // +1 for null terminator


    fread(buffer, 1, file_size, dataFile);


    char pat[] = "instituto";

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    printf("%d\n", naive(pat, buffer));

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;


    printf("Time measured: %.3f seconds.\n", elapsed);

    fclose(dataFile);
    return 0;
}