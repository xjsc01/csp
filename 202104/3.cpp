#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, Tdef, Tmax, Tmin;
string H;
#define UN 0
#define WAIT 1
#define USE 2
#define OUT 3
int nowTime;
struct Baowen{
    string send, receive;
    string type;
    int ip;
    int Tout;
};

struct IpPoll{
    int Tout, type;
    string who;
}ipPoll[20000];


void sendOffer(int ip){
    auto &x = ipPoll[ip];
    cout << H << " " << x.who << " " << "OFR" << " " << ip << " " << x.Tout << "\n";
}
void sendAck(int ip){
    cout << H << " " << ipPoll[ip].who << " " << "ACK" << " " << ip << " " << ipPoll[ip].Tout << "\n";
}
void sendNak(string x, int fakeIp){
    cout << H << " " << x << " " << "NAK" << " " << fakeIp << " " << 0 << "\n";
}

inline int searchIp(string &d){
    for(int i = 1; i <= n; i++){
        if(ipPoll[i].who == d) return i;
    }
    for(int i = 1; i <= n; i++){
        if(ipPoll[i].type == UN) return i;
    }
    for(int i = 1; i <= n; i++){
        if(ipPoll[i].type == OUT) return i;
    }
    return -1;
}

void run(Baowen &b){
    {// 判断是否是本主机
        if(b.receive.compare(H) && b.receive.compare(string("*")) && b.type != "REQ") return;
        if(b.type != "DIS" && b.type != "REQ") return;
        if(b.receive.compare(string("*"))==0 && b.type != "DIS") return;
        if(b.receive.compare(H)==0 && b.type == "DIS") return;
    }
    
    if(b.type == "DIS"){
        int getIp;
        getIp = searchIp(b.send);
        if(getIp == -1) return;
        ipPoll[getIp].type = WAIT;
        ipPoll[getIp].who = b.send;
        int Tdue;
        if(b.Tout){
            Tdue = b.Tout - nowTime;//!!!!!!!!!!!
            Tdue = max(Tmin, Tdue);
            Tdue = min(Tmax, Tdue);
        }
        else{
            Tdue = Tdef;
        }
        ipPoll[getIp].Tout = nowTime + Tdue;
        sendOffer(getIp);
    }

    else if(b.type == "REQ"){
        if(b.receive.compare(H) != 0){
            for(int i = 1; i <= n; i++){
                if(ipPoll[i].who == b.send && ipPoll[i].type == WAIT){
                    ipPoll[i].type = UN;
                    ipPoll[i].Tout = 0;
                    ipPoll[i].who.clear();
                }
            }
        }
        else{
            if(b.ip < 1 || b.ip > n || ipPoll[b.ip].who.compare(b.send) != 0) {
                sendNak(b.send, b.ip);
            }
            else{
                
                ipPoll[b.ip].type = USE;
                int Tdue;
                if(b.Tout){
                    Tdue = b.Tout - nowTime;
                    Tdue = max(Tmin, Tdue);
                    Tdue = min(Tmax, Tdue);
                }
                else{
                    Tdue = Tdef;
                }
                ipPoll[b.ip].Tout = nowTime + Tdue;
                sendAck(b.ip);
            }
        }
    }
    
}

inline void ck(){
    for(int i = 1; i <= n; i++){
        if(ipPoll[i].Tout <= nowTime){
            auto &x = ipPoll[i];
            if(x.type == USE){
                x.Tout = 0;
                x.type = OUT;
            }
            else if(x.type == WAIT){
                x.Tout = 0;
                x.type = UN;
                x.who.clear();
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> Tdef >> Tmax >> Tmin >> H;
    for(int i = 1; i <= n; i++){
        ipPoll[i].Tout = 0;
        ipPoll[i].type = UN;
        ipPoll[i].Tout = 0;
    }
    int inNum;
    cin >> inNum;
    for(int _ = 1; _ <= inNum; _ ++){
        Baowen b;
        cin >> nowTime >> b.send >> b.receive >> b.type >> b.ip >> b.Tout;
        ck();//!!!!!!!!!!!!!!
        run(b);
    }
    return 0;
}
/*
4 5 10 5 dhcp
1
1 a * DIS 0 0
2 a dhcp REQ 1 0
3 b a DIS 0 0
4 b * DIS 3 0
5 b * REQ 2 12
6 b dhcp REQ 2 12
7 c * DIS 0 11
8 c dhcp REQ 3 11
9 d * DIS 0 0
10 d dhcp REQ 4 20
11 a dhcp REQ 1 20
12 c dhcp REQ 3 20
13 e * DIS 0 0
14 e dhcp REQ 2 0
15 b dhcp REQ 2 25
16 b * DIS 0 0
*/