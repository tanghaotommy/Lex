#include<iostream>
#include<stack>
#include<queue>
#include<stack>
#include<string>
#include<fstream>
using namespace std;

#define BEGIN 1;
#define COMMON 2;
#define END 3;
const int reLength = 100;
const int stateNumber = 100;
const int linkNumber = 100;
const int terminalNumber = 100;
const int DFAStateNumber = 100;
char terminal[terminalNumber];
int terminalCount = 0;
int DFAStateCount = 0;

class State{
	class Link{
		char terminal;
		State *nextState;
		State *lastState;
	public:
		Link(){
			terminal = '1';
			//nextState = new State();
		}
		Link(char b, State *s){
			terminal = b;
			nextState = s;
		}
		void setnextState(State *s){
			nextState = s;
		}
		char getTerminal(){
			return terminal;
		}
		State* getnextState(){
			return nextState;
		}
		State* getlastState(){
			return lastState;
		}
	    void setlastState(State *s){
			lastState = s;
		}
	};
private:
	static int count;
	int id;
	Link *link[linkNumber];
	int linkCount;
	int type; //begin end common;
public:
	State(){
		linkCount = 0;
		id = count;
		count++;
		type = COMMON;
	}
	State(int c){
		linkCount = c;
	}
	void setType(int t){
		type = t;
	}
	int getType(){
		return type;
	}
	int addLink(char c, State* s){
		link[linkCount] = new Link(c,s);
		linkCount++;
		if(linkCount >= linkCount) return -1;
		return 1;
	}
	Link* getLink(){
		return link[0];
	}
	bool hasLink(char c){
		for(int i=0;i<linkCount;i++){
			if(link[i]->getTerminal() == c){
				return true;
			}
		}
		return false;
	}
	Link* getLink(char c){
		for(int i=0;i<linkCount;i++){
			if(link[i]->getTerminal() == c){
				return link[i];
			}
		}
	}
	Link* getLink(int i){
		return link[i];
	}
	int getlinkCount(){
		return linkCount;
	}
	void print(){
		for(int i=0;i<linkCount;i++){
			cout<<link[i]->getTerminal()<<endl;
		}
	}
	int getcount(){
		return count;
	}
	int getid(){
		return id;
	}
	void deleteID(){
		count--;
	}
	void setID(int i){
		id = i;
	}

};
class DFAState{
		class Link{
		char terminal;
		DFAState *nextDFAState;
	public:
		Link(){
			terminal = '1';
			//nextState = new State();
		}
		Link(char b, DFAState *s){
			terminal = b;
			nextDFAState = s;
		}
		void setnextState(DFAState *s){
			nextDFAState = s;
		}
		char getTerminal(){
			return terminal;
		}
		DFAState* getnextDFAState(){
			return nextDFAState;
		}
	};
private:
	static int count;
	int id;
	Link *link[linkNumber];
	int linkCount;
	int type; //begin end common;
	State *state[stateNumber];
	int stateCount;
public:
	DFAState(){
		linkCount = 0;
		id = count;
		count++;
		type = COMMON;
		stateCount = 0;
	}
	DFAState(int c){
		linkCount = c;
	}
	void setType(int t){
		type = t;
	}
	int getType(){
		return type;
	}
	int addLink(char c, DFAState* s){
		link[linkCount] = new Link(c,s);
		linkCount++;
		if(linkCount >= linkCount) return -1;
		return 1;
	}
	Link* getLink(){
		return link[0];
	}
	Link* getLink(char c){
		for(int i=0;i<linkCount;i++){
			if(link[i]->getTerminal() == c){
				return link[i];
			}
		}
	}
	Link* getLink(int i){
		return link[i];
	}
	int getlinkCount(){
		return linkCount;
	}
	void addState(State *s){
		state[stateCount] = s;
		stateCount++;
	}
	int getStateCount(){
		return stateCount;
	}
	State *getState(int i){
		return state[i];
	}
	bool hasState(State *s){
		for(int i=0;i<stateCount;i++){
			if(state[i] == s){
				return true;
			}
		}
		return false;
	}
	void printLinks(){
		for(int i=0;i<linkCount;i++){
			cout<<link[i]->getTerminal()<<endl;
		}
	}
	void printStates(){
		for(int i=0;i<stateCount;i++){
			cout<<state[i]->getid()<<",";
		}
		cout<<endl;
	}
	int getcount(){
		return count;
	}
	int getid(){
		return id;
	}
	void deleteCount(){
		count--;
	}
	bool isEquals(DFAState *ds){
		if(ds->getStateCount() != stateCount) return false;
		for(int i=0;i<stateCount;i++){
			bool flag = false;
			for(int j=0;j<ds->getStateCount();j++){
				if(state[i] == ds->getState(j)){
					flag = true;break;
				}
			}
			if(flag == false) return false;
		}
		return true;
	}
};
int State::count = 0;
int DFAState::count = 0;
State *initial;
DFAState *DFAinitial;
DFAState *DFAstate[DFAStateNumber];

bool isTerminalExists(char c){
		for (int i=0;i<terminalCount;i++){
		if (terminal[i] == c){
			return true;
		}
	}
	return false;
};
void addTerminal(char c){
	terminalCount++;
	terminal[terminalCount-1] = c;
}
void printTerminals(){
		for (int i=0;i<terminalCount;i++){
			cout<<terminal[i];
		}
		cout<<endl;
}

State* parser(State *start,State *end, char *re,int length,int flag){
	char *current = re;
	char *tail = re + length -1;
	State *currentState = start;
	int or = 0;
	cout<<"Length: "<<length<<endl;
	while(current <= tail){
		if(*current == '('){//发现(
			int count = 0;
			int pareCount = 0;
			pareCount++;
			for(char* i=current+1;i<=tail;i++){
				if(*i == '(') pareCount++;
				if(*i == ')') pareCount--;
				//if(*i == ')' && *(i+1) != '*'){
				if(pareCount == 0){//找到了对应的)
					if( i<tail && *(i+1) != '*' ){//括号后面不是*
						if( *(i+1) != '|' && *(i+1) != '(' && *(i+1) != ')'){//括号后面是终结符，需要加一个状态
							cout<<"Message: Find terminal after )! Add a new state."<<endl;
							int clength = i - current - 1;
							char *c = new char[clength];
							cout<<"Get (): "<<*i<<endl;
							for(int j = 0 ;j<i-current-1;j++){
								c[j] = *(current+j+1);
								cout<<c[j];
							}
							cout<<strlen(c)<<endl;
							current = i + 1;
							State *state = new State();
							currentState = parser(currentState,state,c,clength,1);
							cout<<"Return state: "<<currentState->getid()<<endl;
							break;
						}else if(*(i+1) == '|' && or == 0){//括号后面是第一个|
							cout<<"Message: Find the first )|! Add a new state."<<endl;
							int clength = i - current - 1;
							char *c = new char[clength];
							cout<<"Get (): "<<*i<<endl;
							for(int j = 0 ;j<i-current-1;j++){
								c[j] = *(current+j+1);
								cout<<c[j];
							}
							cout<<strlen(c)<<endl;
							current = i;
							State *state = new State();
							currentState = parser(currentState,state,c,clength,1);
							cout<<"Return state: "<<currentState->getid()<<endl;
							break;
						}else{
							cout<<"Message: Find ( or | after )."<<endl;
							int clength = i - current - 1;
							char *c = new char[clength];
							cout<<"Get (): "<<*i<<endl;
							for(int j = 0 ;j<i-current-1;j++){
								c[j] = *(current+j+1);
								cout<<c[j];
							}
							cout<<strlen(c)<<endl;
							current = i;
							currentState = parser(currentState,end,c,clength,1);
							cout<<"Return state: "<<currentState->getid()<<endl;
							break;
						}
					}
					if(i == tail ){
						cout<<"Message: Find ) at tail."<<endl;
						int clength = i - current - 1;
						char *c = new char[clength];
						cout<<"Get (): "<<*i<<endl;
						for(int j = 0 ;j<i-current-1;j++){
							c[j] = *(current+j+1);
							cout<<c[j];
						}
						cout<<strlen(c)<<endl;
						current = i;
						currentState = parser(currentState,end,c,clength,1);
						cout<<"Return state: "<<currentState->getid()<<endl;
						break;
					}
					//if(*i == ')' && *(i+1) == '*' ){
					if( *(i+1) == '*'){
						cout<<"Message: Find * after )! Add two new states."<<endl;
						int clength = i - current - 1;
						char *c = new char[clength];
						cout<<"Get (): "<<*i<<endl;
						for(int j = 0 ;j<i-current-1;j++){
							c[j] = *(current+j+1);
							cout<<c[j];
						}
						cout<<strlen(c)<<endl;
						current = i;
						State *state = new State();
						State *state2 = new State();
						currentState->addLink('$',state);
						cout<<"add link $ from "<<currentState->getid()<<" to "<<state->getid()<<endl; 
						state->addLink('$',state2);
						cout<<"add link $ from "<<state->getid()<<" to "<<state2->getid()<<endl; 
						currentState = parser(state,state,c,clength,1);
						currentState = state2;
						cout<<"Return state: "<<currentState->getid()<<endl;
						break;
					}
				}
				if(i == tail && pareCount!= 0){
					cout<<"Wrong REs with no matching \')\'!"<<endl;
					getchar();
					exit(0);
				}
			}
			continue;
		}
		if(current<tail && *current == '|'){//发现|
			if(or == 0){
				cout<<"Message: Find the first |!"<<endl;
				if(flag == 0){
					cout<<"Set "<<currentState->getid()<<" to "<<end->getid()<<endl;
					currentState->setID(end->getid());
					currentState->deleteID();
					delete end;
				}
				end = currentState;
				currentState = start;
				or = 1;
				//cout<<"or = "<<or<<endl;
			}
			current++;continue;
		}
		if(current<tail && *current != '*' && *current != ')' && *(current+1) == '|' && or == 1){//发现第二个|
			cout<<"Message: Find another | after terminal!";
			if(!isTerminalExists(*current)) addTerminal(*current);
			currentState->addLink(*current,end);
			currentState->getLink(*current)->setlastState(currentState);
			cout<<"Add link "<<*current<<" from "<<currentState->getid()<<" to "<<end->getid()<<endl;
			currentState = start;
			current++;continue;
		}
		if(current<tail &&  *current == ')' && *(current+1) == '|' && or == 1){//发现第二个|
			cout<<"Message: Find another )|!"<<endl;
			currentState = start;
			current++;continue;
		}
		if(current<tail && (*current == '*' || *current == '(' || *current == ')')) {//发现一系列非终结符
			cout<<"Message: Find non-terminal!"<<endl;
			current++;continue;
		}
		if(current<tail && *(current + 1) != '*'  ){//发现连续两个终结符
			cout<<"Message: Find two successive terminals!"<<endl;
			State *state = new State();
			if(!isTerminalExists(*current)) addTerminal(*current);
			currentState->addLink(*current,state);
			currentState->getLink(*current)->setlastState(currentState);
			cout<<"Add link "<<*current<<" from "<<currentState->getid()<<" to "<<state->getid()<<endl;
			current++;
			currentState = state;
			continue;
		}
		if(current<tail && *(current + 1) == '*' && or == 0 ){//发现a*
			cout<<"Message: Find terminal*!"<<endl;
			State *state = new State();
			State *state2 = new State();
			if(!isTerminalExists(*current)) addTerminal(*current);
			currentState->addLink('$',state);
			currentState->getLink('$')->setlastState(currentState);
			cout<<"Add link $ from "<<currentState->getid()<<" to "<<state->getid()<<endl;
			state->addLink('$',state2);
			state->getLink('$')->setlastState(state);
			cout<<"Add link $ from "<<state->getid()<<" to "<<state2->getid()<<endl;
			state->addLink(*current,state);
			state->getLink(*current)->setlastState(state);
			cout<<"Add link "<<*current<<" from "<<state->getid()<<" to "<<state->getid()<<endl;
			current++;
			currentState = state2;
			continue;
		}
		if(current<tail && *(current + 1) == '*' && or == 1 ){//发现a*并且与另外一个并列
			if(current+1<tail && (*(current+1)!='|' || *(current+1)!=')'|| *(current+1)!='(')){
				State *state = new State();
				State *state2 = new State();
				if(!isTerminalExists(*current)) addTerminal(*current);
					currentState->addLink('$',state);
				currentState->getLink('$')->setlastState(currentState);
				cout<<"Add link $ from "<<currentState->getid()<<" to "<<state->getid()<<endl;
				state->addLink('$',state2);
				state->getLink('$')->setlastState(state);
				cout<<"Add link $ from "<<state->getid()<<" to "<<state2->getid()<<endl;
				state->addLink(*current,state);
				state->getLink(*current)->setlastState(state);
				cout<<"Add link "<<*current<<" from "<<state->getid()<<" to "<<state->getid()<<endl;
				current++;
				currentState = state2;
				continue;
			}
			if(current + 1 == tail){
				State *state = new State();
				if(!isTerminalExists(*current)) addTerminal(*current);
				currentState->addLink('$',state);
				currentState->getLink('$')->setlastState(currentState);
				cout<<"Add link $ from "<<currentState->getid()<<" to "<<state->getid()<<endl;
				state->addLink('$',end);
				state->getLink('$')->setlastState(state);
				cout<<"Add link $ from "<<state->getid()<<" to "<<end->getid()<<endl;
				state->addLink(*current,state);
				state->getLink(*current)->setlastState(state);
				cout<<"Add link "<<*current<<" from "<<state->getid()<<" to "<<state->getid()<<endl;
				current++;
				currentState = end;
				currentState->setType(3);
				continue;
			}
		}
		if(current == tail && *current != '*' && *current != ')'){//尾部是终结符
			cout<<"Message: Find terminal at the end!";
			if(!isTerminalExists(*current)) addTerminal(*current);
			currentState->addLink(*current,end);
			currentState->getLink(*current)->setlastState(currentState);
			cout<<"Add link "<<*current<<" from "<<currentState->getid()<<" to "<<end->getid()<<endl;
			if(flag == 0)//主字符串才需要将最末尾状态变为3
				end->setType(3);
			current++;
			continue;
		}
		if(current == tail && or == 0 && *current == '*' ){//尾部是*，并且无并列关系
			cout<<"Message: Find * at the end and no | appears!";
			cout<<"Set "<<currentState->getid()<<" to "<<end->getid()<<endl;
			currentState->setID(end->getid());
			delete end;
			end = currentState;
			if(flag == 0)//主字符串才需要将最末尾状态变为3
				currentState->setType(3);
			current++;
			currentState->deleteID();
			continue;
		}
		if(current == tail && or == 1 && *current == '*' ){//有并列关系，并且尾部是*
			cout<<"Message: Find * at the end and | appears!"<<endl;
			current++;
			continue;
		}
		if(current == tail && *current == ')'){
			cout<<"Message: Find ) at the end!"<<endl;
			if(flag == 0)
				currentState->setType(3);
			current++;
			continue;
		}
	}
	return end;
}

State* converttoNFA(State *start,State *end, char *re,int length,int flag){
	return parser(start,end,re,length,flag);
}
void printNFA(){
	bool visited[stateNumber];
	for(int i=0;i<stateNumber;i++){
		visited[i] = false;
	}
	stack<State*> s;
	s.push(initial);
	visited[initial->getid()] = true;
	while(!s.empty()){
		State *currentState = s.top();
		s.pop();
		for(int i=0;i<currentState->getlinkCount();i++){
			if(!visited[currentState->getLink(i)->getnextState()->getid()]) {
				s.push(currentState->getLink(i)->getnextState());
				visited[currentState->getLink(i)->getnextState()->getid()] = true;
			}
			cout<<currentState->getid()<<"-"<<currentState->getLink(i)->getTerminal()<<">"<<currentState->getLink(i)->getnextState()->getid()<<"  ";
		}
		cout<<currentState->getid()<<" type: "<<currentState->getType()<<endl;
	}
};
void addEnclosure(DFAState *ds){
	stack<State*> s;
	for(int i = 0;i<ds->getStateCount();i++){
		s.push(ds->getState(i));
	}
	while(!s.empty()){
		State *currentState = s.top();
		s.pop();
		if(currentState->hasLink('$')){
			if(!ds->hasState(currentState->getLink('$')->getnextState())){
				ds->addState(currentState->getLink('$')->getnextState());
				s.push(currentState->getLink('$')->getnextState());
			}
		}
	}
	cout<<ds->getid()<<": {";
    ds->printStates();
}
bool hasDFAState(DFAState *ds){
	cout<<"Checking ";
	ds->printStates();
	for(int i = 0 ;i<DFAStateCount;i++){
		DFAState *currentDFAState = DFAstate[i];
		if(currentDFAState->isEquals(ds)){
			currentDFAState->printStates();
			return true;
		}
	}
	return false;
}
DFAState* getRepeatDFAState(DFAState* ds){
	for(int i = 0 ;i<DFAStateCount;i++){
		DFAState *currentDFAState = DFAstate[i];
		if(currentDFAState->isEquals(ds)){
			return currentDFAState;
		}
	}
}
bool isEndDFA(DFAState* ds){
	for(int i=0;i<ds->getStateCount();i++){
		if(ds->getState(i)->getType() == 3) {
			return true;
		}
	}
	return false;
}
char* convertoDFA(){
	DFAinitial = new DFAState();
	DFAstate[DFAStateCount] = DFAinitial;
	DFAStateCount++;
	stack<DFAState*> s;
	DFAState *currentDFAState = DFAinitial;
	currentDFAState->addState(initial);
	currentDFAState->setType(1);
	addEnclosure(currentDFAState);
	s.push(currentDFAState);
	while(!s.empty()){
		currentDFAState = s.top();
		s.pop();
		for(int i=0;i<terminalCount;i++){
			cout<<currentDFAState->getid()<<"-"<<terminal[i]<<">: ";
			DFAState *ds = new DFAState();
			for(int j=0;j<currentDFAState->getStateCount();j++){
				if(currentDFAState->getState(j)->hasLink(terminal[i])){
					if(!ds->hasState(currentDFAState->getState(j)->getLink(terminal[i])->getnextState())){
						ds->addState(currentDFAState->getState(j)->getLink(terminal[i])->getnextState());
					}
				}
			}
			addEnclosure(ds);
			if(hasDFAState(ds)){
				cout<<"Repeated DFA\n";
				currentDFAState->deleteCount();
				currentDFAState->addLink(terminal[i],getRepeatDFAState(ds));
			}else{		
				if(ds->getStateCount() > 0){
					cout<<"New DFA!\n";
					currentDFAState->addLink(terminal[i],ds);
					cout<<currentDFAState->getid()<<"-"<<terminal[i]<<">"<<ds->getid()<<endl;
					s.push(ds);
					DFAstate[DFAStateCount] = ds;
					DFAStateCount++;
					if(isEndDFA(ds)){
						ds->setType(3);
					}
				}
				else{
					ds->deleteCount();
					cout<<"NULL DFA!\n";
				}
			}
		}
	}
	return "Convert to DFA Success!\n";
}
void printDFA(){
	bool visited[stateNumber];
	for(int i=0;i<stateNumber;i++){
		visited[i] = false;
	}
	stack<DFAState*> s;
	s.push(DFAinitial);
	int count = 0;
	while(!s.empty()){
		DFAState *currentDFAState = s.top();
		s.pop();
		count++;
		visited[currentDFAState->getid()] = true;
		for(int i=0;i<currentDFAState->getlinkCount();i++){
			if(!visited[currentDFAState->getLink(i)->getnextDFAState()->getid()]) s.push(currentDFAState->getLink(i)->getnextDFAState());
			cout<<currentDFAState->getid()<<"-"<<currentDFAState->getLink(i)->getTerminal()<<">"<<currentDFAState->getLink(i)->getnextDFAState()->getid()<<"  ";
		}
		cout<<currentDFAState->getid()<<" type: "<<currentDFAState->getType()<<endl;
	}
}
char* convertoScanner(){
	ofstream of;
	of.open("d:\\scanner.cpp");
	of<<"#include<iostream>\nusing namespace std;\n";
    of<<"int state = "<<DFAinitial->getid()<<";\n";

	of<<"int judge(char* next,char* input, int length){\n";
	of<<"while(next <= input+length){\n";
	of<<"switch(state){\n";
	for(int i=0;i<DFAStateCount;i++){
		of<<"case "<<DFAstate[i]->getid()<<":\n";
		for(int j=0;j<DFAstate[i]->getlinkCount();j++){
			of<<"if(*next == \'"<<DFAstate[i]->getLink(j)->getTerminal()<<"\'";
			of<<") ";
			of<<"{\nstate = "<<DFAstate[i]->getLink(j)->getnextDFAState()->getid()<<";break;\n}\n";
		}
		if(DFAstate[i]->getType() == 3){
			of<<"if(next == input+length){\n";
			of<<"return 0;";
			of<<"}\n";
		}
		of<<"return 1;\n";
	}
	of<<"}\n";
	of<<"next++;\n";
	of<<"}\n";
	of<<"}\n";

	of<<"void main(){\n";

	of<<"int length_MAX = 100;\n";
	of<<"char *input = new char[length_MAX];\n";
	of<<"cout<<\"Input the lex: \";\n";
	of<<"cin>>input;\n";
	of<<"int length = strlen(input);\n";
	of<<"char *begin = input;\nchar *next = begin;\n";
	of<<"int result = judge(begin,begin,length);\n";
	of<<"if(result == 0) cout<<\"Correct lexem!\";\nelse cout<<\"Lexical Error!\";\n";
	of<<"getchar();getchar();\n}\n";

	of.close();
	return "Convert to Scanner Success!Path at d:\\scanner.cpp\n";
}
void main(){
	//char *re = "(a*a(abc)c)";
	//char *re = "a|b|c";
	//char *re = "if|then";
	//char *re =  "a(bab*a)*(a|b)b*";
	char *re = new char[reLength];
	cout<<"Input the REs: ";
	cin>>re;
	int length = strlen(re);
	initial = new State();
	State *end = new State();
	initial->setType(1);
	end->setType(3);
	cout<<"Result end: "<<converttoNFA(initial,end,re,strlen(re),0)->getid()<<endl;
	cout<<"********************"<<endl;
	cout<<"NFA:\n";
	printNFA();
	cout<<"********************"<<endl;
	cout<<"********************"<<endl;
	cout<<"terminals: ";
	printTerminals();
	cout<<"********************"<<endl;
	cout<<convertoDFA();
	cout<<"********************"<<endl;
	cout<<"DFA:\n";
	printDFA();
	cout<<"********************"<<endl;
	cout<<convertoScanner();
	getchar();
	getchar();
}

