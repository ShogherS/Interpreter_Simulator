
void Parser::updateVars(Variables& newVars, Variables& variables) {
    // Update boolean variables
    for (auto& it : newVars.booleans) {
        if (variables.booleans.contains(it.first)) {
            variables.booleans[it.first] = it.second;
        }
    }

    // Update character variables
    for (auto& it : newVars.characters) {
        if (variables.characters.contains(it.first)) {
            variables.characters[it.first] = it.second;
        }
    }

    // Update integer variables
    for (auto& it : newVars.integers) {
        if (variables.integers.contains(it.first)) {
            variables.integers[it.first] = it.second;
        }
    }

    // Update double variables
    for (auto& it : newVars.doubles) {
        if (variables.doubles.contains(it.first)) {
            variables.doubles[it.first] = it.second;
        }
    }

    // Update string variables
    for (auto& it : newVars.strings) {
        if (variables.strings.contains(it.first)) {
            variables.strings[it.first] = it.second;
        }
    }

    // Update charArr variables
    for (auto& it : newVars.charArr) {
        if (variables.charArr.contains(it.first)) {
            variables.charArr[it.first] = it.second;
        }
    }
   
    // Update intArr variables
    for (auto& it : newVars.intArr) {
        if (variables.intArr.contains(it.first)) {
            variables.intArr[it.first] = it.second;
        }
    }

    // Update doubleArr variables
    for (auto& it : newVars.doubleArr) {
        if (variables.doubleArr.contains(it.first)) {
            variables.doubleArr[it.first] = it.second;
        }
    }
}
