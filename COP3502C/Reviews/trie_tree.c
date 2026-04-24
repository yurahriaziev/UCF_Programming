// Trie Trees
// - used to represent strings
// Applications:
// - dictionary
// - spell check
// - document word count/frequency
// - find all words beginning with given prefix
// - word prediction for typing/texting/

// Runtime of trie
// Type:   Best | Worst
// Search: O(1) | O(k) where k -> len of string
// Insert: O(k) | O(k)
// Delete: O(1) | O(k)

// Get index of child with the next letter: c[char - 'a']

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie {
    int isWord;
    struct trie *next[26];
} trie;

trie *init();
void insert(trie *t, char word[], int k);
int search(trie *t, char word[], int k);
void print_all(trie *t, char cur[]);
trie *delete(trie *t, char key[], int depth);
int is_empty(trie *t);

trie *init() {
    trie *my_tree = malloc(sizeof(trie));
    my_tree->isWord = 0;

    for (int i=0; i<26; i++) {
        my_tree->next[i] = NULL;
    }

    return my_tree;
}

int is_empty(trie *t) {
    for (int i=0; i<26; i++) {
        if (t->next[i]) {
            return 0;
        }
    }

    return 1;
}

void insert(trie *t, char word[], int k) {
    if (k == strlen(word)) {
        t->isWord = 1;
        return;
    }

    int next_index = word[k] - 'a';
    if (t->next[next_index] == NULL) {
        t->next[k] = init();
    }

    insert(t->next[next_index], word, k+1);
}

int search(trie *t, char word[], int k) {
    if (k == strlen(word)) {
        return t->isWord;
    }

    int next_index = word[k] - 'a';
    if (t->next[next_index] == NULL) {
        return 0;
    }

    return search(t->next[next_index], word, k+1);
}

trie *delete(trie *t, char key[], int k) {
    if (!t) {
        return NULL;
    }

    // if last character of the key is being processed
    if (key[k] == '\0') {
        if (t->isWord) {
            t->isWord = 0;
        }

        if(is_empty(t)) {
            free(t);
            t = NULL;
        }

        return t;
    }

    int index = key[k] - 'a';
    t->next[index] = delete(t->next[index], key, k+1);

    // if root does not have any child (its only child got deleted)
    // and it is not end of another word
    if (is_empty(t) && t->isWord == 0) {
        free(t);
        t = NULL;
    }

    return t;
}

int main() {
    struct trie *my_dictionary = init(); // create node function

    int i, n;
    FILE *ifp
}