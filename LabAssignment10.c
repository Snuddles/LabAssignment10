#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max size of the Trie nodes
#define ALPHABET_SIZE 26

// Creates the struct of the Trie
struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    int count;
};

void insert(struct Trie **ppTrie, char *word);
int numberOfOccurrences(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

// Inserts character into node
void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;
    if (!pTrie) {
        pTrie = (struct Trie *) calloc(1, sizeof(struct Trie));
        *ppTrie = pTrie;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
            if (!pTrie->children[c]) {
                pTrie->children[c] = (struct Trie *) calloc(1, sizeof(struct Trie));
            }
            pTrie = pTrie->children[c];
        }
    }
    pTrie->count++;
}

//Returns the amount of children for the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    if (!pTrie) {
        return 0;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
            pTrie = pTrie->children[c];
            if (!pTrie) {
                return 0;
            }
        }
    }
    return pTrie->count;
}

// Deallocates/free memory of the children node then the tree itself
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (!pTrie) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Main function
int main(void) {
    struct Trie *trie = NULL;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
        printf("%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}   
