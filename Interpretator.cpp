#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Token {
	public:
	std::string T_value;
	std::string T_type;
};

class Variable {
public:
	std::string V_value;
	std::string V_name;
};


void openFile(const char *, std::ifstream &);

void parser(std::string tok, Token(&arrayToken)[50], int &iteration) {
	if (tok == "pghvar" || tok == "print") {
		arrayToken[iteration].T_type = "keyword";
		arrayToken[iteration].T_value = tok;
	}
	else if (tok == "+" || tok == "-" || tok == "/" || tok == "*" || tok == ";" ||  tok == "=") {
		return;
	}
	else {
		arrayToken[iteration].T_type = "variable";
		arrayToken[iteration].T_value = tok;
	}
	for (int i = 0; i < tok.size(); ++i) {
		if ( (tok[0] == '"' && tok[tok.size() - 1] == '"') || ((int)tok[i] <= 57 && tok[i] >= 49)) {
			arrayToken[iteration].T_type = "literal";
			arrayToken[iteration].T_value = tok;
		}
	}
	++iteration;
}

void tokenizer(std::string line, Variable(&DB)[50]) {
	std::string tok;
	std::string type;
	std::stringstream s(line);
	Token arrayToken[50];
	int i = 0;
	while (s >> tok) {
		parser(tok, arrayToken, i);
	}
	if (arrayToken[0].T_value == "pghvar") {
		DB[0].V_name = arrayToken[1].T_value;
		DB[0].V_value = arrayToken[2].T_value;
	}
	else if (arrayToken[0].T_value == "print") {
		std::cout << DB[0].V_value << std::endl;
	}
	//std::cout << i << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << " There is no file name to read!" << std::endl;
		return -1;
	}

	std::ifstream data;
	openFile(argv[1], data);
	std::string line;
	int i = 1;
	Variable DB[50];
	for (std::string line; getline(data, line); )
	{
		if (line == "")
			continue;
		tokenizer(line, DB);
	//	std::cout << line << std::endl;
			++i;
	}
}

void openFile(const char *filename, std::ifstream &data) {
	std::string  fname(filename);
	std::string ext(".pgh");
	std::size_t found = fname.rfind(ext);
	if (found != fname.length() - 4) {
		std::cout << "Not correct file format!" << std::endl;
		return;
	}
	data.open(filename);
	if (data.fail())
	{
		std::cout << "FileError " << filename << " could not be found" << std::endl;
	}
}



