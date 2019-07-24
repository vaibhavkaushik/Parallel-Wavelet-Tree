#include<bits/stdc++.h>
using namespace std;
struct node
{
    node *left,*right;
    vector<pair<int,int> > v;
};
vector< pair<string,int> > s;
string lelo;
vector<string> word;
void print(vector<pair<int,int> >bit)
{
    for(int i=0;i<bit.size();i++) {
        cout << bit[i].first<<"->"<<bit[i].second<<" ";
    }
    cout << endl;
}
void printlist(node *root)
{
    if(root == NULL) {
        return ;
    }
    print(root->v);
    printlist(root->left);
    printlist(root->right);
    return ;
}
vector<pair<int,int> > bitvector(vector< pair<string,int> > s,int l,int r,int ch)
{
    vector<pair<int,int> > bit;
    if(l == r) {
        for(int i=0;i<s.size();i++)
            bit.push_back(make_pair(ch,s[i].second));
        return bit;
    }
    int m = (l+r)/2;
    for(int i=0;i<s.size();i++) {
        int found = 1;
        for(int j=l;j<=m;j++) {
            if(s[i].first == word[j])
               found = 0;
        }
        bit.push_back(make_pair(found,s[i].second));
    }
    return bit;
}
vector<vector<pair<string,int> > > parallelSplit(vector< pair<string,int> > s,vector<pair<int,int> >bit)
{
    vector<pair<string,int> > s1,s2;
    vector<vector< pair<string,int> > > vs;
    for(int i=0;i<bit.size();i++) {
        if(bit[i].first == 0)
            s1.push_back(s[i]);
        else
            s2.push_back(s[i]);
    }
    vs.push_back(s1);
    vs.push_back(s2);
    return vs;
}
node * rwTree(vector< pair<string,int> > s,int l,int r,int ch)
{
    node *temp = new node();
    if(l == r) {
        temp->left = NULL;
        temp->right = NULL;
        temp->v = bitvector(s,l,r,ch);
        return temp;
    }
    temp->v = bitvector(s,l,r,ch);
 
    vector<vector<pair<string,int> > >vs = parallelSplit(s,temp->v);
    temp->left = rwTree(vs[0],l,(l+r)/2,0);
    temp->right = rwTree(vs[1],(l+r)/2+1,r,1);
    return temp;
}


void mapper()
{
	
 string filesname[]={"file1.txt","file2.txt"};
   int size = (int)(sizeof(filesname)/sizeof(filesname[0]));
   ifstream fp;
   for(int i=0;i<size;i++)
   {
	 fp.open(filesname[i].c_str());
     while(fp >> lelo)
    {
        s.push_back(make_pair(lelo,i+1));

    }
    fp.close();
   }

}

void access_query(int idx,int l,int r,node *root)
{
	map<int,int> uniqueId;
	int m = (l+r)/2;
	if(root->leaf) {
		vector< pair<int,int> >u = root->v;
		//cout << u.size() << endl;
		for(int i=0;i<u.size();i++) {
			if(uniqueId[u[i].second]++ == 0)
			cout << u[i].second << " ";
		}
		return ;
	}
	if(idx >= l && idx <= m) {
		access_query(idx,l,m,root->left);
	}
	else {
		access_query(idx,m+1,r,root->right);
	}
}



int main()
{
   mapper();
   int size = s.size();
    for(int i=0;i<size;i++)
    word.push_back(s[i].first);

    
    //unique words
    sort( word.begin(), word.end() );
    word.erase( unique( word.begin(), word.end() ), word.end() );
    
    
 
    node *root;
    int len = s.size();
 
   
    int l=0,r = word.size();
    root = rwTree(s,l,r-1,0);
    
     int t;
   cout << "enter the number of words u want to enter" << endl;
    cin >> t;
    while(t--) {
	    string sword;
	    cout << "enter the word" << endl;
	    cin >> sword;
	    int idx = -1;
	    for(int i=0;i<word.size();i++) {
	    	if(sword == word[i])
	    	   idx = i;
		}
		if(idx == -1) {
			cout << "Not Found";
		}
		else {
	        access_query(idx,l,r-1,root);
	    }
	    cout << endl;

   // printlist(root);
}
 
