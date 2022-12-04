#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using std::string;
struct entry {

    string connection_name;
    string destAddress;
    string id;
    string legId;
    string message;
    string sourceAddress;
    string timestamp;


};




int main(){
    using namespace std;

    std::ifstream in("../data.txt");

    map<string,string> reqs;
    std::string req,resp,line;
    while (in) {
        getline(in,line);
        if (line.find("process_antispam_req()") != std::string::npos) {
            req.clear();
            continue;
        }

        if (line.find("process_antispam_resp()") != std::string::npos) {
            getline(in,resp);
            reqs.insert(make_pair(req,resp));
            continue;
        }
        req.append(line);

    }

    map<json,json> json_reqs;
    for (auto & [req,resp]: reqs) {
        json_reqs.insert(make_pair(json::parse(req),json::parse(resp)));

    }

    for (auto & [req,resp]: json_reqs) {
        cout << req.dump() << "\n";
        cout << resp.dump() << "\n\n";
    }



}