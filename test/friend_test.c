#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "friend.h"
#include "test_utilities.h"

typedef struct Student{
	char* name;
	int age;
}*Student;

static Student creatStudent(char* name, int age){
	if(!name) return NULL;
	Student new_Student1 = (Student)malloc(sizeof(*new_Student1));
	if(!new_Student1) return NULL;
	new_Student1->name = (char*)malloc(strlen(name)+1);
	if(!new_Student1->name){
		free(new_Student1);
		return NULL;
	}
	new_Student1->name = strcpy(new_Student1->name,name);
	new_Student1->age = age;
	return new_Student1;
}
static void destroyStudent(Student student){
	free(((Student)student)->name);
	((Student)student)->age = 0;
	free(student);
}


///////////////////////////////END OF Student////////////////////////////////


///////////////////TEST FUNCTIONS FOR EVERY FRIEND FUNCTION/////////////////



int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	FriendsSet new_set = createFriends(copyFriend,freeFriend,compareFriend);

	Student s1 = creatStudent("Assaf",32);
	Friend new_friend1 = createFriend((Friend)s1);
    addFriend(new_set,new_friend1);

	Student s2 = creatStudent("Amit",23);
	Friend new_friend2 = createFriend((Friend)s2);
	addFriend(new_set,new_friend2);

	Student s3 = creatStudent("Doron",25);
	Friend new_friend3 = createFriend((Friend)s3);
	addFriend(new_set,new_friend3);

	Student s4 = creatStudent("Ofirchuk",21);
	Friend new_friend4 = createFriend((Friend)s4);
	addFriend(new_set,new_friend4);

	Student s5 = creatStudent("Ariel",22);
	Friend new_friend5 = createFriend((Friend)s5);
	addFriend(new_set, new_friend5);

	Student s6 = creatStudent("Tales",23);
	Friend new_friend6 = createFriend((Friend)s6);
	addFriend(new_set, new_friend6);

	Student s7 = creatStudent("Bar",19);
	Friend new_friend7 = createFriend((Friend)s7);

	int size = getFriendSetSize(new_set);
	ASSERT_TEST(size==6);

	//TESTS CREATE FRIENDS
	ASSERT_TEST(createFriends(NULL,NULL,NULL)==NULL);
	ASSERT_TEST(new_set!=NULL);

	//TESTS REMOVE
	removeFriend(new_set, new_friend3);
	size = getFriendSetSize(new_set);
	ASSERT_TEST(size==5);

	ASSERT_TEST(removeFriend(new_set, new_friend7)==FRIEND_NOT_EXISTS);
	ASSERT_TEST(addFriend(new_set, new_friend2)==FRIEND_ALREADY_EXISTS);

	printf("%d\n", getFriendID(new_friend1));
	printf("%d\n", getFriendID(new_friend2));
	printf("%d\n", getFriendID(new_friend4));
	printf("%d\n", getFriendID(new_friend5));
	printf("%d\n", getFriendID(new_friend6));
	printf("%d\n", getFriendID(new_friend7));

	ASSERT_TEST(getFriendID(getFriendByID(new_set, getFriendID(new_friend1)))==getFriendID(new_friend1));

	free(new_friend7);
	destroyStudent(s7);
	destroyStudent(s1);
	destroyStudent(s2);
	destroyStudent(s3);
	destroyStudent(s4);
	destroyStudent(s5);
	destroyStudent(s6);
	friendsDestroy(new_set);
	return 0;
}
