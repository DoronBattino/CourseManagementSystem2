#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "friend.h"
#include "friend_request.h"
#include "student.h"
#include "test_utilities.h"

static bool createFriendRequestTest(){
	StudentResult sr = STUDENT_SUCCESS;
	StudentResult* result = &sr;

	Student s1 = createStudent(000000001,"Doron","Battino",result);
	Student s2 = createStudent(000000002,"Assaf","Regev",result);

	FriendRequestResult frr = createFriendRequest(s1,s2);
	ASSERT_TEST(frr==FRIEND_REQUEST_SUCCESS);
	ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==1);

	frr = createFriendRequest(s1,s2);
	ASSERT_TEST(frr==FRIEND_REQUEST_ALREADY_SENT);

	frr = createFriendRequest(s1,s1);
	ASSERT_TEST(frr==FRIEND_REQUEST_NO_SELF_REQUEST);

	studentDestroy(s1);
	studentDestroy(s2);
	return true;
}

static bool acceptFriendRequestTest(){
	StudentResult sr = STUDENT_SUCCESS;
	StudentResult* result = &sr;
	Student s1 = createStudent(000000001,"Doron","Battino",result);
	if(sr != STUDENT_SUCCESS) return false;
	Student s2 = createStudent(000000002,"Assaf","Regev",result);
	if(sr != STUDENT_SUCCESS) return false;
	FriendRequestResult frr = createFriendRequest(s1,s2);
	ASSERT_TEST(frr==FRIEND_REQUEST_SUCCESS);
	ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==1);

	FriendRequestResult frr1 = acceptFriendRequest(s2,s1);
	ASSERT_TEST(frr1==FRIEND_REQUEST_SUCCESS);
	ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(s2)))==1);
	ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==0);

	studentDestroy(s1);
	studentDestroy(s2);
	return true;
}

static bool rejectFriendRequestTest(){
	StudentResult sr = STUDENT_SUCCESS;
	StudentResult* result = &sr;
	Student s1 = createStudent(000000001,"Doron","Battino",result);
	if(sr != STUDENT_SUCCESS) return false;
	Student s2 = createStudent(000000002,"Assaf","Regev",result);
	if(sr != STUDENT_SUCCESS) return false;
	FriendRequestResult frr = createFriendRequest(s1,s2);
	ASSERT_TEST(frr==FRIEND_REQUEST_SUCCESS);

	ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==1);
	rejectFriendRequest(s2,s1);
	ASSERT_TEST(setGetSize(getFriendRequestSet(s2))==0);

	studentDestroy(s1);
	studentDestroy(s2);
	return true;
}

int main(){
	RUN_TEST(createFriendRequestTest);
	RUN_TEST(acceptFriendRequestTest);
	RUN_TEST(rejectFriendRequestTest);
	return 0;
}


