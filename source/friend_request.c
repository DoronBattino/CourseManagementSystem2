#include <stdbool.h>
#include <stdlib.h>
#include "friend_request.h"

struct friend_request{
	int ID;
};

int getRequestID(FriendRequest request){
	if(!request) return -1;
	return request->ID;
}

FriendRequest getFriendRequestByID(Set friendRequestSet, int ID){
	if(!friendRequestSet) return NULL;
	SET_FOREACH(FriendRequest,iterator,friendRequestSet){
		if(iterator->ID==ID) return iterator;
	}
	return NULL;
}

FriendRequestResult createFriendRequest(Student sender, Student receiver){
	if(!sender||!receiver) return FRIEND_REQUEST_NULL_ARGUMENT;
	if(getID(sender)==getID(receiver)) return FRIEND_REQUEST_NO_SELF_REQUEST;
	FriendRequest new_request = malloc(sizeof(*new_request));
	if(!new_request) return FRIEND_REQUEST_MEMORY_ERROR;
	new_request->ID = getID(sender);
	SetResult sr = setAdd(getFriendRequestSet(receiver),new_request);
	if(sr==SET_OUT_OF_MEMORY) return FRIEND_REQUEST_MEMORY_ERROR;
	if(sr==SET_ITEM_ALREADY_EXISTS){
		free(new_request);
		return FRIEND_REQUEST_ALREADY_SENT;
	}
	return FRIEND_REQUEST_SUCCESS;
}

FriendRequest getFriendRequest(Set set, int ID){
	if(!set) return NULL;
	SET_FOREACH(FriendRequest, iterator, set){
		if(iterator->ID==ID){
			return iterator;
		}
	}
	return NULL;
}

FriendRequestResult acceptFriendRequest(Student accepter, Student sender){
	FriendRequest fr=getFriendRequest(getFriendRequestSet(accepter),
			getID(sender));
	if(fr){
		Friend f1 = createFriend((Friend)sender);
		if(!f1) return FRIEND_REQUEST_MEMORY_ERROR;
		FriendResult fr1 = addFriend(getFriends(accepter), f1);
		if(fr1==FRIEND_MEMMORY_ERROR) return FRIEND_REQUEST_MEMORY_ERROR;
		if(fr1==FRIEND_ALREADY_EXISTS) return FRIEND_REQUEST_ALREADY_REQUESTED;
		if(fr1==FRIEND_SUCCESS){
			Friend f2 = createFriend((Friend)accepter);
			if(!f2) return FRIEND_REQUEST_MEMORY_ERROR;
			FriendResult fr2 = addFriend(getFriends(sender),f2);
			if(fr2==FRIEND_MEMMORY_ERROR){
				setRemove(getFriendSetSet(getFriends(accepter)),(Friend)sender);
				return FRIEND_REQUEST_MEMORY_ERROR;
			}
			setRemove(getFriendRequestSet(accepter),
				getFriendRequest(getFriendRequestSet(accepter),getID(sender)));
			return FRIEND_REQUEST_SUCCESS;
		}
	}
	return FRIEND_REQUEST_NOT_EXISTE;
}

FriendRequestResult rejectFriendRequest(Student rejecter, Student sender){
	if(!rejecter || !sender) return FRIEND_REQUEST_NULL_ARGUMENT;
	SetResult sr = setRemove(getFriendRequestSet(rejecter),
		getFriendRequest(getFriendRequestSet(rejecter),getID(sender)));
	if(sr==SET_ITEM_DOES_NOT_EXIST) return FRIEND_REQUEST_NOT_EXISTE;
	return FRIEND_REQUEST_SUCCESS;
}

SetElement copyFriendRequest(SetElement friendRequest){
	if(!friendRequest) return NULL;
	return friendRequest;
}

int compareFriendRequest(SetElement request1, SetElement request2){
	if(!request1 || !request2) return 0;
	if(((FriendRequest)request1)->ID==((FriendRequest)request2)->ID) return 0;
	if(((FriendRequest)request1)->ID>((FriendRequest)request2)->ID) return 1;
	return -1;
}

void freeFriendRequest(SetElement friendRequest){
	free(friendRequest);
}
