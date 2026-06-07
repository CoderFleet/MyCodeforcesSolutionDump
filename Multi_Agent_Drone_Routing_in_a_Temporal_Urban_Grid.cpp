// Start of HEAD
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <json/json.h>  // jsoncpp (provided on HackerRank)

#define pii pair<int, int>;

using namespace std;

int main() {
    // Read all input from stdin
    string input_str((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    Json::Value input_data;
    Json::CharReaderBuilder rb;
    string errs;
    istringstream ss(input_str);
    Json::parseFromStream(rb, ss, &input_data, &errs);

    double mapW = input_data["map_size"][0].asDouble();
    double mapH = input_data["map_size"][1].asDouble();
    double warehouseX = mapW / 2.0, warehouseY = mapH / 2.0;
    Json::Value drones = input_data["drones"];
    Json::Value deliveries = input_data["deliveries"];
    Json::Value no_fly_zones = input_data.get("no_fly_zones", Json::Value(Json::arrayValue));
    Json::Value charging_stations = input_data.get("charging_stations", Json::Value(Json::arrayValue));
// End of HEAD

// Start of BODY
    /*
     * Schedule drone deliveries to maximize on-time deliveries
     * while minimizing energy and makespan.
     *
     * Input:
     *   warehouse: [x, y] - center of map, pickup/return location
     *   drones: array of {"id": str, "max_payload": double}
     *   deliveries: array of {"id": str, "x": double, "y": double, "weight": double, "deadline": double}
     *   no_fly_zones: array of {"shape": "circle"|"rectangle", "center"/"corners", "radius", "T_start", "T_end"}
     *   charging_stations: array of {"x": double, "y": double}
     *
     * Output:
     *   JSON: {"flight_manifest": [drone_entries]}
     *   Each drone_entry: {"drone_id": str, "path": [steps]}
     *   Each step: {"x": double, "y": double, "t": double, "action": str, ...}
     *   Actions: PICKUP (+delivery_ids), DELIVER (+delivery_id), RETURN, CHARGE, CHARGE_COMPLETE, WAIT, WAYPOINT
     *
     * Scoring:
     *   score = (on_time_deliveries * 100) - (total_energy * 0.1) - (makespan * 0.05)
     *   energy per leg = distance * (1 + current_payload_weight)
     *   Battery capacity = 500, recharges on RETURN to warehouse
     */

    auto fdist = [](pii a, pii b) {
        return sqrt(pow(b.first-a.first, 2) + pow(b.second-a.second, 2));
    };

    struct NFZ {
        
    }

    Json::Value flight_manifest(Json::arrayValue);

    // TODO: Implement your solution here

// End of BODY

// Start of TAIL
    Json::Value output;
    output["flight_manifest"] = flight_manifest;
    Json::StreamWriterBuilder wb;
    wb["indentation"] = "";
    cout << Json::writeString(wb, output) << endl;
    return 0;
}
// End of TAIL