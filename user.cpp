#include "User.h"
#include "Post.h"
#include "Public.h"
#include "Follow.h"
#include "Private.h"
#include <iostream>
#include <fstream>
using namespace std;
void User::a_request(User* u) {
    User** temp = new User*[n_r + 1];
    for (int i = 0; i < n_r; ++i) temp[i] = requests[i];
    temp[n_r] = u;
    delete[] requests;
    requests = temp;
    ++n_r;
}
void User::r_request(User* u) {
    int idx = -1;
    for (int i = 0; i < n_r; ++i)
        if (requests[i] == u) idx = i;
    if (idx == -1) return;
    User** nr = new User*[n_r - 1];
    int k = 0;
    for (int i = 0; i < n_r; ++i)
        if (i != idx) nr[k++] = requests[i];
    delete[] requests;
    requests = nr;
    --n_r;
}
int User::get_requestcount() const {
return n_r;
}
User* User::get_requestuser(int idx) const {
    if (idx >= 0 && idx < n_r)
	return requests[idx];
    return NULL;
}
void User::a_sentrequest(User* u) {
    User** n = new User*[n_s_r + 1];
    for (int i = 0; i < n_s_r; ++i)
	n[i] = sentRequests[i];
    n[n_s_r] = u;
    delete[] sentRequests;
    sentRequests = n;
    ++n_s_r;
}
void User::r_sentrequest(User* u) {
    int idx = -1;
    for (int i = 0; i < n_s_r; ++i)
        if (sentRequests[i] == u) idx = i;
    if (idx == -1) return;
    User** new_sent = new User*[n_s_r - 1];
    int k = 0;
    for (int i = 0; i < n_s_r; ++i)
        if (i != idx) new_sent[k++] = sentRequests[i];
    delete[] sentRequests;
    sentRequests = new_sent;
    --n_s_r;
}
int User::get_sentrequestcount() const {
return n_s_r;
}
User* User::get_sentrequestuser(int idx) const {
    if (idx >= 0 && idx < n_s_r)
	return sentRequests[idx];
    return NULL;
}
User::~User() {
for (int i = 0; i < n_p; ++i){
    delete posts[i];
	posts[i]=NULL;	
	}
    for (int i = 0; i < n_follows; ++i) {
    	delete follows[i];
    	follows[i]=NULL;
	}
    for (int i = 0; i < n_followers; ++i){
    	   delete followers[i];
    	 followers[i]=NULL;
	}
    for (int i = 0; i < n_noti; ++i){
    	 delete notifications[i];
    	 notifications[i]=NULL;
	}
    for (int i = 0; i < n_r; ++i) {
delete requests[i];
    	requests[i]=NULL;
	}
for (int i = 0; i < n_s_r; ++i){
    	 delete sentRequests[i];
    	 sentRequests[i]=NULL;
	}
    delete[] posts;
    delete[] follows;
    delete[] followers;
    delete[] notifications;
    delete[] requests;
    delete[] sentRequests;
}
String User::getid() const
{ 
return id; 
}
bool User::is_pub() const
{ 
return is_public; 
}
String User::getpass() const
{ 
return pass; 
}
void User::a_followed(Follow* f) {
    Follow** nfs = new Follow*[n_follows + 1];
    for (int i = 0; i < n_follows; ++i) {
    if (follows)
        nfs[i] = follows[i];
    else
        nfs[i] = NULL;
}
    nfs[n_follows] = f;
    delete[] follows;
    follows = nfs;
    nfs=NULL;
    ++n_follows;
}
void User::a_follower(Follow* f) {
    Follow** nfr = new Follow*[n_followers + 1];
    for (int i = 0; i < n_followers; ++i) {
    if (followers)
        nfr[i] = followers[i];
    else
        nfr[i] = NULL;
}
    nfr[n_followers] = f;
    delete[] followers;
    followers = nfr;
    nfr=NULL;
    ++n_followers;
}
int User::get_followcount() const {
    return n_follows;
}
User* User::get_followeduser(int idx) const {
    if (idx >= 0 && idx < n_follows && follows[idx])
	return follows[idx]->followed;
    return NULL;
}
int User::get_followercount() const {
    return n_followers;
}
User* User::get_followeruser(int idx) const {
    if (idx >= 0 && idx < n_followers && followers[idx])
	return followers[idx]->follower;
    return NULL;
}
void User::a_post(Post* post) {
    Post** np = new Post*[n_p + 1];
    for (int i = 0; i < n_p; ++i) {
    if (posts)
        np[i] = posts[i];
    else
        np[i] = NULL;
}
    np[n_p] = post;
    delete[] posts;
    posts = np;
    ++n_p;
}
int User::get_postcount() const {
return n_p;
}
Post* User::get_post(int idx) const {
	if(idx >= 0 && idx < n_p){
		return posts[idx];
	}
	return NULL;
}
void User::a_noti(Notification* n) {
    Notification** nn = new Notification*[n_noti + 1];
    for (int i = 0; i < n_noti; ++i) nn[i] = notifications[i];
    nn[n_noti] = n;
    delete[] notifications;
    notifications = nn;
    ++n_noti;
}
void User::print_notifications() const {
    if (n_noti == 0) cout << "You have no notifications.\n";
    for (int i = 0; i < n_noti; ++i) notifications[i]->print();
}
void User::print_userinfo() const {
    cout << "User ID: "; id.print(); cout << endl;
    cout << "Name: "; name.print(); cout << endl;
    cout << "Bio: "; bio.print(); cout << endl;
    cout << "DOB: "; dob.print(); cout << endl;
    cout << "Followers: " << n_followers << ", Following: " << n_follows << endl;
    cout << "Posts: " << n_p << endl;
    for (int i = 0; i < n_p; ++i) {
        cout << "  ";
        posts[i]->print();
    }
}
void User::save_users(const char* f, User** users, int n_u) {
    ofstream fout(f, ios::binary|ios::trunc);
    fout.seekp(0);
    fout.write((char*)&n_u, sizeof(n_u));
    for (int i = 0; i < n_u; ++i) {
        String id = users[i]->getid();
        id.wif(fout);
        String pass = users[i]->getpass();
        pass.wif(fout);
        bool isPub = users[i]->is_pub();
        fout.write((char*)&isPub, sizeof(isPub));
        users[i]->name.get_f().wif(fout);
        users[i]->name.get_l().wif(fout);
        users[i]->bio.wif(fout);
        int y = users[i]->dob.year, m = users[i]->dob.month, d = users[i]->dob.day;
        fout.write((char*)&y, sizeof(y));
        fout.write((char*)&m, sizeof(m));
        fout.write((char*)&d, sizeof(d));
    }
    fout.close();
}
User** User::load_users(const char* f, int& n_u) {
    ifstream fin(f, ios::binary);
    fin.seekg(0);
    fin.read((char*)&n_u, sizeof(n_u));
    User** users = new User*[n_u];
    for (int i = 0; i < n_u; ++i) {
        String id, pass, fname, lname, bio;
        id.rif(fin);
        pass.rif(fin);
        bool isPub;
        fin.read((char*)&isPub, sizeof(isPub));
        fname.rif(fin);
        lname.rif(fin);
        bio.rif(fin);
        int y, m, d;
        fin.read((char*)&y, sizeof(y));
        fin.read((char*)&m, sizeof(m));
        fin.read((char*)&d, sizeof(d));
        if (isPub)
            users[i]=new Public(id,fname,lname,Date(y,m,d),pass,bio);
        else
            users[i]=new Private(id,fname,lname,Date(y,m,d),pass,bio);
    }
    fin.close();
    return users;
}
User::User():id(""),bio(""),pass(""),dob(Date()),posts(NULL),n_p(0), follows(NULL), n_follows(0), followers(NULL), n_followers(0), notifications(NULL), n_noti(0), is_public(true), requests(NULL), n_r(0), sentRequests(NULL), n_s_r(0) {}
User::User(const String& userid, const String& fname, const String& lname, const Date& dob, const String& p, const String& b, bool pub):id(userid), name(fname, lname), bio(b), pass(p), dob(dob), posts(NULL), n_p(0), follows(NULL), n_follows(0), followers(NULL), n_followers(0), notifications(NULL), n_noti(0), is_public(pub), requests(NULL), n_r(0), sentRequests(NULL), n_s_r(0) {}
