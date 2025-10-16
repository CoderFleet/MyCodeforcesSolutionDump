
using namespace chrono;
typedef unsigned long long H; 
static H C;
static H L;
struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(str.size()+1), pw(ha) {
        pw[0] = 1;
        for(int i=0;i<str.size();i++)   
            ha[i+1] = (ha[i] * L + str[i]-'a'+1)%C,
            pw[i+1] = (pw[i] * L)%C;
    }
    H hashInterval(int a, int b){       // 
        return (ha[b] - ha[a] * pw[b - a]%C+C)%C;
    }
}; 
template<typename T>
bool isPrime(T N) {
    if(N<2)return false;
    if(N<4)return true;
    if(N%2==0 or N%3==0)return false;
    T curr=5;
    while(curr*curr<=N){
\tif(N%curr==0)return false;
        curr+=2;
        if(N%curr==0)return false;
        curr+=4;
    }
    return true;
}
/*  USAGE!
    string t;
    cin>>t;
    precompH();

    HashInterval alpha(t);      //computes hash for the entire string..

    alpha.hashInterval(l,r);        // gives you the hash interval for this range!
*/
void precompH(){                //  [DONT FORGET TO USE THIS !!! -> CALLING ONCE IS FINE!]
    mt19937 rng(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
    uniform_int_distribution<unsigned long long> distribution(1000000000,4000000000);
    uniform_int_distribution<unsigned long long> distribution2(31,200);
    C = distribution(rng);
    L = distribution2(rng);
    while(!isPrime(C))C++;
}