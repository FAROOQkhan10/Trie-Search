#include<bits/stdc++.h>
using namespace std;

class TrieNode{
   public:
     unordered_map<char,TrieNode*> children;
     bool isEnd;

     TrieNode(){
          isEnd=false;
     }     
};

class Trie{
 public:      
   TrieNode *root;    
   Trie(){        
        root = new TrieNode();
   }
  
  void insert(string s);
  TrieNode* exact_search(string s); 
  vector<string> pre_search(string s);

};



void Trie::insert(string s){
 
     TrieNode * current = root;

     for(auto t:s){

          if(current->children.find(t)!=current->children.end())
                current = current->children[t];
          
          else{
               current->children.insert({t,new TrieNode()});
          }

     }
     current->isEnd=true;
}


TrieNode* Trie::exact_search(string s){
       
       TrieNode* current = root;
       
       auto start = chrono::high_resolution_clock::now();


       for(auto t:s){
 
          if(current->children.find(t)!=current->children.end())
               current = current->children[t];
          
          else
             return NULL;

       }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\n"
         << current->isEnd << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

     
     return current->isEnd?current:NULL;
}

void get_all_words(TrieNode* current,vector<string>&res,string s){
     
    if(current == NULL) return;

    if(current->isEnd) res.push_back(s);
    
    for(auto t:current->children){

        get_all_words(t.second,res,(s+t.first));

    }

}


vector<string> Trie::pre_search(string s){
 
     auto start = chrono::high_resolution_clock::now();

     TrieNode* current  = root;

     vector<string> res;
     
     for(auto t:s){

           if(current->children.find(t)!=current->children.end())
                      current = current->children[t];
         
           else 
              {
                   cout<<"No matching results are found !!!\n";
                   return res;
                   
             }
     }

    get_all_words(current,res,s);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << res.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";  


    return res;

}



