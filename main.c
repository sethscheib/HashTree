#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <openssl/sha.h>

#define NODE_DATA_SIZE 1000
#define NUM_NODES 30
#define DIR_PATH "./files"

struct node
{
    char data[NODE_DATA_SIZE];
    struct node *parent;
};

int main()
{
    DIR *d;
    FILE *fp;
    int i = 0;
    struct dirent *dir;
    struct node nodes[NUM_NODES];
    char temp[NODE_DATA_SIZE];
    char filename[100];
    unsigned char allData[NODE_DATA_SIZE*NUM_NODES];

    unsigned char hash[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];

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
                strcpy(nodes[i].data, temp);
                fclose(fp);
            }

            //clear filename string
            filename[0] = '\0';
            i++;
        }
        closedir(d);
    }

    for(i=0; i<NUM_NODES; i++)
    {
        strcpy(temp, nodes[i].data);
        strcat(allData, temp);
        //printf("Stored: %s\n", nodes[i].data);
    }

    /*

    SHA GEN WORKING

    */

    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(hash, 0x0, SHA_DIGEST_LENGTH);

    SHA1(allData, strlen(allData), hash);

    for (i=0; i < SHA_DIGEST_LENGTH; i++)
    {
        sprintf((char*)&(buf[i*2]), "%02x", hash[i]);
    }

    printf("SHA1: %s\n", buf);

    return 0;
}
