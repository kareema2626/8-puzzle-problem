#include <iostream>
using namespace::std;
class puzzle{
	struct node{
		int arr[3][3];
		node *parent;
		int cost;
		node()
		{
			cost=0;
			arr[3][3]={0};
			parent=NULL;
		}
	};
	struct queue{
		node *q;
		queue *next;
		queue()
		{
			q=NULL;
			next=NULL;
		}
	};
	struct list{
		int mat[3][3];
		list *right;
		list()
		{
			right=NULL;
			mat[3][3]={0};
		}
	};
	list *head;
	list *tail;
	queue *front;
	queue *rear;
	int final[3][3]=
	{
				{1,2,3},
				{4,5,6},
				{7,8,0}
			      };
	int initial[3][3];
	public:
		puzzle()
		{
			head=NULL;
			tail=NULL;
			front=NULL;
			rear=NULL;
		}
		void get_initial(int arr1[3][3])
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					initial[i][j]=arr1[i][j];
				}
			}
		}
		bool is_goal(int arr1[3][3])
		{
			int diff=0;
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(arr1[i][j]!=final[i][j])
					{
						diff=1;
					}
				}
			}
			if(diff==0)
			{
				return true;
			}
			else
			return false;
		}
		node *create_node(int arr1[3][3],int moves)
		{
			node *temp=new node;
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					temp->arr[i][j]=arr1[i][j];
				}
			}
			int cost1=0;
			//calcultaing cost
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
				    if(temp->arr[i][j]!=final[i][j])
					{
						cost1++;
					}	
				}
			}
			temp->cost=cost1+moves;
			return temp;
		}
		void enqueue(node *temp)
		{
			queue *temp2=new queue;
			temp2->q=temp;
		
		//	cout<<"enqueue 1"<<endl;
			
			if(front==NULL)
			{
				front=temp2;
				rear=front;
			}
			else
			{
//				rear->next=temp2;
//				rear=temp2;
                if(temp2->q->cost<front->q->cost)
                {
                	front=temp2;
				}
			}
		
		}
		void enqueue_checklist(int arr1[3][3])
		{
			list *temp=new list;
			copy_arr(temp->mat,arr1);
			//print_arr(arr1);
			//cout<<"checklist: "<<endl;
			//print_arr(temp->q->arr);
			if(head==NULL)
			{
				head=temp;
				tail=head;
			}
			else
			{
				tail->right=temp;
				tail=temp;
			}
		}
		node *dequeue()
		{
		//	cout<<"dequeue"<<endl;
			queue *ptr=front;
			front=front->next;
			node *ptr2=ptr->q;
			delete ptr;
			return ptr2;
		}
		int compare(int array2[3][3],int array1[3][3])
		{
			int is_equal=0;
			for(int i=0;i<3;i++)
			{
				for (int j=0;j<3;j++)
				{
			       //cout<<array2[i][j]<<"      "<<array1[i][j]<<"   ";

					if(array2[i][j]==array1[i][j])
					{
						is_equal++;
					}
				}
									//cout<<endl;

			}
			if(is_equal==9)
			return 1;
			else
			return 0;
	
		}
		int is_present(int array[3][3])
		{
			int is_equal=1;
			list *ptr=head;
			if(head==NULL)
			{
				return 0;
			}
			while(ptr!=NULL)
			{
			    if(compare(array,ptr->mat)==1)
			    {
			    	return 1;
				}
				ptr=ptr->right;
		    }
			return 0;
		}
		bool move_check(int x, int y)
		{
		      if((x<0||x>2)||(y<0||y>2))
		        return false;
			    else
			    return true;
		}
		void move_left(int array[3][3],int x,int y,int moves)
		{
			int temp=0;
			int y1=y-1;
			if(move_check(x,y1))
			{
			//	cout<<"move left"<<endl;
				
				temp=array[x][y1];
				array[x][y1]=0;
				array[x][y]=temp;
			//	cout<<"In move left funct"<<endl;
			//	print_arr(array);
				if(is_present(array)==0)
				{
									node *temp1=new node;

				temp1=create_node(array,moves);

				enqueue(temp1);
			}
			}
		}
		void move_right(int array[3][3],int x, int y, int moves)
		{
		    int temp=0;
			int y1=y+1;
			if(move_check(x,y1))
			{
			//	cout<<"move right"<<endl;
				temp=array[x][y1];
				array[x][y1]=0;
				array[x][y]=temp;
			
			//	cout<<"In move right funct"<<endl;
			//	print_arr(array);
				if(!is_present(array))
				{
					node *temp1=new node;
				temp1=create_node(array,moves);
				enqueue(temp1);
			}
			}
		}
		void move_up(int array[3][3],int x, int y,int moves)
		{
			int temp=0;
			int x1=x-1;
			if(move_check(x1,y))
			{
			//	cout<<"move up"<<endl;
				temp=array[x1][y];
				array[x1][y]=0;
				array[x][y]=temp;
			
				if(!is_present(array))
				{
					node *temp1=new node;
				temp1=create_node(array,moves);
				enqueue(temp1);
			}
			}
		}
		void move_down(int array[3][3],int x,int y,int moves)
		{
			int temp=0;
			int x1=x+1;
			if(move_check(x1,y))
			{
				temp=array[x1][y];
				array[x1][y]=0;
				array[x][y]=temp;
				
			//	cout<<"In move down funct"<<endl;
			//	print_arr(array);
				if(!is_present(array))
				{
					node *temp1=new node;
				temp1=create_node(array,moves);
					enqueue(temp1);
				}
			}
		}
		void copy_arr(int arr1[3][3],int arr2[3][3])
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					arr1[i][j]=arr2[i][j];
				}
			}
		}
		display2()
		{
			list *ptr=head;
			while(ptr!=NULL)
			{
				print_arr(ptr->mat);
				cout<<endl<<endl;
				ptr=ptr->right;
			}
		}
		void display(int arr[3][3])
		{
	
		}
		void solution(int array[3][3])
		{
						int moves=0;

			node *temp=new node;
			temp=create_node(array,moves);
			enqueue(temp);
			int x=0;
			int y=0;
			node *ptr=NULL;
			while(1)
			{
			    ptr=dequeue();
			    moves++;
			    int arr1[3][3];
			    int arr2[3][3];
			    int arr3[3][3];
			    int arr4[3][3];
			    copy_arr(arr1, ptr->arr); 
			    copy_arr(arr2, ptr->arr); 
			    copy_arr(arr3, ptr->arr); 
			    copy_arr(arr4, ptr->arr); 
                if(is_present(arr1)==0)
                enqueue_checklist(arr1);
				print_arr(ptr->arr);
				cout<<endl;
				cout<<endl;
				if(is_goal(ptr->arr))
                break;
				for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(ptr->arr[i][j]==0)
					{
						x=i;
						y=j;
					}
				}
			}
		//	cout<<i<<"->       "<<"x: "<<x<<"    y:"<<y<<endl;
			move_right(arr1,x,y,moves);
			move_left(arr2,x,y,moves);
			move_up(arr3,x,y,moves);
			move_down(arr4,x,y,moves);
		//	cout<<"before clean"<<endl;	
			//clean_queue();
		//	cout<<"after clean"<<endl;
			         cout<<"Moves: "<<moves<<endl;

         }
		}
		void print_arr(int array[3][3])
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					cout<<"  "<<array[i][j];
				}
				cout<<endl;
			}
		}
};
int main()
{
	puzzle obj;
	int initial[3][3];
	cout<<"Please enter the initial matrix"<<endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>initial[i][j];
		}
		cout<<endl;
	}
	obj.solution(initial);
	cout<<endl<<endl;
	int mat[3][3]=
	{
		{0,2,3},
		{1,4,5},
		{6,7,8}
		
	};
	//cout<<"After"<<endl;
	//if(obj.is_present(initial)==1)
	//cout<<"Present"<<endl;
	//else
	//cout<<"NOT"<<endl;
}
