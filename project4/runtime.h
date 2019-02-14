#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "parser.h"

using namespace std;
string printOp();
string plusOp();
string minusOp();
string starOp();
string slashOp();
void Decleration();
string Initialize();
vector<ParseTree*> TreeVector;

int i = 0;
string errorMessage = "files";
map<string, string> stringVars;
map<string, int> intVars;
bool isError = false, setError = false;
string errors = "";

void run(ParseTree *tree, string file){
    errorMessage = file;
    tree->nodeIterator(TreeVector);
    int size = TreeVector.size(); 
    string output;

    

    for(i = 0; i < size; i++){
        if(TreeVector[i]->GetType() == PRINT_TYPE){
            string toPrint = printOp();
            if(toPrint.find(errorMessage) == 0){
                errors += file + toPrint.substr(errorMessage.size(), toPrint.size()-errorMessage.size()) + "\n";
            }
            output += toPrint;
        }
        else if(TreeVector[i]->GetType() == DECL_TYPE){
            Decleration();
        }
        else if(TreeVector[i]->GetType() == SET_TYPE){
            string Init = Initialize();
            if(Init.find(errorMessage) == 0){
                errors += file + Init.substr(errorMessage.size(), Init.size()-errorMessage.size()) + "\n";
            }
        }
    } 
    if(isError == false)
        cout<< output;
    else
        cout<< errors;
}

string printOp(){
    bool newLine = TreeVector[i]->is_newLine();
    i++;
    string out;
    if(TreeVector[i]->GetType() == PLUS_TYPE){
        out = plusOp();
    }
    else if(TreeVector[i]->GetType() == MINUS_TYPE){
        out = minusOp();
    }
    else if(TreeVector[i]->GetType() == STAR_TYPE){
        out = starOp();
    }
    else if(TreeVector[i]->GetType() == SLASH_TYPE){
        string temp = slashOp();
        if(temp.find_first_not_of( "0123456789." ) == string::npos)
            out = to_string((int)(atof(temp.c_str())));
        else
            out = temp;
    }
    else if(TreeVector[i]->GetType() == ID_TYPE){
        if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end())
            out = to_string(intVars[TreeVector[i]->GetIdValue()]);
        else if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end())
            out = stringVars[TreeVector[i]->GetIdValue()];
    }
    else if(TreeVector[i]->GetType() == INT_TYPE){
        out = to_string(TreeVector[i]->GetIntValue());
       
    }
    else if(TreeVector[i]->GetType() == STRING_TYPE){
        out = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
    }
    if(newLine){
        out += "\n";
    }
    return out;
}

string plusOp(){
    bool is_string = false;
    i++;
    int x, y;
    string a,b;
    if(TreeVector[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
    }
    else if(TreeVector[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(TreeVector[i]->GetType() == STAR_TYPE){
        string temp = starOp();
        if(temp.find_first_not_of( "0123456789." ) != string::npos){
            is_string = true;
            a = temp;
        }
        else{
            x = atoi(temp.c_str());
        }
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            
            b = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        }
    }
    else if(TreeVector[i]->GetType() == SLASH_TYPE){
        x = atoi(slashOp().c_str());
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        if(TreeVector[i]->GetType() == SLASH_TYPE){
            y = atoi(slashOp().c_str());
        }
    }
    else if(TreeVector[i]->GetType() == ID_TYPE){
        if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
            x = intVars[TreeVector[i]->GetIdValue()];
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                
            }
            else if(TreeVector[i]->GetType() == INT_TYPE){
                y = TreeVector[i]->GetIntValue();
            }
            else if(TreeVector[i]->GetType() == ID_TYPE){
                if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
                    y = intVars[TreeVector[i]->GetIdValue()];
                }
                else{
                    setError = true;
                    isError = true;
                    errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end()){
            is_string = true;
            a = stringVars[TreeVector[i]->GetIdValue()];
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                b = atoi(plusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == MINUS_TYPE){
                b = atoi(minusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                b = atoi(starOp().c_str());
            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                
            }
            else if(TreeVector[i]->GetType() == STRING_TYPE){
                b = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
            }
            else if(TreeVector[i]->GetType() == ID_TYPE){
                if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end()){
                    b = stringVars[TreeVector[i]->GetIdValue()];
                }
                else{
                    setError = true;
                    isError = true;
                    errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else{
            setError = true;
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(TreeVector[i]->GetType() == INT_TYPE){
        x = TreeVector[i]->GetIntValue();
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
    }
    else if(TreeVector[i]->GetType() == STRING_TYPE){
        is_string = true;
        a = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            b = plusOp();
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            b = minusOp();
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            b = starOp();
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            b = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        }
        else if(TreeVector[i]->GetType() == ID_TYPE){
            if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end()){
                b = stringVars[TreeVector[i]->GetIdValue()];
            }
            else{
                isError = true;
                errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
        }
    }
    if(is_string)
        return (a + b);
    else
        return to_string(x + y);
}

string starOp(){
    bool is_stringFirst = false, is_stringSecond = false;
    i++;
    int x;
    float y;
    string a,b;
    if(TreeVector[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            is_stringSecond = true;
            b = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        }
    }
    else if(TreeVector[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(TreeVector[i]->GetType() == STAR_TYPE){
        x = atoi(starOp().c_str());
    }
    else if(TreeVector[i]->GetType() == SLASH_TYPE){
        x = atoi(slashOp().c_str());
    }
    else if(TreeVector[i]->GetType() == ID_TYPE){
        if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
            x = intVars[TreeVector[i]->GetIdValue()];
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                string temp = slashOp();
                if(temp.find_first_not_of( "0123456789" ) == string::npos){
                    is_stringSecond = true;
                    b = temp;
                }
                else{
                    y = atoi(slashOp().c_str());
                }
            }
            else if(TreeVector[i]->GetType() == INT_TYPE){
                y = TreeVector[i]->GetIntValue();
            }
            else if(TreeVector[i]->GetType() == ID_TYPE){
                if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
                    y = intVars[TreeVector[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end()){
            is_stringFirst = true;
            a = stringVars[TreeVector[i]->GetIdValue()];
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                
            }
            else if(TreeVector[i]->GetType() == STRING_TYPE){
                isError = true;
                errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
            else if(TreeVector[i]->GetType() == INT_TYPE){
                y = TreeVector[i]->GetIntValue();
            }
            else if(TreeVector[i]->GetType() == ID_TYPE){
                if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
                    y = intVars[TreeVector[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(TreeVector[i]->GetType() == INT_TYPE){
        x = TreeVector[i]->GetIntValue();
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            y = atof(slashOp().c_str());
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            is_stringSecond = true;
            b = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        }
    }
    else if(TreeVector[i]->GetType() == STRING_TYPE){
        is_stringFirst = true;
        a = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }

    }
    if(is_stringFirst){
        string temp = a;
        for(int j = 1; j < y; j++)
            a = a + temp;
        return a;
    }
    else if(is_stringSecond){
        string temp = b;
        for(int j = 1; j < x; j++)
            b = b + b;
        return b;
    }
    else
        return to_string((int)(x * y));
}

string minusOp(){
    i++;
    int x, y;
    if(TreeVector[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
    }
    else if(TreeVector[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(TreeVector[i]->GetType() == STAR_TYPE){
        x = atoi(starOp().c_str());
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
    }
    else if(TreeVector[i]->GetType() == SLASH_TYPE){
        
    }
    else if(TreeVector[i]->GetType() == ID_TYPE){
        if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
            x = intVars[TreeVector[i]->GetIdValue()];
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                
            }
            else if(TreeVector[i]->GetType() == INT_TYPE){
                y = TreeVector[i]->GetIntValue();
            }
            else if(TreeVector[i]->GetType() == ID_TYPE){
                if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
                    y = intVars[TreeVector[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(TreeVector[i]->GetType() == INT_TYPE){
        x = TreeVector[i]->GetIntValue();
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
    }
    else if(TreeVector[i]->GetType() == STRING_TYPE){
        isError = true;
        errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
        return "done";
    }
        return to_string(x - y);
}

string slashOp(){
    bool is_string = false;
    int x, y;
    string a,b;
    i++;

    if(TreeVector[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(TreeVector[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(TreeVector[i]->GetType() == STAR_TYPE){
        x = atoi(starOp().c_str());
    }
    else if(TreeVector[i]->GetType() == ID_TYPE){
        if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
            x = intVars[TreeVector[i]->GetIdValue()];
            back1:
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                x = intVars[TreeVector[i-1]->GetIdValue()] / intVars[TreeVector[i+1]->GetIdValue()];
                i += 2;
                return to_string(x * intVars[TreeVector[i]->GetIdValue()]);

            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                i++;
                if(TreeVector[i]->GetType() == PLUS_TYPE){
                    x = x / atoi(plusOp().c_str());
                    goto back1;
                }
                else{
                    x = x/intVars[TreeVector[i]->GetIdValue()];
                    goto back1;
                }
            }
            else if(TreeVector[i]->GetType() == ID_TYPE){
                if(intVars.find(TreeVector[i]->GetIdValue()) != intVars.end()){
                    y = intVars[TreeVector[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
            else if(TreeVector[i]->GetType() == INT_TYPE){
                y = TreeVector[i]->GetIntValue();
            }
            else if(TreeVector[i]->GetType() == STRING_TYPE){
                isError = true;
                errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
        }
        else if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end()){
            a = stringVars[TreeVector[i]->GetIdValue()];
            back2:
            i++;
            if(TreeVector[i]->GetType() == PLUS_TYPE){
                b = plusOp();
            }
            else if(TreeVector[i]->GetType() == STAR_TYPE){
                b = starOp();
            }
            else if(TreeVector[i]->GetType() == SLASH_TYPE){
                i++;
                string temp = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
                int pos = a.find(temp);
                if(pos != -1){
                    a = a.erase(pos, temp.size());
                }
                goto back2;
            }
            else if(TreeVector[i]->GetType() == INT_TYPE){
                isError = true;
                errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
            else if(TreeVector[i]->GetType() == STRING_TYPE){
                is_string = true;
                b = TreeVector[i]->GetStringValue();
            }
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(TreeVector[i]->GetType() == INT_TYPE){
        back:
        x = TreeVector[i]->GetIntValue();
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            x = x/TreeVector[i]->GetType();
            i++;
            goto back;
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            y = TreeVector[i]->GetIntValue();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(TreeVector[i]->GetType() == STRING_TYPE){
        is_string = true;
        a = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            b = TreeVector[i]->GetStringValue();
        }
        else if(TreeVector[i]->GetType() == INT_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    if(is_string){
        string temp = b.substr(1, TreeVector[i]->GetStringValue().size()-2);
        int pos = a.find(temp);
        if(pos != -1){
            return a.erase(pos, temp.size());
        }
        return a;
    }
    else{
        return to_string((float)x / (float)y);
    }
}

void Decleration(){
    if(TreeVector[i]->GetDeclType() == T_STRING){
        i++;
        stringVars[TreeVector[i]->GetIdValue()];
    }
    else if(TreeVector[i]->GetDeclType() == T_INT){
        i++;
        intVars[TreeVector[i]->GetIdValue()];
    }
}

string Initialize(){
    setError = false;
    string a, b;
    i++;
    string key = TreeVector[i]->GetIdValue();
    if(stringVars.find(key) != stringVars.end()){
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            stringVars[key] = plusOp();
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            stringVars[key] = minusOp();
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            stringVars[key] = starOp();
        }
        else if(TreeVector[i]->GetType() == ID_TYPE){
            if(stringVars.find(TreeVector[i]->GetIdValue()) != stringVars.end()){
                stringVars[key] = stringVars[TreeVector[i]->GetIdValue()];
            }
            else{
                isError = true;
                errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            stringVars[key] = slashOp();
        }
        else if(TreeVector[i]->GetType() == STRING_TYPE){
            stringVars[key] = TreeVector[i]->GetStringValue().substr(1, TreeVector[i]->GetStringValue().size()-2);
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(intVars.find(key) != intVars.end()){
        i++;
        if(TreeVector[i]->GetType() == PLUS_TYPE){
            intVars[key] = atoi(plusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == MINUS_TYPE){
            intVars[key] = atoi(minusOp().c_str());
        }
        else if(TreeVector[i]->GetType() == STAR_TYPE){
            intVars[key] = atoi(starOp().c_str());
        }
        else if(TreeVector[i]->GetType() == SLASH_TYPE){
            intVars[key] = atoi(slashOp().c_str());
        }
        else if(TreeVector[i]->GetType() == INT_TYPE)
            intVars[key] = TreeVector[i]->GetIntValue();
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    if(setError){
        isError = true;
        errors += errorMessage + ":" + to_string(TreeVector[i]->getLineNumber()+1) + ":type error\n";
    }
    return "done";
}
