#include <bits/stdc++.h>

using namespace std;

long long SCORE = 0;

struct Street {
    int B, E;
    string name;
    int idx;
    int L;
    int pref_time, self_time;
};

struct Cars {
    vector<int> path_indices;
    int index;
};

struct intersection {
    unordered_map<int, int> duration;
    int total_Time;
};

vector<intersection> intersections;
vector<Street> streets;
vector<Cars> cars;
vector<vector<int>> outgoing, incoming;
unordered_map<string, int> string_index;
vector<queue<int>> car_info;  // street index
vector<Street> active_streets;

// {what Time,{which street,which car}}

void push_car_in_street(pair<int, pair<int, int>> x) {
    if (car_info[x.second.first].size() == 0) {
        active_streets.push_back(streets[x.second.first]);
    }
    car_info[x.second.first].push(x.second.second);
}

bool is_Light_green(Street x, int Time) {
    int inter = x.E;
    int curr_Time = Time % intersections[inter].total_Time;
    if (curr_Time >= x.pref_time && curr_Time < x.pref_time + x.self_time) {
        return true;
    }
    return false;
}

int main(int argc, char **argv) {

    FILE *fp = freopen(argv[1], "r", stdin);
    long long D, I, S, V, F;
    
    cin >> D >> I >> S >> V >> F;
    
    streets.resize(S);
    cars.resize(V);
    intersections.resize(I);
    car_info.resize(S);
    incoming.resize(I);
    outgoing.resize(I);
    
    cout << "RRR" << endl;
    for (int i = 0; i < S; i++) {
        cin >> streets[i].B >> streets[i].E >> streets[i].name >> streets[i].L;
        streets[i].idx = i;
        string_index[streets[i].name] = i;
        incoming[streets[i].E].push_back(i);
        outgoing[streets[i].B].push_back(i);
    }
    
    cout << "input1" << endl;
    for (int i = 0; i < V; i++) {
    
        int p;
        cin >> p;
        cars[i].path_indices.resize(p);
        cars[i].index = 0;

        for (int j = 0; j < p; j++) {
            string s;
            cin >> s;
        
            cars[i].path_indices.push_back(string_index[s]);
            if (car_info[string_index[s]].size() == 0) {
                active_streets.push_back(streets[string_index[s]]);
            }
            
            if (j == 0) {
                car_info[string_index[s]].push(i);
            }
        }
    }

    fp = freopen(argv[2], "r", stdin);
    
    // output file number of scheduled inters
    int A;
    cin >> A;
    
    for (int i = 0; i < A; i++) {
    
        int id, no_of_streets;
        cin >> id >> no_of_streets;
        intersections[id].total_Time = 0;
        for (int j = 0; j < no_of_streets; j++) {
            string s;
            cin >> s;
            int T;
            cin >> T;
            intersections[id].duration[string_index[s]] = T;

            streets[string_index[s]].pref_time = intersections[id].total_Time;
            streets[string_index[s]].self_time = T;
            intersections[id].total_Time += T;
        }
    }
    // {what Time,{which street,which car}}
    queue<pair<int, pair<int, int>>> events;
    for (int Time = 0; Time < D; Time++) {
        if (events.size() > 0) {
            while (events.front().first == Time) {
                cout << "fsdlf" << endl;
                push_car_in_street(events.front());
                events.pop();
                if (events.size() == 0) break;
            }
        }
        vector<Street> temp_active_street;
        for (int i = 0; i < active_streets.size(); i++) {
            int street_index = active_streets[i].idx;
            if (is_Light_green(active_streets[i], Time)) {
                int car_index = car_info[street_index].front();
                int what_Time = Time + streets[street_index].L;
                int st = ++cars[car_index].index;
                if (st == cars[car_index].path_indices.size()) {
                    SCORE += F + D - Time;
                }
                int which_street = cars[car_index].path_indices[st];
                events.push({what_Time, {which_street, car_index}});
                car_info[street_index].pop();
                if (car_info[street_index].size() > 0) {
                    temp_active_street.push_back(active_streets[i]);
                    // Street temp = active_streets[i];
                    // active_streets[i] =
                    // active_streets[active_streets.size()-1];
                    // active_streets[active_streets.size()-1] = temp;
                    // active_streets.pop_back();
                }
            }
        }
        active_streets = temp_active_street;
    }
    cout << SCORE << '\n';
}
