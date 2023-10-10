std::string Parser::getValue(std::string& name) {
    if (name.back() != ']') {
        // Not an array, check its data type
        std::string type = isDeclared(name);
        if (type == "bool") {
            bool val = variables.booleans[name].first;
            return val ? "true" : "false";
        } else if (type == "char") {
            char val = variables.characters[name].first;
            return std::string(1, val);
        } else if (type == "int") {
            int val = variables.integers[name].first;
            return std::to_string(val);
        } else if (type == "string") {
            std::string val = variables.strings[name].first;
	    val = val.substr(1,val.size() - 2);
            return val;
        } else if (type == "double") {
		double val = variables.doubles[name].first;
		return std::to_string(val);
	}
    } else {
        // It's an array element, retrieve the array and index
        std::pair<std::string, int> p = arrNamePars(name, variables);
        std::string type = isDeclared(p.first);
        if (type == "charArr") {
            std::vector<char> val = variables.charArr[p.first];
            if (val.size() <= p.second) {
                throw std::invalid_argument("Segmentation fault.");
            }
            char ch = val[p.second];
            return std::string(1, ch);
        } else if (type == "intArr") {
            std::vector<int> val = variables.intArr[p.first];
            if (val.size() <= p.second) {
                throw std::invalid_argument("Segmentation fault.");
            }
            int i = val[p.second];
            return std::to_string(i);
        } else if (type == "doubleArr") {
            std::vector<double> val = variables.doubleArr[p.first];
            if (val.size() <= p.second) {
                throw std::invalid_argument("Segmentation fault.");
            }
            double d = val[p.second];
            return std::to_string(d);
        }
    }
    // If none of the above conditions match, return the original name
    if (name.front() == '"') {
	name = name.substr(1, name.size() - 1);
    }
    if (name.back() == '"') {
	name = name.substr(0, name.size() - 1);
    }

    return name;
}
