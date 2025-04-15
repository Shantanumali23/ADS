#include<iostream>
using namespace std;

#define TEMP 9999999
#define V 5

class graph{
    public:
    int arr[V][V];

    void input(){
        cout<<"Enter The Distance between Departments(5*5): "<<endl;
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                cin>>arr[i][j];
            }
        }
    }

    void display(){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void prims(){
        bool visited[V];
        int no_edge=0;
        int totalCost=0;
        int row,col;
        visited[0]=true;

        while(no_edge < V-1){
            int min=TEMP;
            row=0;
            col=0;
            for(int i=0;i<V;i++){
                if(visited[i]){
                    for(int j=0;j<V;j++){
                        if(!visited[j] && arr[i][j]){
                            if(min > arr[i][j]){
                                min=arr[i][j];
                                row=i;
                                col=j;
                            }
                        }
                    }
                }
            }
            cout<<row<<" - "<<col<<" : "<<arr[row][col]<<endl;
            visited[col]=true;
            totalCost=totalCost+arr[row][col];
            no_edge++;
        }
        cout<<"Total Distance: "<<totalCost;
    }
};

int main(){
    graph g;
    g.input();
    cout<<"Prims Algorithm: "<<endl;
    g.prims();
    return 0;
}