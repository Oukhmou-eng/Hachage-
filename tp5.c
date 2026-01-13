#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    int cle ; 
    int valeur ;
    struct Node* suivant ;
}Node ;

typedef struct {
    int taille ; 
    Node** table ;
}HashTable ;

int hashFunction(int key, int taille) {
    return key % taille ;
}
// Initialisation de la table de hachage
HashTable* initHashTable(int taille) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->taille = taille ;
    ht->table = (Node**)malloc(taille * sizeof(Node*));
    for(int i = 0 ; i < taille ; i++) {
        ht->table[i] = NULL ;
    }
    return ht ;
}

void libererHashTable(HashTable* ht) {
    for(int i = 0 ; i < ht->taille ; i++) {
        Node* current = ht->table[i];
        while(current != NULL) {
            Node* temp = current;
            current = current->suivant ;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

void inserer(HashTable* ht, int key, int valeur) {
    int index = hashFunction(key, ht->taille);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->cle = key ;
    newNode->valeur = valeur ;
    newNode->suivant = ht->table[index];
    ht->table[index] = newNode ;
}
int rechercher(HashTable* ht, int key) {
    int index = hashFunction(key, ht->taille);
    Node* current = ht->table[index];
    while(current != NULL) {
        if(current->cle == key) {
            return 1 ;
        }
        current = current->suivant ;
    }
    return 0; // Indiquer que la clé n'a pas été trouvée
}



//supprimer une cle  
int supprimer(HashTable* ht, int key) {
    int index = hashFunction(key, ht->taille);
    Node* current = ht->table[index];
    Node* prev = NULL ;
    while(current != NULL) {
        if(current->cle == key) {
            if(prev == NULL) {
                ht->table[index] = current->suivant ;
            } else {
                prev->suivant = current->suivant ;
            }
            free(current);
            return 1; // Suppression réussie
        }
        prev = current ;
        current = current->suivant ;
    }
    return 0; // Clé non trouvée
}

void affichage_table(HashTable* ht) {
  
      printf("Affichage de la table de hachage:\n");
      printf("=======================================\n");
      printf("|| Index   ||   [Cle / Valeur]       ||\n");
      printf("=======================================\n");

    for(int i = 0 ; i < ht->taille ; i++) {
        Node* current = ht->table[i];
       
        printf("|| Index %d:||  ", i);
        while(current != NULL) {
            printf("[%d|%d] ==> ", current->cle, current->valeur);
            current = current->suivant ;
        }
        printf(" [NULL] \n");
    }
    printf("===========================================\n");
}
int main() {
    HashTable* ht = initHashTable(10);
    inserer(ht, 1, 100);
    inserer(ht, 2, 200);
    inserer(ht, 3, 500);
    inserer(ht, 12, 300); // Collision avec clé 2

    affichage_table(ht);

    printf("Recherche cle 2: %d\n", rechercher(ht, 2));
    printf("Recherche cle 3: %d\n", rechercher(ht, 3));

    supprimer(ht, 2);
    printf("Après suppression de la cle 2:\n");
    affichage_table(ht);

    libererHashTable(ht);
    return 0;
}




