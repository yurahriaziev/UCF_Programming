#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie {
    int isWord;
    struct trie *next[26];
} trie;

trie *init() {
    trie *myTree = malloc(sizeof(trie));
    myTree->isWord = 0;

    for (int i=0; i<26; i++) {
        myTree->next[i] = NULL;
    }

    return myTree;
}

int isEmpty(trie *root) {
    for (int i=0; i<26)
}

void insert(trie *tree, char word, int depth) {

}

int main() {
    // creating the trie
    trie* my_dict = init();

    int n;
    FILE* ifp = fopen("dictionary.txt", "r");
    fscanf(ifp, "%d", n);

    // read each word in the file and insert into the trie
    for (int i=0; i<n; i++) {
        char word[100];
        fscanf(ifp, "%s", word);
        insert(my_dict, word, 0);
    }

    // seach word in the trie
    char searchKey[100];
    printf("Enter a word to search: ");
    scanf("%s", searchKey);

    if (search(my_dict, searchKey, 0)) {
        printf("Found %s\n", searchKey);
    } else {
        printf("Not found %s\n", searchKey);
    }

    // printing all the words
    printf("Printing all the words:\n");
    char word[100];
    printAll(my_dict, word);

    // delete a word
    char deleteKey[100];
    printf("Enter a word to remove: ");
    scanf("%s", deleteKey);
    my_dict = del(my_dict, deleteKey, 0);

    word[0] = '\0';
    printall(my_dict, word);

    fclose(ifp);
    freeDict(my_dict);
    return 0;
}