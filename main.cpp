#include <iostream>
#include <fstream>
#include "User.h"
#include "Public.h"
#include "Follow.h"
#include "Private.h"
#include "Post.h"
#include "Notification.h"
#include "Reply.h"
using namespace std;
bool lower(char ch){
    return(ch>='a'&&ch<='z');
}
bool upper(char ch){
    return(ch>='A'&&ch<='Z');
}
bool digit(char ch){
    return(ch>='0'&&ch<='9');
}
template <class T>
int strLen(const T* s){
int len = 0;
    while(s[len]!='\0')
len++;
    return len;
}
bool valid_p(const char* p) {
    int len = strLen(p);
    if (len < 8)
        return false;
    bool lo = false, up = false, di = false, sy = false;
    for (int i = 0; i < len; i++) {
        char ch = p[i];
        if (lower(ch))
            lo = true;
        else if (upper(ch))
            up = true;
        else if (digit(ch))
            di = true;
        else
            sy = true;
    }
    return lo && up && di && sy;
}
void savefollows(const char* f, User** users, int n_users) {
    ofstream fout(f, ios::binary|ios::trunc);
    fout.seekp(0);
    int tf = 0;
    for (int i = 0; i < n_users; ++i)
    tf+=users[i]->get_followcount();
    fout.write((char*)&tf, sizeof(tf));
    for (int i = 0; i < n_users; ++i) {
        for (int j = 0; j < users[i]->get_followcount(); ++j) {
            User* fd = users[i]->get_followeduser(j);
            users[i]->getid().wif(fout);
            if (fd)
                fd->getid().wif(fout);
            else
                String("").wif(fout);
        }
    }
    fout.close();
}
void loadfollows(const char* f, User** users, int n_users) {
    ifstream fin(f, ios::binary);
    int tf;
    fin.read((char*)&tf, sizeof(tf));
    for (int i = 0; i < tf; ++i) {
        String fid, fdid;
        fid.rif(fin);
        fdid.rif(fin);
        User* fr = NULL;
        User* fd = NULL;
        for (int j = 0; j < n_users; ++j) {
            if (users[j]->getid() == fid) fr = users[j];
            if (users[j]->getid() == fdid) fd = users[j];
        }
        if (fr && fd) {
            Follow* f = new Follow(fr, fd);
            fr->a_followed(f);
            fd->a_follower(f);
        }
    }
    fin.close();
}
void saveposts(const char* f, User** users, int n_users) {
    ofstream fout(f, ios::binary|ios::trunc);
    fout.seekp(0);
    int t_p = 0;
    for (int i = 0; i < n_users; ++i)
    t_p+=users[i]->get_postcount();
    fout.write((char*)&t_p, sizeof(t_p));
    for (int i = 0; i < n_users; ++i) {
        for (int j = 0; j < users[i]->get_postcount(); ++j) {
            Post* p = users[i]->get_post(j);
            p->wif(fout);
        }
    }
    fout.close();
}
void loadposts(const char* f, User** users, int n_users) {
    ifstream fin(f, ios::binary);
    int t_p;
    fin.read((char*)&t_p, sizeof(t_p));
    for (int i = 0; i < t_p; ++i) {
        Post* p = Post::rif(fin, users, n_users);
        if (p && p->get_user())
            p->get_user()->a_post(p);
    }
    fin.close();
}
void printusers(User** users, int n_users) {
    cout << "All users:\n";
    for (int i = 0; i < n_users; ++i) {
        cout << i + 1 << ". ";
        users[i]->getid().print();
        cout << " (";
        if (users[i]->is_pub()) cout << "Public";
        else cout << "Private";
        cout << ")\n";
    }
}
int main() {
    int userc= 0;
User** users = User::load_users("users.bin",userc);
loadfollows("follows.bin", users, userc);
loadposts("posts.bin", users, userc);
cout<<"Total number of users: "<<userc;
    User* ME = NULL;
    while (true) {
        cout << "\n***** Social Media Main Menu *****\n";
        cout << "1. Create account\n";
        cout << "2. Login\n";
        cout << "3. Show all users\n";
        cout << "4. Exit\n";
        cout<<"**********************************\n";
        cout << "Choose: ";
        int ch;
        cin >> ch;
        cin.ignore();
        if (ch == 1) {
            cout << "Enter user id: ";
            char idch[100];
            cin.getline(idch,100);
            String id(idch);
            cout << "First name: ";
            char fch[100];
            cin.getline(fch,100);
            String fname(fch);
            cout << "Last name: ";
            char lch[100];
            cin.getline(lch,100);
            String lname(lch);
            String pass;
            bool val=false;
            while(!val){
            cout << "Password:\n";
            cout << "*Atleast one(uppercase,lowercase,number,symbol).\n*Should be atleast 8 characters.\nEnter: ";
            char pch[100];
            try{
            cin.getline(pch,100);
            if(!valid_p(pch)){
            	throw "Password not valid.";
			}
			String temp(pch);
			pass=temp;
			val=true;
			}
			catch(const char* ch){
				cout<<"\n"<<ch<<"\n";
			}
			}
            cout << "Bio: ";
            char bch[200];
            cin.getline(bch,200);
            String bio(bch);
            int y, m, d;
            cout << "Birth year: "; cin >> y;
            cout << "Birth month: "; cin >> m;
            cout << "Birth day: "; cin >> d;
            cin.ignore();
            cout << "Public account? (1=Yes, 0=No): ";
            int pub;
            cin >> pub;
            cin.ignore();
            User* u;
            if (pub == 1)
                u = new Public(id, fname, lname, Date(y,m,d), pass, bio);
            else
          u = new Private(id, fname, lname, Date(y,m,d), pass, bio);
            User** n_u = new User*[userc+1];
            for (int i = 0; i < userc; ++i) n_u[i] = users[i];
            n_u[userc] = u;
            delete[] users;
            users = n_u;
            n_u=NULL;
            userc++;
            cout << "Account created!\n";
        }
		else if (ch == 2) {
            cout << "Enter user id: ";
            char idch[100];
            cin.getline(idch,100);
            String id(idch);
            cout << "Password: ";
            char pcha[100];
            cin.getline(pcha,100);
            String pass(pcha);
            ME = NULL;
            for (int i = 0; i < userc; ++i)
                if (users[i]->getid() == id && users[i]->getpass() == pass)
                    ME = users[i];
            if (ME == NULL) {
                cout << "Login failed.\n";
            }
			else {
                cout << "Login done!\n";
                while (true) {
                    cout << "\n********** User Menu **********\n";
                                  cout << "1. Show user info\n";
                    cout << "2. Create a post\n";
                    cout << "3. Show my posts\n";
                    cout << "4. Like a post\n";
                    cout << "5. Reply to a post\n";
                    cout << "6. Follow a user\n";
                    cout << "7. Show my followers\n";
                cout << "8. Show my following\n";
                    cout << "9. Show notifications\n";
                    cout << "10. Show all users\n";
                    cout << "11. Logout\n";
                    cout << "12. Show received follow requests\n";
cout << "13. Accept a follow request\n";
cout << "14. Reject a follow request\n";
cout << "15. Show sent follow requests\n";
cout << "16. For You Page\n";
cout<<"***************************************************\n";
                    cout << "Choose: ";
                    int op;
                    cin >> op;
                    cin.ignore();
                    if (op == 1) {
                        ME->print_userinfo();
                    }
					else if (op == 2) {
                        cout << "Enter post content: ";
                        char pst[200];
                        cin.getline(pst,200);
                        String msg(pst);
                        String pid=ME->getid()+String("_post")+String("1");
                        Post* p=new Post(pid,msg,ME);
                        ME->a_post(p);
                        cout << "Posted!\n";
                    }
		else if (op == 3) {
                int pc=ME->get_postcount();
                if(pc==0)cout<<"No posts.\n";
                        for(int i=0;i<pc;++i){
                            cout<<i+1<<". ";
                            ME->get_post(i)->print();
                        }
                    }
		else if (op == 4) {
                        printusers(users, userc);
                    cout << "Enter user id whose post you want to like: ";
                    char fo[100];
                        cin.getline(fo,100);
                        String fid(fo);
                        User* ou = NULL;
                        for (int i = 0; i < userc; ++i)
                            if (users[i]->getid() == fid)
                                ou = users[i];
                    bool flag = false;
for (int i = 0; i<ME->get_followcount();++i)
    if (ME->get_followeduser(i) == ou)
        flag = true;
if (!flag) {
    cout << "You donot follow this user.\n";
    break;
}
                        if (ou == NULL) {
                            cout << "No user with this id.\n";
                        }
				else {
                        int pc = ou->get_postcount();
                            if (pc == 0) cout << "No posts.\n";
                            else {
                                for (int i = 0; i < pc; ++i) {
                                    cout << i + 1 << ". ";
                                    ou->get_post(i)->print();
                                }
                                cout << "Enter post number to like: ";
                                int pn;
                                cin >> pn;
                                cin.ignore();
                                if (pn< 1||pn>pc)cout<<"Invalid.\n";
                                else {
                                    Post* post=ou->get_post(pn-1);
                                    post->add_like(ME);
                                    Notification* n = new Notification(ME->getid() + String(" has liked your post."));
                                    ou->a_noti(n);
                                    cout << "Liked!\n";
                                }
                            }
                        }
                    }
			else if (op == 5) {
                        printusers(users, userc);
                        cout << "Enter user id whose post to reply: ";
                char f5[100];
                cin.getline(f5,100);
                        String fid(f5);
                User* ou = NULL;
                        for (int i = 0; i < userc; ++i)
                            if (users[i]->getid() == fid)
                                ou = users[i];
                                bool flag = false;
for (int i = 0; i < ME->get_followcount(); ++i)
    if (ME->get_followeduser(i) == ou)
        flag = true;
if (!flag) {
    cout << "You donnot follow this user.\n";
    break;
}
                    if (ou == NULL) {
                            cout << "No user with this id.\n";
                        }
			else {
                            int pc = ou->get_postcount();
                            if (pc == 0) cout << "No posts.\n";
                    else {
                                for (int i = 0; i < pc; ++i) {
                                    cout << i + 1 << ". ";
                                    ou->get_post(i)->print();
                                }
                                cout << "Enter post number to reply: ";
                                int pn;
                                cin >> pn;
                                cin.ignore();
                                if (pn< 1||pn> pc) cout << "Invalid.\n";
                                else {
                                    cout << "Enter reply: ";
                                    char rch[300];
                                    cin.getline(rch,300);
                                    ou->get_post(pn- 1)->add_reply(ME, String(rch));
                            Notification* n = new Notification(ME->getid() + String(" has replied to your post."));
                                ou->a_noti(n);
                            cout << "Replied!\n";
                                }
                            }
                        }
                    }
		else if (op == 6) {
                printusers(users,userc);
                cout<<"Enter user id to follow: ";
                        char f6[100];
                        cin.getline(f6,100);
       String fid(f6);
                        User* ou = NULL;
            for (int i = 0; i < userc; ++i)
                            if (users[i]->getid() == fid)
                                ou = users[i];
                        if (ou == NULL) {
                            cout << "No user with this id.\n";
                        }
						else {
                            ou->follow(ME);
                        }
                    }
				else if (op==7) {
                        int fc = ME->get_followercount();
                        if (fc == 0) cout << "You have no followers.\n";
                        for (int i = 0; i < fc; ++i) {
                            User* u = ME->get_followeruser(i);
                            if (u) {
                                u->getid().print();
                                cout << endl;
                            }
                        }
                    }
		else if (op==8){
        int fc = ME->get_followcount();
                        if (fc == 0) cout << "you are not following anyone.\n";
    for (int i = 0; i < fc; ++i) {
                            User* u = ME->get_followeduser(i);
                            if (u) {
                                u->getid().print();
                                cout << endl;
                            }
                        }
                    }
					else if (op == 9) {
                        ME->print_notifications();
                    }
					else if (op == 10) {
                        printusers(users,userc);
                    }
					else if (op == 11) {
                        break;
                    }
                    else if (op == 12) {
    if (!ME->is_pub()) {
        int rc = ME->get_requestcount();
        if (rc == 0) cout << "You have no follow requests.\n";
        for (int i = 0; i < rc; ++i) {
            User* u = ME->get_requestuser(i);
            if (u) { u->getid().print(); cout << endl; }
        }
    } else {
        cout << "You have public account.\n";
    }
} else if (op == 13) {
    if (!ME->is_pub()) {
        int rc = ME->get_requestcount();
        if (rc == 0) cout << "You have no follow requests.\n";
        else {
            for (int i = 0; i < rc; ++i) {
                cout << i + 1 << ". ";
                ME->get_requestuser(i)->getid().print();
                cout << endl;
            }
    cout << "Enter request number to accept: ";
            int rn;
            cin >> rn;
            cin.ignore();
            if(rn<1||rn> rc) cout << "Invalid.\n";
            else {
                User* otherus = ME->get_requestuser(rn- 1);
                Follow* f = new Follow(otherus, ME);
                otherus->a_followed(f);
                ME->a_follower(f);
             Notification* n = new Notification(ME->getid() + String(" accepted your follow request."));
        otherus->a_noti(n);
      ME->r_request(otherus);
                otherus->r_sentrequest(ME);
                cout << "Accepted.\n";
            }
        }
    }
	else {
        cout << "You have public account.\n";
    }
} else if (op == 14) {
    if (!ME->is_pub()) {
        int rc = ME->get_requestcount();
        if (rc == 0) cout << "You have no follow requests.\n";
        else {
            for (int i = 0; i < rc; ++i) {
                cout << i + 1 << ". ";
                ME->get_requestuser(i)->getid().print();
                cout << endl;
            }
            cout << "Enter request number to reject: ";
            int rno;
            cin >> rno;
            cin.ignore();
            if (rno<1||rno>rc)cout<< "Invalid.\n";
            else {
                User* otheruser = ME->get_requestuser(rno- 1);
                Notification* n = new Notification(ME->getid() + String(" rejected your follow request."));
                otheruser->a_noti(n);
        ME->r_request(otheruser);
                otheruser->r_sentrequest(ME);
cout << "Rejected!\n";
            }
        }
    } else {
        cout << "You have public account.\n";
    }
}
else if (op == 15) {
    int sc=ME->get_sentrequestcount();
    if (sc == 0) cout << "You have no sent follow requests.\n";
    for (int i = 0; i < sc; ++i) {
        User* u = ME->get_sentrequestuser(i);
        if (u) { u->getid().print(); cout << endl; }
    }
                }
                else if (op == 16) {
    int fc = ME->get_followcount();
    if (fc == 0) cout << "You are not following any user.\n";
    else {
        for (int i = 0; i < fc; ++i) {
            User* otheru = ME->get_followeduser(i);
            if (otheru) {
                int pc = otheru->get_postcount();
                for (int j = 0; j < pc; ++j) {
                    otheru->get_post(j)->print();
                }
            }
        }
    }
}
            }
        }
		
    }
    else if (ch == 3) {
            printusers(users, userc);
        } else if (ch == 4) {
User::save_users("users.bin", users, userc);
savefollows("follows.bin", users, userc);
saveposts("posts.bin", users, userc);
            break;
        }
    }
    return 0;
}
