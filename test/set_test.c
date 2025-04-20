#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

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

static SetElement personCopy(SetElement person) {
	int age = ((Person)person)->age;
	bool loves_basketball = ((Person)person)->loves_basketball;
	return (SetElement) personCreate(((Person)person)->name, age,
			loves_basketball);
}

static int olderPerson(SetElement first, SetElement second) {
	return (((Person)first)->age - ((Person)second)->age);
}


static void personDestroy(SetElement person) {
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

static SetElement copyString(SetElement str) {
	ASSERT_TEST(str);
	char *copy = (char *)malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}



static int strCmp(SetElement s1, SetElement s2){
	ASSERT_TEST(s1 && s2);
	return strcmp((char *)s1, (char*)s2);
}



static Set generateSet(int x) {
	Set set;
	switch (x) {
	case 0:
		set = setCreate(copyString, free, strCmp);
		break;
	case 1:
		set = setCreate(copyString, free, strCmp);
		setAdd(set, "Maor");
		setAdd(set, "Assaf");
		setAdd(set, "Avi");
		setAdd(set, "Maria");
		setAdd(set, "Michal");
		break;
	case 2:
		set = setCreate(copyString, free, strCmp);
		setAdd(set, "We're leaving together");
		setAdd(set, "But still it's farewell");
		setAdd(set, "And maybe we'll come back");
		setAdd(set, "To earth, who can tell?");
		setAdd(set, "I guess there is no one to blame");
		setAdd(set, "We're leaving ground");
		setAdd(set, "Will things ever be the same again?");
		setAdd(set, "It's the final countdown!");
		break;
	// case 3:
	// 	set = setCreate(personCopy, personDestroy,strCmp);
	// 	Person persons[] = {
	// 			personCreate("Maor", 25, true),
	// 			personCreate("Assaf", 36, true),
	// 			personCreate("Maria", 28, false),
	// 			personCreate("Daniel", 23, true)
	// 	};
	// 	setAdd(set, persons[0]);
	// 	setAdd(set, persons[1]);
	// 	setAdd(set, persons[2]);
	// 	setAdd(set, persons[3]);
	// 	for (int i = 0; i < 4; i++) {
	// 		personDestroy((SetElement)persons[i]);
	// 	}
	// 	break;
	}
	return set;
}






static bool testSetCreate() {
	ASSERT_TEST(setCreate(NULL,NULL,NULL) == NULL);
	ASSERT_TEST(setCreate(copyString,NULL,NULL) == NULL);
	ASSERT_TEST(setCreate(NULL,free,NULL) == NULL);
    ASSERT_TEST(setCreate(NULL,NULL,strCmp) == NULL);
	Set set = generateSet(0);
	ASSERT_TEST(set != NULL);

	setDestroy(set);
	return true;
}



static bool testSetCopy() {
	Set set = generateSet(1);
	setGetFirst(set);
	setGetNext(set);
	setGetNext(set);

	Set set_copy = setCopy(NULL);
	ASSERT_TEST(set_copy == NULL);

	set_copy = setCopy(set);
	ASSERT_TEST(set_copy != NULL);
	ASSERT_TEST(setGetFirst(set) != NULL);
	ASSERT_TEST(strcmp(setGetFirst(set), setGetFirst(set_copy)) == 0);
	ASSERT_TEST(false == setIsIn(set, "Sharon"));
	setAdd(set, "Sharon");
	ASSERT_TEST(true == setIsIn(set, "Sharon"));
	setAdd(set_copy, "Sharon");
	ASSERT_TEST(strcmp(setGetFirst(set), setGetFirst(set_copy)) == 0);

	setDestroy(set);
	setDestroy(set_copy);
	return true;
}


static bool testSetGetSize() {
	Set empty_set = generateSet(0);
	ASSERT_TEST(setGetSize(empty_set) == 0);
	setDestroy(empty_set);
	ASSERT_TEST(setGetSize(NULL) == -1);

	Set set = generateSet(1);
	ASSERT_TEST(setGetSize(set) == 5);
	ASSERT_TEST(setIsIn(set, "Doron") == false);

	setDestroy(set);
	return true;
}


static bool testSetGetFirst() {
	ASSERT_TEST(setGetFirst(NULL) == NULL);

	Set set = generateSet(1);
	Set empty_set = generateSet(0);

	ASSERT_TEST(setGetFirst(empty_set) == NULL);
	ASSERT_TEST(setIsIn(set, "Maor") == true);

	setDestroy(empty_set);
	setDestroy(set);
	return true;
}



static bool testSetGetNext() {
	ASSERT_TEST(setGetNext(NULL) == NULL);
	Set set = generateSet(1);
	ASSERT_TEST(setGetNext(set) == NULL);

	setGetFirst(set);
	for (int i = 0; i < 4; i++) {
		ASSERT_TEST(setGetNext(set) != NULL);
	}
	ASSERT_TEST(setGetNext(set) == NULL);

	setGetFirst(set);
	ASSERT_TEST(setIsIn(set, "Assaf") == true);

	setDestroy(set);
	return true;
}


static bool testSetAdd() {
	ASSERT_TEST(setAdd(NULL, "b") == SET_NULL_ARGUMENT);

	Set set = generateSet(0);
	ASSERT_TEST(setGetFirst(set) == NULL);
	ASSERT_TEST(setAdd(set, "Moshe") == SET_SUCCESS);
	ASSERT_TEST(setIsIn(set, "Moshe") == true);
	ASSERT_TEST(setAdd(set, "Moshe") == SET_ITEM_ALREADY_EXISTS);
	ASSERT_TEST(setAdd(set, "Doron") == SET_SUCCESS);
	ASSERT_TEST(setAdd(set, "Doron") == SET_ITEM_ALREADY_EXISTS);

	setDestroy(set);
	return true;
}



static bool testSetRemove() {

	Set set = generateSet(1);
	ASSERT_TEST(setRemove(set,NULL) == SET_NULL_ARGUMENT);
	ASSERT_TEST(setRemove(set,"Doron") == SET_ITEM_DOES_NOT_EXIST);
	ASSERT_TEST(setGetSize(set) == 5);
	setGetFirst(set);
	ASSERT_TEST(setRemove(set,"Maor") == SET_SUCCESS);
	ASSERT_TEST(setGetSize(set) == 4);
	ASSERT_TEST(setRemove(set,"Hila") == SET_ITEM_DOES_NOT_EXIST);
	for (int i = 0; i < 4; i++) {
		ASSERT_TEST(setRemove(set,setGetFirst(set)) == SET_SUCCESS);
	}
	ASSERT_TEST(setGetSize(set) == 0);
	ASSERT_TEST(setRemove(set,setGetFirst(set)) == SET_NULL_ARGUMENT);

	setDestroy(set);
	return true;
}

static bool testSetClear() {
	Set song = generateSet(2);
	ASSERT_TEST(setClear(NULL) == SET_NULL_ARGUMENT);

	ASSERT_TEST(setGetSize(song) == 8);
	ASSERT_TEST(setClear(song) == SET_SUCCESS);
	ASSERT_TEST(setGetSize(song) == 0);
	ASSERT_TEST(setClear(song) == SET_SUCCESS);
	ASSERT_TEST(setGetSize(song) == 0);

	setDestroy(song);
	return true;
}


int main() {
	RUN_TEST(testSetCreate);
	RUN_TEST(testSetCopy);
	RUN_TEST(testSetGetSize);
	RUN_TEST(testSetGetFirst);
	RUN_TEST(testSetGetNext);
	RUN_TEST(testSetAdd);
	RUN_TEST(testSetRemove);
	RUN_TEST(testSetClear);
	return 0;
}