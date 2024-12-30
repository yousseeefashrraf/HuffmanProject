#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
class cNode {
public:
    int freq;
    char symbol;
    char * path;
    int numberOfBits;
    cNode * pNext;

};
class list{
public:
    cNode * head;
    cNode * tail;

    list(){
        head = tail = NULL;
    }
    ~list(){
        cNode * pTrav = head;
        while(pTrav != NULL){
            head = pTrav->pNext;
            pTrav->pNext = NULL;
            delete pTrav;
            pTrav = head;
        }
    }
    void attach(cNode * newcNode){
        if (head == NULL){
            head = newcNode;
            tail = newcNode;
        } else {
            tail->pNext = newcNode;
            tail = newcNode;
        }
    }
    cNode * serachAndFind(char val){
        cNode * pTrav = head;
        while (pTrav != NULL && pTrav ->symbol != val) {
            pTrav = pTrav->pNext;
        }
        
        return pTrav;
    }
        
};
    

void listOut (list &l){
    cNode * pTrav = l.head;
    cout<<"[";
    while (pTrav!=NULL) {
        if (pTrav->pNext!=NULL){
            cout<<"("<<pTrav->symbol<<", "<<pTrav->freq<<")"<<" ,";
        } else { cout<<"("<<pTrav->symbol<<", "<<pTrav->freq<<")"; }
        pTrav=pTrav->pNext;
    }
    cout<<"]\n";
}




cNode * getNode(char * encodedBits, int numBits, list & code){
    cNode * pTrav = code.head;
    char currentCodeBit;
    while (pTrav != NULL) {

        if(numBits==pTrav->numberOfBits){
            
            int flagDifferent = 0;
            for(int i=0; i<numBits;i++){
                if(pTrav->path[i] == '0'){
                    
                    char m = 0;
                     currentCodeBit = m<<7;
                } else {
                    char m = 1;
                     currentCodeBit = m<<7;
                }
                if((currentCodeBit) != encodedBits[i]){
                    flagDifferent = 1;
                    break;
                }
            }
            if(!flagDifferent){
                
                return pTrav;
            }
        }
        pTrav = pTrav->pNext;
    }
    
    return NULL;
}
void getCodeToFile(list & code, ifstream & huffmanFile){
    string data="";
    cNode* pnn = NULL;
    int start;
    int currPosition=0;
    int k=0;
    huffmanFile.seekg(0, huffmanFile.end);
    int h = huffmanFile.tellg();
    huffmanFile.seekg(0, huffmanFile.beg);
    char ch;
    int ct=0;
    for(int i=0; i<h; i++, currPosition++){
        if(currPosition==0){
            pnn = new cNode();
        }
        huffmanFile.read(&ch, 1);

        if(ch == ',' && currPosition!=0){
            data="";
            ct++;
        } else {
            if(ch == '\n' && currPosition!=0){
                currPosition = -1;
                code.attach(pnn);
                pnn = NULL;
                ct=0;
                k=0;
            } else {
                if(ct==0){
                    pnn->symbol = ch;
                }
                if(ct==1){
                    data+=ch;
                    pnn->numberOfBits = stoi(data);
                } else {
                    if( ct == 2){
                        char *newPath;
                        int x;
                        int size;
                        if(pnn->path != NULL){
                            if(ch!='0' || ch!= '1'){
                                
                            }
                            for (size=0; pnn->path[size]!='\0'; size++) {
                                
                            }
                            newPath = new char [size+1];
                            newPath[size] = ch;
                            for (x=0; x<size; x++) {
                                newPath[x] = pnn->path[x];
                            }
                        } else {
                            pnn->path = new char;
                            pnn->path[0]=ch;
                        }
                        if(pnn->path == NULL){
                            k=0;
                        }
                        pnn -> path[k++] = ch;
                    }
            }
            
            }
        }
     
        


    }
}

void decoding(ifstream & file, list&code, ofstream & decoded, int minBits){
    char * encodedByte = NULL;
    char m = 1;
    int currBit = 0;
    file.seekg(0, file.end);
    int h = file.tellg();
    file.seekg(0, file.beg);

    char ch;
        for(int i=0; i<h;i++){
            file.read(&ch, 1);
            for (int bit=0; bit<8; bit++, currBit++) {
                if(encodedByte != NULL){
                    char * newByteWithNewBit = new char [currBit+1];
                    newByteWithNewBit[currBit] = ((m<<(7-bit)) & ch)<<bit;

                    for(int c=0; c<currBit; c++){
                        newByteWithNewBit[c] = encodedByte[c];
                    }
                    delete encodedByte;
                    encodedByte = newByteWithNewBit;
                    
                } else {
                    encodedByte = new char;
                    encodedByte[0] = ((m<<(7-bit)) & ch)<<bit;
                }
                cNode * nodeWithCode = NULL;
                //if this byte is in the list
                if(currBit>=minBits){
                    nodeWithCode = getNode(encodedByte, currBit+1, code);
                }
                
                if(nodeWithCode != NULL){
                    
//                    decoed.write(&ch, 1);
                    decoded<<nodeWithCode->symbol;
                    currBit = -1;
                    delete encodedByte;
                    encodedByte = NULL;
                }
                
            
        }
    }
}

int main() {

    ifstream decodedTxt;
    ifstream huffmanFile ("huffmanCode.txt", ifstream::binary);

    ofstream decodedImg ("decodedImg.bmp", ofstream::binary);
    ifstream encodedTxt ("encodedImg.txt", ifstream::binary);

    list huffmanCode;
    int minBits = -99999999;
    
    getCodeToFile(huffmanCode, huffmanFile);
    
    decodedTxt.open("encodedImg.Txt");
    decoding(encodedTxt, huffmanCode, decodedImg, minBits);
    decodedTxt.close();
}
