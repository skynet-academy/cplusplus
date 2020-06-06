#include<iostream>
#include<list>

class node
{
private:
    int data;
	node* left;	//To point to left node
	node* right;	//To point to right node
	bool lbit,rbit;	//To check presence of thread
	friend class tree;  //Allowing class tree to access private members of class node
};

class tree
{
private:
	int val;
	node *root,*temp,*p;
	node *dummy;
	bool cr;
    std::list<node*>q;
    std::list<node*> s;
public:
	tree();
	void create();		//To create a BST
	node* get_root();		//getter method for root
	node* insert(node*,node*);	//To insert node in BST
	void display(node*); 		//To display the tree using Threads
	void pushIn(node*);		//To push elements in a list 
	void thread(node*);		//To create threads successor as well as predecessor
	node* next_inorder(node*);	//To get the next inorder node
    ~tree();
    
};

tree :: tree()
{
	root = NULL;
	//Dummy node is created so that there are no dangling pointers
	dummy = new node;
	dummy->data = 9999;
	dummy->left = root;	
	dummy->right = dummy;
	
	cr = false;
}

node* tree :: get_root()
{
	//Getter method for root which is a private member
	return this->root;
}

void tree :: create()
{	
	int total;
	if(cr)
	{
        std::cout<<"\n*******Tree already exists********\n";
		return;
	}
	
	cr = true;
	
	//Accept total number of elements in the tree
    std::cout<<"\nEnter the total number of elements : ";
    std::cin>>total;
				
	for(int i=0;i<total;i++)
	{
        std::cout<<"\nEnter the element : ";
        std::cin>>val;
		temp = new node;
		temp->left = NULL;
		temp->right = NULL;
		temp->lbit = false;
		temp->rbit = false;
		temp->data = val;
		root = insert(root,temp);
	}
	
	//calling thread function to put threads
	thread(root);
}

node* tree :: insert(node *r,node* t)
{
	//places the node according to the BST 
	if(r == NULL)
	{
		r = t;
	}
	else
	{
		if(r->data > t->data)
		{
			r->left = insert(r->left,t);
		}
		else
		{
			r->right = insert(r->right,t);
		}	
	}
	
	return r;
}

void tree :: display(node* r)
{
	if(r == NULL)
	{
        std::cout<<"\n********No Tree present*********\n";
		return;
	}
	node *cur = r;
	while(cur->left != dummy)
			cur = cur->left;
		
    std::cout<<"\nInorder traversal using Threads : ";	
	while(true)
	{
        std::cout<<cur->data<<"\t";
		if(cur->right == dummy)	
			break;
		cur = next_inorder(cur);
	}
    std::cout<<std::endl;
}

node* tree :: next_inorder(node *r)
{
    //sends the next inorder node
	if(r->rbit)
		return r->right;
	
	r = r->right;
	while(!r->lbit)
	{
		r = r->left;
	}	
	return r;
}

void tree :: pushIn(node *r)
{
    //Pushing the nodes in list in inorder
	if(r==NULL || r == dummy)
		return;
	else
	{
		pushIn(r->left);
		q.push_back(r);
		pushIn(r->right);
	}
}

void tree :: thread(node *r)
{
	//pushing nodes in the list in inorder
    pushIn(r);
    
    //stacking the elements of the list for predecessor threads
	while(!q.empty())
	{
		s.push_front(q.front());
		q.pop_front();
	}
    
    //pushing nodes in the list in inorder for successor threads
	pushIn(r);
	
    node* cur;      //Node pointer to traverse the list to put threads
    bool check = false; //Flag to check whether all the threads are linked
	
    //Threads to successor	
	while(!check)
	{
		cur = q.front();
		if(q.empty())
			check = true;
		else
		{
			q.pop_front();
			if(cur->right == NULL)
			{	
				if(q.empty())
				{
					cur->right = dummy;
				}	
				else
				{	
					cur->right = q.front();
					cur->rbit = true;
				}
			}
		}

	}

    //Threads to predecessor
	check = false;
	
	while(!check)
	{
		cur = s.front();
		if(s.empty())
			check = true;
		else
		{
			s.pop_front();
			if(cur->left == NULL)
			{	
				if(s.empty())
				{
					cur->left = dummy;
				}	
				else
				{	
					cur->left = s.front();
					cur->lbit = true;
				}
			}
		}

	}
	
}

tree :: ~tree()
{
    delete root;
}


int main()
{
	tree t; //Object of class tree is created
	int ch; //variable for user choice
	
    std::cout<<"\n\t|| PORGRAM TO CONVERT BST TO TBT ||\n";
	do
	{
        std::cout<<"\n1.Create Tree";
        std::cout<<"\n2.Display";
        std::cout<<"\n3.Exit";
        std::cout<<"\n>>";
        std::cin>>ch;
		
		switch(ch)
		{
			case 1:
				t.create();     //Create the BST
				break;
			case 2:
				t.display(t.get_root());    //Display Threaded Binary Tree [Inorder]
				break;
			case 3:
                std::cout<<"\n********Exit*********\n";
				break;
			default:
                std::cout<<"\nInvalid Choice";
				break;
		}
		
	}while(ch!=3);
	return 0;
}
