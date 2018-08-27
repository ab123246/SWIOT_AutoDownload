#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;


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
	cout << buffer2 << endl;
	cr = "";
	cr += "adb shell input tap ";
	cr += buffer[0];
	cr += " ";
	cr += buffer2;
	system(cr.c_str());
		
	//str.insert(0 , cr , 0 , *str);
	
}

int getstringlength(char *s){
	int num1 = 0;
	while(1){
		if(*(s+num1) == '\0')
			break;
		num1++;
	}
	return num1;
}

void doumean(){
	bool done;
	char cr[99];
	char cr1[10]="是不是要查";
	system("adb shell uiautomator dump");
	system("adb pull /sdcard/window_dump.xml ./filename.xml");
	FILE *fp;
	fp = fopen("filename.xml", "r");
	while(1){
		done = true;
		fgets(cr,99,fp);
		for(int loopnum1 = 0;loopnum1 < getstringlength(cr1);loopnum1++){
			if(cr[loopnum1] != cr1[loopnum1]){
				done = false;
				break;
			}
		}
	}
}

int main(){
	char cr[99];
	char cr1[5]="END;";
	string cr2="adb shell input text ";
	string str;
	bool done;
	
	FILE *fp; 
	fp = fopen("SWIOT.txt", "r");
	while(1){
		done = true;
		fgets(cr,99,fp);
		for(int loopnum1 = 0;loopnum1 < getstringlength(cr1);loopnum1++){
			if(cr[loopnum1] != cr1[loopnum1]){
				done = false;
				break;
			}	
		}
		if(done)
			break;
		str.assign(cr);
		str.insert(0 , cr2 , 0 , cr2.length());
		system("adb shell am start -n com.android.vending/com.google.android.finsky.activities.MainActivity");
		system(str.c_str());
    	system("adb shell input keyevent 66");
    	system("adb shell uiautomator dump");
    	system("adb pull /sdcard/window_dump.xml ./filename.xml");
    	char* _coordi = get_node("filename.xml");
    	coordinum(_coordi);
    	//check_access();
		//check_wifidownload();
		system("adb shell input tap 672 833");
    	system("adb shell input keyevent 4");
    	system("adb shell input keyevent 4");
	}
	cout<<endl<<"finished!!";
	fclose(fp);
}
