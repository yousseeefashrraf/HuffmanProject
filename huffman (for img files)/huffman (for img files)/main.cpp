

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
class cTNode{
public:
    int freq;
    char symbol;
    int numberOfBits;
    char * path;
    cTNode * pRight;
    cTNode * pLeft;
};
class binaryTree{
public:
    cTNode * root;
    binaryTree(){
        root = NULL;
    }
    void insert(cTNode * pnn){
        cTNode * pBack = NULL;
        cTNode * pTrav = root;
        if(pTrav == NULL){
            root = pnn;
        } else {
            while (pTrav != NULL) {
                pBack = pTrav;
                if(pTrav->freq > pnn->freq){
                    pTrav = pTrav->pLeft;
                } else {
                    pTrav = pTrav->pRight;
                }
            }
        }
    }
};
class cNode {
public:
    int freq;
    char symbol;
    char * path;
    int numberOfBits;
    cNode * pNext;
    cTNode * pDown;

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
class sortedLL{
public:
    cNode * head;
    sortedLL(){
        head = NULL;
    }
    
    cNode * serachAndFind(char val){
        cNode * pTrav = head;
        while (pTrav != NULL && pTrav ->symbol != val) {
            pTrav = pTrav->pNext;
        }
        
        return pTrav;
    }
    void insert (cNode * pnn){
        cNode * pBack = NULL;
        cNode * pTrav = head;
        if(pTrav == NULL){
            head = pnn;
            return ;
        } else {
            while (pTrav != NULL && pnn->freq > pTrav -> freq){
                pBack = pTrav;
                pTrav = pTrav->pNext;
                
            }
            
            if(pBack == NULL){
                pnn -> pNext = head;
                head = pnn;
                
            } else {
                pnn->pNext = pTrav;
                pBack->pNext = pnn;
            }
        }
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
void sortOut (sortedLL &l){
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
list calcFreq (ifstream & file){
    list frequecyList;
    file.seekg(0, file.end);
    int h = file.tellg();
    file.seekg(0, file.beg);
    char ch;
        for(int i = 0; i<h; i++){
            file.read(&ch, 1);
            cNode * nodeWithFrequency = frequecyList.serachAndFind(ch);
            if(nodeWithFrequency == NULL){
                cNode * pnn = new cNode ();
                pnn->pNext = NULL;
                pnn->symbol = ch;
                pnn->freq = 1;
                frequecyList.attach(pnn);
            } else {
                nodeWithFrequency -> freq += 1;
            }
        }
    
    return frequecyList;
}
sortedLL sortList(list l){
    sortedLL sorted;
    cNode * pTrav = l.head;
    cNode * pnn;
    while (pTrav != NULL) {
        pnn = new cNode ();
        pnn-> pNext = NULL;
        pnn->pDown = NULL;
        pnn->symbol = pTrav ->symbol;
        pnn->freq = pTrav -> freq;
        sorted.insert(pnn);
        pTrav = pTrav->pNext;
    }
    return sorted;
}
binaryTree makeTree(sortedLL & list){
    cNode * pTrav ;
    cTNode * head;
    cTNode * tempDown;
    binaryTree huffmanTree;
    while (list.head->pNext != NULL) {
        head = new cTNode();
        head->freq = list.head->freq + list.head->pNext->freq;
        head->symbol = '\0';
        head->pLeft = head->pRight = NULL;
        
        if(list.head->pDown==NULL){
            tempDown = new cTNode();
            tempDown->pLeft = tempDown->pRight = NULL;
            tempDown->symbol = list.head->symbol;
            tempDown->freq = list.head->freq;
            head->pLeft = tempDown;
            
        } else{
            head->pLeft = list.head->pDown;
        }
        
        pTrav = list.head;
        list.head = pTrav->pNext;
        delete pTrav;
        
        if(list.head->pDown==NULL){
            tempDown = new cTNode();
            tempDown->pLeft = tempDown->pRight = NULL;
            tempDown->symbol = list.head->symbol;
            tempDown->freq = list.head->freq;

            head->pRight = tempDown;
        } else{
            head->pRight = list.head->pDown;
        }
        pTrav = list.head;
        list.head = pTrav->pNext;
        delete pTrav;
        
        pTrav = new cNode ();
        pTrav->freq = head->freq;
        pTrav->pNext = NULL;
        pTrav->pDown = head;
        list.insert(pTrav);
    }
    
    huffmanTree.root = list.head->pDown;
    return huffmanTree;
}

void makeCode(cTNode * pTrav, char* path, char selection, list & huffmanCode, int numberOfBits, int & minBits){
    int len;
    char * newPath;
    cNode * pnn;
    if(pTrav == NULL){
        return;
    }

    if(path != NULL && selection != '\0'){
        for(len=0; path[len] != '\0';len++){
            
        }
        newPath = new char [len+1];
        for(int i=0; i<len;i++){
            newPath[i] = path[i];
        }
        newPath[len] = selection;
        path = newPath;
    } else {
        if(selection != '\0'){
            path = new char[1];
            path[0] = selection;
            pnn = new cNode();
            pnn->pNext = NULL;
            pnn->pDown = NULL;
            pnn->freq = pTrav->freq;
            pnn->numberOfBits = numberOfBits;
            pnn->symbol = pTrav->symbol;

        }
    }
    

    makeCode(pTrav->pLeft, path, '0', huffmanCode, numberOfBits+1, minBits);
    
    if(numberOfBits<minBits){
        minBits = numberOfBits;
    }
    if(pTrav->pLeft == NULL && pTrav->pRight == NULL){
         pnn = new cNode();
        int size=0;
        int i;
        for(i=0; path[i]!= '\0'; i++){
        }
        size = i+1;
        pnn->path = new char [size];
        for(i=0; i<size; i++){
            pnn->path[i] = path[i];
        }
        
        pnn->pNext = NULL;
        pnn->pDown = NULL;
        pnn->freq = pTrav->freq;
        pnn->symbol = pTrav->symbol;
        pnn->numberOfBits = numberOfBits;
        huffmanCode.attach(pnn);
    }
    makeCode(pTrav->pRight, path, '1', huffmanCode, numberOfBits+1, minBits);
}
void encoding(ifstream& file, list &code, ofstream & encoded){
    int currBit = 7;
    char encodedBit = 0;
    char bitToEncode;
    cNode *currNode;
    string message;
    file.seekg(0, file.end);
    int h = file.tellg();
    file.seekg(0, file.beg);
    char ch;
    
        for(int i=0; i<h; i++){
            file.read(&ch, 1);
            currNode = code.serachAndFind(ch);
            for(int j=0; currNode->path[j]!='\0';j++){
                if(currBit==-1){
                    currBit=7;
                    //putting the enocded bit into the encoded message
                    encoded<<encodedBit;
                        
                    
                    encodedBit = 0;
                    
                }
                if(currNode->path[j] == '0'){
                    bitToEncode = 0;
                } else {
                    bitToEncode = 1;
                }
                encodedBit = encodedBit | (bitToEncode<<currBit);
                    currBit--;
            }
        
    }
}


cNode * getNode(char * encodedBits, int numBits, list & code){
    cNode * pTrav = code.head;
    char currentCodeBit;
    while (pTrav != NULL) {

        if(numBits==pTrav->numberOfBits){
            
            int flagDifferent = 0;
            for(int i=0; i<numBits;i++){
                if( pTrav->path[i] == '0'){
                    
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

void getCodeToFile(list & code, ofstream & outputFile){
    cNode * pTrav = code.head;
    while (pTrav != NULL) {
        string path = "";
        for(int i=0; pTrav->path[i]!= '\0';i++){
            path+=pTrav->path[i];
        }
        
        outputFile<<pTrav->symbol<<","<<pTrav->numberOfBits<<","<<path<<endl;
            
        
        pTrav = pTrav->pNext;
    }
}
int main() {
    ofstream encodedTxt;
    encodedTxt.open("encodedImg.Txt");
    ofstream codeFile;
    codeFile.open("huffmanCode.txt");
    ifstream decodedTxt;
    ifstream img("img.bmp", ifstream::binary);
    list huffmanCode;
    sortedLL sortedFrequeny = sortList(calcFreq(img));
    int minBits = -99999999;
    binaryTree huffmanTree = makeTree(sortedFrequeny);
    makeCode(huffmanTree.root, NULL, '\0', huffmanCode, 0, minBits);
    
    /*
     cNode * pTrav = huffmanCode.head;

    while (pTrav != NULL) {
     
        cout<<"Freq: "<<pTrav->freq<<", "<<pTrav->symbol<<" << ";
        for(int i=0;pTrav->path[i]!='\0';i++){
            cout<<pTrav->path[i];
        }
        cout<<endl;
        pTrav = pTrav->pNext;
    }
    */
    
    encoding(img, huffmanCode, encodedTxt);
    getCodeToFile(huffmanCode, codeFile);
    codeFile.close();
    }
