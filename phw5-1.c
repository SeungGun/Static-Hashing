#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKET_SIZE 33
typedef struct hashTable {
	char value[10];
	struct hashTable *next;
}Hash;
Hash table[BUCKET_SIZE];

//description : produces new node using malloc to connect to overflow key in hash table.
//input : key value to do overflow chaining.
//output : returns a new node's address including initialized member value.
Hash *newNode(char *key) {
	Hash *node;
	node = (Hash*)malloc(sizeof(Hash));
	node->next = NULL;
	strcpy(node->value, key);
	return node;
}
//description : plus ASCII code value of each alphabet for condition of hash function(sum % 33).
//input : a string to plus each alphabet. 
//output : returns sum of ASCII code value of each alphabet. 
int ASCIISum(char *key) {
	int sum = 0;
	int i = 0;
	while (key[i] != NULL) {
		sum += key[i];
		i++;
	}
	return sum;
}
//description : search a specific key from user in hash table.
//input : key to search
//output : if key found, prints search key, otherwise prints Not found.
void SearchHash(char *key) {
	for (int i = 0; i < BUCKET_SIZE; i++) {
		if (table[i].next == NULL) {
			if (strcmp(" ", table[i].value) == 0)continue;

			if (strcmp(key, table[i].value) == 0) {
				printf("[Search] : Found!\n");
				return;
			}
		}
		else {
			Hash *prev = NULL;
			Hash *ptr = table[i].next;
			while (ptr != NULL) {
				prev = table[i].next;
				if (strcmp(key, ptr->value) == 0) {
					printf("[Search] : Found!\n");
					return;
				}
				ptr = ptr->next;
			}
		}
	}
	printf("[Search] : Not found!\n");
}
//description : insert a specific key from user in hash table
//input : key to insert
//output : if same key is already existed, prints exist! ,otherwise, prints inserted.
void insertHash(char *key) {
	int index = ASCIISum(key) % BUCKET_SIZE;
	if (table[index].next == NULL) {
		if (strcmp(key, table[index].value) == 0) {
			printf("[Insert] : exists!\n");
			return;
		}
		if (strcmp(" ", table[index].value) == 0) {
			strcpy(table[index].value, key);
			printf("[Insert] : inserted!\n");
			return;
		}
	}
	else {
		int flag = 0;
		Hash *prev = NULL;
		Hash *ptr = table[index].next;
		while (ptr != NULL) {
			if (strcmp(key, table[index].next->value) == 0) {
				printf("[Insert] : exists!\n");
				return;
			}
			prev = ptr;
			ptr = ptr->next;
			if (ptr == NULL) {
				ptr = prev;
				flag = 1;
				ptr->next = newNode(key);
				printf("[Insert] : inserted!\n");
				break;
			}
		}
		if (!flag) {
			table[index].next = newNode(key);
			printf("[Insert] : inserted!\n");
			flag = 0;
		}
	}
}
//description : delete a specific key from user in the hash table
//input : key to delete
//output : if key found, prints delete, otherwise prints Not found.
void deleteHash(char *key) {
	for (int i = 0; i < BUCKET_SIZE; i++) {
		if (table[i].next == NULL) {
			if (strcmp(" ", table[i].value) == 0) continue;

			if (strcmp(key, table[i].value) == 0) {
				if (table[i].next == NULL) {
					printf("[Delete] : deleted!\n");
					strcpy(table[i].value, " ");
					return;
				}
			}
		}
		else {
			Hash *prev = NULL;
			Hash *ptr = table[i].next;
			while (ptr != NULL) {
				prev = ptr;
				if (strcmp(key, ptr->value) == 0) {
					printf("[Delete] : deleted!\n");
					if (ptr->next != NULL) {

						table[i].next = ptr->next;
						ptr->next = NULL;

					}
					else {
						ptr = NULL;
					}
					free(ptr);
					return;
				}
				ptr = ptr->next;
			}
		}
	}
	printf("[Delete] : Not found!\n");
}
//description : prints structurally all values in hash table. 
//input : none
//output : prints struct of hash table including overflow.	
void printTable() {
	printf("------------------------------------\n");
	printf("|  index  |  bucket  |  overflow Chaining => \n");
	for (int i = 0; i < BUCKET_SIZE; i++) {
		printf("    %d       ", i);
		if (strcmp(" ", table[i].value) == 0) printf("(null)");
		else printf("%s     ", table[i].value);
		if (table[i].next == NULL) printf("");
		else printf("%s     ", table[i].next->value);

		if (table[i].next == NULL) printf("");
		else printf("%s     ", table[i].next->next->value);

		if (table[i].next == NULL || table[i].next->next == NULL) printf("");
		else printf("%s     ", table[i].next->next->next->value);
		printf("\n");
	}
	printf("------------------------------------\n");
}
int main() {
	char buff[20][10];
	FILE *fp;
	if ((fp = fopen("keyinput.txt", "r")) == NULL) {
		printf("Error : read file failure\n");
		return 0;
	}
	for (int i = 0; i < 20; i++) fscanf(fp, "%s", buff[i]);
	
	for (int i = 0; i < BUCKET_SIZE; i++) {
		table[i].next = NULL;
		strcpy(table[i].value, " ");
	}

	int index = 0;
	for (int i = 0; i < 20; i++) {
		index = ASCIISum(buff[i]) % BUCKET_SIZE;
		if (strcmp(" ", table[index].value) == 0) {
			strcpy(table[index].value, buff[i]);
		}
		else {
			int flag = 0;
			Hash *prev = NULL;
			while (table[index].next != NULL) {	
				prev = table[index].next;
				table[index].next = table[index].next->next;
				if (table[index].next == NULL) {
					table[index].next = prev;
					flag = 1;
					table[index].next->next = newNode(buff[i]);
					break;
				}
			}
			if (!flag) {
				table[index].next = newNode(buff[i]);
				flag = 0;
			}
		}
	}

	printf("\n");
	printTable();
	printf("\n");

	SearchHash("Blue");
	SearchHash("black");
	SearchHash("Purple");
	printf("\n");

	deleteHash("Purple");
	deleteHash("Blue");
	deleteHash("Green");
	printf("\n");

	
	insertHash("Green");
	insertHash("White");
	insertHash("Golden");
	insertHash("nedloG");
	printf("\n");

	SearchHash("Blue");
	SearchHash("nedloG");
	SearchHash("Yellow");
	SearchHash("Green");
	printf("\n");

	printTable();
	printf("\n");

	fclose(fp);
}
