#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <openssl/sha.h>

#define NODE_DATA_SIZE 500
#define NUM_NODES 500
#define DIR_PATH "./files"

char *getSHA(unsigned char *data);

int main()
{
    DIR *d;
    FILE *fp;
    int i = 0;
    struct dirent *dir;
    char data[NUM_NODES][NODE_DATA_SIZE];
    char temp[NODE_DATA_SIZE];
    char filename[100];
    unsigned char allData[NODE_DATA_SIZE*NUM_NODES];

    char currSHA[SHA_DIGEST_LENGTH*2];

    //get all text from directory
    d = opendir(DIR_PATH);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strcat(filename, DIR_PATH);
            strcat(filename, "/");
            strcat(filename, dir->d_name);

            fp = fopen(filename, "r");

            if (fp == NULL) printf("Cannot Open.\n");
            else
            {
                fgets(temp, NODE_DATA_SIZE, fp);
                strcpy(data[i], temp);
                fclose(fp);
            }

            //clear filename string
            filename[0] = '\0';
            i++;
        }
        closedir(d);
    }

    for(i=1; i<NUM_NODES; i++){
        if(i==1)
            strcpy(currSHA, getSHA(strcat(data[i], data[i-1])));

        strcpy(currSHA, getSHA(strcat(currSHA, data[i])));
    }

    printf("%s\n", currSHA);

    return 0;
}

char *getSHA(unsigned char *data)
{
    int i = 0;
    unsigned char temp[SHA_DIGEST_LENGTH];
    char *buf = malloc(SHA_DIGEST_LENGTH*2);

    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(temp, 0x0, SHA_DIGEST_LENGTH);

    SHA1((unsigned char *)data, strlen(data), temp);

    for (i=0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
    }

    return buf;

    return 0;
}
