
#include <iostream>
#include <fstream>

#include <string>
using namespace std;


// Use Map Class as the main funcional class
class Map;

// Use Block Class to insert the Block.
class Block{
    friend Map;

private:
    int Block_Row_Num,Block_Col_Num;
    // Use Array Pointer to represent the Block.
    int *Block_Array;
    int Type;
    int T1[6]={0,1,0,1,1,1}; //Row*Col=2*3
    int L1[6]={1,1,1,0,1,0}; //3*2
    int J1[6]={1,1,0,1,0,1}; //3*2
    int S1[6]={1,1,0,0,1,1}; //2*3
    int I1[4]={1,1,1,1};     //4*1
    int T2[6]={0,1,1,1,0,1}; //3*2
    int L2[6]={1,0,0,1,1,1}; //2*3
    int J2[6]={1,1,1,1,0,0}; //2*3
    int S2[6]={0,1,1,1,1,0}; //3*2
    int I2[4]={1,1,1,1};     //1*4
    int T3[6]={1,1,1,0,1,0}; //2*3
    int L3[6]={0,1,0,1,1,1}; //3*2
    int J3[6]={1,0,1,0,1,1}; //3*2
    int Z1[6]={0,1,1,1,1,0}; //2*3
    int O[4]={1,1,1,1};      //2*2
    int T4[6]={1,0,1,1,1,0}; //3*2
    int L4[6]={1,1,1,0,0,1}; //2*3
    int J4[6]={0,0,1,1,1,1}; //2*3
    int Z2[6]={1,0,1,1,0,1}; //3*2
    
public:
    
    // Constructor
    Block():Block_Row_Num(0),Block_Col_Num(0),Block_Array(nullptr){}
    
    Block(int Row_Num,int Col_Num,int *Block_type):
    Block_Row_Num(Row_Num),Block_Col_Num(Col_Num){
        Block_Array=Block_type;
    }
    
    // To return the Block with Rows, Columns, and the Block_Array
    Block Insert_Block(string Block_Type){
        if (Block_Type=="T1")  return Block(2,3,T1);
        else if (Block_Type=="L1") return Block(3,2,L1);
        else if (Block_Type=="J1") return Block(3,2,J1);
        else if (Block_Type=="S1") return Block(2,3,S1);
        else if (Block_Type=="I1") return Block(4,1,I1);
        else if (Block_Type=="T2") return Block(3,2,T2);
        else if (Block_Type=="L2") return Block(2,3,L2);
        else if (Block_Type=="J2") return Block(2,3,J2);
        else if (Block_Type=="S2") return Block(3,2,S2);
        else if (Block_Type=="I2") return Block(1,4,I2);
        else if (Block_Type=="T3") return Block(2,3,T3);
        else if (Block_Type=="L3") return Block(3,2,L3);
        else if (Block_Type=="J3") return Block(3,2,J3);
        else if (Block_Type=="Z1") return Block(2,3,Z1);
        else if (Block_Type=="O")  return Block(2,2,O);
        else if (Block_Type=="T4") return Block(3,2,T4);
        else if (Block_Type=="L4") return Block(2,3,L4);
        else if (Block_Type=="J4") return Block(2,3,J4);
        else if (Block_Type=="Z2") return Block(3,2,Z2);
        else return Block();
    }
};


class Map{

private:
    int Map_Row_Num,Map_Col_Num;
    int Block_Start_Position;
    int *Map_Array;
    int *Temp_Array;
    Block S;
    
public:
    // constructor | 建構子 | Build the Map base in Array Pointer
    Map():Map_Row_Num(0),Map_Col_Num(0){}
    
    Map(int Rows,int Columns):Map_Row_Num(Rows),Map_Col_Num(Columns){
        // Creating Map matrix with (Rows+5)*(Columns)
        // 在 Map 中 Row=0 的元素設為 1，供後續方塊掉落來判斷是否撞到。
        // 在 Map 中 存放輸出矩陣上多存四列，供方塊掉落前暫存，並提供後續遊戲結束的判斷。（Condition 2）
        int Size= (Map_Row_Num+5)*Map_Col_Num;
        Map_Array = new int[Size]{0};
        for (int i=0;i<Map_Col_Num;i++){
            Map_Array[i]=1;
        }
    }
    
    ~Map(){
        delete []Map_Array;
        delete []Temp_Array;
    }
    // To print the map from the top
    void Print_Map();
    
    // Used to input the Block type and Re-Arrange the map array.
    void Re_Arrange(string Block_Type,int S);
    
    // To determine where the Block would stop
    bool Hit_Wall(int Current_Row);
    
    // To check whether the row is full.
    // If so, move the elements.
    void Row_Filled(int Current_Row);
    
    // To check whether there is still elements in the temperate storages after shifting.
    bool Storage_Left();
};


void Map::Print_Map(){
    
    for (int i=Map_Row_Num;i>0;i--){
        for (int j=0;j<Map_Col_Num;j++){
            cout << Map_Array[j+i*Map_Col_Num];
        }
        cout<<endl;
    }
}

void Map::Re_Arrange(string Block_Type,int Start_Position){

    // Input the Starting Position and the Block as S
    Block_Start_Position=Start_Position;
    S=S.Insert_Block(Block_Type);
    int Current_Row;
    int Current_Col=Block_Start_Position-1;
    
    // Current 從 Map 上方一格開始 Ex：Row_Number=2, Current=3。
    for(Current_Row=Map_Row_Num+1;Current_Row>0;Current_Row--){
        
        // If not hiting the row, move one current row down.
        if(Hit_Wall(Current_Row)==true){
            // If so, change the element to 1 in the map.
            for(int i=Current_Row;i<Current_Row+S.Block_Row_Num;i++){
                for(int j=Current_Col;j<Current_Col+S.Block_Col_Num;j++){            Map_Array[i*Map_Col_Num+j]+=S.Block_Array[j-Current_Col+(i-Current_Row)*S.Block_Col_Num];
                }
            }
            // Check whether it is full or not.
            Row_Filled(Current_Row);
            break;
        }
    }
}

bool Map::Storage_Left(){

    for (int i=Map_Row_Num+4;i>Map_Row_Num;i--){
        for (int j=0;j<Map_Col_Num;j++){
            if(Map_Array[j+i*Map_Col_Num]!=0){
                return true;
            };
        }
    }
    return false;
}

bool Map::Hit_Wall(int Current_Row){
    
    // Assign a temperate array pointer to determine hitting the wall.
    int Current_Col=Block_Start_Position-1;
    Temp_Array=new int[S.Block_Col_Num*S.Block_Row_Num];
    for(int i=0;i<S.Block_Col_Num*S.Block_Row_Num;i++){
        Temp_Array[i]=0;
    }
    
    // Temperate Array 會紀錄所有Block 遇到落下那一格加起來的量值。
    for(int i=Current_Row;i<Current_Row+S.Block_Row_Num;i++){
        for(int j=Current_Col;j<Current_Col+S.Block_Col_Num;j++){
            Temp_Array[j-Current_Col+(i-Current_Row)*S.Block_Col_Num]=
                Map_Array[(i-1)*Map_Col_Num+j]+
                S.Block_Array[j-Current_Col+(i-Current_Row)*S.Block_Col_Num];
            }
    }
    // 若 Temperate Array 量值為2，則表示撞到牆，即方塊或最下面一列。（ Block ==1 && Map ==1 )
    for (int i=0;i<S.Block_Row_Num*S.Block_Col_Num;i++){
        if(Temp_Array[i]==2)return true;
    }
    return false;
}


void Map::Row_Filled(int Current_Row){
    
    // 從上而下確認是否 Row 的所有元素是滿的。
    for ( int i=Current_Row+3;i>=Current_Row;i--){
        int Count=0;
        for (int j=0;j<Map_Col_Num;j++){
            Count+=Map_Array[i*Map_Col_Num+j];
        }
        
        // 當 Row 滿時，將所有 Row 以上的格子往下移一格。
        if(Count==Map_Col_Num){
            
            for(int k=i;k<=Map_Row_Num+3;k++){
                for(int r=0;r<Map_Col_Num;r++){
                    Map_Array[k*Map_Col_Num+r]=Map_Array[(k+1)*Map_Col_Num+r];
                }
            }
            for(int r=0;r<Map_Col_Num;r++){
                Map_Array[(Map_Row_Num+4)*Map_Col_Num+r]=0;
            }
        }
    }

}


int main(){
    
    int Rows,Columns,Start_Position;
    string Block_Type;
    
    // ofstream fout;
    
    
    // Creating the Tetris
    cin >> Rows >> Columns;
    Map Tetris(Rows,Columns);
    
    // Input the block and starting position until
    // (1): "End" to print the map.
    // (2): There are still blocks in temperate storages uppon the map after shifting.
    
    while (cin >> Block_Type){
        if(Block_Type=="End"){
            // Condition 1
            Tetris.Print_Map();
            break;
        }
        else{
            // Condition 2
            cin >> Start_Position;
            Tetris.Re_Arrange(Block_Type,Start_Position);
            if(Tetris.Storage_Left()==true){
                Tetris.Print_Map();
                break;
            }
        }
    }
    return 0;
}
