#ifndef POST_H
#define POST_H
#include "String.h"
#include"iostream"
#include"fstream"
using namespace std;
class User;
class Reply;
class Post {
    String id;
    String msg;
    User* user;
    Reply** replies;
    int n_rep;
    User** likes;
    int n_likes;
public:
    Post(const String& id, const String& msg, User* user);
    ~Post();
    String get_id() const;
    void print() const;
    void add_like(User* u);
    void add_reply(User* user, const String& msg);
    int get_likecount() const;
    User* get_likeuser(int idx) const;
    int get_replycount() const;
    Reply* get_reply(int idx) const;
    User* get_user() const;
    void wif(ofstream& fout) const;
    static Post* rif(ifstream& fin, User** users, int userCount);
};
#endif
