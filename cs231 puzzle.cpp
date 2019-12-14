	#include <iostream>
	using namespace::std;
	class puzzle{
		struct node{
			int arr[3][3];
			node *parent;
			int cost;
			int level;
			node **child;
			node()
			{
				child=new node *[4];
				level=0;
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
			node *q;
			list *right;
			list()
			{
				right=NULL;
				q=NULL;
			}
		};
		list *head;
		list *tail;
		queue *front;
		queue *rear;
		int final[3][3]=
		{
					{0,1,2},
					{3,4,5},
					{6,7,8}
				      };
		public:
			puzzle()
			{
				head=NULL;
				tail=NULL;
				front=NULL;
				rear=NULL;
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
				temp->level=moves;
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
				//this queue is a priority queue that accepts node with minimum cost only
				queue *temp2=new queue;
				temp2->q=temp;
			
				
				if(front==NULL)
				{
					front=temp2;
					rear=front;
				}
				else
	         	{
		
	                if(temp2->q->cost<front->q->cost)
	                {
	                	front=temp2;
					}
				}
			
			}
			void enqueue_checklist(node *ptr)
			{
				list *temp=new list;
				temp->q=ptr;
			
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
	
						if(array2[i][j]==array1[i][j])
						{
							is_equal++;
						}
					}
	
				}
				if(is_equal==9)
				return 1;
				else
				return 0;
		
			}
			int is_present(node *child)
			{
				int is_equal=1;
				list *ptr=head;
				if(head==NULL)
				{
					return 0;
				}
				while(ptr!=NULL)
				{
	              if(compare(child->arr,ptr->q->arr)==1)
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
			void move_left(node *ptr,int array[3][3],int x,int y,int moves,int &flag)
			{
				int temp=0;
				int y1=y-1;
				if(move_check(x,y1))
				{
					temp=array[x][y1];
					array[x][y1]=0;
					array[x][y]=temp;
		            node *temp1=new node;
	                temp1=create_node(array,moves);
	                temp1->parent=ptr;
	                ptr->child[0]=temp1;
					if(is_present(temp1)==0)
					{
					enqueue(temp1);
					flag=1;
				}
				}
			}
			void move_right(node *ptr,int array[3][3],int x, int y, int moves, int &flag)
			{
			    int temp=0;
				int y1=y+1;
				if(move_check(x,y1))
				{
					temp=array[x][y1];
					array[x][y1]=0;
					array[x][y]=temp;
					node *temp1=new node;
					temp1=create_node(array,moves);
					temp1->parent=ptr;
					ptr->child[1]=temp1;
			
					if(!is_present(temp1))
					{
					
					enqueue(temp1);
					flag=1;
				}
				}
			}
			void move_up(node *ptr,int array[3][3],int x, int y,int moves, int &flag)
			{
				int temp=0;
				int x1=x-1;
				if(move_check(x1,y))
				{
					temp=array[x1][y];
					array[x1][y]=0;
					array[x][y]=temp;
				
				node *temp1=new node;
					temp1=create_node(array,moves);
					temp1->parent=ptr;
					ptr->child[2]=temp1;
					if(!is_present(temp1))
					{
					enqueue(temp1);
					flag=1;
				}
				}
			}
			void move_down(node *ptr,int array[3][3],int x,int y,int moves, int &flag)
			{
				int temp=0;
				int x1=x+1;
				if(move_check(x1,y))
				{
					temp=array[x1][y];
					array[x1][y]=0;
					array[x][y]=temp;
					node *temp1=new node;
					temp1=create_node(array,moves);
					temp1->parent=ptr;
					ptr->child[3]=temp1;
					if(!is_present(temp1))
					{
					
						enqueue(temp1);
						flag=1;
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
			void solution(int array[3][3])
			{
				int moves=0;
	            int flag=0;
				node *temp=new node;
				temp=create_node(array,moves);
				enqueue(temp);
				int x=0;
				int y=0;
				node *ptr=NULL;
				while(1)
				{
				    ptr=dequeue();
				    flag=0;
				    moves++;
				    int arr1[3][3];
				    int arr2[3][3];
				    int arr3[3][3];
				    int arr4[3][3];
				    copy_arr(arr1, ptr->arr); 
				    copy_arr(arr2, ptr->arr); 
				    copy_arr(arr3, ptr->arr); 
				    copy_arr(arr4, ptr->arr); 
	                if(is_present(ptr)==0)
	                enqueue_checklist(ptr);
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
				move_right(ptr,arr1,x,y,moves,flag);
				move_left(ptr,arr2,x,y,moves,flag);
				move_up(ptr,arr3,x,y,moves,flag);
				move_down(ptr,arr4,x,y,moves,flag);
	            if(flag==0)
	            {
	            	choose_func(ptr);
	            	break;
				}
				         cout<<"Moves: "<<moves<<endl;
	           }
			}
			choose_func(node *ptr)
			{
				node *ptr2=ptr->parent;
				for(int i=0;i<3;i++)
				{
				
					if(ptr2->child[i]!=ptr&&ptr2->child[i]!=NULL)
					{
						enqueue(ptr2->child[i]);
					}
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
	}
