#include "Post.h"
#include "User.h"
#include "Reply.h"
#include <fstream>
#include <iostream>
using namespace std;
Post::Post(const String& id, const String& msg, User* user)
    : id(id), msg(msg), user(user), replies(NULL), n_rep(0), likes(NULL), n_likes(0) {}
Post::~Post() {
    for (int i = 0; i < n_rep; ++i) delete replies[i];
    for (int i = 0; i < n_likes; ++i) likes[i]=NULL;
    delete[] replies;
    delete[] likes;
}
String Post::get_id() const{
return id;
}
void Post::print() const {
    cout << "Post ID: "; id.print(); cout << " | By user: "; user->getid().print(); cout << " | "; msg.print(); cout << endl;
    cout << "Likes: " << n_likes << " | Replies: " << n_rep << endl;
    for (int i = 0; i < n_rep; ++i) {
        cout << "  ";
        replies[i]->print();
    }
}
void Post::add_like(User* u) {
    for (int i = 0; i < n_likes; ++i)
        if (likes[i] == u) return;
    User** new_likes = new User*[n_likes + 1];
    for (int i = 0; i < n_likes; ++i) new_likes[i] = likes[i];
    new_likes[n_likes] = u;
    delete[] likes;
    likes = new_likes;
    ++n_likes;
}
void Post::add_reply(User* user, const String& msg) {
    Reply** new_replies = new Reply*[n_rep + 1];
    for (int i = 0; i < n_rep; ++i) new_replies[i] = replies[i];
    new_replies[n_rep] = new Reply(user, msg);
    delete[] replies;
    replies = new_replies;
    ++n_rep;
}
int Post::get_likecount() const
{
return n_likes;
}
int Post::get_replycount() const {
return n_rep;
}
User* Post::get_user() const {
return user;
}
User* Post::get_likeuser(int idx) const
{
    if (idx >= 0 && idx < n_likes) return likes[idx];
    return NULL;
}

Reply* Post::get_reply(int idx) const {
    if (idx >= 0 && idx < n_rep) return replies[idx];
    return NULL;
}

void Post::wif(std::ofstream& fout) const {
    id.wif(fout);
    user->getid().wif(fout);
    msg.wif(fout);
    fout.write((char*)&n_rep, sizeof(n_rep));
    for (int i = 0; i < n_rep; ++i)
        replies[i]->wif(fout);
    fout.write((char*)&n_likes, sizeof(n_likes));
    for (int i = 0; i < n_likes; ++i)
        likes[i]->getid().wif(fout);
}
Post* Post::rif(std::ifstream& fin, User** users, int userCount) {
    String id, uid, msg;
    id.rif(fin);
    uid.rif(fin);
    msg.rif(fin);
    User* u = NULL;
    for (int i = 0; i < userCount; ++i)
        if (users[i]->getid() == uid) u = users[i];
    if (!u) return NULL;
    Post* p = new Post(id, msg, u);
    fin.read((char*)&p->n_rep, sizeof(p->n_rep));
    p->replies = new Reply*[p->n_rep];
    for (int i = 0; i < p->n_rep; ++i)
        p->replies[i] = Reply::rif(fin, users, userCount);
    fin.read((char*)&p->n_likes, sizeof(p->n_likes));
    p->likes = new User*[p->n_likes];
    for (int i = 0; i < p->n_likes; ++i) {
   String l;
		l.rif(fin);
        p->likes[i] = NULL;
        for (int j = 0; j < userCount; ++j)
            if (users[j]->getid()==l)
			p->likes[i] = users[j];
    }
    return p;
}
