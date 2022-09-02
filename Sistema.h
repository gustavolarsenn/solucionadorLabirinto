class Sistema
{
    public:
        string nome;
        int row_length;
        int column_length;
   
    public: 
         Sistema(string n, int r, int c)
         {
            this->nome = n;
            this->row_length = r;
            this->column_length = c;
         }


        int lerTamColuna()
        {
            ifstream arquivo;
            arquivo.open("maze.txt");
            this->column_length = 0;
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
            this->row_length = 0;
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

        vector<vector<char>> mapear()
        {
            int c = this->column_length;
            int r = this->row_length;
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

        vector<pair<int, int>> acharEntrada()
        {
            int r = this->row_length;
            int c = this->column_length;
            int i, j;
            vector<vector<char>> maze = mapear();
            vector<pair<int, int>> entrada;


            for(i = 0; i < r; i++)
            {
                for(j = 0; j < c; j++)
                {
                    if(maze[i][j] == 'S')
                    {
                        entrada.push_back({i, j});
                        break;
                    }
                }
            }

            
            return entrada;
        }

        vector<pair<int, int>> acharSaida()
        {
            int r = this->row_length;
            int c = this->column_length;
            int i, j;
            vector<vector<char>> maze = mapear();
            vector<pair<int, int>> saida;


            for(i = 0; i < r; i++)
            {
                for(j = 0; j < c; j++)
                {
                    if(maze[i][j] == 'E')
                    {
                        saida.push_back({i, j});
                        break;
                    }
                }
            }

            return saida;
        }

        void caminhoCorreto()
        {
            vector<pair<int, int>> saida = acharSaida();
            vector<pair<int, int>> entrada = acharEntrada();
            vector<vector<char>> maze = mapear();
            vector<vector<int>> caminhoCerto;
            vector<pair<int, int>> visitado;
            vector<vector<char>> mazeCopy = mapear();

            int i, j, sr, sc, er, ec, r = this->row_length;
            int c = this->column_length;

            for(auto x : saida)
            {
                sr = x.first;
                sc = x.second;
                break;
            }
            for(auto x : entrada)
            {
                i = x.first;
                j = x.second;
                break;
            }

            string currentMov;
            while(achouFinal(i, j, mazeCopy))
            {
                
                if(podeVisitar(i+1, j, mazeCopy) && naoVisitou(i+1, j, visitado))
                {
                    i++;
                    visitado.push_back({i, j});
                    currentMov = "i++";
                }

                else if(podeVisitar(i, j+1, mazeCopy) && naoVisitou(i, j+1, visitado))
                {
                    j++;
                    visitado.push_back({i, j});
                    currentMov = "j++";
                }

                else if(podeVisitar(i-1, j, mazeCopy) && naoVisitou(i-1, j, visitado))
                {
                    i--;
                    visitado.push_back({i, j});
                    currentMov = "i--";
                }

                else if(podeVisitar(i, j-1, mazeCopy) && naoVisitou(i, j-1, visitado))
                {
                    j--;
                    visitado.push_back({i, j});
                    currentMov = "j--";
                } 
                else {
                    if(currentMov == "j--")
                    {
                        mazeCopy[i][j] = '#';
                        j++;
                        currentMov = "j++";
                        visitado.pop_back();
                    } else if(currentMov == "j++")
                    {
                        mazeCopy[i][j] = '#';
                        j--;
                        currentMov = "j--";
                        visitado.pop_back();
                    } else if(currentMov == "i--")
                    {
                        mazeCopy[i][j] = '#';
                        i++;
                        currentMov = "i++";
                        visitado.pop_back();
                    } else if(currentMov == "i++")
                    {
                        mazeCopy[i][j] = '#';
                        i--;
                        currentMov = "i--";
                        visitado.pop_back();
                    }
                }
                
            }
            
            mapaInicial(r, c, maze);

            mapaFinal(r, c, mazeCopy, visitado);

            mostrarCoordenadas(visitado);    

        }

        bool podeVisitar(int i, int j, vector<vector<char>> maze){

            if(maze[i][j] != '#') // Descer
            {
                return true;
            }

            return false;

        }

        bool naoVisitou(int i, int j, vector<pair<int, int>> posicao)
        {
            for(auto x : posicao)
            {
                if(x.first == i && x.second == j)
                {
                    return false;
                }
            }
            return true;
        }

        bool achouFinal(int i, int j, vector<vector<char>>maze)
        {
            if(maze[i][j] != 'E')
            {
                return true;
            }

            return false;
        }

        void mapaInicial(int r, int c, vector<vector<char>> maze)
        {
            cout << endl << "**** Mapa Inicial ****" << endl;

            for(int i = 0; i < r; i++)
            {
                cout << endl;
                for(int j = 0; j < c; j++)
                {
                    cout << maze[i][j];
                }
            }

            cout << endl;
        }

        void mapaFinal(int r, int c, vector<vector<char>> maze, vector<pair<int, int>> visitado)
        {

            cout << endl << "**** Mapa Final ****" << endl;

            for(auto x : visitado)
            {
                for(int i = 0; i < r; i++){
                    for(int j = 0; j < c; j++){
                        if(i == x.first && j == x.second){
                            maze[i][j] = '*';
                        } else if(maze[i][j] == '.' && maze[i][j] == '.') {
                            maze[i][j] = '#';
                        }
                    }
                }
            }

            for(int i = 0; i < r; i++)
            {
                cout << endl;
                for(int j = 0; j < c; j++)
                {
                    cout << maze[i][j];
                }
            }
        }

        void mostrarCoordenadas(vector<pair<int, int>> visitado)
        {
            cout << endl;
            for(auto x : visitado)
            {
                cout << "[" << x.first << ", " << x.second << "] " << endl;
            }
        }
};
