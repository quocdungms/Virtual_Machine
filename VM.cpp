#include "VM.h"


void VM::run(string filename)
{
	/*load_datav1(filename);
	this->test_regex(filename);
	this->print_list();

	this->print_reg();*/
	

	load_datav1(filename);
	process();
	
}


/*///////////////////////////////////////////
*
* Cac ham check, get
* 
*////////////////////////////////////////////

bool VM::check_int(string src){
	regex INT("^([1-9]|[1-9][0-9]+|0)$");
	return regex_match(src, INT);
}

bool VM::check_float(string src){
	regex FLOAT("^([1-9]|[1-9][0-9]+|0).[0-9]+$");
	return regex_match(src, FLOAT);
}

bool VM::check_bool(string src){
	if (src == "true" || src == "false")
		return true;
	return false;
}

bool VM::check_address(string src) {
	regex ADDRESS("(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])A");
	return regex_match(src, ADDRESS);
}

bool VM::check_reg(string src) {
	regex REG("^R([0-9]|[1-9]+[0-9]+)$");
	return regex_match(src, REG);
}

bool VM::valid_reg(int dest) {
	if (dest >= 0 && dest <= 14)
		return true;
	return false;
}

int VM::check_instruction(string command) {
	if (command == "Add") return 1;
	else if (command == "Minus") return 2;
	else if (command == "Mul") return 3;
	else if (command == "Div") return 4;
	else if (command == "CmpEQ") return 5;
	else if (command == "CmpNE") return 6;
	else if (command == "CmpLT") return 7;
	else if (command == "CmpLE") return 8;
	else if (command == "CmpGT") return 9;
	else if (command == "CmpGE") return 10;
	else if (command == "Not") return 11;
	else if (command == "And") return 12;
	else if (command == "Or") return 13;
	else if (command == "Move") return 14;
	else if (command == "Load") return 15;
	else if (command == "Store") return 16;
	else if (command == "Jump") return 17;
	else if (command == "JumpIf") return 18;
	else if (command == "Call") return 19;
	else if (command == "Return") return 20;
	else if (command == "Halt") return 21;
	else if (command == "Input") return 22;
	else if (command == "Output") return 23;

	return -1;
}



int VM::get_int(string src) {
	return stoi(src);
}

float VM::get_float(string src) {
	return stof(src);
}

bool VM::get_bool(string src) {
	return src == "true" ? true : false;
}

int VM::get_address(string src) {
	return stoi(src.substr(0, src.length() - 1));
}

int VM::get_reg(string dest){
	string str;
	str = dest.substr(1, dest.length() - 1);
	return stoi(str);
}

int VM::get_type(string src) {
	if (check_int(src)) return 1;
	else if (check_float(src)) return 2;
	else if (check_bool(src)) return 3;
	else if (check_address(src)) return 4;
	else if (check_reg(src)) return 5;
	return -1;
}


int VM::get_abs(int a) {
	if (a < 0)
		return a = 0 - a;
	else
		return a;
}

/*///////////////////////////////////////////
*
* Cac ham print
*
*////////////////////////////////////////////

void VM::print_list()
{
	cout << "Size: " << this->size << endl;
	for (int i = 0; i < this->size; i++)
	{
		cout << "|" << command_list[i].cmd
			<< "|" << command_list[i].dest
			<< "|" << command_list[i].src
			<< "|" << endl;
	}
}

void VM::print_reg() {
	cout << "Print REG\n";
	cout << "REG | INT | FLOAT | BOOL | ADDRESS | TYPE\n";
	for (int i = 0; i < 15; i++)
	{
		printf("%3d | %3d | %.3f | %4d | %7d | %4d\n", i + 1, reg[i].iData, reg[i].fData, reg[i].bData, reg[i].address, reg[i].type);
		
	}
}




/*///////////////////////////////////////////
*
* Cac ham xu ly
*
*////////////////////////////////////////////


void VM::push_to_command_list(int address, string command, int dest, string src)
{
	if (address > capacity - 1)
		throw StackFull(address);
	this->command_list[address].cmd = command;
	this->command_list[address].dest = dest;
	this->command_list[address].src = src;
	this->size++;
}



int VM::classify(string command)
{
   /*
	* Version 2
	*/

	// R0-Rxxxxxxxxxxx
	// ^R([0-9]|[1-9]+[0-9]+)$
	// 
	// 0A-999A
	// ([1-9][0-9]{0,2}|0)A
	// 
	// INT NUMBER
	// 0$|^[1-9][0-9]*
	//
	// FLOAT NUMBER
	// ([0-9]*[.])?[0-9]+

	/*regex Add("^Add R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([0-9]*[.])?[0-9]+)$");
	regex Minus("^Minus R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([0-9]*[.])?[0-9]+)$");
	regex Mul("^Mul R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([0-9]*[.])?[0-9]+)$");
	regex Div("^Div R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([0-9]*[.])?[0-9]+)$");
	regex CmpEQ("^CmpEQ R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");
	regex CmpNE("^CmpNE R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");
	regex CmpLT("^CmpLT R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");
	regex CmpLE("^CmpLE R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");
	regex CmpGT("^CmpGT R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");
	regex CmpGE("^CmpGE R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");
	regex Not("^Not R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false)$");
	regex And("^And R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false)$");
	regex Or("^Or R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false)$");
	regex Move("^Move R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|([0-9]*[.])?[0-9]+|(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])A)$");
	regex Load("^Load R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([1-9][0-9]{0,2}|0)A)$");
	regex Store("^Store R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|([0-9]*[.])?[0-9]+|(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])A)$");
	regex Jump("^Jump (R([0-9]|[1-9]+[0-9]+)|([1-9][0-9]{0,2}|0)A)$");
	regex JumpIf("^JumpIf R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([1-9][0-9]{0,2}|0)A)$");
	regex Call("^Call (R([0-9]|[1-9]+[0-9]+)|([0-9]|[1-9]+[0-9]+)A)$");
	regex Return("^Return$");
	regex Halt("^Halt$");
	regex Input("^Input R([0-9]|[1-9]+[0-9]+)$");
	regex Output("Output R([0-9]|[1-9]+[0-9]+)$");

	if (regex_match(command, Add)) return 1;
	else if (regex_match(command, Minus)) return 2;
	else if (regex_match(command, Mul)) return 3;
	else if (regex_match(command, Div)) return 4;
	else if (regex_match(command, CmpEQ)) return 21;
	else if (regex_match(command, CmpNE)) return 22;
	else if (regex_match(command, CmpLT)) return 23;
	else if (regex_match(command, CmpLE)) return 24;
	else if (regex_match(command, CmpGT)) return 25;
	else if (regex_match(command, CmpGE)) return 26;
	else if (regex_match(command, Not)) return 31;
	else if (regex_match(command, And)) return 32;
	else if (regex_match(command, Or)) return 33;
	else if (regex_match(command, Move)) return 41;
	else if (regex_match(command, Load)) return 42;
	else if (regex_match(command, Store)) return 43;
	else if (regex_match(command, Jump)) return 51;
	else if (regex_match(command, JumpIf)) return 52;
	else if (regex_match(command, Call)) return 53;
	else if (regex_match(command, Return)) return 54;
	else if (regex_match(command, Halt)) return 55;
	else if (regex_match(command, Input)) return 60;
	else if (regex_match(command, Output)) return 61;
	
	return -1;*/












   /*
	* Version 1
	* Chi sua lai ma regex:
	*   Miss loi InvalidOperand
	*	Sai kieu du lieu
	*/

	
	// 1. Cac lenh so hoc = 10
	regex g1("^(Add|Minus|Mul|Div) R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([0-9]*[.])?[0-9]+)$");

	// 2. Cac lenh so sanh = 20
	regex g2("^Cmp(EQ|NE|LT|LE|GT|GE) R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|0$|[1-9][0-9]*|([0-9]*[.])?[0-9]+)$");

	// 3. Cac lenh luan ly = 30
	regex g3("^(Not|Or|And) R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false)$");

	// 4. Cac lenh doc va ghi du lieu
	//  Move = 41
	regex g41("^Move R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|([0-9]*[.])?[0-9]+|(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])A)$");
	//  load = 42
	regex g42("^Load R([0-9]|[1-9]+[0-9]+), R([0-9]|[1-9]+[0-9]+)$");
	//  Store = 43
	regex g43("^Store R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|true|false|([0-9]*[.])?[0-9]+|(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])A)$");

	// 5. Lenh dieu khien trinh tu
	// Jump = 51
	regex g51("^Jump (R([0-9]|[1-9]+[0-9]+)|([1-9][0-9]{0,2}|0)A)$");
	// JumpIf = 51
	regex g52("^JumpIf R([0-9]|[1-9]+[0-9]+), (R([0-9]|[1-9]+[0-9]+)|([1-9][0-9]{0,2}|0)A)$");
	// Call = 53
	regex g53("^Call (R([0-9]|[1-9]+[0-9]+)|([0-9]|[1-9]+[0-9]+)A)$");

	// Return = 60
	regex g60("^Return$");
	// Half = 70
	regex g70("^Halt$");

	// Input = 100
	regex g100("^Input R([0-9]|[1-9]+[0-9]+)$");

	// Output = 200
	//regex g200("^Output R([0-9]|[1-9]+[0-9]+)$");

	regex g200("^Output (R([0-9]|[1-9]+[0-9]+)|([1-9]|[1-9][0-9]+|0).[0-9]+|([1-9]|[1-9][0-9]+|0)|(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])A)$");

	if (regex_match(command, g1)) return 10;
	else if (regex_match(command, g2)) return 20;
	else if (regex_match(command, g3)) return 30;
	else if (regex_match(command, g41)) return 41;
	else if (regex_match(command, g42)) return 42;
	else if (regex_match(command, g43)) return 43;
	else if (regex_match(command, g51)) return 51;
	else if (regex_match(command, g52))return 52;
	else if (regex_match(command, g53))return 53;
	else if (regex_match(command, g60))return 60;
	else if (regex_match(command, g70))return 70;
	else if (regex_match(command, g100))return 100;
	else if (regex_match(command, g200))return 200;

	return -1;
}



/*
* Version 1
* 
* 
*/

void VM::load_datav1(string filename)
{
	ifstream ifs;
	ifs.open(filename);
	string line;
	while (!ifs.eof())
	{
		getline(ifs, line);
		data_in->push_back(line);
	}
	ifs.close();


	string command, dest, src, check;
	string temp = "";
	int flag = -1;
	int address = 0, pos = 0, pivot = 0;
	while (!data_in->isEmpty())
	{
		command.clear();
		dest.clear();
		src.clear();
		check.clear();
		pivot = 0;
		pos = 0;
		temp = data_in->pop();
		flag = classify(temp);
		switch (flag)
		{
		case 10:
			while (temp[pos] != '\0')
			{
				if (pos < 4)
				{
					check += temp[pos];
				}
				if (temp[pos] == ' ')
				{
					if (check == "Minu")
						command = temp.substr(0, 5);
					else
						command = temp.substr(0, 3);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					if (check == "Minu")
					{
						dest = temp.substr(pivot, pos - 6);
						src = temp.substr(pos + 2, temp.length() - 1);
					}
					else
					{
						dest = temp.substr(pivot, pos - 4);
						src = temp.substr(pos + 2, temp.length() - 1);
					}
					break;
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), src);

			break;
		case 20:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 5);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					dest = temp.substr(pivot, pos - 4);
					src = temp.substr(pos + 2, temp.length() - 1);
					break;
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), src);
			break;
		case 30:
			while (temp[pos] != '\0')
			{
				if (pos < 2)
				{
					check += temp[pos];
				}
				if (temp[pos] == ' ')
				{
					if (check == "Or")
						command = temp.substr(0, 2);
					else
						command = temp.substr(0, 3);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					if (check == "Or")
					{
						dest = temp.substr(pivot, pos - 6);
						src = temp.substr(pos + 2, temp.length() - 1);
					}
					else
					{
						dest = temp.substr(pivot, pos - 4);
						src = temp.substr(pos + 2, temp.length() - 1);
					}
					break;
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), src);
			break;
		case 41:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 4);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					dest = temp.substr(pivot, pos - 4);
					src = temp.substr(pos + 2, temp.length() - 1);
					break;
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), src);
			break;
		case 42:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 4);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					dest = temp.substr(pivot, pos - 4);
					src = temp.substr(pos + 2, temp.length() - 1);
					break;
				}
				pos++;
			}

			this->push_to_command_list(address, command, get_reg(dest), src);
			break;
		case 43:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 5);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					dest = temp.substr(pivot, pos - 4);
					src = temp.substr(pos + 2, temp.length() - 1);
					break;
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), src);
			break;
		case 51:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 4);
					pivot = pos + 1;
					src = temp.substr(pivot, temp.length() - 1);
				}

				pos++;
			}
			this->push_to_command_list(address, command, -9999, src);
			break;
		case 52:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 6);
					pivot = pos + 1;
				}
				if (temp[pos] == ',' && temp[pos + 1] == ' ')
				{
					dest = temp.substr(pivot, pos - 4);
					src = temp.substr(pos + 2, temp.length() - 1);
					break;
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), src);
			break;
		case 53:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 4);
					pivot = pos + 1;
					src = temp.substr(pivot, temp.length() - 1);
				}

				pos++;
			}
			this->push_to_command_list(address, command, -9999, src);
			break;
		case 60:
			command = temp;
			this->push_to_command_list(address, command, -9999, "FFFF");
			break;
		case 70:
			command = temp;
			this->push_to_command_list(address, command, -9999, "FFFF");
			break;
		case 100:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 5);
					pivot = pos + 1;
					dest = temp.substr(pivot, temp.length() - 1);
				}
				pos++;
			}
			this->push_to_command_list(address, command, get_reg(dest), "FFFF");
			break;
		case 200:
			while (temp[pos] != '\0')
			{
				if (temp[pos] == ' ')
				{
					command = temp.substr(0, 6);
					pivot = pos + 1;
					src = temp.substr(pivot, temp.length() - 1);
				}
				pos++;
			}
			this->push_to_command_list(address, command, -9999, src);
			break;
		default:
			throw InvalidInstruction(address);
		}

		address++;
	}
}


void VM::process() {
	int address = 0;
	int current = 0;
	int flag = -1;
	int pos_reg = -1;
	string src;
	while (address < size)
	{
		current = IP;
		IP++;
		flag = check_instruction(command_list[current].cmd);
		pos_reg = command_list[current].dest - 1;
		src = command_list[current].src;
		switch (flag)
		{
		case 1:
			this->ADD(pos_reg, src, address);
			break;
		case 2:
			this->MINUS(pos_reg, src, address);
			break;
		case 3:
			this->MUL(pos_reg, src, address);
			break;
		case 4:
			this->DIV(pos_reg, src, address);
			break;
		case 5:
			this->CMPEQ(pos_reg, src, address);
			break;
		case 6:
			this->CMPNE(pos_reg, src, address);
			break;
		case 7:
			this->CMPLT(pos_reg, src, address);
			break;
		case 8:
			this->CMPLE(pos_reg, src, address);
			break;
		case 9:
			this->CMPGT(pos_reg, src, address);
			break;
		case 10:
			this->CMPGE(pos_reg, src, address);
			break;
			// Not
		case 11:
			this->NOT(pos_reg, address);
			break;
			// And
		case 12:
			this->AND(pos_reg, src, address);
			break;
			// Or
		case 13:
			this->OR(pos_reg, src, address);
			break;
		case 14:
			this -> MOVE(pos_reg, src, address);
			break;
		case 15:
			this->LOAD(pos_reg, src, address);
			break;
		case 16:
			this->STORE(pos_reg, src, address);
			break;
		case 17:
			IP = this->JUMP(src, address);
			address = IP;
			continue;
			break;
		case 18:
			// 
			IP = this->JUMPIF(pos_reg, src, address);
			address = IP;

			/*this->JUMPIF(pos_reg, src, IP, address);*/
			continue;
			break;
		case 19:
			IP = this->CALL(IP, src, address);
			address = IP;
			continue;
			break;
		case 20:
			IP = this->RETURN();
			address = IP;
			continue;
			break;
		case 21:
			// Halt
			this->HALT(address);
			break;
		case 22:
			// input
			this->INPUT(pos_reg, address);
			break;
		case 23:
			// output
			this->OUTPUT(src, address);
			break;
		default:
			break;
		}
		address++;
	}



	////
	//printf("\nIP: %d\n", IP);
	//printf("Address: %d\n", address);
}




void VM::ADD(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	/*
	* -1. NONE
	* 1. INT
	* 2. FLOAT
	* 3. BOOL
	* 4. ADDRESS
	* 5. REG
	*/
	int flag = reg[dest].type;
	
	

	/*
	* -1. NONE
	* 1. INT
	* 2. FLOAT
	* 3. BOOL
	* 4. ADDRESS
	* 5. REG
	*/
	int check = get_type(src);
	switch (flag)
	{
	case -1:
		if (check == 1) {
			reg[dest].iData = get_int(src);
			reg[dest].type = 1;
		}else if (check == 2) {
			reg[dest].fData = get_float(src);
			reg[dest].type = 2;
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	case 1:
		if (check == 1) {
			reg[dest].iData = get_int(src);
		} else if (check == 2) {
			reg[dest].fData = reg[dest].iData + get_float(src);
			reg[dest].iData = 0;
			reg[dest].type = 2;
		}else if (check == 5) {
			int num_reg = get_reg(src) - 1;
			if(!valid_reg(num_reg))
				throw InvalidOperand(address);
			int ty_reg = reg[num_reg].type;
			switch (ty_reg)
			{
			case 1:
				reg[dest].iData += reg[num_reg].iData;
				break;
			case 2:
				reg[dest].fData = reg[dest].iData + reg[num_reg].fData;
				reg[dest].iData = 0;
				reg[dest].type = 2;
				break;
			default:
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	case 2:
		if (check == 1) {
			reg[dest].fData += get_int(src);
		}
		else if (check == 2) {
			reg[dest].fData += get_float(src);
		}
		else if (check == 5) {
			int num_reg = get_reg(src) - 1;
			if (!valid_reg(num_reg))
				throw InvalidOperand(address);
			int ty_reg = reg[num_reg].type;
			switch (ty_reg)
			{
			case 1:
				reg[dest].fData += reg[num_reg].iData;
				break;
			case 2:
				reg[dest].fData = reg[dest].fData + reg[num_reg].fData;
				break;
			default:
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	default:
		throw InvalidOperand(address);
	}
}


void VM::MINUS(int dest, string src, int address){
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	
	/*
	* -1. NONE
	* 1. INT
	* 2. FLOAT
	* 3. BOOL
	* 4. ADDRESS
	* 5. REG
	*/
	// Lay type cua dest
	int flag = reg[dest].type;

	// kiem tra type cua src
	int check = get_type(src);

	switch (flag)
	{
	case 1:
		if (check == 1) {
			reg[dest].iData -= get_int(src);
		}
		else if (check == 2) {
			reg[dest].fData = reg[dest].iData - get_float(src);
			reg[dest].iData = 0;
			reg[dest].type = 2;
		}
		else if (check == 5) {
			int pos_reg = get_reg(src) - 1;
			if (!valid_reg(pos_reg))
				throw InvalidOperand(address);
			int type_reg = reg[pos_reg].type;
			if (type_reg == 1) {
				reg[dest].iData -= reg[pos_reg].iData;
			}
			else if (type_reg == 2) {
				reg[dest].fData = reg[dest].iData - reg[pos_reg].fData;
				reg[dest].iData = 0;
				reg[dest].type = 2;
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	case 2:
		if (check == 1) {
			reg[dest].fData -= get_int(src);
		}
		else if (check == 2) {
			reg[dest].fData -= get_float(src);
		}
		else if (check == 5) {
			int pos_reg = get_reg(src) - 1;
			if (!valid_reg(pos_reg))
				throw InvalidOperand(address);
			int type_reg = reg[pos_reg].type;
			if (type_reg == 1) {
				reg[dest].fData -= reg[pos_reg].iData;
			}
			else if (type_reg == 2) {
				reg[dest].fData -= reg[pos_reg].fData;
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	default:
		throw InvalidOperand(address);
	}
}

void VM::MUL(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	// Lay type cua dest
	int flag = reg[dest].type;

	// kiem tra type cua src
	int check = get_type(src);

	switch (flag)
	{
	case 1:
		if (check == 1) {
			reg[dest].iData *= get_int(src);
		}
		else if (check == 2) {
			reg[dest].fData = reg[dest].iData * get_float(src);
			reg[dest].iData = 0;
			reg[dest].type = 2;
		}
		else if (check == 5) {
			int pos_reg = get_reg(src) - 1;
			if (!valid_reg(pos_reg))
				throw InvalidOperand(address);
			int type_reg = reg[pos_reg].type;
			if (type_reg == 1) {
				reg[dest].iData *= reg[pos_reg].iData;
			}
			else if (type_reg == 2) {
				reg[dest].fData = reg[dest].iData * reg[pos_reg].fData;
				reg[dest].iData = 0;
				reg[dest].type = 2;
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	case 2:
		if (check == 1) {
			reg[dest].fData *= get_int(src);
		}
		else if (check == 2) {
			reg[dest].fData *= get_float(src);
		}
		else if (check == 5) {
			int pos_reg = get_reg(src) - 1;
			if (!valid_reg(pos_reg))
				throw InvalidOperand(address);
			int type_reg = reg[pos_reg].type;
			if (type_reg == 1) {
				reg[dest].fData *= reg[pos_reg].iData;
			}
			else if (type_reg == 2) {
				reg[dest].fData *= reg[pos_reg].fData;
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	default:
		throw InvalidOperand(address);
	}

}

void VM::DIV(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	// Lay type cua dest
	int flag = reg[dest].type;

	// kiem tra type cua src
	int check = get_type(src);

	switch (flag)
	{
	case 1:
		if (check == 1) {
			if (get_int(src) == 0)
				throw DivideByZero(address);
			reg[dest].iData /= get_int(src);
		}
		else if (check == 2) {
			if (get_int(src) == 0)
				throw DivideByZero(address);
			reg[dest].fData = reg[dest].iData / get_float(src);
			reg[dest].iData = 0;
			reg[dest].type = 2;
		}
		else if (check == 5) {
			int pos_reg = get_reg(src) - 1;
			if (!valid_reg(pos_reg))
				throw InvalidOperand(address);
			int type_reg = reg[pos_reg].type;
			if (type_reg == 1) {
				if(reg[pos_reg].iData == 0)
					throw DivideByZero(address);
				reg[dest].iData /= reg[pos_reg].iData;
			}
			else if (type_reg == 2) {
				reg[dest].fData = reg[dest].iData / reg[pos_reg].fData;
				reg[dest].iData = 0;
				reg[dest].type = 2;
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	case 2:
		if (check == 1) {
			if (get_int(src) == 0)
				throw DivideByZero(address);
			reg[dest].fData /= get_int(src);
		}
		else if (check == 2) {
			reg[dest].fData /= get_float(src);
		}
		else if (check == 5) {
			int pos_reg = get_reg(src) - 1;
			if (!valid_reg(pos_reg))
				throw InvalidOperand(address);
			int type_reg = reg[pos_reg].type;
			if (type_reg == 1) {
				if (reg[pos_reg].iData == 0)
					throw DivideByZero(address);
				reg[dest].fData /= reg[pos_reg].iData;
			}
			else if (type_reg == 2) {
				reg[dest].fData /= reg[pos_reg].fData;
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw InvalidOperand(address);
		}
		break;
	default:
		throw InvalidOperand(address);
	}

}


void VM::CMPEQ(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	int flag = reg[dest].type;

	int type = get_type(src);

	switch (flag)
	{
	case 1:
		if (type == 1) {
			if (reg[dest].iData == get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			MOVE(dest, "false", address);
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 1) {
				if (reg[dest].iData == reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 2) {
				MOVE(dest, "false", address);
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else
			throw TypeMismatch(address);

		break;
	case 2:
		if (type == 1) {
			MOVE(dest, "false", address);
		}
		else if (type == 2) {
			if (reg[dest].fData == get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 2) {
				if (reg[dest].fData == reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 1) {
				MOVE(dest, "false", address);
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type == 3) {
			if (reg[dest].bData == get_bool(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 3) {
				if (reg[dest].bData == reg[sreg].bData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	default:
		throw TypeMismatch(address);
	}

}



void VM::CMPNE(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	int flag = reg[dest].type;

	int type = get_type(src);

	switch (flag)
	{
	case 1:
		if (type == 1) {
			if (reg[dest].iData != get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			MOVE(dest, "true", address);
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 1) {
				if (reg[dest].iData != reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 2) {
				MOVE(dest, "true", address);
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else
			throw TypeMismatch(address);

		break;
	case 2:
		if (type == 1) {
			MOVE(dest, "true", address);
		}
		else if (type == 2) {
			if (reg[dest].fData != get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 2) {
				if (reg[dest].fData != reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 1) {
				MOVE(dest, "true", address);
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type == 3) {
			if (reg[dest].bData != get_bool(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 3) {
				if (reg[dest].bData != reg[sreg].bData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	default:
		throw TypeMismatch(address);
	}

}

void VM::CMPLT(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	int flag = reg[dest].type;

	int type = get_type(src);

	switch (flag)
	{
	case 1:
		if (type == 1) {
			if (reg[dest].iData < get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].iData < get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 1) {
				if (reg[dest].iData < reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 2) {
				if (reg[dest].iData < reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else
			throw TypeMismatch(address);

		break;
	case 2:
		if (type == 1) {
			if (reg[dest].fData < get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].fData < get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 2) {
				if (reg[dest].fData < reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 1) {
				if (reg[dest].fData < reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type == 3) {
			if (reg[dest].bData < get_bool(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 3) {
				if (reg[dest].bData < reg[sreg].bData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	default:
		throw TypeMismatch(address);
	}

}



void VM::CMPLE(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	int flag = reg[dest].type;

	int type = get_type(src);

	switch (flag)
	{
	case 1:
		if (type == 1) {
			if (reg[dest].iData <= get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].iData <= get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 1) {
				if (reg[dest].iData <= reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 2) {
				if (reg[dest].iData <= reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else
			throw TypeMismatch(address);

		break;
	case 2:
		if (type == 1) {
			if (reg[dest].fData <= get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].fData <= get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 2) {
				if (reg[dest].fData <= reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 1) {
				if (reg[dest].fData <= reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type == 3) {
			if (reg[dest].bData <= get_bool(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 3) {
				if (reg[dest].bData <= reg[sreg].bData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	default:
		throw TypeMismatch(address);
	}

}



void VM::CMPGT(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	int flag = reg[dest].type;

	int type = get_type(src);

	switch (flag)
	{
	case 1:
		if (type == 1) {
			if (reg[dest].iData > get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].iData > get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 1) {
				if (reg[dest].iData > reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 2) {
				if (reg[dest].iData > reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else
			throw TypeMismatch(address);

		break;
	case 2:
		if (type == 1) {
			if (reg[dest].fData > get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].fData > get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 2) {
				if (reg[dest].fData > reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 1) {
				if (reg[dest].fData > reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type == 3) {
			if (reg[dest].bData > get_bool(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 3) {
				if (reg[dest].bData > reg[sreg].bData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	default:
		throw TypeMismatch(address);
	}

}



void VM::CMPGE(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	int flag = reg[dest].type;

	int type = get_type(src);

	switch (flag)
	{
	case 1:
		if (type == 1) {
			if (reg[dest].iData >= get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].iData >= get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 1) {
				if (reg[dest].iData >= reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 2) {
				if (reg[dest].iData >= reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else
			throw TypeMismatch(address);

		break;
	case 2:
		if (type == 1) {
			if (reg[dest].fData >= get_int(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 2) {
			if (reg[dest].fData >= get_float(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 2) {
				if (reg[dest].fData >= reg[sreg].fData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else if (treg == 1) {
				if (reg[dest].fData >= reg[sreg].iData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type == 3) {
			if (reg[dest].bData >= get_bool(src)) {
				MOVE(dest, "true", address);
			}
			else {
				MOVE(dest, "false", address);
			}
		}
		else if (type == 5) {
			int sreg = get_reg(src) - 1;
			if (!valid_reg(sreg))
				throw InvalidOperand(address);
			int treg = reg[sreg].type;
			if (treg == 3) {
				if (reg[dest].bData >= reg[sreg].bData) {
					MOVE(dest, "true", address);
				}
				else {
					MOVE(dest, "false", address);
				}
			}
			else {
				throw TypeMismatch(address);
			}
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	default:
		throw TypeMismatch(address);
	}

}











void VM::MOVE(int dest, string src, int address) {
	if (!valid_reg(dest)) {
		throw InvalidOperand(address);
	}


	int check = get_type(src);
	switch (check)
	{
	case 1:
		reg[dest].iData = get_int(src);
		reg[dest].fData = 0;
		reg[dest].bData = false;
		reg[dest].address = 0;
		reg[dest].type = 1;
		break;
	case 2:
		reg[dest].fData = get_float(src);
		reg[dest].iData = 0;
		reg[dest].bData = false;
		reg[dest].address = 0;
		reg[dest].type = 2;
		break;
	case 3:
		reg[dest].bData = get_bool(src);
		reg[dest].iData = 0;
		reg[dest].fData = 0;
		reg[dest].address = 0;
		reg[dest].type = 3;
		break;
	case 4:
		reg[dest].address = get_address(src);
		reg[dest].iData = 0;
		reg[dest].fData = 0;
		reg[dest].bData = false;
		reg[dest].type = 4;
		break;
	case 5: 
	{
		int pos_reg = get_reg(src) - 1;
		if (!valid_reg(pos_reg))
			throw InvalidOperand(address);
		int type_src = reg[pos_reg].type;
		if (type_src == 1) {
			reg[dest].iData = reg[pos_reg].iData;
			reg[dest].fData = 0;
			reg[dest].bData = false;
			reg[dest].address = 0;
			reg[dest].type = 1;
		}
		else if (type_src == 2) {
			reg[dest].fData = reg[pos_reg].fData;
			reg[dest].iData = 0;
			reg[dest].bData = false;
			reg[dest].address = 0;
			reg[dest].type = 2;
		}
		else if (type_src == 3) {
			reg[dest].bData = reg[pos_reg].bData;
			reg[dest].iData = 0;
			reg[dest].fData = 0;
			reg[dest].address = 0;
			reg[dest].type = 3;
		}
		else if (type_src == 4) {
			reg[dest].address = reg[pos_reg].address;
			reg[dest].iData = 0;
			reg[dest].fData = 0;
			reg[dest].bData = false;
			reg[dest].type = 4;
		}
		break;
	}
	default:
		break;
	}
}



void VM::LOAD(int dest, string src, int address) {
	if (!valid_reg(dest)) {
		throw InvalidOperand(address);
	}

	int flag = reg[dest].type;

	int src_reg = get_reg(src) - 1;
	if (!valid_reg(src_reg))
		throw InvalidOperand(address);

	int type_src = reg[src_reg].type;
	switch (flag)
	{
	case 1:
		if (type_src == 1) {
			reg[dest].iData = reg[src_reg].iData;
		}
		else if (type_src == 2) {
			reg[dest].fData = reg[src_reg].fData;
			reg[dest].iData = 0;
			reg[dest].type = 2;
		}
		else if (type_src == 3)
		{
			reg[dest].bData = reg[src_reg].bData;
			reg[dest].iData = 0;
			reg[dest].type = 3;
		}
		else if (type_src == 4) {
			reg[dest].address = reg[src_reg].address;
			reg[dest].iData = 0;
			reg[dest].type = 4;
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 2:
		if (type_src == 1) {
			reg[dest].iData = reg[src_reg].iData;
			reg[dest].fData = 0;
			reg[dest].type = 1;
		}
		else if (type_src == 2) {
			reg[dest].fData = reg[src_reg].fData;
		}
		else if (type_src == 3)
		{
			reg[dest].bData = reg[src_reg].bData;
			reg[dest].fData = 0;
			reg[dest].type = 3;
		}
		else if (type_src == 4) {
			reg[dest].address = reg[src_reg].address;
			reg[dest].fData = 0;
			reg[dest].type = 4;
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 3:
		if (type_src == 1) {
			reg[dest].iData = reg[src_reg].iData;
			reg[dest].bData = false;
			reg[dest].type = 1;
		}
		else if (type_src == 2) {
			reg[dest].fData = reg[src_reg].fData;
			reg[dest].bData = 0;
			reg[dest].type = 2;
		}
		else if (type_src == 3){
			reg[dest].bData = reg[src_reg].bData;
		}
		else if (type_src == 4) {
			reg[dest].address = reg[src_reg].address;
			reg[dest].bData = 0;
			reg[dest].type = 4;
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case 4:
		if (type_src == 1) {
			reg[dest].iData = reg[src_reg].iData;
			reg[dest].address = 0;
			reg[dest].type = 1;
		}
		else if (type_src == 2) {
			reg[dest].fData = reg[src_reg].fData;
			reg[dest].address = 0;
			reg[dest].type = 2;
		}
		else if (type_src == 3) {
			reg[dest].bData = reg[src_reg].bData;
			reg[dest].address = 0;
			reg[dest].type = 3;
		}
		else if (type_src == 4) {
			reg[dest].address = reg[src_reg].address;
		}
		else {
			throw TypeMismatch(address);
		}
		break;
	case -1:
		this->MOVE(dest, src, address);
		break;
	default:
		throw InvalidOperand(address);
	}
}





int VM::JUMP(string src, int address) {
	int type = get_type(src);
	if (type == 4) {
		int tele = get_address(src);
		if (tele > this->size) {
			throw InvalidDestination(address);
		}
		return tele;
	}
	else {
		throw TypeMismatch(address);
	}

}



int VM::JUMPIF(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);
	if (reg[dest].type == 3) {
		int type = get_type(src);
		if (type == 4) {
			int adr = get_address(src);
			if (reg[dest].bData == false) {
				
				return address + 1;
			}
			else {
				if (adr >= size) {
					throw InvalidDestination(address);
				}
				return adr;
			}
		}
		else {
			throw TypeMismatch(address);
		}
	}
	else {
		throw InvalidDestination(address);
	}
	
    
}



int VM::CALL(int IP, string src, int address) {
	int type = get_type(src);
	if (type == 4) {
		int adr = get_address(src);
		if (adr >= size) {
			throw InvalidDestination(address);
		}
		this->state->push(IP);
		return adr;

	}
	else {
		throw TypeMismatch(address);
	}
}


int VM::RETURN() {
	return state->isEmpty() ? size : state->pop();
}


void VM::STORE(int dest, string src, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);
	MOVE(dest, src, address);

}




void VM::INPUT(int dest, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);

	//int flag = reg[dest].type;

	string temp = "";
	getline(cin, temp);

	int type = get_type(temp);

	if (type == 1 || type == 2 || type == 3) {
		this->MOVE(dest, temp, address);
	}
	else {
		throw InvalidInput(address);
	}
}




void VM::OUTPUT(string src, int address) {
	int type = get_type(src);
	if (type == 5) {
		int sreg = get_reg(src) - 1;
		if (!valid_reg(sreg))
			throw InvalidOperand(address);
		int treg = reg[sreg].type;
		if (treg == 1) {
			cout << reg[sreg].iData;
		}
		else if (treg == 2) {
			cout << reg[sreg].fData;
		}
		else if (treg == 3) {
			cout << reg[sreg].bData;
		}
		else if (treg == 4) {
			cout << reg[sreg].address;
		}
		else {
			cout << "NONE";
		}
	}
	else {
		cout << src;
	}
}









void VM::NOT(int dest, int address) {
	if (!valid_reg(dest))
		throw InvalidOperand(address);
	if (reg[dest].type == 3) {
		reg[dest].bData = !reg[dest].bData;
	}
	else {
		throw TypeMismatch(address);
	}
}



void VM::AND(int dest, string src, int address){
	if(!valid_reg(dest))
		throw InvalidOperand(address);
	if (reg[dest].type == 3) {
		reg[dest].bData = reg[dest].bData && get_bool(src);
	}
	else {
		throw TypeMismatch(address);
	}
}

void VM::OR(int dest, string src, int address)
{
	if (!valid_reg(dest))
		throw InvalidOperand(address);
	if (reg[dest].type == 3) {
		reg[dest].bData = reg[dest].bData || get_bool(src);
	}
	else {
		throw TypeMismatch(address);
	}
	
}



void VM::HALT(int &address) {
	address = size;
}





/*///////////////////////////////////////////
*
* Cac ham test, debug
*
*////////////////////////////////////////////


void VM::test_regex(string filename)
{
	ifstream ifs;
	ifs.open(filename);
	string line;
	while (!ifs.eof())
	{
		getline(ifs, line);
		data_in->push_back(line);
	}
	ifs.close();
	data_in->pr();
	int i = 1;
	while (!data_in->isEmpty())
	{
		cout << i << ". " << classify(data_in->getTop()) << endl;
		data_in->pop();
		i++;
	}
}