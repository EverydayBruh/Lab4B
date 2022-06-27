#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "InOut.h"

char *randString(int length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789               ";
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {
            for (int i = 0;i < length;i++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[i] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

int randTree(Tree* tree, int size)
{   
    Node* root = tree->root;
    KeyType key;
    InfoType info;

    for(int i = 0; i < size; i++)
    {
        key = randString(5);
        info = randString(5);
        addElement(tree, key, info);
    }
    return 0;
}

int timing()
{
    clock_t time1;
    clock_t time2;
    Tree tree = {NULL};
    char* s;
    int k;
    FILE* fb;
    char* key;
    for(int n = 1; n<=3; n++)
    {
        switch (n)
        {
        case 1:
            s = "timtingAdd";
            break;
        case 2:
            s = "timtingFind";
            break;
        case 3:
            s = "timtingDelete";
            break;
        }
        
        fb = fopen(s, "w");
        fprintf(fb, "Tree_Size\tTime\n");
        fclose(fb);
    }
    for(int i = 20000; i<=400000; i+=20000)
    {
        randTree(&tree, 20000);
        // printTree(root, 0);
        for(int n = 1; n<=3; n++)
        {
            switch (n)
            {
                case 1:
                    s = "timtingAdd";
                    time1 = clock();
                    for (int j = 0; j < 10000; j++)
                    {
                        addElement(&tree, randString(5), randString(5));
                    }
                    break;
                case 2:
                    s = "timtingFind";
                    time1 = clock();
                    for (int j = 0; j < 10000; j++)
                    {
                        key = randString(5);
                        k = 0;
                        findByKey(tree.root, key, &k, 1);
                        free(key);
                    }
                    break;
                case 3:
                    s = "timtingDelete";
                    time1 = clock();

                    for (int j = 0; j < 10000; j++)
                    {
                        key = randString(5);
                        deleteNode(&tree, key, 1);
                        free(key);
                    }
                    break;
            }
            time2 = clock();
            // fprintf(fb, "%d\t%d\n", i, time2 - time1);
            fb = fopen(s, "a");
            fprintf(fb, "%d\t%f\n", i, ( (float) time2 - time1) / CLOCKS_PER_SEC);
            fclose(fb);
        }
    }
    freeTree(tree.root);
    return 1;
}