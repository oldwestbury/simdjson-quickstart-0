
#include <iostream>
#include "simdjson.h"
using namespace simdjson;
using namespace std;

void recursive_print_json(ondemand::value element) {
    bool add_comma;
    switch (element.type()) {
    case ondemand::json_type::array:
      cout << "[";
      add_comma = false;
      for (auto child : element.get_array()) {
        if (add_comma) {
          cout << ",";
        }
        // We need the call to value() to get
        // an ondemand::value type.
        recursive_print_json(child.value());
        add_comma = true;
      }
      cout << "]";
      break;
    case ondemand::json_type::object:
      cout << "{";
      add_comma = false;
      for (auto field : element.get_object()) {
        if (add_comma) {
          cout << ",";
        }
        // key() returns the key as it appears in the raw
        // JSON document, if we want the unescaped key,
        // we should do field.unescaped_key().
        // We could also use field.escaped_key() if we want
        // a std::string_view instance, but we do not need
        // escaping.
        cout << "\"" << field.key() << "\": ";
        recursive_print_json(field.value());
        add_comma = true;
      }
      cout << "}\n";
      break;
    case ondemand::json_type::number:
      // assume it fits in a double
      cout << element.get_double();
      break;
    case ondemand::json_type::string:
      // get_string() would return escaped string, but
      // we are happy with unescaped string.
      cout << "\"" << element.get_raw_json_string() << "\"";
      break;
    case ondemand::json_type::boolean:
      cout << element.get_bool();
      break;
    case ondemand::json_type::null:
      // We check that the value is indeed null
      // otherwise: an error is thrown.
      if (element.is_null()) {
        cout << "null";
      }
      break;
    }
  }
  int main(){
    padded_string json = R"( [
    { "make": "Toyota", "model": "Camry",  "year": 2018, "tire_pressure": [ 40.1, 39.9, 37.7, 40.4 ] },
    { "make": "Kia",    "model": "Soul",   "year": 2012, "tire_pressure": [ 30.1, 31.0, 28.6, 28.7 ] },
    { "make": "Toyota", "model": "Tercel", "year": 1999, "tire_pressure": [ 29.8, 30.0, 30.2, 30.5 ] }
  ] )"_padded;
    ondemand::parser parser;
    ondemand::document doc = parser.iterate(json);
    ondemand::value val = doc;
    recursive_print_json(val);
    std::cout << std::endl;
    return 0;
  }