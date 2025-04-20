

#ifndef FRIEND_H_
#define FRIEND_H_
#include <stdbool.h>
#include "set.h"



/**Type for defining a friend*/
typedef struct friend_m *Friend;

/** Type for defining the set */
typedef struct friend_t *FriendsSet;

/**Error codes*/
typedef enum{
	FRIEND_SUCCESS,
	FRIEND_ALREADY_EXISTS,
	FRIEND_NOT_EXISTS,
	FRIEND_MEMMORY_ERROR,
	FRIEND_NULL_ARGUMENT
}FriendResult;

/**Getting the friend set size*/
int getFriendSetSize(FriendsSet friends);

/**Gets the friends set*/
FriendsSet getFriendSet(FriendsSet);

/**Gets the friends set set*/
Set getFriendSetSet(FriendsSet friends);

/**Gets the friend ID*/
int getFriendID(Friend);

/**Gets a friend by his ID*/
Friend getFriendByID(FriendsSet,int);

/**Create student as a friend if request accepted
 * @param friend - the new friend
 * @return
 * NULL if a null argument was sent or the new friend*/
Friend createFriend(Friend friend);

/**If a friend request accepted the student will pass on to the set*/
SetElement copyFriend(SetElement friend);

/**Removes a students from friends set
 * @param friend - the student to be removed.
 * */
void freeFriend(SetElement friend);

/**Compare friend in the the set with a given friend
 * to see if a friend already in the set*/
int compareFriend(SetElement friend1, SetElement friend2);

/** Allocates a new empty friend set
 * @param copyElement - Function pointer to be used for copying elements into
 * 		the set or when copying the set.
 * @param freeElement - Function pointer to be used for removing elements from
 * 		the set
 * @param compareElements - Function pointer to be used for comparing elements
 * 		inside the set. Used to check if new elements already exist in the set.
 * @return
 * 	NULL - if one of the parameters is NULL or allocations failed.
 * 	A new Set in case of success.
 * */
FriendsSet createFriends(copySetElements copyFriend,freeSetElements removeFriend,
		compareSetElements compareFriend);

/**Add a student as a friend
 * @param friends-  a set of friends.
 * @param friend- a friend to add.
 * @return
 * 	FRIEND_NULL_ARGUMENT if a friend set or a friend is NULL.
 * 	FRIEND_ALREADY_FRIEND if the friend found in the set.
 * 	FRIEND_MEMMORY_ERROR if a memory problem occurred.
 * 	FRIEND_SUCCESS if the friend was added.
 *
 * */
FriendResult addFriend(FriendsSet friends, Friend friend);

/**Remove a friend from the friends set
 * @param friends-  a set of friends.
 * @param friend- a friend to remove.
 * @return
 * FRIEND_NULL_ARGUMENT if a friend set or a friend is NULL.
 * FRIEND_SUCCESS if the friend was removed.*/
FriendResult removeFriend(FriendsSet friends, Friend friend);

/** Deallocates the friend set
 * @param friends - the friend set to deallocate
 * */
void friendsDestroy(FriendsSet friends);

#endif /* FRIEND_H_ */
