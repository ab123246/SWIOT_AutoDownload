#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"codecvt_char.h"

using namespace std;

int get_caseAd (char* st){
FILE *fp;
	
	//若無此檔 c:\\test1.txt , 畫面會一閃而過(沒顯示訊息) 
	if((fp=fopen( st , "r")) == NULL){
		printf("此程式找不到檔案，請找程式設計者詢問\t");
		return 0;
	}
	bool checkboxoff=false;
	bool go_on = false;
	char ch;
	//string check_text = "";
	char check_text_char[10000];
	check_text_char[0] = '\0';
	int check_text_char_index = 0;
	while((ch = fgetc(fp)) != EOF){ //讀取整個檔案 (直到檔案結尾) , 每次讀出一個字元  
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
		    					printf("程式抓到參數: %s\t\t索引值: %s\n",check_text.c_str(),get_check_text.c_str());
		    				else
		    					printf("程式抓到參數: %s\t索引值: %s\n",check_text.c_str(),get_check_text.c_str());*/
		    				char buffer[200000];
		    				codecvt_char codecvtc ;
							buffer[0]='\0';
							strcat(buffer,codecvtc.UTF8ToBIG5(get_check_text_char));
							get_check_text_char[0] = '\0';
							strcat(get_check_text_char,buffer);
							if(strcmp(check_text_char,"com.android.vending:id/wifi_checkbox") == 0){
								system("adb shell input tap 156 1074");
								checkboxoff = true;
							}
							if(checkboxoff){
								if(strcmp(get_check_text_char,"繼續"))
									return 2;
								else if(strcmp(get_check_text_char,"com.android.vending:id/continue_button"))
									return 3;
							}
		    			}
    				}
    			}
    		}
    	}
	}
	fclose(fp);  //關檔 
}

int get_node(char* st){
	string str1 = "";
	string str2 = "";
	string str3 = "";
	string str4 = "";
	
	FILE *fp;
	
	//若無此檔 c:\\test1.txt , 畫面會一閃而過(沒顯示訊息) 
	if((fp=fopen( st , "r")) == NULL){
		printf("此程式找不到檔案，請找程式設計者詢問\t");
		return 0;
	}
	bool go_on = false;
	bool print_coordi = false;
	char ch;
	string check_text = "";
	while((ch = fgetc(fp)) != EOF){	//讀取整個檔案 (直到檔案結尾) , 每次讀出一個字元  
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
	fclose(fp);  //關檔
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
			break;//如果讀出來的值為END;就結束迴圈 
		str.assign(cr);
		str.insert(0 , cr2 , 0 , cr2.length());//將讀出的字串加入adb shell input text  
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
