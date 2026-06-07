#include <bits/stdc++.h>
using namespace std;

struct User {
    string name;
    int budget;
    int energy;
    set<string> tags;
    bool active = true;
};

struct Activity {
    int id;
    string name;
    int cost;
    int duration;
    int energy;
    string tag;
};

struct Input {
    int N, D, H;
    vector<User> users;
    map<int, Activity> activities;     // ordered by id
    vector<string> events;             // verbatim event lines
};

static Input readInput() {
    Input in;
    cin >> in.N >> in.D >> in.H;
    in.users.resize(in.N);
    for (int i = 0; i < in.N; i++) {
        int k;
        cin >> in.users[i].name >> in.users[i].budget >> in.users[i].energy >> k;
        for (int j = 0; j < k; j++) {
            string t; cin >> t;
            in.users[i].tags.insert(t);
        }
        in.users[i].active = true;
    }
    int A; cin >> A;
    for (int i = 0; i < A; i++) {
        Activity a;
        cin >> a.id >> a.name >> a.cost >> a.duration >> a.energy >> a.tag;
        in.activities[a.id] = a;
    }
    int E; cin >> E;
    cin.ignore();
    for (int i = 0; i < E; i++) {
        string line;
        getline(cin, line);
        // trim
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
        in.events.push_back(line);
    }
    return in;
}

/** Format a single day line exactly per spec. Use REST if ids is empty. */
static string formatDay(int day, vector<int> ids, int cost, int sat) {
    if (ids.empty()) {
        return "Day "+to_string(day)+": REST | cost=0 satisfaction=0";
    }
    sort(ids.begin(), ids.end());
    string s = "Day "+to_string(day)+": ";
    for (size_t i = 0; i < ids.size(); i++) {
        if (i) s += ' ';
        s += to_string(ids[i]);
    }
    s += " | cost="+to_string(cost)+" satisfaction="+to_string(sat);
    return s;
}

// =========================================================================
// YOUR CODE GOES HERE.
//
// Implement solve(const Input& in) and return the FULL output string
// (including the trailing newline) that the judge will diff against
// the expected output.
//
// Helpers available from the Head section:
//   - formatDay(day, ids, cost, sat)  -> properly formatted "Day X: ..." line
//   - in.users        : vector<User>           ({name, budget, energy, tags, active})
//   - in.activities   : map<int,Activity>      ({id, name, cost, duration, energy, tag})
//   - in.events       : vector<string>         verbatim event lines, e.g.
//                       "DROP 2 Bob", "WEATHER 3 NATURE",
//                       "FATIGUE 2 Alice 5", "BUDGET 4 Alice 20"
// =========================================================================
static string solve(Input in) {
    string out;
    out += "=== PLAN ===\n";

    vector<vector<User>> tmlusers(in.D+1, in.users);
    vector<set<string>> wBlock(in.D+1);

    vector<vector<int>> ids(in.D+1);
    vector<int> costs(in.D+1, 0);
    vector<int> sat(in.D+1, 0);

    // TODO 1: build the initial D-day plan.
    //   for (int day = 1; day <= in.D; day++) {
    //       out += formatDay(day, chosenIds, totalCost, satisfaction) + "\n";
    //   }
    auto rp = [&](int st) {
        set<int> used;
        for(int d = 1; d < st; d++) {
            for(int id : ids[d]) {
                used.insert(id);
            }
        }
        
        for(int d = st; d <= in.D; d++) {
            vector<User> actusers;
            for(auto& u: tmlusers[d]) {
                if(u.active) {
                    actusers.push_back(u);
                }
            }
            
            if(actusers.empty()) {
                ids[d].clear();
                costs[d] = 0;
                sat[d] = 0;
                continue;
            }
            int minb=2e9, mine=2e9;
            for(auto& u: actusers) {
                minb = min(minb, u.budget);
                mine = min(mine, u.energy);
            }
            // cout << d << endl;
            // cout << d << " " << mine << " " <<minb;  
            struct Elg {
                Activity act;
                int sat;
            };
            
            vector<Elg> elgbl;
            for(auto& kv: in.activities) {
                Activity a = kv.second;
                if(used.count(a.id)) continue;
                if(wBlock[d].count(a.tag)) continue;
                if((a.cost<=minb) && a.energy <= mine && (a.duration <= in.H)) {
                    int sat = 0;
                    for(auto& u: actusers) {
                        if(u.tags.count(a.tag)) {
                            sat++;
                        }
                    }


                    // cout << a << " " << sat << endl;
                    elgbl.push_back({a, sat});
                }
            }
            
            vector<int> bestS;
            int bstSat = -1;
            int bstCost = -1;
            vector<int> curr;
            
            // dfs
            auto dfs= [&](auto& self, int idx, int cst, int ceng, int dur, int csat) -> void {
                bool flg = 0;
                if(bstSat == -1) flg = 1;
                else if(csat > bstSat) flg = 1;
                else if(csat == bstSat) {
                    if(cst < bstCost) flg = 1;
                    else if(cst == bstCost) {
                        if(curr < bestS) flg = 1;
                    }
                }
                if(flg) {
                    bestS = curr;
                    bstSat = csat;
                    bstCost = cst;
                    // cout << bstSat << " ";
                }
                // cout << 
                for(int i = idx; i < elgbl.size(); i++) {
                    auto& e = elgbl[i];
                    if(cst+e.act.cost <= minb && ceng + e.act.energy <= mine && (dur + e.act.duration <= in.H)) {
                        curr.push_back(e.act.id);
                        self(self, i+1, cst+e.act.cost, ceng+e.act.energy, dur+e.act.duration, csat+e.sat);
                        curr.pop_back();
                    }
                }
            };
            
            dfs(dfs, 0, 0, 0, 0, 0);
            // cout << "\n\n";
            ids[d] = bestS;
            costs[d] = max(0, bstCost);
            sat[d] = max(0, bstSat);
            for(int id: bestS) {
                used.insert(id);
            }
        }
    };
    // TODO 2: process events in order. For each event i (1-indexed):
    //   - append "=== EVENT i: <event line verbatim> ===\n"
    //   - mutate state (DROP / WEATHER / FATIGUE / BUDGET)
    //   - re-plan days [eventDay .. D], preserving days [1 .. eventDay-1]

    rp(1);
    for(int day = 1; day <= in.D; day++) {
        out += formatDay(day, ids[day], costs[day], sat[day]) + "\n";
    }

    for(size_t i = 0; i < in.events.size(); i++) {
        string ev_str = in.events[i];
        out += "=== EVENT " + to_string(i + 1) + ": " + ev_str + " ===\n";
        stringstream ss(ev_str);
        string etype;
        int day = 1;
        ss >> etype >> day;
        // cout << i << " ";
        // cout << etype << endl;
        if(day<1) day = 1;
        if(day>in.D) continue;
        if(etype == "WEATHER") {
            string tag;
            ss >> tag;
            wBlock[day].insert(tag);
            // cout << "ts" << endl;
        } else if(etype == "DROP") {
            string user;
            ss >> user;
            for(int d = day; d <= in.D; d++) {
                for(auto& u : tmlusers[d]) {
                    if(u.name == user) u.active = false;
                }
            }
        } else if(etype == "FATIGUE") {
            string user;
            int val;
            ss >> user >> val;
            for(int d = day; d <= in.D; d++) {
                for(auto& u : tmlusers[d]) {
                    if(u.name == user) u.energy = val;
                }
            }
        } else if(etype == "BUDGET") {
            string user;
            int val;
            ss >> user >> val;
            for(int d = day; d <= in.D; d++) {
                for(auto& u : tmlusers[d]) {
                    if(u.name == user) u.budget = val;
                }
            }
            // cout << val << endl;
        }
        rp(day);
        for(int d = day; d <= in.D; d++) {
            out += formatDay(d, ids[d], costs[d], sat[d]) + "\n";
        }
    }
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Input in = readInput();
    cout << solve(in);
    return 0;
}