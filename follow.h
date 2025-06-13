#ifndef FOLLOW_H
#define FOLLOW_H
class User;
class Follow {
public:
    User* follower;
    User* followed;
    Follow(User* follower, User* followed);
};
#endif
