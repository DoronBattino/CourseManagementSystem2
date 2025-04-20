#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "friend.h"
#include "friend_request.h"
#include "student.h"
#include "test_utilities.h"

static bool createStudentTest(){
	StudentResult value = STUDENT_SUCCESS;
	StudentResult* result = &value;

	Student s1 = createStudent(-2,"Doron","Battino",result);
	ASSERT_TEST(s1==NULL);
	ASSERT_TEST(*result==STUDENT_INVALID_ID);

	Student s2 = createStudent(301387593,"","",result);
	ASSERT_TEST(s2==NULL);
	ASSERT_TEST(*result==STUDENT_NULL_ARGUMENT);

	Student s3 = createStudent(301387593,"Doron","Battino",result);
	ASSERT_TEST(s3!=NULL);
	ASSERT_TEST(*result==STUDENT_SUCCESS);

	studentDestroy(s3);
	return true;
}

static bool unfriendTest(){
		StudentResult sr = STUDENT_SUCCESS;
		StudentResult* result = &sr;
		Student s1 = createStudent(000000001,"Doron","Battino",result);
		Student s2 = createStudent(000000002,"Assaf","Regev",result);
		FriendRequestResult frr = createFriendRequest(s1,s2);
		ASSERT_TEST(frr==FRIEND_REQUEST_SUCCESS);
		ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==1);
		FriendRequestResult frr1 = acceptFriendRequest(s2,s1);
		ASSERT_TEST(frr1==FRIEND_REQUEST_SUCCESS);
		ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(s2)))==1);
		ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==0);

		sr = unfriend(s2,s1);
		ASSERT_TEST(sr==STUDENT_SUCCESS);
		ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(s2)))==0);
		sr = unfriend(s2,s1);
		ASSERT_TEST(sr==STUDENT_NOT_A_FRIEND);

		studentDestroy(s1);
		studentDestroy(s2);
		return true;
}

int main(){
	RUN_TEST(createStudentTest);
	RUN_TEST(unfriendTest);
	return 0;
}

