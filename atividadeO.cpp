#include <iostream>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>
using namespace std;

#define MAX 1000000

int main()
{

    int maiorNum = 0;     //variavel que armazena o numero que produz a maior sequencia
    int maiorSeq = 0; // variavel que armazena o tamanho da maior sequencia
    int *tabHash = new int[MAX];

    auto inicio = std::chrono::high_resolution_clock::now(); //contador iniciado

    for (int i = 0; i < MAX; i++){
        tabHash[i] = 0;
    }

    for (int n = 1; n < MAX; n++)
    { //laço que vai verificar qual o numero que produz a maior sequencia

        int seq = 0;           //variavel auxiliar que conta a quantidade da sequencia produzida pelo numero atual e depois zera
        long long int num = n; //variavel auxiliar que recebe o numero a ser verificado a sequencia

        while (num > 1)
        { //condição de que enquanto o num for maior que um ou não existe a sequencia na tabela Hash, o processo de continuar

            if (num < MAX && tabHash[num] != 0)
            {
                seq = seq + tabHash[num];
                break;
            }
            else if (num % 2 == 0)
            { //se o numero for par ele entra nesse if
                num = num / 2;
                seq++;
            }
            else
            { //se não for par ele entra nesse
                num = (3 * num) + 1;
                seq++;
            }
            
        }

        tabHash[n] = seq;
        
        if (tabHash[n] > maiorSeq)
        { //se o num atual produziu uma sequecia maior que o num anterior, ele entra nesse if e armazena a sequencia e o num como sendo os maiores até ent
            maiorNum = n;
            maiorSeq = tabHash[n];
        }
    }

    auto resultado = std::chrono::high_resolution_clock::now() - inicio;                          //fim do contador
    long long seconds = std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count(); //o tempo é armazenado e será mostrado

    cout << maiorNum << " é o numero que produz a maior sequencia, sendo essa sequencia de " << maiorSeq+1 << " numeros." << endl;
    cout << "O codigo demorou " << seconds << " milissegundo para finalizar" << endl;

    auto myHandle = GetCurrentProcess(); //pega no controle deste processo

    PROCESS_MEMORY_COUNTERS pmc; //para preencher os detalhes de uso de memória do processo

    if (GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc))) // retorna o uso (bytes), se eu for possivel
        cout << "Memoria usada (em bytes): " << pmc.WorkingSetSize << endl;
    else
        cout << "Memoria usada (em bytes): 0" << endl;
}