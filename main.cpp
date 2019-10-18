
#include <iostream>
#include <string>

using namespace std;

class Base_Map {
    
private:
    int row_matrix,col_matrix; // the size of the map to be outputed
    int start_position;   //the starting position of the block
    int type;  // the block type
    int **map; // 2D array matrix
    int block_matrix[4][4]; // store the block
    int T[19][4][4]={
        {0, 1, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, // T[0]=T1
        
        {1, 1, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0,
            0, 0, 0, 0},// T[1]=L1
        
        {1, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0}, //T[2]=J1
        
        {1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[3]=S1
        
        {1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0}, //T[4]=I1
        
        {0, 1, 0, 0,
            1, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0}, //T[5]=T2
        
        {1, 0, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[6]=L2
        
        {1, 1, 1, 0,
            1, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[7]=J2
        
        {0, 1, 0, 0,
            1, 1, 0, 0,
            1, 0, 0, 0,
            0, 0, 0, 0}, //T[8]=S2
        
        {1, 1, 1, 1,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[9]=I2
        
        {1, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[10]=T3
        
        {0, 1, 0, 0,
            0, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0}, //T[11]=L3
        
        {1, 0, 0, 0,
            1, 0, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0}, //T[12]=J3
        
        {0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[13]=Z1
        
        {1, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[14]=O
        
        {1, 0, 0, 0,
            1, 1, 0, 0,
            1, 0, 0, 0,
            0, 0, 0, 0}, //T[15]=T4
        
        {1, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[16]=L4
        
        {0, 0, 1, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0}, //T[17]=J4
        
        {1, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0} //T[18]=Z2
    };
    
public:
    
    // constructor | 建構子 | Build the Base map matrix
    Base_Map ():row_matrix(0),col_matrix(0){}
    
    Base_Map (int Rows,int Columns):row_matrix(Rows),col_matrix(Columns){
        // Creating Map matrix with (Rows+5)*(Columns+3)
        // 在 Map 中 Row=0 的元素設為 1，供後續方塊掉落來判斷是否撞到。
        // 在 Map 中 存放輸出矩陣上多存四列，供方塊掉落前暫存，並提供後續遊戲結束的判斷。（Condition 2）
        map = new int*[row_matrix+5];
        for (int i=0;i<row_matrix+5;i++){
            
            // 將 Columns 多加三行，主要供方塊掉落時為 0 的格子能有相對應的量值。
            // 但由於皆無非法測資，故此三行的所有量值除了 Rows=0 應皆為 0
            map[i]=new int[col_matrix+3];
            for(int j=0;j<col_matrix+3;j++){
                map[i][j]=0;
            }
        }
        for(int k=0;k<col_matrix+3;k++){
            map[0][k]=1;
        }
    }
    // destructor | 解構子
    ~Base_Map(){
        for (int i = 0; i < row_matrix+5; i++){
            delete[]map[i]; // Delete Columns
        }
        delete[]map; // Delete Rows
    }
    
    
    // Print every element in map in order | 由上而下依序印出
    void Game_over() {
        for(int i= row_matrix;i>0;i--){
            for (int j=0;j<col_matrix;j++){
                cout<< map[i][j];
            }
            cout<<endl;
        }
    }
    
    // Load the input block and transform it from string to int
    // Input the block_matrix and re-arranging the map.
    void InsertBlock(string Block_Type,int start){
        
        start_position=start;
        if (Block_Type=="T1") type=0;
        else if (Block_Type=="L1")type= 1;
        else if (Block_Type=="J1")type= 2;
        else if (Block_Type=="S1")type= 3;
        else if (Block_Type=="I1")type= 4;
        else if (Block_Type=="T2")type= 5;
        else if (Block_Type=="L2")type= 6;
        else if (Block_Type=="J2")type= 7;
        else if (Block_Type=="S2")type= 8;
        else if (Block_Type=="I2")type= 9;
        else if (Block_Type=="T3")type= 10;
        else if (Block_Type=="L3")type= 11;
        else if (Block_Type=="J3")type= 12;
        else if (Block_Type=="Z1")type= 13;
        else if (Block_Type=="O") type= 14;
        else if (Block_Type=="T4")type= 15;
        else if (Block_Type=="L4")type= 16;
        else if (Block_Type=="J4")type= 17;
        else if (Block_Type=="Z2")type= 18;
        Change_Block_Matrix(T[type]);
        this->Rearranging();
    }
    // Transform from 3D matrix to 2D matrix
    void Change_Block_Matrix (int block[4][4]){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                block_matrix[i][j]=block[i][j];
            }
        }
    }
    
    // Re-Arranging the map
    void Rearranging (){
        // current_row 是 block 最底層的位置，從row_matrix開始往下掉，但其16格觸底前，先印到 map 上
        for (int current_row=row_matrix+1;current_row>0;current_row--){
            if (hit_the_block(current_row)==true){
                for( int s=current_row;s<current_row+4;s++){
                    for(int j=start_position-1;j<start_position+3;j++){
                        map[s][j]+= block_matrix[s-current_row][j-start_position+1];
                    }
                }
                Row_filled(current_row); //判斷是否填滿，並進行平移
                break;
            }
        }
    }
    
    // 判斷16格是否撞到方格
    bool hit_the_block(int cur_row) {
        
        for(int i=cur_row;i<cur_row+4;i++){
            for (int j=start_position-1;j<start_position+3;j++){
                // 當下一 row 的 map element 和 block 總和為二，表示不能再降落了。
                if(map[i-1][j]+block_matrix[i-cur_row][j-start_position+1]==2) return true;
            }
        }
        return false;
    }
    
    //判斷同一列是否已經達到可消除的狀態
    void Row_filled (int current_row){
        
        for(int i=current_row+3;i>=current_row;i--){    // current=1, i=4
            int sum=0;
            for(int j=0;j<col_matrix;j++){      // 0~col_matrix
                sum+=map[i][j];
                if(sum==col_matrix){
                    //copy the elements
                    for(int r=i;r<row_matrix+4;r++){
                        for(int k=0;k<col_matrix;k++){
                            map[r][k]=map[r+1][k];
                        }
                    }
                    
                }
            }
        }
    }
    // To determing whether there are still blocks left in the temperate storages.
    // If returning TRUE, Game is over.
    bool temp_storage_check(){
        for(int i=row_matrix+1;i<row_matrix+5;i++){
            for (int j=0;j<col_matrix;j++){
                if(map[i][j]==1)return true;
            }
        }
        return false;
    }
};










int main() {
    
    int Rows,Columns,Start_Position;
    string Block_Type;
    
    // Creating the Base_Map matrix
    cin >> Rows >> Columns;
    Base_Map Tetris(Rows,Columns);
    
    // Input the block and starting position until
    // (1): "End" to print the map.
    // (2): There are still blocks in temperate storages uppon the map after erasing.
    
    while (cin >> Block_Type){
        if(Block_Type=="End"){
            // Condition 1
            Tetris.Game_over();
            break;
        }
        else{
            // Condition 2
            cin >> Start_Position;
            Tetris.InsertBlock(Block_Type,Start_Position);
            if(Tetris.temp_storage_check()){
                Tetris.Game_over();
                break;
            }
        }
    }
    return 0;
}
