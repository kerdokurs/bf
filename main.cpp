#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

const int MEMORY_SIZE = (1 << 16); // 1024 bits
int MEMORY[MEMORY_SIZE];

const int CODE_SIZE = (1 << 16);
char CODE[CODE_SIZE];
int code_end;

int load_code(fstream &file) {
	int i = 0;
	char c;
	while (file >> c) {
		if (i >= CODE_SIZE) return 1;
		CODE[i] = c;
		i++;
	}

	code_end = i;
	
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "usage: bf <source_file>\n";
		return 0;
	}

	char *file_name = argv[1];
	fstream source_file;
	source_file.open(file_name, ios::in);

	if (!source_file) {
		cout << file_name << " not found\n";
		return 0;
	}

	int error = load_code(source_file);
	if (error) {
		cout << "loading code failed\n";
	}

	stack<int> stack;

	int cp;
	int dp = 0;
	for (cp = 0; cp < code_end; cp++) {
		char c = CODE[cp];

		switch (c) {
			case '+':
				MEMORY[dp]++;
				break;
			case '-':
				MEMORY[dp]--;
				break;
			case '<':
				dp--;
				break;
			case '>':
				dp++;
				break;
			case '.':
				cout << MEMORY[dp];
				break;
			case ',':
				cin >> MEMORY[dp];
				break;
			case '[':
				stack.push(cp);
				break;
			case ']':
				if (MEMORY[dp]) {
					if (!stack.empty()) {
						int to = stack.top();
						stack.pop();
						cp = to - 1;
					}
				}
				break;
		}
	}

	source_file.close();
	
	return 0;
}
