#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char msg[20], cmsg[20], dmsg[20], omsg[20];
int encrypt[1][2], decrypt[1][2], key[2][2], D_Key[2][2], mes[20], crypt[1][2], dc[1][2], c[2][2], z[2][2];
 
int determinant_pos(int);	//encrypts the message
void check_matrix(int a[2][2]);	//decrypts the message
void getKeyMessage();	//gets key and message from user
int inverse_modulo(int);
void inverse_confactor(int a[2][2]);
void cofactor(int d);		//finds inverse of key matrix
void printingkey(int a[2][2]);
void encryption();
void decryption();

void check_matrix(int a[2][2]){
	int cal;
	int det = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	printf("%d determinant \n", det);
	if (det < 0){	
		 cal = determinant_pos(det) % 26;
		printf("%d is its inverse \n", cal);
	}
	else{ cal = det % 26;
	printf("%d determinant eta \n", cal);	
	}
	
	if (cal == 1 || cal == 3 || cal == 5 || cal == 7 || cal == 9 || cal == 11 || cal == 15 || cal == 17 || cal == 19 || cal == 21 || cal == 23)
	{
		printf("\nThe matrix is valid\n");
		printf("\nInverse modulo of %d is %d \n", cal, inverse_modulo(cal));
		inverse_confactor(a);
		cofactor(inverse_modulo(cal));	
	}	
	else{
		printf("Invalid matrix");		
		exit(0);}
}

void inverse_confactor(int a[2][2]){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++) {
			if (i == j){c[i][j] = a[(i+1)%2][(j+1)%2];}			
			if ( i != j ){c[i][j] = a[i][j] * -1;
					c[i][j] = determinant_pos(c[i][j]) % 26;}
					
		}
	}
}

int determinant_pos(int det){
	int r, i = 1;
	while(det < 0 ){
		det = det + (i * 26);  
		i++;
	}
	return det;	
}
int inverse_modulo(int cal){
	for (int i = 1; i < 26; i++){	
		if (((cal%26)*(i%26)) % 26 == 1){

		return i;
		}
	}
}
void cofactor(int d){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++) {
			D_Key[i][j] = (d * c[i][j]) % 26;
		}
	}
}
void getKeyMessage() {
	int i, j;
 
	printf("Enter 2x2 matrix for key (It should be inversible):\n");
	
	for(i = 0; i < 2; i++)
		for(j = 0; j < 2; j++) {
			scanf("%d", &key[i][j]);
			z[i][j] = key[i][j];
		}
	
	check_matrix(key);
	
}
void printingkey(int a[2][2]){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++) {
			printf("%d\t", a[i][j]);
		}
	printf("\n");
	}
}



void encryption() {
	int i, j, k, m_loop;
	char ch;
	for(m_loop = 0; m_loop < strlen(msg); m_loop = m_loop + 2){
		
		crypt[0][0] = mes[m_loop];
		crypt[0][1] = mes[m_loop + 1];

		printf("\n\n %d %d ", crypt[0][0], crypt [0][1]);	
		for(i = 0; i < 1; i++){
			for(j = 0; j < 2; j++){
				for(k = 0; k < 2; k++)
					{encrypt[i][j] = encrypt[i][j] + crypt[i][k] * z[k][j];}
				}		
		printf(" encoded to %d %d \n", encrypt[0][0] % 26, encrypt [0][1] % 26);		
	}
		for(int l = 0 ; l < 2; l++){
			ch = (char) ((encrypt[0][l] % 26) + 97);
			printf("%c", ch);			
			strncat(cmsg , &ch, 1);
			encrypt[0][l] = 0;} 

	};

	printf("\nEncrypted string is:  %s\n", cmsg);
	
 
}
 
void decryption() {
	int i, j, k, m_loop;
	char ch;
	for(m_loop = 0; m_loop < strlen(cmsg); m_loop = m_loop + 2){
	
		dc[0][0] = cmsg[m_loop] - 97;
		dc[0][1] = cmsg[m_loop + 1] - 97;

		printf("\n\n %d %d ", dc[0][0], dc[0][1]);	
		for(i = 0; i < 1; i++){
			for(j = 0; j < 2; j++){
				for(k = 0; k < 2; k++)
					{decrypt[i][j] = decrypt[i][j] + dc[i][k] * D_Key[k][j];}
				}		
		printf(" decoded to %d %d \n\n", decrypt[0][0] % 26, decrypt [0][1] % 26);		
	}
		for(int l = 0 ; l < 2; l++){
			ch = (char) ((decrypt[0][l] % 26) + 97);
			printf("%c", ch);			
			strncat(dmsg , &ch, 1);
			decrypt[0][l] = 0;} 

	};

	printf("\ndecrypted string is:  %s\n", dmsg);
}

int main(int argc, char *argv[])
{
	
	if (argc != 2){
		printf("Provide option to decrypt or encrypt \n");
		return 1;
	}

	
	
	getKeyMessage();
	printingkey(z);
	printf("\n Key for Decryption: D_key is\n");
	printingkey(D_Key);
	
	

	
	if (strcmp (argv[1],"-e") == 0 ){
		// encrypt using Playfair Cipher
		printf("\nEnter a string to encrypt: ");
		scanf("%s", msg);
		
		for(int i = 0; i < strlen(msg); i++)
		{	mes[i] = msg[i] - 97;
			}

		encryption();
	}

	else if (strcmp (argv[1],"-d") == 0 ){
		printf("\nEnter a string to decrypt: ");
		scanf("%s", omsg);
		for(int i = 0; i < strlen(omsg); i++)
		{	cmsg[i] = omsg[i];
			}
		decryption();	
	}
	else{
	printf("Unknown arguments\n");
	
	}
	
	

	return 0;
}


 
