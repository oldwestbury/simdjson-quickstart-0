#include "simdjson.h"
#include <iostream>
#include <unordered_map>

using namespace simdjson;
using namespace std;
unordered_map<string, string> ht;

void get_type(string k, ondemand::value element) {
    std::string  type_of_value = "";
    switch (element.type()) {
    case ondemand::json_type::array:
        for (auto child : element.get_array()) {
            get_type(k + "[] ", child.value());
        }
        // Add something

        break;
    case ondemand::json_type::object:
        for (auto field : element.get_object()) {
            //stringstream s;

            //s << k << "." << field.key();
            std::string_view s(field.escaped_key());
            get_type(k+"."+string(s), field.value());



        }

        break;
    case ondemand::json_type::number:
        type_of_value = "number";
        break;
    case ondemand::json_type::string:
        type_of_value = "string";
        break;
    case ondemand::json_type::boolean:
        type_of_value = "boolean";
        break;
    case ondemand::json_type::null:
        if (element.is_null()) {
            type_of_value = "null";
        }
        break;
    }
    ht.insert(make_pair(k, type_of_value));
}

int main(void) {
    ondemand::parser parser;
    padded_string json = padded_string::load("cars.json");
    ondemand::document cars = parser.iterate(json);
    ondemand::value v = cars;
    get_type("", v);


    for (auto k : ht) {
        cout << k.first << "  " << k.second << "\n";

    }
}