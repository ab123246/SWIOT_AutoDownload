#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"codecvt_char.h"

using namespace std;
int get_caseAd (char* st){
	FILE *fp;
	//�Y�L���� c:\\test1.txt , �e���|�@�{�ӹL(�S��ܰT��) 
	if((fp=fopen( st , "r")) == NULL){
		printf("���{���䤣���ɮסA�Ч�{���]�p�̸߰�\t");
		return 0;
	}
	bool go_on = false;
	char ch;
	//string check_text = "";
	char check_text_char[10000];
	check_text_char[0] = '\0';
	int check_text_char_index = 0;
	while((ch = fgetc(fp)) != EOF){ //Ū������ɮ� (�����ɮ׵���) , �C��Ū�X�@�Ӧr��  
    	if(!go_on){
    		if(ch == '<'){
    			//check_text = "";
    			check_text_char_index = 0;
    			check_text_char[check_text_char_index] = '\0';
    			while((ch = fgetc(fp))!=' ' && ch != '>' && ch != EOF){
    				//check_text += ch;
    				check_text_char[check_text_char_index] = ch;
    				check_text_char[++check_text_char_index] = '\0';
    			}
    			//if(strcmp(check_text.c_str(),"node") == 0){
    			if(strcmp(check_text_char,"node") == 0){
    				bool marker = false;
    				//while(!(strcmp(check_text.c_str(),"</node") == 0)){
    				while(!(strcmp(check_text_char,"</node") == 0)){
    					//check_text = "";
    					check_text_char_index = 0;
						check_text_char[check_text_char_index] = '\0';
    					
    					//string get_check_text = "";
    					char get_check_text_char[100000];
    					int get_check_text_char_index = 0;
    					get_check_text_char[get_check_text_char_index] = '\0';
    					while((ch = fgetc(fp))!='=' && ch != ' ' && ch != '>' && ch != EOF){
		    				//check_text += ch;
		    				check_text_char[check_text_char_index] = ch;
    						check_text_char[++check_text_char_index] = '\0';
		    			}
		    			if(ch == '='){
		    				if((ch = fgetc(fp)) == '"')
		    					marker = true;
		    				while(marker){
		    					if((ch = fgetc(fp)) == '"')
		    						break;
		    					//get_check_text += ch;
		    					get_check_text_char[get_check_text_char_index] = ch;
    							get_check_text_char[++get_check_text_char_index] = '\0';
		    				}
		    				/*if(strlen(check_text.c_str()) <= 9)
		    					printf("�{�����Ѽ�: %s\t\t���ޭ�: %s\n",check_text.c_str(),get_check_text.c_str());
		    				else
		    					printf("�{�����Ѽ�: %s\t���ޭ�: %s\n",check_text.c_str(),get_check_text.c_str());*/
		    				char buffer[200000];
		    				codecvt_char codecvtc ;
							buffer[0]='\0';
							strcat(buffer,codecvtc.UTF8ToBIG5(get_check_text_char));
							get_check_text_char[0] = '\0';
							strcat(get_check_text_char,buffer);
		    				if(strlen(check_text_char) <= 9)
		    					printf("�{�����Ѽ�: %s\t\t���ޭ�: %s\n",check_text_char,get_check_text_char);
		    				else
		    					printf("�{�����Ѽ�: %s\t���ޭ�: %s\n",check_text_char,get_check_text_char);
							//cout << "�{�����Ѽ�: " << check_text << "\t���ޭ�: " << get_check_text << endl; 
		    			}
    				}
    			}
    		}
    	}
	}
	fclose(fp);  //���� 
}


int get_node(char* st){
	string str1 = "";
	string str2 = "";
	string str3 = "";
	string str4 = "";
	
	FILE *fp;
	
	//�Y�L���� c:\\test1.txt , �e���|�@�{�ӹL(�S��ܰT��) 
	if((fp=fopen( st , "r")) == NULL){
		printf("���{���䤣���ɮסA�Ч�{���]�p�̸߰�\t");
		return 0;
	}
	bool go_on = false;
	bool print_coordi = false;
	char ch;
	string check_text = "";
	while((ch = fgetc(fp)) != EOF){	//Ū������ɮ� (�����ɮ׵���) , �C��Ū�X�@�Ӧr��  
   		if(ch == '<'){
   			check_text = "";
			while((ch = fgetc(fp))!=' ' && ch != '>' && ch != EOF){
   				check_text += ch;
   			}
			if(strcmp(check_text.c_str(),"node") == 0){
    			bool marker = false;
    			while(!(strcmp(check_text.c_str(),"</node") == 0)){
    				check_text = "";
					string get_check_text = "";
					while((ch = fgetc(fp))!='=' && ch != ' ' && ch != '>' && ch != EOF){
	    				check_text += ch;
	    			}
	    			if(ch == '='){
	    				if((ch = fgetc(fp)) == '"')
	    					marker = true;
	    				while(marker){
	    					if((ch = fgetc(fp)) == '"')
	    						break;
	    					get_check_text += ch;
	    				}
						if(strcmp(get_check_text.c_str(),"com.android.vending:id/li_overflow") == 0){
							print_coordi=true;								
						}else if(strcmp(check_text.c_str(),"bounds")==0 && print_coordi){
							print_coordi=false;
							return get_check_text.c_str(); 
						}		    			
					}
    			}
    		}
    	}
    }
	fclose(fp);  //����
}

int coordinum(char *str){
string coordi = "";
string cr="adb shell input tap ";
string buffer[2];
int index = 0;
int num1=0;
	while(1){
		if(*(str+num1) != '[' && *(str+num1)!= ']' && *(str+num1)!= ','){
			//coordi+=*(s+num1);
			buffer[index] += *(str+num1);
		}else if(*(str+num1)==','){
			//coordi+=" ";
			index = 1;
		}else if(*(str+num1)==']'){
			break;
		}
		num1++;
	}
	cr += buffer[0];
	cr += " ";
	cr += buffer[1];
	system(cr.c_str());
	cout << cr << endl;
	cr= buffer[1];
	int num_buff = atof(cr.c_str())+150;
	char buffer2[100];
	sprintf(buffer2,"%d",num_buff);
	cr = "";
	cr += "adb shell input tap ";
	cr += buffer[0];
	cr += " ";
	cr += buffer2;
	system(cr.c_str());
		
	//str.insert(0 , cr , 0 , *str);
	
}

int main(){
	char cr[99];
	char cr1[5]="END;";
	string cr2="adb shell input text ";
	string str;
	bool done;
	
	FILE *fp; 
	fp = fopen("SWIOT.txt", "r");
	system("adb shell input keyevent KEYCODE_APP_SWITCH");
	
	while(1){
		done = true;
		fgets(cr,99,fp);
		for(int loopnum1 = 0;loopnum1 < strlen(cr1);loopnum1++){
			if(cr[loopnum1] != cr1[loopnum1]){
				done = false;
				break;
			}	
		}
		if(done)
			break;//�p�GŪ�X�Ӫ��Ȭ�END;�N�����j�� 
		str.assign(cr);
		str.insert(0 , cr2 , 0 , cr2.length());//�NŪ�X���r��[�Jadb shell input text  
		system("adb shell am start -n com.android.vending/com.google.android.finsky.activities.MainActivity");
		system("adb shell input tap 300 200");
		system(str.c_str());
    	system("adb shell input keyevent 66");
    	system("adb shell uiautomator dump");
    	system("adb pull /sdcard/window_dump.xml ./filename.xml");
    	char* _coordi = get_node("filename.xml");
    	coordinum(_coordi);
    	//check_access();
		//check_wifidownload();
    	system("adb shell input keyevent 4");
    	system("adb shell input keyevent 4");
	}
	cout<<endl<<"finished!!";
	fclose(fp);
}