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

int Rabin(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    int count = 0;


    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                count ++;

        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
                t = (t + q);
        }
    }
    return count;

}

// Driver's code
int main()
{

    FILE *dataFile = fopen("ifg.md", "r");

    // Seek to the end of the file to get its size
    fseek(dataFile, 0, SEEK_END);
    long file_size = ftell(dataFile);
    rewind(dataFile);  // Reset file pointer to the beginning

    // Allocate memory to store the entire file content
    char *buffer = (char *)malloc(file_size + 1); // +1 for null terminator


    fread(buffer, 1, file_size, dataFile);




//    fseek(dataFile, 0, SEEK_SET);
//
//    unsigned long len = (unsigned long)ftell(dataFile);
//
//    char* string = (char*)calloc( len ,sizeof(char));
//
//    int odio = 0;
//
//    while (fgets(myline, 1000, dataFile)) {
//        odio += sizeof (myline);
//        printf("%d\n", strlen(myline));
//        strcat(string, myline);
//    }
//
//
//    printf("%s", string);
//    fclose(dataFile);

    char pat[] = "instituto";
    int q = 7;

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

//    printf("%d\n", Rabin(pat, buffer, q));


    printf("%d\n", naive(pat, buffer));

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;


    printf("Time measured: %.3f seconds.\n", elapsed);

    fclose(dataFile);
    return 0;
}