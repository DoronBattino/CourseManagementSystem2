#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

#define RUN_TEST(test)                    \
    do {                                  \
        printf("Running %s... ", #test);  \
        test();                           \
        printf("✓ Passed\n");             \
    } while (0)

#define ASSERT_TEST(expr)                                        \
    do {                                                         \
        if (!(expr)) {                                           \
            printf("❌ Assertion failed at %s:%d: %s\n",          \
                   __FILE__, __LINE__, #expr);                   \
            break;                                              \
        }                                                        \
    } while (0)

/*----------------------------------
 * start of static Person
 ----------------------------------*/
typedef struct s_person {
	char *name;
	int age;
	bool loves_basketball;
} *Person;

static Person personCreate(char *name, int age, bool loves_basketball) {
	Person person = malloc(sizeof(*person));
	if (!person) {
		return NULL;
	}
	person->name = malloc(strlen(name) + 1);
	if (!person->name) {
		free(person);
		return NULL;
	}
	strcpy(person->name, name);
	person->age = age;
	person->loves_basketball = loves_basketball;
	return person;
}

static ListElement personCopy(ListElement person) {
	int age = ((Person)person)->age;
	bool loves_basketball = ((Person)person)->loves_basketball;
	return (ListElement) personCreate(((Person)person)->name, age,
			loves_basketball);
}

static int olderPerson(ListElement first, ListElement second, ListSortKey key) {
	return (((Person)first)->age - ((Person)second)->age)-*(int*)key;
}

static bool lovesBasketball(ListElement person, ListFilterKey loves_basketball) {
	if ( ((Person)person)->loves_basketball == *(bool*)loves_basketball ) {
		return true;
	}
	return false;
}

static void personDestroy(ListElement person) {
	char *name = ((Person)person)->name;
	printf("Deleting %s!\n", name);
	if ( (Person)person != NULL ) {
		free( ((Person)person)->name );
		free( person );
	}
}
/*----------------------------------
 * end of static Person
 ----------------------------------*/

static bool isLongerThan(ListElement str, ListFilterKey key) {
	return ((int)strlen(str) > *(int*) key);
}

static bool wordExist(ListElement str, ListFilterKey key) {
	return (strstr((char*) str, (char*) key) != NULL);
}

static int compareStrLength(ListElement first, ListElement second, ListSortKey key) {
	return (strlen((char*)first) - strlen((char*)second)) - *(int*)key;
}

static ListElement copyString(ListElement str) {
	ASSERT_TEST(str);
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

static List generateList(int x) {
	List list;
	switch (x) {
	case 0:
		list = listCreate(copyString, free);
		break;
	case 1:
		list = listCreate(copyString, free);
		listInsertLast(list, "Maor");
		listInsertLast(list, "Assaf");
		listInsertLast(list, "Avi");
		listInsertLast(list, "Maria");
		listInsertLast(list, "Michal");
		break;
	case 2:
		list = listCreate(copyString, free);
		listInsertLast(list, "We're leaving together");
		listInsertLast(list, "But still it's farewell");
		listInsertLast(list, "And maybe we'll come back");
		listInsertLast(list, "To earth, who can tell?");
		listInsertLast(list, "I guess there is no one to blame");
		listInsertLast(list, "We're leaving ground");
		listInsertLast(list, "Will things ever be the same again?");
		listInsertLast(list, "It's the final countdown!");
		break;
	case 3:
		list = listCreate(personCopy, personDestroy);
		Person persons[] = {
				personCreate("Maor", 25, true),
				personCreate("Assaf", 36, true),
				personCreate("Maria", 28, false),
				personCreate("Daniel", 23, true)
		};
		listInsertLast(list, persons[0]);
		listInsertLast(list, persons[1]);
		listInsertLast(list, persons[2]);
		listInsertLast(list, persons[3]);
		for (int i = 0; i < 4; i++) {
			personDestroy((ListElement)persons[i]);
		}
		break;
	}
	return list;
}

/**
 * List of tests, one for each function is usually a good thumb rule.
 */
static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,free) == NULL);
	List list = generateList(0);
	ASSERT_TEST(list != NULL);

	listDestroy(list);
	return true;
}

static bool testListCopy() {
	List list = generateList(1);
	listGetFirst(list);
	listGetNext(list);
	listGetNext(list);

	List list_copy = listCopy(NULL);
	ASSERT_TEST(list_copy == NULL);

	list_copy = listCopy(list);
	ASSERT_TEST(list_copy != NULL);
	ASSERT_TEST(listGetCurrent(list_copy) != NULL);
	ASSERT_TEST(strcmp(listGetCurrent(list), listGetCurrent(list_copy)) == 0);
	listGetNext(list);
	ASSERT_TEST(strcmp(listGetCurrent(list), listGetCurrent(list_copy)) != 0);
	ASSERT_TEST(strcmp(listGetFirst(list), listGetFirst(list_copy)) == 0);
	listInsertFirst(list, "Sharon");
	listInsertFirst(list_copy, "Sharon");
	ASSERT_TEST(strcmp(listGetFirst(list), listGetFirst(list_copy)) == 0);

	listDestroy(list);
	listDestroy(list_copy);
	return true;
}

static bool testListGetSize() {
	List empty_list = generateList(0);
	ASSERT_TEST(listGetSize(empty_list) == 0);
	listDestroy(empty_list);
	ASSERT_TEST(listGetSize(NULL) == -1);

	List list = generateList(1);
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(listGetCurrent(list) == NULL);

	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
	ASSERT_TEST(listGetFirst(NULL) == NULL);

	List list = generateList(1);
	List empty_list = generateList(0);

	ASSERT_TEST(listGetFirst(empty_list) == NULL);
	ASSERT_TEST(strcmp(listGetFirst(list), "Maor") == 0);

	listDestroy(empty_list);
	listDestroy(list);
	return true;
}

static bool testListGetNext() {
	ASSERT_TEST(listGetNext(NULL) == NULL);
	List list = generateList(1);
	ASSERT_TEST(listGetNext(list) == NULL);

	listGetFirst(list);
	for (int i = 0; i < 4; i++) {
		ASSERT_TEST(listGetNext(list) != NULL);
	}
	ASSERT_TEST(listGetNext(list) == NULL);

	listGetFirst(list);
	ASSERT_TEST(strcmp(listGetNext(list), "Assaf") == 0);

	listDestroy(list);
	return true;
}

static bool testListGetCurrent() {
	ASSERT_TEST(listGetCurrent(NULL) == NULL);

	List list = generateList(1);
	ASSERT_TEST(listGetCurrent(list) == NULL);
	listGetFirst(list);
	ASSERT_TEST(strcmp(listGetCurrent(list), "Maor") == 0);
	listGetNext(list);
	ASSERT_TEST(strcmp(listGetCurrent(list), "Assaf") == 0);

	for (int i = 0; i < 6; i++) {
		listGetNext(list);
	}
	ASSERT_TEST(listGetCurrent(list) == NULL);

	List empty_list = generateList(0);
	ASSERT_TEST(listGetCurrent(empty_list) == NULL);

	listDestroy(empty_list);
	listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
	ASSERT_TEST(listInsertFirst(NULL, "b") == LIST_NULL_ARGUMENT);

	List list = generateList(0);
	ASSERT_TEST(listGetFirst(list) == NULL);
	ASSERT_TEST(listInsertFirst(list, "Moshe") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(list), "Moshe") == 0);

	listDestroy(list);
	return true;
}

static bool testListInsertLast() {
	ASSERT_TEST(listInsertLast(NULL, "b") == LIST_NULL_ARGUMENT);
	List list1 = generateList(0);
	ASSERT_TEST(listInsertLast(list1, "Miri") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(list1), "Miri") == 0);

	List list2 = generateList(1);
	ASSERT_TEST(listInsertLast(list2, "Miri") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(list2), "Maor") == 0);
	for (int i = 0; i < 5; i++) {
		listGetNext(list2);
	}
	ASSERT_TEST(strcmp(listGetCurrent(list2), "Miri") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list2), "Miro") != 0);

	listDestroy(list1);
	listDestroy(list2);
	return true;
}

static bool testListInsertBeforeCurrent() {
	ASSERT_TEST(listInsertBeforeCurrent(NULL, "b") == LIST_NULL_ARGUMENT);

	List song = generateList(2);
	ASSERT_TEST(listInsertBeforeCurrent(song, "b") == LIST_INVALID_CURRENT);

	char str[] = "Help! I need somebody!";
	listGetFirst(song);
	ASSERT_TEST(strcmp(listGetFirst(song), str) != 0);
	ASSERT_TEST(listInsertBeforeCurrent(song, str) == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(song), str) == 0);
	listGetNext(song);
	listGetNext(song);
	ASSERT_TEST(listInsertBeforeCurrent(song, str) == LIST_SUCCESS);
	listGetFirst(song);
	listGetNext(song);
	ASSERT_TEST(strcmp(listGetCurrent(song), str) != 0);
	listGetNext(song);
	ASSERT_TEST(strcmp(listGetCurrent(song), str) == 0);

	listGetFirst(song);
	for (int i = 0; i < 9; i++) {
		listGetNext(song);
	}
	ASSERT_TEST(strcmp(listGetCurrent(song), "It's the final countdown!") == 0);
	ASSERT_TEST(listInsertBeforeCurrent(song, str) == LIST_SUCCESS);

	ASSERT_TEST(listGetNext(song) == NULL);

	listDestroy(song);
	return true;
}

static bool testListInsertAfterCurrent() {
	ASSERT_TEST(listInsertAfterCurrent(NULL, "b") == LIST_NULL_ARGUMENT);

	List song = generateList(2);
	ASSERT_TEST(listInsertAfterCurrent(song, "b") == LIST_INVALID_CURRENT);

	listGetFirst(song);
	for (int i = 0; i < 7; i++) {
		listGetNext(song);
	}
	ASSERT_TEST(strcmp(listGetCurrent(song), "It's the final countdown!") == 0);
	char str[] = "We don't need no education";
	ASSERT_TEST(listInsertAfterCurrent(song, str) == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(song), "It's the final countdown!") == 0);
	ASSERT_TEST(strcmp(listGetNext(song), str) == 0);

	listDestroy(song);
	return true;
}

static bool testListRemoveCurrent() {
	ASSERT_TEST(listRemoveCurrent(NULL) == LIST_NULL_ARGUMENT);

	List list = generateList(1);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);
	ASSERT_TEST(listGetSize(list) == 5);
	listGetFirst(list);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(list) == 4);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);
	for (int i = 0; i < 4; i++) {
		listGetFirst(list);
		ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
	}
	ASSERT_TEST(listGetSize(list) == 0);
	listGetFirst(list);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);

	listDestroy(list);
	return true;
}

static bool testListSort() {
	List list = generateList(1);
	ASSERT_TEST(listSort(NULL, compareStrLength, 0) == LIST_NULL_ARGUMENT);
	ASSERT_TEST(listSort(list, NULL, 0) == LIST_NULL_ARGUMENT);

	listGetFirst(list);
	ASSERT_TEST(strcmp(listGetNext(list), "Assaf") == 0);
	int b = 0;
	int* key1 = &b;
	ASSERT_TEST(listSort(list, compareStrLength, key1) == LIST_SUCCESS);
	ASSERT_TEST(listGetCurrent(list) != NULL);
	ASSERT_TEST(strcmp(listGetCurrent(list), "Maor") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "Assaf") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "Maria") == 0);
	ASSERT_TEST(strlen(listGetNext(list)) == strlen("michal"));
	ASSERT_TEST(strcmp(listGetFirst(list), "Avi") == 0);

	List list2 = generateList(3);
	listGetFirst(list2);
	int age = ((Person)listGetNext(list2))->age;
	ASSERT_TEST(age == 36);
	int a=0;
	ListSortKey key = &a;
	ASSERT_TEST(listSort(list2, olderPerson , key) == LIST_SUCCESS);
	age = ((Person)listGetCurrent(list2))->age;
	ASSERT_TEST(age == 25);


	listDestroy(list);
	listDestroy(list2);
	return true;
}

static bool testListClear() {
	List song = generateList(2);
	ASSERT_TEST(listClear(NULL) == LIST_NULL_ARGUMENT);

	ASSERT_TEST(listGetSize(song) == 8);
	ASSERT_TEST(listClear(song) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(song) == 0);
	ASSERT_TEST(listClear(song) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(song) == 0);

	listDestroy(song);
	return true;
}

static bool testListFilter() {
	List names = generateList(1);

	int size = 4;
	ASSERT_TEST(listFilter(names, NULL, &size) == NULL);
	ASSERT_TEST(listFilter(NULL, isLongerThan, &size) == NULL);

	List filtered_names = listFilter(names, isLongerThan, &size);
	ASSERT_TEST(filtered_names != NULL);
	ASSERT_TEST(listGetCurrent(filtered_names) == NULL);


	List song = generateList(2);
	char word[] = "the";
	List filtered_song = listFilter(song, wordExist, word);
	printf("\n%s\n", (char*) listGetFirst(filtered_song));
	for (int i = 0; i < 3; i++) {
		printf("%s\n", (char*) listGetNext(filtered_song));
	}
	ASSERT_TEST(listGetSize(filtered_song) == 4);


	List persons = generateList(3);
	bool love_it = true;
	List filtered_persons = listFilter(persons, lovesBasketball, &love_it);
	ASSERT_TEST(listGetSize(filtered_persons) == 3);

	love_it = false;
	List filtered_persons2 = listFilter(persons, lovesBasketball, &love_it);
	ASSERT_TEST(listGetSize(filtered_persons2) == 1);

	List filtered_persons3 = listFilter(filtered_persons, lovesBasketball, &love_it);
	ASSERT_TEST(listGetSize(filtered_persons3) == 0);


	listDestroy(names);
	listDestroy(filtered_names);
	listDestroy(song);
	listDestroy(filtered_song);
	listDestroy(persons);
	listDestroy(filtered_persons);
	listDestroy(filtered_persons2);
	listDestroy(filtered_persons3);

	return true;
}

static bool testListDestroy() {
	return true;
}

int main() {
	RUN_TEST(testListCreate);
	RUN_TEST(testListCopy);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListGetNext);
	RUN_TEST(testListGetCurrent);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListSort);
	RUN_TEST(testListClear);
	RUN_TEST(testListFilter);
	RUN_TEST(testListDestroy);
	return 0;
}
