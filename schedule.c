#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define max_schedule 100

int space;
int newStuff[6];
int storeSchedules[max_schedule][6];
char names[max_schedule][100];
char newName[100];

void clearBuffer() {
    // Fun��o que realiza a limpeza do buffer.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int lookUpId(int code) {
    // Fun��o que procura onde o agendamento est� indexado, retorna 'i' como posi��o do index e -1 caso n�o encontre um c�digo equivalente ao fornecido.
    int i;
    for (i = 0; i < space; i++) {
        if (code == storeSchedules[i][0]) {
            return i;
        }
    }
    printf("|Codigo desconhecido\n"
    "|---------------------------------\n");
    return -1;
}

int scheduleCheck() {
    // Fun��o que realiza a busca por agendamentos id�nticos, retorna o index do agendamento igual ou -1 caso n�o encontre.
    int i, j;
    int found = 0;

    if (space > 0) {
        for (i = 0; i < space; i++) {
            found = 0;
            for (j = 1; j < 6; j++) {
                if (storeSchedules[i][j] == newStuff[j]) {
                    found++;
                }
            }
            if (found == 5) {
                return i;
            }
        }
    }
    return -1;
}

int generateCode() {
    //Fun��o que gera um c�digo aleat�rio e �nico com base na soma dos hor�rios e datas fornecidos.
    int random, sum = 0, i, found = 0;
    for (i = 0; i < 6; i++) {
        sum += newStuff[i];
    }
    
    while (1) {
        srand(sum);
        random = rand();
        
        for (i = 0; i < space; i++) {
            if (random == storeSchedules[i][0]){
                found = 1;
                break;
            }
        }
        if (!found){
            return random;
        }
    }           
    return 0;
}

int consulting(int accessType, int index) {
    // Fun��o que exibe os dados de um agendamento com dois tipos de acesso, um que requisita o c�digo do usu�rio e outro que se 
    // baseia no index de um agendamento, fornecido anteriormente.
    int j, found = 0, code = 0;
    
    if (space == 0) {
        printf("|---------------------------------\n"
        "|Sistema vazio!\n"
        "|---------------------------------\n");
    } else {
        if (!accessType) {
           found = index;
        } else {
            printf("|---------------------------------\n"
            "|Informe o codigo: ");
            scanf("%d", &code);
            found = lookUpId(code);
        }
        if (found != -1) {
            printf("|---------------------------------\n"
            "|Nome: %s\n"
            "|Data: %d/%d/%d\n"
            "|Horario: %d:%d\n"
            "|---------------------------------\n", names[found], storeSchedules[found][1], storeSchedules[found][2],
            storeSchedules[found][3], storeSchedules[found][4], storeSchedules[found][5]);
        }
        return 0;
    }
    return 1;
}

void getName(int accessType, int index) {
    // Fun��o que recebe o nome do cliente com dois tipos de acesso, um que apenas guarda o nome numa vari�vel tempor�ria  
    // e outro que o aloca numa vari�vel de armazenamento.
    int i;
    printf("|---------------------------------\n");
    printf("|Digite o nome: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;

    for (i = 0; newName[i] != '\0'; i++) {
        newName[i] = toupper(newName[i]);
    }

    if (accessType) {
        strcpy(names[index], newName);
    }
}

int fetchYear(int year, int currentYear) {
    // Fun��o que recebe o ano do agendamento e verifica se este � valido, retornando a vari�vel "year" 
    // corrigida ou sem altera��es. 
    while (1) {
        if (year < currentYear) {
        printf("|Formato invalido, por favor tente novamente.\n"
        "|---------------------------------\n"
        "|Ano: ");
        scanf("%d", &year);
        } else {
            return year;
        }
    }
    return 1;
}

int fetchMonth(int year, int currentYear, int month, int currentMonth) {
    // Fun��o que recebe o m�s do agendamento e verifica se este � valido, retornando a vari�vel "month" 
    // corrigida ou sem altera��es.
    while (1) {
        if (month > 12 || month < 0 || (year == currentYear && month < currentMonth)) {
        printf("|Formato invalido, por favor tente novamente.\n"
        "|---------------------------------\n"
        "|Mes: ");
        scanf("%d", &month);
        } else {
            return month;
        }
    }
    return 1;
}

int fetchDay(int year, int currentYear, int month, int currentMonth, int day, int currentDay) {
    // Fun��o que recebe o dia do agendamento e verifica se este � valido, dentro dos par�metros de um ano ser bissexto ou o m�s possuir menos que 31 dias,  
    // retornando a vari�vel "day" corrigida ou sem altera��es.
    int maxDay;
    if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2) {
        maxDay = 29;
    } else if (month == 2){
        maxDay = 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    } else {
        maxDay = 31;
    }
    
    while (1) {
        if (day > maxDay || day <= 0 || (year == currentYear && month == currentMonth && day < currentDay)) {
        printf("|Formato invalido, por favor tente novamente.\n"
        "|---------------------------------\n"
        "|Dia: ");
        scanf("%d", &day);
        } else {
            return day;
        }
    }
    return 1;
}

int fetchHour(int year, int currentYear, int month, int currentMonth, int day, int currentDay, int hour, int currentHour) {
    // Fun��o que recebe a hora do agendamento e verifica se esta � valida, retornando a vari�vel "hour" 
    // corrigida ou sem altera��es.
    while (1) {
        if (hour > 23 || hour < 0 || (year == currentYear && month == currentMonth && day == currentDay && hour < currentHour)) {
        printf("|Formato invalido, por favor tente novamente.\n"
        "|---------------------------------\n"
        "|Hora: ");
        scanf("%d", &hour);
        } else {
            return hour;
        }
    }
    return 1;
}

int fetchMin(int year, int currentYear, int month, int currentMonth, int day, int currentDay, int hour, int currentHour, int minutes, int currentMin) {
    // Fun��o que recebe os minutos do agendamento e verifica se estes s�o validos, retornando a vari�vel "minutes" 
    // corrigida ou sem altera��es.
    while (1) {
        if (minutes >= 60 || minutes < 0 || (year == currentYear && month == currentMonth && day == currentDay &&
        hour == currentHour && minutes < currentMin)) {
        printf("|Formato invalido, por favor tente novamente.\n"
        "|---------------------------------\n"
        "|Minutos: ");
        scanf("%d", &minutes);
        } else {
            return minutes;
        }
    }
    return 1;
}

int scheduler(int currentYear, int currentMonth, int currentDay, int currentHour, int currentMin) {
	// Fun��o respons�vel por gerar os agendamentos, armazenando as datas e hor�rios na v�riavel tempor�ria "newStuff", e depois os transportando ap�s uma verifica��o
    // para a vari�vel de armazenamento "storeSchedules", e o nome em "newName" para a vari�vel de armazenamento "Names". 
    int i, j, found = 0, hour, minutes, day, month, year;

    while (1) {
        if (space >= max_schedule) {
            printf("|---------------------------------\n"
            "|Limite de Agendamentos Atingido! (%d)\n"
            "|---------------------------------\n", space);
        }

        getName(0, 0);

        printf("|---------------------------------\n"
        "|Ano: ");
        scanf(" %d", &year);
        year = fetchYear(year, currentYear);
        newStuff[3] = year;

        printf("|---------------------------------\n"
        "|Mes: ");
        scanf("%d", &month);
        month = fetchMonth(year, currentYear, month, currentMonth);
        newStuff[2] = month;

        printf("|---------------------------------\n"
        "|Dia: ");
        scanf("%d", &day);
        day = fetchDay(year, currentYear, month, currentMonth, day, currentDay);
        newStuff[1] = day;

        printf("|---------------------------------\n"
        "|Hora: ");
        scanf("%d", &hour);
        hour = fetchHour(year, currentYear, month, currentMonth, day, currentDay, hour, currentHour);
        newStuff[4] = hour;

        printf("|---------------------------------\n"
        "|Minutos: ");
        scanf("%d", &minutes);
        minutes = fetchMin(year, currentYear, month, currentMonth, day, currentDay, hour, currentHour, minutes, currentMin);
        newStuff[5] = minutes;

        if (scheduleCheck() != -1) {
            printf("|Horario Indisponivel, tente novamente\n");
            clearBuffer();
			} else {
                strcpy(names[space], newName);
                newStuff[0] = generateCode();
                for (j = 0; j < 6; j++) {
                    storeSchedules[space][j] = newStuff[j];
                }
                return 0;
            }
        }
    return 1;
}

int erase() {
    // Fun��o que apaga um agendamento, enviando os agendamentos e nomes ap�s o requisitado uma posi��o "para cima" na matriz, e apagando o 
    // �ltimo valor que foi duplicado.
    int i, j, index = 0, code = 0, temp;
    char choice;
    
    if (space == 0) {
        printf("|---------------------------------\n"
        "|Sistema vazio!\n"
        "|---------------------------------\n");
    } else {
        printf("|---------------------------------\n"
        "|Informe o codigo: ");
        scanf(" %d", &code);
        index = lookUpId(code);
        
        if (index != -1) {
        	printf("|Agendamento a ser apagado: \n");
        	consulting(0, index);
        	printf("|Voce realmente quer apagar? [y/n]\n"
			"|Escolha: ");
        	scanf(" %c", &choice);
        	if (choice == 'y' || choice == 'Y') {
        		temp = space;
	            for (i = index; i < temp - 1; i++) {
	                for (j = 0; j < 6; j++) {
	                    storeSchedules[i][j] = storeSchedules[i+1][j];
	                }
	            }
	            for (i = index; i < temp - 1; i++) {
	                strcpy(names[i], names[i+1]);
	                
	            }
	            for (j = 0; j < 6; j++) {
	                storeSchedules[temp-1][j] = 0;
	            }
	            strcpy(names[temp-1], "");
	            
	            printf("|Produto apagado com sucesso!\n"
	            "|---------------------------------\n");
	            space--;
	            return 0;
			} else {
				printf("|---------------------------------\n");
				return 2;
			}
        }
    }
    return 1;
}

void displayOptions() {
    // Fun��o que escreve na tela as op��es de atualiza��o de um agendamento.
    printf("|Voce deseja atualizar:\n"
    "|1. Dia\n"
    "|2. Mes\n"
    "|3. Ano\n"
    "|4. Hora\n"
    "|5. Minutos\n"
    "|6. Nome\n"
    "|7. Sair\n"
    "|Escolha: ");
}

int editing(int currentYear, int currentMonth, int currentDay, int currentHour, int currentMin) {
    // Fun��o que permite a atualiza��o de um agendamento, permitindo a mudan�a de todos os seus atributos menos o seu c�digo.
    // Ap�s uma altera��o, os resultados s�o printados no console.
    int i, index = 0, code = 0, choice = 0;
    int hour, minutes, day, month, year;
    
    if (space == 0) {
        printf("|---------------------------------\n"
        "|Sistema vazio!\n"
        "|---------------------------------\n");
    } else {
        printf("|---------------------------------\n"
        "|Informe o codigo: ");
        scanf("%d", &code);
        index = lookUpId(code);
        
        if (index != -1) {
            for (i = 0; i < 6; i++) {
                newStuff[i] = storeSchedules[index][i];
            }
            consulting(0, index);
            do {
                displayOptions();
                scanf("%d", &choice);
                switch(choice) {
                    case 1:
                        printf("|---------------------------------\n"
                        "|Dia: ");
                        scanf("%d", &day);
                        newStuff[1] = fetchDay(year, currentYear, month, currentMonth, day, currentDay);
                        break;
                    case 2:
                        printf("|---------------------------------\n"
                        "|Mes: ");
                        scanf("%d", &month);
                        newStuff[2] = fetchMonth(year, currentYear, month, currentMonth);
                        break;
                    case 3:
                        printf("|---------------------------------\n"
                        "|Ano: ");
                        scanf("%d", &year);
                        newStuff[3] = fetchYear(year, currentYear);
                        break;
                    case 4:
                        printf("|---------------------------------\n"
                        "|Hora: ");
                        scanf("%d", &hour);
                        newStuff[4] = fetchHour(year, currentYear, month, currentMonth, day, currentDay, hour, currentHour);
                        break;
                    case 5:
                        printf("|---------------------------------\n"
                        "|Minutos: ");
                        scanf("%d", &minutes);
                        newStuff[5] = fetchMin(year, currentYear, month, currentMonth, day, currentDay, hour, currentHour, minutes, currentMin);
                        break;
                    case 6:
                        clearBuffer();
                        getName(1, index);
                        break;
                    case 7:
                        break;
                    default:
                        printf("|---------------------------------\n"
                        "Operacao desconhecida, por favor tente novamente.\n"
                        "|---------------------------------\n");
                }
                if (choice > 0 && choice < 6 && scheduleCheck(space) != -1) {
                    printf("|Horario Indisponivel, tente novamente\n"
                    "|---------------------------------\n");
                } else {
                    if (choice > 0 && choice < 6) {
                        for (i = 0; i < 6; i++) {
                            storeSchedules[index][choice] = newStuff[choice];
                        }
                    } 
                    if (choice != 7) {
                        consulting(0, index);
                    }
                }
            } while (choice != 7);
            printf("|---------------------------------\n");
            return 0;
        }
    }
    return 1;
}

void displayAll() {
    // Fun��o adicional de qualidade de vida, mostra todos os agendamentos e seus c�digos.
    int i;
    if (space == 0) {
        printf("|---------------------------------\n"
        "|Sistema vazio!\n"
        "|---------------------------------\n");
    }
    for (i = 0; i < space; i++) {
        printf("|---------------------------------\n"
        "|Codigo: %d\n", storeSchedules[i][0]);
        consulting(0, i);
    }
}

void displayMenu() {
    // Fun��o que apresenta um "menu" do programa no console, com todas as suas features, o atual n�mero de agendamentos
    // presentes no sistema e o m�ximo de agendamentos poss�veis.
    printf("|Agendamentos: %d/%d\n"
    "|O que voce gostaria de fazer?\n"
    "|1. Cadastrar\n"
    "|2. Consultar\n"
    "|3. Atualizar\n"
    "|4. Excluir\n"
    "|5. Todos os Agendamentos\n"
    "|6. Sair\n"
	"|Escolha: ", space, max_schedule);
}

int main() {
    // Fun��o main que permite a escolha de uma funcionalidade do programa, define os par�metros de tempo, confirma a adi��o 
    // de um cadastro somando a vari�vel "space" e possui uma op��o de encerrar o programa.
	int choice = 0;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int currentYear = t->tm_year + 1900;
    int currentMonth = t->tm_mon + 1;
    int currentDay = t->tm_mday;
    int currentHour = t->tm_hour;
    int currentMin = t->tm_min;

    printf("|---------------------------------\n"
    "|Bem-vindo ao Salao Lambimia     |\n"
    "|---------------------------------\n");
    displayMenu();

    do {
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                if (scheduler(currentYear, currentMonth, currentDay, currentHour, currentMin) == 0) {
                    space++;
                    printf("|---------------------------------\n"
                    "|Horario agendado com sucesso!\n"
                    "|Codigo: %d\n", storeSchedules[space-1][0]);
                    consulting(0, space - 1);
                }
                break;
            case 2:
                consulting(1, 0);
                break;
            case 3:
                editing(currentYear, currentMonth, currentDay, currentHour, currentMin);
                break;
            case 4:
                erase();
                break;
            case 5:
                displayAll();
                break;
            case 6:
                printf("|---------------------------------\n"
                "|Obrigado por utilizar nosso sistema!\n"
                "|---------------------------------\n");
                exit(0);
                break;
            default:
                printf("|---------------------------------\n"
                "|Operacao desconhecida, por favor tente novamente.\n"
                "|---------------------------------\n");
        }
        
        displayMenu();

    } while (1);

    return 0;
} 
