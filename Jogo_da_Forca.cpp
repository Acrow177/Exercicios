#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

class JogoDaForca
{
private:
    string palavra_secreta;
    map<char, bool> CHUTOU;
    vector<char> chutes_errados;

    bool letra_existe(char chute)
    {
        for (char letra : palavra_secreta)
        {
            if (chute == letra)
            {
                return true;
            }
        }
        return false;
    }

    bool nao_acertou()
    {
        for (char letra : palavra_secreta)
        {
            if (!CHUTOU[letra])
            {
                return true;
            }
        }
        return false;
    }

    bool nao_enforcou()
    {
        return chutes_errados.size() < 8;
    }

    void imprime_cabecalho()
    {
        cout << "**********************'\n";
        cout << "****Jogo da Forca*****'\n";
        cout << "**********************'\n";
        cout << '/n';
    }

    void imprime_erros()
    {
        cout << "Chutes errados: ";
        for (char letra : chutes_errados)
        {
            cout << letra << " ";
        }
        cout << '/n';
    }

    void imprime_palavra()
    {
        for (char letra : palavra_secreta)
        {
            if (CHUTOU[letra])
            {
                cout << letra << " ";
            }
            else
            {
                cout << "_ ";
            }
        }
        cout << '/n';
    }

    void desenharForca()
    {
        vector<string> forca = {
            " +---+\n |   |\n     |\n     |\n     |\n     |\n=======",
            " +---+\n |   |\n O   |\n     |\n     |\n     |\n=======",
            " +---+\n |   |\n O   |\n |   |\n     |\n     |\n=======",
            " +---+\n |   |\n O   |\n/|   |\n     |\n     |\n=======",
            " +---+\n |   |\n O   |\n/|\\  |\n     |\n     |\n=======",
            " +---+\n |   |\n O   |\n/|\\  |\n/    |\n     |\n=======",
            " +---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n     |\n=======",
        };

        int max_tentativas = forca.size();
        int num_tentativas = chutes_errados.size();

        if (num_tentativas < max_tentativas)
        {
            cout << forca[num_tentativas] << '/n';
        }
        else
        {
            cout << " +---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n     |\n=======\n\nVoce perdeu!'\n";
        }
    }

    void chuta()
    {
        char chute;
        cout << "Informe seu chute: ";
        cin >> chute;
        CHUTOU[chute] = true;

        if (letra_existe(chute))
        {
            cout << "Você acertou! Seu chute está na palavra.'\n";
        }
        else
        {
            cout << "Você errou! Seu chute não está na palavra.'\n";
            chutes_errados.push_back(chute);
        }
        cout << '/n';
    }

    vector<string> le_arquivo()
    {
        ifstream arquivo;
        arquivo.open("palavras.txt");

        if (arquivo.is_open()){
        int quantidade_palavras;
        arquivo >> quantidade_palavras;

        vector<string> palavra_do_arquivo;

        for (int i = 0; i < quantidade_palavras; i++)
        {
            string palavra_lida;
            arquivo >> palavra_lida;
            palavra_do_arquivo.push_back(palavra_lida);
        }
        return palavra_do_arquivo;
    } else {
    cout << " Não foi possivel acessar o banco de dados.'\n";
    exit (0);
    }
}

    void sorteia_palavra()
    {
        vector<string> palavras = le_arquivo();

        srand(time(NULL));
        int indice_sorteado = rand() % palavras.size();

        palavra_secreta = palavras[indice_sorteado];
    }

public:
    JogoDaForca()
    {
        imprime_cabecalho();
        sorteia_palavra();
    }

    void jogar()
    {
        while (nao_acertou() && nao_enforcou())
        {
            desenharForca();
            imprime_erros();
            imprime_palavra();
            chuta();
        }

        if (nao_acertou())
        {
            cout << "        *******************************'\n";
            cout << "        **********Fim de jogo!*********'\n";
            cout << "        *Você perdeu! Tente novamente!*'\n";
            cout << "        *******************************'\n";
        }
        else
        {
            cout << "*****************************************************'\n";
            cout << "* Parabéns! Você acertou a palavra secreta " << palavra_secreta << " *'\n";
            cout << "*****************************************************'\n";
        }
    }
};

int main()
{
    JogoDaForca jogo;
    jogo.jogar();
    return 0;
}
