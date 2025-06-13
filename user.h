#ifndef USER_H
#define USER_H
#include "String.h"
#include "Date.h"
#include "Name.h"
#include "Notification.h"
#include <fstream>
#include <iostream>
using namespace std;
class Post;
class Follow;
class User {
protected:
	User** requests;
    int n_r;
    User** sentRequests;
    int n_s_r;
    Name name;
    String id, bio, pass;
    Date dob;
    Post** posts;
    int n_p;
    Follow** follows;
    int n_follows;
    Follow** followers;
    int n_followers;
    Notification** notifications;
    int n_noti;
    bool is_public;
public:
	    void a_request(User* u);
    void r_request(User* u);
    int get_requestcount() const;
    User* get_requestuser(int idx) const;
    void a_sentrequest(User* u);
    void r_sentrequest(User* u);
    int get_sentrequestcount() const;
    User* get_sentrequestuser(int idx) const;
    User();
    User(const String& userid, const String& fname, const String& lname, const Date& dob, const String& p, const String& b, bool pub);
    virtual ~User();
    String getid() const;
    bool is_pub() const;
    String getpass() const;
    virtual void follow(User* other) = 0;
    void a_followed(Follow* f);
    void a_follower(Follow* f);
    int get_followcount() const;
    User* get_followeduser(int idx) const;
    int get_followercount() const;
    User* get_followeruser(int idx) const;
    void a_post(Post* post);
    int get_postcount() const;
    Post* get_post(int idx) const;
    void a_noti(Notification* n);
    void print_notifications() const;
    void print_userinfo() const;
    static void save_users(const char* f, User** users, int n_u);
    static User** load_users(const char* f, int& n_u);
};
#endif
