#include <stdbool.h>
#include <stdlib.h>
#include "friend.h"

struct friend_m{
	int ID;
	void* friend;
};

struct friend_t{
	Set friends;
	copySetElements copyFriend;
	freeSetElements removeFriend;
	compareSetElements isAFriend;
};

Friend createFriend(Friend friend){
	if(!friend) return NULL;
	Friend new_friend = malloc(sizeof(*new_friend));
	if(!new_friend) return NULL;
	new_friend->ID = friend->ID;
	new_friend->friend = friend;
	return new_friend;
}

int getFriendID(Friend friend){
	return friend->ID;
}

Friend getFriendByID(FriendsSet friendSet, int ID){
	if(!friendSet) return NULL;
	SET_FOREACH(Friend,iterator,friendSet->friends){
		if(iterator->ID==ID) return iterator;
	}
	return NULL;
}

Set getFriendSetSet(FriendsSet friends){
	if(!friends) return NULL;
	return friends->friends;
}

FriendsSet getFriendSet(FriendsSet friends){
	if(!friends) return NULL;
	return friends;
}

int getFriendSetSize(FriendsSet friends){
	if(!friends) return 0;
	return setGetSize(friends->friends);
}

SetElement copyFriend(SetElement friend){
	return friend;
}

void freeFriend(SetElement friend){
	if(!friend) return;
	((Friend)friend)->friend=NULL;
	free((Friend)friend);
	return;
}

int compareFriend(SetElement friend1, SetElement friend2){
	return ((Friend)friend1)->ID - ((Friend)friend2)->ID;
}

FriendsSet createFriends(copySetElements copyFriend,freeSetElements removeFriend,
		compareSetElements isAFriend){
	if(!copyFriend || !removeFriend || !isAFriend) return NULL;
	FriendsSet new_set = malloc(sizeof(*new_set));
	if(!new_set) return NULL;
	new_set->friends = setCreate(copyFriend,removeFriend,compareFriend);
	if(!new_set){
		free(new_set);
		return NULL;
	}
	new_set->copyFriend = copyFriend;
	new_set->removeFriend = removeFriend;
	new_set->isAFriend = isAFriend;
	return new_set;
}

FriendResult addFriend(FriendsSet friends, Friend friend){
	if(!friends || !friend) return FRIEND_NULL_ARGUMENT;
	SetResult sr = setAdd(friends->friends, (SetElement)friend);
	if(sr==SET_OUT_OF_MEMORY) return FRIEND_MEMMORY_ERROR;
	if(sr==SET_ITEM_ALREADY_EXISTS) return FRIEND_ALREADY_EXISTS;
	return FRIEND_SUCCESS;
}

FriendResult removeFriend(FriendsSet friends, Friend friend){
	if(!friends || !friend) return FRIEND_NULL_ARGUMENT;
	SetResult sr = setRemove(friends->friends, (SetElement)friend);
	if(sr==SET_ITEM_DOES_NOT_EXIST) return FRIEND_NOT_EXISTS;
	return FRIEND_SUCCESS;
}

void friendsDestroy(FriendsSet friends){
	if(!friends) return;
	setDestroy(friends->friends);
	free(friends);
}

