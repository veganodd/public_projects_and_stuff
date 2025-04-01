#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <direct.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LENGTH 50

int used[10];
char name[MAX_LENGTH];
char words[10][MAX_LENGTH];
char fileName[] = "saves\\savegame.bin";
int regiwords = 0, hp = 6, ua = 0;

const char hang[4][15] = {
    "|-----|",
    "|     O",
    "|    /I\\",
    "|    / \\"
};

char tempHang[4][15];

int emptyMsg(){
    if (!regiwords){
        printf("Nenhuma palavra registrada no sistema, carregue um salvamento ou registre uma palavra!\n");
        return 1;
    }
    return 0;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void upper(char *str){
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int find_equal(char *str){
    int i;
    for (i = 0; i < regiwords; i++){
        if (strcmp(words[i], str) == 0){
            return 1;
        }
    }
    return 0;
}

int check_palavra(char *str) {
    if (str[0] == '\0' || str[0] == '\n') {
        return 1;
    }
    return 0;
}

void load_game(){
    FILE *file = fopen(fileName, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo de salvamento\n");
        return;
    }

    if (fread(&regiwords, sizeof(int), 1, file) != 1) {
        printf("Erro lendo o número de palavras registradas\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < regiwords; i++) {
        if (fread(words[i], sizeof(char), MAX_LENGTH, file) != MAX_LENGTH) {
            printf("Erro lendo palavras\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Jogo carregado com sucesso!\n");
}

void save_game() {
    FILE *file;

    file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Erro, arquivo .bin nao foi criado\n");
        return;
    }

    if (fwrite(&regiwords, sizeof(int), 1, file) != 1) {
        printf("Erro ao salvar o número de palavras\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < regiwords; i++) {
        if (fwrite(words[i], sizeof(char), MAX_LENGTH, file) != MAX_LENGTH) {
            printf("Erro ao salvar a palavra %d\n", i);
            fclose(file);
            return;
        }
    }

    printf("Jogo salvo com sucesso em %s\n", fileName);
    fclose(file);
}

void cad_word(int type, int choice){
    if (regiwords >= 10 && type == 0) {
        printf("Limite de palavras atingido!\n");
        return;
    }
    
    int i;
    bool found = true;
    char new[50];

    printf("Palavra: ");
    clearBuffer();
    fgets(new, sizeof(new), stdin);
    new[strcspn(new, "\n")] = '\0';
    upper(new);

    while (check_palavra(new) || strlen(new) < 5 || find_equal(new)) {
        printf("Palavra vazia, menor que cinco caracteres ou igual a outra cadastrada, tente novamente\nPalavra: ");
        fgets(new, sizeof(new), stdin);
        new[strcspn(new, "\n")] = '\0';
        upper(new);
    }

    if (!type){
        strcpy(words[regiwords], new);
        regiwords++;
    } else{
        strcpy(words[choice], new);
    }
}

void see_all(){
    int i;
    if (emptyMsg()){
        return;
    } else {
        printf("\n");
        for (i = 0; i < regiwords; i++){
        printf("Palavra %d: %s\n", i + 1, words[i]);
        }
    }
}

void update_word(){
    int choice;
    if (emptyMsg()){
        return;
    }

    see_all();

    printf("Você deseja atualizar qual palavra?\n"
    "Escolha: ");
    scanf("%d", &choice);
    cad_word(1, choice - 1);
}

int del_one(){
    int i, index;
    printf("Digite o número da palavra: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= regiwords) {
        printf("Índice inválido!\n");
        return 1;
    }

    for (i = index; i < regiwords - 1; i++) {
	    strcpy(words[i], words[i+1]);
	}
    regiwords--;

    return 0;
}

void delete_word(){
    int choice, i;
    if (emptyMsg()){
        return;
    }

    see_all();

    while (1) {
        printf("Você deseja deletar\n"
        "1. Uma palavra\n"
        "2. Todas as palavras\n"
        "3. Sair\n"
        "Escolha: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                if (del_one() == 1){
                    printf("Erro realizando a operação.\n");
                    return;
                } else {
                    printf("Operação realizada com sucesso\n");
                    return;
                }
                break;
            case 2:
                regiwords = 0;
                printf("Operação realizada com sucesso\n");
                return;
                break;
            case 3:
                return;
                break;
            default:
                printf("Opção inexistente, tente novamente.\n");
                break;
        }
    }
}

void hangman(){
    int i;
    for (i = 0; i < 4; i++){
        printf("%s\n", tempHang[i]);
    }
}

void resetHang(){
    int i;
    for (i = 0; i < 4; i++) {
        strcpy(tempHang[i], hang[i]);
    }
}

void states(){
    switch (hp) {
        case 5: // Remove a perna direita
            tempHang[3][7] = ' ';
            break;
        case 4: // Remove a perna esquerda
            tempHang[3][5] = ' ';
            break;
        case 3: // Remove o braço direito
            tempHang[2][7] = ' ';
            break;
        case 2: // Remove o braço esquerdo
            tempHang[2][5] = ' ';
            break;
        case 1: // Remove o corpo
            tempHang[2][6] = ' ';
            break;
        case 0: // Remove a cabeça
            tempHang[1][6] = ' ';
            break;
        default:
    }
}

int generateRandom(){
    if (ua >= 10) {
        printf("Todas as palavras já foram usadas!\n");
        return -1;
    }
    
    bool isUsed;
    int i, n;

    do {
        n = rand() % 10;
        isUsed = false;

        for (i = 0; i < ua; i++){
            if (n == used[i]){
                isUsed = true;
                break;
            }
        }
    } while (isUsed);

    return n;
}

void game(){
    if (emptyMsg()){
        return;
    }
    
    if (regiwords < 10){
        printf("O jogo não pode ser iniciado com menos de 10 palavras\n"
        "Palavras no sistema: %d\n", regiwords);
        return;
    }

    int random, i;
    if ((random = generateRandom()) == -1) {
        return;
    }

    resetHang();

    char guess, guess_word[50], palpites[50];

    strcpy(guess_word, words[random]);
    
    for(i = 0; guess_word[i] != '\0'; i++){
    	guess_word[i] = '_';
	}
	
	for(i = 0; words[random][i] != '\0'; i++){
		if(words[random][i] == ' '){
			guess_word[i] = ' ';
		}
	}
	
	int cont_palpites = 0, check = 0, check_palp = 0;

    while (hp > 0){
    	
    	check = 0;
    	
    	for(i = 0; guess_word[i] != '\0'; i++){
    		printf("%c ", guess_word[i]);
		}
		printf("\n");
    	
        hangman();
        
        printf("Palpite: ");
        
        if(cont_palpites != 0){
        	
	       	while(1){
	       		
	        	scanf(" %c", &guess);
	        	
	        	guess = toupper(guess);
	        	
	        	check_palp = 0;
	        	
	        	for(i = 0; i < cont_palpites; i++){
	        		if(guess == palpites[i]){
	        			printf("Este palpite já foi utilizado, tente novamente: ");
	        			check_palp = 1;
	        			break;
					}
				}
				
				if(!check_palp){
					break;
				}
			}
			
		} else {
			scanf(" %c", &guess);
			guess = toupper(guess);
		}

        for(i = 0; guess_word[i] != '\0'; i++){
            if (guess == words[random][i]){
                guess_word[i] = words[random][i];
                check = 1;
            } else {
            	if(check == 1){
            		continue;
				} else {
					check = 2;
				}
                
            }
        }
        
        if(check == 2){
        	hp--;
            states();
            check = 0;
		}

        if(strcmp(guess_word,words[random]) == 0){
            hp = 6;
            printf("\nVocê acertou em %d palpites.\nA palavra era %s.\nParabéns!\n", cont_palpites + 1, guess_word);
            used[ua++] = random;
            return;
        }
        
        palpites[cont_palpites] = guess;
        
        cont_palpites++;
        
        printf("\nPalpites anteriores: ");
        for (int i = 0; i < cont_palpites; i++){
        	printf("%c, ", palpites[i]);
		}
		printf("\n");
    }

    if (!hp){
        hangman();
        printf("\nGame Over!\nVocê errou a palavra em %d palpites\nA Palavra era %s\n", cont_palpites, words[random]);
        hp = 6;
        return;
    }
}

void menu(int type){
    switch (type) {
        case 0:
            ua = 0;
            printf("\nJogo da Forca\n");
            hangman();
            printf("\n1. Jogar\n"
            "2. Carregar\n"
            "3. Salvar\n"
            "4. Cadastrar Palavra\n"
            "5. Ver Todas as Palavras\n"
            "6. Atualizar Palavra\n"
            "7. Apagar Palavra\n"
            "8. Sair\n"
            "Escolha: ");
            break;
        case 1:
            printf("\n1. Jogar\n"
            "2. Menu Principal\n"
            "3. Sair\n"
            "Escolha: ");
            break;
    }
}

void exit_msg(){
    char option;
    printf("Você deseja salvar? [y/n]\n"
    "Escolha: ");
    scanf(" %c", &option);
    if (option == 'Y' || option == 'y'){
        save_game();
    }
    printf("Obrigado por jogar!\n");
    exit(0);
}

int second_menu(){
    int choice;
    while (1) {
        menu(1);
        scanf(" %d", &choice);
        switch(choice) {
            case 1:
                game();
                break;
            case 2:
                return 1;
                break;
            case 3:
                exit_msg();
                break;
        }
    }
}
 
int main(){
    setlocale(LC_ALL, "pt_BR");
    system("chcp 1252 > null");
    srand(time(NULL));

    int choice;
    resetHang();
    while (1){
        menu(0);
        scanf(" %d", &choice);
        switch (choice){
            case 1:
                while (1){
                    game();
                    if (second_menu()){
                        break;
                    }
                }
                break;
            case 2:
                load_game();
                break;
            case 3:
                save_game();
                break;
            case 4:
                cad_word(0, 0);
                break;
            case 5:
                see_all();
                break;
            case 6:
                update_word();
                break;
            case 7:
                delete_word();
                break;
            case 8:
                exit_msg();
                break;
            default:
                printf("Opção inexistente, tente novamente\n");
                break;
        }
    }
    return 0;
}