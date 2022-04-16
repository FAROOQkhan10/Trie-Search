#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    bool isEnd;

    TrieNode()
    {
        isEnd = false;
    }
};

class Trie
{
public:
    TrieNode *root;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(string str);
    TrieNode* exact_search(string str);
    vector<string> pre_search(string str);
    
};

void Trie::insert(string str)
{
    TrieNode *current = root;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            current->children.insert(make_pair(ch, new TrieNode()));
            current = current->children[ch];
        }
    }

    current->isEnd = true;
}

TrieNode* Trie::exact_search(string str)
{
    TrieNode *current = root;

    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {   
            return NULL;
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\n"
         << current->isEnd << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return current->isEnd ? current : NULL;
}

void get_words_dfs(TrieNode *current, string pre, vector<string> &results)
{
    if (current == NULL)
    {
        return;
    }
    if (current->isEnd)
    {
        results.push_back(pre);
    }

    for (auto i : current->children)
    {
        get_words_dfs(i.second, (pre + i.first), results);
    }
}

vector<string> Trie::pre_search(string str)
{
    auto start = chrono::high_resolution_clock::now();

    TrieNode *current = root;
    vector<string> res;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {   cout<<"No matching results are found \n";
            return res;
        }
    }

    get_words_dfs(current, str, res);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << res.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return res;
}

