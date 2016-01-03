/**
 * File: extract-query-map.cpp
 * ---------------------------
 * Provides the implementation of extractQueryMap, and the test harness
 * used to actually test and confirm it works.
 */

#include "genlib.h"
#include "map.h"
#include "set.h"
#include <string>
#include <iostream>

/**
 * Generates the explosion of the specified string around
 * the given delimiter, and returns the tokens, in sequence, in
 * a Vector<string>
 *
 * @param string str the string to be exploded/tokenized, i.e. "171.64.64.135"
 * @param char delim the delimiting token, i.e. '.'
 * @return Vector<string> the series of tokens within str, when delim is considered
 *         to be the searating delimiter, i.e. ["171". "64", "64", "135"] as a Vector<string>
 */

Vector<string> Explode(string str, char delim) {
	Vector<string> explosion;
	string cluster;
	str += delim; // last cluster gets appended w/ minimal special casing
	
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == delim) {
			explosion.add(cluster);
			cluster.clear(); // cluster = "" works, too
		} else {
			cluster += str[i];
		}
	}
	
	return explosion;
}

/**
 * The function you need to implement, as described in the lab handout.
 *
 * @param string url the well-formed URL whose parameter map is of interest to us.
 * @return Map<string> the URL's parameter map, in Map<string> form.
 */

Map<string> extractQueryMap(string url) {
Map<string> parameters;
int index = url.find('?');
if (index == string::npos) return parameters;
string query = url.substr(index + 1);
index = query.find('#');
if (index != string::npos) {
query = query.substr(0, index); // chop off hash
}
Vector<string> pairs = Explode(query, '&');
for (int i = 0; i < pairs.size(); i++) {
Vector<string> components = Explode(pairs[i], '=');
string key = components[0];
string value = "true";
if (components.size() > 1 && !components[1].empty()) {
value = components[1];
}
parameters[key] = value;
}
return parameters;
}

/**
 * Type: testCase
 * --------------
 * Encapsulates all of the data we need for a particular test case.
 * A properly implemeted extractQueryMap will analyze the .url
 * to find a total of .numParams.  Those parameters with specific
 * values can be found in .fullKeyValuePairs, and those with arbitrary
 * values can be found in .arbitraryKeys.
 */

struct testCase {
	string url;
	int numParams;
	Map<string> fullKeyValuePairs;
	Set<string> arbitraryKeys;
};

/**
 * Presumes the supplied file contains information about the
 * various test cases that can be given to the extractQueryMap
 * function.  You can inspect the data file to intuit the file format,
 * but it's perfectly reasonable to just ignore this function and let
 * it work for you without understanding it.  It's just file processing
 * that assumes a perfectly formatted file.
 *
 * @param string filename the name of the file with the test data.
 * @return Vector<testCases> all of the test cases rehydrated from the data file.
 */

static const char kEndOfLine = '\n';
Vector<testCase> buildTestCases(string filename = "test-cases.dat") {
	ifstream infile(filename.c_str());
	Vector<testCase> testCases;
	while (true) {
		string url;
		getline(infile, url, kEndOfLine);
		if (infile.fail()) return testCases;
		testCase test = {url, 0};
		string numPairsString;
		getline(infile, numPairsString, kEndOfLine);
		int numPairs = StringToInteger(numPairsString);
		for (int i = 0; i < numPairs; i++) {
			string key, value;
			getline(infile, key, kEndOfLine);
			getline(infile, value, kEndOfLine);
			test.fullKeyValuePairs.put(key, value);
			test.numParams++;
		}
		string numArbitraryKeysString;
		getline(infile, numArbitraryKeysString, kEndOfLine);
		int numArbitraryKeys = StringToInteger(numArbitraryKeysString);
		for (int j = 0; j < numArbitraryKeys; j++) {
			string key;
			getline(infile, key, kEndOfLine);
			test.arbitraryKeys.add(key);
			test.numParams++;
		}
		
		testCases.add(test);
	}
}

/**
 * Brute force testing of a particular test case as described by the provided
 * test case.  We extract the parameter map from the test case's url, and do some
 * aggressive error checking to see if the extraction generated the correct information.
 * The function has the side effect of printout out all of the errors we detect, and
 * returning true if and only if we don't find any errors at all.
 *
 * @param testCase& test data about a particular test case that can be administered
 *        to confirm extractQueryMap is working properly.
 * @return bool true if the function works in the provide test case scenario, and false otherwise.
 */

bool testCasePasses(testCase& test) {
	Map<string> parameterMap = extractQueryMap(test.url);
	bool pass = true;
	cout << "Testing \"" << test.url << "\":" << endl;
	if (parameterMap.size() != test.numParams) {
		cout << "   Error: Expected this many parameters: " << test.numParams << endl;
		cout << "          Got this many instead: " << parameterMap.size() << endl;
		pass = false;
	}

	foreach (string key in test.fullKeyValuePairs) {
		if (!parameterMap.containsKey(key)) {
			cout << "   Error: \"" << key << "\" should be in the map, but isn't." << endl;
			pass = false;			
		} else if (parameterMap[key] != test.fullKeyValuePairs[key]) {
			cout << "   Error: Expected \"" << key << "\" to map to \"" <<  test.fullKeyValuePairs[key] << "\"." << endl; 
			cout << "          Currently see \"" << key << "\" mapping to \"" << parameterMap[key] << "\" instead." << endl;
			pass = false;
		}
	}
	
	foreach (string key in test.arbitraryKeys) {
		if (!parameterMap.containsKey(key)) {
			cout << "   Error: \"" << key << "\" should be in the map (with arbitrary value), but isn't." << endl;
			pass = false;
		}
	}
	
	if (pass) {
		cout << "   Passed!" << endl;
	}
	
	return pass;
}

/**
 * The main function has been set up to run as a unit test
 * to exercise the functionality of our extractQueryMap
 * function.  Initially, most of the tests will fail, but as
 * you complete the implementation of the extractQueryMap, they should
 * start passing.
 */

int main() {
	Vector<testCase> testCases = buildTestCases();
	int numErrors = 0;
	for (int i = 0; i < testCases.size(); i++) {
		if (!testCasePasses(testCases[i])) {
			numErrors++;
		}
	}
	
	cout << endl;
	if (numErrors == 0) {
		cout << "All tests passed.  Woo!" << endl;
	} else {
		cout << "You had this many failures: " << numErrors << endl;
	}
	
	return 0;
}

