#include "InputJSON.h"


InputJSON::InputJSON(string fileName): 
	time(0)
{
	Json::Reader reader;
	reader.parse(fileName, root);
}

InputJSON::~InputJSON()
{
}

void InputJSON::input()
{

	ifstream file("F:/workspace/Simulation/bin/test.json", std::ifstream::binary);
	Json::Value root;
	file >> root;
	// string encoding = root.get("0", "UTF-8" ).asString();
    cout << root["0"] << endl;




	// if (time > 0)
	// 	myfile << "," << endl;
	// myfile << "\"" << time << "\"" << ": [" << endl;
	// unsigned int particleCount = particles.size();
	// unsigned int i = 0;
	// for (const auto& p : particles) {
	// 	myfile << "{ ";
	// 	myfile << "\"r\": " << p->radius << "," << endl;
	// 	myfile << "\"pos\": [";
	// 	myfile << p->position.x << ",";
	// 	myfile << p->position.y << ",";
	// 	myfile << p->position.z;
	// 	myfile << "]}" << endl;
	// 	if (++i < particleCount)
	// 		myfile << "," << endl;

	// }
	// myfile << "]";
}
