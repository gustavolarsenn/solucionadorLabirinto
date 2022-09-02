class Sistema
{
    public:
        string nome;
   
    public: 
         Sistema(string n)
         {
            this->nome = n;
         }


        int lerTamColuna()
        {
            ifstream arquivo;
            arquivo.open("maze.txt");
            int column_length = 0;
            string str;

            if(arquivo.is_open())
            {
                getline(arquivo, str);
                column_length = str.length();

            } 
            else 
            {
                cout << "Erro ao abrir o arquivo!";
            }
            arquivo.close();
            return column_length;
        }

        int lerTamLinha()
        {
            ifstream arquivo;
            arquivo.open("maze.txt");
            int row_length = 0;
            string str;

            if(arquivo.is_open())
            {
                while(getline(arquivo, str))
                {
                    row_length++;
                }
            } 
            else
            {
                cout << "Erro ao abrir o arquivo!";
            }
            
            arquivo.close();
            return row_length;
        }

        vector<vector<char>> mapear(int r, int c)
        {

            ifstream arquivo;
            arquivo.open("maze.txt");
            vector<vector<char>> mapa;
            int i = 0, j;
            string str;

            if(arquivo.is_open())
            {

                while(getline(arquivo, str))
                {
                    vector<char> linha;
                    for(i = 0; i < r; i++)
                    {
                        for(j = 0; j < c; j++)
                        {
                            linha.push_back(str[j]);
                        }
                    }
                    mapa.push_back(linha);
                }

            }
            else
            {
                cout << "Erro ao abrir o arquivo!";
            }

            arquivo.close();
  
            return mapa;
        }

        bool podeVisitar(char posicao)
        {
            if(posicao == '#'){
                return false;
            } 

            return true;   
        }

        void caminhoCorreto()
        {
            set<pair<int ,int>> pode;
            int i, j, r = this->lerTamLinha();
            int c = this->lerTamColuna();
            vector<vector<char>> maze = mapear(r, c);
            

            for(i = 0; i < r; i++)
            {
                for(j = 0; j < c; j++)
                {
                    if(this->podeVisitar(maze[i][j]))
                    {
                        pode.insert({i, j});
                    }
                }
            }

            for(auto x : pode)
            {
                    cout << "[" << x.first << "]" << " [" << x.second << "]" << endl;      
            }
            

        }


};
