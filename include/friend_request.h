#ifndef FRIEND_REQUEST_H_
#define FRIEND_REQUEST_H_

#include <stdbool.h>
#include "student.h"
#include "friend.h"

/**Type for defining friend request*/
typedef struct friend_request *FriendRequest;

/**Error codes for friend request*/
typedef enum{
	FRIEND_REQUEST_SUCCESS,
	FRIEND_REQUEST_MEMORY_ERROR,
	FRIEND_REQUEST_NULL_ARGUMENT,
	FRIEND_REQUEST_ALREADY_SENT,
	FRIEND_REQUEST_ALREADY_REQUESTED,
	FRIEND_REQUEST_NOT_EXISTE,
	FRIEND_REQUEST_NO_SELF_REQUEST
}FriendRequestResult;

/**Gets the request ID
 * @param FriendRequest the request to take ID from
 * @return the ID of the request*/
int getRequestID(FriendRequest);

/**Gets the friend request by ID
 * param Set- the set to search in.
 * param ID the ID to look for.*/
FriendRequest getFriendRequestByID(Set friendRequestSet, int ID);

/**Create a friend request for a student
 * @param Student - the sender of request.
 * @param Student - the receiver of request.
 * @return FRIEND_REQUEST_MEMORY_ERROR if a memory error was  occurred or
 * invalid id.
 * FRIEND_REQUEST_NULLARGUMENT if a null was sent.
 * FRIEND_REQUEST_SUCCESS if the request was sent successfully.
 * the friend request in case of success */
FriendRequestResult createFriendRequest(Student, Student);

/**Accept a friend request
 * @param Student- the accepter.
 * @param Student- the sender.
 * @return
 * FRIEND_REQUEST_NULL_ARGUMET if a null was sent.
 * FRIEND_REQUEST_MEMORY_ERROR if a memory allocation failed.
 * FRIEND_REQUEST_SUCCESS if the student who sent the request been added
 * 						  as a friend.
 * */
FriendRequestResult acceptFriendRequest(Student, Student);

/**Gets a friend request
 * @param set- the friend request set to search in.
 * @param friendRequest- the request to get
 * @return
 * NULL- if no such request or the request in case it found.*/
FriendRequest getFriendRequest(Set, int);

/**Reject a friend request
 * @param Student- the rejecter
 * @param Student- the sender*/
FriendRequestResult rejectFriendRequest(Student, Student);

/**Copy a friend request*/
SetElement copyFriendRequest(SetElement friendRequest);

/**Comparing requests by ID*/
int compareFriendRequest(SetElement, SetElement);

/**Deallocates a friend request
 * @param FriendRequest the request to remove.*/
void freeFriendRequest(SetElement);

#endif /* FRIEND_REQUEST_H_ */
